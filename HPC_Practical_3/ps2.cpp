#include<iostream>
#include<stdio.h>
#include<omp.h>

using namespace std;

int main()
{
	int size=0;
	printf("Size of matrix\n");
	scanf("%d", &size);
	// omp_set_num_threads(10);
	int* matrix = new int[size*size];
	int* vector = new int[size];
	int* result = new int[size];
	#pragma omp run for num_thread(2)
	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
			*(matrix+i*size+j) = 2;
	}
	#pragma omp run for num_threads(4)
	for(int i=0; i<size; i++)
	{
		*(vector+i)= 3;
	}
	int temp=0,threads;
	double time = omp_get_wtime();
	#pragma omp parallel for num_threads(8)
	for(int i=0; i<size; i++)
	{

		for(int j=0; j<size; j++)
		{
			temp=0;
			for(int k=0; k<size; k++)
			{
				temp += *(matrix+j*size+k) * *(vector+k);
			}
		}
			threads = omp_get_num_threads();
		*(result+i) = temp;
	}

	// for(int i=0; i<size; i++)
	// {
	// 	printf(" %d ", result[i]);
	// }

	printf("\nExecuted when size = %d and threads =%d \nDone in %f seconds\n", size,threads, omp_get_wtime()-time);
	return 0;
}
