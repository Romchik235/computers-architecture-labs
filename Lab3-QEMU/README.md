#### Лабораторна робота № 3  
## Розгортання мінімальної Linux-системи у QEMU (BusyBox + Kernel)

---

## Опис проєкту

У межах лабораторної роботи було побудовано мінімальну операційну систему Linux, яка складається з:

- зібраного з нуля ядра Linux;
- статично зібраного BusyBox;
- власноруч сформованої кореневої файлової системи (rootfs);
- кастомного `init`-процесу;
- запуску готової системи у емуляторі **QEMU**.

В результаті запуску формується повноцінне середовище BusyBox, яке стартує у QEMU та дозволяє взаємодіяти з системою через консоль.

---

## Використані інструменти

- **Ubuntu 24.04 (VirtualBox)**
- **Linux Kernel 6.1.3 - 6.2.7 (компіляція вручну)**
- **BusyBox (static build)**
- **QEMU-system-x86_64**
- `cpio`, `gzip`, `make`, `gcc`

---

## Структура репозиторію

├── busybox/ # вихідні коди та конфіг BusyBox
├── linux-stable/ # зібране ядро Linux + .config
├── rootfs/ # коренева файлова система
│ ├── bin/
│ ├── sbin/
│ ├── dev/
│ ├── proc/
│ ├── sys/
│ ├── tmp/
│ └── init # стартовий процес
├── rootfs.cpio.gz # архівований rootfs (initramfs)
└── run.sh # скрипт запуску QEMU

## Як запустити систему

### Головне, це переконатися, що rootfs.cpio.gz існує

```bash
ls -lh rootfs.cpio.gz

## Запуск Qemu
./run.sh

## Результат очікуваний
Після запуску з’явиться консоль mini-Linux:
=== ROOTFS INIT STARTED ===
/ # 

Це означає, що ядро успішно завантажило init, а BusyBox працює в режимі shell.

### Вміст init-файлу

#!/bin/sh

mount -t devtmpfs devtmpfs /dev
mount -t proc none /proc
mount -t sysfs none /sys
mount -t tmpfs tmpfs /run

echo /sbin/mdev > /proc/sys/kernel/hotplug
mdev -s

echo "=== ROOTFS INIT STARTED ==="

exec /bin/sh

###

### Після запуску. В системі можна використовувати наступні команди BusyBox:
ls
cd
mkdir
cat
echo
dmesg
uname -a
ps
mount
ls -l /dev  - Також можна переглянути наступні девайси



