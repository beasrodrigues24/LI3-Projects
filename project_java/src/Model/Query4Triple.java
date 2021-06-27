package Model;

public class Query4Triple {

    /**
     * Fields
     */
    private int n_reviews;
    private int n_users;
    private double average_score;

    /**
     * Parametrized Constructor
     * @param nr Number of reviews
     * @param nu Number of users
     * @param as Average score
     */
    public Query4Triple(int nr, int nu, double as) {
        this.n_reviews = nr;
        this.n_users = nu;
        this.average_score = as;
    }

    /**
     * Getter of the number of reviews
     * @return Number of reviews
     */
    public int getN_reviews() {
        return this.n_reviews;
    }

    /**
     * Getter of the number of users
     * @return Number of users
     */
    public int getN_users() {
        return this.n_users;
    }

    /**
     * Getter of the average score
     * @return Average score
     */
    public double getAverage_score() {
        return this.average_score;
    }
}
