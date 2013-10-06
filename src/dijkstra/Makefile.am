bin_PROGRAMS=dijkstra
dijkstra_SOURCES=dijkstra_small.c

dijkstra_SOURCES += ../platformcode/platformcode.c

if PLATFORMSRC
    dijkstra_SOURCES += ../platformcode/exit.c ../platformcode/jrand.c ../platformcode/sbrk.c
endif

include $(top_srcdir)/src/common.mk.am
