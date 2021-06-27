package Tests.Model;

import Model.Users;
import java.io.IOException;
import org.junit.jupiter.api.Test;

class UsersTest {

    @Test
    void containsUser() {
        Users users = new Users();
        try {
            users.read_users_file("src/files/users_full.csv");
        }
        catch (IOException ignore) {}
        assert users.exists_user("ak0TdVmGKo4pwqdJSTLwWw");
    }
}
