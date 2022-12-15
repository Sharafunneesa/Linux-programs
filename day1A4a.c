//Write a system programming your own version of tail command

#include<stdio.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{
    int fd,i=0,j=0,n,choice;
    char ch,**p=NULL,*buff=NULL;
    fd=open(argv[1],O_RDONLY);
    if(fd<0)
    {
        perror("Error:");
        return -1;
    }

    while((read(fd,&ch,1))>0)
    {
        buff=realloc(buff,i+1);
        buff[i++]=ch;
        if(ch=='\n')
        {
            buff=realloc(buff,i+1);
            buff[i++]='\0';
            p=realloc(p,(j+1)*sizeof(p));
            p[j++]=buff;
            //free(buff);
            buff=NULL;
            i=0;
        }
    }
    if(j>=1 && j<=10)
               {
                for(int k=0;k<j;k++)
                    printf("%s",p[k]);
               }
               else if(j>10)
               {
                   n=j-10;
                for(int k=n;k<j;k++)
                    printf("%s",p[k]);
               }
               else
                   printf("file is empty\n");
}
