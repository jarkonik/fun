#pragma once
#include <stddef.h>
#include <stdint.h>

static uint16_t *const VGA_ADDR = (uint16_t *)0xb8000;
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t *const VGA_END = VGA_ADDR + VGA_WIDTH * 2 * VGA_HEIGHT;

void print(char *string);
