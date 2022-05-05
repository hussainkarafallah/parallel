#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<stdbool.h>

void* the_thread_func(void* arg) {
    int *idx = (int*)(arg);
    printf("thread number %d is running\n" , *idx);
    return NULL;
}

int main(){
    int n;
    scanf("%d",&n);
    pthread_t* threads = (pthread_t*) malloc(sizeof(pthread_t) * n);
    for(int j = 0 ; j < n ; j++){
        int *idx = (int*) malloc(sizeof(int));
        *idx = j;
        pthread_create(&threads[j], NULL, the_thread_func, idx);
    }
    for(int j = 0 ; j < n ; j++)
        pthread_join(threads[j], NULL);
}