#!/bin/bash

# main scheduler file
cp /media/pietro/cf739281-9e11-46cb-880b-25e524f90f73/ODROIDXU3/kernel/samsung/exynos5422/kernel/sched/core.c .
# cpufreq file, inserted hook for getting frequency
cp /media/pietro/cf739281-9e11-46cb-880b-25e524f90f73/ODROIDXU3/kernel/samsung/exynos5422/drivers/cpufreq/cpufreq.c .
# ina231 driver, hook for getting power
cp /media/pietro/cf739281-9e11-46cb-880b-25e524f90f73/ODROIDXU3/kernel/samsung/exynos5422/drivers/hardkernel/ina231-i2c.c .
# thermal driver for exynos. Inserted hook in the function exynos_thermal_get_value to get sensor values
cp /media/pietro/cf739281-9e11-46cb-880b-25e524f90f73/ODROIDXU3/kernel/samsung/exynos5422/drivers/thermal/exynos_thermal.c .
# fan driver. gets both fan state and calls periodicall exynos_thermal_get_value
cp /media/pietro/cf739281-9e11-46cb-880b-25e524f90f73/ODROIDXU3/kernel/samsung/exynos5422/drivers/hardkernel/odroid_fan.c .
