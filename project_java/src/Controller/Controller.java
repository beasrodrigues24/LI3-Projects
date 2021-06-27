package Controller;

import java.io.IOException;
import java.util.List;
import java.util.Map;
import java.util.NoSuchElementException;
import java.util.Scanner;
import java.util.regex.PatternSyntaxException;

import static java.lang.System.in;
import View.*;
import Model.*;

public class Controller implements ControllerInterface{

    /**
     * Fields
     */
    private ViewInterface view;
    private GestReviewsInterface gestReviews;

    /**
     * Parametrized Constructor
     * @param view ViewInterface
     * @param gestReviews GestReviewsInterface
     */
    public Controller(ViewInterface view, GestReviewsInterface gestReviews) {
        this.view = view;
        this.gestReviews = gestReviews;
    }

    /**
     * Runs the program
     */
    public void run() {
        Scanner scanner = new Scanner(in);
        boolean flag = true, loaded = false;

        while (!loaded) {
            int n = this.view.welcomePrompt();

            if (n == 1) {
                try {
                    load("files/users_full.csv", "files/reviews_1M.csv", "files/business_full.csv");
                    loaded = true;
                } catch (IOException e) {
                    this.view.loadErrorMessage();
                }
            } else {
                List<String> paths = this.view.pathsToFiles();
                try {
                    load(paths.get(0), paths.get(1), paths.get(2));
                    loaded = true;
                } catch (IOException e) {
                    this.view.loadErrorMessage();
                }

            }
        }

        while (flag) {

            try {
                this.view.queryPrompt();
                String input = scanner.nextLine();
                String[] parsed_input = input.split(" ");
                if (parsed_input.length >= 1) {
                    switch (Integer.parseInt(parsed_input[0])) {
                        case 1:
                            query1();
                            break;
                        case 2:
                            query2(parsed_input);
                            break;
                        case 3:
                            query3(parsed_input);
                            break;
                        case 4:
                            query4(parsed_input);
                            break;
                        case 5:
                            query5(parsed_input);
                            break;
                        case 6:
                            query6(parsed_input);
                            break;
                        case 7:
                            query7();
                            break;
                        case 8:
                            query8(parsed_input);
                            break;
                        case 9:
                            query9(parsed_input);
                            break;
                        case 10:
                            query10();
                            break;
                        case 11:
                            statistics1();
                            break;
                        case 12:
                            statistics2();
                            break;
                        case 13:
                            this.gestReviews = loadObject();
                            break;
                        case 14:
                            saveObject();
                            break;
                        case 0: {
                            view.exitPrompt();
                            flag = false;
                            break;
                        }
                        default:
                            this.view.errorMessage("Invalid option.");
                    }
                }
            } catch (NoSuchElementException | IllegalStateException | PatternSyntaxException e) {
                this.view.errorMessage("Invalid option");
            }

        }

    }

    /**
     * Loads the files
     * @param users_filepath Users' filepath
     * @param reviews_filepath Reviews' filepath
     * @param businesses_filepath Businesses' filepath
     * @throws IOException Couldn't load file
     */
    public void load(String users_filepath, String reviews_filepath, String businesses_filepath) throws IOException {
        Clock.start();
        this.gestReviews.readUsersFile(users_filepath);
        this.gestReviews.readBusinessesFile(businesses_filepath);
        this.gestReviews.readReviewsFile(reviews_filepath);
        double time = Clock.end();
        this.view.loadMessage(time);
    }

    /**
     *  Loads object from path
     */
    public GestReviewsInterface loadObject() {
        Clock.start();
        String path = this.view.objectMenu(true);
        GestReviewsInterface gri = new GestReviews();
        try {
            gri = GestReviewsInterface.loadSGRObject(path);
        }
        catch (IOException | ClassNotFoundException e) {
            this.view.errorMessage("Object not found");
        }
        double time = Clock.end();
        this.view.loadMessage(time);

        return gri;
    }

    /**
     * Loads object from path
     */
    public void saveObject() {
        Scanner scanner = new Scanner(in);
        String path = this.view.objectMenu(false);
        try {
            this.gestReviews.saveSGRObject(path);
        }
        catch (IOException e) {
            this.view.errorMessage("Fail saving");
        }
    }

    /**
     * Runs query 1
     */
    public void query1() {
        Clock.start();
        List<String> output = this.gestReviews.collectsBusinessesNeverEval();
        double time = Clock.end();
        Scanner sc = new Scanner(in);
        int pageSize = 12;
        String option = "";
        int index = 0;
        while(!option.equals("quit")) {
            this.view.printQuery1(output, index, time);
            option = sc.nextLine();
            if(option.equals("prev")) {
                if(index - pageSize < 0) {
                    index = 0;
                }
                else index -= pageSize;
            }
            else if(option.equals("next")) {
                if(index + pageSize < output.size()) index += pageSize;
            }
            else if(option.equals("last")) {
                int realLast = output.size()/12;
                int resto = output.size()%12;
                if(resto==0) {
                    index = (realLast-1)*12;
                }
                else{
                    index = realLast*12;
                }

            }
            else if(option.equals("first")) {
                index = 0;
            }
        }
    }

    /**
     * Runs query 2
     * @param input Month and year
     */
    public void query2(String[] input) {

        try {
            Clock.start();
            Query2Pair output = this.gestReviews.reviewsUsersByDate(Integer.parseInt(input[1]), Integer.parseInt(input[2]));
            double time = Clock.end();
            this.view.printQuery2(output, time);
        }
        catch (NumberFormatException | ArrayIndexOutOfBoundsException e) {
            this.view.errorMessage("Invalid arguments");
        }
        catch (EmptyQueryException e) {
            this.view.errorMessage("Empty query");
        }
    }

    /**
     * Runs query 3
     * @param input User-id
     */
    public void query3(String[] input) {
        try {
            Clock.start();
            Map<Integer, Query3Triple> output = this.gestReviews.userReviewsByMonth(input[1]);
            double time = Clock.end();
            this.view.printQuery3(output, time);
        }
        catch (ArrayIndexOutOfBoundsException e){
            this.view.errorMessage("Invalid arguments");
        }
        catch (UserDoesntExistException e) {
            this.view.errorMessage("Invalid user id");
        }
    }

    /**
     * Runs query 4
     * @param input Business-id
     */
    public void query4(String[] input) {
        try {
            Clock.start();
            Map<Integer, Query4Triple> output = this.gestReviews.businessReviewedByMonth(input[1]);
            double time = Clock.end();
            this.view.printQuery4(output, time);
        }
        catch (ArrayIndexOutOfBoundsException e){
            this.view.errorMessage("Invalid arguments");
        }
        catch (BusinessDoesntExistException e) {
            this.view.errorMessage("Invalid business id");
        }
    }

    /**
     * Runs query 5
     * @param input User-id
     */
    public void query5(String[] input) {
        try {
            Clock.start();
            List<Map.Entry<String, Integer>> output = this.gestReviews.reviewedBusinessesByUser(input[1]);
            double time = Clock.end();
            Scanner sc = new Scanner(in);
            int pageSize = 12;
            String option = "";
            int index = 0;
            while (!option.equals("quit")) {
                this.view.printQuery5(output, index, time);
                option = sc.nextLine();
                if (option.equals("prev")) {
                    if (index - pageSize < 0) {
                        index = 0;
                    } else index -= pageSize;
                } else if (option.equals("next")) {
                    if (index + pageSize < output.size()) index += pageSize;
                } else if (option.equals("last")) {
                    int realLast = output.size() / 12;
                    int resto = output.size() % 12;
                    if (resto == 0) {
                        index = (realLast - 1) * 12;
                    } else {
                        index = realLast * 12;
                    }

                } else if (option.equals("first")) {
                    index = 0;
                }
            }
        }
        catch (ArrayIndexOutOfBoundsException e) {
            this.view.errorMessage("Invalid arguments");
        }
        catch (UserDoesntExistException e) {
            this.view.errorMessage("Invalid user id");
        }

    }

    /**
     * Runs query 6
     * @param input Number of the most reviewed businesses
     */
    public void query6(String[] input) {
        try {
            Clock.start();
            Map<Integer, Map<String, Integer>> output = this.gestReviews.mostReviewedBusinessesByYear(Integer.parseInt(input[1]));
            double time = Clock.end();
            this.view.printQuery6(output, time);
        }
        catch (ArrayIndexOutOfBoundsException e) {
            this.view.errorMessage("Invalid arguments");
        }
    }

    /**
     * Runs query 7
     */
    public void query7() {
        Clock.start();
        Map<String, List<String>> output = this.gestReviews.mostFamousByCity();
        double time = Clock.end();
        this.view.printQuery7(output, time);
    }

    /**
     * Runs query 8
     * @param input Number of users
     */
    public void query8(String[] input) {
        try {
            Clock.start();
            List<Map.Entry<String, Integer>> output = this.gestReviews.usersReviewedMostBusinesses(Integer.parseInt(input[1]));
            double time = Clock.end();
            this.view.printQuery8(output, time);
        }
        catch (ArrayIndexOutOfBoundsException e){
            this.view.errorMessage("Invalid arguments");
        }
    }

    /**
     * Runs query 9
     * @param input Business-id and number Number of users
     */
    public void query9(String[] input) {
        try {
            Clock.start();
            List<Map.Entry<String, Double>> output = this.gestReviews.mostReviewsMadeByUserToBusiness(input[1], Integer.parseInt(input[2]));
            double time = Clock.end();
            this.view.printQuery9(output, time);
        }
        catch (ArrayIndexOutOfBoundsException e) {
            this.view.errorMessage("Invalid arguments");
        }
        catch (BusinessDoesntExistException e) {
            this.view.errorMessage("Invalid business id");
        }
    }

    /**
     * Runs query 10
     */
    public void query10() {
        Clock.start();
        Map<String, Map<String, Map<String, Double>>> output = this.gestReviews.averageScoreByCityAndState();
        double time = Clock.end();
        this.view.printQuery10(output, time);
    }

    /**
     * Runs statistics 1.
     */
    public void statistics1() {
        Clock.start();
        Map<Integer, Integer> output = this.gestReviews.statistics1();
        String filePathUsers = this.gestReviews.getFilePathUsers();
        String filePathBusinesses = this.gestReviews.getFilePathBusinesses();
        String filePathReviews = this.gestReviews.getFilePathReviews();
        double time = Clock.end();
        this.view.printStatistics1(output,filePathUsers, filePathBusinesses, filePathReviews, time);
    }

    /**
     * Runs statistics 2.
     */
    public void statistics2() {
        Clock.start();
        Map<Integer, Integer> output1 = this.gestReviews.statsTotalRevByMonth();
        Map<Integer, Integer> output2 = this.gestReviews.statsUsersRevByMonth();
        Map<Integer, Float> output3 = this.gestReviews.statsAverageStars();
        Float output4 = this.gestReviews.statsAverageStarsGlobal();
        double time = Clock.end();
        this.view.printStatistics2(output1, output2, output3, output4, time);
    }
}
