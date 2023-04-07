BUILDDIR=build/${TARGET}
TARGETDIR=../mainboard/${TARGET}

.if !exists(${TARGETDIR}/conf/mainboard.conf)
.error 'ERROR: invalid target "${TARGET}"'
.else
.include <${TARGETDIR}/conf/mainboard.conf>
.endif

SRC=\
    kern/entry.S\
    kern/init.c\
    kern/printf.c\
    kern/mm/kalloc.c\
    dev/sbi.c

${BUILDDIR}/kernel.elf: ${SRC}
	mkdir -p ${BUILDDIR}
	${CROSS_COMPILE}gcc ${SRC} \
		-Wl,--defsym=LOAD_ADDR=${LOAD_ADDR}\
		-Wl,--defsym=PAGE_SIZE=${PAGE_SIZE}\
		-Wl,--defsym=NPROC=${NPROC}\
		-DPAGE_SIZE=${PAGE_SIZE}\
		-I ./include\
		${CFLAGS} -T kern/kernel.lds ${LDFLAGS}\
		-L../lib/${BUILDDIR}/\
		-l:libc.a\
		-o $@

debug: ${BUILDDIR}/kernel.elf
	${DEBUG} ${BUILDDIR}/kernel.elf

clean:
	rm -rf ${BUILDDIR}

.PHONY: debug clean
