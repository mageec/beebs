bin_PROGRAMS=int_matmult
int_matmult_SOURCES=matmult.c

int_matmult_SOURCES += ../platformcode/platformcode.c

if PLATFORMSRC
    int_matmult_SOURCES += ../platformcode/exit.c ../platformcode/jrand.c ../platformcode/sbrk.c
endif


include $(top_srcdir)/src/common.mk.am
