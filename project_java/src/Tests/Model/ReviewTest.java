package Tests.Model;

import Model.Review;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class ReviewTest {

    @Test
    void getReview() {

        String expec_id = "R1234";
        String expec_user_id = "U1234";
        String expec_business_id = "B1234";
        float expec_stars = 4;
        int expec_useful = 3;
        int expec_funny = 5;
        int expec_cool = 2;
        String expec_date = "19-06-2021";
        String expec_text = "Review";

        Review r = new Review(expec_id, expec_user_id, expec_business_id, expec_stars, expec_useful, expec_funny, expec_cool, expec_date, expec_text);
        assertEquals(expec_id, r.getReview_id());
        assertEquals(expec_user_id, r.getUser_id());
        assertEquals(expec_business_id, r.getBusiness_id());
        assertEquals(expec_stars, r.getStars());
        assertEquals(expec_useful, r.getUseful());
        assertEquals(expec_funny, r.getFunny());
        assertEquals(expec_cool, r.getCool());
        assertEquals(expec_date, r.getDate());
        assertEquals(expec_text, r.getText());

    }

}
