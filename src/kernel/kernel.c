#include "serial.h"
#include "tty.h"
#include "utils.h"
#include "idt.h"
#include "../shared/memory_map.h"

#ifndef OSNAME
#define OSNAME "NO_OSNAME_PROVIDED"
#endif

void main()
{
    init_serial();
    init_idt();

    print(
        "welcome to " OSNAME "\n");

    SMAP_entry_t *buffer = (SMAP_entry_t *)MEMORY_MAP_ADDR;
    print("Detected memory:\n");
    print(itoa(buffer[0].Length / 1024, 10));
    print("kb\n");
    print(itoa(buffer[1].Length / 1024, 10));
    print("kb\n");
    print(itoa(buffer[2].Length / 1024, 10));
    print("kb\n");
    print(itoa(buffer[3].Length / 1024, 10));
    print("kb\n");
    print(itoa(buffer[4].Length / 1024, 10));
    print("kb\n");
    print(itoa(buffer[5].Length / 1024, 10));
    print("kb\n");

    while (1)
    {
    }
}
