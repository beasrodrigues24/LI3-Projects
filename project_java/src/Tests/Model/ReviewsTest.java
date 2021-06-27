package Tests.Model;

import Model.Businesses;
import Model.Reviews;
import java.io.IOException;

import Model.Users;
import org.junit.jupiter.api.Test;


class ReviewsTest {

    @Test
    void containsReview() {
        Reviews reviews = new Reviews();
        Businesses businesses = new Businesses();
        Users users = new Users();
        try {
            users.read_users_file("src/files/users_full.csv");
            businesses.read_businesses_file("src/files/business_full.csv");
            reviews.set_users_ids(users.collectUserIds());
            reviews.set_businesses_interface(businesses.collectsBusinessesInterfaces());
            reviews.read_reviews_file("src/files/reviews_1M.csv");
            assert reviews.exists_review("sjm_uUcQVxab_EeLCqsYLg");
            assert reviews.exists_review("lWC-xP3rd6obsecCYsGZRg");
        } catch (IOException ignored) {}

    }

}
