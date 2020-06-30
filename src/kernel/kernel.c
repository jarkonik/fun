#include "serial.h"
#include "tty.h"
#include "utils.h"
#include "idt.h"
#include "memory_map.h"

#ifndef OSNAME
#define OSNAME "NO_OSNAME_PROVIDED"
#endif

void main()
{
    init_serial();
    init_idt();

    print(
        "welcome to " OSNAME "\n");

    get_memory_map();

    while (1)
    {
    }
}
