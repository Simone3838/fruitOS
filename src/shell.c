#include <stdint.h>

// VGA text mode buffer address
#define VGA_ADDRESS 0xB8000
#define BUFSIZE 2200

// Define screen width and height
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

// Define VGA colors
#define WHITE_ON_BLACK 0x07

// Function prototypes
void clear_screen();
void print(const char* str);
void shell();

// Global variables
char* vga_buffer = (char*)VGA_ADDRESS;

void clear_screen() {
    for (int i = 0; i < BUFSIZE; i += 2) {
        vga_buffer[i] = ' ';
        vga_buffer[i + 1] = WHITE_ON_BLACK;
    }
}

void print(const char* str) {
    static uint16_t index = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] == '\n') {
            index = (index / SCREEN_WIDTH + 1) * SCREEN_WIDTH;
        } else {
            vga_buffer[index] = str[i];
            vga_buffer[index + 1] = WHITE_ON_BLACK;
            index += 2;
        }
    }
}

void shell() {
    clear_screen();
    print("Welcome to fruitOS shell!\n");
    print("Type 'help' for a list of commands.\n");

    while (1) {
        print("\nfruitOS> ");

        // Here you would capture user input and act on it. For simplicity, we use a static command
        // In a real implementation, you'd read from the keyboard buffer

        // Example command processing
        char command[10] = "help";  // Simulate user typing 'help'

        if (strcmp(command, "clear") == 0) {
            clear_screen();
        } else if (strcmp(command, "help") == 0) {
            print("Available commands:\n");
            print("  clear - Clear the screen\n");
            print("  help  - Display this help message\n");
        } else {
            print("Unknown command. Type 'help' for a list of commands.\n");
        }
    }
}

int strcmp(const char* str1, const char* str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}
