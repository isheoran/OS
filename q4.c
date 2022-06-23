#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

void Collatz(int n) {
    
    printf("%d ",n);

    if(n==1) {
        return;
    }

    if(n%2==0) {
        Collatz(n/2);
    }
    else {
        Collatz(3*n+1);
    }
}

int main(int argc, char ** argv) {

    if(argc==1) {
        printf("No Arguments passed in command line\n");
        return 0;
    }

    int n = atoi(argv[1]);

    if(n<=0) {
        printf("Non-positive integer passed.\n");
        return 0;
    }

    pid_t newFork = fork();

    if(newFork == 0) {
        printf("Inside Child Process\n\n");
        Collatz(n);
        printf("\n\n");
    }
    else if(newFork > 0) {
        printf("Parent Process waiting...\n\n");
        wait(NULL);
        printf("Parent Process Exiting\n");
    }
    else {
        printf("! ! FORK ERROR ! ! \n");
    }

    return 0;
}