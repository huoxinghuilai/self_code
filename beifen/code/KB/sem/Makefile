obj-m := sem.o
current := $(shell pwd)
kernel := /usr/src/kernels/$(shell uname -r)
all:
	make -C $(kernel) M=$(current) modules
clean:
	make -C $(kernel) M=$(current) clean
