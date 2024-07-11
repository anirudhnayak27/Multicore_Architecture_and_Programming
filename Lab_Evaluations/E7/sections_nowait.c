#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            printf("Section 1 executed by thread %d\n", omp_get_thread_num());
        }

        #pragma omp section
        {
            printf("Section 2 executed by thread %d\n", omp_get_thread_num());
        }

        #pragma omp section 
        {
            printf("Section 3 executed by thread %d\n", omp_get_thread_num());
        }

        #pragma omp section
        {
            printf("Section 4 executed by thread %d\n", omp_get_thread_num());
        }

        #pragma omp section
        {
            printf("Section 5 executed by thread %d\n", omp_get_thread_num());
        }

        #pragma omp section
        {
            printf("Section 6 executed by thread %d\n", omp_get_thread_num());
        }
    }

    printf("Outside sections executed by thread %d\n", omp_get_thread_num());

    return 0;
}