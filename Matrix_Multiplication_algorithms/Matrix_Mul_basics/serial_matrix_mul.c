#include <stdio.h>
#include <sys/time.h>
#include "test.h"
#define N 100

int main() {
    double A[N][N], B[N][N], C[N][N];
    int i, j;
    struct timeval start, end;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = i + j;
            B[i][j] = i - j;
        }
    }
    gettimeofday(&start, 0);
    matrix_multiply_serial(A, B, C);
    gettimeofday(&end, 0);
    double elapsed = (end.tv_sec - start.tv_sec) * 1.0f + (end.tv_usec - start.tv_usec) / 1000000.0f;
    printf("Elapsed time: %f ms\n", elapsed);
    // printf("Result matrix C:\n");
    // for (i = 0; i < N; i++) {
    //     for (j = 0; j < N; j++) {
    //         printf("%f ", C[i][j]);
    //     }
    //     printf("\n");
    // }

    return 0;
}
