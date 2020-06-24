SOURCES=$(wildcard src/*.asm)
AS=nasm
ASFLAGS=-f bin
MKDIR_P=mkdir -p
OUT_DIR=bin

.PHONY: all clean run directories

all: directories bin/boot.bin

directories: ${OUT_DIR}

${OUT_DIR}:
	${MKDIR_P} ${OUT_DIR}

run: all

bin/boot.bin: $(SOURCES)
	$(AS) -f bin src/main.asm -o $@

run: bin/boot.bin
	qemu-system-x86_64 -drive format=raw,file=$<

clean:
	rm -rf bin/*
