#include <stdio.h> 
#include <unistd.h>
#include <pthread.h> 
#include <stdlib.h> 

struct Inp {
	int ** matrix1; 
	int ** matrix2; 
	int ** ans; 
	int r1,c1,r2, c2; 
};

void * multiply(void * rawData) {
	struct Inp *data = ((struct Inp *) rawData); 
	// dynamically allocate space  
	data->ans = (int **)(malloc(sizeof(int *)*data->r1)); 
	for(int i =0; i < (data->r1); ++i) {
		data->ans[i] = (int *) (malloc(sizeof(int)*(data->c2))); 
	}
	// func to multiply 
	for(int i=0;i<(data->r1);i++) {
              for(int j=0;j<(data->c2);j++) {
                   int res = 0;
                   for(int k=0;k<(data->c1);k++){
                      res += (data->matrix1[i][k])*(data->matrix2[k][j]);
                  }
                  data->ans[i][j] = res;
             }
         }
	// return the pointer
	return((void *)(data)); 
	// pthread_exit(data);
}

int main() {
	int r1=2, c1=2, r2=2, c2=2; 
	printf("Enter the row and col of the first matrix ::: "); 
	scanf("%d %d", &r1, &c1);
	printf("Enter the row and col of the second matrix ::: "); 
	scanf("%d %d", &r2, &c2); 
	struct Inp * Inp_p = (struct Inp *) (malloc(sizeof(struct Inp))); 

	if(r2 != c1) {
		exit(-1); 
	}

	Inp_p->r1 = r1; 
	Inp_p->r2 = r2; 
	Inp_p->c1 = c1; 
	Inp_p->c2 = c2; 

	// first matrix created 
	Inp_p->matrix1 = (int **) (malloc(sizeof(int *)*r1)); 
	for(int i = 0; i < r1; ++i) {
		Inp_p->matrix1[i] = (int *) (malloc(sizeof(int)*c1)); 
	}

	// similarly 
	Inp_p->matrix2 = (int **) (malloc(sizeof(int *)*r2)); 
	for(int i = 0; i < r2; ++i) {
		Inp_p->matrix2[i] = (int *) (malloc(sizeof(int)*c2)); 
	}
	
	// // memory allocation completed 
	printf("enter the values of the first matrix ::: "); 
	for(int i = 0; i < r1; ++i){
		for(int j = 0; j < c1; ++j) 
			scanf("%d", &(Inp_p->matrix1[i][j])); 
	}
	printf("enter the values of the second matrix ::: "); 
	for(int i = 0; i < r2; ++i){
		for(int j = 0; j < c2; ++j) 
			scanf("%d", &(Inp_p->matrix2[i][j])); 
	}
	pthread_t thread; 
	pthread_create(&thread, NULL, multiply, (void *)(Inp_p)); 
 	void * received = NULL; 
	pthread_join(thread, (void *)&received); 
	
	// print the answer 
	for(int i = 0; i < Inp_p->r1; ++i) {
		for(int j = 0; j < Inp_p->c2; ++j) {
			printf("%d ", ((struct Inp *)received)->ans[i][j]); 
		}
		printf("\n"); 
	}
	printf("END OF PROGRAM"); 
}