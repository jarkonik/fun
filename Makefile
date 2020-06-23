SOURCES=$(wildcard src/*.asm)
AS=nasm
ASFLAGS=-f bin
MKDIR_P=mkdir -p
OUT_DIR=bin

.PHONY: all clean run directories

all: directories bin/os.bin

directories: ${OUT_DIR}

${OUT_DIR}:
	${MKDIR_P} ${OUT_DIR}

run: all run

bin/os.bin: $(SOURCES)
	$(AS) -f bin src/main.asm -o $@

run: bin/os.bin
	qemu-system-x86_64 -nographic $<

clean:
	rm -rf bin/*
