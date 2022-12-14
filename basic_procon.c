/* program to check the producer consumer */
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

// function declaration
void *producer();
void *consumer();

// variable declaration
int counter = 0;
char buffer[5];

//drive code
int main()
{
	//pthread declaration
	pthread_t pro,con;

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

	// Joining the thread
	if(pthread_join(pro, NULL)!=0)
	{
		perror("Thread failed to join\n");
		exit(EXIT_FAILURE);
	}

	// Joining the thread
	if(pthread_join(con, NULL)!=0)
	{
		perror("Thread failed to join\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

// function for producr to produce
void *producer()
{
	// declaring an variable
	int i = 0;
	char c = 'Z';

	// infinite while loop
	while(1)
	{
		//checking the counter is 5 or not
		while(counter == 5);

		//putting the character into buffer
		buffer[i] = c;
		i = (i + 1) % 5;

		//checking the i value if it 0 then printing the whole buffer 
		//and reassignning the value of c
		if (i == 0)
		{
			c = 'Z';
			printf("Producer : %s\n", buffer);
		}

		//if it not 0 then decreasing the character by 1
		else
		{
			c--;
		}

		//incriment the counter value by one
		counter++;
	}
	pthread_exit("exit");
}

//function for consumer consumes 
void *consumer()
{   

    // declaring an variable 
    int i = 0;
    char data[5];
    
    //taking while loop for infinite
    while(1)
    {
        //taking the character from the buffer 
        while(counter == 0);
        data[i] = buffer[i];
        i = (i+1) % 5;
        if (i == 0)
        {
            printf("Consumer : %s\n",data);
        }
        counter--;
    }
    
    //exit the thread
    pthread_exit("exit");
}


