#ifndef _STDINT_H
#define _STDINT_H


typedef unsigned char	uint8_t;
typedef unsigned short 	uint16_t;
typedef unsigned int	uint32_t;
typedef unsigned long	uint64_t;

typedef char	int8_t;
typedef short 	int16_t;
typedef int	int32_t;
typedef long	int64_t;

typedef unsigned long uintptr_t;

#if __riscv_xlen == 32
typedef unsigned int uintptr_t;
#elif __riscv_xlen == 64
typedef unsigned long uintptr_t;
#endif 

#define INT16_MIN  (-1-0x7fff)
#define INT32_MIN  (-1-0x7fffffff)
#define INT64_MIN  (-1-0x7fffffffffffffff)

#define INT8_MAX   (0x7f)
#define INT16_MAX  (0x7fff)
#define INT32_MAX  (0x7fffffff)
#define INT64_MAX  (0x7fffffffffffffff)

#define UINT8_MAX  (0xff)
#define UINT16_MAX (0xffff)
#define UINT32_MAX (0xffffffffu)
#define UINT64_MAX (0xffffffffffffffffu)

#define INT_FAST8_MIN   INT8_MIN
#define INT_FAST64_MIN  INT64_MIN

#define INT_LEAST8_MIN   INT8_MIN
#define INT_LEAST16_MIN  INT16_MIN
#define INT_LEAST32_MIN  INT32_MIN
#define INT_LEAST64_MIN  INT64_MIN

#define INT_FAST8_MAX   INT8_MAX
#define INT_FAST64_MAX  INT64_MAX

#define INT_LEAST8_MAX   INT8_MAX
#define INT_LEAST16_MAX  INT16_MAX
#define INT_LEAST32_MAX  INT32_MAX
#define INT_LEAST64_MAX  INT64_MAX

#define UINT_FAST8_MAX  UINT8_MAX
#define UINT_FAST64_MAX UINT64_MAX

#define UINT_LEAST8_MAX  UINT8_MAX
#define UINT_LEAST16_MAX UINT16_MAX
#define UINT_LEAST32_MAX UINT32_MAX
#define UINT_LEAST64_MAX UINT64_MAX

#define INTMAX_MIN  INT64_MIN
#define INTMAX_MAX  INT64_MAX
#define UINTMAX_MAX UINT64_MAX

#define WINT_MIN 0U
#define WINT_MAX UINT32_MAX

#if L'\0'-1 > 0
#define WCHAR_MAX (0xffffffffu+L'\0')
#define WCHAR_MIN (0+L'\0')
#else
#define WCHAR_MAX (0x7fffffff+L'\0')
#define WCHAR_MIN (-1-0x7fffffff+L'\0')
#endif

#endif /* _STDINT_H */
  
  
