package aws3tier;

import org.jetbrains.annotations.NotNull;

import java.util.ArrayList;
import java.util.List;

/**
 * Represents the configuration for an EC2 instance.
 * <p>
 * This class provides a builder pattern implementation for constructing EC2 configurations.
 * </p>
 */
public class EC2Configuration {
    private final InstanceType instanceType;
    private final AMI ami;
    private final String instanceId;
    private final List<SecurityGroup> securityGroups;
    private final String vpcId;
    private final String subnetId;
    private final String privateIp;
    private final String publicIp;

    /**
     * Constructs a new {@code EC2Configuration} using the provided {@code ConfigBuilder}.
     * <p>
     * This constructor is intended to be used internally for the builder pattern implementation.
     * </p>
     *
     * @param configBuilder a non-null {@code ConfigBuilder} containing the desired configuration values
     * @throws IllegalArgumentException if the provided {@code ConfigBuilder} is null
     */

    private EC2Configuration(@NotNull ConfigBuilder configBuilder) {
        this.instanceType = configBuilder.instanceType;
        this.ami = configBuilder.ami;
        this.instanceId = configBuilder.instanceId;
        this.securityGroups = configBuilder.securityGroups;
        this.vpcId = configBuilder.vpcId;
        this.subnetId = configBuilder.subnetId;
        this.privateIp = configBuilder.privateIp;
        this.publicIp = configBuilder.publicIp;
    }

    /**
     * A builder for {@code EC2Configuration}, following the Builder design pattern.
     * This builder allows for the incremental construction of an {@code EC2Configuration} object.
     * Each method in this builder, apart from {@code build}, returns the builder itself,
     * allowing for method chaining.
     *
     */
    public static class ConfigBuilder {
        private InstanceType instanceType;
        private AMI ami;
        private String instanceId;
        private List<SecurityGroup> securityGroups;
        private String vpcId;
        private String subnetId;
        private String privateIp;
        private String publicIp;

        public ConfigBuilder() {
            this.securityGroups = new ArrayList<>(); // 기본값
        }

        public ConfigBuilder setInstanceType(InstanceType instanceType) {
            this.instanceType = instanceType;
            return this;
        }

        public ConfigBuilder setAmi(AMI ami) {
            this.ami = ami;
            return this;
        }

        public ConfigBuilder setInstanceId(String instanceId) {
            this.instanceId = instanceId;
            return this;
        }

        public ConfigBuilder setSecurityGroups(List<SecurityGroup> securityGroups) {
            this.securityGroups = securityGroups;
            return this;
        }

        public ConfigBuilder setVpcId(String vpcId) {
            this.vpcId = vpcId;
            return this;
        }

        public ConfigBuilder setSubnetId(String subnetId) {
            this.subnetId = subnetId;
            return this;
        }

        public ConfigBuilder setPrivateIp(String privateIp) {
            this.privateIp = privateIp;
            return this;
        }

        public ConfigBuilder setPublicIp(String publicIp) {
            this.publicIp = publicIp;
            return this;
        }

        public EC2Configuration build() {
            return new EC2Configuration(this);
        }
    }

    public InstanceType getInstanceType() {
        return this.instanceType;
    }

    public AMI getAmi() {
        return this.ami;
    }

    public String getInstanceId() {
        return this.instanceId;
    }

    public List<SecurityGroup> getSecurityGroups() {
        return this.securityGroups;
    }

    public String getVpcId() {
        return this.vpcId;
    }

    public String getSubnetId() {
        return this.subnetId;
    }

    public String getPrivateIp() {
        return this.privateIp;
    }

    public String getPublicIp() {
        return this.publicIp;
    }
}
