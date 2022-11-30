//Write a system programming your own version of cat command

//adding header files
#include<stdio.h> 
#include<unistd.h>
#include<errno.h>
#include<sys/stat.h>
#include <fcntl.h>

int main(int argc, char * argv[])
{
  //checking the coomand line arguments if it less printing the usage message
  if (argc < 2)
  {
    printf("give file name\n");
    return 0;
  }
  
  //declairing the variables
  int fd, data;
  char  buffer[100];
  
  //open the file in read only mode and checking its open or not
  fd = open(argv[1] ,O_RDONLY);
  if(fd < 0)
  {
    perror("cannot open file");
    printf("errno:%d\n",errno);
    return -1;
  }
  
  //using read system call reading the content of the given file and printing
  while((data=read(fd,buffer,sizeof(buffer)))>0) 
  {
     printf("%s",buffer);
     write(1,&buffer,sizeof(buffer));
  }
  
  //closing the file
  close(fd);
}
