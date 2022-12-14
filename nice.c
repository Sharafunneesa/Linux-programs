/* nice command */

//including all header files
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

//driving code
int main(int argc , char*argv[])
{

        //checking the command line argument.and printing the usage message
        if(argc <=1)
        {
          printf("give the process id and nice value\n");
          return 1;
        }
        
        //declairing the variables
        int id, priority,ret,nice;
        
        //taking process id from the user
        id = atoi(argv[1]);
        
        //taking nice value from the user
        nice= atoi(argv[2]);
	
	//using getpriority getting the previos priority of the process
	priority = getpriority(PRIO_PROCESS, id);
	printf("priority:%d\n", priority);
	
	
	//setting the new prioity value
	ret = setpriority(PRIO_PROCESS, id,nice);
	
	//checking the priority is et or not
	if (ret == 0)
	{
		printf("priority is set\n");
		
		//if it set then printing the new priority value
		priority = getpriority(PRIO_PROCESS, id);
	        printf("new priority is :%d\n",priority);
	}
	else 
	{
		printf("not set\n");
	}
	
	
}
