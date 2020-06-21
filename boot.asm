[bits 16]
[org 0x7c00]

boot:
	call print
	jmp $

halt:
	hlt

print:
	mov si, welcome
	mov ah, 0x0e

.loop:
	lodsb 

	cmp al, 0
	je .done

	int 0x10
	jmp .loop

.done


; data
	welcome: db "Welcome to koniOS", 0

; Fill remaining bytes to 512 border
	times 510-($-$$) db 0
	dw 0xaa55
