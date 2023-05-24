//Write a system programming your own version of getchar() standard C Library

//adding header files
#include<stdio.h> 
#include<unistd.h>
#include<sys/stat.h>
#include <fcntl.h>

int main() 
{
  //declairing the variables
  int fd;
  char buffer[100];
  
  //reding the content from keyboard
  fd = read(0,buffer,100);
  
  //printing the content in moniter 
  fd = write(0,buffer,1);
  printf("\n");
  return 0;
}


