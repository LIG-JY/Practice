package aws3tier;

/**
 * Represents a routing record within a Routing Table in the context of AWS networking.
 *
 * <p>
 * Each {@code Route} object has a destination CIDR block and a target, which can be any entity
 * that implements the {@link IRoutable} interface (e.g., Internet Gateway, NAT Gateway, etc.).
 * The destination CIDR block defines the IP address range for the route, and the target
 * specifies where network traffic is directed when it matches the CIDR block.
 * </p>
 */
public class Route {
    private String destinationCidrBlock;
    private IRoutable target;

    /**
     * Creates a new route with the specified destination CIDR block and target.
     *
     * @param destinationCidrBlock the CIDR notation for the IP address range.
     * @param target               the target to which network traffic is directed when it matches the CIDR block.
     */
    public Route(String destinationCidrBlock, IRoutable target) {
        this.destinationCidrBlock = destinationCidrBlock;
        this.target = target;
    }

}
