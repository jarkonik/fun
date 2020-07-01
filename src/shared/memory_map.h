#pragma once

typedef struct SMAP_entry
{

    uint64_t Base;   // base address uint64_t
    uint64_t Length; // length uint64_t
    uint32_t Type;   // entry Type
    uint32_t ACPI;   // extended

} __attribute__((packed)) SMAP_entry_t;

void read_memory_map();
