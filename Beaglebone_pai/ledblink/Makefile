BBB_BUILD_DIR := 3.8.13-bone71

#obj-m+=ex1_bb_ledblink.o
obj-m+=ex2_bb_ledblink_module_param.o

all:
	make -C /lib/modules/$(BBB_BUILD_DIR)/build/ M=$(PWD) modules
clean:
	make -C /lib/modules/$(BBB_BUILD_DIR)/build/ M=$(PWD) clean