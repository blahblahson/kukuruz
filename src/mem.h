#ifndef __MEM_H
#define __MEM_H

extern void *memcpy(void *dest, const void *src, int count);
extern void *memset(void *dest, char val, int count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val,
        int count);
extern int strlen(const char *str);

#endif /* __MEM_H */
