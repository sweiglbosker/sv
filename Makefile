TARGET?=virt
BUILD?=debug
CROSS_COMPILE?=riscv64-unknown-elf- 
GDB_PORT?=1234
CFLAGS=-nostdlib -ffreestanding -mcmodel=medany -I${.CURDIR}/include 
.if ${BUILD}==debug
CFLAGS+=-ggdb
.endif
.export

sys: ${SRC} lib/libc/build/libc.a lib/libfdt/build/libfdt.a
	@echo "building kernel"
	(${MAKE} -C sys -e) 

lib/libc/build/libc.a: 
	@echo "building libc"
	(${MAKE} -C lib/libc -e)

lib/libfdt/build/libfdt.a: 
	@echo "building libfdt"
	(${MAKE} -C lib/libfdt -e)

debug: sys
	(${MAKE} -C sys -e debug) 

clean:
	(${MAKE} -C sys -e clean)
	(${MAKE} -C lib/libc -e clean)
	(${MAKE} -C lib/libfdt -e clean)

.PHONY: sys debug all clean
