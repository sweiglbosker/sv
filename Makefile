TARGET?=virt
CROSS_COMPILE?=riscv64-unknown-elf- 

BUILDDIR=build/${TARGET}
TARGETDIR=mainboard/${TARGET}

CFLAGS=-nostdlib -ffreestanding -mcmodel=medany

.if !exists(${TARGETDIR}/conf/mainboard.mk)
.error 'ERROR: invalid target "${TARGET}"'
.else
.include <${TARGETDIR}/conf/mainboard.mk>
.endif

all: ${BUILDDIR}/kernel.elf 

clean:
	rm -rf ${BUILDDIR}

${BUILDDIR}/kernel.elf: ${SRC}
	mkdir -p ${BUILDDIR}
	${CROSS_COMPILE}gcc ${SRC} \
		-Wl,--defsym=LOAD_ADDR=${LOAD_ADDR}\
		-Wl,--defsym=PAGE_SIZE=${PAGE_SIZE}\
		-Wl,--defsym=NPROC=${NPROC}\
		-DPAGE_SIZE=${PAGE_SIZE}\
		${CFLAGS} -T kernel/lds/kernel.ld ${LDFLAGS}\
		-o $@

.PHONY: all clean
