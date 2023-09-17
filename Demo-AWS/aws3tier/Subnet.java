package aws3tier;

/**
 * Represents a subnet within an Amazon VPC (Virtual Private Cloud).
 * A subnet is a range of IP addresses in your VPC.
 * <p>
 * The Subnet class provides identifiers and configurations for the specific subnet
 * such as the subnet ID, the VPC ID it belongs to, the availability zone in which it resides,
 * and its CIDR block notation.
 * </p>
 */
public class Subnet {
    private String subnetId;
    private String vpcId;
    private AvailabilityZone az;
    private String CIDR_block;
}
