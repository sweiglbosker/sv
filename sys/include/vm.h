#ifndef _VM_H
#define _VM_H

#include <stdint.h>

#define PAGEBITS_VALID    (1 << 0)
#define PAGEBITS_R        (1 << 1)
#define PAGEBITS_W        (1 << 2)
#define PAGEBITS_X        (1 << 3)
#define PAGEBITS_USER     (1 << 4)
#define PAGEBITS_GLOBAL   (1 << 5)
#define PAGEBITS_ACCESSED (1 << 6)
#define PAGEBITS_DIRTY    (1 << 7)

#define PAGEBITS_RO	PAGEBITS_R
#define PAGEBITS_XO	PAGEBITS_X
#define PAGEBITS_RW	(PAGEBITS_R | PAGEBITS_W)
#define PAGEPITS_RX	(PAGEBITS_R | PAGEBITS_X)
#define PAGEBITS_RWX	(PAGEBITS_R | PAGEBITS_W | PAGEBITS_X)

#define MODE_SV39 	(8L << 60)

typedef uint64_t pt_entry_t;
typedef struct _pagetable {
	pt_entry_t entries[512];
} pagetable_t; 

/* allocate kernel pagetable */ 
void kptinit(void);
void kptinithart(void);
//void kptinitharts(uintptr_t mask);

/* maps virtual address to physical address for @pt. */
void vmap(pagetable_t *root, uintptr_t vaddr, uintptr_t paddr, int bits, int level);

/* returns address of page table entry for @vaddr. if @alloc, next level page tables will be allocated */ 
pt_entry_t *walkpt(pagetable_t *root, uintptr_t vaddr, int alloc);

/* helper functions */
static inline void write_satp(uintptr_t mode, uintptr_t ppn);
static inline int pte_is_branch(pt_entry_t);
static inline int pte_is_valid(pt_entry_t);

#define PA2PTE(pa) ((uintptr_t)pa >> 2)
#define PTE2PA(pa) ((uintptr_t)pa << 2)
#define FLUSH_TLB() asm volatile("sfence.vma zero, zero")

static inline void 
write_satp(uintptr_t mode, uintptr_t ppn)
{
	FLUSH_TLB();
	asm volatile("csrw satp, %0" : : "r"((ppn >> 12) | mode));
	FLUSH_TLB();
}

static inline int
pte_is_branch(pt_entry_t e)
{
	return ((e & PAGEBITS_RWX) == 0);
}
#define pte_is_leaf(e) (!pte_is_branch(e))

static inline int
pte_is_valid(pt_entry_t e)
{
	return (e & PAGEBITS_VALID);
}


#endif /* _VM_H */
