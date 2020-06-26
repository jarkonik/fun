#include "serial.h"
#include "tty.h"
#include "utils.h"

void main()
{
    init_serial();

    int i = 0;
    while (1)
    {
        print("Iteration: ");
        print(itoa(i, 10));
        print("\n");
        i++;
    }
}
