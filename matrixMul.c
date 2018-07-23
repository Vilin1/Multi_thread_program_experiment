#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define MAX 1000;

#define ROW  3
#define COLUMN  3
#define N  2

int A[ROW][N] = {{1, 4}, {2, 5}, {3, 6}};
int B[N][COLUMN] = {{8, 7, 6}, {5, 4, 3}};
int result[ROW][COLUMN];

struct v {
	int i;
	int j;
};

void *matrixMul(void *data);

int main() {
	printf("formula 1----->1\n");
	printf("rand matrix--->2\n");
	printf("$");
	int command;
	scanf("%d", &command);
	if(command == 1) {
       ;
	} else {
		//set matrix in random way
		srand(time(0));
		for(int i = 0; i < ROW; i++) {
			for(int j = 0; j < N; j++) {
				int num;
				num = rand()%MAX;
				A[i][j] = num;
			}
		}
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < COLUMN; j++) {
				int num;
				num = rand()%MAX;
				B[i][j] = num;
			}
		}
	}			

	//print origin matrix A B
	printf("Matrix A\n");
	for(int i = 0; i < ROW; i++) {
		for(int j = 0; j < N; j++) {
			printf("%d ", A[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	printf("Matrix B\n");
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < COLUMN; j++) {
			printf("%d ", B[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	//
	pthread_t tid[ROW][COLUMN];
	pthread_attr_t attr;
	//get default attr
	pthread_attr_init(&attr);

	/*
		create some thread to calculate the value
	*/
	for(int i = 0; i < ROW; i++) {
		for(int j = 0; j < COLUMN; j++) {
			struct v *data = (struct v*)malloc(sizeof(struct v));
			data->i = i;
			data->j = j;
			//create thread
			pthread_create(&tid[i][j], &attr, matrixMul, (void *)data);
		}
	}

	//wait every thead to finish
	for(int i = 0; i < ROW; i++) {
		for(int j = 0; j < COLUMN; j++) {
			pthread_join(tid[i][j], NULL);
		}
	}

	//output the result of A*B
	printf("A*B\n");
	for(int i = 0; i < ROW; i++) {
		for(int j = 0; j < COLUMN; j++) {
			printf("%d ", result[i][j]);
		}
		printf("\n");
	}

	return 0;
}

//function to calculate a element
void *matrixMul(void *data) {
	struct v *data1 = (struct v*)data;
	int sum = 0;
	for(int i = 0; i < N; i++) {
		sum += A[data1->i][i] * B[i][data1->j];
	}
	result[data1->i][data1->j] = sum;
}