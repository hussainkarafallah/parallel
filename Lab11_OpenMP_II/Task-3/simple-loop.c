#include <omp.h>
#include <stdio.h>

/*
deadwing@deadwing:~/Desktop/Parallel/Lab11_OpenMP_II/Task-3$ time ./out
sum = 19999.749173

real	0m3.240s
user	0m3.240s
sys	0m0.000s
deadwing@deadwing:~/Desktop/Parallel/Lab11_OpenMP_II/Task-3$ gcc simple-loop.c -fopenmp -o out
deadwing@deadwing:~/Desktop/Parallel/Lab11_OpenMP_II/Task-3$ time ./out
sum = 19999.749173

real	0m1.083s
user	0m3.246s
sys	0m0.000s
*/

long int N = 5000000;

double f(int q) {
  long int i;
  double x = 1.0;
  for(i = 0; i < N; i++)
    x *= 1.000000001;
  return x * q;
}

int main(int argc, char *argv[]) {
  const int M = 200;
  double arr[M];
  int i;
  
#pragma omp parallel for num_threads(3)
  for(i = 0; i < M; i++)
		arr[i] = f(i);

  /* Sum up results. */
  double sum = 0;
  int k;
  for(k = 0; k < M; k++)
    sum += arr[k];

  printf("sum = %f\n", sum);

  return 0;
}
