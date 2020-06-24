SOURCES=$(wildcard src/*.asm)
AS=nasm
ASFLAGS=-f bin
MKDIR_P=mkdir -p
OUT_DIR=bin

.PHONY: all clean run directories

all: directories bin/fun.img

directories: ${OUT_DIR}

${OUT_DIR}:
	${MKDIR_P} ${OUT_DIR}

run: all

bin/boot.bin: $(SOURCES)
	$(AS) -f bin src/main.asm -o $@

run: bin/fun.img
	qemu-system-x86_64 -drive format=raw,file=$<

bin/fun.img: bin/boot.bin
	dd if=/dev/zero of=$@ bs=512 count=2880
	dd if=bin/boot.bin of=$@ conv=notrunc bs=512 count=1

clean:
	rm -rf bin/*
