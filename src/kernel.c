// kernel.c
#include <stdint.h>

// Function prototype
void shell();

void kernel_main(void) {
    // Initialize the shell
    shell();

    // The shell function will take over, so no further code is needed here
}
