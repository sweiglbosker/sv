#ifndef _ENDIAN_H
#define _ENDIAN_H

#include <stdint.h>

#define LITTLE_ENDIAN 1234
#define BIG_ENDIAN	4321
#define BYTE_ORDER __BYTE_ORDER__

static inline uint32_t
__bswap32(uint32_t x)
{
        uint8_t *p = (uint8_t*)&x;
        return ((p[0] << 030) | (p[1] << 020) | (p[2] << 010) | p[3]);
}

#endif /* _ENDIAN_H */
