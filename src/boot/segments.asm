%macro SET_SEGMENT_REGISTERS 1
	mov ax, %1
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
%endmacro
