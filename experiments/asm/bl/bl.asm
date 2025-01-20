[BITS 16]
[ORG 0x7C00]

start:
    mov si, message ; Anything starts at 0x7C00
    call print_string
    jmp $

print_string:
    mov ah, 0x0E
.loop:
    lodsb
    test al, al
    jz .done
    int 0x10
    jmp .loop
.done:
    ret

message: db 'Hey, Actarus OS', 0

times 510-($-$$) db 0
dw 0xAA55