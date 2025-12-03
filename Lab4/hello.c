#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int count = 5;
module_param(count, int, 0660);
MODULE_PARM_DESC(count, "How many times to print Hello");

static int __init hello_init(void)
{
    pr_info("Hello, world in Linux Kernel Training count=%d\n", count);
    return 0;
}

static void __exit hello_exit(void)
{
    pr_info("Goodbye, kernel!\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Roman Dushko");
MODULE_DESCRIPTION("Simple test kernel module");
