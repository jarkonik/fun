#include <stdint.h>
#include "memory_map.h"

extern SMAP_entry_t memory_map_start;

void read_memory_map()
{
    SMAP_entry_t *buffer = &memory_map_start;

    int smap_size = 0x2000;
    int maxentries = smap_size / sizeof(SMAP_entry_t);
    int contID = 0;
    int entries = 0, signature, bytes;

    do
    {
        __asm__ __volatile__("int 0x15"
                             : "=a"(signature), "=c"(bytes), "=b"(contID)
                             : "a"(0xE820), "b"(contID), "c"(24), "d"(0x534D4150), "D"(buffer));
        if (signature != 0x534D4150)
            asm("hlt");

        if (bytes > 20 && (buffer->ACPI & 0x0001) == 0)
            continue;

        buffer++;
        entries++;
    } while (contID != 0 && entries < maxentries);
}
