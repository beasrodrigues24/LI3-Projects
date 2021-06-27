package Model;

import java.io.IOException;
import java.util.List;
import java.util.Map;
import java.util.Set;

public interface UsersInterface {

    void read_users_file(String filepath) throws IOException;

    int get_n_users();

    boolean exists_user(String user_id);

    Set<String> collectUserIds();

}
