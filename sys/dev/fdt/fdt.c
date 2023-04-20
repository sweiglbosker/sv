#include <fdt.h>
#include <sbi.h>
#include <printf.h>
#include <stdint.h>

void    
fdt_walk(struct fdt_header *header) 
{
	if (fdt_uint32(header->magic) != FDT_HEADER_MAGIC) {
		printf("corrupted or invalid fdt");
	}
	printf("parsing fdt @%p...\n", header);
	printf("header->totalsize: %d\n", fdt_uint32(header->totalsize));
	printf("header->off_dt_struct: %d\n", fdt_uint32(header->off_dt_struct));
	printf("header->off_dt_strings: %d\n", fdt_uint32(header->off_dt_strings));
	printf("header->off_mem_rsvmap: %d\n", fdt_uint32(header->off_mem_rsvmap));
	printf("header->version: %d\n", fdt_uint32(header->version));
	printf("header->last_comp_version: %d\n", fdt_uint32(header->last_comp_version));
	printf("header->boot_cpuid_phys: %d\n", fdt_uint32(header->boot_cpuid_phys));
	printf("header->size_dt_strings: %d\n", fdt_uint32(header->size_dt_strings));
	printf("header->size_dt_struct: %d\n",  fdt_uint32(header->size_dt_struct));

	printf("walking the memory reservation block...\n");
	struct fdt_reserve_entry *p = header + fdt_uint32(header->off_mem_rsvmap);
//	do {
//		printf("reserved entry at %p with size %i\n", p->address, p->size);
//		p++;
//	} while (!(p->size == 0 && p->address == 0));
}
