package Tests.Model;

import Model.User;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class UserTest {

    @Test
    void getUser() {
        String expected_id = "U12345";
        String expected_name = "Tom";
        User user = new User(expected_id, expected_name);
        String actual_id = user.getUser_id();
        String actual_name = user.getName();
        assertEquals(actual_id, expected_id);
        assertEquals(actual_name, expected_name);
    }

}
