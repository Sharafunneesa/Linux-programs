//Write a system programming your own version of cp command

//adding header files
#include<stdio.h> 
#include<unistd.h>
#include<errno.h>
#include<sys/stat.h>
#include <fcntl.h>

int main(int argc, char * argv[])
{
  //checking the commands if it is less pprinting the usage message
  if (argc < 3)
  {
    printf("give file name\n");
    return 0;
  }
  
  //declairing the variables
  int fs, fd, data;
  char buffer[100];
  
  //open source file in read mode
  fs = open(argv[1] ,O_RDONLY);
  
  //open destination file in write mode and checking it open or not 
  fd = open(argv[2] ,O_WRONLY | O_CREAT,0777);
  if(fs < 0)
  {
    perror("cannot open file");
    printf("errno:%d\n",errno);
    return -1;
  }
  
  //using read and write system call copy the content ofsource file into destination file
  while((data = read(fs,buffer,1))>0) 
  {
    write(fd,buffer,1);
  }
  
  //closing two files
  close(fs);
  close(fd);
}
