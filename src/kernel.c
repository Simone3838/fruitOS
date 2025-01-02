// kernel.c
#include "kernel.h"
#include <stdint.h>

// Define ports for keyboard input
#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_COMMAND_PORT 0x64

void outb(uint16_t port, uint8_t data) {
    __asm__ __volatile__("outb %1, %0" : : "dN"(port), "a"(data));
}

uint8_t inb(uint16_t port) {
    uint8_t result;
    __asm__ __volatile__("inb %1, %0" : "=a"(result) : "dN"(port));
    return result;
}

void keyboard_handler(void) {
    uint8_t status = inb(KEYBOARD_STATUS_PORT);
    if (status & 0x01) {
        uint8_t keycode = inb(KEYBOARD_DATA_PORT);
        // Handle keycode (e.g., print it to the screen)
    }
}

void kernel_main(void) {
    // Initialize the shell
    shell();

    // The shell function will take over, so no further code is needed here
}
