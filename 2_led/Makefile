NAME 			:= led
NAME_KO 		:= $(NAME)
NAME_APP 		:= $(NAME)APP
CROSS_COMPILE 	:= arm-linux-gnueabihf-
CC   			:= $(CROSS_COMPILE)gcc
KERNELDIR 		:= /home/zhen/linux/nxp_linux/linux-imx-rel_imx_4.1.15_2.1.0_ga
CURRENT_PATH 	:= $(shell pwd)

obj-m := $(NAME).o

build: kernel_modules

kernel_modules:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) modules
app: $(NAME_APP).o
	$(CC) $^ -o $(NAME_APP)

%.o: %.c
	$(CC) -c $^ -o $@

clean:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) clean