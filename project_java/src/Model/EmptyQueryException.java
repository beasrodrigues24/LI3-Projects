package Model;

public class EmptyQueryException extends Exception {

    public EmptyQueryException() {
        super();
    }

    public EmptyQueryException(String error_message) {
        super(error_message);
    }

}
