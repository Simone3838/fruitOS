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

    ; Print "Loading kernel..." to the screen
    mov si, msg_loading
print_char:
    lodsb
    or al, al
    jz done_print
    mov ah, 0x0E
    int 0x10
    jmp print_char
done_print:

    ; Load the kernel (512 bytes, one sector) from the second sector of the disk
    mov ah, 0x02  ; BIOS read sector function
    mov al, 1     ; Number of sectors to read
    mov ch, 0     ; Cylinder number
    mov cl, 2     ; Sector number (second sector)
    mov dh, 0     ; Head number
    mov dl, 0     ; Drive number (first floppy disk)
    mov bx, 0x1000 ; Address to load the kernel (0x1000:0x0000)
    int 0x13      ; BIOS interrupt

    ; Check for errors
    jc disk_error

    ; Print "Kernel loaded" to the screen
    mov si, msg_loaded
    call print_string

    ; Jump to the kernel
    jmp 0x1000:0000

disk_error:
    ; Print "Disk error" to the screen
    mov si, msg_error
    call print_string
    hlt

print_string:
print_char_loop:
    lodsb
    or al, al
    jz done_string
    mov ah, 0x0E
    int 0x10
    jmp print_char_loop
done_string:
    ret

msg_loading db 'Loading kernel...', 0
msg_loaded db 'Kernel loaded', 0
msg_error db 'Disk error', 0

times 510-($-$$) db 0
dw 0xAA55
