#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main() {
    int num_points = 1000000;
    int count = 0;
    double pi;

    struct timeval start, end;
    gettimeofday(&start, NULL);
    #pragma omp parallel
    {
        int local_count = 0;
        unsigned int seed = omp_get_thread_num();
        #pragma omp for lastprivate(count)
        for (int i = 0; i < num_points; ++i) {
            double x = (double)rand_r(&seed) / RAND_MAX;
            double y = (double)rand_r(&seed) / RAND_MAX;
            if (x * x + y * y <= 1.0) {
                local_count++;
            }
        }

        #pragma omp critical
        count += local_count;
    }
    gettimeofday(&end, NULL);

    pi = 4.0 * count / num_points;
    printf("Estimated Pi = %f\n", pi);

    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    printf("Time elapsed: %f seconds\n", elapsed);

    return 0;
}
