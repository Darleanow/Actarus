[BITS 32]

section .asm

global task_return
global restore_general_purpose_registers
global user_registers

task_return:
    mov ebp, esp
    ; PUSH DATA SEG (SS FINe)
    ; PUSH STACK ADDR
    ; PUSH FLAGS
    ; PUSH CODE SEG
    ; PUSH IP

    ; Access structure passed to us
    mov ebx, [ebp+4]

    ; push data stack selector
    push dword [ebx+44]

    ; push stack pointer
    push dword [ebx+40]

    ; push flags
    pushf
    pop eax
    or eax, 0x200
    push eax

    ; Push code segment
    push dword [ebx+32]

    ; push IP to exec
    push dword [ebx+28]

    ; Setup Segment registers
    mov ax, [ebx+44]
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push dword [ebp+4]
    call restore_general_purpose_registers
    add esp, 4

    ; Leave kland and execute in uland
    iretd

restore_general_purpose_registers:
    push ebp
    mov ebp, esp
    mov ebx, [ebp+8]
    mov edi, [ebx]
    mov esi, [ebx+4]
    mov ebp, [ebx+8]
    mov edx, [ebx+16]
    mov ecx, [ebx+20]
    mov eax, [ebx+24]
    mov ebx, [ebx+12]
    pop ebp
    ret

user_registers:
    mov ax, 0x23
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    ret