#include "system.h"

/* set up descriptor in GDT */
void gdt_set_gate(int num, unsigned long base, unsigned long limit,
        unsigned char access, unsigned char gran)
{
    /* base address */
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    /* descriptor limits */
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    /* granularity and access flags */
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}

/* called by kmain() - will initialise the GDT */
void gdt_init()
{
    /* set up GDT pointer and limit */
    gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gp.base = &gdt;

    /* NULL descriptor */
    gdt_set_gate(0, 0, 0, 0, 0);

    /* second entry (code segment):
     * base address : 0
     * limit        : 4GB (FFFFFFFF)
     * opcodes      : 32-bit
     * granularity  : 4KB
     */
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    /* third entry (data segment):
     * same as above, just another descriptor
     */
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    /* set changes */
    gdt_flush();
    
    /* print out success */
    puts("Global Descriptor Table (GDT) initialised\n");
}
