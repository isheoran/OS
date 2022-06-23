#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

long long fib[100];

void *thread_fibonacci(void *arg) {
    long n = (long)arg;

    fib[0] = 0;
    fib[1] = 1;

    for(int i=2;i<n;i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }
}

int main(int argc, char ** argv) {
    if(argc == 1) {
        printf("No input provided !!\n");
        return 0;
    }

    long n = atoi(argv[1]);

    if(n<=0) {
        printf("Non-positive number entered in command line !!\n");
        return 0;
    }

    pthread_t thread_id;

    pthread_create(&thread_id, NULL, thread_fibonacci, (void *)n);
    pthread_join(thread_id,NULL);

    printf("Fibonacci sequence upto %ld : \n\n",n);

    for(int i=0;i<n;i++) {
        printf("%lld ",fib[i]);
    }

    printf("\n\n");
    
    return 0;
}