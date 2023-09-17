package aws3tier;

/**
 * Represents a command that can be executed.
 *
 * <p>
 * This interface is a part of the Command pattern, providing a way to decouple objects
 * that invoke operations from objects that perform the operation.
 * </p>
 *
 */
public interface ICommand {

    /**
     * Executes the command.
     */
    void execute();
}


