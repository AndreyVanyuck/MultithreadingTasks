#include <iostream>
#include <omp.h>
#include <cassert>

#define N 20000

using namespace std;

int main() {
    long long a[N], b[N];
    long long result_parallel[N], result_simple[N];
    int i, j;

    for (i = 0; i < N; i++) {
        a[i] = rand();
        b[i] = rand();
        result_parallel[i] = 0;
        result_simple[i] = 0;
    }
    double parallel_time_start = omp_get_wtime();

#pragma omp parallel for private(i,j)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (i - j < N) {
                result_parallel[i] += a[i - j] * b[j];
            }
        }
    }
    double parallel_time_end = omp_get_wtime();

    cout << "Parallel time " << parallel_time_end - parallel_time_start << endl;

    double simple_time_start = omp_get_wtime();
    
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (i - j < N) {
                result_simple[i] += a[i - j] * b[j];
            }
        }
    }

    double simple_time_end = omp_get_wtime();
    
    cout << "Simple time " << simple_time_end - simple_time_start << endl;


    
    for (i = 0; i < N; i++) {
        assert(result_parallel[i] == result_simple[i]);
    }

    return 0;
}
