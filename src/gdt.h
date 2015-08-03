/* define GDT entry - stop compiler from messing up stuff by packing */
struct gdt_entry
{
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_middle;
    unsigned char access;
    unsigned char granularity;
    unsigned char base_high;
} __attribute__((packed));

/* GDT pointer - includes limit (limit = max bytes taken up by GDT - 1) */
struct gdt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

/* the GDT with 3 entries + GDT pointer */
struct gdt_entry gdt[3];
struct gdt_ptr gp;

/* defined in start.asm */
extern void gdt_flush();

/* prototypes */
void gdt_init();
void gdt_set_gate(int, unsigned long, unsigned long, unsigned char,
        unsigned char);
