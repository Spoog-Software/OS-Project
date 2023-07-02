sudo apt install xorriso qemu
BINUTILS_PATH=$HOME/opt/cross/bin
echo "Assembling bootstrap code..." & $BINUTILS_PATH/i686-elf-as boot.s -o boot.o
echo "Compiling kernel..." & $BINUTILS_PATH/i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
echo "Linking bootstrap and kernel..." & $BINUTILS_PATH/i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc
grub-file --is-x86-multiboot myos.bin && echo "OS was built x86-bootable" || echo "OS cannot be booted on x86!"
mkdir -p isodir/boot/grub
cp myos.bin isodir/boot/myos.bin
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o myos.iso isodir
