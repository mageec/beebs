bin_PROGRAMS=fdct
fdct_SOURCES=fdct.c

fdct_SOURCES += ../platformcode/platformcode.c

if PLATFORMSRC
    fdct_SOURCES += ../platformcode/exit.c ../platformcode/jrand.c ../platformcode/sbrk.c
endif


include $(top_srcdir)/src/common.mk.am
