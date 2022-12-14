//example for zombi process and orphan process

//adding header files
#include<stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

//declairing the two functions zombi and orphan process
void zombi_process();
void orphan_process();

//driving code
int main()
{

//calling zomb function
 printf("zombi process\n");
 zombi_process();
 
 //take 5 second deleay
 sleep(5);
 
 //calling orphan process
 printf("after sleep call orphan process\n");
 printf("orphan process\n");
 orphan_process();
}


//definition of zombi process
void zombi_process()
{
        //exicuting the parent process for five second 
	int child_pid = fork();
	if (child_pid > 0)
		sleep(5);

	else	
	       //exit the child process without give any updation to parent	
		exit(0);

	
}


//definition of orphan process
void orphan_process()
{
       //calling fork system call 
       int pid = fork();
	
	
	//exicuting the child process for 5 second
	if(pid == 0)
	{
		printf("I am the child, my process ID is %d\n",getpid());
		sleep(5);
		printf("\nAfter sleep\nI am the child, my process ID is %d\n",getpid());
               exit(0);
	}
	
	//exicuting the parent process for 2 second and exit
	else
	{
		sleep(2);
		printf("I am the parent, my process ID is %d\n",getpid());
           	printf("Parent terminates\n");
	}
}


