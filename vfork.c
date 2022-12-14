/* vfork means parent id and child id is same and after termination of child parent active*/

// for input and output file
#include<stdio.h>
// standard lib function
#include<stdlib.h>
//for Linux access
#include<unistd.h>
// for pid
#include<sys/types.h>



int main()
{
        //creating the child process
    pid_t pid = vfork();  



   //printf("parent process pid before if...else block: %d\n", getpid());
        // Condition to check the child process ID
    if (pid == 0)
    {  
        printf("Child process and pid is: %d\n", getpid());
        exit(0);
    }
     
    // Condition to check the parent process ID
    else if (pid > 0)
    {
        printf("Parent process and pid is: %d\n", getpid());
    }
     
    else
    {
        printf("Error while forking\n");
        exit(EXIT_FAILURE);
        
    }
    return 0;
}


