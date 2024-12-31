; boot.asm
BITS 16
ORG 0x7C00

start:
    cli             ; Clear interrupts
    hlt             ; Halt CPU

times 510 - ($ - $$) db 0  ; Fill the rest of the sector with zeros
dw 0xAA55                  ; Boot signature
