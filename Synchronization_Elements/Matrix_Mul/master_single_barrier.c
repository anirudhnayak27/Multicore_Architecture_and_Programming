#include <stdio.h>
#include <omp.h>

#define N 10

int main() {
    int fib[N];
    int i, tid, num_threads;

    #pragma omp parallel private(i, tid, num_threads)
    {
        tid = omp_get_thread_num();
        num_threads = omp_get_num_threads();
        #pragma omp barrier
        #pragma omp for schedule(auto)
        for (i = 0; i < N; i++) {
            if (i == 0)
                fib[i] = 0;
            else if (i == 1)
                fib[i] = 1;
            else
                fib[i] = fib[i-1] + fib[i-2];
        }
        #pragma omp barrier
        // Only the master thread executes this block
        #pragma omp master
        {
            printf("Fibonacci sequence (calculated by %d threads) printed by thread %d:\n", num_threads, tid);
            for (i = 0; i < N; i++) {
                printf("%d ", fib[i]);
            }
            printf("\n");
        }
        #pragma omp barrier
        // Only one thread executes this block
        #pragma omp single
        {
            printf("Thread %d computed the Fibonacci sequence.\n", tid);
        }
    }
    

    return 0;
}
