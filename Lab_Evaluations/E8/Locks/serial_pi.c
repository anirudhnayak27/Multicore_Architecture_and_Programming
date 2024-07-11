#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double calculate_pi_serial(long num_points) {
    long inside_circle = 0;
    srand(time(NULL));

    for (long i = 0; i < num_points; i++) {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        if (x * x + y * y <= 1.0) {
            inside_circle++;
        }
    }

    return (4.0 * inside_circle) / num_points;
}

int main() {
    long num_points = 1000000;  // Number of points to use for the estimation
    double pi_estimate;

    // Measure time
    clock_t start_time = clock();

    // Calculate pi
    pi_estimate = calculate_pi_serial(num_points);

    // Measure time
    clock_t end_time = clock();

    double cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Estimated value of pi: %f\n", pi_estimate);
    printf("Time taken: %f seconds\n", cpu_time_used);

    return 0;
}

