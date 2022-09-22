#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#include<bits/stdc++.h>
using namespace std;


 int main(){
 	long long sum = 0;

 	double getInTime = omp_get_wtime();

 	#pragma omp parallel for reduction(+ : sum)

 	for(int i=1;i<=100000000;i++){
 		sum += (i*i);
	 }

 	double getOutTime = omp_get_wtime();

 	double exptTime = getOutTime - getInTime;


 	printf("Time Required For Execution in Parallel : %f\n",exptTime);

 	printf("Answer is : %lld",sum);

 	return 0;

 }
