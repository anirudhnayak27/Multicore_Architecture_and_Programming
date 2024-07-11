//parallel code for matrix multiplication using floating point numbers
#include <stdio.h>
#include <sys/time.h>
#include <omp.h>

#define N 100

void matrix_multiply(float A[N][N], float B[N][N], float C[N][N]) {
    int i, j, k;
    #pragma omp parallel for private(i, j, k) collapse(2)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            float temp = 0.0;
            for (k = 0; k < N; k++) {
                temp += A[i][k] * B[k][j];
            }
            #pragma omp critical
            C[i][j] += temp;
        }
    }
}

void matrix_mul_serial(float A[N][N], float B[N][N], float C[N][N]) {
    int i, j, k;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            float temp = 0.0;
            for (k = 0; k < N; k++) {
                temp += A[i][k] * B[k][j];
            }
            C[i][j] = temp;
        }
    }
}

int main () {
    float A[N][N], B[N][N], C[N][N];
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
    double elapsed = (end.tv_sec - start.tv_sec) * 1.0f + (end.tv_usec - start.tv_usec) / 1000000.0f;
    printf("Parallel time: %f ms\n", elapsed);

    gettimeofday(&start, 0);
    matrix_mul_serial(A, B, C);
    gettimeofday(&end, 0);
    elapsed = (end.tv_sec - start.tv_sec) * 1.0f + (end.tv_usec - start.tv_usec) / 1000000.0f;
    printf("Serial time serial: %f ms\n", elapsed);
    // printf("Result matrix C:\n");
    // for (i = 0; i < N; i++) {
    //     for (j = 0; j < N; j++) {
    //         printf("%f ", C[i][j]);
    //     }
    //     printf("\n");
    // }

    return 0;
}