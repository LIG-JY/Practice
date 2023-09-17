package aws3tier;

import java.util.List;

/**
 * Defines the strategy interface for load balancing among a list of EC2 instances.
 *
 * <p>
 * This interface provides a way to abstract the behavior of load balancing
 * and allow for different strategies to be implemented and switched dynamically.
 * Implementing classes should define the behavior for selecting an appropriate EC2 instance
 * from a given list based on specific criteria.
 * </p>
 */
public interface ILoadBalancingStrategy {

    /**
     * Selects an appropriate EC2 instance from the provided list based on the
     * implemented load balancing strategy.
     *
     * @param instances The list of available EC2 instances.
     * @return Selected EC2 instance based on the strategy.
     */
    EC2 selectInstance(List<EC2> instances);
}
