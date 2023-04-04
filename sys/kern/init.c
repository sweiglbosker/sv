#include <fdt.h>
#include <kernel_earlyprintf.h>

void 
init(unsigned long hartid, struct fdt_header *fdt)
{
	kernel_earlyputs("booting...\n");
	if (fdt_uint32(fdt->magic) == FDT_HEADER_MAGIC) 
		kernel_earlyputs("found flattened device tree!\n");

}
