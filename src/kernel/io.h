#pragma once
#include <stdint.h>

static inline void outb(uint16_t port, uint8_t val)
{
    asm volatile("outb %1, %0"
                 :
                 : "a"(val), "Nd"(port));
}

static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile("inb %0, %1"
                 : "=a"(ret)
                 : "Nd"(port));
    return ret;
}
