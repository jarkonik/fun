%define VGA_TEXT_MODE 0x03

%macro SET_VGA_MODE 1
	mov ax, %1
	int 0x10
%endmacro
