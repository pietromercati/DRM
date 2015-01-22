obj-m := monitor_infrastructure_driver.o

all:
	make ARCH=arm CROSS_COMPILE=/media/pietro/cf739281-9e11-46cb-880b-25e524f90f73/ODROIDXU3/prebuilts/gcc/linux-x86/arm/arm-eabi-4.6/bin/arm-eabi- -C /media/pietro/cf739281-9e11-46cb-880b-25e524f90f73/ODROIDXU3/kernel/samsung/exynos5422 M=$(PWD) modules
	#make ARCH=arm CROSS_COMPILE=/media/ftpdrive/Dragonboard/Android/prebuilt/linux-x86/toolchain/arm-eabi-4.4.3/bin/arm-eabi- -C /media/ftpdrive/Dragonboard/Android/out/target/product/msm8960/obj/KERNEL_OBJ M=$(PWD) modules

# Path Odroid board
#./prebuilts/gcc/linux-x86/arm/arm-eabi-4.6

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
