// MatrixOnVectorMultiply.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <omp.h>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;


void ParallelMulty(int ** matrix, int * vector, int rows, int cols)
{
	double startTime, endtime;
	int * resVector = new int[rows];
	printf("Parallel: \n");
	printf("********************************************\n");
	printf("static: \n");
	startTime = omp_get_wtime();
#pragma omp parallel for schedule(static, rows/omp_get_num_threads())
	for (int i = 0; i < rows; i++)
	{
		resVector[i] = 0;
		for (int j = 0; j < cols; j++)
			resVector[i] += matrix[i][j] * vector[j];
	}
	endtime = omp_get_wtime();
	printf("static mode elapsed time = %f \n", (endtime - startTime) / (CLOCKS_PER_SEC / 1000));
	printf("-------------------------------------------\n");
	printf("dynamic:\n ");
	startTime = omp_get_wtime();
#pragma omp parallel for schedule(dynamic, rows/omp_get_num_threads())
	for (int i = 0; i < rows; i++)
	{
		resVector[i] = 0;
		for (int j = 0; j < cols; j++)
			resVector[i] += matrix[i][j] * vector[j];
	}
	endtime = omp_get_wtime();
	printf("dynamic mode elapsed time = %f \n", (endtime - startTime) / (CLOCKS_PER_SEC / 1000));
	printf("-------------------------------------------\n");

	printf("guided:\n ");
	startTime = omp_get_wtime();
#pragma omp parallel for schedule(guided, rows/omp_get_num_threads())
	for (int i = 0; i < rows; i++)
	{
		resVector[i] = 0;
		for (int j = 0; j < cols; j++)
			resVector[i] += matrix[i][j] * vector[j];
	}
	endtime = omp_get_wtime();
	printf("guided mode elapsed time = %f \n", (endtime - startTime) / (CLOCKS_PER_SEC / 1000));
	printf("-------------------------------------------\n");
	printf("runtime:\n ");
	startTime = omp_get_wtime();
#pragma omp parallel for schedule(runtime)
	for (int i = 0; i < rows; i++)
	{
		resVector[i] = 0;
		for (int j = 0; j < cols; j++)
			resVector[i] += matrix[i][j] * vector[j];
	}
	endtime = omp_get_wtime();
	printf("runtime mode elapsed time = %f \n", (endtime - startTime) / (CLOCKS_PER_SEC / 1000));
	printf("********************************************\n");
	delete[] resVector;
}

void NonParallelMulty(int ** matrix, int * vector, int rows, int cols)
{
	double startTime, endtime;
	int * resVector = new int[rows];
	startTime = omp_get_wtime();
	for (int i = 0; i < rows; i++)
	{
		resVector[i] = 0;
		for (int j = 0; j < cols; j++)
			resVector[i] += matrix[i][j] * vector[j];
	}
	endtime = omp_get_wtime();
	printf("Non-parallel mode elapsed time = %f \n", (endtime - startTime) / (CLOCKS_PER_SEC / 1000));
	delete[] resVector;
}

int main()
{
	int rows, cols;

	for (int i = 100; i < 200; i += 10)
	{
		rows = i;
		cols = i;
		int** matrix = new int*[rows];
		int* vector = new int[rows];
		for (int i = 0; i < rows; ++i)
			matrix[i] = new int[cols];
		printf("\nmatrix size = %i x %i\n", i,i);
		printf("vector size = %i\n", i);
		for (int j = 0; j < i; j++)
		{
			for (int k = 0; k < i; k++)
			{
				matrix[j][k] = rand() % 10 + 1;
			}
			vector[j] = rand() % 10 + 1;
		}

		ParallelMulty(matrix, vector, rows, cols);
		NonParallelMulty(matrix, vector, rows, cols);

		for (int i = 0; i < rows; ++i)
			delete[] matrix[i];
		delete[] matrix;
		delete[] vector;
	}
	//100x100 guided
	system("pause");
    return 0;
}

