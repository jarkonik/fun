#include "serial.h"
#include "tty.h"
#include "utils.h"
#include "idt.h"
#include "../shared/memory_map.h"

#ifndef OSNAME
#define OSNAME "NO_OSNAME_PROVIDED"
#endif

extern SMAP_entry_t memory_map_start[];
extern uint32_t memory_map_entries_count;

void main()
{
    init_serial();
    init_idt();

    print(
        "welcome to " OSNAME "\n");

    print("Detected memory:\n");
    int total_memory = 0;
    for (uint32_t i = 0; i < memory_map_entries_count; i++)
    {
        total_memory += memory_map_start[i].Length;
    }
    print(itoa(total_memory / 1024 / 1024, 10));
    print("MB\n");

    while (1)
    {
    }
}
