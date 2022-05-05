#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>


static double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}

long int N1;
long int N2;

void* the_thread_func(void* arg) {
  long int i;
  long int sum = 0;
  for(i = 0; i < N2; i++)
    sum += 7;
  /* OK, now we have computed sum. Now copy the result to the location given by arg. */
  long int * resultPtr;
  resultPtr = (long int *)arg;
  *resultPtr = sum;
  return NULL;
}

void execute(int n1 , int n2){
  N1 = n1;
  N2 = n2;

  long int thread_result_value = 0;
  /* Start thread. */
  pthread_t thread;
  //printf("the main() function now calling pthread_create().\n");
  pthread_create(&thread, NULL, the_thread_func, &thread_result_value);

  //printf("This is the main() function after pthread_create()\n");
  
  double st = get_wall_seconds();
  
  long int i;
  long int sum = 0;
  for(i = 0; i < N1; i++)
    sum += 7;

  /* Wait for thread to finish. */
  //printf("the main() function now calling pthread_join().\n");
  pthread_join(thread, NULL);

  printf("sum computed by main() : %ld\n", sum);
  printf("sum computed by thread : %ld\n", thread_result_value);
  long int totalSum = sum + thread_result_value;
  printf("totalSum : %ld\n", totalSum);
  double en = get_wall_seconds();
  
  printf("time elapsed :: %lf \n",en - st);
  
}
int main() {
	printf("This is the main() function starting.\n");
	execute(100000000 , 700000000);
	execute(200000000 , 600000000);
	execute(300000000 , 500000000);
	execute(400000000 , 400000000);



  return 0;
}
