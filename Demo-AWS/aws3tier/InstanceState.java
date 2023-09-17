package aws3tier;

/**
 * Represents the possible states of an Amazon EC2 instance.
 *
 * <p>
 * These states provide information about the lifecycle and operational status
 * of an EC2 instance. They help in understanding the current phase in which
 * an instance might be, from its creation to termination.
 * </p>
 *
 * <p><strong>States Explanation:</strong></p>
 * <ul>
 *     <li><strong>PENDING:</strong> The instance is being prepared for running.</li>
 *     <li><strong>RUNNING:</strong> The instance is currently operational.</li>
 *     <li><strong>SHUTTING_DOWN:</strong> The instance is in the process of being stopped or terminated.</li>
 *     <li><strong>TERMINATED:</strong> The instance is fully terminated and cannot be started again.</li>
 *     <li><strong>STOPPING:</strong> The instance is in the process of stopping, but not fully shut down yet.</li>
 *     <li><strong>STOPPED:</strong> The instance is halted but can be started again.</li>
 * </ul>
 */
public enum InstanceState {
    PENDING,
    RUNNING,
    SHUTTING_DOWN,
    TERMINATED,
    STOPPING,
    STOPPED,

}
