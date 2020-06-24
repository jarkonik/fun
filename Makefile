# TODO: Use linker scripts

BOOT_SOURCES=$(wildcard src/boot/*.asm)
KERNEL_SOURCES=$(wildcard src/kernel/*.c)
AS=nasm
CC=i386-elf-gcc
ASFLAGS=-f elf32
MKDIR_P=mkdir -p
OUT_DIR=bin
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra -nostdlib

.PHONY: all clean run directories

all: directories bin/fun.img

directories: ${OUT_DIR}

${OUT_DIR}:
	${MKDIR_P} ${OUT_DIR}

run: all

bin/kernel.o: $(KERNEL_SOURCES)
	$(CC) $(CFLAGS) -c $< -o $@

bin/boot.o: $(BOOT_SOURCES)
	$(AS) $(ASFLAGS) src/boot/boot.asm -o $@

run: bin/fun.img
	qemu-system-x86_64 -drive format=raw,file=$<

bin/fun.img: bin/boot.o bin/kernel.o
	i386-elf-gcc -T linker.ld -o $@ $(CFLAGS) bin/boot.o bin/kernel.o -lgcc

clean:
	rm -rf bin/*
