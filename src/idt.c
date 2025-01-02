// idt.c
#include "idt.h"
#include "kernel.h"

struct idt_entry {
    uint16_t base_low;
    uint16_t sel;
    uint8_t always0;
    uint8_t flags;
    uint16_t base_high;
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

// Define the IDT and IDT pointer
struct idt_entry idt[256];
struct idt_ptr idt_ptr;

extern void idt_load(void);

void set_idt_gate(int n, uint32_t handler) {
    idt[n].base_low = handler & 0xFFFF;
    idt[n].base_high = (handler >> 16) & 0xFFFF;
    idt[n].sel = 0x08;  // Kernel code segment
    idt[n].always0 = 0;
    idt[n].flags = 0x8E;  // Present, ring 0, 32-bit interrupt gate
}

void init_idt(void) {
    idt_ptr.limit = sizeof(idt) - 1;
    idt_ptr.base = (uint32_t)&idt;

    // Set keyboard interrupt (IRQ1)
    set_idt_gate(33, (uint32_t)keyboard_handler);

    idt_load();
}
