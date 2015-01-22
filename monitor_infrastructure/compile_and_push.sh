

#!bin/bash/

make clean

make

adb push monitor_infrastructure_driver.ko data/PIETRO
