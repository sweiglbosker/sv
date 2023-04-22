#include <string.h>

char *strchr(const char *s, int c) {
	do {
		if ((char)c == *s) 
			return (char*)s;
	} while (*s++ != '\0');
	return NULL;
}

char *strrchr(const char *s, int c)
{
	const char *last = NULL;
	do {
		if (*s == (char)c)
			last = s;
	} while (*s++);
	return (char *)last;
}
