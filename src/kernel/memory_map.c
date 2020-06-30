#include "memory_map.h"
#include "tty.h"
#include "serial.h"

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

// For the first call to the function, point ES:DI at the destination buffer for
// the list. Clear EBX. Set EDX to the magic number 0x534D4150. Set EAX to
// 0xE820 (note that the upper 16-bits of EAX should be set to 0). Set ECX to
// 24. Do an INT 0x15. If the first call to the function is successful, EAX will
// be set to 0x534D4150, and the Carry flag will be clear. EBX will be set to
// some non-zero value, which must be preserved for the next call to the
// function. CL will contain the number of bytes actually stored at ES:DI
// (probably 20). For the subsequent calls to the function: increment DI by your
// list entry size, reset EAX to 0xE820, and ECX to 24. When you reach the end
// of the list, EBX may reset to 0. If you call the function again with EBX = 0,
// the list will start over. If EBX does not reset to 0, the function will
// return with Carry set when you try to access the entry after the last valid
// entry.

void __attribute__((noinline)) __attribute__((regparm(3))) get_memory_map()
{
    uint32_t contID = 0;
    uint32_t signature = 0, bytes;

    print_serial("test");
    asm volatile(
        "int 0x15\n"
        : "=a"(signature), "=c"(bytes), "=b"(contID)
        : "a"(0x0E820), "b"(contID), "c"(24), "d"(0x534D4150), "D"(&smap));
    print_serial("test2");
}
