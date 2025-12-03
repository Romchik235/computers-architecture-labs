#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/ktime.h>

#include "../inc/hello1.h"

static LIST_HEAD(time_list);

void print_hello(int count)
{
    int i;
    struct timestamp *ts;

    if (count <= 0 || count > 10)
        pr_warn("hello1: count=%d unusual (0 or 5..10); continuing\n", count);

    for (i = 1; i <= count; i++) {
        ts = kmalloc(sizeof(*ts), GFP_KERNEL);
        if (!ts) {
            pr_err("hello1: memory allocation failed\n");
            return;
        }

        ts->time = ktime_get_ns();
        list_add_tail(&ts->list, &time_list);

        pr_info("Hello, world! (%d/%d)\n", i, count);
    }
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void)
{
    pr_info("hello1: loaded\n");
    return 0;
}

static void __exit hello1_exit(void)
{
    struct timestamp *ts, *tmp;

    pr_info("hello1: dumping timestamps and freeing list...\n");

    list_for_each_entry_safe(ts, tmp, &time_list, list) {
        pr_info("hello1: print duration: %llu ns\n",
               (unsigned long long)ts->time);
        kfree(ts);
    }

    pr_info("hello1: unloaded\n");
}

module_init(hello1_init);
module_exit(hello1_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Roman");
MODULE_DESCRIPTION("hello1: backend list + timing module");
