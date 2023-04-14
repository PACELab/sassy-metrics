#!/bin/bash

sudo perf stat -e cycles,instructions,ref-cycles,LLC-load-misses,LLC-loads,LLC-store-misses,LLC-stores -I 200 --per-thread --all-user &> perftrace-${1}.txt & sudo blktrace -d /dev/sda -o - | blkparse -i - -f "%5T.%9t %5p %5n %9N %3d\n" &> iotrace-${1}.txt & sudo turbostat --show PkgWatt,RAMWatt  --interval 1 &> rapltrace-${1}.txt && kill $!