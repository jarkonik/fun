#include "idt.h"
#include "serial.h"
#include "io.h"

static const char GDT_SELECTOR = 0x08;

typedef void (*handler_t)();

handler_t handlers[256];

typedef enum
{
    INTERRUPT_GATE = 0x8e
} gate_t;

struct IDT_entry
{
    unsigned short int offset_lowerbits;
    unsigned short int selector;
    unsigned char zero;
    unsigned char type_attr;
    unsigned short int offset_higherbits;
};

struct IDT_entry IDT[256];

static inline void rempap_pic()
{
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 40);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
}

static void irq0_handler()
{
    print_serial("ble");
    outb(0x20, 0x20); //EOI
}

static inline void lidt(void *base, uint16_t size)
{ // This function works in 32 and 64bit mode
    struct
    {
        uint16_t length;
        void *base;
    } __attribute__((packed)) IDTR = {size, base};

    asm("lidt %0"
        :
        : "m"(IDTR));
}

#define DEFINE_IRQ(idx)                     \
    static void irq##idx()                  \
    {                                       \
        asm("pusha");                       \
        asm("call %0" ::"m"(irq0_handler)); \
        asm("popa");                        \
        asm("iret");                        \
    }

#define INIT_IRQ(idx)                                     \
    u32_u16_t irq##idx##_address = (u32_u16_t)irq##idx;   \
    IDT[32].offset_lowerbits = irq##idx##_address.u16[0]; \
    IDT[32].selector = GDT_SELECTOR;                      \
    IDT[32].zero = 0;                                     \
    IDT[32].type_attr = INTERRUPT_GATE;                   \
    IDT[32].offset_higherbits = irq##idx##_address.u16[1];

DEFINE_IRQ(0)
DEFINE_IRQ(1)
DEFINE_IRQ(2)
DEFINE_IRQ(3)
DEFINE_IRQ(4)
DEFINE_IRQ(5)
DEFINE_IRQ(6)
DEFINE_IRQ(7)
DEFINE_IRQ(8)
DEFINE_IRQ(9)
DEFINE_IRQ(10)
DEFINE_IRQ(11)
DEFINE_IRQ(12)
DEFINE_IRQ(13)
DEFINE_IRQ(14)
DEFINE_IRQ(15)

void init_idt()
{
    rempap_pic();

    INIT_IRQ(0)
    INIT_IRQ(1)
    INIT_IRQ(2)
    INIT_IRQ(3)
    INIT_IRQ(4)
    INIT_IRQ(5)
    INIT_IRQ(6)
    INIT_IRQ(7)
    INIT_IRQ(8)
    INIT_IRQ(9)
    INIT_IRQ(10)
    INIT_IRQ(11)
    INIT_IRQ(12)
    INIT_IRQ(13)
    INIT_IRQ(14)
    INIT_IRQ(15)

    void *idt_address = IDT;

    lidt(
        idt_address,
        sizeof(IDT));

    asm("sti");

    print_serial("idt iniitalized");
}
