package Model;

import java.io.IOException;
import java.io.Serializable;

public class User implements UserInterface, Serializable {

    /**
     * Fields
     */
    private String user_id;
    private String name;
    private String friends;

    /**
     * Empty Constructor
     */
    public User() {
        this.user_id = "";
        this.name = "";
        this.friends = "";
    }

    /**
     * Parametrized Constructor without friends
     * @param user_id User-id
     * @param name Name
     */
    public User(String user_id, String name) {
        this.user_id = user_id;
        this.name = name;
    }

    /**
     * Parametrized Constructor
     * @param user_id User-id
     * @param name Name
     * @param friends Friends
     */
    public User(String user_id, String name, String friends) {
        this.user_id = user_id;
        this.name = name;
        this.friends = friends;
    }

    /**
     * Copy Constructor
     * @param u User
     */
    public User(User u) {
        this.user_id = u.getUser_id();
        this.name = u.getName();
        this.friends = u.getFriends();
    }

    /**
     * Clones a User
     * @return Cloned User
     */
    public User clone() {
        return new User(this);
    }

    /**
     * Validates a user
     * @return 1 if it's valid, 0 if not
     */
    public boolean validate_user()  {
        return this.getUser_id().length() == 22 && !this.name.equals("");
    }

    /**
     * Getter of a user-id
     * @return  user-id
     */
    public String getUser_id() {
        return this.user_id;
    }

    /**
     * Setter of a user-id
     * @param user_id User-id
     */
    public void setUser_id(String user_id) {
        this.user_id = user_id;
    }

    /**
     * Getter of a user name
     * @return Name of a user
     */
    public String getName() {
        return this.name;
    }

    /**
     * Setter of a user name
     * @param name Name to be
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * Getter of friends
     * @return Friends
     */
    public String getFriends() {
        return this.friends;
    }

    /**
     * Setter of friends
     * @param friends Friends to be
     */
    public void setFriends(String friends) {
        this.friends = friends;
    }

    /**
     * Parses a User
     * @param buffer User read
     * @return User
     */
    public static User parse_user(String buffer) throws IOException {
        User u;
        String[] split_buffer = buffer.split(";");
        try {
            String user_id = split_buffer[0];
            String user_name = split_buffer[1];
            String friends = split_buffer[2];

            u = new User(user_id, user_name);
        }
        catch (NumberFormatException | ArrayIndexOutOfBoundsException e){
            u = null;
        }

        return u;
    }
}