#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([beebs], [1.0], [james.pallister@embecosm.com])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])

AM_MAINTAINER_MODE([disable])

# AM_SILENT_RULES([yes])

AC_ARG_ENABLE([simulate],
            [AS_HELP_STRING([--enable-simulate],
                [Enable the simulation for the specified platform])],
            [],
            [enable_simulate=no],
            )

# Option for selecting the target board
AC_ARG_WITH([board],
    [AS_HELP_STRING([--with-board], [Select the board to target])],
    [],
    [with_board=none]
    )

# Option for selecting the target board
AC_ARG_WITH([chip],
[AS_HELP_STRING([--with-chip], [Select the chip to target])],
    [],
    [with_chip=none]
    )


AC_CANONICAL_SYSTEM

# Work out which architecutre, board and chip we need
# Also pass this through to be substituted
arch=$target_cpu
board=$with_board
chip=$with_chip

AC_SUBST(ARCH, $arch)
AC_SUBST(BOARD, $board)
AC_SUBST(CHIP, $chip)

# Some platforms cannot compile certain benchmarks, so we exclude them
# from the build
AC_ARG_VAR(EXCLUDED_BENCHMARKS, exclude benchmarks from the build)

if test -f $srcdir/config/$arch/boards/$board/boardsupport.h; then
    AC_DEFINE([HAVE_BOARDSUPPORT_H], [1], [Board support header is present])
fi
if test -f $srcdir/config/$arch/chips/$chip/chipsupport.h; then
    AC_DEFINE([HAVE_CHIPSUPPORT_H], [1], [Chip support header is present])
fi

if test -f $srcdir/config/$arch/boards/$board/board.cfg; then
    source $srcdir/config/$arch/boards/$board/board.cfg
fi

if test -f $srcdir/config/$arch/chips/$chip/chip.cfg; then
    source $srcdir/config/$arch/chips/$chip/chip.cfg
fi

AC_SUBST([AM_LDFLAGS], ["$CHIP_LDFLAGS $BOARD_LDFLAGS"])
AC_SUBST([AM_CFLAGS], ["$CHIP_CFLAGS $BOARD_CFLAGS"])

# Sometimes we need to have the CFLAGS and LDFLAGS set so that
# the config test pass. We save them first so we can restore them later
save_CFLAGS=$CFLAGS
save_LDFLAGS=$LDFLAGS

CFLAGS="$CFLAGS $CHIP_CFLAGS $BOARD_CFLAGS"
LDFLAGS="$LDFLAGS $CHIP_LDFLAGS $BOARD_LDFLAGS"

AM_INIT_AUTOMAKE
AC_PROG_LIBTOOL
LT_INIT

AC_PROG_CC_C99
AM_PROG_AS

# Quick check to see if we are cross compiling or not
if test x$host == x$build ; then
    cross_compiling=no
else
    cross_compiling=yes
fi

if test x$cross_compiling == xyes ; then
    # Check that the specified cross compiler exists
    AC_CHECK_PROG(CROSS_COMPILER_CHECK,$host_alias-gcc,yes,no)

    if test x"${CROSS_COMPILER_CHECK}" == x"no" ; then
        AC_MSG_ERROR([Cannot find $host_alias-gcc])
    fi
fi

# Restore the saved CFLAGs, etc.
CFLAGS=$save_CFLAGS
LDFLAGS=$save_LDFLAGS

# List of the benchmarks. This list gets expanded into a variable passed
# into the makefile, and configures the various makefiles. This allows an
# individual benchmark to be excluded from the compilation in a easy way.
m4_define([benchmarklist],[dnl
[2dfir],
[adpcm],
[blowfish],
[bs],
[bsort100],
[bubblesort],
[cnt],
[compress],
[cover],
[crc],
[crc32],
[ctl-string],
[ctl-stack],
[ctl-vector],
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
[float_matmult],
[frac],
[gdb-advance],
[gdb-all-types],
[gdb-anon],
[gdb-arrayidx],
[gdb-async],
[gdb-bitfields],
[gdb-constvars],
[gdb-store],
[huffbench],
[insertsort],
[int_matmult],
[janne_complex],
[jfdctint],
[lcdnum],
[levenshtein],
[lms],
[ludcmp],
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
[prime],
[qsort],
[qurt],
[recursion],
[rijndael],
[select],
[sglib-arraybinsearch],
[sglib-arraysort],
[sglib-arraysort1],
[sglib-dllist],
[sglib-hashtable],
[sglib-listinsertsort],
[sglib-listinsertsort1],
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
[tarai],
[ud],
[wikisort],
[whetstone]])

BENCHMARKS=""
BENCHMARKS_SUBDIRS=""

m4_foreach([benchmark], [benchmarklist], [
    bmark=benchmark
    if ! echo "$EXCLUDED_BENCHMARKS" | egrep -q "\b$bmark\b" ; then
        AC_CONFIG_FILES(src/benchmark/Makefile)
        BENCHMARKS+="benchmark "
        BENCHMARKS_SUBDIRS+="src/benchmark "
    fi
])

AC_SUBST(BENCHMARKS_SUBDIRS,$BENCHMARKS_SUBDIRS)

AC_CONFIG_SRCDIR([src/])
AC_CONFIG_HEADERS([config.h])

AC_CONFIG_FILES([src/template/Makefile])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT

echo
echo \*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*
echo
echo "Target arch                   $arch"
echo "Target board                  $with_board"
echo "Target chip                   $with_chip"
echo "Target triple                 $target"

if test "x$EXCLUDED_BENCHMARKS" == x ; then
    echo "Excluded benchmarks           none"
else
    echo "Excluded benchmarks           $EXCLUDED_BENCHMARKS"
fi
