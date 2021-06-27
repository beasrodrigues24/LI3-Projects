package Tests.Model;

import Model.Business;
import Model.Businesses;
import java.io.IOException;
import org.junit.jupiter.api.Test;

class BusinessesTest {

    @Test
    void containsBusiness() {
        Businesses b = new Businesses();
        try {
            b.read_businesses_file("src/files/business_full.csv");
            assert b.exists_business("buF9druCkbuXLX526sGELQ");
        } catch (IOException ignore) {}
    }
}
