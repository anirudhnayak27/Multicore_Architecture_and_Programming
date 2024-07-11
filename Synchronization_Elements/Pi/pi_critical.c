#include <stdio.h>
#include <omp.h>
static long num_steps = 100000;   double step;
#define Threads 1;
void main(){
    double itime = omp_get_wtime();
    int i,nthreads;
    double pi,sum;
    step = 1.0/(double) num_steps;
    omp_set_num_threads(2);
    #pragma omp parallel
    {
        int i,id,ntds;
        double x;
        id = omp_get_thread_num();
        ntds = omp_get_num_threads();
        if(id == 0) nthreads = ntds;
        for(i=id,sum=0.0;i<num_steps;i=i+ntds){
            x = (i+0.5)*step;
            sum += 4.0/(1.0+x*x);
        }
        #pragma omp critical
        pi += sum *step;
    }
    int ftime  = omp_get_wtime();
    printf("Time: %f\n", ftime-itime);
}