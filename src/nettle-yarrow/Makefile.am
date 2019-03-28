# Makefile.am for nettle-yarrow
#
# Copyright (C) 2019 Embecosm Limited and University of Bristol
#
# This file is part of the Bristol/Embecosm Embedded Benchmark Suite.
#
# Contributor: Graham Markall <graham.markall@embecosm.com>
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

if ENABLED_BENCHMARK_NETTLE_YARROW

include $(top_srcdir)/src/common.mk.am

bin_PROGRAMS             = nettle-yarrow
noinst_LTLIBRARIES       = libnettle-yarrow.la

nettle_yarrow_SOURCES       =
libnettle_yarrow_la_SOURCES = nettle-yarrow.c

nettle_yarrow_LDADD         = $(DUMMY_CRT0) \
                              $(top_builddir)/support/libsupport.la \
                              libnettle-yarrow.la \
                              $(DUMMY_LIBC) $(DUMMY_LIBGCC) $(DUMMY_COMPILERRT)

endif
