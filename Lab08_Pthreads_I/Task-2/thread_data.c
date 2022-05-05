#include <stdio.h>
#include <pthread.h>

void* the_thread_func(void* arg) {
  /* Do something here? */
  double *arr = (double*)(arg);
  for(int i = 0 ; i < 3 ; i++)
  	printf("%lf\n",arr[i]);
}

int main() {
  printf("This is the main() function starting.\n");

  double data_for_thread[3];
  data_for_thread[0] = 5.7;
  data_for_thread[1] = 9.2;
  data_for_thread[2] = 1.6;
	
  double data_for_thread2[3];
  data_for_thread2[0] = 1.7;
  data_for_thread2[1] = 2.2;
  data_for_thread2[2] = 3.6;
  /* Start thread. */
  pthread_t thread , thread2;
  printf("the main() function now calling pthread_create().\n");
  pthread_create(&thread, NULL, the_thread_func, data_for_thread);
  pthread_create(&thread2, NULL, the_thread_func, data_for_thread2);
  printf("This is the main() function after pthread_create()\n");

  /* Do something here? */

  /* Wait for thread to finish. */
  printf("the main() function now calling pthread_join().\n");
  pthread_join(thread, NULL);
  pthread_join(thread2, NULL);

  return 0;
}
