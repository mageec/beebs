bin_PROGRAMS=crc32
crc32_SOURCES=crc_32.c

crc32_SOURCES += ../platformcode/platformcode.c

if PLATFORMSRC
    crc32_SOURCES += ../platformcode/exit.c ../platformcode/jrand.c ../platformcode/sbrk.c
endif


include $(top_srcdir)/src/common.mk.am
