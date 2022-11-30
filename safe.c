//implement a thread safe function

// adding header files 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

//variable declaration
int number = 0, odd_sum=0, even_sum=0,max,rc;


//declairing mutex
pthread_mutex_t mutex; 


//function for finding the sum of odd and even numbers
void * odd_even_sum()
{ 
  
  //locking the thread
  pthread_mutex_lock(&mutex);
  
  
  //loop for finding the sum of odd and even numbers
  for(; number <= max; number++)
  {
     if(number % 2 != 0)
     {
          odd_sum = odd_sum + number;
     }
     else 
     {
          even_sum = even_sum+ number;
     }
   }
  
  
  //unlocking the thread
  pthread_mutex_unlock(&mutex); 
}
 
//drive code 
int main()
{ 

  //taking the limit from user
  printf("give the maximum range :");
  scanf("%d",&max);
  
  
  //declairing the thread variables
  pthread_t odd;
  pthread_t even; 
  
  //initiolizing the mutex variable
  pthread_mutex_init(&mutex);
  
  //creating two threads and calling the function
  pthread_create(&odd,NULL,&odd_even_sum,NULL);
  pthread_create(&even,NULL,&odd_even_sum,NULL);
          
          
  //join will block the state of the thread 
  if(pthread_join(odd,NULL) !=0 )
       return 2;
  
 
  //join will block the state of the thread
  if(pthread_join(even,NULL) !=0 )
       return 3; 
       
 
 //printing the sum of odd and even numbers 
 printf("sum of even numbers = %d\n",even_sum);
 printf("sum of odd numbers = %d\n",odd_sum);
 
 
 //destroying the mutex
 pthread_mutex_destroy(&mutex);   
}

  

