#include <vm.h>
#include <stddef.h>
#include <kalloc.h>
#include <stdio.h>
#include <asm.h>

pagetable_t *kpt;

#define VPN(vaddr, level) \
	(((uintptr_t)vaddr >> (12 + (9 * level))) & 0x1ff)

#define PPN(paddr, level) \
	(((uintptr_t)paddr >> (12 + (9 * level))) & \
		((level == 2) ? 0x3ffffff : 0x1ff))

void 
kptinit(void)
{
	kpt = kzalloc();
}

void 
kptinithart(void)
{
	FLUSH_TLB();
	write_satp(MODE_SV39, (uintptr_t)kpt); 
	FLUSH_TLB();
}

void 
vmap(pagetable_t *root, uintptr_t vaddr, uintptr_t paddr, int bits, int level)
{
	if (pte_is_branch(bits))
		printf("error: pte_is_branch\n"); return;

	pt_entry_t *e = walkpt(root, vaddr, 1);
	if (pte_is_valid(*e))
		printf("warning: mapping already exists for this address\n");

	*e = PA2PTE(paddr) | PAGEBITS_VALID | bits;
}

pt_entry_t *
walkpt(pagetable_t *root, uintptr_t vaddr, int alloc) {
	pt_entry_t *pt = root->entries;
	for (int level = 2; level > 0; level--) {
		pt_entry_t *e = &pt[VPN(vaddr, level)];
		if (!pte_is_valid(*e)) {
			if (!alloc)
				return NULL;
			pt = kzalloc();
			*e = PA2PTE(pt) | PAGEBITS_VALID;
			continue;
		}
		pt = (pt_entry_t *)PTE2PA(*e);

	}
	/* now we should be at level 0, and e should point to our entry */ 
	return &pt[VPN(vaddr, 0)];
}
