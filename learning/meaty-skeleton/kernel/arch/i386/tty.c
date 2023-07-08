#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>
#include "vga.h"

static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;
static const int SCROLL_AMOUNT = 1;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

void terminal_initialize(void) {
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminal_buffer = VGA_MEMORY;
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

void terminal_setcolor(uint8_t color) {
    terminal_color = color;
}

void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}

inline void terminal_scroll(int num_lines) {
    for (size_t i = VGA_WIDTH*num_lines; i < VGA_WIDTH*VGA_HEIGHT; i++) {
        terminal_buffer[i-VGA_WIDTH*num_lines] = terminal_buffer[i];
    }
    for (size_t i = VGA_WIDTH * (VGA_HEIGHT - num_lines); i < VGA_WIDTH * VGA_HEIGHT; i++) {
        terminal_buffer[i] = ' ';
    }
    terminal_row -= num_lines;
}

void terminal_print_int(uint8_t num) {
    int digits_reversed[3];

    int i = 0;
    while (num > 0) {
        digits_reversed[i] = num % 10;
        num /= 10;
        i++;
    }

    int first = digits_reversed[2]+0x30;
    int second = digits_reversed[1]+0x30;
    if (first != 0x30) {
        terminal_putchar(first);
    }
    if (second != 0x30 || first != 0x30) {
        terminal_putchar(second);
    }
    terminal_putchar(digits_reversed[0]+0x30);
}

void terminal_putchar(char c) 
{
    if (c == '\n') {
        terminal_row++;
        terminal_column = 0;
    } else if (c == '\t') {
        terminal_column += (4 - (terminal_column % 4));
    } else if (c == '\b') {
        terminal_column--;
        if (terminal_column < 0) {
            terminal_column = 0;
            terminal_row -= 1;
        }
        terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
    } else {
        terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
        terminal_column++;
    }
    
    // Check if current column exceeds the screen width
    if (terminal_column == VGA_WIDTH) {
        terminal_column = 0;
        // Move onto the next row; if we reach the bottom, scroll everything up
        if (++terminal_row == VGA_HEIGHT)
        {
            terminal_scroll(SCROLL_AMOUNT);
        }
    }
}

void terminal_write(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++)
        terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) {
    terminal_write(data, strlen(data));
}
