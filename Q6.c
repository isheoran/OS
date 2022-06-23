#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

#define MAX 3

void *multiply(void* arg)
{
	int *data = (int *)arg;
	int k = 0, i = 0;
	
	int x = data[0];
	for (i = 1; i <= x; i++)
		k += data[i]*data[i+x];
	
	int *response = (int*)malloc(sizeof(int));
	*response = k;
	pthread_exit(response);
}

int main()
{
	int m1[MAX][MAX];
	int m2[MAX][MAX];
	int r1,c1;
    int r2,c2;
    printf("No. Of Rows in Matrix A: ");
    scanf(" %d",&r1);
    printf("No. Of Columns in Matrix A: ");
    scanf(" %d",&c1);
    printf("No. Of Rows in Matrix B: ");
    scanf(" %d",&r2);
    printf("No. Of Columns in Matrix B: ");
    scanf(" %d",&c2);
    if(c1!=r2){
        printf("Matrix Multiplication Not Defined for these matrices !");
        return 0;
    }
    
    int i,j,k;
    printf("Enter Matrix A (4x4):\n");
	for (i = 0; i < r1; i++)
			for (j = 0; j < c1; j++)
				scanf(" %d",&m1[i][j]);
    printf("Enter Matrix B (4x4):\n");
	for (i = 0; i < r2; i++)
			for (j = 0; j < c2; j++)
				scanf(" %d",&m2[i][j]);
	
    int max = r1*c2;
	pthread_t *threads = (pthread_t*)malloc(max*sizeof(pthread_t));
	
	int count = 0;
	int* data = NULL;
	for (i = 0; i < r1; i++){
        for (j = 0; j < c2; j++){
            data = (int *)malloc((c1+r2+1)*sizeof(int));
            data[0] = c1;
        
            for (k = 0; k < c1; k++)
                data[k+1] = m1[i][k];
        
            for (k = 0; k < r2; k++)
                data[k+c1+1] = m2[k][j];
                
            pthread_create(&threads[count++], NULL,multiply, (void*)(data));
        }
    }
		
	printf("\nResultant Matrix:\n");
	for (i = 0; i < max; i++)
	{
        void *response;
        pthread_join(threads[i], &response);
        printf("%d ",*((int*)response));
        if ((i+1)%c2 == 0){
            printf("\n");
        }
	}
    return 0;
}
