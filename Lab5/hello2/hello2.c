#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include "../inc/hello1.h"

// ---- Параметри Модуля ----

static int count = 1;
module_param(count, int, 0660);
MODULE_PARM_DESC(count, "How many times to call print_hello()");

// -------------------

static int __init hello2_init(void)
{
    pr_info("hello2: init, count=%d\n", count);
    print_hello(count);
    return 0;
}

static void __exit hello2_exit(void)
{
    pr_info("hello2: exit\n");
}

module_init(hello2_init);
module_exit(hello2_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Roman");
MODULE_DESCRIPTION("hello2: frontend calling hello1::print_hello()");
