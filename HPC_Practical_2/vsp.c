#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
	int n=4;
	int vector[n],scalar,result[n],i;
	for(i=0;i<n;i++)
	{
		vector[i] = i+1;
	}
	
	scalar=10;
	
	#pragma omp parallel for firstprivate(vector,scalar) num_threads(3)
	for(i=0;i<n;i++)
	{
		result[i] = vector[i] + scalar;
		printf("Thread %d working on section %d\n", omp_get_thread_num(), i);

	}
	
	printf("i\ta[i]\t+\t%d\t=\tc[i]\n",scalar);
    for(i=0; i<n; i++) {
		printf("%d\t%d\t\t%d\t\t%d\n", i, vector[i], scalar, result[i]);
    }
	return 0;
}
