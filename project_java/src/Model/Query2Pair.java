package Model;

public class Query2Pair {

    /**
     * Fields
     */
    private int total_reviews;
    private int number_users;

    /**
     * Parametrized Constructor
     * @param total_reviews Total number of reviews
     * @param number_users Total number of users that reviewed
     */
    public Query2Pair(int total_reviews, int number_users) {
        this.total_reviews = total_reviews;
        this.number_users = number_users;
    }

    /**
     * Getter of the total number of reviews
     * @return Total number of reviews
     */
    public int getTotal_reviews() {
        return this.total_reviews;
    }

    /**
     * Getter of the total number of users that reviewed
     * @return Total number of users that reviewed
     */
    public int getNumber_users() {
        return this.number_users;
    }
}
