// Newton raphson method in c using parallel programming
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <omp.h>

#define EPSILON 0.001
#define MAX_ITER 1000

double f(double x, double num){
    return x*x - num; 
}

double f_prime(double x){
    return 2*x;
}

double newton_raphson(double x, double num){
    double x1;
    int i;
    #pragma omp parallel for private(x1) shared(x)
    for(i=0;i<MAX_ITER;i++){
        x1 = x - f(x, num)/f_prime(x);
        if(fabs(x1-x) < EPSILON){
            return x1;
        }
        x = x1;
    }
    return x1;
}

int main(){
    double x, num;
    struct timeval start, end;
    printf("Enter the number to find square root: ");
    scanf("%lf",&num);
    printf("Enter the initial guess: ");
    scanf("%lf",&x);
    gettimeofday(&start, NULL);
    x = newton_raphson(x, num);
    gettimeofday(&end, NULL);
    printf("The square root of %lf is: %lf\n", num, x);
    double time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)/1000000.0;    
    printf("Time taken: %.15f\n", time);
    
    return 0;
}