#pragma once

#define VGA_ADDR 0xb8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_END (VGA_ADDR + VGA_WIDTH * 2 * VGA_HEIGHT)

void print(char *string);
