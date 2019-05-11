#include <unistd.h>
#include <stdlib.h>
// #include <mpi.h>
#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <chrono>
#include <iostream>
#define THREADS 4
#define N 16
using namespace std;
int main()
{
    auto start = std::chrono::system_clock::now();
    int i;
    printf("Running %d iterations on %d threads dynamically.\n", N, THREADS);
    #pragma omp parallel for schedule(guided) num_threads(THREADS)
    for (i = 0; i < N; i++)
    {
        /* a loop that doesn’t take very long */
        sleep(i);
        printf("Thread %d has completed iteration %d.\n", omp_get_thread_num(), i);
    }
    /* all threads done */
    printf("All done!\n");
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << elapsed.count() << '\n';
    return 0;
}