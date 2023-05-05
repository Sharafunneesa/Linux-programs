/********** USER LEVEL PROGRAM FOR LCD USING I2C WITH BBB **********/



#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#define I2C_BUS "/dev/i2c-2"  // I2C bus device node
#define LCD_ADDR 0x27         // I2C address of the LCD driver

int fd;                       // I2C file descriptor



void lcd_command(unsigned char cmd) 
{
    unsigned char buf[2];
    buf[0] = 0x00;  // command mode
    buf[1] = cmd;
    if (write(fd, buf, 2) != 2) 
    {
        perror("Error writing to I2C device");
        exit(EXIT_FAILURE);
    }
    usleep(1000);  // wait for command to complete
}

void lcd_write(unsigned char data) 
{
    unsigned char buf[2];
    buf[0] = 0x40;  // data mode
    buf[1] = data;
    if (write(fd, buf, 2) != 2) 
    {
        perror("Error writing to I2C device");
        exit(EXIT_FAILURE);
    }
    usleep(1000);  // wait for write to complete
}

void lcd_init() 
{
    // initialize LCD in 4-bit mode
    lcd_command(0x33);
    lcd_command(0x32);
    lcd_command(0x28);
    lcd_command(0x0C);
    lcd_command(0x06);
    lcd_command(0x01);
}

void lcd_clear() 
{
    lcd_command(0x01);
}

void lcd_puts(const char *s) 
{
    while (*s) 
    {
        lcd_write(*s++);
    }
}

int main() 
{
    char data[] = {0};
    // open I2C bus device node
    if ((fd = open(I2C_BUS, O_RDWR)) < 0) 
    {
        perror("Error opening I2C device");
        exit(EXIT_FAILURE);
    }

    // set I2C slave address of the LCD driver
    if (ioctl(fd, I2C_SLAVE, LCD_ADDR) < 0) 
    {
        perror("Error setting I2C slave address");
        exit(EXIT_FAILURE);
    }

    // initialize LCD
    lcd_init();

    // test LCD display
    lcd_clear();
    
    printf(" Enther the data to print in LCD Display :");
    scanf("%s",data);
    lcd_puts(data);

    // close I2C bus device node
    close(fd);

    return 0;
}

