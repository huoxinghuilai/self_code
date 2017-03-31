obj-m := map_driver.o

CURRENT_PATF := $(shell pwd)
LINUX_KERNELS := $(shell uname -r)
LINUX_KERNELS_PATH := /usr/src/kernels/$(LINUX_KERNELS)

all:
	make -C $(LINUX_KERNELS_PATH) M=$(CURRENT_PATH) modules

clean:
	make -C $(LINUX_KERNELS_PATH) M=$(CURRENT_PATH) clean
 
