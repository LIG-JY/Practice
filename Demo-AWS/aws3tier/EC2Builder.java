package aws3tier;

import java.util.ArrayList;

/**
 * Provides a fluent interface for building Amazon Elastic Compute Cloud (EC2) instances.
 * The {@code EC2Builder} encapsulates the construction logic for EC2 instances and
 * provides a clear API for its creation.
 *
 * <p><strong>Example usage:</strong></p>
 * <pre>
 * EC2 instance1 = ec2Builder1
 *                 .setInstanceType(InstanceType.T)
 *                 .setAmi(AMI.UBUNTU)
 *                 .setInstanceId("i-12345678")
 *                 .setSecurityGroups(new ArrayList<>(Arrays.asList(new SecurityGroup(), new SecurityGroup())))
 *                 .setVpcId("vpc-1234")
 *                 .setSubnetId("subnet-1234")
 *                 .setPrivateIp("192.168.1.10")
 *                 .setPublicIp("203.0.113.0")
 *                 .build();
 * </pre>
 */

public class EC2Builder implements IAmazonResourceBuilder<EC2> {

    /**
     * The internal configuration builder for the EC2 instance.
     */
    private EC2Configuration.ConfigBuilder configBuilder;

    /**
     * Initializes a new EC2Builder with default configurations.
     */
    public EC2Builder() {
        this.configBuilder = new EC2Configuration.ConfigBuilder();
    }

    /**
     * Finalizes the configuration and constructs the EC2 instance.
     *
     * @return The constructed EC2 instance.
     */
    @Override
    public EC2 build() {
        EC2Configuration config = this.configBuilder.build();
        return new EC2(config);
    }

    /**
     * Sets the instance type of the EC2 instance.
     *
     * @param instanceType The instance type.
     * @return This builder.
     */
    public EC2Builder setInstanceType(InstanceType instanceType) {
        this.configBuilder.setInstanceType(instanceType);
        return this;
    }

    /**
     * Sets the AMI (Amazon Machine Image) of the EC2 instance.
     *
     * @param ami The AMI.
     * @return This builder.
     */
    public EC2Builder setAmi(AMI ami) {
        this.configBuilder.setAmi(ami);
        return this;
    }

    /**
     * Sets the ID of the EC2 instance.
     *
     * @param instanceId The ID.
     * @return This builder.
     */
    public EC2Builder setInstanceId(String instanceId) {
        this.configBuilder.setInstanceId(instanceId);
        return this;
    }

    /**
     * Sets a list of security groups for the EC2 instance.
     *
     * @param securityGroups The security groups.
     * @return This builder.
     */
    public EC2Builder setSecurityGroups(ArrayList<SecurityGroup> securityGroups) {
        this.configBuilder.setSecurityGroups(securityGroups);
        return this;
    }

    /**
     * Sets the ID of the VPC that the EC2 instance is in.
     *
     * @param vpcId The ID.
     * @return This builder.
     */
    public EC2Builder setVpcId(String vpcId) {
        this.configBuilder.setVpcId(vpcId);
        return this;
    }

    /**
     * Sets the ID of the subnet that the EC2 instance is in.
     *
     * @param subnetId The ID.
     * @return This builder.
     */
    public EC2Builder setSubnetId(String subnetId) {
        this.configBuilder.setSubnetId(subnetId);
        return this;
    }

    /**
     * Sets the private IP address of the EC2 instance.
     *
     * @param privateIp The private IP address.
     * @return This builder.
     */
    public EC2Builder setPrivateIp(String privateIp) {
        this.configBuilder.setPrivateIp(privateIp);
        return this;
    }

    /**
     * Sets the public IP address of the EC2 instance.
     *
     * @param publicIp The public IP address.
     * @return This builder.
     */
    public EC2Builder setPublicIp(String publicIp) {
        this.configBuilder.setPublicIp(publicIp);
        return this;
    }
}
