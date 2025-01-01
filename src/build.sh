# Assemble the bootloader
nasm -f bin boot.asm -o boot.bin

# Compile the kernel, shell, and IDT
gcc -m32 -c kernel.c -o kernel.o -ffreestanding -O2 -Wall -Wextra
gcc -m32 -c shell.c -o shell.o -ffreestanding -O2 -Wall -Wextra
gcc -m32 -c idt.c -o idt.o -ffreestanding -O2 -Wall -Wextra

# Link the kernel
ld -m elf_i386 -T linker.ld kernel.o shell.o idt.o -o kernel.bin -nostdlib

# Create a bootable image
cat boot.bin kernel.bin > fruitOS.bin
