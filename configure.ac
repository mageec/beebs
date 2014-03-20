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

# Manually format the help string, so that we can have custom formatting on the RHS
AC_ARG_WITH([platform],
[  --with-platform         Select the platform compile for. Possible platforms
                          are:
                              stm32f0discovery
                              stm32vldiscovery
                              atmega328p
                              pic32mx250f128b
                              xmegaa3buxplained
                              msp-exp430f5529
                              msp-exp430fr5739
                              sam4lxplained],
    [],
    [with_platform=none]
    )

# Some platforms cannot compile certain benchmarks, so we exclude them
# from the build
EXCLUDED_BENCHMARKS=""

AM_CONDITIONAL([STM32F0DISCOVERY], [false])
AM_CONDITIONAL([STM32VLDISCOVERY], [false])
AM_CONDITIONAL([ATMEGA328P], [false])
AM_CONDITIONAL([PIC32MX250F128B], [false])
AM_CONDITIONAL([XMEGAA3BUXPLAINED], [false])
AM_CONDITIONAL([MSPEXP430F5529], [false])
AM_CONDITIONAL([MSPEXP430FR5739], [false])
AM_CONDITIONAL([SAM4LXPLAINED], [false])

save_CFLAGS=$CFLAGS
save_LDFLAGS=$LDFLAGS

case $with_platform in
    stm32f0discovery)
        if test x$host == x$build ; then
            AC_MSG_ERROR([Please rerun configure with --host=arm-none-eabi for this platform])
        fi

        # gcc-arm-embedded requires these libraries for the tests, else they'll fail
        AC_SUBST([AM_LDFLAGS], ["-lc -lnosys"])
        AC_SUBST([AM_CFLAGS], ["-mthumb -mcpu=cortex-m0 -DCORTEX_M0"])
        CFLAGS="$CFLAGS -mthumb -mcpu=cortex-m0 -DCORTEX_M0"
        LDFLAGS="$LDFLAGS -lc -lnosys"

        # enable_platformsources=yes

        if test x$enable_simulate == xyes; then
            enable_simulate_cortex_m0=yes
        fi

        AM_CONDITIONAL([STM32F0DISCOVERY], [true])
        ;;

    stm32vldiscovery)
        if test x$host == x$build ; then
            AC_MSG_ERROR([Please rerun configure with --host=arm-none-eabi for this platform])
        fi

        # gcc-arm-embedded requires these libraries for the tests, else they'll fail
        AC_SUBST([AM_LDFLAGS], ["-lc -lnosys"])
        AC_SUBST([AM_CFLAGS], ["-mthumb -mcpu=cortex-m3 -DCORTEX_M3"])
        CFLAGS="$CFLAGS -mthumb -mcpu=cortex-m3 -DCORTEX_M0"
        LDFLAGS="$LDFLAGS -lc -lnosys"

        # enable_platformsources=yes

        if test x$enable_simulate == xyes; then
            enable_simulate_cortex_m3=yes
        fi

        AM_CONDITIONAL([STM32VLDISCOVERY], [true])
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

    xmegaa3buxplained)
        if test x$host == x$build ; then
            AC_MSG_ERROR([Please rerun configure with --host=avr for this platform])
        fi

        # gcc does not support the atxmega256a3bu yet, but atxmega256a3 works
        # just fine.
        AC_SUBST([AM_CFLAGS], ["$AM_CFLAGS -mmcu=atxmega256a3 -std=gnu99 -DAVR_ATXMEGA"])
        if test x$enable_simulate == xyes; then
            enable_simulate_avr=yes
        fi

        EXCLUDED_BENCHMARKS="miniz"

        AM_CONDITIONAL([XMEGAA3BUXPLAINED], [true])
        ;;

   pic32mx250f128b)
        if test x$host == x$build ; then
            AC_MSG_ERROR([Please rerun configure with --host=pic32 for this platform])
        fi

        AC_SUBST([AM_CFLAGS], ["-mprocessor=32MX250F128B -mips32r2 -std=gnu99 -mips16 -DPIC -Wl,-wrap,main"])
        if test x$enable_simulate == xyes; then
            enable_simulate_pic=yes
        fi

        AM_CONDITIONAL([PIC32MX250F128B], [true])
        ;;

    msp-exp430f5529)
        if test x$host == x$build ; then
            AC_MSG_ERROR([Please rerun configure with --host=msp430 for this platform])
        fi

        AC_SUBST([AM_CFLAGS], ["-mmcu=msp430f5529 -std=gnu99 -mcpu=430 -DMSP430F"])
        if test x$enable_simulate == xyes; then
            enable_simulate_msp430=yes
        fi

        EXCLUDED_BENCHMARKS="miniz"

        CFLAGS="$CFLAGS -mmcu=msp430f5529 -std=gnu99 -mcpu=430 -DMSP430F"

        AM_CONDITIONAL([MSPEXP430F5529], [true])
        ;;

    msp-exp430fr5739)
        if test x$host == x$build ; then
            AC_MSG_ERROR([Please rerun configure with --host=msp430 for this platform])
        fi

        AC_SUBST([AM_CFLAGS], ["-mmcu=msp430fr5739 -std=gnu99 -mcpu=430 -DMSP430FR"])
        if test x$enable_simulate == xyes; then
            enable_simulate_msp430=yes
        fi

        EXCLUDED_BENCHMARKS="blowfish cubic dtoa float_matmult int_matmult nettle-cast128 rijndael stringsearch1 ns nsichneu ud miniz wikisort fir nettle-des whetstone"

        CFLAGS="$CFLAGS -mmcu=msp430fr5739 -std=gnu99 -mcpu=430 -DMSP430FR"

        AM_CONDITIONAL([MSPEXP430FR5739], [true])
        ;;

    sam4lxplained)
        if test x$host == x$build ; then
            AC_MSG_ERROR([Please rerun configure with --host=arm-none-eabi for this platform])
        fi

        # gcc-arm-embedded requires these libraries for the tests, else they'll fail
        AC_SUBST([AM_LDFLAGS], ["-lc -lnosys"])
        AC_SUBST([AM_CFLAGS], ["-mthumb -mcpu=cortex-m4 -DCORTEX_M4"])
        CFLAGS="$CFLAGS -mthumb -mcpu=cortex-m4 -DCORTEX_M4"
        LDFLAGS="$LDFLAGS -lc -lnosys"

        if test x$enable_simulate == xyes; then
            enable_simulate_cortex_m4=yes
        fi

        AM_CONDITIONAL([SAM4LXPLAINED], [true])
        ;;

    none)
        ;;

    *)
        AC_MSG_ERROR([Please specify a supported platform])
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

# ==== AC_CONFIG_FILES (This is a marker for the generate-benchmark.sh script)
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
if test x$SIMULATORPATH == x ; then
    echo "Simulator                     none"
else
    echo "Simulator                     $SIMULATORPATH"
fi

if test "x$EXCLUDED_BENCHMARKS" == x ; then
    echo "Excluded benchmarks           none"
else
    echo "Excluded benchmarks           $EXCLUDED_BENCHMARKS"
fi
