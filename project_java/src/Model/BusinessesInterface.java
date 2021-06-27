package Model;

import java.io.IOException;
import java.util.Map;

public interface BusinessesInterface {

    void read_businesses_file(String filepath) throws IOException;

    int get_n_businesses();

    boolean exists_business(String business_id);


    Map<String, BusinessInterface> collectsBusinessesInterfaces();

}
