#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 2
#define ARRAY_SIZE 10000000

int shared_array[ARRAY_SIZE];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *increment_array(void *thread_id) {
    long tid;
    tid = (long)thread_id;

    for (int i = 0; i < ARRAY_SIZE; ++i) {
        pthread_mutex_lock(&mutex);
        shared_array[i]++; // Modify the shared array
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;

    // Create threads
    for (t = 0; t < NUM_THREADS; ++t) {
        rc = pthread_create(&threads[t], NULL, increment_array, (void *)t);
        if (rc) {
            printf("ERROR: return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    // Join threads
    for (t = 0; t < NUM_THREADS; ++t) {
        pthread_join(threads[t], NULL);
    }

    printf("Array elements after incrementing:\n");
    for (int i = 0; i < 10; ++i) {
        printf("%d ", shared_array[i]);
    }
    printf("\n");

    pthread_exit(NULL);
    return 0;
}