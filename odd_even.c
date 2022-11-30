//WAP create two threads using pthreads and print even no and odd no alternatively.

// adding header files 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

//variable declaration
int number = 0;

//taking one function to find out the odd numbers
void * odd_number()
{ 
  while(number <= 20)
  {
     if(number % 2 != 0)
     {
        printf(" thread1 :%d\n",number);
        number++;
        sleep(1);
     }
  }
  
}
 
//taking another function to find out the even numbers 
void * even_number()
{ 
  while(number <=20)
  {
     if(number % 2 == 0)
     {
        printf(" thread2 :%d\n",number);
        number++;
        sleep(1);    
    }
    }
}
  
//driving code
int main()
{
  //taking two thread variables
  pthread_t odd;
  pthread_t even; 
  
  //creating one thread and checking it will create or not
  if(pthread_create(&odd,NULL,&odd_number,NULL) !=0 )
       return 0;
  
  //creating another thread and checking it will create or not 
  if(pthread_create(&even,NULL,&even_number,NULL) !=0 )
       return 1;
  
  //join will block the state of the thread
  if(pthread_join(odd,NULL) !=0 )
       return 2;
  
  //join will block the state of the thread
  if(pthread_join(even,NULL) !=0 )
       return 3;
  
  printf("\n");
  return 4;
}






