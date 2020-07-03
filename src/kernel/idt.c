#include "idt.h"
#include "serial.h"
#include "io.h"
#include "tty.h"
#include "utils.h"

char kbd_US[128] =
    {
        0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
        '\t', /* <-- Tab */
        'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
        0, /* <-- control key */
        'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
        '*',
        0,   /* Alt */
        ' ', /* Space bar */
        0,   /* Caps lock */
        0,   /* 59 - F1 key ... > */
        0, 0, 0, 0, 0, 0, 0, 0,
        0, /* < ... F10 */
        0, /* 69 - Num lock*/
        0, /* Scroll Lock */
        0, /* Home key */
        0, /* Up Arrow */
        0, /* Page Up */
        '-',
        0, /* Left Arrow */
        0,
        0, /* Right Arrow */
        '+',
        0, /* 79 - End key*/
        0, /* Down Arrow */
        0, /* Page Down */
        0, /* Insert Key */
        0, /* Delete Key */
        0, 0, 0,
        0, /* F11 Key */
        0, /* F12 Key */
        0, /* All other keys are undefined */
};

static const char GDT_SELECTOR = 0x08;

typedef void (*irq_handler_t)();

typedef union {
    irq_handler_t irq_handler;
    uint16_t u16[2];
} irq_handler_u;

typedef enum
{
    INTERRUPT_GATE = 0x8e
} gate_t;

typedef struct
{
    uint16_t offset_lowerbits;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_higherbits;
} IDT_entry;

IDT_entry IDT[256];

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

static void exception0_handler()
{
    print_serial("division by zero");
    outb(0x20, 0x20); //EOI
}

static void exception1_handler()
{
    print_serial("division by zero");
    outb(0x20, 0x20); //EOI
}

static void exception2_handler()
{
    outb(0x20, 0x20); //EOI
}

static void exception3_handler()
{
    outb(0x20, 0x20); //EOI
}

static void exception4_handler()
{
    outb(0x20, 0x20); //EOI
}

static void exception5_handler()
{
    outb(0x20, 0x20); //EOI
}

static void exception6_handler()
{
    outb(0x20, 0x20); //EOI
}

static void exception7_handler()
{
    outb(0x20, 0x20); //EOI
}

static void exception8_handler()
{
    outb(0x20, 0x20); //EOI
}

static void exception9_handler()
{
    outb(0x20, 0x20); //EOI
}

static void exception10_handler()
{
    outb(0x20, 0x20); //EOI
}

static void exception11_handler()
{
    outb(0x20, 0x20); //EOI
}

static void exception12_handler()
{
    outb(0x20, 0x20); //EOI
}

static void exception13_handler()
{
    outb(0x20, 0x20); //EOI
}

static void exception14_handler()
{
    outb(0x20, 0x20); //EOI
}

static void exception15_handler()
{
    outb(0x20, 0x20); //EOI
}

static void exception16_handler()
{
    outb(0x20, 0x20); //EOI
}

static void exception17_handler()
{
    outb(0x20, 0x20); //EOI
}

static void exception18_handler()
{
    outb(0x20, 0x20); //EOI
}

static void exception19_handler()
{
    outb(0x20, 0x20); //EOI
}

static void exception20_handler()
{
    outb(0x20, 0x20); //EOI
}

static void exception21_handler()
{
    outb(0x20, 0x20); //EOI
}

static void exception22_handler()
{
    outb(0x20, 0x20); //EOI
}

static void exception23_handler()
{
    outb(0x20, 0x20); //EOI
}

static void exception24_handler()
{
    outb(0x20, 0x20); //EOI
}

static void exception25_handler()
{
    outb(0x20, 0x20); //EOI
}

static void exception26_handler()
{
    outb(0x20, 0x20); //EOI
}

static void exception27_handler()
{
    outb(0x20, 0x20); //EOI
}

static void exception28_handler()
{
    outb(0x20, 0x20); //EOI
}

static void exception29_handler()
{
    outb(0x20, 0x20); //EOI
}

static void exception30_handler()
{
    outb(0x20, 0x20); //EOI
}

static void exception31_handler()
{
    outb(0x20, 0x20); //EOI
}

static void irq0_handler()
{
    outb(0x20, 0x20); //EOI
}

static void irq1_handler()
{
    unsigned char scan_code = inb(0x60);

    if (scan_code < 128)
    {
        char letter = kbd_US[scan_code];
        if (letter != 0)
        {
            char string[2];
            string[0] = letter;
            string[1] = 0;
            print(string);
        }
    }

    outb(0x20, 0x20); //EOI
}

static void irq2_handler()
{
    outb(0x20, 0x20); //EOI
}

static void irq3_handler()
{
    outb(0x20, 0x20); //EOI
}

static void irq4_handler()
{
    outb(0x20, 0x20); //EOI
}

static void irq5_handler()
{
    outb(0x20, 0x20); //EOI
}

static void irq6_handler()
{
    outb(0x20, 0x20); //EOI
}

static void irq7_handler()
{
    outb(0x20, 0x20); //EOI
}

static void irq8_handler()
{
    outb(0xA0, 0x20);
    outb(0x20, 0x20); //EOI
}

static void irq9_handler()
{
    outb(0xA0, 0x20);
    outb(0x20, 0x20); //EOI
}

static void irq10_handler()
{
    outb(0xA0, 0x20);
    outb(0x20, 0x20); //EOI
}

static void irq11_handler()
{
    outb(0xA0, 0x20);
    outb(0x20, 0x20); //EOI
}

static void irq12_handler()
{
    outb(0xA0, 0x20);
    outb(0x20, 0x20); //EOI
}

static void irq13_handler()
{
    outb(0xA0, 0x20);
    outb(0x20, 0x20); //EOI
}

static void irq14_handler()
{
    outb(0xA0, 0x20);
    outb(0x20, 0x20); //EOI
}

static void irq15_handler()
{
    outb(0xA0, 0x20);
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

typedef struct interrupt_frame interrupt_frame_t;

#define DEFINE_IRQ_HANDLER(irq_idx)                                                                \
    __attribute__((interrupt)) void irq##irq_idx(__attribute__((unused)) interrupt_frame_t *frame) \
    {                                                                                              \
        irq##irq_idx##_handler();                                                                  \
    }

#define DEFINE_EXCEPTION_HANDLER(exception_idx)                                                                \
    __attribute__((interrupt)) void exception##exception_idx(__attribute__((unused)) interrupt_frame_t *frame) \
    {                                                                                                          \
        exception##exception_idx##_handler();                                                                  \
    }

static void bind_irq(uint8_t irq, irq_handler_t irq_handler)
{
    irq_handler_u irq_address;
    irq_address.irq_handler = irq_handler;

    uint8_t idx = irq + 32;
    IDT[idx].offset_lowerbits = irq_address.u16[1];
    IDT[idx].selector = GDT_SELECTOR;
    IDT[idx].zero = 0;
    IDT[idx].type_attr = INTERRUPT_GATE;
    IDT[idx].offset_lowerbits = irq_address.u16[0];
}

static void bind_exception(uint8_t exception, irq_handler_t exception_handler)
{
    irq_handler_u irq_address;
    irq_address.irq_handler = exception_handler;

    uint8_t idx = exception;
    IDT[idx].offset_lowerbits = irq_address.u16[1];
    IDT[idx].selector = GDT_SELECTOR;
    IDT[idx].zero = 0;
    IDT[idx].type_attr = INTERRUPT_GATE;
    IDT[idx].offset_lowerbits = irq_address.u16[0];
}

#define BIND_IRQ(irq_idx) \
    bind_irq(irq_idx, irq##irq_idx);

#define BIND_EXCEPTION(exception_idx) \
    bind_exception(exception_idx, exception##exception_idx);

DEFINE_IRQ_HANDLER(0)
DEFINE_IRQ_HANDLER(1)
DEFINE_IRQ_HANDLER(2)
DEFINE_IRQ_HANDLER(3)
DEFINE_IRQ_HANDLER(4)
DEFINE_IRQ_HANDLER(5)
DEFINE_IRQ_HANDLER(6)
DEFINE_IRQ_HANDLER(7)
DEFINE_IRQ_HANDLER(8)
DEFINE_IRQ_HANDLER(9)
DEFINE_IRQ_HANDLER(10)
DEFINE_IRQ_HANDLER(11)
DEFINE_IRQ_HANDLER(12)
DEFINE_IRQ_HANDLER(13)
DEFINE_IRQ_HANDLER(14)
DEFINE_IRQ_HANDLER(15)

DEFINE_EXCEPTION_HANDLER(0)
DEFINE_EXCEPTION_HANDLER(1)
DEFINE_EXCEPTION_HANDLER(2)
DEFINE_EXCEPTION_HANDLER(3)
DEFINE_EXCEPTION_HANDLER(4)
DEFINE_EXCEPTION_HANDLER(5)
DEFINE_EXCEPTION_HANDLER(6)
DEFINE_EXCEPTION_HANDLER(7)
DEFINE_EXCEPTION_HANDLER(8)
DEFINE_EXCEPTION_HANDLER(9)
DEFINE_EXCEPTION_HANDLER(10)
DEFINE_EXCEPTION_HANDLER(11)
DEFINE_EXCEPTION_HANDLER(12)
DEFINE_EXCEPTION_HANDLER(13)
DEFINE_EXCEPTION_HANDLER(14)
DEFINE_EXCEPTION_HANDLER(15)
DEFINE_EXCEPTION_HANDLER(16)
DEFINE_EXCEPTION_HANDLER(17)
DEFINE_EXCEPTION_HANDLER(18)
DEFINE_EXCEPTION_HANDLER(19)
DEFINE_EXCEPTION_HANDLER(20)
DEFINE_EXCEPTION_HANDLER(21)
DEFINE_EXCEPTION_HANDLER(22)
DEFINE_EXCEPTION_HANDLER(23)
DEFINE_EXCEPTION_HANDLER(24)
DEFINE_EXCEPTION_HANDLER(25)
DEFINE_EXCEPTION_HANDLER(26)
DEFINE_EXCEPTION_HANDLER(27)
DEFINE_EXCEPTION_HANDLER(28)
DEFINE_EXCEPTION_HANDLER(29)
DEFINE_EXCEPTION_HANDLER(30)
DEFINE_EXCEPTION_HANDLER(31)

void init_idt()
{
    rempap_pic();

    BIND_EXCEPTION(0)
    BIND_EXCEPTION(1)
    BIND_EXCEPTION(2)
    BIND_EXCEPTION(3)
    BIND_EXCEPTION(4)
    BIND_EXCEPTION(5)
    BIND_EXCEPTION(6)
    BIND_EXCEPTION(7)
    BIND_EXCEPTION(8)
    BIND_EXCEPTION(9)
    BIND_EXCEPTION(10)
    BIND_EXCEPTION(11)
    BIND_EXCEPTION(12)
    BIND_EXCEPTION(13)
    BIND_EXCEPTION(14)
    BIND_EXCEPTION(15)
    BIND_EXCEPTION(16)
    BIND_EXCEPTION(17)
    BIND_EXCEPTION(18)
    BIND_EXCEPTION(19)
    BIND_EXCEPTION(20)
    BIND_EXCEPTION(21)
    BIND_EXCEPTION(22)
    BIND_EXCEPTION(23)
    BIND_EXCEPTION(24)
    BIND_EXCEPTION(25)
    BIND_EXCEPTION(26)
    BIND_EXCEPTION(27)
    BIND_EXCEPTION(28)
    BIND_EXCEPTION(29)
    BIND_EXCEPTION(30)
    BIND_EXCEPTION(31)

    BIND_IRQ(0)
    BIND_IRQ(1)
    BIND_IRQ(2)
    BIND_IRQ(3)
    BIND_IRQ(4)
    BIND_IRQ(5)
    BIND_IRQ(6)
    BIND_IRQ(7)
    BIND_IRQ(8)
    BIND_IRQ(9)
    BIND_IRQ(10)
    BIND_IRQ(11)
    BIND_IRQ(12)
    BIND_IRQ(13)
    BIND_IRQ(14)
    BIND_IRQ(15)

    lidt(
        IDT,
        sizeof(IDT));

    asm("sti");

    print_serial("idt iniitalized\n");
}
