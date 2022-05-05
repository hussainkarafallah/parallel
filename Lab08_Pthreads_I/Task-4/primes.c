#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<stdbool.h>

struct Range{
    int start , end , answer;
};

int is_prime(int x){
    if(x == 1) return 0;
    for(int j = 2 ; j < x ; j++) if(x % j == 0) return 0;
    return 1;
}
void* the_thread_func(void* arg) {
    struct Range* range = (struct Range*)(arg);
    range->answer = 0;
    int ret = 0;
    for(int i = range->start ; i <= range->end ; i++){
        range->answer += is_prime(i);
    }
    return NULL;
}

int main(){
    pthread_t thread1 , thread2;
    struct Range range1;
    struct Range range2;
    
    range1.start = 1;
    range1.end = 5;
    range2.start = 6;
    range2.end = 10;
    
    pthread_create(&thread1, NULL, the_thread_func, &range1);
    pthread_create(&thread2, NULL, the_thread_func, &range2);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("%d\n",range1.answer + range2.answer);

}


