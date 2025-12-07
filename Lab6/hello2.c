#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/bug.h>
#include "hello1.h"

static unsigned int count = 1;
module_param(count, uint, 0644);

static int __init hello2_init(void)
{
    unsigned int i;
    int ret;

    pr_info("hello2 loaded, count=%u\n", count);

    BUG_ON(count > 10);

    for (i = 0; i < count; i++) {
        ret = print_hello();
        if (ret)
            return ret;
    }
    return 0;
}

static void __exit hello2_exit(void)
{
    pr_info("hello2 unloaded\n");
}

module_init(hello2_init);
module_exit(hello2_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Dushko Roman, variant 3206");
