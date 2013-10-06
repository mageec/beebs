bin_PROGRAMS=cubic
cubic_SOURCES=cubic.c basicmath_small.c

cubic_SOURCES += ../platformcode/platformcode.c

if PLATFORMSRC
    cubic_SOURCES += ../platformcode/exit.c ../platformcode/jrand.c ../platformcode/sbrk.c
endif


cubic_LDFLAGS = "-lm"

include $(top_srcdir)/src/common.mk.am
