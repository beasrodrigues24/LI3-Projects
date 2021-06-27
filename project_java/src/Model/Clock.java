package Model;

public class Clock {

    /**
     * Fields
     */
    private static double start_time = 0;

    /**
     * Starts counting the running time
     */
    public static void start() {
        start_time = System.nanoTime();
    }

    /**
     * Ends counter and calculates the time running
     * @return Time running
     */
    public static double end() {
        return (System.nanoTime() - start_time)/(Math.pow(10, 9));
    }

}
