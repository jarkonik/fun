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
    volatile char *prev_line = (char *)VGA_ADDR;
    volatile char *cur_line = prev_line + VGA_WIDTH * 2;

    while (cur_line != VGA_END)
    {
        *(prev_line++) = *(cur_line++);
    }

    while (prev_line != VGA_END)
    {
        *(prev_line++) = 0x0;
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
    init_serial();

    int i = 0;
    while (1)
    {
        print("Iteration: ");
        print(itoa(i, 10));
        print("\n");
        i++;
    }
}
