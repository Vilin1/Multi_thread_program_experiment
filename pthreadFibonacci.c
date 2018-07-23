#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

//the data shared
long fibo[MAX_SIZE] = {0};

//function run in thread
void *fibonacci(void *length);

int main(int argc, char *argv[]) {
	//input the size of fibonacci
	int length = 0;
	if(argc != 2) {
		fprintf(stderr, "usage:./a.out <interger value>\n");
		return -1;
	}
	if(atoi(argv[1]) < 0) {
		fprintf(stderr, "%d must be <= 0\n", atoi(argv[1]));
		return -1;
	}	
	//case out of range
	length = atoi(argv[1]);
	if(length > 100) {
		fprintf(stderr, "The size out of range\n");
		return -1;
	}

	//new thread
	pthread_t tid;
	pthread_attr_t attr;
	//get default attr
	pthread_attr_init(&attr);
	//create thread
	pthread_create(&tid, &attr, fibonacci, (void *)&length);
	//wait for the thread to exit
	pthread_join(tid, NULL);

	for(int i = 0; i < length; i++) {
		printf("%ld ", fibo[i]);
	}
	printf("\n");

	return 0;
}

void *fibonacci(void *length) {
	int *size = (int*)length;
	if(*size == 1) {
		fibo[0] = 0;
	} else if(*size == 2) {
		fibo[0] = 0;
		fibo[1] = 1;
	} else {
		fibo[0] = 0;
		fibo[1] = 1;
		for(int i = 2; i < *size; i++) {
			fibo[i] = fibo[i-1] + fibo[i-2];
		}
	}
}