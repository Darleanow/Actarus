ORG 0x7c00 ; origin
BITS 16 ; 16 bit architecture (for now)

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

_start: ; Bios Parameter Block specific
    jmp short start
    nop

times 33 db 0 ; fill null to BPB (offset total is 33)

start:
    jmp 0:step2

step2:
    cli ; clear interrupts
    mov ax, 0x00
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7c00 ; stack pointer
    sti ; enable interrupts


.load_protected:
    cli
    lgdt[gdt_descriptor]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    jmp CODE_SEG:load32

; GDT
gdt_start:
gdt_null:
    dd 0x0
    dd 0x0

; offset 0x8
gdt_code:     ; CH points to this
    dw 0xffff ; segment limit first 0-15 bits
    dw 0      ; Base first 0-15 bits
    db 0      ; Base 16-23 bits
    db 0x9a   ; access byte
    db 11001111b ; High 4 bit & low 4 bit flags
    db 0      ; base 24-31 bits

; offset 0x10
gdt_data:     ; DS, SS, ES, FS, GS
    dw 0xffff ; segment limit first 0-15 bits
    dw 0      ; Base first 0-15 bits
    db 0      ; Base 16-23 bits
    db 0x92   ; access byte
    db 11001111b ; High 4 bit & low 4 bit flags
    db 0      ; base 24-31 bits

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

[BITS 32]
load32:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov ebp, 0x00200000
    mov esp, ebp

    ; fast enable a20
    in al, 0x92
    or al, 2
    out 0x92, al

    jmp $

times 510-($- $$) db 0 ; fill at least 510 bytes of data, pabbing rest to 0
dw 0xAA55 ; signature