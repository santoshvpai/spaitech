BBB_BUILD_DIR := 3.8.13-bone71

obj-m+=hello.o

all:
	make -C /lib/modules/$(BBB_BUILD_DIR)/build/ M=$(PWD) modules
clean:
	make -C /lib/modules/$(BBB_BUILD_DIR)/build/ M=$(PWD) clean