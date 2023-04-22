#include <dev.h>
#include <libfdt.h>
#include <sbi.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

void
dev_init(struct fdt_header *fdt)
{
	if (fdt_check_header(fdt) == 0) 
		printf("[dev_init] valid fdt at %p\n", fdt);
	else
		printf("[dev_init] error: fdt_check_header()\n");

	int offset = fdt_next_node(fdt, offset, 0);
	do {
		printf("[dev_init] found %s\n", fdt_get_name(fdt, offset, NULL));
		offset = fdt_next_node(fdt, offset, 0);
	} while (offset != -FDT_ERR_NOTFOUND);
}

