package Model;

import java.io.*;
import java.util.*;

import static java.util.stream.Collectors.groupingBy;

public class GestReviews implements GestReviewsInterface, Serializable {

    /**
     * Fields
     */
    private UsersInterface users;
    private BusinessesInterface businesses;
    private ReviewsInterface reviews;
    private String filePathUsers;
    private String filePathBusinesses;
    private String filePathReviews;

    /**
     * Empty Constructor
     */
    public GestReviews() {
        this.users = new Users();
        this.businesses = new Businesses();
        this.reviews = new Reviews();
        this.filePathUsers = "";
        this.filePathBusinesses = "";
        this.filePathReviews = "";
    }

    /**
     * Reads the Users' file
     * @param filepath Filepath to the Users' file
     * @throws IOException in case I/O failed
     */
    public void readUsersFile(String filepath) throws IOException {
        this.filePathUsers = filepath;
        this.users.read_users_file(filepath);
    }

    /**
     * Reads the Businesses' file
     * @param filepath Filepath to the Businesses' file
     * @throws IOException in case I/O failed
     */
    public void readBusinessesFile(String filepath) throws IOException {
        this.filePathBusinesses = filepath;
        this.businesses.read_businesses_file(filepath);
    }

    /**
     * Reads the Reviews' file
     * @param filepath Filepath to the Reviews' file
     * @throws IOException in case I/O failed
     */
    public void readReviewsFile(String filepath) throws IOException {
        this.filePathReviews = filepath;
        this.reviews.set_users_ids(this.users.collectUserIds());
        this.reviews.set_businesses_interface(this.businesses.collectsBusinessesInterfaces());
        this.reviews.read_reviews_file(filepath);
    }

    /**
     * Verifies if a certain user exists through its id
     * @param user_id User-id
     * @return 1 if it exists, 0 if not
     */
    public boolean containsUser(String user_id) {
        return this.users.exists_user(user_id);
    }

    /**
     * getter of the users file path
     * @return users file path
     */
    public String getFilePathUsers() {
        return this.filePathUsers;
    }

    /**
     * getter of the businesses file path
     * @return businesses file path
     */
    public String getFilePathBusinesses() {
        return this.filePathBusinesses;
    }

    /**
     * getter of the reviews file path
     * @return reviews file path
     */
    public String getFilePathReviews() {
        return this.filePathReviews;
    }

    /**
     * Saves in object format
     * @param object_path Object's path
     * @throws IOException in case I/O failed
     */
    public void saveSGRObject(String object_path) throws IOException {
        FileOutputStream fos = new FileOutputStream(object_path);
        BufferedOutputStream bos = new BufferedOutputStream(fos);
        ObjectOutputStream oos = new ObjectOutputStream(bos);
        oos.writeObject(this);
        oos.flush();
        oos.close();
    }

    /**
     * Query 1
     * @return List of businesses-ids
     */
    public List<String> collectsBusinessesNeverEval() {
        return this.reviews.collectsBusinessesNotReviewed();
    }

    /**
     * Query 2
     * @param month Month
     * @param year Year
     * @return Query2Pair (total number of reviews and number of users)
     */
    public Query2Pair reviewsUsersByDate(int month, int year) throws EmptyQueryException{
        if (month < 1 || month > 12) {
            throw new EmptyQueryException();
        }
        return this.reviews.reviewsUsersByDate(month, year);
    }

    /**
     * Query 3
     * @param user_id User-id
     * @return Map with the information, with month as key
     */
    public Map<Integer, Query3Triple> userReviewsByMonth(String user_id) throws UserDoesntExistException {
        if (this.users.exists_user(user_id))
            return this.reviews.userReviewsByMonth(user_id);
        else
            throw new UserDoesntExistException();
    }

    /**
     * Query 4
     * @param business_id Business-id
     * @return Map with the information, with month as key
     */
    public Map<Integer, Query4Triple> businessReviewedByMonth(String business_id) throws BusinessDoesntExistException{
        if (this.businesses.exists_business(business_id))
            return this.reviews.businessReviewedByMonth(business_id);
        else
            throw new BusinessDoesntExistException();
    }

    /**
     * Query 5
     * @param user_id User-id
     * @return List of Map.Entry with the number of times reviewed as key
     */
    public List<Map.Entry<String,Integer>> reviewedBusinessesByUser(String user_id) throws UserDoesntExistException {
        return this.reviews.reviewedBusinessesByUser(user_id);
    }

    /**
     * Query 6
     * @param number Number of the most reviewed businesses
     * @return Map with results
     */
    public Map<Integer, Map<String, Integer>> mostReviewedBusinessesByYear(int number) {
        return this.reviews.mostReviewedBusinessesByYear(number);
    }

    /**
     * Query 7
     * @return Map with the lists by city
     */
    public Map<String, List<String>> mostFamousByCity() {
        return this.reviews.mostFamousByCity();
    }

    /**
     * Query 8
     * @param number Number of users
     * @return List of Map.Entry with the ids and number of businesses reviewed required
     */
    public List<Map.Entry<String, Integer>> usersReviewedMostBusinesses(int number) {
        return this.reviews.usersReviewedMostBusinesses(number);
    }

    /**
     * Query 9
     * @param business_id Business-id
     * @param number Number of users
     * @return List of users and its average classification
     */
    public List<Map.Entry<String, Double>> mostReviewsMadeByUserToBusiness(String business_id, int number) throws BusinessDoesntExistException {
        if (this.businesses.exists_business(business_id))
            return this.reviews.mostReviewsMadeByUserToBusiness(business_id, number);
        else
            throw new BusinessDoesntExistException();
    }

    /**
     * Query 10
     * @return Map that connects the state, city and average classification for each business
     */
    public Map<String, Map<String, Map<String, Double>>> averageScoreByCityAndState() {
        return this.reviews.averageScoreByCityAndState();
    }

    /**
     * Statistics1
     * @return Map that connects the statistics with a number(key)
     */
    public Map<Integer, Integer> statistics1(){
        Map<Integer, Integer> stats1 = new Hashtable<>();
        int totalBusinesses = this.businesses.get_n_businesses();
        int totalBusNotRev = this.reviews.collectsBusinessesNotReviewed().size();
        int totalBusReviewed = totalBusinesses - totalBusNotRev;

        int totalUsers = this.users.get_n_users();
        Map<String, ReviewInterface> reviews_table = this.reviews.collectsReviewsInterfaces();
        Set<String> userIds = new HashSet<>();
        int totalUsersRev = 0;
        int totalRevNoImpact = 0;

        for(Map.Entry<String, ReviewInterface> r : reviews_table.entrySet()) {
            ReviewInterface review = r.getValue();
            String user_id = review.getUser_id();
            int useful = review.getUseful();
            int funny = review.getFunny();
            int cool = review.getCool();

            if(!userIds.contains(user_id)) {
                userIds.add(user_id);
                totalUsersRev++;
            }

            if(useful == 0 || funny == 0 || cool == 0)
                totalRevNoImpact++;
        }

        int totalUsersNotRev = totalUsers - totalUsersRev;
        int invalidReviews = reviews.getInvalid_reviws();

        stats1.put(1, totalBusinesses);
        stats1.put(2, totalBusReviewed);
        stats1.put(3, totalBusNotRev);
        stats1.put(4, totalUsers);
        stats1.put(5, totalUsersRev);
        stats1.put(6, totalUsersNotRev);
        stats1.put(7, totalRevNoImpact);
        stats1.put(8, invalidReviews);

        return stats1;
    }

    /**
     * Determines the total number of reviews by month
     * @return Map that associates a month with a number of reviews
     */
    public Map<Integer,Integer> statsTotalRevByMonth(){
        List<ReviewInterface> revByMonth = new ArrayList<>();
        Map<String, ReviewInterface> reviews_table = reviews.collectsReviewsInterfaces();

        for(Map.Entry<String, ReviewInterface> r : reviews_table.entrySet()) {
            ReviewInterface review = r.getValue();
            revByMonth.add(review);
        }

        Map<Integer, List<ReviewInterface>> mapRevByMonth = revByMonth.stream().collect(groupingBy(ReviewInterface::getMonth));
        Map<Integer,Integer> totalRevByMonth = new Hashtable<>();

        for(Map.Entry<Integer, List<ReviewInterface>> rev : mapRevByMonth.entrySet()) {
            int month = rev.getKey();
            List<ReviewInterface> reviews = rev.getValue();
            int totalRev = reviews.size();
            totalRevByMonth.put(month, totalRev);
        }

        return totalRevByMonth;
    }

    /**
     * Determines the total number of users that reviewed, by month
     * @return Map that associates a month with a number of users
     */
    public Map<Integer, Integer> statsUsersRevByMonth() {
        List<ReviewInterface> revMonth = new ArrayList<>();
        Map<String, ReviewInterface> reviews_table = reviews.collectsReviewsInterfaces();

        for (Map.Entry<String, ReviewInterface> r : reviews_table.entrySet()) {
            ReviewInterface review = r.getValue();
            revMonth.add(review);
        }

        Map<Integer, List<ReviewInterface>> mapUsersRev = revMonth.stream().collect(groupingBy(ReviewInterface::getMonth));
        Map<Integer, Integer> totalUsersRevMonth = new Hashtable<>();

        for (Map.Entry<Integer, List<ReviewInterface>> rev : mapUsersRev.entrySet()) {
            int month = rev.getKey();
            List<ReviewInterface> reviews = rev.getValue();
            int totalUsers = (int) reviews.stream().map(ReviewInterface::getUser_id).distinct().count();
            totalUsersRevMonth.put(month, totalUsers);
        }

        return totalUsersRevMonth;
    }

    /**
     * Determines the average classification of reviews, by month
     * @return Map that associates a month with the average classification of reviews
     */
    public Map<Integer, Float> statsAverageStars() {
        List<ReviewInterface> revByMonth = new ArrayList<>();
        Map<String, ReviewInterface> reviews_table = reviews.collectsReviewsInterfaces();

        for (Map.Entry<String, ReviewInterface> r : reviews_table.entrySet()) {
            ReviewInterface review = r.getValue();
            revByMonth.add(review);
        }

        Map<Integer, List<ReviewInterface>> mapStarsRev = revByMonth.stream().collect(groupingBy(ReviewInterface::getMonth));
        Map<Integer, Float> averageStarsRevMonth = new Hashtable<>();

        float totalStars = 0;
        int totalRevs = 0;

        for (Map.Entry<Integer, List<ReviewInterface>> rev : mapStarsRev.entrySet()) {
            int month = rev.getKey();
            for(ReviewInterface r : rev.getValue()){
                totalRevs++;
                totalStars += r.getStars();
            }
            averageStarsRevMonth.put(month, totalStars/totalRevs);
            totalRevs = 0;
            totalStars = 0;
        }

        return averageStarsRevMonth;
    }

    /**
     * Determines the average classification of reviews
     * @return Average classification of reviews
     */
    public Float statsAverageStarsGlobal() {
        Map<String, ReviewInterface> reviews_table = reviews.collectsReviewsInterfaces();
        float totalStars = 0;
        int totalRevs = 0;
        float averageStars = 0;

        for (Map.Entry<String, ReviewInterface> r : reviews_table.entrySet()) {
            ReviewInterface review = r.getValue();
            totalRevs++;
            totalStars += review.getStars();
        }
        totalStars = totalStars/totalRevs;

        return totalStars;
    }
}
