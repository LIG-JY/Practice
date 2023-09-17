package aws3tier;

/**
 * Represents an Amazon VPC Internet Gateway (IGW).
 *
 * <p>
 * An Internet Gateway is a VPC component that allows communication between instances
 * in the VPC and the Internet. It therefore imposes no availability risks or bandwidth constraints
 * on the network traffic.
 * </p>
 *
 * <p>
 * This class implements the {@link IRoutable} interface, ensuring it can be used
 * as a target in AWS VPC route tables.
 * </p>
 */
public class InternetGateway implements IRoutable {
    private String internetGatewayId;
    private String vpcId;
    private String state;

    /**
     * Constructs a new Internet Gateway with a specified ID.
     *
     * @param internetGatewayId The unique identifier for the Internet Gateway.
     */
    public InternetGateway(String internetGatewayId) {
        this.internetGatewayId = internetGatewayId;
        this.state = "detached"; // 초기 상태는 detached, attached로 변경가능
    }

    /**
     * Attaches this Internet Gateway to a specified VPC.
     *
     * @param vpcId The unique identifier of the VPC to attach to.
     * @throws IllegalStateException if the Internet Gateway is already attached to a VPC.
     */
    public void attach(String vpcId) {
        if (this.state.equals("attached")) {
            throw new IllegalStateException("The gateway is already attached to a VPC.");
        }
        this.vpcId = vpcId;
        this.state = "attached";
    }

    /**
     * Returns the unique identifier of this Internet Gateway.
     * This is used for routing purposes when the Internet Gateway is a target in route tables.
     *
     * @return The unique identifier of the Internet Gateway.
     */
    @Override
    public String getTargetId() {
        return this.internetGatewayId;
    }
}
