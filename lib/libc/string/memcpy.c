#include <string.h>

void *memcpy(void *__restrict s1, const void *__restrict s2, size_t n)
{
	char *tmp = s1;
	const char *s = s2;

	while (n--)
		*tmp++ = *s++;
	return s1;
}
