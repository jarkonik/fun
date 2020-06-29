#include "serial.h"
#include "tty.h"
#include "utils.h"
#include "idt.h"

#ifndef OSNAME
#define OSNAME "NO_OSNAME_PROVIDED"
#endif

void main()
{
    init_serial();
    init_idt();

    print(
        "welcome to " OSNAME "\n");

    while (1)
    {
    }
}
