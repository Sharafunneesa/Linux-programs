/********* CHARACTER DEVICE DRIVER FOR LED TURN ON AND TURN OFF ********************/

#include <linux/kernel.h>       //kernel
#include <linux/init.h>         //for module init and exit
#include <linux/module.h>       //module builds
#include <linux/kdev_t.h>       //definition of major number and minor number
#include <linux/fs.h>           // file operations
#include <linux/cdev.h>         //character device structure       
#include <linux/device.h>       //device information
#include <linux/delay.h>        // for using sleeping 
#include <linux/gpio.h>         // for using the GPIO
#include <linux/err.h>          //for pr_err error message


//LED is connected to this GPIO
#define GPIO_60 60
 
dev_t dev = 0;
static struct class *dev_class;
static struct cdev gpio_cdev;
 
static int __init gpio_driver_init(void);
static void __exit gpio_driver_exit(void);
 
 
/*************** Driver functions **********************/
static int gpio_open(struct inode *inode, struct file *file);
static int gpio_release(struct inode *inode, struct file *file);
static ssize_t gpio_read(struct file *filp,char __user *buf, size_t len,loff_t * off);
static ssize_t gpio_write(struct file *filp, const char *buf, size_t len, loff_t * off);

 
//File operation structure 
static struct file_operations fops =
{
  .owner          = THIS_MODULE,
  .read           = gpio_read,
  .write          = gpio_write,
  .open           = gpio_open,
  .release        = gpio_release,
};


//This function will be called when we open the Device file
static int gpio_open(struct inode *inode, struct file *file)
{
  pr_info("Device File Opened...!!!\n");
  return 0;
}

//This function will be called when we close the Device file
static int gpio_release(struct inode *inode, struct file *file)
{
  pr_info("Device File Closed...!!!\n");
  return 0;
}


//This function will be called when we read the Device file
static ssize_t gpio_read(struct file *filp,char __user *buf, size_t len, loff_t *off)
{
  
  int gpio_state = 0;
  gpio_state = gpio_get_value(GPIO_60);
  pr_info("Read function : GPIO_60 = %d \n", gpio_state);
  return 0;

}

// This function will be called when we write the Device file
static ssize_t gpio_write(struct file *filp,const char __user *buf, size_t len, loff_t *off)
{
	int i;
	for(i = 0;i<10;i++)
	{ 
               gpio_set_value(GPIO_60, 1);
	       msleep(2000);
               gpio_set_value(GPIO_60, 0);
	       msleep(2000);
	}
  
        return len;
}

// Module Init function 
static int __init gpio_driver_init(void)
{
  
  /*Allocating Major number*/
  if((alloc_chrdev_region(&dev, 0, 1, "gpio_Dev")) <0)
  {
    pr_err("Cannot allocate major number\n");
  }
  pr_info("Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));
 
  
  /*Creating cdev structure*/
  cdev_init(&gpio_cdev,&fops);
 
  /*Adding character device to the system*/
  if((cdev_add(&gpio_cdev,dev,1)) < 0)
  {
    pr_err("Cannot add the device to the system\n");
  }
 
  /*Creating struct class*/
  if(IS_ERR(dev_class = class_create(THIS_MODULE,"gpio_class")))
  {
    pr_err("Cannot create the struct class\n");
  }
 
  /*Creating device*/
  if(IS_ERR(device_create(dev_class,NULL,dev,NULL,"gpio_device")))
  {
    pr_err( "Cannot create the Device \n");
  }

 
  //Checking the GPIO is valid or not
  if(gpio_is_valid(GPIO_60) == false)
  {
    pr_err("GPIO %d is not valid\n", GPIO_60);
  }

  //Requesting the GPIO
  if(gpio_request(GPIO_60,"GPIO_60") < 0)
  {
    pr_err("ERROR: GPIO %d request\n", GPIO_60);
  }
  
  //configure the GPIO as output
  gpio_direction_output(GPIO_60, 0);
  
  pr_info("Device Driver Insert...Done!!!\n");
  return 0;
}

// Module exit function
static void __exit gpio_driver_exit(void)
{
  gpio_free(GPIO_60);
  device_destroy(dev_class,dev);
  class_destroy(dev_class);
  cdev_del(&gpio_cdev);
  unregister_chrdev_region(dev, 1);
  pr_info("Device Driver Remove...Done!!\n");
}
 
module_init(gpio_driver_init);
module_exit(gpio_driver_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("SHARAFUNNEESA PT");
MODULE_DESCRIPTION("A simple device driver - GPIO Driver");



