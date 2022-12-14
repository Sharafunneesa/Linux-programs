/* program to check the producer consumer problem using with semaphore and mutex */

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>

// function declaration
void * producer1();
void * producer2();
void * consumer();
// variable declaration
int count = 0, limit=0;
char buffer[5];

//declairing the mutex
pthread_mutex_t mutex1,mutex2; 
sem_t full, empty;

int main()
{
	//declairing the semaphore
	pthread_t pro1,pro2,con;
	sem_init(&full,0,0);
	sem_init(&empty,0,5);

	// first thread creation(producer1)
	if(pthread_create(&pro1,NULL,&producer1,NULL) !=0)
	{
		perror("Thread failed to create\n");
		exit(EXIT_FAILURE);
	}

	// first thread creation(producer2)
	if(pthread_create(&pro2,NULL,&producer2,NULL) !=0)
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
	if(pthread_join(pro1, NULL)!=0)
	{
		perror("Thread failed to join\n");
		exit(EXIT_FAILURE);
	}

	// Joining the thread producer
	if(pthread_join(pro2, NULL)!=0)
	{
		perror("Thread failed to join\n");
		exit(EXIT_FAILURE);
	}


	//Joining the thread consumer
	if(pthread_join(con, NULL)!=0)
	{
		perror("Thread failed to join\n");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}

// function for producer to produce
void *producer1()
{
	// declaring an variable
	int i = 0;
	char c = 'Z';

	// infinite while loop
	while(1)
	{
		//waiting for buffer is free
		sem_wait(&empty);

		//using mutex locking the thread
		pthread_mutex_lock(&mutex1);

		//assgining the character to buffer 
		while(count == 5);
		buffer[i] = c;
		i = (i + 1) % 5;
		if (i == 0)
		{
			c = 'Z';
			printf("Producer 1 : %s\n", buffer);
		}

		else
		{
			c--;
		}
		count++;

		//unlocking the thread
		pthread_mutex_unlock(&mutex1);

		//waiting for bufferfull
		sem_post(&full);
	}

	pthread_exit("exit");
}


// function for producer to produce
void *producer2()
{
	// declaring an variable
	int i = 0;
	char c = 'A';


	// infinite while loop
	while(1)
	{
		//waiting for buffer is empty
		sem_wait(&empty);

		//using mutex locking the thread
		pthread_mutex_lock(&mutex1);

		//assgining the character to buffer
		while(count == 5);
		buffer[i] = c;
		i = (i + 1) % 5;
		if (i == 0)
		{
			c = 'A';
			printf("Producer 2 : %s\n", buffer);
		}

		else
		{
			c++;
		}
		count++;

		//unlocking the tread
		pthread_mutex_unlock(&mutex1);

		//waiting for buffer is full
		sem_post(&full);
	}

	pthread_exit("exit");
}

//function for consumer to consume
void *consumer()
{
	//declairing the variables
	int i = 0;
	char data[5];

	while(1)
	{
		//waiting for the buffer is full
		sem_wait(&full);

		//locking the tread
		pthread_mutex_lock(&mutex2);

		//consuming the character from the buffer
		while(count == 0);
		data[i] = buffer[i];
		i = (i+1) % 5;
		if (i == 0)
		{
			printf("Consumer : %s\n",data);
		}
		count--;
		//unlocking the thread
		pthread_mutex_unlock(&mutex2);

		//wait for next empty
		sem_post(&empty);
	}
	pthread_exit("exit");
}



