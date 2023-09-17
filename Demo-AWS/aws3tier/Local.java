package aws3tier;

/**
 * Represents a local target in a Virtual Private Cloud (VPC).
 *
 * <p>
 * In the context of AWS VPC routing, the "local" target refers to the route within
 * the VPC itself. This ensures that traffic between resources inside the VPC is
 * properly routed without needing to leave the VPC.
 * </p>
 *
 * <p>
 * This class implements the {@link IRoutable} interface, ensuring it can be used
 * as a target in AWS VPC route tables.
 * </p>
 */
public class Local implements IRoutable {

    private String vpcId;

    /**
     * Constructs a new Local target for the specified VPC.
     *
     * @param vpcId The ID of the VPC this local target is associated with.
     */
    public Local(String vpcId) {
        this.vpcId = vpcId;
    }

    /**
     * Retrieves the target ID for this local target.
     *
     * <p>
     * For local targets, this is always "local".
     * </p>
     *
     * @return The string "local".
     */
    @Override
    public String getTargetId() {
        return "local";
    }
}
