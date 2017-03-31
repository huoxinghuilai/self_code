obj-m := drv_miscdevice.o
path := $(shell pwd)
kernel := /usr/src/kernels/$(shell uname -r)

all:
	make -C $(kernel) M=$(path) modules
clean:
	make -C $(kernel) M=$(path) clean
 
