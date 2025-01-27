ORG 0x7c00 ; origin
BITS 16 ; 16 bit architecture (for now)

start:
    mov si, message
    call print

    jmp $ ; endless loop

print:
    mov bx, 0
.loop:
    lodsb
    cmp al, 0
    je .done
    call print_char
    jmp .loop
.done:
    ret

print_char:
    mov ah, 0eh
    int 0x10 ; BIOS call
    ret

message: db 'Hello Actarus', 0

times 510-($- $$) db 0 ; fill at least 510 bytes of data, pabbing rest to 0
dw 0xAA55 ; signature