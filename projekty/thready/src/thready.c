/*
 ============================================================================
 Name        : thready.c
 Author      : szymon
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t lock;


void *numChars(void *arg){
	pthread_mutex_lock(&lock);
	const char *helloMsg = arg;
	printf("%s\n",helloMsg);
	int *length = malloc(sizeof(*length));
	int sum=0;
	while(helloMsg[sum]!='\0')
		sum++;
	*length = sum;
	pthread_mutex_unlock(&lock);
	pthread_exit(length);
}

int main(int argc, char **argv){
	pthread_mutex_init(&lock, NULL);
	pthread_t tids[argc-1];
	for(int i=1;i<argc;i++){
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tids[i],&attr, numChars, argv[i]);
	}

	for(int i=1;i<argc;i++){
		int *result;
		pthread_join(tids[i], (void**)&result);
		printf("%d: len: %d\n",i+1 ,*result);
		free(result);
	}
	pthread_mutex_destroy(&lock);
	return 0;
}
