//
// Created by rafael on 5/14/22.
//

#include <iostream>
#include "OpenMP.h"

int pi() {
    int i;
    long double pi = 0.0;
    const long double step = 1.0 / (INT_MAX);

    int threads;
#pragma omp parallel default(none) shared(threads)
    {
        threads = omp_get_num_threads();
    }

    long double sum[threads];

#pragma omp parallel shared(step, sum) default(none)
    {
        long double x;
        int thread = omp_get_thread_num();
        sum[thread] = 0.0;

#pragma omp for
        for (i = 1; i < INT_MAX; i++) {
            x = (i - 0.5) * step;
            sum[thread] += 4 / (1 + (x * x));
        }
    }

    for (i = 0; i < threads; i++) {
        pi += (step * sum[i]);
    }
    std::cout << "El resultado es: " << pi << std::endl;
    return EXIT_SUCCESS;
}


