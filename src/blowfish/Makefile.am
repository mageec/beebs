# Makefile.am for BEEBS blowfish test
#
# Copyright (C) 1995-1997 Eric Young (eay@mincom.oz.au)
# Copyright (C) 2013 Embecosm Limited and University of Bristol
#
# Contributor Eric Young <eay@mincom.oz.au>
# Contributor Jeremy Bennett <jeremy.bennett@embecosm.com>
#
# This file is part of the Bristol/Embecosm Embedded Benchmark Suite.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.

bin_PROGRAMS=blowfish
blowfish_SOURCES = bf.c \
                   bf_enc.c \
                   bf_skey.c \
                   bf_cfb64.c \
                   bf_locl.h   \
                   bf_pi.h \
                   blowfish.h
EXTRA_DIST = COPYRIGHT \
             LICENSE

include $(top_srcdir)/src/common.mk.am

blowfish_SOURCES += ${platform_src}
