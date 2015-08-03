#ifndef __KB_H
#define __KB_H

/* prototypes */
void keyboard_handler(struct regs *r);
void keyboard_init();
char getch();
void gets(char *buffer, int read);


#endif /* __KB_H */
