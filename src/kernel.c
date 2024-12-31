// kernel.c
void kernel_main(void) {
    const char *str = "Welcome to fruitOS!";
    char *vidptr = (char*)0xb8000;  // Video memory address
    unsigned int i = 0;
    unsigned int j = 0;

    // Clear the screen
    while(j < 80 * 25 * 2) {
        vidptr[j] = ' ';
        vidptr[j+1] = 0x07;
        j += 2;
    }

    j = 0;

    // Write the string to video memory
    while(str[j] != '\0') {
        vidptr[i] = str[j];
        vidptr[i+1] = 0x07;  // Attribute byte - white text on black background
        ++j;
        i += 2;
    }

    return;
}
