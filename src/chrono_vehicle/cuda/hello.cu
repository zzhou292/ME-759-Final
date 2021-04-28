#include "chrono_vehicle/cuda/hello.cuh"
#include <stdio.h>
#include <stdlib.h>

__global__ void cuda_hello() {
  printf("Hello from Thread %d in block %d\n", threadIdx.x, blockIdx.x);
}

void wrapper() {
  cuda_hello<<<1, 1>>>();
  cudaDeviceSynchronize();
}
