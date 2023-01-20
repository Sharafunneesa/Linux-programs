#include <linux/module.h>    // MODULE_AUTHOR , MODULE_LICENSE, MODULE_DESCRIPTION 
#include <linux/init.h>      // module_init & module_exit macro
#include <linux/kernel.h>    // printk function prototype
int add (int , int );        // function declaration

MODULE_AUTHOR("Kernel Masters");
MODULE_DESCRIPTION("Hello Module");
MODULE_LICENSE("GPL2");

/* adding function */
int add (int x, int y)
{
	printk ("This is add function\n");
	return x+y;
}

EXPORT_SYMBOL(add);

/* module init function */
static int avg_init(void)
{
	printk ("This is a avg_init function:\n avg result:%d \n",add(10,20)/2);
	return 0;
}

/* module exit function */
static void avg_exit(void)
{
	printk ("This is a avg_exit function\n");
}

module_init(avg_init);
module_exit(avg_exit);


