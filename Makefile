# TODO: Use linker scripts

BOOT_SOURCES=$(wildcard src/boot/*.asm)
KERNEL_SOURCES=$(wildcard src/kernel/*.c)
AS=nasm
CC=i386-elf-gcc
ASFLAGS=-f elf32
MKDIR_P=mkdir -p
OUT_DIR=bin
ROOTFS_DIR =${OUT_DIR}/rootfs
ROOTFS_FILE=rootfs.dmg
RAWROOTFS_FILE=rootfs.raw
OS_IMAGE_FILE=os.img
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra -nostdlib -pedantic

.PHONY: all clean run-bochs run-qemu directories

all: ${OUT_DIR}/${OS_IMAGE_FILE} ${OUT_DIR}/rootfs.dmg

${OUT_DIR}:
	${MKDIR_P} ${OUT_DIR}

${ROOTFS_DIR}:
	${MKDIR_P} ${ROOTFS_DIR}

${OUT_DIR}/kernel.o: $(KERNEL_SOURCES) ${OUT_DIR}
	$(CC) $(CFLAGS) -c $< -o $@

${OUT_DIR}/boot.o: $(BOOT_SOURCES) ${OUT_DIR}
	$(AS) $(ASFLAGS) src/boot/boot.asm -o $@

run-qemu: ${OUT_DIR}/${OS_IMAGE_FILE} ${OUT_DIR}/${RAWROOTFS_FILE}
	qemu-system-x86_64 -drive format=raw,file=${OUT_DIR}/${OS_IMAGE_FILE} -drive format=raw,file=${OUT_DIR}/${RAWROOTFS_FILE}

run-bochs: ${OUT_DIR}/${OS_IMAGE_FILE}
	bochs -q

${OUT_DIR}/os.bin: ${OUT_DIR}/boot.o ${OUT_DIR}/kernel.o linker.ld
	i386-elf-gcc -T linker.ld -o $@ $(CFLAGS) ${OUT_DIR}/boot.o ${OUT_DIR}/kernel.o -lgcc

${ROOTFS_FILE}:
	hdiutil create $@ -ov -volname "rootfs" -fs FAT32 -srcfolder ${OUT_DIR}/rootfs

${OUT_DIR}/${RAWROOTFS_FILE}: ${OUT_DIR}/${ROOTFS_FILE}
	qemu-img convert $< $@

bin/${OS_IMAGE_FILE}: bin/os.bin ${ROOTFS_DIR}
	dd bs=512 count=2880 if=/dev/zero of=$@
	dd if=$< of=$@ conv=notrunc

clean:
	rm -rf bin/*
