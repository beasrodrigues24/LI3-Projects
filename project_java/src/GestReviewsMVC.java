import Model.*;
import View.*;
import Controller.*;

public class GestReviewsMVC {

    /**
     * Main
     */
    public static void main(String[] args) {
        GestReviewsInterface gestReviews = new GestReviews();
        ViewInterface view = new View();
        ControllerInterface controller = new Controller(view, gestReviews);
        controller.run();
    }
}
