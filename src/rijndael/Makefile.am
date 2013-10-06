bin_PROGRAMS=rijndael
rijndael_SOURCES=aes.c aesxam.c

rijndael_SOURCES += ../platformcode/platformcode.c

if PLATFORMSRC
    rijndael_SOURCES += ../platformcode/exit.c ../platformcode/jrand.c ../platformcode/sbrk.c
endif


include $(top_srcdir)/src/common.mk.am
