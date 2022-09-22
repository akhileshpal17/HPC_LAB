#include <omp.h>
#include <stdio.h>
#include <pthread.h>
void main()
{
int N = 1000;
int A[1000];
for(int i=0;i<N;i++)A[i] = i + 1;
int S = 2;
double itime, ftime, exec_time;
itime = omp_get_wtime();
#pragma omp parallel for
for (int i = 0; i < N; i++)
{
A[i] *= S;
printf("Thread: %d Index: %d\n", omp_get_thread_num(),i);
}
for(int i=0;i<N;i++){
printf("%d ", A[i]);
}
ftime = omp_get_wtime();exec_time = ftime - itime;
printf("\nTime taken is %f\n", exec_time);
printf("\n");
}
