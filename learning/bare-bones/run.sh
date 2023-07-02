sh build.sh # Build the program first
qemu-system-i386 -cdrom myos.iso # Run using QEMU, runs through the bootloader (GRUB) first
# BE REALLY CAREFUL NOT TO CLICK INSIDE THE WINDOW, IT IS REALLY HARD TO REGAIN CONTROL OF YOUR COMPUTER AFTERWARDS