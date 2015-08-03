#include "system.h"

/* main function - sits in idle loop forever */
void kmain() /* called kmain() because main() can conflict with other stuff */
{
    gdt_init(); /* initialise GDT */
    idt_init(); /* initialise IDT */
    isrs_init(); /* initialise ISRs */
    irq_init(); /* initialise IRQs */
    __asm__ __volatile__ ("sti"); /* allow IRQs to happen */
    timer_init(); /* initialise the timer handler to IRQ0 */
    keyboard_init(); /* initialise the keyboard handler to IRQ1 */

    /* boot screen */
    puts("\nKukuruz Kernel ready!\n\n"
            "Kukuruz Kernel/Operating System,\n"
            "Copyright (C) 2006 Alvin Sipraga, Calvin Southwood\n"
            "Kukuruz comes with ABSOLUTELY NO WARRANTY. "
            "This is free software,\nand you are welcome "
            "to redistribute it under certain conditions;\nsee COPYING "
            "for details.\n");
    
    char buffer[100];
                        
    while(1)
    {
      puts("\nkuk $ ");
      gets(buffer, 100);
      puts("You entered: ");
      puts(buffer);
    }
}
