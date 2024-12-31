; boot.asm
BITS 16
ORG 0x7C00

start:
    ; Set up the stack
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00
    sti

    ; Print "fruitOS" to the screen
    mov si, msg
print_char:
    lodsb
    or al, al
    jz done
    mov ah, 0x0E
    int 0x10
    jmp print_char
done:
    hlt

msg db 'fruitOS', 0

times 510-($-$$) db 0
dw 0xAA55
