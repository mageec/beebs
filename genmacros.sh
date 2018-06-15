#!/bin/bash

# Script to generate some of the configuration for BEEBS
#
# Copyright (C) 2018 Embecosm Limited
#
# Contributor: Jeremy Bennett <jeremy.bennett@embecosm.com>
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
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# SPDX-License-Identifier: GPL-3.0-or-later

# This is a convenience script to generate repeat text in various
# files. Should never really need to be used.

bmlist="aha-compress          \
        aha-mont64            \
        bs                    \
        bubblesort            \
        cnt                   \
        compress              \
        cover                 \
        crc                   \
        crc32                 \
        ctl                   \
        ctl-stack             \
        ctl-string            \
        ctl-vector            \
        cubic                 \
        dijkstra              \
        dtoa                  \
        duff                  \
        edn                   \
        expint                \
        fac                   \
        fasta                 \
        fdct                  \
        fibcall               \
        fir                   \
        frac                  \
        huffbench             \
        insertsort            \
        janne_complex         \
        jfdctint              \
        lcdnum                \
        levenshtein           \
        ludcmp                \
        matmult               \
        matmult-float         \
        matmult-int           \
        mergesort             \
        miniz                 \
        minver                \
        nbody                 \
        ndes                  \
        nettle-arcfour        \
        nettle-cast128        \
        nettle-des            \
        nettle-md5            \
        newlib-exp            \
        newlib-log            \
        newlib-mod            \
        newlib-sqrt           \
        ns                    \
        nsichneu              \
        picojpeg              \
        prime                 \
        qrduino               \
        qsort                 \
        qurt                  \
        recursion             \
        rijndael              \
        select                \
        sglib-arraybinsearch  \
        sglib-arrayheapsort   \
        sglib-arrayquicksort  \
        sglib-arraysort       \
        sglib-dllist          \
        sglib-hashtable       \
        sglib-listinsertsort  \
        sglib-listsort        \
        sglib-queue           \
        sglib-rbtree          \
        slre                  \
        sqrt                  \
        st                    \
        statemate             \
        stb_perlin            \
        stringsearch1         \
        strstr                \
        tarai                 \
        template              \
        trio                  \
        trio-snprintf         \
        trio-sscanf           \
        ud                    \
        whetstone             \
        wikisort"

for bm in ${bmlist}
do
    bm_var=$(echo $bm | tr "-" "_")
    bm_uc=$(echo $bm_var | tr "[:lower:]" "[:upper:]")
    echo "AC_ARG_ENABLE([benchmark-${bm}],"
    echo "  [AS_HELP_STRING([--enable-benchmark-${bm}],"
    echo "     [Enable benchmark ${bm}])],"
    echo "  [case \"\${enableval}\" in"
    echo "      yes) benchmark_${bm_var}=true ;;"
    echo "      no)  benchmark_${bm_var}=false ;;"
    echo "      *)   AC_MSG_ERROR([bad value \${enableval} for --enable-benchmark-${bm}]) ;;"
    echo "   esac],"
    echo "  [benchmark_${bm_var}=true])"
    echo "AM_CONDITIONAL([ENABLED_BENCHMARK_${bm_uc}],"
    echo "               [test x$benchmark_${bm_var} = xtrue])"
    echo
done
