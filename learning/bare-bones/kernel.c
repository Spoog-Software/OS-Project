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

/* Hardware text mode color constants. */
enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
    // bg occupies upper 4 bits, fg occupies bottom 4
    return bg << 4 | fg;
}

static inline uint16_t vga_entry(unsigned char character, uint8_t color) 
{
    // upcast color and character to 16 bits; then, shift color up to the upper 8 bits, and join with character in the lower 8
    return (uint16_t) color << 8 | (uint16_t) character ;
}

size_t strlen(const char* str) 
{
    // while current character is not a null byte, increment length; all strings end in null (i.e. character code 0) in C
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;  // Pointer to the VGA screen buffer in memory; will be assigned its actual address later

void terminal_initialize(void) 
{
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminal_buffer = (uint16_t*) 0xB8000;
    // This loop initialises all the screen data to empty space. (Is it necessary to do this, or will the terminal buffer be zeroed by default?)
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

void terminal_setcolor(uint8_t color) 
{
    terminal_color = color;
}

static inline size_t get_index(size_t x, size_t y) {
    return y * VGA_WIDTH + x;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
    const size_t index = get_index(x, y);
    terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) 
{
    if (c == '\n') {
        terminal_row++;
        terminal_column = 0;
    } else if (c == '\t') {
        terminal_column += (4 - (terminal_column % 4));
    } else {
        terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
    }
    
    if (++terminal_column == VGA_WIDTH) {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT)
        {
            for (size_t i = VGA_WIDTH; i < VGA_WIDTH*VGA_HEIGHT; i++) {
                terminal_buffer[i-VGA_WIDTH] = terminal_buffer[i];
            }
            for (size_t i = VGA_WIDTH * (VGA_HEIGHT - 1); i < VGA_WIDTH * VGA_HEIGHT; i++) {
                terminal_buffer[i] = '\0';
            }
            terminal_row--;
        }
    }
}

void terminal_write(const char* data, size_t size) 
{
    // Writes a specified number of characters to the screen
    for (size_t i = 0; i < size; i++) {
        terminal_putchar(data[i]);
    }
}

void terminal_writestring(const char* data) 
{
    terminal_write(data, strlen(data));
}

void kernel_main(void) 
{
    /* Initialize terminal interface */
    terminal_initialize();
 
    /* Newline support is left as an exercise. */
    terminal_writestring("Hello, kernel World!\n");
    for (size_t i = 0; i < VGA_HEIGHT-2; i++) {
        terminal_writestring("EEEEE\n");
    }
    terminal_writestring("SINQIWSNIQUWSNUIQNSUINQUISHELPQWDNUQWDINQWUDSINQIWSNIQUWSNUIQNSUINQUISHELPQWDNUQWDINQWUD");
}
