ORG 0 ; origin
BITS 16 ; 16 bit architecture (for now)

jmp 0x7c0:start

start:
    cli ; clear interrupts
    mov ax, 0x7c0
    mov ds, ax
    mov es, ax

    mov ax, 0x00 ; set stack 0
    mov ss, ax
    mov sp, 0x7c00 ; stack pointer
    sti ; enable interrupts

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