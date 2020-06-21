#!/bin/bash

yasm -f bin boot.asm -o boot.bin && qemu-system-x86_64 -nographic boot.bin
