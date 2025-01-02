; idt_load.asm
BITS 32

global idt_load
idt_load:
    ; Load the address of the IDT pointer
    lidt [idt_ptr]
    ret
