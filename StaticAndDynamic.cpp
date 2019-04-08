// ForAndReduction.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <omp.h>
#include <iostream>
#include <random>
using namespace std;
int main()
{
	int a[12], b[12], c[12];
	int i;
#pragma omp parallel for schedule(static,12/3)
	for (i = 0; i < 12; i++)
	{
		printf("Amount of threads: %i;\nThread number: %i;\n------------------\n", omp_get_num_threads(), omp_get_thread_num());
		a[i] = rand() % 10 + 1;
		b[i] = rand() % 10 + 1;
	}
	printf("A:\n");
	for (int i = 0; i < 12; i++)
	{
		printf("%i ", a[i]);
	}
	printf("\n");
	printf("B:\n");
	for (int i = 0; i < 12; i++)
	{
		printf("%i ", b[i]);
	}
	printf("\n");
#pragma omp parallel for schedule(dynamic,12/4)
	for (i = 0; i < 12; i++)
	{
		printf("Amount of threads: %i;\nThread number: %i;\n------------------\n", omp_get_num_threads(), omp_get_thread_num());
		c[i] = a[i] + b[i];
	}
	printf("\n");
	printf("C:\n");
	for (int i = 0; i < 12; i++)
	{
		printf("%i ", c[i]);
	}
	/*
	double sum = 0;
	for (int i = 0; i < 100; i++)
	{
		sum += a[i];
	}
	sum /= 100;
	printf("w/o parallel average = %f\n", sum);

	sum = 0;
#pragma omp parallel for reduction (+:sum)
	for (int i = 0; i < 100; i++)
	{
		sum += a[i];
	}

	sum /= 100;
	printf("parallel + reduction average = %f\n", sum);

	sum = 0;
#pragma omp parallel for 
	for (int i = 0; i < 100; i++)
	{
		sum += a[i];
	}

	sum /= 100;
	printf("parallel w/o reduction average = %f\n", sum);
*/
	system("pause");
	return 0;
}

