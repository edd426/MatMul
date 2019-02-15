#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <Windows.h>
#include <cuda_runtime.h>

using namespace std;

//extern void use_saxpy_cuda(int n, float a, float * x, float * y);
extern void use_cudamult(int n, int p, int m, float* A, float* B, float* C);

void matmult(int n, int p, int m, float* A, float* B, float* C)
{
	use_cudamult(n, p, m, A, B, C);
}


int main(int argc, const char* argv[])
{

	int n = 3;
	int p = 4;
	int m = 5;

	float * A;
	float * B;
	float * C;
	// Allocate memory
	cudaMallocManaged(&A, n*p*sizeof(float));
	cudaMallocManaged(&B, p*m * sizeof(float));
	cudaMallocManaged(&C, n*m * sizeof(float));


	for (int i = 0; i < n*p; i++) {
		A[i] = 1.0f;
	}

	for (int i = 0; i < p*m; i++) {
		B[i] = 1.0f;
	}

	cout << "A: ";
	for (int i = 0; i < n*p; i++) {
		if (i%p == 0)
			cout << endl;
		cout << A[i] << " ";
	}
	cout << endl;

	cout << "B: ";
	for (int i = 0; i < p*m; i++) {
		if (i%m == 0)
			cout << endl;
		cout << B[i] << " ";
	}
	cout << endl;

	matmult(n, p , m, A, B, C);
	cudaDeviceSynchronize();

	cout << "C: ";
	for (int i = 0; i < n*m; i++) {
		if (i%m == 0 )
			cout << endl;
		cout << C[i] << " ";
	}

	Sleep(6000);

	cudaFree(A);
	cudaFree(B);
	cudaFree(C);

}