//Write a system programming your own version of wc command

//adding header files
#include<stdio.h> 
#include<unistd.h>
#include<errno.h>
#include<sys/stat.h>
#include <fcntl.h>

int main(int argc, char * argv[])
{
  //checking command line arguments are less than 2 if it is printing the usage message
  if (argc < 2)
  {
    printf("give file name\n");
    return 0;
  }
  
  //declairing the variables
  int fd, i=0;
  int c_ch=0, c_word=0, c_line=0;
  char buffer[100],data;
  
  //open the file in read mode and cecking it open or not
  fd = open(argv[1] ,O_RDONLY);
  if(fd < 0)
  {
    perror("cannot open file");
    printf("errno:%d\n",errno);
    return -1;
  }
  
  //using while and read system call reading character by character from the file
  while((data=read(fd,buffer,1))>0) 
  {
     //for counting the character increment the counter
     c_ch++;
   
   //checking the character is space or new line  
   if(buffer[i] == ' ' || buffer[i] == '\n')
     //if it is increment the word counter    
     c_word++;
   
   //checking the character is new line or not
   if( buffer[i] == '\n')
     //if it is, incrementing the line counter
     c_line++;
  }
 
  //printing the wc command
  printf(" %d  %d %d %s\n",c_line,c_word,c_ch,argv[1]);
  
  //closing the file
  close(fd);

}

