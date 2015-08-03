#include "system.h"

/* US keyboard keymap */
unsigned char kb_us[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',                      /* 9 */
  '9', '0', '-', '=', '\b',                                      /* backspace */
  '\t',                                                                /* Tab */
  'q', 'w', 'e', 'r',                                                   /* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',                      /* enter */
    0,                                                      /* 29   - control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',                     /* 39 */
 '\'', '`',   15,                                               /* left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',                                    /* 49 */
  'm', ',', '.', '/',   15,                                    /* right shift */
  '*',
    16,                                                                /* alt */
  ' ',                                                           /* space bar */
    17,                                                          /* caps lock */
    1,                                                   /* 59 - F1 key ... > */
    2, 3, 4, 5, 6, 7, 8, 9,
    10,                                                          /* < ... F10 */
    29,                                                       /* 69 - num lock*/
    30,                                                        /* scroll lock */
    13,                                                               /* home */
    14,                                                                 /* up */
    15,                                                            /* page up */
  '-',
    18,                                                               /* left */
    19,
    20,                                                              /* right */
  '+',
    21,                                                           /* 79 - end */
    22,                                                               /* down */
    23,                                                          /* page down */
    24,                                                             /* insert */
    25,                                                             /* delete */
    26,   27,   28,
    11,                                                                /* F11 */
    12,                                                                /* F12 */
    31,                                       /* all other keys are undefined */
} ;

/* global status variables */
short capslock = 0;
short numlock = 0;
short scrllock = 0;
short shift = 0;
short control = 0;
short alt = 0;

/* for gets() */
int read_i; 

/* set kb handler to IRQ1 */
void keyboard_init()
{
    irq_install_handler(1, keyboard_handler);
    puts("Keyboard handler initialised\n");
}

/* handle keyboard interrupt */
void keyboard_handler(struct regs *r)
{
    //unsigned char scancode;

    /* read from the keyboard's data buffer */
    //scancode = inportb(0x60);    

 //if(get_read_state())
 //{
    //if(kb_us[scancode] == '\n')
    //{
    //  set_read_state(); 
    //}

    //if(!(scancode & 0x80))
    //{
    //   putch(kb_us[scancode]);
    //}
 //}
}

char getch()
{
    unsigned char scancode = 0;
    unsigned char kb_status = 0;   
    
    while(scancode == 0) {
        kb_status = inportb(0x64);

        if(kb_status&1)
            scancode = inportb(0x60);
    }     

    if(!(scancode & 0x80)) {
        if(kb_us[scancode] == '\t') {
            if(read_i > 0) {
                putch(' '); 
                putch(' ');
                putch(' ');
                putch(' ');
            }
            
            return kb_us[scancode];
        }
        else if(kb_us[scancode] == '\b') {
            if(read_i > 0) {
                putch('\b'); 
                putch(' ');
                putch('\b');
            }
            
            return kb_us[scancode];
        } 
        
        if(kb_us[scancode] != 15)
            putch(kb_us[scancode]); 
        return kb_us[scancode];
    }
   
    return 0;
}

void gets(char* buffer, int read)
{
   
   
    memset(buffer, 0, read);

    for(read_i=0; read_i<read; )
    {
        if((buffer[read_i] = getch())) {
            /* new-line condition */
            if(buffer[read_i] == '\n') {
                buffer[read_i] = '\0';
                return;
            }
            /* backspace handler; similar to the newline condition, but don't
             * return
             */
            else if(buffer[read_i] == '\b') {
                if(read_i > 0) {
                    --read_i;
                    buffer[read_i] = '\0';
                }
            }
            /* printable condition; this stops non-printable values being
             * assumed, e.g. F1
             */
            else if(buffer[read_i] < 32 || buffer[read_i] > 126)
                continue;
            /* else, increment and continue */
            else
                ++read_i;
        }
    }
}
