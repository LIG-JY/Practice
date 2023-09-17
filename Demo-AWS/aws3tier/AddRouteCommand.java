package aws3tier;

/**
 * A command class implementing the ICommand interface to represent
 * the action of adding a route to a given routing table.
 *
 * @see ICommand
 * @see RoutingTable
 * @see Route
 */
public class AddRouteCommand implements ICommand {

    private RoutingTable routingTable;
    private Route route;

    /**
     * Constructs a new AddRouteCommand with the specified routing table
     * and route.
     *
     * @param routingTable the target routing table where the route will be added
     * @param route        the route to be added
     */
    public AddRouteCommand(RoutingTable routingTable, Route route) {
        this.routingTable = routingTable;
        this.route = route;
    }

    /**
     * Executes the command which adds the route to the specified routing table.
     * After adding the route, a message is printed indicating the addition.
     */
    @Override
    public void execute() {
        this.routingTable.addRoute(this.route);
        System.out.println(this.route.toString() + " added to the routing table!");
    }
}
