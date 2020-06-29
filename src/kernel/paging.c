#include "paging.h"
#include <stdint.h>

uint32_t page_directory[1024] __attribute__((aligned(4096)));

void init_paging()
{
    for (int i = 0; i < 1024; i++)
    {
        // This sets the following flags to the pages:
        //   Supervisor: Only kernel-mode can access them
        //   Write Enabled: It can be both read from and written to
        //   Not Present: The page table is not present
        page_directory[i] = 0x00000002;
    }
}
