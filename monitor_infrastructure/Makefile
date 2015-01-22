obj-m := reliability_stats_module.o

all:
	make ARCH=arm CROSS_COMPILE=/media/ftpdrive/Dragonboard/Android/prebuilt/linux-x86/toolchain/arm-eabi-4.4.3/bin/arm-eabi- -C /media/ftpdrive/Dragonboard/Android/out/target/product/msm8960/obj/KERNEL_OBJ M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
