# Makefile.am for building a BEEBS benchmark
#
# Copyright (C) 2014 Embecosm Limited and University of Bristol
# Copyright (C) 2020 AdaCore
#
# This file is part of the Bristol/Embecosm Embedded Benchmark Suite.
#
# Contributor: James Pallister <james.pallister@bristol.ac.uk>
# Contributor: Kyriakos Georgiou <georgiou@adacore.com>
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

# SPDX-License-Identifier: GPL-3.0-or-later

if ENABLED_BENCHMARK_FIBCALL

include $(top_srcdir)/src/common.mk.am

bin_PROGRAMS          = fibcall

if ADA
noinst_LTLIBRARIES = libfibcall_ada.la
else
noinst_LTLIBRARIES    = libfibcall.la
endif


fibcall_SOURCES       =

if ADA
libfibcall_la_SOURCES = libfibcall_ada.c
else
libfibcall_la_SOURCES = libfibcall.c
endif

fibcall_LDADD         = $(DUMMY_CRT0) \
                        $(top_builddir)/support/libsupport.la \
                        libfibcall.la \
                        $(DUMMY_LIBC) $(DUMMY_LIBGCC) $(DUMMY_COMPILERRT)

if ADA

AM_LDFLAGS = -L. -ladaStatic -lgnat

EXTRA_fibcall_DEPENDENCIES = build_ada

.PHONY: build_ada

build_ada: libadaStatic.a

libadaStatic.a: 
	./ada_library_build.sh $(top_builddir)

clean-local:
	-rm -rf libadaStatic.a

endif

endif
