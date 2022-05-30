#ifndef WAIFUGENERATOR_CU_CORE_HH
#define WAIFUGENERATOR_CU_CORE_HH

#include <iostream>
#include <fstream>
#include <iomanip>
#include <functional>
#include <math.h>

#include <curand.h>
#include <cublas_v2.h>
#include <cusolverDn.h>
#include <cuda_runtime.h>
#include <curand_kernel.h>

#define HANDLE_ERROR( err ) ( HandleError( err, FILE, LINE ) )
static void HandleError(cudaError_t err, const char* file, int line)
{
    if (err != cudaSuccess)
    {
        printf("%s in %s at line %d\n", cudaGetErrorString(err), file, line);
        exit(EXIT_FAILURE);
    }
}

size_t block_dim(size_t n_ele);

#endif // !WAIFUGENERATOR_CU_CORE_HH
