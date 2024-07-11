#include <omp.h>
#include <stdio.h>
#include <sys/time.h>   

#define NUM_THREADS 4
#define NUM_ITERATIONS 10000

int shared_variable = 0;

int main() {

    omp_set_num_threads(NUM_THREADS);
    struct timeval t0,t1;
    #pragma omp parallel
    {
        gettimeofday(&t0, 0);
        int tid = omp_get_thread_num();
        int private_sum = 0;

        #pragma omp critical
        {
            shared_variable++;
        }

        #pragma omp atomic
        shared_variable++;
        for (int i = 0; i < NUM_ITERATIONS; i++) {
            private_sum += i;
        }
        // printf("Thread %d: Shared variable value: %d\n", tid, shared_variable);
        printf("Thread %d: Private sum = %d\n", tid, private_sum);

        #pragma omp barrier
        printf("Thread %d reached the barrier\n", tid);
    }

    printf("Final shared variable value: %d\n", shared_variable);
    gettimeofday(&t1, 0);
    double elapsed = (t1.tv_sec-t0.tv_sec) * 1.0f + (t1.tv_usec - t0.tv_usec) / 1000000.0f;
    printf("Elapsed time: %f ms\n", elapsed);
    return 0;
}
