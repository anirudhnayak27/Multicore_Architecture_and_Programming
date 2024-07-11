#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

// Function to calculate pi using the Monte Carlo method with OpenMP locks
double calculate_pi(long num_points) {
    long inside_circle = 0;
    omp_lock_t_ lock;
    omp_init_nest_lock(&lock);

    #pragma omp parallel
    {
        unsigned int seed = omp_get_thread_num();
        long local_inside_circle = 0;
        
        #pragma omp for
        for (long i = 0; i < num_points; i++) {
            double x = (double)rand_r(&seed) / RAND_MAX;
            double y = (double)rand_r(&seed) / RAND_MAX;
            if (x * x + y * y <= 1.0) {
                local_inside_circle++;
            }
        }

        // Update the global count with the local count in a critical section
        omp_set_nest_lock(&lock);
        inside_circle += local_inside_circle;
        omp_unset_nest_lock(&lock);
    }

    omp_destroy_nest_lock(&lock);
    return (4.0 * inside_circle) / num_points;
}

int main() {
    long num_points = 1000000;  // Number of points to use for the estimation
    double pi_estimate;

    // Initialize OpenMP
    omp_set_num_threads(4);  // Set the number of threads

    // Measure time
    double start_time = omp_get_wtime();

    // Calculate pi
    pi_estimate = calculate_pi(num_points);

    // Measure time
    double end_time = omp_get_wtime();

    printf("Estimated value of pi: %f\n", pi_estimate);
    printf("Time taken: %f seconds\n", end_time - start_time);

    return 0;
}

