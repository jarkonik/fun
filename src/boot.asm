bits 16
org 0x7c00

start:
    jmp boot

%include "src/write_string.asm"

data:
.welcomeString: db "Welcome to koniOS! Starting boot process...", 0

boot:
    mWriteString data.welcomeString
    jmp $

halt:
    hlt

    ; Fill remaining bytes to 512 border
    times 510-($-$$) db 0
    dw 0xaa55
