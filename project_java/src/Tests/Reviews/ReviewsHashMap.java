package Tests.Reviews;

import Model.*;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;
import java.util.stream.Collectors;

import static java.util.stream.Collectors.groupingBy;

public class ReviewsHashMap {
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
    public ReviewsHashMap() {
        this.reviews_table = new HashMap<>();
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
     * Collects reviews' interfaces in a map whose keys are review-id
     * @return Map with the reviews' interfaces
     */
    public Map<String, ReviewInterface> collectsReviewsInterfaces() {
        Map<String, ReviewInterface> reviewInterfaces = new HashMap<>();
        for (Map.Entry<String, ReviewInterface> e : this.reviews_table.entrySet())
            reviewInterfaces.put(e.getKey(), e.getValue().clone());

        return reviewInterfaces;
    }

}
