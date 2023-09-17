package aws3tier;

/**
 * The invoker class in the command pattern structure, responsible for executing commands.
 *
 * <p>
 * The {@code RouteTableInvoker} holds a reference to a command object and can invoke
 * the command's {@code execute()} method. This allows for decoupling of the sender
 * from the receiver of a command, enabling more modular and testable code.
 * </p>
 *
 * <p>
 * Example usage:
 * <pre>
 *     ICommand command = new AddRouteCommand(...);
 *     RouteTableInvoker invoker = new RouteTableInvoker();
 *     invoker.setCommand(command);
 *     invoker.executeCommand();
 * </pre>
 * </p>
 */
public class RouteTableInvoker {

    private ICommand command;

    /**
     * Sets the command that the invoker will execute.
     *
     * @param command the command to be set for execution.
     */
    public void setCommand(ICommand command) {
        this.command = command;
    }

    /**
     * Executes the command that has been set.
     */
    public void executeCommand() {
        command.execute();
    }
}
