#include <omp.h>
#include <stdio.h>

#define N 4
#define ITERATIONS 1000000
#define PAD 64 / sizeof(int)  // Assuming a cache line size of 64 bytes

int main() {
    int array[N][PAD] = {0};  // 2D array to introduce padding

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < ITERATIONS; j++) {
            array[i][0]++;
        }
    }

    for (int i = 0; i < N; i++) {
        printf("array[%d][0] = %d\n", i, array[i][0]);
    }

    return 0;
}
