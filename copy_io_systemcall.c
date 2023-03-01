//Write a C program that makes a copy of a file using standard I/O and system calls. Explain the Difference between System Call and Standard Library.

//adding header files
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{

  //variable declaration
  FILE *fd, *fs;
  char  c;
  
  //opening the source file and checking is it open or not
  fs = fopen(argv[1], "r");
	if (fs <0 )
	{
	   printf("Cannot open file %s \n", argv[1]);
	   exit(0);
	}

  //open the destination file and checking it openor not
  fd = fopen(argv[2], "w");
	if (fd <0)
	{
	   printf("Cannot open file %s \n", argv[2]);
	   exit(0);
	}
	
	//using while loop taking the charcter from source file using fgetc and putting to des file using fputc
	while ((c = fgetc(fs))!=-1)
	{
		fputc(c, fd);
	
	}
        
        //closing the files
	printf("the content of %s is copied to %s\n", argv[1], argv[2]);
        fclose(fs);
	fclose(fd);
	return 0;
}

