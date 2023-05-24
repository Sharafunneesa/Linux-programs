//Write a system programming your own version of echo command

//declairing all header files
#include<stdio.h>
#include<unistd.h>
#include<string.h>

int main(int argc ,char *argv[])
{ 
    int i;
    
    // taking for loop to check the arguments given and write it in moniter
    for(i=1;i<argc;i++)
    {
       write(1,argv[i], strlen(argv[i]));
       // if space is there print space also
       write(1," ",1); 
    }
    //printf("\n");
    write(1,"\n",1); 
}
