asm(".code16gcc\n");

#include "memory_map.h"
#include <stdint.h>

typedef struct SMAP_entry
{

    uint32_t BaseL; // base address uint64_t
    uint32_t BaseH;
    uint32_t LengthL; // length uint64_t
    uint32_t LengthH;
    uint32_t Type; // entry Type
    uint32_t ACPI; // extended

} __attribute__((packed)) SMAP_entry_t;
SMAP_entry_t smap;

void __attribute__((noinline)) __attribute__((regparm(3))) read_memory_map()
{
    uint32_t contID = 0;
    uint32_t signature = 0, bytes;

    asm volatile(
        "int 0x15\n"
        : "=a"(signature), "=c"(bytes), "=b"(contID)
        : "a"(0x0E820), "b"(contID), "c"(24), "d"(0x534D4150), "D"(&smap));
}
