#include <stdio.h>
#include <omp.h>

int main() {
    omp_lock_t lock1, lock2;
    omp_init_lock(&lock1);
    omp_init_lock(&lock2);

    #pragma omp parallel num_threads(2)
    {
        int tid = omp_get_thread_num();
        if (tid == 0) {
            omp_set_lock(&lock1);
            printf("Thread 0 acquired lock 1\n");
            // Sleep to introduce potential deadlock
            sleep(1);
            omp_set_lock(&lock2);
            printf("Thread 0 acquired lock 2\n");
            // Do something with both locks
            omp_unset_lock(&lock2);
            printf("Thread 0 released lock 2\n");
            omp_unset_lock(&lock1);
            printf("Thread 0 released lock 1\n");
        } else {
            omp_set_lock(&lock2);
            printf("Thread 1 acquired lock 2\n");
            // Sleep to introduce potential deadlock
            sleep(1);
            omp_set_lock(&lock1);
            printf("Thread 1 acquired lock 1\n");
            // Do something with both locks
            omp_unset_lock(&lock1);
            printf("Thread 1 released lock 1\n");
            omp_unset_lock(&lock2);
            printf("Thread 1 released lock 2\n");
        }
    }

    omp_destroy_lock(&lock1);
    omp_destroy_lock(&lock2);

    return 0;
}
