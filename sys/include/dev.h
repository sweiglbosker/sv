#ifndef _DEV_H
#define _DEV_H

#include <libfdt.h>
#include <stdint.h> 

enum { DT_MMUTYPE_SV32, DT_MMUTYPE_SV39, DT_MMUTYPE_SV48 };

struct _reg {
	fdt64_t address;
	fdt64_t size;
};
/* unflattend device tree */ 
struct devicetree {
	const char *compat;
	const char *model;
	int nproc;
	/* main cpu, monitor/alternative cores will be ignored for now */
	struct {
		short mmu_type;
		const char *isa;
		unsigned int freq;
	} cpu;
	struct {
		uintptr_t origin;
	 	uintptr_t size;
	} memory;
	struct {
		unsigned int freq;
		const char *compat;
		int interrupt;
		struct _reg reg;
	} uart;
};

struct devicetree dev_init(struct fdt_header* fdt);

#endif /* _DEV_H */
