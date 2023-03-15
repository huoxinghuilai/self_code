arm-none-eabi-as -mcpu=arm926ej-s -g start.s -o start.o
arm-none-eabi-gcc -c -mcpu=arm926ej-s -g init.c -o init.o
arm-none-eabi-gcc -c -mcpu=arm926ej-s -g task.c -o task.o
arm-none-eabi-gcc -c -mcpu=arm926ej-s -g common.c -o common.o
arm-none-eabi-gcc -c -mcpu=arm926ej-s -g mem.c -o mem.o
arm-none-eabi-ld -T link.ld init.o start.o task.o common.o mem.o -o image.elf

qemu-system-arm -M versatilepb -m 128M -nographic -kernel image.elf