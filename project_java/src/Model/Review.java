package Model;

import java.io.IOException;
import java.io.Serializable;

public class Review implements ReviewInterface, Serializable {
    /**
     * Fields
     */
    private String review_id;
    private String user_id;
    private String business_id;
    private float stars;
    private int useful;
    private int funny;
    private int cool;
    private String date;
    private String text;

    /**
     * Empty Constructor
     */
    public Review() {
        this.review_id = "";
        this.user_id = "";
        this.business_id = "";
        this.stars = 0;
        this.useful = 0;
        this.funny = 0;
        this.cool = 0;
        this.date = "";
        this.text = "";
    }

    /**
     * Parametrized Constructor
     * @param review_id Review-id
     * @param user_id User-id
     * @param business_id Busienss-id
     * @param stars Review stars
     * @param useful Review useful
     * @param funny Review funny
     * @param cool Review cool
     * @param date Review date
     * @param text Review text
     */
    public Review(String review_id, String user_id, String business_id, float stars, int useful, int funny, int cool, String date, String text) {
        this.review_id = review_id;
        this.user_id = user_id;
        this.business_id = business_id;
        this.stars = stars;
        this.useful = useful;
        this.funny = funny;
        this.cool = cool;
        this.date = date;
        this.text = text;
    }

    /**
     * Copy Constructor
     * @param r Review
     */
    public Review(Review r) {
        this.review_id = r.getReview_id();
        this.user_id = r.getUser_id();
        this.business_id = r.getBusiness_id();
        this.stars = r.getStars();
        this.useful = r.getUseful();
        this.funny = r.getFunny();
        this.cool = r.getCool();
        this.date = r.getDate();
        this.text = r.getText();
    }

    /**
     * Clones a Review
     * @return Cloned Review
     */
    public Review clone() {
        return new Review(this);
    }

    /**
     * Validates a review
     * @return 1 if it's valid, 0 if not
     */
    public boolean validate_review() {
        return (this.review_id.length() == 22 && this.business_id.length() == 22
                && this.user_id.length() == 22 && this.stars <= 5 && this.stars >= 0
                && this.useful >= 0 && this.funny >= 0 && this.cool >= 0 && this.date.length() == 19);
    }

    /**
     * Getter of a review-id
     * @return  Review-id
     */
    public String getReview_id() {
        return this.review_id;
    }

    /**
     * Setter of a review-id
     * @param review_id Review-id
     */
    public void setReview_id(String review_id) {
        this.review_id = review_id;
    }

    /**
     * Getter of a user-id
     * @return  User-id
     */
    public String getUser_id() {
        return this.user_id;
    }

    /**
     * Setter of a User-id
     * @param user_id User-id
     */
    public void setUser_id(String user_id) {
        this.user_id = user_id;
    }

    /**
     * Getter of a business-id
     * @return  Business-id
     */
    public String getBusiness_id() {
        return this.business_id;
    }

    /**
     * Setter of a busieness-id
     * @param business_id Business-id
     */
    public void setBusiness_id(String business_id) {
        this.business_id = business_id;
    }

    /**
     * Getter of stars
     * @return Stars
     */
    public Float getStars() {
        return this.stars;
    }

    /**
     * Setter of stars
     * @param stars Stars to be
     */
    public void setStars(Float stars) {
        this.stars = stars;
    }

    /**
     * Getter of useful
     * @return Useful
     */
    public int getUseful() {
        return this.useful;
    }

    /**
     * Setter of useful
     * @param useful Useful to be
     */
    public void setUseful(int useful) {
        this.useful = useful;
    }

    /**
     * Getter of funny
     * @return Funny
     */
    public int getFunny() {
        return this.funny;
    }

    /**
     * Setter of funny
     * @param funny Funny to be
     */
    public void setFunny(int funny) {
        this.funny = funny;
    }

    /**
     * Getter of cool
     * @return Cool
     */
    public int getCool() {
        return this.cool;
    }

    /**
     * Setter of cool
     * @param cool Cool to be
     */
    public void setCool(int cool) {
        this.cool = cool;
    }

    /**
     * Getter of date
     * @return Date
     */
    public String getDate() {
        return this.date;
    }

    /**
     * Setter of date
     * @param date Date to be
     */
    public void setDate(String date) {
        this.date = date;
    }

    /**
     * Getter of text
     * @return Text
     */
    public String getText() {
        return this.text;
    }

    /**
     * Setter of text
     * @param text Text to be
     */
    public void setText(String text) {
        this.text = text;
    }

    /**
     * Getter of month
     * @return Month
     */
    public int getMonth() {
        String[] split_date = this.date.split("-");
        return Integer.parseInt(split_date[1]);
    }

    /**
     * Getter of year
     * @return Year
     */
    public int getYear() {
        String[] split_date = this.date.split("-");
        return Integer.parseInt(split_date[0]);
    }

    /**
     * Parses a Review
     * @param buffer Review read
     * @return Review
     */
    public static Review parse_review(String buffer) throws IOException {

        Review r;
        String[] split_buffer = buffer.split(";");

        try {
            String review_id = split_buffer[0];
            String user_id = split_buffer[1];
            String business_id = split_buffer[2];
            float stars = Float.parseFloat(split_buffer[3]);
            int useful = Integer.parseInt(split_buffer[4]);
            int funny = Integer.parseInt(split_buffer[5]);
            int cool = Integer.parseInt(split_buffer[6]);
            String date = split_buffer[7];
            String text = split_buffer[8];

            r = new Review(review_id,user_id, business_id, stars, useful, funny, cool, date, text);
        }
        catch (NumberFormatException | ArrayIndexOutOfBoundsException e){
            r = null;
        }

        return r;
    }
}
