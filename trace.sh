#! /bin/bash
# Path: sassy-metrics/trace.sh

# This script is used to trace the performance of a all running processes
# on a system. It uses the perf tool to trace the performance of the system
# and the plugged in power monitors to trace the power consumption of the system.

# The script takes one argument, the name of the trace file to be created.

# The script is run as root, so that it can trace all processes on the system.

# The script is run as a background process, so that it can run for a long time
# without interfering with the user.

# The script is run with the following command:
# ./trace.sh <trace-file-name>

# The script is run from the sassy-metrics directory.

sudo python3 power-meter-logging/pm.py -o power-meter-logging/tracefile-${1}.csv & sudo perf stat -e cycles,instructions,ref-cycles,LLC-load-misses,LLC-loads,LLC-store-misses,LLC-stores -I 200 --per-thread &> res-usage/perftrace-${1}.txt & sudo blktrace -d /dev/sda -o - | blkparse -i - -f "%5T.%9t %5p %5n %9N %3d\n" &> res-usage/iotrace-${1}.txt & sudo turbostat --show PkgWatt,RAMWatt  --interval 1 &> res-usage/rapltrace-${1}.txt && kill $!
