package aws3tier;

import java.util.List;
import java.util.Random;

/**
 * An Amazon Elastic Compute Cloud (EC2) instance.
 */
public class EC2 {

    /**
     * The instance type of the EC2 instance.
     */
    private InstanceType instanceType;

    /**
     * The AMI (Amazon Machine Image) of the EC2 instance.
     */
    private AMI ami;

    /**
     * The ID of the EC2 instance.
     */
    private String instanceId;

    /**
     * A list of security groups for the EC2 instance.
     */
    private List<SecurityGroup> securityGroups;

    /**
     * The ID of the VPC that the EC2 instance is in.
     */
    private String vpcId;

    /**
     * The ID of the subnet that the EC2 instance is in.
     */
    private String subnetId;

    /**
     * The private IP address of the EC2 instance.
     */
    private String privateIp;

    /**
     * The public IP address of the EC2 instance.
     */
    private String publicIp;

    /**
     * The state of the EC2 instance.
     */
    private InstanceState instanceState;

    /**
     * The current number of connections to the EC2 instance.
     * <p>
     * This is used by the `LeastConnectionsStrategy` load balancing algorithm.
     */
    private int currentConnections;

    /**
     * Creates a new EC2 instance.
     *
     * @param config The configuration for the EC2 instance.
     */
    public EC2(EC2Configuration config) {
        this.instanceType = config.getInstanceType();
        this.ami = config.getAmi();
        this.instanceId = config.getInstanceId();
        this.securityGroups = config.getSecurityGroups();
        this.vpcId = config.getVpcId();
        this.subnetId = config.getSubnetId();
        this.privateIp = config.getPrivateIp();
        this.publicIp = config.getPublicIp();
        this.instanceState = InstanceState.PENDING; // 생성 시 PENDING
    }

    /**
     * Gets the private IP address of the EC2 instance.
     *
     * @return The private IP address of the EC2 instance.
     */
    public String getPrivateIp() {
        return this.privateIp;
    }

    /**
     * Gets the state of the EC2 instance.
     *
     * @return The state of the EC2 instance.
     */
    public InstanceState getInstanceState() {
        return this.instanceState;
    }

    /**
     * Gets the current number of connections to the EC2 instance.
     *
     * @return The current number of connections to the EC2 instance.
     */
    public int getCurrentConnections() {
        return this.currentConnections;
    }

    /**
     * Starts the EC2 instance.
     * <p>
     * If the instance is already running, this method does nothing.
     */
    public void startInstance() {
        if (this.instanceState == InstanceState.PENDING) {
            this.instanceState = InstanceState.RUNNING;
            setRandomConnections();
        }
    }

    /**
     * Sets a random number of connections to the EC2 instance.
     * <p>
     * This is used by the `LeastConnectionsStrategy` load balancing algorithm.
     */
    private void setRandomConnections() {
        Random random = new Random();
        this.currentConnections = random.nextInt(4);
    }
}
