#ifndef _KALLOC_H
#define _KALLOC_H

void *kalloc(void);

void *kzalloc(void);

void kfree(void *);

void kalloc_init(size_t);

void walkfree(void);

#endif /* _KALLOC_H */

