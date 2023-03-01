//Write an Linux System Programming copy one file content to another file using mmap() system call.

//including the header files we need
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{ 
     //condition to check whether the required argument are passed or not
     if(argc<3)
     {
     printf("ERROR:Less argument passed\n");
     return 0;
     }
    
    //declairing the variables
    int fs, fd, size;
    char *sour, *dest;
    struct stat s;   
   
     //SOURSE:- open file, find the size of the file and mapping the file
     fs= open(argv[1], O_RDONLY);
     size = lseek(fs,0,SEEK_END);
     sour = mmap(NULL, 1, PROT_READ, MAP_PRIVATE, fs, 0);
     
     //DESTINATION:- create file, creating a memory to the dest file, open the file amd last mapping the file
     fd = creat(argv[2], 0777);
     ftruncate(fd, size+1);
     fd = open(argv[2], O_RDWR | O_CREAT ,0777);
     dest = mmap(NULL, 1, PROT_READ | PROT_WRITE, MAP_SHARED,fd, 0);
    
    //using for loop copy the content of the source file into destination file
    for(int i = 0; i<size; i++)
    {
        //write(fd,&sour[i], 1);
        dest[i] = sour[i];
    }
    printf("the content of the source file copied into destination file\n");
    
    //after copying the file unmap the files
    munmap(sour, s.st_size);
    munmap(dest, s.st_size);
  
    // close two files
    close(fs);
    close(fd);
    return 0;
}


