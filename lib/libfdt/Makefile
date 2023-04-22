BUILDDIR=build/${TARGET}
TARGETDIR=../../mainboard/${TARGET}

.if !exists(${TARGETDIR}/conf/mainboard.conf)
.error 'ERROR: invalid target "${TARGET}"'
.else
.include <${TARGETDIR}/conf/mainboard.conf>
.endif

SRC=fdt.c fdt_ro.c fdt_wip.c fdt_sw.c fdt_rw.c fdt_strerror.c fdt_empty_tree.c \
	fdt_addresses.c fdt_overlay.c fdt_check.c


${BUILDDIR}/libfdt.a: ${SRC}
	mkdir -p ${BUILDDIR}
	cd ${BUILDDIR} && ${CROSS_COMPILE}gcc -c ${CFLAGS} -L ../libc/${BUILDDIR} -l:libc.a -nostdlib -nostdinc -I../../include/ ${SRC:%=../../%}
	cd ${BUILDDIR} && ${CROSS_COMPILE}ar -rcs ${@:T} ${SRC:T:%.c=%.o}


clean:
	rm -rf ${BUILDDIR}
