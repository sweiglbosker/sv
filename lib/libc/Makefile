BUILDDIR=build/${TARGET}
TARGETDIR=../../mainboard/${TARGET}

.if !exists(${TARGETDIR}/conf/mainboard.conf)
.error 'ERROR: invalid target "${TARGET}"'
.else
.include <${TARGETDIR}/conf/mainboard.conf>
.endif

SRC=\
    string/memcpy.c \
    string/memmove.c \
    string/memset.c \
    string/memcmp.c \
    string/memchr.c \


${BUILDDIR}/libc.a: ${SRC}
	mkdir -p ${BUILDDIR}
	cd ${BUILDDIR} && ${CROSS_COMPILE}gcc -c ${CFLAGS} ${SRC:%=../../%}
	cd ${BUILDDIR} && ${CROSS_COMPILE}ar -rcs ${@:T} ${SRC:T:%.c=%.o}


clean:
	rm -rf ${BUILDDIR}
