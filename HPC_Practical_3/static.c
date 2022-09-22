#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define CHUNK 500

void static_fun(){

int a[1000];
  int b[1000];
  int c[1000];
 
  double time = omp_get_wtime();
  
  #pragma omp parallel 
  {
    #pragma omp for nowait
    for(int i=0;i<1000;i++)
      a[i] = i;
    
    #pragma omp for nowait
    for(int i=0;i<1000;i++)
      b[i] = i+1;
  }
  int threads;
  #pragma omp parallel for num_threads(4) schedule(static,CHUNK)
  for(int i=0;i<1000;i++) {
    c[i] = a[i] + b[i];
    threads = omp_get_num_threads();
  }
  
  
  for(int i=0;i<1000;i++)
    printf("%d ",c[i]);
    

  printf("\n Using %d no of threads with chunk size=%d and execution time=%f\n",threads,CHUNK,omp_get_wtime() - time);
}



int main() {
    static_fun();
  return(0);
  
}