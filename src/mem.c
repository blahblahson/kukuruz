#include "system.h"

/* memcpy - copy n bytes from s2 into s1 */
void *memcpy(void *dest, const void *src, int count)
{
    const char *sp = (const char *) src;
    char *dp = (char *) dest;
    
    for(; count != 0; count--)
        *dp++ = *sp++;
    
    return dest;
}

/* memset - copy c into the first n bytes of s */
void *memset(void *dest, char val, int count)
{
    char *temp = (char *) dest;
    
    for( ; count != 0; count--)
        *temp++ = val;
    
    return dest;
}

/* wmemset - copy c into the first n bytes of s */
unsigned short *wmemset(unsigned short *dest, unsigned short val, int count)
{
    unsigned short *temp = (unsigned short *) dest;
    
    for( ; count != 0; count--)
        *temp++ = val;
    
    return dest;
}

/* strlen - size of a string */
int strlen(const char *str)
{
    const char *ss = str;
    
    while(*ss)
        ss++;
    
    return ss-str;
}
