/********** ALLOCATING MAJOR NUMBER (STATICALLY) *********/

#include<linux/kernel.h>                 //kernel
#include<linux/init.h>                   //init and exit function
#include<linux/module.h>                 //module building
#include <linux/fs.h>                    //file operations


//creating the dev with our custom major and minor number
dev_t dev = MKDEV(235, 0);


// Module Init function
static int __init hello_world_init(void)
{
    //allocating major number
    register_chrdev_region(dev, 1, "innominds_dev");
    
    //printing the message
    printk(KERN_INFO "Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));
    printk(KERN_INFO "Kernel Module Inserted Successfully...\n");
    return 0;
}


//Module exit function

static void __exit hello_world_exit(void)
{ 
    //reallocating major and minor number
    unregister_chrdev_region(dev, 1);
    
    printk(KERN_INFO "Kernel Module Removed Successfully...\n");
}
 
module_init(hello_world_init);
module_exit(hello_world_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("kernal Master");
MODULE_DESCRIPTION("Simple linux driver (Statically allocating the Major and Minor number)");



