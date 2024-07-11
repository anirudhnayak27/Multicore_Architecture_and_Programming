#include "_atomic_matrix_mul.h"
#include "Serial_Matrix_Mul.h"
#include <stdio.h>
#include <sys/time.h>
#include <omp.h>
#define N 100

int main() {
    // struct timeval start_serial, end_serial;
    double A[N][N], B[N][N], C[N][N];
    int i, j;
    struct timeval start, end;
    // gettimeofday(&start_serial, 0);
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = i + j;
            B[i][j] = i - j;
        }
    }
    // gettimeofday(&end_serial, 0);
    // double elapsed_serial_e = (end_serial.tv_sec - start_serial.tv_sec) * 1.0f + (end_serial.tv_usec - start_serial.tv_usec) / 1000000.0f;
    // printf("Elapsed time for serial: %f ms\n", elapsed_serial_e);
    gettimeofday(&start, 0);
    matrix_multiply(A, B, C);
    gettimeofday(&end, 0);
    double elapsed = (end.tv_sec - start.tv_sec) * 1.0f + (end.tv_usec - start.tv_usec) / 1000000.0f;
    printf("Elapsed time for parallel: %f ms\n", elapsed);
    gettimeofday(&start, 0);
    matrix_multiply_serial(A, B, C);
    gettimeofday(&end, 0);
    double elapsed_serial = (end.tv_sec - start.tv_sec) * 1.0f + (end.tv_usec - start.tv_usec) / 1000000.0f;
    printf("Elapsed time for serial: %f ms\n", elapsed_serial);
    float speedup;
    speedup = elapsed_serial/elapsed;
    printf("Speedup: %f\n", speedup);
    return 0;
}