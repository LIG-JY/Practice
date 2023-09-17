package aws3tier;

import java.util.List;
import java.util.stream.Collectors;

/**
 * Implements the IP hash load balancing strategy based on the {@link ILoadBalancingStrategy} interface.
 *
 * <p>
 * This strategy determines the target instance using the hash code of the private IP
 * address of the first running instance in the list. The idea behind this is to provide
 * a deterministic way of routing client requests based on their IP address.
 * </p>
 *
 * <p>
 * The {@link #selectInstance(List)} method returns an EC2 instance based on the Ip hashcode.
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
 *
 */
public class IPHashStrategy implements ILoadBalancingStrategy {

    /**
     * Selects an EC2 instance from the given list based on the IP hash strategy.
     *
     * @param instances A list of EC2 instances from which to select.
     * @return The selected EC2 instance.
     * @throws RuntimeException if there are no available running instances.
     */
    @Override
    public EC2 selectInstance(List<EC2> instances) {
        if (instances.isEmpty()) {
            throw new RuntimeException("No available instances");
        }

        List<EC2> runningInstances = instances.stream()
                .filter(instance -> instance.getInstanceState().equals(InstanceState.RUNNING))
                .collect(Collectors.toList());

        int hashValue = runningInstances.get(0).getPrivateIp().hashCode();
        int index = Math.abs(hashValue) % runningInstances.size();
        return runningInstances.get(index);
    }
}
