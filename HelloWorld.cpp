// HelloWorld.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <omp.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <stdio.h>
#include <dos.h>
using namespace std;

//I.2
void CheckNumThreads(int val)
{
	

	#pragma omp parallel num_threads(3) if(val>2) 
	if (omp_in_parallel())
	{
		printf("thread id: %i \n total: %i\n", omp_get_thread_num(), omp_get_num_threads());	
	}
	else
	{
		#pragma omp parallel num_threads(1)
		{
			printf("single\n");
			printf("thread id: %i \n total: %i\n", omp_get_thread_num(), omp_get_num_threads());
		}
	}
}


void PrintReverse1()// 1�� ������
{
#pragma omp parallel 
	{
		int n = omp_get_thread_num();


		if (n == 3)
		{
			printf("Hello World\n thread id: %i\n total: %i\n", omp_get_thread_num(), omp_get_num_threads());
		}
#pragma omp barrier

		if (n == 2)
		{
			printf("Hello World\n thread id: %i\n total: %i\n", omp_get_thread_num(), omp_get_num_threads());
		}
#pragma omp barrier
		if (n == 1)
		{
			printf("Hello World\n thread id: %i\n total: %i\n", omp_get_thread_num(), omp_get_num_threads());
		}
#pragma omp barrier
		if (n == 0)
		{
			printf("Hello World\n thread id: %i\n total: %i\n", omp_get_thread_num(), omp_get_num_threads());
		}
#pragma omp barrier

	}

}

void PrintReverse2() // 2�� ������
{
#pragma omp parallel
	{
		int n = omp_get_thread_num();
		switch (n)
		{
		case 3:
			printf("Hello World\n thread id: %i\n total: %i\n", omp_get_thread_num(), omp_get_num_threads());
			break;
		case 2:
			_sleep(100);
			printf("Hello World\n thread id: %i\n total: %i\n", omp_get_thread_num(), omp_get_num_threads());
			break;
		case 1:
			_sleep(200);
			printf("Hello World\n thread id: %i\n total: %i\n", omp_get_thread_num(), omp_get_num_threads());
			break;
		case 0:
			_sleep(300);
			printf("Hello World\n thread id: %i\n total: %i\n", omp_get_thread_num(), omp_get_num_threads());
			break;
		}
	}
}

void first()
{
	#pragma omp parallel num_threads(8)
	{
		printf("Hello World\n thread id: %i\n total: %i\n", omp_get_thread_num(), omp_get_num_threads());
	}
}

void third()
{
	int b = 1;
	int a = 1;

	printf("before parallel:\na = %i,\nb = %i\n", a, b);
	#pragma omp parallel private(a) firstprivate(b) num_threads(2)
	{
		int a = 1;
		printf("in parallel, thread: %i\na = %i,\nb = %i\n", omp_get_thread_num(), a, b);
		a = a + omp_get_thread_num();
		b = b + omp_get_thread_num();
		printf("a + #thread = %i,\nb + #thread = %i\n", a, b);
	}
	printf("after parallel:\na = %i,\n b = %i\n", a, b);
	
	int c, d;
	c = d = 10;

	printf("before parallel:\na = %i,\nb = %i\n", a, b);
	#pragma omp parallel shared(c) private(d) num_threads(4)
	{
		d = 10;
		printf("in parallel, thread: %i\na = %i,\nb = %i\n", omp_get_thread_num(), c, d);
		c = c - omp_get_thread_num();
		d = d - omp_get_thread_num();
		printf("a - number_of_thread = %i,\nb - number_of_thread = %i\n", c, d);
	}
	printf("after parallel:\na = %i,\n b = %i\n", c, d);
}

int main()
{
	/// I.1
	
	first();
	
	
	/// I.2 test
	
	//CheckNumThreads(1);
	//CheckNumThreads(2);
	//CheckNumThreads(3);


	/// I.3
	//third();

	/// 13
	PrintReverse1();
	PrintReverse2();

	getchar();
	system("pause");
    return 0;
}

