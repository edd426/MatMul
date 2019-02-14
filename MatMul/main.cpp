#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <Windows.h>
#include <cuda_runtime.h>

using namespace std;

//extern void use_saxpy_cuda(int n, float a, float * x, float * y);
extern void use_cudamult(int twod, int offset, int* output);

void matmult(int n, int p, int m, float* A, float* B, float* C)
{
	
}


int main(int argc, const char* argv[])
{

	int n = 16;
	int p = 16;
	int m = 16;

	float * A;
	float * B;
	float * C;
	// Allocate memory
	cudaMallocManaged(&A, n*p*sizeof(float));
	cudaMallocManaged(&B, p*m * sizeof(float));
	cudaMallocManaged(&C, n*m * sizeof(float));

	// Initialize matrices
	for (int i = 0; i<n; i++) {
		for (int j = 0; j<p; j++) {
			A[i*n + j] = 1;
		}
	}

	for (int i = 0; i<p; i++) {
		for (int j = 0; j<m; j++) {
			B[i*n + j] = 2;
		}
	}

	matmult(n, p , m, A, B, C);
	cudaDeviceSynchronize();

	cout << "num_repeats is " << num_repeats << endl;

	Sleep(5000);


	//free(x_cu); // CPU version
	cudaFree(x_cu);
}