#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

void thread_func() {
  int id = omp_get_thread_num();
  if(id < 2){
  	printf("first pair\n");
  }
  else if(id < 4){
  	printf("second pair\n");
  }
  else if(id < 6){
  	printf("third pair\n");
  }
  else if(id < 8){
  	printf("forth pair\n");
  }
  
}

int main(int argc, char** argv) {
	if(argc != 2){
	  	printf("Wrong number of arguments");
	  	return 0;
	  }
	int n = strtol(argv[1] , NULL , 10); 
#pragma omp parallel num_threads(n)
	{
		thread_func();
	}

	return 0;
}
