package Model;

import java.io.BufferedInputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.util.List;
import java.util.Map;

public interface GestReviewsInterface {
    void readUsersFile(String filepath) throws IOException;
    void readBusinessesFile(String filepath) throws IOException;
    void readReviewsFile(String filepath) throws IOException;

    static GestReviewsInterface loadSGRObject(String object_path) throws IOException, ClassNotFoundException {
        FileInputStream fis = new FileInputStream(object_path);
        BufferedInputStream bif = new BufferedInputStream(fis);
        ObjectInputStream ois = new ObjectInputStream(bif);
        GestReviewsInterface gestReviewsInterface = (GestReviewsInterface) ois.readObject();
        ois.close();
        return gestReviewsInterface;
    }

    public String getFilePathUsers();
    public String getFilePathBusinesses();
    public String getFilePathReviews();

    void saveSGRObject(String object_path) throws IOException;

    List<String> collectsBusinessesNeverEval();
    Query2Pair reviewsUsersByDate(int month, int year) throws EmptyQueryException;
    Map<Integer, Query3Triple> userReviewsByMonth(String user_id) throws UserDoesntExistException;
    Map<Integer, Query4Triple> businessReviewedByMonth(String business_id) throws BusinessDoesntExistException;
    List<Map.Entry<String,Integer>> reviewedBusinessesByUser(String user_id) throws UserDoesntExistException;
    Map<Integer, Map<String, Integer>> mostReviewedBusinessesByYear(int number);
    Map<String, List<String>> mostFamousByCity();
    List<Map.Entry<String, Integer>> usersReviewedMostBusinesses(int number);
    List<Map.Entry<String, Double>> mostReviewsMadeByUserToBusiness(String business_id, int number) throws BusinessDoesntExistException;
    Map<String, Map<String, Map<String, Double>>> averageScoreByCityAndState();

    Map<Integer, Integer> statistics1();
    Map<Integer,Integer> statsTotalRevByMonth();
    Map<Integer, Integer> statsUsersRevByMonth();
    Map<Integer, Float> statsAverageStars();
    Float statsAverageStarsGlobal();
}
