ifneq ($(KERNELRELEASE),)
obj-m := hello1.o hello2.o
ccflags-y += -g -O0 -fno-omit-frame-pointer -fno-inline
ccflags-y += -I$(src)/inc
else
KDIR ?= /lib/modules/$(shell uname -r)/build
default:
        $(MAKE) -C $(KDIR) M=$$PWD
clean:
        $(MAKE) -C $(KDIR) M=$$PWD clean
endif
