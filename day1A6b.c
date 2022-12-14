/*Write a system programming your own version of du command */

#include<stdio.h> //for input and output
#include<unistd.h> //for lseek
#include<fcntl.h> //for rdonly
#include<string.h> // for string
#include<errno.h> //for perror


//drive code
int main(int argc,char *argv[])
{
        //declairing the variables
	int fd , size=0, i;
	
	//taking the for loop for checking all the file given in argument
	for(i =1;i < argc;i++)
	{
	        //checking the file open or not and print the error message
		fd = open(argv[i],O_RDONLY);
		if(fd < 0)
		{
			perror("cannot open file");
			printf("errno:%d\n",errno);
			return -1;
		}
		
		//calculating the size useeing lseek
		size = lseek(fd,0,SEEK_END);
		
		//take back the pointer at starting point
		lseek(fd,0,SEEK_SET);
		
		//printing the du command 
		printf("%d\t%s\n",size,argv[i]);

	}
}
