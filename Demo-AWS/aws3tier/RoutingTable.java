package aws3tier;

import java.util.ArrayList;
import java.util.List;

/**
 * Represents a virtual table that maintains the network routes within an Amazon VPC.
 *
 * <p>
 * The {@code RoutingTable} class holds the routes that determine where network traffic is directed.
 * Each VPC has an associated route table, and each subnet in the VPC is explicitly associated with a
 * single route table. The table defines the possible destinations for traffic and the route the traffic
 * should be directed to.
 * </p>
 *
 * <p>
 * For example, when an instance in a VPC sends traffic to a specific IP address, the routing table determines
 * the next hop for that traffic based on the destination IP address.
 * </p>
 */
public class RoutingTable {

    private String routeTableId;
    private String vpcId;
    private List<Route> routeList;
    private List<String> associatedSubnets;

    /**
     * Constructs a new {@code RoutingTable} with a specified ID and associated VPC ID.
     *
     * @param routeTableId the unique ID for the routing table.
     * @param vpcId        the ID of the VPC associated with the routing table.
     */
    public RoutingTable(String routeTableId, String vpcId) {
        this.routeTableId = routeTableId;
        this.vpcId = vpcId;
        this.routeList = new ArrayList<>(64);
        this.associatedSubnets = new ArrayList<>(64);
    }

    /**
     * Adds a new route to the routing table.
     *
     * @param route the route to be added.
     * @throws IllegalArgumentException if the route is null.
     */
    public void addRoute(Route route) {
        if (route == null) {
            throw new IllegalArgumentException("Route cannot be null");
        }
        this.routeList.add(route);
    }

    /**
     * Removes a specified route from the routing table.
     *
     * @param route the route to be removed.
     */
    public void removeRoute(Route route) {
        this.routeList.remove(route);
    }


}
