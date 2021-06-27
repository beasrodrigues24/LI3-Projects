package Tests.Users;

import Model.User;
import Model.UserInterface;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

public class UsersTreeMap {
    /**
     * Fields
     */
    private Map<String, UserInterface> users_table;

    /**
     * Empty Constructor
     */
    public UsersTreeMap() {
        this.users_table = new TreeMap<>();
    }

    /**
     * Verifies if a certain user exists through its id
     * @param user_id User-id
     * @return 1 if it exists, 0 if not
     */
    public boolean exists_user(String user_id) {
        return this.users_table.containsKey(user_id);
    }

    /**
     * Searches for certain user through its id
     * @param user_id User-id
     * @return UserInterface
     */
    public UserInterface lookup_user(String user_id) {
        return this.users_table.get(user_id);
    }

    /**
     * Getter of the number of users
     * @return Number of users
     */
    public int get_n_users() {
        return this.users_table.size();
    }

    /**
     * Reads the Users' file
     * @param filepath Filepath to the Users' file
     * @throws IOException in case I/O failed
     */
    public void read_users_file(String filepath) throws IOException {
        BufferedReader inFile = new BufferedReader(new FileReader(filepath));
        String user_buffer;
        while ((user_buffer = inFile.readLine()) != null) {
            User u = User.parse_user(user_buffer);
            if (u != null && u.validate_user()) {
                UserInterface user = new User(u);
                this.users_table.put(user.getUser_id(), user);
            }
        }

    }

    /**
     * Collects users' ids in a set
     * @return Set with the users' ids
     */
    public Set<String> collectUserIds() {
        Set<String> ids = new HashSet<>();
        for (Map.Entry<String, UserInterface> e : this.users_table.entrySet())
            ids.add(e.getKey());
        return ids;
    }
}
