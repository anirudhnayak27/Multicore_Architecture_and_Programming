#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <sys/time.h>

// Simulation parameters
#define NX 100
#define NY 100
#define MAX_ITER 10000
#define DT 0.01
#define RE 100.0

// Function to initialize fields
void initialize(double u[NX][NY], double v[NX][NY], double p[NX][NY]) {
    int i, j;
    #pragma omp parallel for private(i, j)
    for (i = 0; i < NX; i++) {
        for (j = 0; j < NY; j++) {
            u[i][j] = 0.0;
            v[i][j] = 0.0;
            p[i][j] = 1.0;
        }
    }
}

// Function to calculate the velocity field
void update_velocity(double u[NX][NY], double v[NX][NY], double p[NX][NY], double u_new[NX][NY], double v_new[NX][NY]) {
    int i, j;
    double dx = 1.0 / (NX - 1);
    double dy = 1.0 / (NY - 1);

    #pragma omp parallel for private(i, j) shared(u, v, p, u_new, v_new)
    for (i = 1; i < NX - 1; i++) {
        for (j = 1; j < NY - 1; j++) {
            u_new[i][j] = u[i][j] - u[i][j] * DT / dx * (u[i][j] - u[i - 1][j])
                                      - v[i][j] * DT / dy * (u[i][j] - u[i][j - 1])
                                      - DT / (2.0 * dx) * (p[i + 1][j] - p[i - 1][j])
                                      + DT / (RE * dx * dx) * (u[i + 1][j] - 2.0 * u[i][j] + u[i - 1][j])
                                      + DT / (RE * dy * dy) * (u[i][j + 1] - 2.0 * u[i][j] + u[i][j - 1]);
            v_new[i][j] = v[i][j] - u[i][j] * DT / dx * (v[i][j] - v[i - 1][j])
                                      - v[i][j] * DT / dy * (v[i][j] - v[i][j - 1])
                                      - DT / (2.0 * dy) * (p[i][j + 1] - p[i][j - 1])
                                      + DT / (RE * dx * dx) * (v[i + 1][j] - 2.0 * v[i][j] + v[i - 1][j])
                                      + DT / (RE * dy * dy) * (v[i][j + 1] - 2.0 * v[i][j] + v[i][j - 1]);
        }
    }
}

// Function to update the pressure field
void update_pressure(double u[NX][NY], double v[NX][NY], double p[NX][NY], double p_new[NX][NY]) {
    int i, j;
    double dx = 1.0 / (NX - 1);
    double dy = 1.0 / (NY - 1);
    double b[NX][NY];

    #pragma omp parallel for private(i, j) shared(u, v, b)
    for (i = 1; i < NX - 1; i++) {
        for (j = 1; j < NY - 1; j++) {
            b[i][j] = (u[i + 1][j] - u[i - 1][j]) / (2.0 * dx) + (v[i][j + 1] - v[i][j - 1]) / (2.0 * dy);
        }
    }

    #pragma omp parallel for private(i, j) shared(p, p_new, b)
    for (i = 1; i < NX - 1; i++) {
        for (j = 1; j < NY - 1; j++) {
            p_new[i][j] = (b[i][j]
                           - (p[i + 1][j] + p[i - 1][j]) / (dx * dx)
                           - (p[i][j + 1] + p[i][j - 1]) / (dy * dy))
                          / (-2.0 / (dx * dx) - 2.0 / (dy * dy));
        }
    }
}

// Main function
int main() {
    double u[NX][NY], v[NX][NY], p[NX][NY];
    double u_new[NX][NY], v_new[NX][NY], p_new[NX][NY];
    int iter;
    struct timeval start, end;
    gettimeofday(&start, NULL);
    // Initialize fields
    initialize(u, v, p);

    // Time-stepping loop
    for (iter = 0; iter < MAX_ITER; iter++) {
        update_velocity(u, v, p, u_new, v_new);
        update_pressure(u, v, p, p_new);

        // Update old fields with new values
        #pragma omp parallel for
        for (int i = 0; i < NX; i++) {
            for (int j = 0; j < NY; j++) {
                u[i][j] = u_new[i][j];
                v[i][j] = v_new[i][j];
                p[i][j] = p_new[i][j];
            }
        }
    }
    gettimeofday(&end, NULL);

    // Calculate elapsed time
    double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
    printf("Parallel time: %f seconds\n", elapsed_time);
    // Output results
    // for (int i = 0; i < NX; i++) {
    //     for (int j = 0; j < NY; j++) {
    //         printf("u[%d][%d] = %f, v[%d][%d] = %f, p[%d][%d] = %f\n", i, j, u[i][j], i, j, v[i][j], i, j, p[i][j]);
    //     }
    // }

    return 0;
}
