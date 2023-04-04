#include <stdint.h>
#include <endian.h>

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

#endif /* _FDT_H */
