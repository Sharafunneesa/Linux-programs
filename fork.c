//understanding about fork system call

//adding header files
#include<stdio.h>
#include<unistd.h>

int main()
{  
  //calling fork system call
  printf("fork process\n");
  fork();
  
  //printing the process id and parent process id
  printf("pid =%d, ppid =%d\n",getpid(),getppid());
  printf("terminated\n");
}
