#include <stdio.h>
#include <sys/time.h>
#include <omp.h>

void strassen_multiply(int N, int A[N][N], int B[N][N], int C[N][N]);

void naive_multiply(int N, int A[N][N], int B[N][N], int C[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void strassen_multiply(int N, int A[N][N], int B[N][N], int C[N][N]) {
    if (N == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int A11[N/2][N/2], A12[N/2][N/2], A21[N/2][N/2], A22[N/2][N/2];
    int B11[N/2][N/2], B12[N/2][N/2], B21[N/2][N/2], B22[N/2][N/2];
    int M1[N/2][N/2], M2[N/2][N/2], M3[N/2][N/2], M4[N/2][N/2], M5[N/2][N/2], M6[N/2][N/2], M7[N/2][N/2];
    int temp1[N/2][N/2], temp2[N/2][N/2];

    for (int i = 0; i < N/2; i++) {
        for (int j = 0; j < N/2; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + N/2];
            A21[i][j] = A[i + N/2][j];
            A22[i][j] = A[i + N/2][j + N/2];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + N/2];
            B21[i][j] = B[i + N/2][j];
            B22[i][j] = B[i + N/2][j + N/2];
        }
    }

    strassen_multiply(N/2, A11, B11, temp1);
    strassen_multiply(N/2, A12, B21, temp2);
    naive_multiply(N/2, temp1, temp2, M1);

    strassen_multiply(N/2, A11, B12, temp1);
    strassen_multiply(N/2, A12, B22, temp2);
    naive_multiply(N/2, temp1, temp2, M2);

    strassen_multiply(N/2, A21, B11, temp1);
    strassen_multiply(N/2, A22, B21, temp2);
    naive_multiply(N/2, temp1, temp2, M3);

    strassen_multiply(N/2, A21, B12, temp1);
    strassen_multiply(N/2, A22, B22, temp2);
    naive_multiply(N/2, temp1, temp2, M4);

    strassen_multiply(N/2, A11, B22, temp1);
    strassen_multiply(N/2, A22, B11, temp2);
    naive_multiply(N/2, temp1, temp2, M5);

    strassen_multiply(N/2, A12, B21, temp1);
    strassen_multiply(N/2, A22, B12, temp2);
    naive_multiply(N/2, temp1, temp2, M6);

    strassen_multiply(N/2, A11, B21, temp1);
    strassen_multiply(N/2, A21, B12, temp2);
    naive_multiply(N/2, temp1, temp2, M7);

    // Compute result submatrices
    for (int i = 0; i < N/2; i++) {
        for (int j = 0; j < N/2; j++) {
            C[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
            C[i][j + N/2] = M3[i][j] + M5[i][j];
            C[i + N/2][j] = M2[i][j] + M4[i][j];
            C[i + N/2][j + N/2] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
        }
    }
}

void naive_multiply_parallel(int N, int A[N][N], int B[N][N], int C[N][N]) {
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

void strassen_multiply_parallel(int N, int A[N][N], int B[N][N], int C[N][N]) {
    if (N == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int A11[N/2][N/2], A12[N/2][N/2], A21[N/2][N/2], A22[N/2][N/2];
    int B11[N/2][N/2], B12[N/2][N/2], B21[N/2][N/2], B22[N/2][N/2];
    int M1[N/2][N/2], M2[N/2][N/2], M3[N/2][N/2], M4[N/2][N/2], M5[N/2][N/2], M6[N/2][N/2], M7[N/2][N/2];
    int temp1[N/2][N/2], temp2[N/2][N/2];

    #pragma omp parallel for 
    for (int i = 0; i < N/2; i++) {
        for (int j = 0; j < N/2; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + N/2];
            A21[i][j] = A[i + N/2][j];
            A22[i][j] = A[i + N/2][j + N/2];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + N/2];
            B21[i][j] = B[i + N/2][j];
            B22[i][j] = B[i + N/2][j + N/2];
        }
    }

    #pragma omp parallel sections
    {
        #pragma omp section 
        {
            strassen_multiply_parallel(N/2, A11, B11, temp1);
            strassen_multiply_parallel(N/2, A12, B21, temp2);
            naive_multiply_parallel(N/2, temp1, temp2, M1);
        }

        #pragma omp section
        {
            strassen_multiply_parallel(N/2, A11, B12, temp1);
            strassen_multiply_parallel(N/2, A12, B22, temp2);
            naive_multiply_parallel(N/2, temp1, temp2, M2);
        }

        #pragma omp section
        {
            strassen_multiply_parallel(N/2, A21, B11, temp1);
            strassen_multiply_parallel(N/2, A22, B21, temp2);
            naive_multiply_parallel(N/2, temp1, temp2, M3);
        }

        #pragma omp section
        {
            strassen_multiply_parallel(N/2, A21, B12, temp1);
            strassen_multiply_parallel(N/2, A22, B22, temp2);
            naive_multiply_parallel(N/2, temp1, temp2, M4);
        }

        #pragma omp section
        {
            strassen_multiply_parallel(N/2, A11, B22, temp1);
            strassen_multiply_parallel(N/2, A22, B11, temp2);
            naive_multiply_parallel(N/2, temp1, temp2, M5);
        }

        #pragma omp section
        {
            strassen_multiply_parallel(N/2, A12, B21, temp1);
            strassen_multiply_parallel(N/2, A22, B12, temp2);
            naive_multiply_parallel(N/2, temp1, temp2, M6);
        }

        #pragma omp section 
        {
            strassen_multiply_parallel(N/2, A11, B21, temp1);
            strassen_multiply_parallel(N/2, A21, B12, temp2);
            naive_multiply_parallel(N/2, temp1, temp2, M7);
        }
        #pragma omp section
        {
            #pragma omp parallel for 
            for (int i = 0; i < N/2; i++) {
                for (int j = 0; j < N/2; j++) {
                    C[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
                    C[i][j + N/2] = M3[i][j] + M5[i][j];
                    C[i + N/2][j] = M2[i][j] + M4[i][j];
                    C[i + N/2][j + N/2] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
                }
            }
        }
    }
}


int main() {
    int N = 100;
    int A[N][N], B[N][N], C[N][N];
    int i, j;
    
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = i + j;
            B[i][j] = i - j;
        }
    }
    struct timeval start, end;
    gettimeofday(&start, 0);
    strassen_multiply(N, A, B, C);
    gettimeofday(&end, 0);

    double elapsed = (end.tv_sec - start.tv_sec) * 1.0f + (end.tv_usec - start.tv_usec) / 1000000.0f;
    printf("Serial time: %f ms\n", elapsed);

    gettimeofday(&start, 0);
    strassen_multiply_parallel(N, A, B, C);
    gettimeofday(&end, 0);

    elapsed = (end.tv_sec - start.tv_sec) * 1.0f + (end.tv_usec - start.tv_usec) / 1000000.0f;
    printf("Parallel time: %f ms\n", elapsed);

    /*printf("Resultant matrix C:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }*/

    return 0;
}