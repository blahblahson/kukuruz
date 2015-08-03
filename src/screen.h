#ifndef __SCREEN_H
#define __SCREEN_H

extern void cls();
extern void move_csr();
extern void putch(unsigned char);
extern void puts(unsigned char *);
extern void settextcolor(unsigned char, unsigned char);

#endif /* __SCREEN_H */
