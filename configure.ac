#                                               -*- Autoconf -*-
# Main configure script for BEEBS

# Copyright (C) 2013-2014 Embecosm Limited and the University of Bristol

# Contributor James Pallister <james.pallister@embecosm.com>
# Contributor Jeremy Bennett <jeremy.bennett@embecosm.com>

# This file is part of BEEBS

# This program is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the Free
# Software Foundation; either version 3 of the License, or (at your option)
# any later version.

# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
# more details.

# You should have received a copy of the GNU General Public License along
# with this program.  If not, see <http://www.gnu.org/licenses/>.

# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([beebs], [1.0], [beebs@mageec.org])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])

AC_CANONICAL_BUILD
AC_CANONICAL_HOST

AM_INIT_AUTOMAKE([1.11 -Wno-portability])
AM_MAINTAINER_MODE([enable])
AM_SILENT_RULES([yes])

# Option for selecting the target board
AC_ARG_WITH([board],
    [AS_HELP_STRING([--with-board], [Select the board to target])],
    [],
    [with_board=none]
    )

# Option for selecting the target chip.
AC_ARG_WITH([chip],
[AS_HELP_STRING([--with-chip], [Select the chip to target])],
    [],
    [with_chip=generic]
    )

# Work out which architecutre, board and chip we need
# Also pass this through to be substituted
arch=$host_cpu
board=$with_board
chip=$with_chip

# Some platforms cannot compile certain benchmarks, so we exclude them
# from the build
AC_ARG_VAR(EXCLUDED_BENCHMARKS, exclude benchmarks from the build)

if test -f $srcdir/config/$arch/arch.cfg; then
    source $srcdir/config/$arch/arch.cfg
fi

if ! test -d $srcdir/config/$arch/boards/$board; then
    AC_MSG_ERROR([Config directory for board "$board" does not exist])
fi

if test -f $srcdir/config/$arch/boards/$board/board.cfg; then
    source $srcdir/config/$arch/boards/$board/board.cfg
fi

if ! test -d $srcdir/config/$arch/chips/$chip; then
    AC_MSG_ERROR([Config directory for chip "$chip" does not exist])
fi

if test -f $srcdir/config/$arch/chips/$chip/chip.cfg; then
    source $srcdir/config/$arch/chips/$chip/chip.cfg
fi

AM_CONDITIONAL([CHIPSUPPORT_C],
	       [test -f $srcdir/config/$arch/chips/$chip/chipsupport.c])

if test -f $srcdir/config/$arch/boards/$board/boardsupport.h; then
    AC_DEFINE([HAVE_BOARDSUPPORT_H], [1], [Board support header is present])
fi
if test -f $srcdir/config/$arch/chips/$chip/chipsupport.h; then
    AC_DEFINE([HAVE_CHIPSUPPORT_H], [1], [Chip support header is present])
fi

# Test whether we have a calibration file
if test -f $srcdir/config/$arch/boards/$board/calibration; then
    AC_DEFINE([HAVE_CALIBRATION], [1], [Calibration file is present])
    HAVE_CALIBRATION=yes
fi
AM_CONDITIONAL([CALIBRATION], [test x$HAVE_CALIBRATION == xyes])

AC_SUBST(ARCH, $arch)
AC_SUBST(BOARD, $board)
AC_SUBST(CHIP, $chip)

AC_SUBST([CONFIG_LDFLAGS], ["$ARCH_LDFLAGS $CHIP_LDFLAGS $BOARD_LDFLAGS"])
AC_SUBST([CONFIG_CFLAGS], ["$ARCH_CFLAGS $CHIP_CFLAGS $BOARD_CFLAGS"])

# Sometimes we need to have the CFLAGS and LDFLAGS set so that
# the config test pass. We save them first so we can restore them later
confsave_CFLAGS=$CFLAGS
confsave_LDFLAGS=$LDFLAGS

CFLAGS="$CFLAGS $ARCH_CFLAGS $CHIP_CFLAGS $BOARD_CFLAGS"
LDFLAGS="$LDFLAGS $ARCH_LDFLAGS $CHIP_LDFLAGS $BOARD_LDFLAGS"

LT_INIT
AC_SUBST([LIBTOOL_DEPS])

# If we pass the --host option, then AC_PROG_CC will select the
# correct cross-compiler for us.
AC_PROG_CC
AM_PROG_AS
AC_PROG_CC_C99

# Restore the saved CFLAGs, etc.
echo $CONFIG_CFLAGS
echo $LDFLAGS
echo $confsave_LDFLAGS
CFLAGS=$confsave_CFLAGS
LDFLAGS=$confsave_LDFLAGS

# Allow -Werror to be configured on/off as required.
AC_ARG_ENABLE(werror,
  AS_HELP_STRING([--enable-werror], [treat compile warnings as errors]),
  [case "${enableval}" in
     yes | y) ERROR_ON_WARNING="yes" ;;
     no | n)  ERROR_ON_WARNING="no" ;;
     *) AC_MSG_ERROR(bad value ${enableval} for --enable-werror) ;;
   esac])

AC_MSG_NOTICE([Var GCC = ${GCC}])

# Enable -Werror by default when using gcc.  Turn it off for releases.
if test "${GCC}" = yes -a -z "${ERROR_ON_WARNING}" && $development; then
    ERROR_ON_WARNING=yes
fi

WERROR_CFLAGS=""
if test "${ERROR_ON_WARNING}" = yes ; then
    WERROR_CFLAGS="-Werror"
fi

build_warnings="-Wall"
WARN_CFLAGS=""
AC_ARG_ENABLE(build-warnings,
  AS_HELP_STRING([--enable-build-warnings],
                 [enable build-time compiler warnings if gcc is used]),
  [WARN_CFLAGS="on"
   case "${enableval}" in
     yes | y) ;;
     no | n)  build_warnings="" ;;
     ,*)       t=`echo ${enableval} | sed -e "s/,/ /g"`
               build_warnings="${build_warnings} ${t}";;
     *,)       t=`echo ${enableval} | sed -e "s/,/ /g"`
               build_warnings="${t} ${build_warnings}";;
     *)                build_warnings=`echo ${enableval} | sed -e "s/,/ /g"`
   esac])

# Enable build warnings by default for gcc.
if test "${GCC}" = yes -a -z "${WARN_CFLAGS}" && $development; then
   WARN_CFLAGS="${build_warnings}"
elif test "${WARN_CFLAGS}" = on; then
   WARN_CFLAGS="${build_warnings}"
fi

# List of the benchmarks. This list gets expanded into a variable passed
# into the makefile, and configures the various makefiles. This allows an
# individual benchmark to be excluded from the compilation in a easy way.
m4_define([benchmarklist],[dnl
[2dfir],
[adpcm],
[aha-compress],
[aha-mont64],
[blowfish],
[bs],
[bubblesort],
[cnt],
[compress],
[cover],
[crc],
[crc32],
[ctl-string],
[ctl],
[cubic],
[dhrystone],
[dijkstra],
[dtoa],
[duff],
[edn],
[expint],
[fac],
[fasta],
[fdct],
[fft],
[fibcall],
[fir],
[frac],
[huffbench],
[insertsort],
[janne_complex],
[jfdctint],
[lcdnum],
[levenshtein],
[lms],
[ludcmp],
[matmult],
[mergesort],
[miniz],
[minver],
[nbody],
[ndes],
[nettle-arcfour],
[nettle-cast128],
[nettle-des],
[nettle-md5],
[newlib-exp],
[newlib-log],
[newlib-mod],
[newlib-sqrt],
[ns],
[nsichneu],
[picojpeg],
[prime],
[qrduino],
[qsort],
[qurt],
[recursion],
[rijndael],
[select],
[sglib-arraybinsearch],
[sglib-arraysort],
[sglib-dllist],
[sglib-hashtable],
[sglib-listinsertsort],
[sglib-listsort],
[sglib-queue],
[sglib-rbtree],
[sha],
[slre],
[stringsearch1],
[strstr],
[sqrt],
[st],
[statemate],
[stb_perlin],
[tarai],
[trio],
[ud],
[wikisort],
[whetstone]])

BENCHMARKS=""
BENCHMARKS_SUBDIRS=""
# Count the number of benchmarks that are not in the calibration file
# This will be reported to the user at the end of configure
UNCALIBRATED_BENCHMARKS=""
N_UNCALIBRATED_BENCHMARKS=0

m4_foreach([benchmark], [benchmarklist], [
    bmark=benchmark
    if ! echo "$EXCLUDED_BENCHMARKS" | egrep -q "\b$bmark\b" ; then
        AC_CONFIG_FILES(src/benchmark/Makefile)
        BENCHMARKS+="benchmark "
        BENCHMARKS_SUBDIRS+="src/benchmark "

        if test x$HAVE_CALIBRATION == xyes; then
            no_calib=`egrep -c "\b$bmark\b" $srcdir/config/$arch/boards/$board/calibration`
            if test x$no_calib == x0; then
                UNCALIBRATED_BENCHMARKS="$UNCALIBRATED_BENCHMARKS$bmark "
                N_UNCALIBRATED_BENCHMARKS=$((N_UNCALIBRATED_BENCHMARKS+1))
            fi
        fi
    fi
])

AC_SUBST(WARN_CFLAGS)
AC_SUBST(WERROR_CFLAGS)
AC_SUBST(BENCHMARKS,$BENCHMARKS)
AC_SUBST(BENCHMARKS_SUBDIRS,$BENCHMARKS_SUBDIRS)

AC_CONFIG_SRCDIR([src/])
AC_CONFIG_HEADERS([config.h])

AC_CONFIG_FILES([dejagnu/site.exp])
AC_CONFIG_FILES([src/template/Makefile])
AC_CONFIG_FILES([doc/Makefile])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT

echo
echo \*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*
echo
echo "Host arch                   $arch"
echo "Host board                  $board"
echo "Host chip                   $chip"
echo "Host triple                 $target"

if test "x$EXCLUDED_BENCHMARKS" == x ; then
    echo "Excluded benchmarks         none"
else
    echo "Excluded benchmarks         $EXCLUDED_BENCHMARKS"
fi

if test "x$HAVE_CALIBRATION" == xyes ; then
    echo "Calibrated benchmarks       Yes"
    echo "Uncalibrated benchmarks     $N_UNCALIBRATED_BENCHMARKS"
    if test $N_UNCALIBRATED_BENCHMARKS -gt 0; then
        echo "                            $UNCALIBRATED_BENCHMARKS"
    fi
else
    echo "Calibrated benchmarks       No"
fi
