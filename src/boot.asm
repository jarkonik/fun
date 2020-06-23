bits 16
org 0x7c00

boot:
	; enable a20
	mov ax, 0x2401
	int 0x15

	; vga mode 3
	mov ax, 0x3
	int 0x10

	cli

	lgdt [gdt_pointer]

	mov eax, cr0
	or eax,0x1
	mov cr0, eax

	jmp CODE_SEG:boot2

gdt_start:
	dq 0x0
gdt_code:
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 10011010b
	db 11001111b
	db 0x0
gdt_data:
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 10010010b
	db 11001111b
	db 0x0
gdt_end:
gdt_pointer:
	dw gdt_end - gdt_start
	dd gdt_start

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

bits 32
boot2:
	mov dword [0xb8000], 0x07690748
	jmp $

times 510 - ($-$$) db 0
dw 0xaa55
