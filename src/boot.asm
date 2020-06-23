bits 16
org 0x7c00

    jmp boot

%include "src/write_string.asm"

gdtinfo:
    dw gdt_end - gdt - 1
    dd gdt
gdt:
    dd 0, 0
flatdesc:
    db 0xff, 0xff, 0, 0, 0, 10010010b, 11001111b, 0
gdt_end:

welcomeString: db "Welcome to funOS! Starting boot process...", 0

boot:
    mov ax, 0x3
    int 0x10

    mWriteString welcomeString

    ; disable a20 line
    in al, 0x92
    or al, 2
    out 0x92, al

    xor ax, ax   ; make it zero
    mov ds, ax   ; DS=0
    mov ss, ax   ; stack starts at 0
    mov sp, 0x9c00   ; 2000h past code start

    cli      ; no interrupt
    lgdt [gdtinfo]   ; load gdt register
    mov  eax, cr0   ; switch to pmode by
    or al, 1         ; set pmode bit
    mov  cr0, eax

    mov  bx, 0x08   ; select descriptor 1
    mov  ds, bx   ; 8h = 1000b

    jmp boot32

bits 32

boot32:
    mov bx, 0x0f01   ; attrib/char of smiley
    mov eax, 0x0b8000 ; note 32 bit offset
    mov word [ds:eax], bx

    jmp boot32

    ; Fill remaining bytes to 512 border
    times 510-($-$$) db 0
    dw 0xaa55
