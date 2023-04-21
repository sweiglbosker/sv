#include <string.h>

int 
memcmp(const void *s1, const void *s2, size_t n)
{
	const char *str1 = (const char *)s1;
	const char *str2 = (const char *)s2;
	while (n--) {
		if (*str1 != *str2)
			return *str1 - *str2;
		str1++; str2++;
	}
	return 0;
}

