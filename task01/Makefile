ifneq ($(KERNELRELEASE),)
obj-m := hello.o
else
KDIR ?= /lib/modules/`uname -r`/build

default:
	make -C $(KDIR) M=$$PWD
clean:
	rm -f built-in.o hello.ko hello.mod.o Module.symvers hello.mod.c modules.order hello.o
endif
