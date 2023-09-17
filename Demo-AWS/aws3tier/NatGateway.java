package aws3tier;

/**
 * Represents a Network Address Translation (NAT) gateway in a Virtual Private Cloud (VPC).
 *
 * <p>
 * A NAT gateway enables instances in a private subnet to initiate outbound IPv4
 * traffic to the internet or other AWS services, but it prevents unsolicited inbound
 * traffic from reaching those instances.
 * </p>
 *
 * <p>
 * This class implements the {@link IRoutable} interface, ensuring it can be used
 * as a target in AWS VPC route tables.
 * </p>
 */
public class NatGateway implements IRoutable {

    private String natGatewayId;
    private String vpcId;
    private String subnetId;
    private String state;
    private String elasticIpAddress;
    private String connectivityType;

    /**
     * Constructs a new NAT gateway associated with the specified VPC and subnet.
     *
     * @param natGatewayId The unique identifier for the NAT gateway.
     * @param vpcId        The ID of the VPC in which the NAT gateway resides.
     * @param subnetId     The ID of the subnet in which the NAT gateway resides.
     */
    public NatGateway(String natGatewayId, String vpcId, String subnetId) {
        this.natGatewayId = natGatewayId;
        this.vpcId = vpcId;
        this.subnetId = subnetId;

        // Set default values (subject to change)
        this.state = "pending";  // Initial state is pending
        this.elasticIpAddress = null;  // No EIP assigned initially
        this.connectivityType = "public";  // Default connectivity type is public
    }

    /**
     * Retrieves the target ID for this NAT gateway.
     *
     * @return The NAT gateway ID.
     */
    @Override
    public String getTargetId() {
        return this.natGatewayId;
    }
}
