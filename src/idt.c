#include "system.h"

/* set IDT entry */
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel,
        unsigned char flags)
{
    /* interrupt routine's base address */
    idt[num].base_lo = (base & 0xFFFF);
    idt[num].base_hi = (base >> 16) & 0xFFFF;

    /* segment + access flags */
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

/* initialise IDT */
void idt_init()
{
    /* set pointer */
    idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
    idtp.base = &idt;

    /* clear out IDT with 0's */
    memset(&idt, 0, sizeof(struct idt_entry) * 256);

    /* point the processor's internal register to the new IDT */
    idt_load();
    
    /* print success */
    puts("Interrupt Descriptor Table (IDT) initialised\n");
}
