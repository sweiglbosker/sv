#ifndef _CPU_H 
#define _CPU_H 

struct hart {
        int intr_stack;
};

struct hart harts[NPROC] = {0};

#endif /* _CPU_H */
