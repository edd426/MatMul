#include <cuda.h>
#include <cuda_runtime.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace std;


__global__ void cudamult(int n, int p, int m, float* A, float* B, float* C)
{
	//int index = threadIdx.x;

	int ROW = blockIdx.y*blockDim.y + threadIdx.y;
	int COL = blockIdx.x*blockDim.x + threadIdx.x;

	float tmpSum = 0;

	if (ROW > n || COL > m)
		return;
	// each thread computes one element of the block sub-matrix
	for (int i = 0; i < p; ++i) {
		tmpSum += A[ROW * p + i] * B[i * m + COL];
	}

	printf("ROW:%d COL:%d sum: %d \n", ROW, COL, tmpSum); // DEBUG

	C[ROW * m + COL] = tmpSum;

}

extern void use_cudamult(int n, int p, int m, float* A, float* B, float* C)
{
	//int threadsPerBlock = 512;
	//int numberOfBlocks = (N + threadsPerBlock - 1) / threadsPerBlock;
	int numThreads = max(max(n, p), m);
	dim3 threadsPerBlock(numThreads, numThreads);
	dim3 blocksPerGrid(1, 1);
	//threadsPerBlock.x = 512;
	//threadsPerBlock.y = 512;
	//blocksPerGrid.x = ceil(double(N) / double(threadsPerBlock.x));
	//blocksPerGrid.y = ceil(double(N) / double(threadsPerBlock.y));


	cudamult << <blocksPerGrid, threadsPerBlock >> > (n, p, m, A, B, C);
	cudaDeviceSynchronize();
}