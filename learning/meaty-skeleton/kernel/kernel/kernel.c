#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

char key_events[] = {
    ' ', ' ', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    '-', '=', '\b', '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U',
    'I', 'O', 'P', '[', ']', '\n', ' ', 'A', 'S', 'D', 'F', 'G',
    'H', 'J', 'K', 'L', ';', '\'', '`', ' ', '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 'M',
    ',', '.', '/', ' ', ' ', ' ', ' ', ' ',
};

bool key_states[128] = {0};

static const int SCROLL_AMOUNT = 1;

#define PS2_KEYBOARD 0x60
#define KEY_RELEASED_THRESHOLD 0x80

static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port)
                   : "memory");
    return ret;
}

static inline void outb(uint16_t port, uint8_t val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) :"memory");
    /* There's an outb %al, $imm8  encoding, for compile-time constant port numbers that fit in 8b.  (N constraint).
     * Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
     * The  outb  %al, %dx  encoding is the only option for all other cases.
     * %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
}

void kernel_main(void) 
{
    /* Initialize terminal interface */
    terminal_initialize();

    // Keyboard polling loop
    while (true) {
        uint8_t input = inb(PS2_KEYBOARD);
        uint8_t index = (input > KEY_RELEASED_THRESHOLD) ? input - KEY_RELEASED_THRESHOLD : input;
        uint8_t charcode = (uint8_t) key_events[index]; // Get character from scancode, e.g.
        if (input > KEY_RELEASED_THRESHOLD) {
            key_states[charcode] = false;
        } else {
            // Write character if it has just been pressed
            if (!key_states[charcode]) {
                terminal_putchar(charcode);
            }
            key_states[charcode] = true;
        }
    }
}
