bin_PROGRAMS=blowfish
blowfish_SOURCES = bf.c bf_enc.c bf_skey.c bf_cfb64.c

blowfish_SOURCES += ../platformcode/platformcode.c

if PLATFORMSRC
    blowfish_SOURCES += ../platformcode/exit.c ../platformcode/jrand.c ../platformcode/sbrk.c
endif


include $(top_srcdir)/src/common.mk.am
