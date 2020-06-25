# TODO: Use linker scripts

BOOT_SOURCES=$(wildcard src/boot/*.asm)
KERNEL_SOURCES=$(wildcard src/kernel/*.c)
AS=nasm
CC=i386-elf-gcc
ASFLAGS=-f elf32
MKDIR_P=mkdir -p
OUT_DIR=bin
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra -nostdlib -pedantic

.PHONY: all clean run-bochs run-qemu directories

all: directories bin/os.img

directories: ${OUT_DIR}

${OUT_DIR}:
	${MKDIR_P} ${OUT_DIR}

bin/kernel.o: $(KERNEL_SOURCES)
	$(CC) $(CFLAGS) -c $< -o $@

bin/boot.o: $(BOOT_SOURCES)
	$(AS) $(ASFLAGS) src/boot/boot.asm -o $@

run-qemu: bin/os.img
	qemu-system-x86_64 -drive format=raw,file=$<

run-bochs: bin/os.img
	bochs -q

bin/os.bin: bin/boot.o bin/kernel.o linker.ld
	i386-elf-gcc -T linker.ld -o $@ $(CFLAGS) bin/boot.o bin/kernel.o -lgcc

bin/os.img: bin/os.bin
	dd bs=512 count=2880 if=/dev/zero of=$@
	dd if=$< of=$@ conv=notrunc

clean:
	rm -rf bin/*
