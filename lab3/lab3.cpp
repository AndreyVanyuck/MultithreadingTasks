#include <iostream>
#include <omp.h>

using namespace std;

int const N = 3400;
int const M = 10110;

double calculate_time(int* a, int* b)
{
	long long result[N + M - 1];
	double time_start = omp_get_wtime();
	for (int i = 0; i < N + M - 1; i++)
	{
		long long sum = 0;
		for (int j = 0; j < M; j++)
		{
			if (i - j < N)
				sum += a[i - j] * b[j];
		}
		result[i] = sum;
	}
	double time_end = omp_get_wtime();
	return time_end - time_start;
}

double calculate_parallel_time(int* a, int* b)
{
	long long result[N + M - 1];
	double time_start = omp_get_wtime();
	int i, j;

	omp_set_num_threads(4);
#pragma omp parallel for shared(a, b, result) private(i, j)
	for (i = 0; i < N + M - 1; i++)
	{
		long long sum = 0;
		for (j = 0; j < M; j++)
		{
			if (i - j < N)
				sum += a[i - j] * b[j];
		}
		result[i] = sum;
	}
	double time_end = omp_get_wtime();
	return time_end - time_start;
}

int main()
{
	int a[N], b[M];

	for (int i = 0; i < N; i++) {
		a[i] = 5;
	}
	for (int i = 0; i < M; i++) {
		b[i] = 4;
	}

	double simple_time = calculate_time(a, b);
	double parallel_time = calculate_parallel_time(a, b);
	cout << "simple time " << simple_time << endl;
	cout << "parallel time " << parallel_time << endl;
	
	return 0;
}
