#include <stdio.h>
#include <sys/time.h>

#define N 100

void matrix_multiply(double A[N][N], double B[N][N], double C[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void matrix_multiply_parallel(double A[N][N], double B[N][N], double C[N][N]) {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

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
    matrix_multiply(A, B, C);
    gettimeofday(&end, 0);

    // printf("Resultant matrix C:\n");
    // for (int i = 0; i < N; i++) {
    //     for (int j = 0; j < N; j++) {
    //         printf("%d ", C[i][j]);
    //     }
    //     printf("\n");
    // }
    double elapsed = (end.tv_sec - start.tv_sec) * 1.0f + (end.tv_usec - start.tv_usec) / 1000000.0f;
    printf("Serial time: %f ms\n", elapsed);

    gettimeofday(&start, 0);
    matrix_multiply_parallel(A, B, C);
    gettimeofday(&end, 0);

    elapsed = (end.tv_sec - start.tv_sec) * 1.0f + (end.tv_usec - start.tv_usec) / 1000000.0f;
    printf("Parallel time: %f ms\n", elapsed);

    return 0;
}
