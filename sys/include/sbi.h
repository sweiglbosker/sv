#ifndef _SBI_H
#define _SBI_H

struct sbiret {
	long err;
	long val;
};

#define SBI_SUCCESS	 	 0
#define SBI_ERR_FAILED		-1
#define SBI_ERR_NOT_SUPPORTED 	-2
#define SBI_ERR_INVALD_PARAM	-3 
#define SBI_ERR_DENIED		-4
#define SBI_ERR_INVALID_ADDRESS	-5
#define SBI_ERR_ALREADY_AVAILABLE -6
#define SBI_ERR_ALREADY_STARTED -7
#define SBI_ERR_ALREADY_STOPPED -8

enum HART_STATUS {
	STARTED,
	STOPPED,
	START_PENDING,
	STOP_PENDING,
	SUSPENDED,
	SUSPEND_PENDING,
	RESUME_PENDING
};

static inline struct sbiret 
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

static inline void
sbi_console_putchar(int c)
{
	sbi_ecall(1, 0, c, 0, 0, 0, 0, 0);
}

static inline void
sbi_shutdown(void)
{
	sbi_ecall(8, 0, 0, 0, 0, 0, 0, 0);
}

static inline struct sbiret
sbi_hart_start(unsigned long hartid, unsigned long start_addr, unsigned long opaque)
{
	struct sbiret r = sbi_ecall(0x48534D, 0, hartid, start_addr, opaque, 0, 0, 0);
	return r;
}
#define _start_hart(tp, a)	sbi_hart_start(tp, a, 0);

#endif /* _SBI_H */

