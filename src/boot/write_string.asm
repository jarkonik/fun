WriteString:
  lodsb
  or     al, al
  jz     .done

  mov    ah, 0xe
  int    0x10

  jmp    WriteString
.done:
  ret

%macro mWriteString 1
    mov si, %1
    call WriteString
%endmacro
