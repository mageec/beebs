#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([beebs], [1.0], [james.pallister@embecosm.com])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])

AM_MAINTAINER_MODE([disable])

AM_SILENT_RULES([yes])

AC_ARG_ENABLE([simulate],
            [AS_HELP_STRING([--enable-simulate],
                [Enable the simulation for the specified platform])],
            [],
            [enable_simulate=no],
            )

AC_ARG_WITH([platform],
    [AS_HELP_STRING([--with-platform],
        [Select the platform compile for])],
    [],
    [with_platform=none]
    )

AM_CONDITIONAL([STM32F0DISCOVERY], [false])
AM_CONDITIONAL([ATMEGA328P], [false])
AM_CONDITIONAL([MSPEXP430F5529], [false])

case $with_platform in
    stm32f0discovery)
        if test x$host == x$build ; then
            AC_MSG_ERROR([Please rerun configure with --host=arm-none-eabi for this platform])
        fi

        # gcc-arm-embedded requires these libraries for the tests, else they'll fail
        AC_SUBST([AM_LDFLAGS], ["-lc -lnosys"])
        AC_SUBST([AM_CFLAGS], ["-mthumb -mcpu=cortex-m0 -DCORTEX_M0"])

        # enable_platformsources=yes

        if test x$enable_simulate == xyes; then
            enable_simulate_cortex_m0=yes
        fi

        AM_CONDITIONAL([STM32F0DISCOVERY], [true])
        ;;

    atmega328p)
        if test x$host == x$build ; then
            AC_MSG_ERROR([Please rerun configure with --host=avr for this platform])
        fi

        AC_SUBST([AM_CFLAGS], ["-mmcu=atmega328p -std=gnu99 -DAVR"])
        if test x$enable_simulate == xyes; then
            enable_simulate_avr=yes
        fi

        AM_CONDITIONAL([ATMEGA328P], [true])
        ;;

    msp-exp430f5529)
        if test x$host == x$build ; then
            AC_MSG_ERROR([Please rerun configure with --host=msp430 for this platform])
        fi

        AC_SUBST([AM_CFLAGS], ["-mmcu=msp430f5529 -std=gnu99 -mcpu=430 -DMSP430F"])
        if test x$enable_simulate == xyes; then
            enable_simulate_msp430=yes
        fi

        AM_CONDITIONAL([MSPEXP430F5529], [true])
        ;;
esac

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
            [with_linkerscript=none])

if test x$with_linkerscript != xnone ; then
    lk=`readlink -m ${with_linkerscript}`
#    with_linkerscript="-T ${lk}"
    AC_SUBST([LINKERSCRIPT], ["-T ${lk}"])
fi

AC_ARG_ENABLE([platformsources],
            [AS_HELP_STRING([--enable-platformsources],
              [Add platform sources to be compiled in])],
            [],
            [   if [[ -z "$enable_platformsources" ]] ; then
                    enable_platformsources=no
                fi ])

AM_CONDITIONAL([PLATFORMSRC], [test x$enable_platformsources != xno])

AM_CONDITIONAL([SIMULATE], [false])

# Check if we want to simulate AVR #########################################
AC_ARG_ENABLE([simulate-avr],
            [AS_HELP_STRING([--enable-simulate-avr],
                [Enable the simulation for AVR])],
            [],
            [if [[ -z "$enable_simulate_avr" ]] ; then enable_simulate_avr=no; fi],
            )

if test x$enable_simulate_avr == xyes ; then
    AC_CHECK_PROGS(simulavr_cmd, simulavr)
    AC_RUN_IFELSE([], [], [],
        [found_version=`simulavr --version | grep "SimulAVR 1.0.0" -c`])
    if test x$found_version == x0 ; then
        AC_MSG_FAILURE([Need version 1.0.0 of simulavr])
    fi
    AC_SUBST(SIMULATORPATH, [simulavr])
    AM_CONDITIONAL([SIMULATE], [test x$enable_simulate_avr != xno])
fi

# Check if we want to simulate cortex-m0 ###################################
AC_ARG_ENABLE([simulate-cortex-m0],
            [AS_HELP_STRING([--enable-simulate-cortex-m0],
                [Enable the simulation for cortex-m0])],
            [],
            [ if [[ -z "$enable_simulate_cortex_m0" ]] ; then enable_simulate_cortex_m0=no; fi ],
            )

if test x$enable_simulate_cortex_m0 == xyes ; then
    AC_CHECK_PROG(simulate_m0_cmd, thumbulator, thumbulator)

    # Check the version supports the --elf flag
    AC_RUN_IFELSE([], [], [],
        [thumbulator_version=`thumbulator --version | grep "Version: 1.1.0" -c`])
    if test x$thumbulator_version == x0 ; then
        echo $thumbulator_version
        AC_MSG_FAILURE([Need a version of thumbulator which supports --elf])
    fi
    AC_SUBST(SIMULATORPATH, [thumbulator])
    AM_CONDITIONAL([SIMULATE], [test x$enable_simulate_cortex_m0 != xno])
fi


AC_CONFIG_FILES([src/2dfir/Makefile])
AC_CONFIG_FILES([src/adpcm/Makefile])
AC_CONFIG_FILES([src/blowfish/Makefile])
AC_CONFIG_FILES([src/bs/Makefile])
AC_CONFIG_FILES([src/bubblesort/Makefile])
AC_CONFIG_FILES([src/crc32/Makefile])
AC_CONFIG_FILES([src/cnt/Makefile])
AC_CONFIG_FILES([src/cubic/Makefile])
AC_CONFIG_FILES([src/duff/Makefile])
AC_CONFIG_FILES([src/dijkstra/Makefile])
AC_CONFIG_FILES([src/edn/Makefile])
AC_CONFIG_FILES([src/fasta/Makefile])
AC_CONFIG_FILES([src/fdct/Makefile])
AC_CONFIG_FILES([src/float_matmult/Makefile])
AC_CONFIG_FILES([src/gdb-advance/Makefile])
AC_CONFIG_FILES([src/gdb-all-types/Makefile])
AC_CONFIG_FILES([src/gdb-anon/Makefile])
AC_CONFIG_FILES([src/gdb-arrayidx/Makefile])
AC_CONFIG_FILES([src/gdb-async/Makefile])
AC_CONFIG_FILES([src/int_matmult/Makefile])
AC_CONFIG_FILES([src/nbody/Makefile])
AC_CONFIG_FILES([src/rijndael/Makefile])
AC_CONFIG_FILES([src/sha/Makefile])
AC_CONFIG_FILES([src/compress/Makefile])
AC_CONFIG_FILES([src/lms/Makefile])
AC_CONFIG_FILES([src/fft/Makefile])
AC_CONFIG_FILES([src/template/Makefile])
AC_CONFIG_FILES([src/platformcode/Makefile])
AC_CONFIG_FILES([analysis/Makefile])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT

echo
echo \*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*
echo
echo "Target platform               $with_platform"
echo "Target triple                 $host"
echo "Platform sources              $enable_platformsources"
if [[ -z "$SIMULATORPATH" ]]; then
    echo "Simulator                     none"
else
    echo "Simulator                     $SIMULATORPATH"
fi
