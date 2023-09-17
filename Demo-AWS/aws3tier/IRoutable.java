package aws3tier;

/**
 * Represents a routable resource in the AWS environment.
 *
 * <p>
 * Resources that can be targeted by routes in a routing table should implement this interface.
 * It provides a method to retrieve a unique identifier for the resource, which can be used
 * to determine the target of a particular route.
 * </p>
 *
 * <p>
 * For example, resources such as Internet Gateways implement
 * this interface to allow them to be targeted by routes.
 * </p>
 */
public interface IRoutable {

    /**
     * Returns the unique identifier for this routable target.
     *
     * @return A unique identifier representing the routable resource.
     */
    String getTargetId();
}
