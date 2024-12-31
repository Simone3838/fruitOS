# Assemble the bootloader
nasm -f bin boot.asm -o boot.bin

# Compile the kernel
gcc -m32 -c kernel.c -o kernel.o -ffreestanding -O2 -Wall -Wextra

# Link the kernel
ld -m elf_i386 -T linker.ld kernel.o -o kernel.bin -nostdlib

# Create a bootable image
cat boot.bin kernel.bin > fruitOS.bin
