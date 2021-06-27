package Tests.Model;

import Model.Business;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class BusinessTest {

    @Test
    void getBusiness() {

        String expec_busid = "B1234";
        String expec_busname = "ABCDE";
        String expec_city = "Gaia";
        String expec_state = "Porto";
        String expec_categories = "food";

        Business bus = new Business(expec_busid, expec_busname, expec_city, expec_state, expec_categories);
        assertEquals(expec_busid, bus.getBusiness_id());
        assertEquals(expec_busname, bus.getName());
        assertEquals(expec_city, bus.getCity());
        assertEquals(expec_state, bus.getState());
        assertEquals(expec_categories, bus.getCategories());

    }

}
