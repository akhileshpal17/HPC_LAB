#include<omp.h>
#include<stdio.h>
#include<stdlib.h>


int main()
{
	int n=10;
	int vector1[n],vector2[n],result[n],i;
	
	for(i=0;i<n;i++)
	{
		vector1[i] = i + 1;
		vector2[i] = i +2;
	}
	
	#pragma omp parallel for firstprivate(vector1,vector2) shared(result) num_threads(3)
	for(i=0;i<n;i++)
	{
		result[i] = vector1[i] + vector2[i];
		printf("Thread %d working on section %d\n", omp_get_thread_num(), i);
	}
	
	printf("i\ta[i]\t+\tb\t=\tc[i]\n");
    for(i=0; i<n; i++) {
		printf("%d\t%d\t\t%d\t\t%d\n", i, vector1[i], vector2[i], result[i]);
    }
	return 0;
}