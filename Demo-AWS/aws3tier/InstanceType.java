package aws3tier;

/**
 * Enumerates the types of Amazon EC2 instances based on their optimized capacities.
 *
 * <p>
 * Amazon EC2 provides a variety of instance types optimized to fit different use cases.
 * Instances are grouped into families based on target application needs such as
 * computational power, memory capacity, storage, and networking capabilities.
 * </p>
 *
 * <p><strong>Instance Types Explanation:</strong></p>
 * <ul>
 *     <li><strong>M:</strong> General Purpose - Balanced compute, memory, and networking resources.</li>
 *     <li><strong>T:</strong> General Purpose - Burstable performance instances.</li>
 *     <li><strong>C:</strong> Compute Optimized - Suited for compute-bound applications.</li>
 *     <li><strong>R:</strong> Memory Optimized - Suitable for memory-intensive applications.</li>
 *     <li><strong>P:</strong> Accelerated Computing - Used for general-purpose GPU compute applications.</li>
 *     <li><strong>I:</strong> Storage Optimized - Optimized for high random I/O performance.</li>
 *     <li><strong>HPC:</strong> High Performance Computing - Used for batch processing, analytics, simulations, etc.</li>
 * </ul>
 */
public enum InstanceType {
    M,   // General Purpose
    T,   // General Purpose Burstable
    C,   // Compute Optimized
    R,   // Memory Optimized
    P,   // Accelerated Computing
    I,   // Storage Optimized
    HPC  // High Performance Computing
}
