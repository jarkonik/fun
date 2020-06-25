#include "kernel.h"
#include "serial.h"
#include "utils.h"

int cur_x = 0;
int cur_y = 0;

void set_cursor_pos(int x, int y)
{
    uint16_t pos = y * VGA_WIDTH + x;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

void scroll_down()
{
    volatile char *vga = (char *)VGA_ADDR + VGA_WIDTH * 2;

    while (vga != VGA_ADDR + VGA_HEIGHT * VGA_WIDTH * 2)
    {
        *(vga - VGA_WIDTH * 2) = *vga;
        vga++;
    }
    vga -= VGA_WIDTH * 2;
    while (vga != VGA_ADDR + VGA_HEIGHT * VGA_WIDTH * 2)
    {
        *vga = 0x0;
        vga++;
    }
}

void print(char *string)
{
    if (cur_y >= VGA_HEIGHT)
    {
        scroll_down();
        cur_y--;
    }

    volatile char *vga = (char *)VGA_ADDR + 2 * cur_x + cur_y * VGA_WIDTH * 2;

    while (*string != 0)
    {
        if (*string == 10 || cur_x >= VGA_WIDTH)
        {
            cur_x = 0;
            cur_y++;
            string++;
            continue;
        }
        cur_x++;
        *vga++ = *string;
        *vga++ = 0x0a;
        string++;
    }
    set_cursor_pos(cur_x, cur_y);
}

char *itoa(int val, int base)
{
    static char buf[32] = {0};

    int i = 30;

    for (; val && i; --i, val /= base)

        buf[i] = "0123456789abcdef"[val % base];

    return &buf[i + 1];
}

void main()
{
    int i = 0;
    while (1)
    {
        print("Hello, world:");
        print(itoa(i, 10));
        print("\n");
        i++;
    }
}
