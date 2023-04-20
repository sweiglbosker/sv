#ifndef _SPINLOCK_H
#define _SPINLOCK_H

/* fifo ticket lock implementation */ 

typedef struct _spinlock {
	int ticket;
	int turn;
} spinlock_t;

void initlock(spinlock_t *);

void acquire(spinlock_t *);

void release(spinlock_t *);

#endif /* _SPINLOCK_H */
