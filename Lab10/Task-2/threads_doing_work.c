#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void do_some_work() {
  printf("Now I am going to do some work...\n");
  long int i;
  long int j = 0;
  double st = omp_get_wtime();
  for(i = 0; i < 3000000000; i++) {
    j += 3;
  }
  double en = omp_get_wtime();
  printf("Work done! My result j = %ld\n , took time %lf \n", j , en - st);
}

int main(int argc, char** argv) {
  if(argc != 2){
  	printf("Wrong number of arguments");
  	return 0;
  }
  int n = strtol(argv[1] , NULL , 10); 
  printf("number of threads %d\n",n);
#pragma omp parallel num_threads(n)
  {
    do_some_work();
  }

  return 0;
}
