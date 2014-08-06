# Makefile.am for building a BEEBS benchmark
#
# Copyright (C) 2013 Embecosm Limited and University of Bristol
#
# This file is part of the Bristol/Embecosm Embedded Benchmark Suite
# Suite.
#
# Contributor: James Pallister <james.pallister@bristol.ac.uk>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

bin_PROGRAMS=trio-snprintf trio-sscanf

SRC=trio.c trio.h trio_test.c triostr.c \
    triostr.h triodef.h triop.h

trio_snprintf_SOURCES=${SRC}
trio_sscanf_SOURCES=${SRC}

include $(top_srcdir)/src/common.mk.am

AM_CFLAGS += -DTRIO_EXTENSION=0 -DTRIO_DEPRECATED=0 -DTRIO_MICROSOFT=0 -DTRIO_ERRORS=0 -DTRIO_FEATURE_FLOAT=0

trio_snprintf_CFLAGS=-DTRIO_SNPRINTF -DTRIO_SNPRINTF_ONLY ${AM_CFLAGS}
trio_sscanf_CFLAGS=-DTRIO_SSCANF ${AM_CFLAGS} \
                   -DTRIO_FEATURE_FILE=0 -DTRIO_FEATURE_STDIO=0 \
                   -DTRIO_FEATURE_FD=0 -DTRIO_FEATURE_DYNAMICSTRING=0 \
                   -DTRIO_FEATURE_CLOSURE=0 -DTRIO_FEATURE_STRERR=0 \
                   -DTRIO_FEATURE_LOCALE=0 -DTRIO_EMBED_NAN=1 \
                   -DTRIO_EMBED_STRING=1

trio_snprintf_SOURCES += ${platform_src}
trio_sscanf_SOURCES += ${platform_src}
