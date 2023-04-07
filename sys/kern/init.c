#include <fdt.h>
#include <printf.h>
#include <stdint.h>
#include <mm/kalloc.h>

extern uint64_t HEAP_START;

void 
init(unsigned long hartid, struct fdt_header *fdt)
{
	printf("booting from hart #%d\n", hartid);
	if (fdt_uint32(fdt->magic) == FDT_HEADER_MAGIC) 
		printf("found flattened device tree at %p!\n", (uint64_t)fdt);
        
        printf("setting up the heap at %p\n", HEAP_START);
        kalloc_init();
        printf("done!\n");
        printf("printing free pages:\n");
        walkfree();
}
