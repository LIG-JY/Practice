package aws3tier;

import java.util.List;

/**
 * Implements a round-robin load balancing strategy based on the {@link ILoadBalancingStrategy} interface.
 *
 * <p>
 * This strategy cycles through a list of EC2 instances in a sequential manner, ensuring that each instance
 * gets a turn to handle a request before starting over. This approach provides a fair distribution of
 * requests to all instances.
 * </p>
 *
 * <p>
 * The {@link #selectInstance(List)} method returns an EC2 instance based on the round robin mechanism.
 * If the end of the list is reached, it wraps around to the beginning.
 * </p>
 *
 * <p>
 * If no instances are in the RUNNING state, a runtime exception will be thrown.
 * </p>
 *
 * <p>
 * Note: The strategy does not account for the health of EC2 instances. Ensure that the provided list
 * only contains healthy instances.
 * </p>
 */
public class RoundRobinStrategy implements ILoadBalancingStrategy {
    private int currentIndex = -1;

    /**
     * Selects an EC2 instance based on the round-robin algorithm.
     *
     * @param instances A list of available EC2 instances.
     * @return The next EC2 instance in line.
     * @throws RuntimeException if the provided list of instances is empty.
     */
    @Override
    public EC2 selectInstance(List<EC2> instances) {
        if (instances.isEmpty()) {
            throw new RuntimeException("No available instances");
        }

        this.currentIndex = (this.currentIndex + 1) % instances.size();
        return instances.get(this.currentIndex);
    }
}
