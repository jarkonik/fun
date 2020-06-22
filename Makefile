SOURCES := src/os.asm
AS = yasm

.PHONY : all clean run

all: bin/os.bin

run: all run

clean:
	rm -rf bin/*

bin/os.bin: $(SOURCES)
	$(AS) -f bin $< -o $@

run: bin/os.bin
	qemu-system-x86_64 -nographic $<
