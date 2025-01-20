#!/usr/bin/env bash

nasm -f bin -o bootloader.bin bl.asm
qemu-system-x86_64 bootloader.bin &