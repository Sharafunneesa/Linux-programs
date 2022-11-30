//Write a system programming your own version of touch command

//adding header files
#include<stdio.h> 
#include<unistd.h>
#include<errno.h>
#include<sys/stat.h>
#include <fcntl.h>

int main(int argc, char * argv[])
{
  //checking the comand line argument is less than 2. if it is leaa than 2 passing the usage message
  if (argc < 2)
  {
    printf("give file name\n");
    return 0;
  }
  
  //declairing the variables
  int fs, i;
  
  //taking for loop two count the given arguments
  for(i=0; i< argc ; i++)
  {
  
    //opening the files using open system call and checking it open or not
    fs = open(argv[i] ,O_CREAT);
    if(fs < 0)
    {
       perror("cannot open file");
       printf("errno:%d\n",errno);
       return -1;
    }
  }
  //printing the message
  printf("created empty files\n");
}
