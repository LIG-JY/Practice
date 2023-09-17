package aws3tier;

/**
 * Represents a builder for AWS resources.
 * This interface enforces the builder pattern for constructing AWS resources in a step-by-step manner.
 *
 * @param <T> The type of AWS resource to be built.
 */
public interface IAmazonResourceBuilder<T> {

    /**
     * Builds and returns an instance of the AWS resource.
     *
     * @return The built AWS resource of type {@code T}.
     */
    T build();

}
