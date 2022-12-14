/* program to check the producer consumer problem using with semaphore */

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>

// function declaration
void * producer();
void * consumer();
// variable declaration
int count = 0, limit=0;
char buffer[5];

//declairing the mutex
//pthread_mutex_t mutex; 
sem_t full, empty;

int main()
{
	pthread_t pro,con;
	sem_init(&full,0,0);
	sem_init(&empty,0,5);

	// first thread creation(producer)
	if(pthread_create(&pro,NULL,&producer,NULL) !=0)
	{
		perror("Thread failed to create\n");
		exit(EXIT_FAILURE);
	}

	// second thread creation(consumer)
	if(pthread_create(&con,NULL,&consumer,NULL) !=0)
	{
		perror("Thread failed to create\n");
		exit(EXIT_FAILURE);
	}



	// Joining the thread producer
	if(pthread_join(pro, NULL)!=0)
	{
		perror("Thread failed to join\n");
		exit(EXIT_FAILURE);
	}



	// Joining the thread consumer
	if(pthread_join(con, NULL)!=0)
	{
		perror("Thread failed to join\n");
		exit(EXIT_FAILURE);
	}



	exit(EXIT_SUCCESS);
}

// function for producer to produce
void *producer()
{
	// declaring an variable
	int i = 0;
	char c = 'Z';

	// infinite while loop
	while(1)
	{
		//waiting for buffer empty
		sem_wait(&empty);

		//producing the character
		while(count == 5);
		buffer[i] = c;
		i = (i + 1) % 5;
		if (i == 0)
		{
			c = 'Z';
			printf("Producer : %s\n", buffer);
		}

		else
		{
			c--;
		}
		count++;

		//waiting for buffer full
		sem_post(&full);
	}
	pthread_exit("exit");
}

//function for consumer to consume
void *consumer()
{
	//declairing the variables
	int i = 0,limit1 =0;
	char data[5];

	while(1)
	{
		//witing upto buffer is full
		sem_wait(&full);

		//consuming the buffer character
		while(count == 0);
		data[i] = buffer[i];
		i = (i+1) % 5;
		if (i == 0)
		{
			printf("Consumer : %s\n",data);
		}
		count--;

		//waiting upto buffer is empty
		sem_post(&empty);
	}
	pthread_exit("exit");
}

