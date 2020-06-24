section .boot
bits 16
global boot

	jmp 0:boot

%include "src/boot/write_string.asm"
%include "src/boot/a20.asm"
%include "src/boot/vga_mode.asm"
%include "src/boot/gdt.asm"
%include "src/boot/protected_mode.asm"
%include "src/boot/segments.asm"

boot:
	WRITE_STRING welcome_message
	ENABLE_A20
	SET_VGA_MODE VGA_TEXT_MODE

	cli
	lgdt [gdt_pointer]

	ENABLE_PROTECTED_MODE
	SET_SEGMENT_REGISTERS DATA_SEG

	jmp CODE_SEG:boot32

welcome_message:
	db "Welcome to funOS, starting boot process...", 10, 0

bits 32
VGA equ 0xb8000

boot32:
	mov dword [VGA], 0x07690748
	jmp $

times 510 - ($-$$) db 0
dw 0xaa55
