#ifndef ARCH_I386_PS2_H
#define ARCH_I386_PS2_H

#include <kernel/ps2.h>

char key_events[] = {
    ' ', ' ', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    '-', '=', '\b', '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U',
    'I', 'O', 'P', '[', ']', '\n', ' ', 'A', 'S', 'D', 'F', 'G',
    'H', 'J', 'K', 'L', ';', '\'', '`', ' ', '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 'M',
    ',', '.', '/', ' ', ' ', ' ', ' ', ' ',
};

bool key_states[128] = {0};

#endif