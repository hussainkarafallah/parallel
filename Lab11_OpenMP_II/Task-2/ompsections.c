#include <omp.h>
#include <stdio.h>

long int N = 500000000;

void funcA() {
  long int i;
  double x = 1.0;
  for(i = 0; i < N; i++)
    x *= 1.000000001;
  printf("funcA() executed by thread %d result: x = %f\n", omp_get_thread_num() , x);
}

void funcB() {
  long int i;
  double x = 1.0;
  for(i = 0; i < N; i++)
    x *= 1.000000002;
  printf("funcB() executed by thread %d result: x = %f\n", omp_get_thread_num() , x);
}

void funcC() {
  long int i;
  double x = 1.0;
  double st = omp_get_wtime();
  for(i = 0; i < N; i++)
    x *= 1.000000003;
  printf("funcC() executed by thread %d result: x = %f\n", omp_get_thread_num() , x);
}


int main(int argc, char *argv[]) {

#pragma omp parallel num_threads(3)
  {

#pragma omp sections
    {

#pragma omp section
      {
	funcA();
      }

#pragma omp section
      {
	funcB();
      }
#pragma omp section   
      {
        funcC();
      }

    } /* end of omp sections block */

  } /* end of omp parallel block */

  return 0;
}
