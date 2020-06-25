#include <stdint.h>

#define VGA_ADDR 0xb8000
#define VGA_WIDTH 90

volatile char *vga = (char *)VGA_ADDR;

static inline void outb(uint16_t port, uint8_t val)
{
    asm volatile("outb %0, %1"
                 :
                 : "a"(val), "Nd"(port));
}

void print_char(char c)
{
    *vga++ = c;
    *vga++ = 0x0a;
}

void set_cursor_pos(int x, int y)
{
    uint16_t pos = y * VGA_WIDTH + x;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

void print_string(char *string)
{
    while (*string != 0)
    {
        print_char(*string);
        string++;
    }
}

void main()
{
    print_string("> Hello, world!");
    set_cursor_pos(10, 10);

    while (1)
    {
    }
}
