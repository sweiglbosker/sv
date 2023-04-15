#ifndef _LOCK_H
#define _LOCK_H

struct spinlock {
        int locked;
	int tp;
};

void initlock(struct spinlock *);

void acquire(struct spinlock *);

void release(struct spinlock *);

#endif /* _LOCK_H */
