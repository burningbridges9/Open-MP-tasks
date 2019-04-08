// ForAndReduction.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <omp.h>
#include <iostream>
#include <random>
using namespace std;
int main()
{
	int a[100];
	for (int i = 0; i < 100; i++)
	{
		a[i] = rand() % 10 + 1;
	}
	printf("A:\n");
	for (int i = 0; i < 100; i++)
	{
		printf("%i ", a[i]);
		if (i == 49)
		{
			printf("\n");
		}
	}
	printf("\n");

	double sum = 0;
	for (int i = 0; i < 100; i++)
	{
		sum +=a[i];
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

	system("pause");
    return 0;
}

