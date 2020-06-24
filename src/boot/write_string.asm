write_string:
	lodsb
	or     al, al
	jz     .done

	mov    ah, 0xe
	int    0x10

	jmp    write_string
.done:
	ret

%macro WRITE_STRING 1
	mov si, %1
	call write_string
%endmacro
