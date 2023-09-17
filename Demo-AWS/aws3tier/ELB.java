package aws3tier;

import java.util.List;

/**
 * Represents an Elastic Load Balancer (ELB) in the AWS ecosystem.
 * The ELB is responsible for distributing incoming traffic across multiple targets,
 * such as EC2 instances, in one or more Availability Zones.
 * The distribution strategy is determined by the provided {@link ILoadBalancingStrategy}.
 *
 * <p><strong>Example usage:</strong></p>
 * <pre>
 * ELB elb = new ELB(new RoundRobinStrategy(), targetInstances);
 * EC2 targetInstance = elb.getTargetInstance();
 * </pre>
 */
public class ELB {
    // Represents the strategy context in the Strategy Pattern
    private ILoadBalancingStrategy strategy;

    // The list of EC2 instances which are targeted by this ELB
    private List<EC2> targetGroup;

    /**
     * Constructs a new ELB with the specified load balancing strategy and target group.
     *
     * @param strategy    The strategy to use for load balancing.
     * @param targetGroup The group of EC2 instances to balance the load across.
     */
    public ELB(ILoadBalancingStrategy strategy, List<EC2> targetGroup) {
        this.strategy = strategy;
        this.targetGroup = targetGroup;
    }

    /**
     * Retrieves a target EC2 instance based on the currently set load balancing strategy.
     *
     * @return The selected EC2 instance.
     */
    public EC2 getTargetInstance() {
        return this.strategy.selectInstance(this.targetGroup);
    }

    /**
     * Sets the load balancing strategy for this ELB.
     * use Strategy pattern
     *
     * @param strategy The new load balancing strategy.
     */
    public void setStrategy(ILoadBalancingStrategy strategy) {
        this.strategy = strategy;
    }
}
