TARGET?=virt
BUILD?=debug
CROSS_COMPILE?=riscv64-unknown-elf- 
GDB_PORT?=1234
CFLAGS=-nostdlib -ffreestanding -mcmodel=medany -I${.CURDIR}/include 
.if ${BUILD}==debug
CFLAGS+=-ggdb
.endif
.export

sys: ${SRC} lib/build/libc.a
	@echo "building kernel"
	(${MAKE} -C sys -e) 

lib/build/libc.a: 
	@echo "building libc"
	(${MAKE} -C lib -e)

debug: sys
	(${MAKE} -C sys -e debug) 

clean:
	(${MAKE} -C sys -e clean)
	(${MAKE} -C lib -e clean)

.PHONY: sys debug all clean
