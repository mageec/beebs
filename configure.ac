#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([beebs], [1.0], [james.pallister@embecosm.com])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])

AC_CANONICAL_SYSTEM

AM_INIT_AUTOMAKE
AC_PROG_LIBTOOL
LT_INIT
AC_CONFIG_SRCDIR([src/])
#AC_CONFIG_HEADERS([config.h])

if test x$host == x$build ; then
    cross_compiling=no
else
    cross_compiling=yes
fi

AC_PROG_CC_C99
AM_PROG_AS

if test x$cross_compiling == xyes ; then
    # Check that the specified cross compiler exists
    AC_CHECK_PROG(CROSS_COMPILER_CHECK,$host_alias-gcc,yes,no)

    if test x"${CROSS_COMPILER_CHECK}" == x"no" ; then
        AC_MSG_ERROR([Cannot find $host_alias-gcc])
    fi
fi

AC_ARG_WITH([linkerscript],
            [AS_HELP_STRING([--with-linkerscript],
              [Choose the linker script])],
            [],
            [with_linkerscript=no])

if test x$with_linkerscript == xno ; then
    with_linkerscript=""
else
    lk=`readlink -m ${with_linkerscript}`
#    with_linkerscript="-T ${lk}"
    AC_SUBST([LINKERSCRIPT], ["-T ${lk}"])
fi

AC_ARG_ENABLE([platformsources],
            [AS_HELP_STRING([--enable-platformsources],
              [Add platform sources to be compiled in])],
            [enable_platformsources=yes],
            [enable_platformsources=no])

AM_CONDITIONAL([PLATFORMSRC], [test x$enable_platformsources != xno])

# Check if we want to simulate AVR ###########################################
AC_ARG_ENABLE([simulate-avr],
            [AS_HELP_STRING([--enable-simulate-avr],
                [Enable the simulation for AVR])],
            [enable_simulate_avr=yes],
            [enable_simulate_avr=no],
            )

if test x$enable_simulate_avr == xyes ; then
    AC_CHECK_PROGS(simulavr_cmd, simulavr)
    AC_RUN_IFELSE([], [], [],
        [found_version=`simulavr --version | grep "SimulAVR 1.0.0" -c`])
    if test x$found_version == x0 ; then
        AC_MSG_FAILURE([Need version 1.0.0 of simulavr])
    fi
fi

AM_CONDITIONAL([SIMULATE_AVR], [test x$enable_simulate_avr != xno])

AC_CONFIG_FILES([src/2dfir/Makefile])
AC_CONFIG_FILES([src/blowfish/Makefile])
AC_CONFIG_FILES([src/crc32/Makefile])
AC_CONFIG_FILES([src/cubic/Makefile])
AC_CONFIG_FILES([src/dijkstra/Makefile])
AC_CONFIG_FILES([src/fdct/Makefile])
AC_CONFIG_FILES([src/float_matmult/Makefile])
AC_CONFIG_FILES([src/int_matmult/Makefile])
AC_CONFIG_FILES([src/rijndael/Makefile])
AC_CONFIG_FILES([src/sha/Makefile])
AC_CONFIG_FILES([src/template/Makefile])
AC_CONFIG_FILES([src/platformcode/Makefile])
AC_CONFIG_FILES([analysis/Makefile])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
