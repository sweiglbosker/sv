#include <vm.h>
#include <asm.h>

#define SV39 (8L << 60)

void
vminit(void)
{
	csrw_satp(SATP, (uint64_t)pt >> 12);
}
