bin_PROGRAMS=float_matmult
float_matmult_SOURCES=matmult.c

float_matmult_SOURCES += ../platformcode/platformcode.c

if PLATFORMSRC
    float_matmult_SOURCES += ../platformcode/exit.c ../platformcode/jrand.c ../platformcode/sbrk.c
endif


include $(top_srcdir)/src/common.mk.am
