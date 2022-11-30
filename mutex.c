// WAP create two threads using pthreads and print even no and odd no alternatively using mutex.

//adding header files
#include<stdio.h>
#include<pthread.h>
#include <stdlib.h>
#include <unistd.h>


//variable declaration
int number = 0, rc, max;


//declairing the mutex
pthread_mutex_t mutex; 


//declairing the functions
void* even_number();
void* odd_number();


//driving code
void main()
{   

    //takingthe limits from user
    printf("given the maximum value:");
    scanf("%d",&max);
    
    //declairing two thread variables
    pthread_t odd;
    pthread_t even;
   
    //creating threads
    pthread_create(&odd,0,&odd_number,0);
    pthread_create(&even,0,&even_number,0);
    sleep(1);

    //join will block the state of the thread
    pthread_join(odd,NULL);
    pthread_join(even,NULL);
}

//function for printing even numbers using second thread
void* even_number()
{
    //using mutex locked the thread
    pthread_mutex_lock(&mutex);
    
     while(number<= max)
     {
       if(number %2 == 0)
       {
         printf("thread1 :%d\n",number);
         number++;
       }
       else 
          // if the number is not even then unlocking the thread 
          pthread_mutex_unlock(&mutex);
       
    }
}

//function for printing the odd numbers using first thread
void* odd_number()
{
    //locking the thread for safe
    pthread_mutex_lock(&mutex);
    
    while(number <= max)
    {
       if(number % 2 != 0)
       {
          printf("thread2 :%d\n",number);
          number++;
       } 
       else 
       {
          //if the number is not odd unlocking the thread 
          pthread_mutex_unlock(&mutex);
       }
    } 
}










