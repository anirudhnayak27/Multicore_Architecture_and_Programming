#include <stdio.h>
#include <sys/time.h>
// #include <omp.h>

#define N 100
#define BLOCK_SIZE 2

void block_matrix_multiply(double A[N][N], double B[N][N], double C[N][N]) {
    for (int i0 = 0; i0 < N; i0 += BLOCK_SIZE) {
        for (int j0 = 0; j0 < N; j0 += BLOCK_SIZE) {
            for (int k0 = 0; k0 < N; k0 += BLOCK_SIZE) {
                for (int i = i0; i < i0 + BLOCK_SIZE; i++) {
                    for (int j = j0; j < j0 + BLOCK_SIZE; j++) {
                        for (int k = k0; k < k0 + BLOCK_SIZE; k++) {
                            C[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }
}

/*void block_matrix_multiply_parallel(double A[N][N], double B[N][N], double C[N][N]) {
    #pragma omp parallel for collapse(3) schedule(guided,20)
    for (int i0 = 0; i0 < N; i0 += BLOCK_SIZE) {
        for (int j0 = 0; j0 < N; j0 += BLOCK_SIZE) {
            for (int k0 = 0; k0 < N; k0 += BLOCK_SIZE) {
                for (int i = i0; i < i0 + BLOCK_SIZE; i++) {
                    for (int j = j0; j < j0 + BLOCK_SIZE; j++) {
                        for (int k = k0; k < k0 + BLOCK_SIZE; k++) {
                            C[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }
}*/

int main() {
    double A[N][N], B[N][N], C[N][N];
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = i + j;
            B[i][j] = i - j;
        }
    }
    struct timeval start, end;
    gettimeofday(&start, 0);

    block_matrix_multiply(A, B, C);
    gettimeofday(&end, 0);
    /*printf("Resultant matrix C:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }*/
    double elapsed = (end.tv_sec - start.tv_sec) * 1.0f + (end.tv_usec - start.tv_usec) / 1000000.0f;
    printf("Serial time: %f ms\n", elapsed);

    // gettimeofday(&start, 0);
    // block_matrix_multiply_parallel(A, B, C);
    // gettimeofday(&end, 0);

    // elapsed = (end.tv_sec - start.tv_sec) * 1.0f + (end.tv_usec - start.tv_usec) / 1000000.0f;
    // printf("Parallel time: %f ms\n", elapsed);

    return 0;
}
