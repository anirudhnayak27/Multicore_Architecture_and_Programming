#include <omp.h>
#include <stdio.h>
#include <sys/time.h>

#define NUM_THREADS 4
#define ARRAY_SIZE 100000

int main() {
    int i;
    int array[ARRAY_SIZE];
    struct timeval start, end;
    
    for (i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i;
    }

    // printf("Original Array:\n");
    // for (i = 0; i < ARRAY_SIZE; i++) {
    //     printf("%d ", array[i]);
    // }
    // printf("\n\n");

    gettimeofday(&start, 0);
    // #pragma omp parallel for schedule(auto)
    // #pragma omp parallel for 
    // #pragma omp parallel for reduction(+:array[:ARRAY_SIZE])
    for (i = 0; i < ARRAY_SIZE; i++) {
        array[i] *= 2; 
    }
    gettimeofday(&end, 0);

    // printf("\nModified Array:\n");
    // for (i = 0; i < ARRAY_SIZE; i++) {
    //     printf("%d ", array[i]);
    // }
    // printf("\n");

    double elapsed = (end.tv_sec - start.tv_sec) * 1.0f + (end.tv_usec - start.tv_usec) / 1000000.0f;   
    printf("Elapsed time: %f ms\n", elapsed);

    return 0;
}
