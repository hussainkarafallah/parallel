#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<stdbool.h>
#include <sys/time.h>

void* second_level(void* arg){
    printf("second level thread\n");
}

void* first_level(void* arg) {
    printf("first level thread started\n");
    pthread_t thread1 , thread2;
    pthread_create(&thread1, NULL, second_level, NULL);
    pthread_create(&thread2, NULL, second_level, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("first level thread ended\n");

    return NULL;
}

int main(){
    printf("main thread started\n");
    pthread_t thread1 , thread2;
    pthread_create(&thread1, NULL, first_level, NULL);
    pthread_create(&thread2, NULL, first_level, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("main thread ended\n");
}