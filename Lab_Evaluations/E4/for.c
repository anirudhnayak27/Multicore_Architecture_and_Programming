#include <stdio.h>
#include <omp.h>

double parallelMultiply(int dimension, double matrixA[dimension][dimension], double matrixB[dimension][dimension], double matrixC[dimension][dimension]){

#include <sys/time.h>

struct timeval t0, t1;
	gettimeofday(&t0, 0);

	#pragma omp parallel for
	for(int i=0; i<dimension; i++){
		for(int j=0; j<dimension; j++){
			for(int k=0; k<dimension; k++){
				matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
			}
		}
	}

	gettimeofday(&t1, 0);
	double elapsed = (t1.tv_sec-t0.tv_sec) * 1.0f + (t1.tv_usec - t0.tv_usec) / 1000000.0f;

	return elapsed;
}

int main(){
    int dimension = 10;
    double matrixA[dimension][dimension], matrixB[dimension][dimension], matrixC[dimension][dimension];

    for(int i=0; i<dimension; i++){
        for(int j=0; j<dimension; j++){
            matrixA[i][j] = i + j;
            matrixB[i][j] = i - j;
            matrixC[i][j] = 0;
        }
    }

    double elapsed = parallelMultiply(dimension, matrixA, matrixB, matrixC);
    printf("Matrix multiplication took %f seconds\n", elapsed);

    return 0;
}