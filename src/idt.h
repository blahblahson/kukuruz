/* define IDT entry - stop compiler from messing up stuff by packing */
struct idt_entry
{
    unsigned short base_lo;
    unsigned short sel;        /* kernel segment goes here */
    unsigned char always0;     /* always 0 */
    unsigned char flags;
    unsigned short base_hi;
} __attribute__((packed));

/* IDT pointer */
struct idt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

/* IDT of 256 entries - although only 32 are used, the rest catch exceptions */
struct idt_entry idt[256];
struct idt_ptr idtp;

/* defined in start.asm */
extern void idt_load();

/* prototypes */
void idt_set_gate(unsigned char, unsigned long, unsigned short, unsigned char);
void idt_init();
