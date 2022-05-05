#include <stdio.h>
#include <pthread.h>

void* the_thread_func(void* arg) {
  /* Do something here? */
  for(int i = 0 ; i < 30 ; i+=3)
  		printf("%d\n",i);
  return NULL;
}

void* the_thread_func2(void* arg) {
  for(int i = 1 ; i < 30 ; i+=3)
  		printf("%d\n",i);
  return NULL;
}

int main() {
  printf("This is the main() function starting.\n");

  /* Start thread. */
  pthread_t thread , thread2;
  printf("the main() function now calling pthread_create().\n");
  pthread_create(&thread, NULL, the_thread_func, NULL);
  pthread_create(&thread2, NULL, the_thread_func2, NULL);
  printf("This is the main() function after pthread_create()\n");
	
  /* Do something here? */
  for(int i = 2 ; i < 30 ; i+=3)
  	printf("%d\n",i);
  /* Wait for thread to finish. */
  printf("the main() function now calling pthread_join().\n");
  
  pthread_join(thread, NULL);
  pthread_join(thread2, NULL);

  return 0;
}
