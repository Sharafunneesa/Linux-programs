//Write a system programming your own version of tail command

//adding all requires header files
#include<stdio.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>

//driving code
int main(int argc,char *argv[])
{
    int fd,i=0,j=0,n,choice;
    char ch,**p=NULL,*buff=NULL;
    
    //file open in read mode
    fd=open(argv[1],O_RDONLY);
    //if file is not present then it will throw error
    if(fd<0)
    {
        perror("Error:");
        return -1;
    }
    
    //reading one character from file
    while((read(fd,&ch,1))>0)
    {   
        //allocating memory to store one line
        buff=realloc(buff,i+1);
        
        //assigning one character to buffer
        buff[i++]=ch;
        if(ch=='\n')
        {   
            buff=realloc(buff,i+1);
            buff[i++]='\0';
            
            //creating array of pointer to store the one line address
            p=realloc(p,(j+1)*sizeof(p));
            
            //making buff NULL to store another line
            p[j++]=buff;
            //free(buff);
            buff=NULL;
            i=0;
        }
    }
    
    //if lines are less than or equal to 10 then it will print all line
    if(j>=1 && j<=10)
               {
                for(int k=0;k<j;k++)
                    printf("%s",p[k]);
               }
              
               //if line is more than or equal to 10 then it will print 10 lines from the down
               else if(j>10)
               {
                   n=j-10;
                for(int k=n;k<j;k++)
                    printf("%s",p[k]);
               }
               
               //for no line in file
               else
                   printf("file is empty\n");
}
