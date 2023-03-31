.section .text.init

.globl _start
_start:
        csrw       satp, zero
        csrw       sie, zero
        csrw       sip, zero

        .option push
        .option norelax
        la         gp, __global_pointer$
        .option pop

        la         sp, __stack_start
        mv         t0, a0
        li         t1, PAGE_SIZE 
        mul        t0, t0, t1
        add        sp, sp, t0

        li         a2, 1
        lla        a3, _boot_hart
        amoswap.w, a3, a2, (a3)
        bnez a3,   mp_entry 

        la         a2, __bss_start
        la         a3, __bss_end
1:
        sd         zero, (a2)
        addi       a2, a2, __SIZEOF_POINTER__
        blt        a2, a3, 1b 
        
        call       boot

_boot_hart:
        .dword 0

