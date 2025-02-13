OSNAME=noOS
SRC_DIR=src
BOOT_SOURCES=$(wildcard ${SRC_DIR}/boot/*.asm)
AS=nasm
CC=i386-elf-gcc
AR=i386-elf-ar
LD=i386-elf-ld
ASFLAGS=-f elf32
MKDIR_P=mkdir -p
OUT_DIR=bin
ROOTFS_DIR =${OUT_DIR}/rootfs
ROOTFS_FILE=rootfs.dmg
RAWROOTFS_FILE=rootfs.raw
OS_IMAGE_FILE=os.img
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra -nostdlib -pedantic -Werror -lgcc -D OSNAME="\"${OSNAME}\"" -masm=intel
KERNEL_SRC_DIR=${SRC_DIR}/kernel
DEPS=$(wildcard ${KERNEL_SRC_DIR}/*.h)
_OBJ=kernel.o serial.o utils.o tty.o idt.o paging.o
OBJ = $(patsubst %,$(OUT_DIR)/%,$(_OBJ))
BOOT_SRC_DIR=${SRC_DIR}/boot
BOOT_ASM_FILE=${BOOT_SRC_DIR}/boot.asm
LOG_DIR=log
SERIAL_LOG_FILE=${LOG_DIR}/serial.log

.PHONY: all clean run-bochs run-qemu directories

all: ${OUT_DIR}/${OS_IMAGE_FILE} ${OUT_DIR}/${ROOTFS_FILE}

${OUT_DIR}:
	${MKDIR_P} ${OUT_DIR}

${ROOTFS_DIR}:
	${MKDIR_P} ${ROOTFS_DIR}

${OUT_DIR}/%.o: ${KERNEL_SRC_DIR}/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

${OUT_DIR}/boot_main.o: $(BOOT_SOURCES) ${OUT_DIR}
	$(AS) $(ASFLAGS) ${BOOT_ASM_FILE} -o $@

${OUT_DIR}/boot_memory.o: ${OUT_DIR} src/shared/memory_map.c
	${CC} -m16 -c -o $@ $(CFLAGS) src/shared/memory_map.c

${OUT_DIR}/boot.a: ${OUT_DIR} ${OUT_DIR}/boot_main.o ${OUT_DIR}/boot_memory.o
	$(AR) cr $@ ${OUT_DIR}/boot_main.o ${OUT_DIR}/boot_memory.o

run-qemu: ${OUT_DIR}/${OS_IMAGE_FILE} ${OUT_DIR}/${RAWROOTFS_FILE}
	qemu-system-x86_64 \
		-m 128M \
		-drive format=raw,file=${OUT_DIR}/${OS_IMAGE_FILE} \
		-chardev stdio,id=char0,mux=on,logfile=${SERIAL_LOG_FILE},signal=off \
		-serial chardev:char0

${OUT_DIR}/idt.o : CFLAGS+=-mgeneral-regs-only

run-bochs: ${OUT_DIR}/${OS_IMAGE_FILE}
	bochs -q

${OUT_DIR}/os.bin: ${OUT_DIR}/boot.a ${OBJ} linker.ld
	${CC} -T linker.ld -o $@ $(CFLAGS) ${OUT_DIR}/boot.a ${OBJ}

${OUT_DIR}/${ROOTFS_FILE}: ${ROOTFS_DIR}
	hdiutil create $@ -ov -volname "rootfs" -fs FAT32 -srcfolder ${OUT_DIR}/rootfs

${OUT_DIR}/${RAWROOTFS_FILE}: ${OUT_DIR}/${ROOTFS_FILE}
	qemu-img convert $< $@

bin/${OS_IMAGE_FILE}: bin/os.bin
	dd bs=512 count=2880 if=/dev/zero of=$@
	dd if=$< of=$@ conv=notrunc

clean:
	rm -rf bin/*
