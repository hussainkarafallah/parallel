#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<omp.h>


int per_thread; 
int M , n_threads;
int *numbers;
int result = 0;

/*
500000 1deadwing@deadwing:~/Desktop/Parallel/Lab10/Task-6$ ./out 500000 1
thread 0 processed 500000 numbers and took total 36.688317 seconds
total primes :: 41538
deadwing@deadwing:~/Desktop/Parallel/Lab10/Task-6$ ./out 500000 2
thread 0 processed 250000 numbers and took total 18.514906 seconds
thread 1 processed 250000 numbers and took total 18.520829 seconds
total primes :: 41538
deadwing@deadwing:~/Desktop/Parallel/Lab10/Task-6$ ./out 500000 4
thread 1 processed 125000 numbers and took total 9.237201 seconds
thread 3 processed 125000 numbers and took total 9.299631 seconds
thread 0 processed 125000 numbers and took total 9.347820 seconds
thread 2 processed 125000 numbers and took total 9.499622 seconds
total primes :: 41538
*/

void shuffle(int *array, size_t n)
{
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

int is_prime(int x){
    if(x == 1) return 0;
    for(int j = 2 ; j < x ; j++) if(x % j == 0) return 0;
    return 1;
}

void the_thread_func() {
	double st = omp_get_wtime();
    int id = omp_get_thread_num();
    int l = id * per_thread;
    int r = (id + 1) * per_thread;
    if(r > M)
    	r = M;
    int primes = 0;
    for(int j = l ; j < r ; j++)
    	if(is_prime(numbers[j]))
    		++primes;
    		
#   pragma omp critical
	result += primes;
	
	double en = omp_get_wtime();
	printf("thread %d processed %d numbers and took total %lf seconds\n",id,r-l,en-st);
    
}

int main(int argc , char **argv){
	
	if(argc != 3){
		printf("wrong number of arguments");
		return 0;
	}
	
    M = strtol(argv[1] , NULL , 10);
    n_threads = strtol(argv[2] , NULL , 10); 
    per_thread = (M + n_threads - 1)/n_threads;
    
    numbers = (int*) malloc(M * sizeof(int));
    
    for(int j = 0 ; j < M ; j++)
    	numbers[j] = j + 1;
    	
    shuffle(numbers , M);
    
#	pragma omp parallel num_threads(n_threads)
	the_thread_func();
    
    
    printf("total primes :: %d\n" , result);

}


