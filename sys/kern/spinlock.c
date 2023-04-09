#include <spinlock.h>

void 
init_locklock(struct spinlock *l, const char *_name)
{
        l->name = _name;
        l->locked = 0;
        l->cpu = 0;
}

void 
acquire_lock(struct spinlock *l) 
{
       asm volatile("csrr sie, zero");
}
