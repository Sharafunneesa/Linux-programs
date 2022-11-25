//Write a program to read framebuffer fixed size information

//adding the header files we need
#include<stdio.h>
#include<fcntl.h>
#include<linux/input.h>
#include<sys/ioctl.h>
#include<linux/fb.h>

int main(int argc, char *argv[])
{
    //declairing the variables
    int fd;
    struct fb_var_screeninfo varInfo;
    
    //open the file and checking its open or not
    fd = open (argv[1], O_RDONLY);
    if(fd < 3)
    {
        printf("Open Fails");
        return -1;
    }
    
    //using ioctl system call getting the informations containing the structure fb_var_screeninfo
    ioctl(fd, FBIOGET_VSCREENINFO,&varInfo);
    
    //printing the informations
    printf("visiable x res %u\n", varInfo.xres);
    printf("visiable y res %u\n", varInfo.yres);
    printf("bits per pixel %u\n", varInfo.bits_per_pixel);
    
    return 0;
}


