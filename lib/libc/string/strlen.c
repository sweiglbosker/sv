#include <string.h>

size_t 
strlen(const char *s)
{
	int n;
	for (n = 0; s[n]; n++) 
		;
	return n;
}

size_t
strnlen(const char *s, size_t max)
{
	int n;
	for (n = 0; s[n] && n < max; n++)
		;
	return n;
}
