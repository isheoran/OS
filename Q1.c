#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t baseID = getpid();
    printf("Base Id: %d\n",baseID);
    int lev = 1;
    for (int i = 0; i < 4; i++) {
        pid_t newFork = fork();
        if (newFork == 0) {
            pid_t parentID = getppid();
            pid_t processID = getpid();
            if (parentID == baseID) {
                lev = 1;
            }
            else lev++;
            printf("Process ID: %d, Parent ID: %d, level: %d \n", processID, parentID, lev);
        }
        else if(newFork>0){
            wait(NULL);
        }
        else{
            printf("! ! FORK ERROR ! !");
        }
    }
    return 0;
}