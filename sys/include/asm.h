#ifndef _ASM_H 
#define _ASM_H 

#include <stdint.h>

#define SSTATUS_SIE      (1L << 1)

static inline uint64_t 
csrr_sstatus(void) 
{
        uint64_t x;
        asm volatile("csrr %0, sstatus" : "=r"(x));
        return x;
}

static inline void 
csrw_sstatus(uint64_t x) 
{
        asm volatile("csrw sstatus, %0" : : "r"(x));
}

/* will enable all supervisor interrupts using the bit in sstatus */
static inline void 
sie_enable(void) 
{
        csrw_sstatus(csrr_sstatus() | SSTATUS_SIE);
}

/* will disable all supervisor interrupts by using the bitin sstatus (though sie can also be used) */
static inline void 
sie_disable(void) 
{
        csrw_sstatus(csrr_sstatus() & ~SSTATUS_SIE);
}

/* returns the status of the sie bit in sstatus 
 * 1 if enabled, 0 if disabled.
 * for more specific info see the sie register 
 */
static inline uint64_t
sie_status() 
{
        return (csrr_sstatus() & SSTATUS_SIE) != 0;
        
}

/* we use tp to store hartid */ 
static inline uint64_t 
read_tp(void) 
{
        uint64_t x;
        asm volatile("addi %0, tp, 0" : "=r"(x));
	return x;
}

static inline void 
csrw_satp(uint64_t x)
{
	asm volatile("csrw satp, %0" : : "r"(x));
}

#endif /* _ASM_H */ 
