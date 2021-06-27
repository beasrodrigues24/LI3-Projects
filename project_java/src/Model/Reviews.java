package Model;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.Serializable;
import java.util.*;
import java.util.stream.Collectors;

import static java.util.stream.Collectors.*;

public class Reviews implements ReviewsInterface, Serializable {

    /**
     * Fields
     */
    private Map<String, ReviewInterface> reviews_table;
    private Set<String> users_ids;
    private Map<String, BusinessInterface> businesses;

    private static int invalid_reviws = 0;

    /**
     * Empty Constructor
     */
    public Reviews() {
        this.reviews_table = new Hashtable<>();
        this.users_ids = new HashSet<>();
        this.businesses = new Hashtable<>();
    }

    /**
     * Verifies if a certain review exists through its id
     * @param review_id Review-id
     * @return 1 if it exists, 0 if not
     */
    public boolean exists_review(String review_id) {
        return this.reviews_table.containsKey(review_id);
    }

    /**
     * Searches for certain review through its id
     * @param review_id Review-id
     * @return ReviewInterface
     */
    public ReviewInterface lookup_review(String review_id) {
        return this.reviews_table.get(review_id).clone();
    }

    /**
     * Getter of the number of reviews
     * @return Number of reviews
     */
    public int get_n_reviews() {
        return this.reviews_table.size();
    }

    /**
     * getter of the number of invalid reviews
     * @return number of invalid reviews
     */
    public int getInvalid_reviws() {
        return this.invalid_reviws;
    }

    /**
     * Setter of users-ids
     * @param users_ids Set users-ids
     */
    public void set_users_ids(Set<String> users_ids) {
        this.users_ids.addAll(users_ids);
    }

    /**
     * Setter of the map businesses
     * @param businesses Map businesses
     */
    public void set_businesses_interface(Map<String, BusinessInterface> businesses) {
        this.businesses.putAll(businesses); // Doesn't clone because clone was previously made in another function
    }

    /**
     * Reads the Reviews' file
     * @param filepath Filepath to the Reviews' file
     * @throws IOException in case I/O failed
     */
    public void read_reviews_file(String filepath) throws IOException {

        BufferedReader inFile = new BufferedReader(new FileReader(filepath));
        String review_buffer;
        while((review_buffer = inFile.readLine()) != null ) {
            Review r = Review.parse_review(review_buffer);
            if(r != null && r.validate_review()) {
                ReviewInterface review = new Review(r);
                String bid = review.getBusiness_id();
                String uid = review.getUser_id();
                if (this.businesses.containsKey(bid) && this.users_ids.contains(uid))
                    this.reviews_table.put(r.getReview_id(), review);
                else invalid_reviws++;
            }
            else invalid_reviws++;
        }
    }

    /**
     * Collects businesses not reviewed in a list of businesses-ids
     * @return List of businesses-ids
     */
    public List<String> collectsBusinessesNotReviewed() {

        Set<String> businessesIds = new HashSet<>();

        for(Map.Entry<String, ReviewInterface> e : this.reviews_table.entrySet()) {
            ReviewInterface review = e.getValue();
            String businessId = review.getBusiness_id();
            businessesIds.add(businessId);

        }

        List<String> busNotReviewed = new ArrayList<>(this.businesses.keySet());

        return busNotReviewed.stream().filter(b -> !(businessesIds.contains(b))).sorted(Comparator.naturalOrder()).collect(Collectors.toList());
    }

    /**
     * Determines the total number of reviews and the total number of different users who did it
     * @param month Month
     * @param year Year
     * @return Query2Pair (total number of reviews and number of users)
     */
    public Query2Pair reviewsUsersByDate(int month, int year) {
        List<String> userIds = new ArrayList<>();
        int nReviews = 0;

        for(Map.Entry<String, ReviewInterface> r : this.reviews_table.entrySet()) {
            ReviewInterface review = r.getValue();
            if(review.getMonth() == month && review.getYear() == year) {
                nReviews++;
                String user_id = review.getUser_id();
                if(!userIds.contains(user_id)) {
                    userIds.add(user_id);
                }
            }
        }

        return new Query2Pair(nReviews, userIds.size());
    }

    /**
     * Determines, by month, the number of reviews, number of businesses and average stars given by an user
     * @param user_id User-id
     * @return Map with the information, with month as key
     */
    public Map<Integer, Query3Triple> userReviewsByMonth(String user_id) {
        List<ReviewInterface> reviewsByUser = new ArrayList<>();
        for(Map.Entry<String, ReviewInterface> r : this.reviews_table.entrySet()) {
            ReviewInterface review = r.getValue();
            String userId = review.getUser_id();
            if(userId.equals(user_id)) {
                reviewsByUser.add(review);
            }
        }

        Map<Integer, List<ReviewInterface>> mapRevUsers = reviewsByUser.stream().collect(groupingBy(ReviewInterface::getMonth));

        Map<Integer, Query3Triple> userByMonth = new Hashtable<>();

        for(Map.Entry<Integer, List<ReviewInterface>> e : mapRevUsers.entrySet()) {
            int month = e.getKey();
            List<ReviewInterface> reviews = e.getValue();
            int numReviews = reviews.size();
            int numDistinctBus = (int)reviews.stream().map(ReviewInterface::getBusiness_id).distinct().count();
            float avStars = reviews.stream().map(ReviewInterface::getStars).reduce((float)0, Float::sum);
            Query3Triple q = new Query3Triple(numReviews, numDistinctBus, (double) avStars/numReviews);
            userByMonth.put(month, q);
        }

        return userByMonth;
    }

    /**
     * Determines, by month, the number of reviews, number different users and stars average of a business
     * @param business_id Busienss-id
     * @return Map with the information, with month as key
     */
    public Map<Integer, Query4Triple> businessReviewedByMonth(String business_id) {
        List<ReviewInterface> reviewsOfBusiness = new ArrayList<>();
        for(Map.Entry<String, ReviewInterface> r : this.reviews_table.entrySet()) {
            ReviewInterface review = r.getValue();
            String businessId = review.getBusiness_id();
            if(businessId.equals(business_id)) {
                reviewsOfBusiness.add(review);
            }
        }

        Map<Integer, List<ReviewInterface>> mapRevBus = reviewsOfBusiness.stream().collect(groupingBy(ReviewInterface::getMonth));

        Map<Integer, Query4Triple> busByMonth = new Hashtable<>();

        for(Map.Entry<Integer, List<ReviewInterface>> e : mapRevBus.entrySet()) {
            int month = e.getKey();
            List<ReviewInterface> reviews = e.getValue();
            int numReviews = reviews.size();
            int numDistinctUsers = (int)reviews.stream().map(ReviewInterface::getUser_id).distinct().count();
            float avStars = reviews.stream().map(ReviewInterface::getStars).reduce((float)0, Float::sum);
            Query4Triple q = new Query4Triple(numReviews, numReviews, (double) avStars/numReviews);
            busByMonth.put(month, q);
        }

        return busByMonth;
    }

    /**
     * Determines the list of businesses' names reviewed by a certain user and how many
     * @param user_id User-id
     * @return List of Map.Entry with the number of times reviewed as key
     */
    public List<Map.Entry<String,Integer>> reviewedBusinessesByUser (String user_id) {
        Map<String,Integer> map = new Hashtable<>();

        for (Map.Entry<String,ReviewInterface> r : this.reviews_table.entrySet()) {
            ReviewInterface review = r.getValue();
            String userId = review.getUser_id();

            if (userId.equals(user_id)) {
                String busId = review.getBusiness_id();
                BusinessInterface b = this.businesses.get(busId);
                String busName = b.getName();
                if (map.containsKey(busName))
                    map.put(busName, map.get(busName) + 1);
                else
                    map.put(busName, 1);
            }
        }

        List<Map.Entry<String, Integer>> list = new ArrayList<>(map.entrySet());

        return list.stream().sorted((a,b) -> b.getValue() - a.getValue()).collect(Collectors.toList());

    }

    /**
     * Determines the 'number' most reviewed businesses, by year, and the number of different users who did it
     * @param number Number of the most reviewed businesses
     * @return Map with results
     */
    public Map<Integer, Map<String, Integer>> mostReviewedBusinessesByYear(int number) {
        Map<Integer, Map<String, Integer>> numReviewsBus = new Hashtable<>();
        Map<Integer, Map<String, Set<String>>> usersBy = new Hashtable<>();

        for (Map.Entry<String, ReviewInterface> e : this.reviews_table.entrySet()) {
            ReviewInterface r = e.getValue();
            String bid = r.getBusiness_id();
            String uid = r.getUser_id();

            int year = r.getYear();
            if (numReviewsBus.containsKey(year)) {
                if (numReviewsBus.get(year).containsKey(bid)) {
                    Map<String, Integer> business = numReviewsBus.get(year);
                    business.put(bid, business.get(bid) + 1);
                    numReviewsBus.put(year, business);
                } else {
                    Map<String, Integer> business = numReviewsBus.get(year);
                    business.put(bid, 1);
                    numReviewsBus.put(year, business);
                }
            } else {
                Map<String, Integer> business = new Hashtable<>();
                business.put(bid, 1);
                numReviewsBus.put(year, business);
            }


            if (usersBy.containsKey(year)) {
                if (usersBy.get(year).containsKey(bid)) {
                    Set<String> uids = usersBy.get(year).get(bid);
                    uids.add(uid);
                    Map<String, Set<String>> uidsBus = usersBy.get(year);
                    uidsBus.put(bid, uids);
                    usersBy.put(year, uidsBus);
                } else {
                    Map<String, Set<String>> uidsBus = usersBy.get(year);
                    Set<String> uids = new HashSet<>();
                    uids.add(uid);
                    uidsBus.put(bid, uids);
                    usersBy.put(year, uidsBus);
                }

            } else {
                Map<String, Set<String>> uidsBus = new Hashtable<>();
                Set<String> uids = new HashSet<>();
                uids.add(uid);
                uidsBus.put(bid, uids);
                usersBy.put(year, uidsBus);
            }


        }

        for (Map.Entry<Integer, Map<String, Integer>> entry : numReviewsBus.entrySet()) {
            Map<String, Integer> sorted = entry.getValue().entrySet().stream().sorted(Map.Entry.<String, Integer>comparingByValue().reversed()).limit(number)
                    .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
            numReviewsBus.put(entry.getKey(), sorted);
        }

        for (Map.Entry<Integer, Map<String, Set<String>>> e : usersBy.entrySet()) {
            int year = e.getKey();
            for (Map.Entry<String, Set<String>> e2 : usersBy.get(year).entrySet()) {
                String bid = e2.getKey();
                int num = e2.getValue().size();
                if (numReviewsBus.get(year).containsKey(bid)) numReviewsBus.get(year).put(bid, num);
            }
        }

        return numReviewsBus;
    }

    /**
     * Determines, by city, the list of the three most famous businesses, through its number of reviews
     * @return Map with the lists by city
     */
    public Map<String, List<String>> mostFamousByCity() {
        Map<String, List<String>> most_famous = new Hashtable<>();

        Map<String, Map<String, Integer>> number_reviews = new Hashtable<>();
        for (Map.Entry<String, ReviewInterface> r : this.reviews_table.entrySet()) {
            ReviewInterface review = r.getValue();
            String bus_id = review.getBusiness_id();
            BusinessInterface business = this.businesses.get(bus_id);
            String city = business.getCity();
            if (number_reviews.containsKey(city)) {
                Map<String, Integer> business_info = number_reviews.get(city);
                if (business_info.containsKey(bus_id))
                    business_info.put(bus_id, business_info.get(bus_id) + 1);
                else
                    business_info.put(bus_id, 1);
            }
            else {
                Map<String, Integer> business_info = new Hashtable<>();
                business_info.put(bus_id, 1);
                number_reviews.put(city, business_info);
            }

        }

        for (Map.Entry<String, Map<String,Integer>> entry : number_reviews.entrySet()) {
            List<Map<String,Integer>> list = new ArrayList<>();
            Map<String,Integer> order = entry.getValue();
            Map<String,Integer> ordered = order.entrySet().stream().sorted(Map.Entry.<String,Integer>comparingByValue().reversed()).limit(3)
                    .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
            List<String > keys = new ArrayList<>(ordered.keySet());
            most_famous.put(entry.getKey(), keys);
        }

        return most_famous;
    }

    /**
     * Determines the ids of the 'number' users who reviewed more different businesses, and how many
     * @param number Number of users
     * @return List of Map.Entry with the ids and number of businesses reviewed required
     */
    public List<Map.Entry<String, Integer>> usersReviewedMostBusinesses(int number) {

        Map<String, Set<String>> users_reviews = new Hashtable<>();

        for (Map.Entry<String, ReviewInterface> r : this.reviews_table.entrySet()) {

            ReviewInterface review = r.getValue();
            String user_id = review.getUser_id();
            String business_id = review.getBusiness_id();

            if (users_reviews.containsKey(user_id))
                users_reviews.get(user_id).add(business_id);
            else {
                Set<String> new_list = new HashSet<>();
                new_list.add(business_id);
                users_reviews.put(user_id, new_list);
            }

        }

        List<Map.Entry<String, Integer>> final_list = new ArrayList<>();
        for (Map.Entry<String, Set<String>> users : users_reviews.entrySet())
            final_list.add(new AbstractMap.SimpleEntry<>(users.getKey(), users.getValue().size()));

        return final_list.stream().sorted((a,b) -> b.getValue() - a.getValue()).limit(number).collect(Collectors.toList());
    }

    /**
     * Determines the 'number' users that more reviewed a certain business and, for each one, the average classification
     * @param business_id Business-id
     * @param number Number of users
     * @return List of users and its average classification
     */
    public List<Map.Entry<String, Double>> mostReviewsMadeByUserToBusiness(String business_id, int number) {

        Map<String, Set<String>> rev_by_user = new Hashtable<>();

        for (Map.Entry<String, ReviewInterface> r : this.reviews_table.entrySet()) {
            ReviewInterface review = r.getValue();
            String review_id = review.getReview_id();
            String user_id = review.getUser_id();
            String bus_id = review.getBusiness_id();
            if (bus_id.equals(business_id)) {

                if (rev_by_user.containsKey(user_id))
                    rev_by_user.get(user_id).add(review_id);
                else {
                    Set<String> new_list = new HashSet<>();
                    new_list.add(review_id);
                    rev_by_user.put(user_id, new_list);
                }

            }
        }

        double n_reviews = 0;
        double average = 0;

        List<Map.Entry<String, Double>> final_list = new ArrayList<>();
        for (Map.Entry<String, Set<String>> reviews : rev_by_user.entrySet()) {
            for (String s : reviews.getValue()) {
                n_reviews++;
                ReviewInterface ri = lookup_review(s);
                average += ri.getStars();
            }
            final_list.add(new AbstractMap.SimpleEntry<>(reviews.getKey(), (double) average/n_reviews));
            n_reviews = 0;
            average = 0;
        }

        return final_list.stream().sorted((a,b) -> (int) (b.getValue() - a.getValue())).limit(number).collect(Collectors.toList());
    }

    /**
     * Determines for each state, and by city, the average classification of each business
     * @return Map that connects the state, city and average classification for each business
     */
    public Map<String, Map<String, Map<String, Double>>> averageScoreByCityAndState() {

        Map<String, Integer> number_reviews_per_bus = new Hashtable<>();

        Map<String, Map<String, Map<String, Double>>> results = new Hashtable<>();

        for (Map.Entry<String, ReviewInterface> review : this.reviews_table.entrySet()) {

            ReviewInterface r = review.getValue();
            double stars = r.getStars();
            String bus_id = r.getBusiness_id();
            BusinessInterface b = this.businesses.get(bus_id);
            String state = b.getState();
            String city = b.getCity();

            // Updates number of reviews by business
            if (number_reviews_per_bus.containsKey(bus_id))
                number_reviews_per_bus.put(bus_id, number_reviews_per_bus.get(bus_id) + 1);
            else
                number_reviews_per_bus.put(bus_id, 1);

            if (results.containsKey(state)) {

                if (results.get(state).containsKey(city)) {
                    Map<String, Double> inside_city = results.get(state).get(city);

                    if (inside_city.containsKey(bus_id))
                        inside_city.put(bus_id, inside_city.get(bus_id) + stars);
                    else
                        results.get(state).get(city).put(bus_id, stars);
                }
                else {
                    Map<String, Map.Entry<String, Double>> new_city = new Hashtable<>();
                    Map<String,Double> new_business = new Hashtable<>();
                    new_business.put(bus_id, stars);
                    results.get(state).put(city, new_business);
                }

            }
            else {
                Map<String,Double> new_business = new Hashtable<>();
                new_business.put(bus_id, stars);
                Map<String, Map<String, Double>> new_city = new Hashtable<>();
                new_city.put(city, new_business);
                results.put(state, new_city);
            }

        }

        for (Map.Entry<String, Map<String, Map<String, Double>>> map : results.entrySet()) {
            for (Map.Entry<String, Map<String, Double>> new_map : map.getValue().entrySet()) {
                for (Map.Entry<String, Double> pair : new_map.getValue().entrySet()) {
                    Integer n_reviews = number_reviews_per_bus.get(pair.getKey());
                    pair.setValue(pair.getValue()/n_reviews);
                }

            }
        }

        return results;
    }

    /**
     * Collects reviews' interfaces in a map whose keys are review-id
     * @return Map with the reviews' interfaces
     */
    public Map<String, ReviewInterface> collectsReviewsInterfaces() {
        Map<String, ReviewInterface> reviewInterfaces = new Hashtable<>();
        for (Map.Entry<String, ReviewInterface> e : this.reviews_table.entrySet())
            reviewInterfaces.put(e.getKey(), e.getValue().clone());

        return reviewInterfaces;
    }
}
