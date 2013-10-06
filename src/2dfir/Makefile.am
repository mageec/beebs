bin_PROGRAMS=2dfir
2dfir_SOURCES=fir2dim.c

2dfir_SOURCES += ../platformcode/platformcode.c

if PLATFORMSRC
    2dfir_SOURCES += ../platformcode/exit.c ../platformcode/jrand.c ../platformcode/sbrk.c
endif

include $(top_srcdir)/src/common.mk.am
