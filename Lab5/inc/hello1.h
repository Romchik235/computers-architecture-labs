#ifndef HELLO1_H
#define HELLO1_H

#include <linux/ktime.h>
#include <linux/list.h>

void print_hello(int count);

struct timestamp {
    ktime_t time;
    struct list_head list;
};

#endif
