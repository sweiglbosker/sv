#include <kernel_earlyprintf.h>
#include <sbi.h>

int
kernel_earlyputs(const char *str)
{
	do {
		sbi_console_putchar(*str);
	} while (*(str++) != '\0');
}

