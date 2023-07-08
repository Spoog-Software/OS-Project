#ifndef ARCH_I386_IO_H
#define ARCH_I386_IO_H

#include <stdint.h>

inline uint8_t inb(uint16_t port);

inline void outb(uint16_t port, uint8_t val);

#endif