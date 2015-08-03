#include "system.h"

unsigned short *textmemptr = (unsigned short *) 0xB8000;
int attrib = 0x0F;
int csr_x = 0, csr_y = 0;

/* Scrolls the screen */
void scroll(void)
{
    unsigned blank, temp;

    /* define blank space */
    blank = 0x20 | (attrib << 8);

    /* scroll up if out of line space */
    if(csr_y >= 25)
    {
        /* move line up by one */
        temp = csr_y - 25 + 1;
        memcpy(textmemptr, textmemptr + (temp * 80), (25 - temp) * 80 * 2);

        /* fill the copied line with blanks now */
        wmemset(textmemptr + ((25 - temp) * 80), blank, 80);
        csr_y = 25 - 1;
    }
}

/* move the cursor (blinking thing) */
void move_csr()
{
    unsigned index;

    /* index = [(y * width) + x] */
    index = (csr_y * 80) + csr_x;

    /* poke the vga controller's crt conrtol register */
    outportb(0x3D4, 14);
    outportb(0x3D5, index >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, index);
}

/* Clears the screen */
void cls()
{
    unsigned blank;
    int i;

    /* define blank space */
    blank = 0x20 | (attrib << 8);

    /* loop through the entire screen matrix setting every point to blank */
    for(i = 0; i < 25; i++)
        wmemset(textmemptr + (i * 80), blank, 80);

    /* set cursor position to the top left, then apply */
    csr_x = 0;
    csr_y = 0;
    move_csr();
}

/* print a single character to the end of the present screen position */
void putch(unsigned char c)
{
    unsigned short *where;
    unsigned att = attrib << 8;

    /* if it's \b, move back 1 */
    if(c == 0x08)
    {
        if(csr_x != 0) csr_x--;
    }
    
    /* if it's a \t, move forward 4 where applicable */
    else if(c == 0x09)
    {
        csr_x = (csr_x + 4) & ~(4 - 1);
    }
    
    /* if it's \r, go back to the beginning of the line */
    else if(c == '\r')
    {
        csr_x = 0;
    }
    
    /* the BIOS handles \n as if it's \n\r, so go down one line, then return
     * to the beginning of it
     */
    else if(c == '\n')
    {
        csr_x = 0;
        csr_y++;
    }
    
    /* greater than, and including 0x20 (space) is a printable character */
    else if(c >= ' ')
    {
        where = textmemptr + (csr_y * 80 + csr_x);
        *where = c | att;
        csr_x++;
    }

    /* if the cursor reaches the end of the screen, insert a new line */
    if(csr_x >= 80)
    {
        csr_x = 0;
        csr_y++;
    }

    /* scroll the screen if it's needed, and move the cursor */
    scroll();
    move_csr();
}

/* print a string of characters */
void puts(unsigned char *text)
{
    int i;
    
    int length = 0;
    
    while(1) {
        if(text[length] == '\0')
            break;
        
        length++;
    }
    
    for(i = 0; i < length; i++)
    {
        putch(text[i]);
    }
}

/* set foreground and background */
void settextcolor(unsigned char forecolor, unsigned char backcolor)
{
    attrib = (backcolor << 4) | (forecolor & 0x0F);
}
