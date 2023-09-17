package aws3tier;

import java.util.List;

/**
 * Represents a security group in an Amazon VPC.
 *
 * <p>
 * A security group acts as a virtual firewall for EC2 instances to control incoming
 * and outgoing traffic. Inbound rules control the incoming traffic to the instances,
 * and outbound rules control the outgoing traffic from the instances.
 * </p>
 *
 * <p>
 * Typical usage might involve creating a new security group, then adding inbound
 * and outbound rules to define the allowed traffic.
 * </p>
 */
public class SecurityGroup {
    private String sgId;
    private String vpcId;
    private List<Rule> rules;


    //


    /**
     * Represents a rule associated with a security group.
     *
     * <p>
     * Rules define the allowed protocols, ports, and source/destination IP ranges.
     * </p>
     *
     * <p>
     * The Rule class is dependent on SecurityGroup, but for encapsulation and organization purposes,
     * it's implemented as a static nested class.
     * Note: The nested static class can still access the private members of the outer class in Java.
     * </p>
     */
    public abstract static class Rule {
        protected String protocol;
        protected String portRange;

    }

    /**
     * Represents an inbound rule for a security group.
     *
     * <p>
     * Inbound rules define the incoming traffic allowed to the EC2 instances associated
     * with the security group.
     * </p>
     */
    public static class Inbound extends Rule {
        private String source; // CIDR notation for the source IP range

    }

    /**
     * Represents an outbound rule for a security group.
     *
     * <p>
     * Outbound rules define the outgoing traffic allowed from the EC2 instances associated
     * with the security group.
     * </p>
     */
    public static class Outbound extends Rule {
        private String destination; // CIDR notation for the destination IP range

    }

}
