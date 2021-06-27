package Model;

public class Query3Triple {

    /**
     * Fields
     */
    private int number_reviews;
    private int number_businesses;
    private double average_score;

    /**
     * Parametrized Constructor
     * @param nr Number of reviews
     * @param nb Number of businesses
     * @param as Average score
     */
    public Query3Triple(int nr, int nb, double as) {
        this.number_reviews = nr;
        this.number_businesses = nb;
        this.average_score = as;
    }

    /**
     * Getter of the number of reviews
     * @return Number of reviews
     */
    public int getNumber_reviews() {
        return this.number_reviews;
    }

    /**
     * Getter of the number of businesses
     * @return Number of businesses
     */
    public int getNumber_businesses() {
        return this.number_businesses;
    }

    /**
     * Getter of the average score
     * @return Average score
     */
    public double getAverage_score() {
        return this.average_score;
    }
}
