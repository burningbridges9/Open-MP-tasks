// MaxMinInArrays.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <omp.h>
#include <random>
int main()
{
	int d[6][8];
	for (int i = 0; i != 6; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			d[i][j] = rand() % 10 + 1;
		}
	}
	printf("double dimencional array:\n");
	for (int i = 0; i != 6; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			printf("%d  ", d[i][j]);
		}
		printf("\n");
	}

#pragma omp sections
	{
	#pragma omp section //mid
		{
			double sum = 0;
			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					sum+=d[i][j];
				}
			}
			sum /= 6.0 * 8.0;
			printf("Average = %f\n", sum);
			printf("numOfThread = %i\n", omp_get_thread_num());
		}

	#pragma omp section //minmax
	{
		int min, max;
		min = max = d[0][0];
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (min > d[i][j])
					min = d[i][j];

				if (max < d[i][j])
					max = d[i][j];
			}
		}

		printf("min = %i\n", min);
		printf("max = %i\n", max);
		printf("numOfThread = %i\n", omp_get_thread_num());
	}

	#pragma omp section // %3=0
	{
		int count = 0;
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (d[i][j] % 3 == 0)
				{
					count++;
				}
				else continue;
			}
		}
		printf("count = %i\n", count);
		printf("numOfThread = %i\n", omp_get_thread_num());
	}

}

	system("pause");
	return 0;
}

