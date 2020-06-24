%macro ENABLE_A20 0
    mov ax, 0x2401
    int 0x15
%endmacro
