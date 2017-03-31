obj-m := cdev.o 
current_path = $(shell pwd)
kernel_path = /usr/src/kernels/$(shell uname -r)
all:
	make -C $(kernel_path) M=$(current_path) modules
clean:
	make -C $(kernel_path) M=$(current_path) clean

