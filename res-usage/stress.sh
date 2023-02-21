#!/bin/bash

stress-ng --cpu 8 --timeout 90s
stress-ng --io 4 --timeout 90s
stress-ng --vm 2 --vm-bytes 128M --fork 4 --timeout 90s
stress-ng --cpu 8 --io 4 --timeout 90s
stress-ng --io 4 --vm 2 --vm-bytes 128M --timeout 90s
stress-ng --cpu 8 --vm 2 --vm-bytes 128M --fork 4 --timeout 90s
stress-ng --cpu 16 --io 8 --timeout 180s
stress-ng --io 8 --vm 4 --vm-bytes 512M --timeout 180s
stress-ng --cpu 16 --vm 8 --vm-bytes 1024M --fork 8 --timeout 180s