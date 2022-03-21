#include <stdio.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>

#include <omp.h>
#include <chrono>

using namespace std;
using namespace std::chrono;
#define n 1000

void rand_init(double matrix[n][n]) //将一个n行n列的矩阵中每个元素设置为0~1之间随机数
{
	srand((unsigned)time(0));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			matrix[i][j] = (double)rand() / RAND_MAX;
		}
	}
}
double A[n][n];
double B[n][n];
double C[n][n];
int main()
{

	rand_init(A);
	rand_init(B);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			C[i][j] = 0;
		}
	}
	//clock_t Clockstr1 = clock();
	auto start_time = chrono::high_resolution_clock::now();
	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < n; k++)
		{
			for (int j = 0; j < n; j++)
			{
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	auto serial_time = chrono::high_resolution_clock::now();

#pragma omp parallel for
	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < n; k++)
		{
			for (int j = 0; j < n; j++)
			{
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	auto paral_time = chrono::high_resolution_clock::now();
	double speedup = (double)(serial_time - start_time).count() / (paral_time - serial_time).count();
	//int coreNum = omp_get_num_procs();
	//获取处理器个数
	// printf("不使用并行算法需要时间为%.2f毫秒，使用并行算法需要时间为%.2f毫秒，加速比为%.2f，可用核的个数为%d\n",
	// 	duration_cast<microseconds>(serial_time - start_time).count() / 1e6,
	// 	duration_cast<microseconds>(paral_time - serial_time).count() / 1e6,
	// 	speedup, coreNum);
	printf("不使用并行算法需要时间为%.2f毫秒，使用并行算法需要时间为%.2f毫秒，加速比为%.2f\n",
		   duration_cast<microseconds>(serial_time - start_time).count() / 1e6,
		   duration_cast<microseconds>(paral_time - serial_time).count() / 1e6,
		   speedup);
}
