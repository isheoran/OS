#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define N 2
#define size(x) (sizeof(x)/sizeof(int)) 
int arr[N] = {-1}; 
int curr = -1; 
sem_t mutex;

void Producer() {
    // wait for production
    sem_wait(&mutex); 
    while(curr != N-1) {
        ++curr; 
        arr[curr] =rand()%10;
        sleep(1);  
        printf("Producer produced %d \n", arr[curr]); 
    }
    // signal consumption
    sem_post(&mutex);  
}

void Consumer() {
    sem_wait(&mutex); 
    while(curr != -1) {
        sleep(1); 
        printf("Consumer consumed %d \n", arr[curr]); 
        arr[curr] = -1; 
        --curr; 
    }
    sem_post(&mutex); 
}

void * runner(void * inp) {
    while(1) {
        Producer(); 
        Consumer(); 
    }
}

int main() {
    sem_init(&mutex, 0, 1); 
    pthread_t th; 
    pthread_create(&th, NULL, runner, NULL); 
    pthread_join(th , NULL); 
    return 0; 
}
