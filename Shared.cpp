#include "stdafx.h"
#include <omp.h>
#include <iostream>
#include <ctime>
using namespace std;


void task10()
{
	const int N = 6;
	const int M = 8;

	int d[N][M];
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j)
			d[i][j] = (rand() + time(0)) % 100;

	int max = d[0][0],
		min = d[0][0];
	//cout << "max = " << max << endl << "min = " << min << endl;
	omp_set_num_threads(N);

#pragma omp parallel shared(max,min)
	{
		int loc_max = max;
		int loc_min = min;
#pragma omp for
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				int element = d[i][j];
				if (element > loc_max) {
					loc_max = element;
				}
				if (element < loc_min) {
					loc_min = element;
				}

			}
		}
#pragma omp critical
		{
			if (max < loc_max) {
				max = loc_max;
			}
			if (min > loc_min) {
				min = loc_min;
			}
		}
	}

	cout << "d: " << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			cout << d[i][j] << ' ';
		cout << endl;
	}
	cout << "max = " << max << endl << "min = " << min << endl;

}


void task11()
{
	const int N = 30;
	int a[N];

	for (int i = 0; i < N; ++i)
		a[i] = (rand() + time(0)) % 10 + 1;
	//        
	//     for (int i = 0; i < N; ++i)
	//         cout << a[i] % 9 << " ";
	//     cout << endl;

	cout << " array: ";
	for (int i = 0; i < N; ++i)
		cout << a[i] << ' ';
	cout << endl;

	int count = 0;
#pragma omp parallel for 
	for (int i = 0; i < N; ++i)
	{

		if (a[i] % 9 == 0)
		{
#pragma omp atomic
			++count;
		}
	}

	cout << " count =" << count << endl;
}


void task12()
{
	const int N = 30;
	int a[N];

	for (int i = 0; i < N; ++i)
		a[i] = (rand() + time(0)) % 100 + 1;

	cout << " array: ";
	for (int i = 0; i < N; ++i)
		cout << a[i] << ' ';
	cout << endl;

	int max = a[0],
		count = 0;

#pragma omp parallel for num_threads(4) shared(max)
	for (int i = 0; i < N; ++i)
	{
		if (a[i] > max)
			if (a[i] % 7 == 0)
			{
#pragma omp critical 
				{
					if (a[i] > max)
						max = a[i];
				}
			}
	}

	cout << " max =" << max << endl;
}


void task13()
{
	int i, n;
//#pragma omp parallel private(i,n) 
	//{
		//n = omp_get_thread_num();
#pragma omp for ordered
		for (int i = omp_get_num_threads(); i >=0; --i)
		{
			//printf("Thread %d, iter %d\n", n, i);
#pragma omp ordered
			{
				//printf("ordered: thread %d, iter %d\n", n, i);
				printf("Hello World\n thread id: %i\n ", omp_get_thread_num());
			}
		}
	//}
}
int main()
{
	printf("\n 10. \n");
	task10();
	//printf("\n 11. \n");
	//task11();
	//printf("\n 12. \n");
	//task12();
	//printf("\n 13. \n");
	//task13();
//#pragma omp parallel num_threads(8)
//	{
//		printf("Hello World\n thread id: %i\n total: %i\n", omp_get_thread_num(), omp_get_num_threads());
//	}
//#pragma omp parallel num_threads(4)
//	{
//		printf("Hello World\n thread id: %i\n ", omp_get_thread_num());
//
//	}
	system("pause");
}