#include <stddef.h>
#include <spinlock.h>
#include <stdint.h>
#include <string.h>
#include <printf.h>
#include <kalloc.h>
#include <stdio.h>

#define ALIGNPG(n)	(((n) + (uintptr_t)PAGE_SIZE - 1) & ~((uintptr_t)PAGE_SIZE))

extern uint64_t HEAP_START; 

typedef struct freenode {
	struct freenode *next;
} freenode_t;

freenode_t *head = {0};
static spinlock_t mutex;

void *
kalloc(void) 
{
	acquire(&mutex);
	freenode_t *p = head;

	if (p == NULL)
		return NULL;

	head = p->next;
	release(&mutex);
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
	if (p == NULL) {
		return;
	}

	acquire(&mutex);
	freenode_t *tmp = head;
	head = p;
	head->next = tmp;
	release(&mutex);
}

void
kalloc_init(uintptr_t end)
{
	initlock(&mutex);
	freenode_t *p = (freenode_t*)HEAP_START;
	end = ALIGNPG(end);
	for (;(unsigned long)p + PAGE_SIZE <= end; p += PAGE_SIZE) {
		kfree(p);
	}
}

void 
walkfree(void)
{
	freenode_t *node = head;
	int nfree = 0;
	while (node != NULL) {
		printf("freenode at %p\n", node);
		node = node->next;
		nfree++;
	}
	printf("found and printed %d free pages!\n", nfree);
}
