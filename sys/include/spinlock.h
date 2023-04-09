#ifndef _LOCK_H
#define _LOCK_H

struct spinlock {
        int locked;
        const char *name;
};

void initlock(struct spinlock *, const char *);

#endif /* _LOCK_H */
