#!/bin/bash
for i in {12..23}; do
   echo "Disabling logical HT core $i."
   echo 0 > /sys/devices/system/cpu/cpu${i}/online;
done
