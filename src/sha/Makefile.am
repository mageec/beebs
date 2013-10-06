bin_PROGRAMS=sha
sha_SOURCES=sha.c sha_driver.c

sha_SOURCES += ../platformcode/platformcode.c

if PLATFORMSRC
    sha_SOURCES += ../platformcode/exit.c ../platformcode/jrand.c ../platformcode/sbrk.c
endif


include $(top_srcdir)/src/common.mk.am
