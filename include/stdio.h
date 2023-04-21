#ifndef _STDIO_H
#define _STDIO_H

#include <stdarg.h>

int getc(void);

void putchar(const char); 
void puts(const char *);
void printf(const char *, ...);

#define stdin	0
#define stdout	1
#define stderr	2

#endif /* _STDIO_H */
