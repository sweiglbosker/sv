#include <stddef.h>
#include <string.h>
#include <mm/kalloc.h>

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
	if (p == NULL || (unsigned long)p % PAGE_SIZE)
		return;

	freenode_t *tmp = head;
	head = p;
	head->next = tmp;
}
