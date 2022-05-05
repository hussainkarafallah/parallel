#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<stdbool.h>
#include <sys/time.h>
/*
100000 1
9592
Time elapsed :: 1.324515
100000 2
9592
Time elapsed :: 0.960778
100000 4
9592
Time elapsed :: 0.560989
100000 8
9594
Time elapsed :: 0.397742
*/

static double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}

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
    int m , n;
    scanf("%d %d",&m,&n);
    int per_range = (m + n - 1)/n;

    pthread_t* threads = (pthread_t*) malloc(sizeof(pthread_t) * n);
    struct Range* ranges = (struct Range*) malloc(sizeof(struct Range) * n);
    for(int j = 0 ; j < n ; j++){
        ranges[j].start = 1 + per_range * j;
        ranges[j].end = 1 + per_range * (j+1);
        if(ranges[j].end > m)
            ranges[j].end = m;
        if(ranges[j].start > m)
            ranges[j].start = ranges[j].end = 0;
    }

    double st = get_wall_seconds();
    int answer = 0;
    for(int j = 0 ; j < n ; j++){
        pthread_create(&threads[j], NULL, the_thread_func, &ranges[j]);
    }
    for(int j = 0 ; j < n ; j++)
        pthread_join(threads[j], NULL);

    for(int j = 0 ; j < n ; j++)
        answer += ranges[j].answer;
   
    printf("%d\n",answer);

    double en = get_wall_seconds();

    printf("Time elapsed :: %lf" , en - st);

}


