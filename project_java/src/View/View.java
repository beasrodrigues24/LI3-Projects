package View;

import java.util.*;

import Model.*;

import static java.lang.System.in;

public class View implements ViewInterface{

    /**
     * Welcome prompt
     */
    public int welcomePrompt() {
        System.out.println("Welcome to the GestReviewsMVC.");
        System.out.println("Load files: ");
        System.out.println("1 - Default");
        System.out.println("2 - Custom");
        Scanner scanner = new Scanner(in);
        boolean flag = true;
        int n = 0;
        while (flag) {
            try {
                n = scanner.nextInt();
                if (n == 1 || n == 2) flag = false;
                else
                    System.out.println("Try again. Invalid option.");
            }
            catch (InputMismatchException | IllegalStateException e) {
                System.out.println("Try again. Invalid option.");
            }
        }
        return n;
    }

    /**
     * Gets path to the custom files
     */
    public List<String> pathsToFiles() {

        List<String> files = new ArrayList<>();
        Scanner scanner = new Scanner(in);
        boolean flag = true;
        while (flag) {
            System.out.print("Insert users file: ");
            String path;
            try {
                path = scanner.nextLine();
                files.add(path);
                System.out.print("Insert businesses file: ");
                path = scanner.nextLine();
                files.add(path);
                System.out.print("Insert reviews file: ");
                path = scanner.nextLine();
                files.add(path);
                flag = false;

            } catch (NoSuchElementException | IllegalStateException e) {
                System.out.println("Try again.");
                files.clear();
            }
        }

        return files;
    }

    /**
     * Options prompt
     */
    public void queryPrompt() {
        System.out.println("Type:");
        System.out.println(" 0    -> Quit Program");
        System.out.println(" 1-10 -> Queries");
        System.out.println(" 11   -> Statistics1");
        System.out.println(" 12   -> Statistics2");
        System.out.println(" 13   -> Load GestReviews from object file");
        System.out.println(" 14   -> Save GestReviews to object file");
    }

    /**
     * Menu for the object options
     * @param load If it's true, it's the load menu; otherwise it's the save menu
     * @return Path to the object file
     */
    public String objectMenu(boolean load) {
        Scanner scanner = new Scanner(in);
        boolean valid = false;
        String path = null;
        while (!valid) {
            if (load)
                System.out.print("Insert path to load the object from or 'default' to load from default .dat file:");
            else
                System.out.print("Insert path to write the object to or 'default' to save to default .dat file: ");
            try {
                path = scanner.nextLine();
                valid = true;
            }
            catch (NoSuchElementException | IllegalStateException e) {
                System.out.println("Invalid option");
            }
        }
        if (path.equals("default"))
            path = "gestReviews.dat";
        return path;
    }

    /**
     * Exit prompt
     */
    public void exitPrompt() {
        System.out.println("Closing program.");
    }

    /**
     * Load message
     * @param time Time loading
     */
    public void loadMessage(double time) {
        System.out.println("Time " + time);
    }

    /**
     * Load error message
     */
    public void loadErrorMessage() {
        System.out.println("Problem opening source files.");
    }

    /**
     * Page message
     */
    public void pageMessage(){
        System.out.println("Next: for the next page");
        System.out.println("prev: for the previous page");
        System.out.println("first: for the first page");
        System.out.println("last: for the last page");
        System.out.println("quit: to exit the table");
    }

    /**
     * Prints query 1
     * @param output Query's output
     * @param time Time running query
     */
    public void printQuery1(List<String> output, int index, double time) {
        System.out.println("Businesses never evaluated: ");
        int page;
        int totalPages;
        if((output.size()&12) == 0) totalPages = output.size()/12;
        else totalPages = (output.size()/12) + 1;
        for(int j = 0; j<Math.min(output.size() - index, 12); j++) {
            System.out.println(output.get(index+j));
        }
        page = (index/12)+1;
        System.out.println(page + " | " + totalPages);

        System.out.println("Total businesses: " + output.size());
        System.out.println("Time " + time + " seconds.");
        this.pageMessage();
    }

    /**
     * Prints query 2
     * @param output Query's output
     * @param time Time running query
     */
    public void printQuery2(Query2Pair output, double time) {
        System.out.println("Reviewed made by user in requested date: ");
        System.out.println("    *Total reviews -> " + output.getTotal_reviews());
        System.out.println("    *Total users -> " + output.getNumber_users());
        System.out.println("Time: " + time + " seconds.");
    }

    /**
     * Prints query 3
     * @param output Query's output
     * @param time Time running query
     */
    public void printQuery3(Map<Integer, Query3Triple> output, double time) {
        System.out.println("User review stats by month: ");
        for (Map.Entry<Integer, Query3Triple> month : output.entrySet()) {
            System.out.println("Month " + month.getKey());
            System.out.println("    *Total reviews -> " + month.getValue().getNumber_reviews());
            System.out.println("    *Average score -> " + month.getValue().getAverage_score());
            System.out.println("    *Number of reviews -> " + month.getValue().getNumber_businesses());
            System.out.println("-------------------------------------------");
        }
        System.out.println("Time " + time + " seconds.");
    }

    /**
     * Prints query 4
     * @param output Query's output
     * @param time Time running query
     */
    public void printQuery4(Map<Integer, Query4Triple> output, double time) {
        System.out.println("Business review stats by month: ");
        for (Map.Entry<Integer, Query4Triple> month : output.entrySet()) {
            System.out.println("Month " + month.getKey());
            System.out.println("    *Total reviews -> " + month.getValue().getN_reviews());
            System.out.println("    *Average score -> " + month.getValue().getAverage_score());
            System.out.println("    *Number of reviews -> " + month.getValue().getN_users());
            System.out.println("-------------------------------------------");
        }
        System.out.println("Time " + time + " seconds.");
    }

    /**
     * Prints query 5
     * @param output Query's output
     * @param time Time running query
     */
    public void printQuery5(List<Map.Entry<String,Integer>> output, int index, double time) {
        System.out.println("Reviewed businesses: ");
        int page;
        int totalPages;
        if((output.size()&12) == 0) totalPages = output.size()/12;
        else totalPages = (output.size()/12) + 1;
        for(int j = 0; j<Math.min(output.size() - index, 12); j++) {
            System.out.println("    * Business: " + output.get(j).getKey() + " with " + output.get(j).getValue() + " reviews.");
        }
        page = (index/12)+1;
        System.out.println(page + " | " + totalPages);

        System.out.println("Time " + time + " seconds.");
        this.pageMessage();
    }

    /**
     * Prints query 6
     * @param output Query's output
     * @param time Time running query
     */
    public void printQuery6(Map<Integer, Map<String, Integer>> output, double time) {
        System.out.println("Most reviewed businesses by year: ");
        for (Map.Entry<Integer, Map<String, Integer>> map : output.entrySet()) {
            System.out.println("Year " + map.getKey());
            for (Map.Entry<String, Integer> entry : map.getValue().entrySet()) {
                System.out.println("    *Business -> " + entry.getKey());
                System.out.println("    *Number of distinct users that reviewed -> " + entry.getValue());
            }
            System.out.println("----------------------------------------");
        }
        System.out.println("Time " + time + " seconds.");
    }

    /**
     * Prints query 7
     * @param output Query's output
     * @param time Time running query
     */
    public void printQuery7(Map<String, List<String>> output, double time) {
        System.out.println("Three most famous businesses from each city: ");
        for (Map.Entry<String, List<String>> entry : output.entrySet()) {
            System.out.println("City: " + entry.getKey());
            for (String s : entry.getValue())
                System.out.println("    *" + s);
            System.out.println("----------------------------------------");
        }
        System.out.println("Time " + time + " seconds.");
    }

    /**
     * Prints query 8
     * @param output Query's output
     * @param time Time running query
     */
    public void printQuery8(List<Map.Entry<String, Integer>> output, double time) {
        System.out.println("Top users who reviewed different businesses: ");
        for (Map.Entry<String,Integer> elem : output)
            System.out.println("User " + elem.getKey() + " made " + elem.getValue() + " reviews.");

        System.out.println("Time " + time + " seconds.");
    }

    /**
     * Prints query 9
     * @param output Query's output
     * @param time Time running query
     */
    public void printQuery9(List<Map.Entry<String, Double>> output, double time) {
        System.out.println("Users who reviewed input business most times: ");
        for (Map.Entry<String, Double> map : output) {
            System.out.println("    *User " + map.getKey() + " with an average score of " + map.getValue());
        }
        System.out.println("Time " + time + " seconds.");
    }

    /**
     * Prints query 10
     * @param output Query's output
     * @param time Time running query
     */
    public void printQuery10(Map<String, Map<String, Map<String, Double>>> output, double time) {
        System.out.println("Average score of each business, city by city, state by state: ");
        for (Map.Entry<String, Map<String, Map<String, Double>>> map : output.entrySet()) {
            System.out.println("State " + map.getKey());
            for (Map.Entry<String, Map<String,Double>> other_map : map.getValue().entrySet()) {
                System.out.println("    *City -> " + other_map.getKey());
                for (Map.Entry<String,Double> final_map : other_map.getValue().entrySet())
                    System.out.println("        *Business " + final_map.getKey() + "has " + final_map.getValue() + " reviews");
            }
        }
        System.out.println("Time " + time + " seconds.");
    }

    /**
     * Prints statistics 1.
     * @param output Statistics1' output
     * @param filePathUsers users file path
     * @param filePathBusinesses businesses file path
     * @param filePathReviews reviews file path
     * @param time Time running it
     */
    public void printStatistics1(Map<Integer, Integer> output, String filePathUsers, String filePathBusinesses, String filePathReviews, double time){
        System.out.println("Statistics 1: ");
        System.out.println("Users file: " + filePathUsers);
        System.out.println("Businesses file: " + filePathBusinesses);
        System.out.println("Reviews file: " + filePathReviews);
        System.out.println("Total number of businesses: " + output.get(1));
        System.out.println("Total number of businesses reviewed: " + output.get(2));
        System.out.println("Total number of businesses not reviewed: " + output.get(3));
        System.out.println("Total number of users: " + output.get(4));
        System.out.println("Total number of users that reviewed: " + output.get(5));
        System.out.println("Total number of users that didn't reviewed: " + output.get(6));
        System.out.println("Total number of reviews with no impact: " + output.get(7));
        System.out.println("Total invalid reviews: " + output.get(8));
    }

    /**
     * Prints statistics 2.
     * @param output1 Statistics2' output
     * @param time Time running it
     */
    public void printStatistics2(Map<Integer, Integer> output1, Map<Integer, Integer> output2, Map<Integer, Float> output3, Float output4, double time){
        System.out.println("Statistics 2: ");
        System.out.println("Total number of reviews by month: ");
        for(Map.Entry<Integer,Integer> r1 : output1.entrySet())
            System.out.println("Month " + r1.getKey() + ": " + r1.getValue());
        System.out.println("Total number of different users that reviewed, by month: ");
        for(Map.Entry<Integer,Integer> r2 : output2.entrySet())
            System.out.println("Month " + r2.getKey() + ": " + r2.getValue());
        System.out.println("Average classification of reviews, by month: ");
        for(Map.Entry<Integer,Float> r3 : output3.entrySet())
            System.out.println("Month " + r3.getKey() + ": " + r3.getValue());
        System.out.println("Average classification of all the reviews: " + output4);
    }

    /**
     * Prints an error message
     * @param message error message
     */
    public void errorMessage(String message) {
        System.out.println(message);
    }
}
