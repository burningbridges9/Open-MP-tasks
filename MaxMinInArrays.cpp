// MaxMinInArrays.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <omp.h>
#include <random>
int main()
{
	int a[10], b[10];
	for (int i = 0; i != 10; i++)
	{
		a[i] = rand() % 20 + 1;
		b[i] = rand() % 20 + 1;
	}
	printf("A array:\n");
	for (int i = 0; i != 10; i++)
	{
		printf("%d  ", a[i]);
	}
	printf("\nB array:\n");
	for (int i = 0; i != 10; i++)
	{
		printf("%d  ", b[i]);
	}
	std::cout << std::endl;
	int min, max;
	omp_set_nested(0);

#pragma omp parallel num_threads(2) 
	{
#pragma omp master 
		{
			printf("thread num = %d\n", omp_get_thread_num());
			min = a[0];
			for (int i = 1; i < 10; i++)
			{
				if (min > a[i])
				{
					min = a[i];
				}
				else continue;
			}
			printf("min in array A = %d\n", min);
		}
#pragma omp single
		{
			printf("thread num = %d\n", omp_get_thread_num());
			max = b[0];
			for (int i = 1; i < 10; i++)
			{
				if (max < b[i])
					max = b[i];
				else continue;
			}
			printf("max in array B = %d\n", max);
		}
	}

	
	
	system("pause");
    return 0;
}

