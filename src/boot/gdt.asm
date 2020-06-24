gdt:
.start:
	dq 0x0
.code:
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 10011010b
	db 11001111b
	db 0x0
.data:
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 10010010b
	db 11001111b
	db 0x0
.end:

gdt_pointer:
	dw gdt.end - gdt.start
	dd gdt.start

CODE_SEG equ gdt.code - gdt.start
DATA_SEG equ gdt.data - gdt.start
