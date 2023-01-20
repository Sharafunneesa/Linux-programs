/********** ALLOCATING MAJOR NUMBER (DYANAMICALLY) *********/

#include<linux/kernel.h>               //kernel
#include<linux/init.h>                 //for module init nad exit 
#include<linux/module.h>               //module builds
#include<linux/kdev_t.h>               //definition of major number and minor number
#include<linux/fs.h>                   //file operations
 
dev_t dev = 0;                         //initializing the variable with zero


// Module Init function

static int __init hello_world_init(void)
{

        //Allocating Major number
        if((alloc_chrdev_region(&dev, 0, 1, "your_Dev")) <0)
        {
                printk(KERN_INFO "Cannot allocate major number for device 1\n");
                return -1;
        }
        
        //printing the messages
        printk(KERN_INFO "Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));
        printk(KERN_INFO "Kernel Module Inserted Successfully...\n");
        
        return 0;
}

// Module exit function

static void __exit hello_world_exit(void)
{

        //reallocating the major number
        unregister_chrdev_region(dev, 1);
       
        printk(KERN_INFO "Kernel Module Removed Successfully...\n");
}
 
module_init(hello_world_init);
module_exit(hello_world_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("kernal");
MODULE_DESCRIPTION("Simple linux driver (Dynamically allocating the Major and Minor number)");




