#include <sbi.h>

struct sbiret 
sbi_ecall(int ext, int fid, unsigned long arg0,
                        unsigned long arg1, unsigned long arg2,
                        unsigned long arg3, unsigned long arg4,
                        unsigned long arg5)
{
        struct sbiret ret;

        register unsigned long a0 asm ("a0") = (unsigned long)(arg0);
        register unsigned long a1 asm ("a1") = (unsigned long)(arg1);
        register unsigned long a2 asm ("a2") = (unsigned long)(arg2);
        register unsigned long a3 asm ("a3") = (unsigned long)(arg3);
        register unsigned long a4 asm ("a4") = (unsigned long)(arg4);
        register unsigned long a5 asm ("a5") = (unsigned long)(arg5);
        register unsigned long a6 asm ("a6") = (unsigned long)(fid);
        register unsigned long a7 asm ("a7") = (unsigned long)(ext);
        asm volatile ("ecall"
                      : "+r" (a0), "+r" (a1)
                      : "r" (a2), "r" (a3), "r" (a4), "r" (a5), "r" (a6), "r" (a7)
                      : "memory");
        ret.err = a0;
        ret.val = a1;

        return ret;
}

void
sbi_console_putchar(int c)
{
	sbi_ecall(1, 0, c, 0, 0, 0, 0, 0);
}

void
sbi_shutdown(void)
{
	sbi_ecall(8, 0, 0, 0, 0, 0, 0, 0);
}
