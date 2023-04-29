#include <dev.h>
#include <libfdt.h>
#include <sbi.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>


static void
mem_init(struct fdt_header *fdt, struct devicetree *dt)
{

	int memory = fdt_path_offset(fdt, "/memory");
	if (memory < 0)
		printf("[dev_init] failed to find memory node\n");

	int len;

	struct _reg *val = fdt_getprop(fdt, memory, "reg", &len);
	/* bad idea */
	dt->memory.origin = fdt64_to_cpu(val->address);
	dt->memory.size = fdt64_to_cpu(val->size);
	printf("[mem_init] found %dMB of memory at %p\n", dt->memory.size >> 20, dt->memory.origin);

	int n = fdt_num_mem_rsv(fdt);
	printf("[mem_init] found %d memory reserve map entries\n", n);
}

static void
cpu_init(struct fdt_header *fdt, struct devicetree *dt)
{

	int cpus = fdt_path_offset(fdt, "/cpus");
	if (cpus < 0)
		printf("[dev_init] failed to find cpus node\n");

	int node = 0;
	fdt_for_each_subnode(node, fdt, cpus) {
		
	}
}

struct devicetree
dev_init(struct fdt_header *fdt) 
{
	struct devicetree dt = {0};

	if (fdt_check_header(fdt) == 0) 
		printf("[dev_init] valid fdt at %p\n", fdt);
	else
		printf("[dev_init] error: fdt_check_header()\n");

	printf("[dev_init] detecting memory...\n");
	mem_init(fdt, &dt);
	cpu_init(fdt, &dt);

//	int offset = fdt_next_node(fdt, offset, 0);
//	do {
//		printf("[dev_init] found %s\n", fdt_get_name(fdt, offset, 0));
//		offset = fdt_next_node(fdt, offset, 0);
//	} while (offset != -FDT_ERR_NOTFOUND);
	return dt;
}

