#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <printf.h>
#include <mm/kalloc.h>

extern uint64_t HEAP_START; 

typedef struct freenode {
	struct freenode *next;
} freenode_t;

freenode_t *head = NULL;

void *
kalloc(void) 
{
	freenode_t *p = head;

	if (p == NULL)
		return NULL;

	head = p->next;
	return p;
}

void *
kzalloc(void)
{
	freenode_t *p = kalloc();
	memset(p, 0, PAGE_SIZE);
	return p;
}

void
kfree(void *p)
{
	if (p == NULL)
		return;

	freenode_t *tmp = head;
	head = p;
	head->next = tmp;
}

void
kalloc_init(void)
{
        freenode_t *p = (freenode_t*)HEAP_START;
        for (;(unsigned long)p + PAGE_SIZE <= (HEAP_START + 0x100000); p += PAGE_SIZE) {
                kfree(p);
        }
}

void 
walkfree(void)
{
        freenode_t *node = head;
        int nfree = 0;
        while (node) {
                printf("freenode at %p\n", node);
                node = node->next;
                nfree++;
        }
        printf("found and printed %d free pages!\n", nfree);
}
