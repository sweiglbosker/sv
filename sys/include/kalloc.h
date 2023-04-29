#ifndef _KALLOC_H
#define _KALLOC_H

#include <stdint.h>

void *kalloc(void);

void *kzalloc(void);

void kfree(void *);

void kalloc_init(uintptr_t end);

void walkfree(void);

#endif /* _KALLOC_H */

