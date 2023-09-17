package aws3tier;

import java.util.Comparator;
import java.util.List;

/**
 * Implements the Least Connections load balancing strategy based on the {@link ILoadBalancingStrategy} interface.
 *
 * <p>
 * This strategy selects an EC2 instance based on the number of current connections
 * to that instance. Specifically, it will choose the instance with the fewest
 * current connections, ensuring that the load is distributed more evenly across
 * all available instances.
 * </p>
 *
 * <p>
 * * The {@link #selectInstance(List)} method returns an EC2 instance based on the least connections mechanism.
 * </p>
 *
 * <p>
 * If there are multiple instances with the same fewest number of connections,
 * one of them will be selected arbitrarily.
 * If no instances are in the RUNNING state, a runtime exception will be thrown.
 * </p>
 *
 * <p>
 * Note: The strategy does not account for the health of EC2 instances. Ensure that the provided list
 * only contains healthy instances.
 * </p>
 */
public class LeastConnectionsStrategy implements ILoadBalancingStrategy {

    /**
     * Selects an EC2 instance based on the least connection strategy.
     *
     * @param instances List of EC2 instances to consider for load balancing.
     * @return An EC2 instance with the fewest current connections.
     * @throws RuntimeException if no instances are available or if no instances are in the RUNNING state.
     */
    @Override
    public EC2 selectInstance(List<EC2> instances) {
        if (instances.isEmpty()) {
            throw new RuntimeException("No available instances");
        }

        return instances.stream()
                .filter(instance -> instance.getInstanceState().equals(InstanceState.RUNNING))
                .min(Comparator.comparingInt(EC2::getCurrentConnections))
                .orElseThrow(() -> new RuntimeException("No available RUNNING instances"));
    }
}
