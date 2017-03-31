obi-m := irq.o

CURRENT_PATH := $(shell pwd)
KERNEL_PATH := /usr/src/kernels/$(shell uname -r)

all:
	make -C $(KERNEL_PATH) M=$(CURRENT_PATH) modules
clean:
	make -C $(KERNEL_PATH) M=$(CURRENT_PATH) clean

