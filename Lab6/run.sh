#!/bin/bash

qemu-system-x86_64 \
    -kernel linux-stable/arch/x86/boot/bzImage \
    -initrd rootfs.cpio.gz \
    -append "console=ttyS0" \
    -nographic
