#include "serial.h"
#include "tty.h"
#include "utils.h"
#include "idt.h"

void main()
{
    init_serial();
    init_idt();

    while (1)
    {
    }
}
