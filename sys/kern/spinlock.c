#include <asm.h>
#include <spinlock.h>

void 
initlock(struct spinlock *l)
{
        l->locked = 0;
}

void 
acquire(struct spinlock *l)
{
	sie_disable();

	if (l->locked)
		return;

	while (__sync_lock_test_and_set(&l->locked, 1))
			;

	__sync_synchronize();
}

void 
release(struct spinlock *l) 
{
	sie_disable(); // avoid deadlock

	if (l->locked)
		return;  // interrupts are still disabled, what to do here?

	/* fence */
	__sync_synchronize();

	__sync_lock_release(&l->locked);

	sie_enable();
}
