#include <stdio.h>
#include <sys/time.h>

#define N 100

void winograd_multiply(double A[N][N], double B[N][N], double C[N][N]) {
    double M[N/2][N/2], P[N/2][N/2], Q[N/2][N/2], R[N/2][N/2];
    double S[N/2][N/2], T[N/2][N/2], U[N/2][N/2], V[N/2][N/2];

    // Calculate M
    for (int i = 0; i < N/2; i++) {
        for (int j = 0; j < N/2; j++) {
            M[i][j] = (A[i][j] + A[i+N/2][j+N/2]) * (B[i][j] + B[i+N/2][j+N/2]);
        }
    }

    // Calculate P
    for (int i = 0; i < N/2; i++) {
        for (int j = 0; j < N/2 - 1; j++) {
            P[i][j] = (A[i][j+N/2] + A[i+N/2][j+N/2]) * B[i+N/2][j+N/2+1];
        }
        P[i][N/2-1] = A[i][N-1] * B[N/2-1][N-1];
    }

    // Calculate Q
    for (int i = 0; i < N/2; i++) {
        Q[i][0] = A[i][0] * (B[0][0] - B[1][0]);
        for (int j = 1; j < N/2; j++) {
            Q[i][j] = A[i][j] * (B[0][j] - B[1][j]);
        }
    }

    // Calculate R
    for (int i = 0; i < N/2; i++) {
        R[i][0] = (A[i+N/2][0] - A[i][0]) * B[0][0];
        for (int j = 1; j < N/2; j++) {
            R[i][j] = (A[i+N/2][j] - A[i][j]) * B[0][j];
        }
    }

    // Calculate S
    for (int i = 0; i < N/2; i++) {
        S[i][0] = A[i][0] * B[0][0];
        for (int j = 1; j < N/2; j++) {
            S[i][j] = A[i][j] * B[0][j] + S[i][j-1];
        }
    }

    // Calculate T
    for (int i = 0; i < N/2; i++) {
        T[i][0] = A[i+N/2][0] * B[0][0];
        for (int j = 1; j < N/2; j++) {
            T[i][j] = A[i+N/2][j] * B[0][j] + T[i][j-1];
        }
    }

    // Calculate U
    for (int i = 0; i < N/2; i++) {
        U[i][0] = A[i][0] * B[1][0];
        for (int j = 1; j < N/2; j++) {
            U[i][j] = A[i][j] * B[1][j] + U[i][j-1];
        }
    }

    // Calculate V
    for (int i = 0; i < N/2; i++) {
        V[i][0] = A[i+N/2][0] * B[1][0];
        for (int j = 1; j < N/2; j++) {
            V[i][j] = A[i+N/2][j] * B[1][j] + V[i][j-1];
        }
    }

    // Calculate C
    for (int i = 0; i < N/2; i++) {
        for (int j = 0; j < N/2; j++) {
            C[i][j] = M[i][j] + P[i][j] - S[i][N/2-1] + T[i][N/2-1];
            C[i][j+N/2] = R[i][j] + S[i][j] + U[i][N/2-1];
            C[i+N/2][j] = Q[i][j] + R[i][N/2-1] + T[i+N/2][j];
            C[i+N/2][j+N/2] = M[i][j] - Q[i][N/2-1] + U[i+N/2][j] - V[i][N/2-1];
        }
    }
}

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
    winograd_multiply(A, B, C);
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

    return 0;
}
