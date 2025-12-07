include <linux/module.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include <linux/slab.h>
#include <linux/kernel.h>
#include "hello1.h"

static LIST_HEAD(event_head);

int print_hello(void)
{
    static int call_counter = 0;
    struct event *e;
    ktime_t start, end;

    call_counter++;

    e = kmalloc(sizeof(*e), GFP_KERNEL);
    if (!e) {
        pr_err("hello1: kmalloc failed!\n");
        return -ENOMEM;
    }

    if (call_counter == 5) {
        pr_warn("hello1: simulated kmalloc() failure on call 5\n");
        kfree(e);
        e = NULL;
    }

    start = ktime_get();
    pr_info("Hello, world!\n");
    end = ktime_get();

    e->start_time = start;
    e->end_time = end;

    list_add_tail(&e->list, &event_head);
    return 0;
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void)
{
    pr_info("hello1 loaded\n");
    return 0;
}

static void __exit hello1_exit(void)
{
    struct event *e, *tmp;

    pr_info("hello1 unloading...\n");
    list_for_each_entry_safe(e, tmp, &event_head, list) {
        pr_info("Print time: %lld ns\n",
            ktime_to_ns(ktime_sub(e->end_time, e->start_time)));
        list_del(&e->list);
        kfree(e);
    }
}

module_init(hello1_init);
module_exit(hello1_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Dushko Roman, variant 3206");
                                                   
