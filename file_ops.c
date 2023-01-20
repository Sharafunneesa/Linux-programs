/********** FILE OPERATIONS DEMO MODULE ************/

#include<linux/kernel.h>     // printk function prototype
#include<linux/init.h>       // module_init & module_exit macro
#include<linux/module.h>     // MODULE_AUTHOR , MODULE_LICENSE, MODULE_DESCRIPTION 
#include <linux/fs.h>        // file operations

//function prototypes

int file_ops_open(struct inode *pinode, struct file *pfile);                                        //for open file
ssize_t file_ops_read(struct file *pfile, char __user *buffer,size_t length, loff_t *offset);       //for read file
ssize_t file_ops_write(struct file *pfile, const char __user *buffer,size_t length, loff_t *offset);//for write to file
int file_ops_close(struct inode *pinode, struct file *pfile);                                       //for closing the file
    
int file_ops_simple_module_init(void);                                                              //module initialization
void file_ops_simple_module_exit(void);                                                             //module closing

//initializing the major number
int dev = 232;                                   

// file operation structure
struct file_operations mem_ope =
{
       .owner  = THIS_MODULE,
       .open  = file_ops_open,
       .read  = file_ops_read,
       .write  = file_ops_write,
       .release = file_ops_close,
};


//This function will be called when we open the Device file    

int file_ops_open(struct inode *pinode, struct file *pfile)
{
    printk("open operation\n");
    return 0;
}

//This function will be called when we read from the Device file

ssize_t file_ops_read(struct file *pfile, char __user *buffer, size_t length, loff_t *offset)
{
    printk("read operations\n");
    return 0;
}

//This function will be called when we write to the Device file
    
ssize_t file_ops_write(struct file *pfile, const  char __user *buffer,size_t length, loff_t *offset)
{
     printk("write operations\n");
     return length;
}

// This function will be called when we close the Device file

int file_ops_close(struct inode *pinode, struct file *pfile)
{
     printk("close operation\n");
     return 0;
}

// module initfunction

int file_ops_simple_module_init(void)
{
     printk("initialization \n");
     register_chrdev(dev,"char_drive", &mem_ope); 
     return 0; 
}   

// module exit function

void file_ops_simple_module_exit(void)
{
     printk("exit function\n");
     unregister_chrdev(dev, "char_drive");
}

module_init(file_ops_simple_module_init);
module_exit(file_ops_simple_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("kernal");
MODULE_DESCRIPTION("simple demo fro file_operations");

     

   
