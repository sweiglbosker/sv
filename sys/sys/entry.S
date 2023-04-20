.section ".text.init"

// entrypoint for boot hart(s). a0: hartid, a1: *fdt
.globl _start


// entrypoint for other harts. a0: hartid, a1: unused for now
.global _mpentry 

_start: 
        /* disable interrupts and paging */ 
        csrw       satp, zero
        csrw       sie, zero
        csrw       sip, zero

        .option push
        .option norelax
        la         gp, __global_pointer$
        .option pop

        /* setup stack. 
	 * stack grows toward lower address so sp will mark end of frame.
	 */
        addi       t0, a0, 1
        li         t1, PAGE_SIZE 
        la         sp, __stack_start
        mul        t1, t1, t0
        add        sp, sp, t1

        /* setup thread pointer */ 
        mv        tp, a0

        /* the label _boot_hart is shared between threads. after the first atomic swap, all other harts will branch to mpentry */ 
        li         a2, 1
        lla        a3, _boot_hart
        amoswap.w  a3, a2, (a3)
        bnez       a3, _mpentry

        /* clear the bss section */  
        la         a2, __bss_start
        la         a3, __bss_end
1:
        sd	   zero, (a2)
        addi       a2, a2, __SIZEOF_POINTER__
        blt        a2, a3, 1b 
2:
        call       init
        j          _spin

_mpentry:
	/* satp = 0, sstatus.sie = 0, a0 = hartid, a1 = opaque	*/

	call	 mpinit
	/* shouldn't reach this point */
	j 	_spin

_spin:
	wfi
	j 	_spin

.section ".data"
_boot_hart: 
        .word 0

.section ".rodata"
/* linker imports */
.globl HEAP_START
HEAP_START: .dword __heap_start

