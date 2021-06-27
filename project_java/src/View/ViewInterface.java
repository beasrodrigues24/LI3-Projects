package View;

import java.util.InputMismatchException;
import java.util.List;
import java.util.Map;
import Model.*;

public interface ViewInterface {
    int welcomePrompt();
    List<String> pathsToFiles();
    void queryPrompt();
    String objectMenu(boolean load);
    void exitPrompt();
    void loadMessage(double time);
    void loadErrorMessage();
    void printQuery1(List<String> output, int index, double time);
    void printQuery2(Query2Pair output, double time);
    void printQuery3(Map<Integer, Query3Triple> output, double time);
    void printQuery4(Map<Integer, Query4Triple> output, double time);
    void printQuery5(List<Map.Entry<String,Integer>> output, int index, double time);
    void printQuery6(Map<Integer, Map<String, Integer>> output, double time);
    void printQuery7(Map<String, List<String>> output, double time);
    void printQuery8(List<Map.Entry<String, Integer>> output, double time);
    void printQuery9(List<Map.Entry<String, Double>> output, double time);
    void printQuery10(Map<String, Map<String, Map<String, Double>>> output, double time);
    void printStatistics1(Map<Integer, Integer> output, String filePathUsers, String filePathVusinesses, String filePathReviews, double time);
    void printStatistics2(Map<Integer, Integer> output1, Map<Integer, Integer> output2, Map<Integer, Float> output3, Float output4, double time);
    void errorMessage(String message);
}
