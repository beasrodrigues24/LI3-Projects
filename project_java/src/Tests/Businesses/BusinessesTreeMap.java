package Tests.Businesses;

import Model.Business;
import Model.BusinessInterface;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.TreeMap;

public class BusinessesTreeMap {
    /**
     * Fields
     */
    private Map<String, BusinessInterface> businesses_table;

    /**
     * Empty Constructor
     */
    public BusinessesTreeMap() {
        this.businesses_table = new TreeMap<>();
    }

    /**
     * Verifies if a certain business exists through its id
     * @param business_id Business-id
     * @return 1 if it exists, 0 if not
     */
    public boolean exists_business(String business_id) {
        return this.businesses_table.containsKey(business_id);
    }

    /**
     * Searches for certain business through its id
     * @param business_id Business-id
     * @return BusinessInterface
     */
    public BusinessInterface lookup_business(String business_id) {
        return this.businesses_table.get(business_id);
    }

    /**
     * Getter of the number of businesses
     * @return Number of businesses
     */
    public int get_n_businesses() {
        return this.businesses_table.size();
    }

    /**
     * Reads the Businesses' file
     * @param filepath Filepath to the Businesses' file
     * @throws IOException in case I/O failed
     */
    public void read_businesses_file(String filepath) throws IOException {

        BufferedReader inFile = new BufferedReader(new FileReader(filepath));
        String business_buffer;
        while((business_buffer = inFile.readLine()) != null ) {
            Business b = Business.parse_business(business_buffer);
            if(b != null && b.validate_business()) {
                BusinessInterface business = new Business(b);
                businesses_table.put(b.getBusiness_id(), business);
            }

        }
    }

    /**
     * Collects businesses' interfaces in a map whose keys are business-id
     * @return Map with the businesses' interfaces
     */
    public Map<String, BusinessInterface> collectsBusinessesInterfaces() {
        Map<String, BusinessInterface> businessInterfaces = new HashMap<>();
        for (Map.Entry<String, BusinessInterface> e : this.businesses_table.entrySet())
            businessInterfaces.put(e.getKey(), e.getValue().clone());

        return businessInterfaces;
    }
}
