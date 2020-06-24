%macro ENABLE_PROTECTED_MODE 0
	mov eax, cr0
	or eax, 0x1
	mov cr0, eax
%endmacro
