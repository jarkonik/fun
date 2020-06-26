#include <stdint.h>
#include "tty.h"
#include "io.h"

static size_t cur_x = 0;
static size_t cur_y = 0;

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
    volatile uint16_t *prev_line = VGA_ADDR;
    volatile uint16_t *cur_line = prev_line + VGA_WIDTH * 2;

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
