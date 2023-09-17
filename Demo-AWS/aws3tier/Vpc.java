package aws3tier;

import java.util.List;

/**
 * Represents a Virtual Private Cloud (VPC) in the AWS ecosystem.
 * <p>
 * A VPC is a logically isolated section of the AWS Cloud where AWS resources
 * run in a virtual network that you define. With a VPC, you have control over
 * your network settings, such as IP address range, subnets, route tables,
 * and network gateways.
 * </p>
 * <p>
 * This class encapsulates various configurations and associations related to a VPC,
 * including associated subnets, route tables, security groups, internet gateways,
 * and NAT gateways.
 * </p>
 */
public class Vpc {
    private String vpcId;
    private String ipv4CidrBlock;
    private String state;
    private List<Subnet> associatedSubnets;
    private List<RoutingTable> routeTables;
    private List<SecurityGroup> securityGroups;
    private List<InternetGateway> internetGateways;
    private List<NatGateway> natGateways;


    /**
     * Constructs a new VPC with the specified ID and IP address range.
     *
     * @param vpcId The unique identifier for the VPC.
     * @param ipv4CidrBlock The IPv4 network range for the VPC, in CIDR notation.
     */
    public Vpc(String vpcId, String ipv4CidrBlock) {
        this.vpcId = vpcId;
        this.ipv4CidrBlock = ipv4CidrBlock;
        this.state = "Available"; // pending 상태 생략
    }
}
