#include <libfdt.h>
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

	printf("setting up the heap at %p\n", HEAP_START);
	kalloc_init();
	printf_init();
	printf("done!\n");

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

