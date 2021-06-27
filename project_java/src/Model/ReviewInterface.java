package Model;

public interface ReviewInterface {

    String getReview_id();
    String getBusiness_id();
    String getUser_id();
    Float getStars();
    int getUseful();
    int getFunny();
    int getCool();
    int getMonth();
    int getYear();
    Review clone();

}
