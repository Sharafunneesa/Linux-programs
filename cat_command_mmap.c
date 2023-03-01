// WAP our own version of cat command using mmap system call

//adding header files we need
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include<sys/stat.h>

int main(int argc, char* argv[]) 
{
  // condition to check whether the required argument are passed or not
  if(argc < 2)
  {
    printf("given the file name yo want to map\n");
    return 0;
  }
  
  //declairing the variables
  int fd;
  char * region;
  struct stat s;
 
  //open the file and checking its open or not 
  fd = open(argv[1], O_RDONLY);
  if(fd < 0)
  {
    printf(" file open fails\n");
    return -1;
  }
   
  //using fstat finding the size of the file   
  fstat(fd,&s);
  
  //mapping the content of the file  
  region = mmap(0,s.st_size,PROT_READ,MAP_SHARED,fd, 0);
  
  //using for loop printing content of the file
  for(int i = 0;i<s.st_size;i++)
  {
	  printf("%c",region[i]);
  }
  
  //after printing unmaping the file
  munmap(region,s.st_size);
  
  //close the file
  close(fd);
  return 0;
}
