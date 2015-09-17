#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include "buffer.h"

#define MAX_SLEEP 10

sem_t mutex;
sem_t full;
sem_t empty;


void *producer(int id) {
	buffer_item item;
	int sleepTime;

	while(1) {
		sleepTime = rand()%MAX_SLEEP;
		sleep(sleepTime);
		item = rand();

		sem_wait(&empty);
		sem_wait(&mutex);
		if(insert_item(item))
			printf("report error condition\n");
		else
			printf("producer %d : slept %d, prduced %d\n", id, sleepTime, item);
		printBuffer();
		sem_post(&mutex);
		sem_post(&full);
	}
}

void *consumer(int id) {
	buffer_item item;
	int sleepTime;

	while(1) {
		sleepTime = rand()%MAX_SLEEP;
		sleep(sleepTime);
		
		sem_wait(&full);
		sem_wait(&mutex);
		if(remove_item(&item))
			printf("reprot error condition\n");
		else
			printf("consumer %d : slept %d, consumed %d\n", id, sleepTime, item);
		printBuffer();
		sem_post(&mutex);
		sem_post(&empty);
	}
}

int main(int argc, char *argv[]) {
	int i;
	int sleepTime = atoi(argv[1]);
	int numOfP = atoi(argv[2]);
	int numOfC = atoi(argv[3]);
	pthread_t *pThread = (pthread_t*)malloc(numOfP);
	pthread_t *cThread = (pthread_t*)malloc(numOfC);

	sem_init(&mutex, 0, 1);
	sem_init(&full, 0, 0);
	sem_init(&empty, 0, BUFFER_SIZE);

	for(i=0; i<numOfP; i++)
		if(pthread_create(&pThread[i], NULL, producer, i) < 0) {
			perror("thread create error : ");
			exit(0);
		}

	for(i=0; i<numOfC; i++)
		if(pthread_create(&cThread[i], NULL, consumer, i) < 0) {
			perror("thread create error : ");
			exit(0);
		}

	sleep(sleepTime);
	return 0;
}
