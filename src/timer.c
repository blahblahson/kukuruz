#include "system.h"

// Variable to keep track of how many ticks have passed since the system started.
int timer_ticks = 0;

// Function to set the timer rate.
void timer_phase(int hz)
{
    int divisor = 1193180 / hz;       /* Calculate divisor */
    outportb(0x43, 0x36);             /* Set command byte 0x36 */
    outportb(0x40, divisor & 0xFF);   /* Set low byte of divisor */
    outportb(0x40, divisor >> 8);     /* Set high byte of divisor */
}

// Handles the timer.
void timer_handler(struct regs *r)
{
    /* Increment tick count */
    timer_ticks++;

    // Code to be executed every second can be placed here.
  /* if (timer_ticks % 100 == 0)
    {
      puts("Yay!\n");  
    } */ 
}

// Install the timer handles to IRQ 0
void timer_init()
{
    timer_phase(100); //Data rate set to 100Hz
    irq_install_handler(0, timer_handler);
    puts("Timer handler initialised\n");
}

// Wait function (100 ticks per second)
void timer_wait(int ticks)
{
    unsigned long eticks;

    eticks = timer_ticks + ticks;
    while(timer_ticks < eticks)
    {
     
    }
    
}
