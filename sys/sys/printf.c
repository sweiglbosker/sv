#include <printf.h>
#include <stdint.h>
#include <spinlock.h>
#include <sbi.h>
#include <stdarg.h>

static char digits[] = "0123456789abcdef";

static spinlock_t mutex;

int
puts(const char *str)
{
	do {
		sbi_console_putchar(*str);
	} while (*(str++) != '\0');
}

#define PUTCHAR(c)      sbi_console_putchar(c)

static void
printint(int xx, int base, int sign)
{
	char buf[16];
	int i;
	unsigned int x;

	if (sign && (sign = xx < 0))
		x = -xx;
	else 
		x = xx; 

	i = 0;
	do {
		buf[i++] = digits[x % base];
	} while ((x /= base) != 0);

	if (sign)
		buf[i++] = '-';
	while (--i >= 0)
		PUTCHAR(buf[i]);

}

static void 
printptr(uint64_t x)
{
	int i;
	puts("0x");
	for (i = 0; i < (sizeof(uint64_t) * 2); i++, x <<= 4)
		PUTCHAR(digits[x >> (sizeof(int64_t) * 8 - 4)]);
}

void
printf(const char *fmt, ...) 
{
	va_list ap;
	int i, c, _locked;
	char *s;

	acquire(&mutex);

	va_start(ap, fmt);

	for (i = 0; (c = fmt[i] & 0xff) != 0; i++) {
		if (c != '%') {
			PUTCHAR(c);
			continue;
		}
		c = fmt[++i] & 0xff;
		if (!c) 
			break;

		switch (c) {
			case 'd':
			case 'i':
				printint(va_arg(ap, int), 10, 1);
				break;
			case 'x':
				printint(va_arg(ap, int), 16, 1);
				break;
			case 'p':
				printptr(va_arg(ap, uint64_t));
				break;
			case '%':
				PUTCHAR('%');
				break;
		}
	}
	release(&mutex);
}

void printf_init(void)
{
	initlock(&mutex);
}
