// DIfferentPortions.cpp: определяет точку входа для консольного приложения.
//

#include <stdafx.h>
#include <omp.h>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

void Add(int * a, int * b, int n, int portion)
{
	printf("------------------------------\n");
	omp_set_num_threads(8);
	double start_time, end_time;
	printf("portion = %i \n", portion);

	printf("static \n");
	start_time = omp_get_wtime();
	b[0] = a[0];
#pragma omp for schedule(static, portion)
		for (int i = 1; i < n - 1; ++i)
			b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3; 
	
	b[n - 1] = a[n - 1];
	end_time = omp_get_wtime();
	printf("elapsed time = %f \n", (end_time - start_time) / (CLOCKS_PER_SEC / 1000));

	printf("dynamic \n");
	start_time = omp_get_wtime();
	b[0] = a[0];
#pragma omp for schedule(dynamic, portion)
		for (int i = 1; i < n - 1; ++i)
			b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3;

	b[n - 1] = a[n - 1];
	end_time = omp_get_wtime();
	printf("elapsed time = %f \n", (end_time - start_time) / (CLOCKS_PER_SEC / 1000));


	printf("guided \n");
	b[0] = a[0];
	start_time = omp_get_wtime();
#pragma omp for schedule(guided, portion)
		for (int i = 1; i < n - 1; ++i)
			b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3;
	
	b[n - 1] = a[n - 1];
	end_time = omp_get_wtime();
	printf("elapsed time = %f \n", (end_time - start_time) / (CLOCKS_PER_SEC / 1000));



	printf("runtime \n");
	start_time = omp_get_wtime();
	b[0] = a[0];
#pragma omp for schedule(runtime)
		for (int i = 1; i < n - 1; ++i)
			b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3;
	
	b[n - 1] = a[n - 1];
	end_time = omp_get_wtime();
	printf("elapsed time = %f \n", (end_time - start_time) / (CLOCKS_PER_SEC / 1000));
	printf("------------------------------\n");
}

int main()
{
	const int n = 16000;
	int a[n], b[n];
	for (int i = 0; i < n; ++i)
		a[i] = i;
	
	for (int i = 100; i<=1000; i+=100)
	{
		Add(a, b, n, i);
	}
	system("pause");
	//  Optimal params is chunk = 500 by static schedule . 
    return 0;
}

