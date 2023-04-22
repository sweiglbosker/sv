#ifndef _STRING_H
#define _STRING_H

#include <stddef.h>
#define NULL ((void*)0)

extern void *memcpy(void *__restrict, const void *__restrict, size_t);
void *memmove(void *, const void *, size_t);
void *memset(void *, int, size_t);
int memcmp(const void *, const void *, size_t);
void *memchr(const void *, int, size_t);

char *strchr(const char *, int);
char *strrchr(const char*, int);

size_t strlen(const char *);
size_t strnlen(const char *, size_t);
#endif /* _STRING_H */
