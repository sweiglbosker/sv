#include <string.h>

void *memchr(const void *s, int c, size_t n) {
	const char *p = s;
	while (n--) {
		if ((char)c == *p++) {
			return (void*)(p-1);
		}
	}
	return NULL;
}
