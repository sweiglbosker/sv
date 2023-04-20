#include <stdint.h>
#include <endian.h>
#include <printf.h>

#ifndef _FDT_H
#define _FDT_H

#define FDT_HEADER_MAGIC        0xd00dfeed

static inline uint32_t
fdt_uint32(uint32_t x)
{
#if BYTE_ORDER == LITTLE_ENDIAN
return __bswap32(x);
#else
return x;
#endif
}

struct fdt_header {
        uint32_t magic;                 /* FDT_HEADER_MAGIC */
        uint32_t totalsize;             /* size of the whole device tree, in bytes */
        uint32_t off_dt_struct;         /* offset to structure block */
        uint32_t off_dt_strings;        /* offset to strings block */
        uint32_t off_mem_rsvmap;        /* offset to memory reservation block */
        uint32_t version;               /* dt spec version */
        uint32_t last_comp_version;     /* last compatible version. spec says this needs to be 16 */
        uint32_t boot_cpuid_phys;       /* physical id of the systems boot cpu */
        uint32_t size_dt_strings;       /* size of strings block */
        uint32_t size_dt_struct;        /* size of structure block */
};

struct fdt_reserve_entry {
        uint64_t address;
        uint64_t size;
};

struct fdt_node_header {
	uint32_t tag;
	char name[];
};

void    fdt_walk(struct fdt_header *header);

#define FDT_MAGIC	0xd00dfeed	/* 4: version, 4: total size */
#define FDT_TAGSIZE	sizeof(fdt32_t)

#define FDT_BEGIN_NODE	0x1		/* Start node: full name */
#define FDT_END_NODE	0x2		/* End node */
#define FDT_PROP	0x3		/* Property: name off,
					   size, content */
#define FDT_NOP		0x4		/* nop */
#define FDT_END		0x9

#endif /* _FDT_H */
