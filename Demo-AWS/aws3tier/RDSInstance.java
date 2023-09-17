package aws3tier;

import java.util.ArrayList;
import java.util.List;

/**
 * Represents a relational database service (RDS) instance within a specific availability zone (AZ).
 *
 * <p>
 * This class uses a Singleton pattern variant to ensure a limited number of RDS instances
 * are created per availability zone. The maximum number of instances is determined by
 * {@link #MAX_INSTANCES}. Each instance is associated with a specific AZ to ensure
 * high availability and failover capabilities.
 * </p>
 */
public class RDSInstance {

    private static final List<RDSInstance> instances = new ArrayList<>(2);
    private static final int MAX_INSTANCES = 2;
    private AvailabilityZone az;

    /**
     * Private constructor to prevent external instantiation.
     *
     * @param az The availability zone associated with the RDS instance.
     */
    private RDSInstance(AvailabilityZone az) {
        this.az = az;
    }

    /**
     * Retrieves or creates an RDS instance associated with the given availability zone.
     *
     * <p>
     * If the maximum number of instances has been reached, or if an instance already
     * exists for the given AZ, an exception is thrown.
     * </p>
     *
     * @param az The availability zone.
     * @return An RDS instance associated with the given AZ.
     * @throws RuntimeException If the maximum number of instances is exceeded or
     *                          if an instance already exists for the AZ.
     */
    public static RDSInstance getInstance(AvailabilityZone az) {
        if (instances.size() < MAX_INSTANCES && !containsAZ(az)) {
            RDSInstance newInstance = new RDSInstance(az);
            instances.add(newInstance);
            return newInstance;
        } else {
            throw new RuntimeException("Maximum instances reached or AZ already has an instance.");
        }
    }

    /**
     * Retrieves the availability zone associated with this RDS instance.
     *
     * @return The availability zone.
     */
    public AvailabilityZone getAz() {
        return az;
    }

    /**
     * Checks if there is already an RDS instance associated with the given AZ.
     *
     * @param az The availability zone to check.
     * @return {@code true} if an instance exists for the given AZ, {@code false} otherwise.
     */
    private static boolean containsAZ(AvailabilityZone az) {
        return instances
                .stream()
                .anyMatch(instance -> instance.getAz().equals(az));
    }

}
