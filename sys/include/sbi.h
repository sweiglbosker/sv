#ifndef _SBICALL_H
#define _SBICALL_H

struct sbiret {
        long err;
        long val;
};

struct sbiret 	sbi_ecall(int _eid, int _fid, unsigned long _a0, unsigned long _a1, 
               		unsigned long _a2, unsigned long _a3, unsigned long _a4, unsigned long _a5);

void    sbi_console_putchar(int c);
void    sbi_shutdown(void);

#endif /* _SBICALL_H */

