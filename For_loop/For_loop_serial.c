#include <stdio.h>
#include <sys/time.h>
#define N 100

void matrix_multiply_serial(double A[N][N], double B[N][N], double C[N][N]) {
    int i, j, k;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            C[i][j] = 0.0;
            for (k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    double A[N][N], B[N][N], C[N][N];
    int i, j;
    struct timeval start, end, ss, es;
    gettimeofday(&ss, 0);
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = i + j;
            B[i][j] = i - j;
        }
    }
    gettimeofday(&es, 0);
    gettimeofday(&start, 0);
    matrix_multiply_serial(A, B, C);
    gettimeofday(&end, 0);
    double setup = (es.tv_sec - ss.tv_sec) * 1.0f + (es.tv_usec - ss.tv_usec) / 1000000.0f;
    printf("Setup time: %f ms\n", setup);
    double elapsed = (end.tv_sec - start.tv_sec) * 1.0f + (end.tv_usec - start.tv_usec) / 1000000.0f;
    printf("Elapsed time: %f ms\n", elapsed);

    return 0;
}
