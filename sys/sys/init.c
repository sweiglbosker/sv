#include <dev.h>
#include <libfdt.h>
#include <string.h>
#include <kalloc.h>
#include <spinlock.h>
#include <stdio.h>
#include <printf.h>
#include <sbi.h>
#include <stdint.h>

extern uint64_t HEAP_START;

#define HLT()\
	for (;;)\
		asm("wfi")

void
init(unsigned long hartid, struct fdt_header *fdt)
{

	printf("booting from hart #%d\n", hartid);

	printf_init();
	printf("done!\n");

	struct devicetree dt = dev_init(fdt);

	printf("setting up page frame allocator at %p\n", HEAP_START);
	kalloc_init(dt.memory.origin + dt.memory.size);
	printf("done!\n");

//	walkfree();

	printf("bringing up other harts...\n");
	for (int i = 0; i < NPROC; ++i) {
		if (i == hartid) { 
			printf("skipping hart #%d\n", i);
			continue;
		}
		printf("starting hart #%d\n", i); 
		struct sbiret r = _start_hart(i, (unsigned long)LOAD_ADDR);
		if (r.err != SBI_SUCCESS)
			printf("ERROR");
	}
}

void
mpinit(unsigned long hartid)
{
	printf("mpinit: %d", hartid);
	HLT();
}

