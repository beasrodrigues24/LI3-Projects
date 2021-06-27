package Model;

import java.io.IOException;
import java.util.List;
import java.util.Map;
import java.util.Set;

public interface ReviewsInterface {

    void read_reviews_file(String filepath) throws IOException;
    boolean exists_review(String review_id);

    int getInvalid_reviws();
    void set_users_ids(Set<String> users_ids);
    void set_businesses_interface(Map<String, BusinessInterface> businesses);

    List<String> collectsBusinessesNotReviewed();
    Query2Pair reviewsUsersByDate(int month, int year);
    Map<Integer, Query3Triple> userReviewsByMonth(String user_id);
    Map<Integer, Query4Triple> businessReviewedByMonth(String business_id);
    List<Map.Entry<String,Integer>> reviewedBusinessesByUser(String user_id);
    Map<Integer, Map<String, Integer>> mostReviewedBusinessesByYear(int number);
    Map<String, List<String>> mostFamousByCity();
    List<Map.Entry<String, Integer>> usersReviewedMostBusinesses(int number);
    List<Map.Entry<String, Double>> mostReviewsMadeByUserToBusiness(String business_id, int number);
    Map<String, Map<String, Map<String, Double>>> averageScoreByCityAndState();

    public Map<String, ReviewInterface> collectsReviewsInterfaces();
}
