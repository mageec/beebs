# Makefile.am for building a BEEBS benchmark
#
# Copyright (C) 2014 Embecosm Limited and University of Bristol
# Copyright (C) 2020 Adacore
#
# This file is part of the Bristol/Embecosm Embedded Benchmark Suite.
#
# Contributor: Pierre Langlois <pierre.langlois@embecosm.com>
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

if ENABLED_BENCHMARK_FAC

include $(top_srcdir)/src/common.mk.am

bin_PROGRAMS       = fac

if ADA
noinst_LTLIBRARIES = libfac_ada.la
else
noinst_LTLIBRARIES = libfac.la
endif

fac_SOURCES        =

if ADA
libfac_la_SOURCES = libfac_ada.c
fac_LDADD          = $(DUMMY_CRT0) \
                     $(top_builddir)/support/libsupport.la \
                     libfac_ada.la \
                     $(DUMMY_LIBC) $(DUMMY_LIBGCC) $(DUMMY_COMPILERRT)
else
libfac_la_SOURCES = libfac.c
fac_LDADD          = $(DUMMY_CRT0) \
                     $(top_builddir)/support/libsupport.la \
                     libfac.la \
                     $(DUMMY_LIBC) $(DUMMY_LIBGCC) $(DUMMY_COMPILERRT)
endif 

if ADA

AM_LDFLAGS = -L./lib -L. -ladaStatic -lgnat

EXTRA_fac_DEPENDENCIES = build_ada

.PHONY: build_ada

build_ada: lib/libadaStatic.a

lib/libadaStatic.a:
	gprbuild -p -Pada_project

endif

clean-local:
	-rm -rf libfac_ada.la
	-gprclean -Pada_project

endif
