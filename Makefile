SOURCES=$(wildcard src/*.asm)
AS=nasm
ASFLAGS=-f bin

.PHONY: all clean run

all: bin/os.bin

run: all run

bin/os.bin: $(SOURCES)
	$(AS) -f bin src/main.asm -o $@

run: bin/os.bin
	qemu-system-x86_64 -nographic $<

clean:
	rm -rf bin/*
