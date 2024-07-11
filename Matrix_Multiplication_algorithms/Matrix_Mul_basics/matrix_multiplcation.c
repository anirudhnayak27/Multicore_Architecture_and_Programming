#include <stdio.h>
#include <omp.h>

#define N 100
#define CHUNKSIZE 100

int main() {
    int i, j, k;
    double start_time, end_time;

    // Define matrices A, B, and C
    double A[N][N], B[N][N], C[N][N];

    // Initialize matrices A and B
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = i + j;
            B[i][j] = i - j;
        }
    }

    start_time = omp_get_wtime(); // Start timing

    // Perform matrix multiplication in parallel
#pragma omp parallel shared(A, B, C) private(i, j, k)
    {
#pragma omp for schedule(dynamic, CHUNKSIZE)
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                for (k = 0; k < N; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
    } // End of parallel region

    end_time = omp_get_wtime(); // End timing

    // Print the execution time
    printf("Matrix multiplication took %f seconds\n", end_time - start_time);

    // Verify correctness (optional)
    // For brevity, we skip printing the result here

    return 0;
}