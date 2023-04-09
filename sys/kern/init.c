#include <fdt.h>
#include <mm/kalloc.h>
#include <printf.h>
#include <stdint.h>
#include <spinlock.h>

extern uint64_t HEAP_START;

void 
init(unsigned long hartid, struct fdt_header *fdt)
{

	printf("booting from hart #%d\n", hartid);
        asm volatile ("mv tp, %0" : : "r"(hartid));
	if (fdt_uint32(fdt->magic) == FDT_HEADER_MAGIC) 
		printf("found flattened device tree at %p!\n", (uint64_t)fdt);
        
        printf("parsing device tree!\n");
        fdt_walk(fdt);

        printf("setting up the heap at %p\n", HEAP_START);
        kalloc_init();
        printf("done!\n");
       // printf("printing free pages:\n");
        //walkfree();
}

/* non boot harts enter here */ 
void 
mpinit(unsigned long hartid, struct fdt_header *fdt)
{
        unsigned char *uart = (unsigned char*)0x10000000;
        *uart = hartid + '0';
        *(uart + 1) = '\n';
}
