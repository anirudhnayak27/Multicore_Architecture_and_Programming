#include <stdio.h>
#include <omp.h>

int big_calc1(int i) {
    return i;
}

int big_calc2(int i, int A[]) {
    printf("thread after barrier: %d\n", i);
    return A[i];
}

int big_calc3(int i, int C[]) {
    printf("thread after nowait: %d\n", i);
    return C[i]; 
}

int big_calc4(int i) {
    return i+1;
}

int main(){
    int A[1000], B[1000], C[1000];
    int i, tid, num_threads;

    #pragma omp parallel private(i, tid, num_threads) shared(A, B, C)
    {
        tid = omp_get_thread_num();
        num_threads = omp_get_num_threads();
        A[tid] = big_calc1(tid);
        #pragma omp barrier
        #pragma omp for
        for (i = 0; i < num_threads; i++) {
            B[i] = big_calc2(tid, A);
        }
        #pragma omp for nowait
        for(i=0;i< num_threads; i++){
            C[i] = big_calc3(tid,B);
        }
        #pragma omp nowait
        A[tid] = big_calc4(tid);
    }

    return 0;
}