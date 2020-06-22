bits 16
org 0x7c00

start:
    jmp boot

%include "src/boot/write_string.asm"

strings:
.welcome: db "Welcome to koniOS! Starting boot process...", 0

boot:
    mWriteString strings.welcome
    jmp $

halt:
    hlt

    ; Fill remaining bytes to 512 border
    times 510-($-$$) db 0
    dw 0xaa55
