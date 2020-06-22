bits 16
org 0x7c00

boot:
	cli

	call print_welcome

	int 0x15 ; enable A20 bit

	mov ax, 0x3
	int 0x10 ; set vga text mode 3

	cli
	lgdt [gdt_start]

	jmp $

halt:
	hlt

print_welcome:
	mov si, welcome
	mov ah, 0x0e

.loop:
	lodsb

	cmp al, 0
	je .done

	int 0x10
	jmp .loop
.done
	ret


; data
	welcome: db "Welcome to koniOS! Starting boot process...", 0
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
boot32:


; Fill remaining bytes to 512 border
	times 510-($-$$) db 0
	dw 0xaa55
