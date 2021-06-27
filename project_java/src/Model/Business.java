package Model;

import java.io.Serializable;

public class Business implements BusinessInterface, Serializable {

    /**
     * Fields
     */
    private String business_id;
    private String name;
    private String city;
    private String state;
    private String categories;

    /**
     * Default Constructor
     */
    public Business() {
        this.business_id = "";
        this.name = "";
        this.city = "";
        this.state = "";
        this.categories = "";
    }

    /**
     * Parameterized Constructor
     * @param business_id Business-id
     * @param name Business name
     * @param city Business city
     * @param state Business state
     * @param categories Business categories
     */
    public Business(String business_id, String name, String city, String state, String categories){
        this.business_id = business_id;
        this.name = name;
        this.city = city;
        this.state = state;
        this.categories = categories;
    }

    /**
     * Copy Constructor
     * @param b Business
     */
    public Business(Business b){
        this.business_id = b.getBusiness_id();
        this.name = b.getName();
        this.city = b.getCity();
        this.state = b.getState();
        this.categories = b.getCategories();
    }

    /**
     * Clones a Business
     * @return Cloned Business
     */
    public Business clone(){
        return new Business(this);
    }

    /**
     * Validates a Business
     * @return 1 if it's a valid business, 0 if not
     */
    public boolean validate_business(){
        return getBusiness_id().length() == 22 && !getName().equals("") && !getCity().equals("")
                && !getState().equals("") && !getCategories().equals("");
    }

    /**
     * Getter of business-id
     * @return Business-id
     */
    public String getBusiness_id() {
        return this.business_id;
    }

    /**
     * Setter of business-id
     * @param business_id Business-id to be
     */
    public void setBusiness_id(String business_id) {
        this.business_id = business_id;
    }

    /**
     * Getter of a business name
     * @return Name of a business
     */
    public String getName() {
        return this.name;
    }

    /**
     * Setter of a business name
     * @param name Name to be
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * Getter of a business city
     * @return City of a business
     */
    public String getCity() {
        return this.city;
    }

    /**
     * Setter of a business city
     * @param city City to be
     */
    public void setCity(String city) {
        this.city = city;
    }

    /**
     * Getter of a business state
     * @return State of a business
     */
    public String getState() {
        return this.state;
    }

    /**
     * Setter of a business state
     * @param state State to be
     */
    public void setState(String state) {
        this.state = state;
    }

    /**
     * Getter of a business categories
     * @return Categories of a business
     */
    public String getCategories() {
        return this.categories;
    }

    /**
     * Setter of a business categories
     * @param categories Categories to be
     */
    public void setCategories(String categories) {
        this.categories = categories;
    }

    /**
     * Parses a Business
     * @param buffer Business read
     * @return Business
     */
    public static Business parse_business(String buffer){

        Business b;
        String[] split_buffer = buffer.split(";");

        try{
            String business_id = split_buffer[0];
            String name = split_buffer[1];
            String city = split_buffer[2];
            String state = split_buffer[3];
            String categories = split_buffer[4];

            b = new Business(business_id, name, city, state, categories);
        }
        catch (NumberFormatException | ArrayIndexOutOfBoundsException e){
            b = null;
        }

        return b;
    }
}
