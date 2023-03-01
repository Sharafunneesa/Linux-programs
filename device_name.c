//Write a program show the device name

//adding the header file we need
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/ioctl.h>
#include<linux/input.h>

int main(int argc, char *argv[])
{
   //declairing the variables
   int fd1;
   char name[256] ;
   
   //open the file 
   fd1 = open(argv[1],O_RDONLY);
   //checking the file is open or not
   if(fd1<2)
   {
       printf("Open Fails");
       return -1;
   }
   
   //using ioctl finding the name of the device and printing it
   ioctl(fd1,EVIOCGNAME(sizeof(name)),name);
   printf("Input device name:%s \n",name);
   return 0;
}
