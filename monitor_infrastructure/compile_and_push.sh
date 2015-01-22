

#!bin/bash/

make clean

make

adb push reliability_stats_module.ko data/
