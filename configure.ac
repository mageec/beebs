# Main configure script for BEEBS

# Copyright (C) 2013-2014 Embecosm Limited and the University of Bristol
# Copyright (C) 2018 Embecosm Limited

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

# SPDX-License-Identifier: GPL-3.0-or-later

# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])

AC_INIT([beebs], [3.0], [beebs@mageec.org])
AC_CONFIG_MACRO_DIR([m4])

AC_CANONICAL_BUILD
AC_CANONICAL_HOST

AM_INIT_AUTOMAKE([1.11 -Wno-portability])
AM_MAINTAINER_MODE([enable])
AM_SILENT_RULES([yes])

LT_INIT
AC_SUBST([LIBTOOL_DEPS])

# Options for enabling/disabling each test in alphabetical order (see
# genmacros.sh for a script to generate all of this). To add one new test just
# insert the same pattern at the correct place in the list.

# Remember that ctl, matmult, sglib-arraysort and trio are not benchmarks
# themselves, but the frameworks from which others are created.

# NOTE. There is the m4_foreach macro, but it doesn't seem to be rich enough
# for this.

AC_ARG_ENABLE([benchmark-aha-compress],
  [AS_HELP_STRING([--enable-benchmark-aha-compress],
     [Enable benchmark aha-compress])],
  [case "${enableval}" in
      yes) benchmark_aha_compress=true ;;
      no)  benchmark_aha_compress=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-aha-compress]) ;;
   esac],
  [benchmark_aha_compress=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_AHA_COMPRESS],
               [test xaha_compress = xtrue])

AC_ARG_ENABLE([benchmark-aha-mont64],
  [AS_HELP_STRING([--enable-benchmark-aha-mont64],
     [Enable benchmark aha-mont64])],
  [case "${enableval}" in
      yes) benchmark_aha_mont64=true ;;
      no)  benchmark_aha_mont64=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-aha-mont64]) ;;
   esac],
  [benchmark_aha_mont64=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_AHA_MONT64],
               [test xaha_mont64 = xtrue])

AC_ARG_ENABLE([benchmark-bs],
  [AS_HELP_STRING([--enable-benchmark-bs],
     [Enable benchmark bs])],
  [case "${enableval}" in
      yes) benchmark_bs=true ;;
      no)  benchmark_bs=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-bs]) ;;
   esac],
  [benchmark_bs=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_BS],
               [test xbs = xtrue])

AC_ARG_ENABLE([benchmark-bubblesort],
  [AS_HELP_STRING([--enable-benchmark-bubblesort],
     [Enable benchmark bubblesort])],
  [case "${enableval}" in
      yes) benchmark_bubblesort=true ;;
      no)  benchmark_bubblesort=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-bubblesort]) ;;
   esac],
  [benchmark_bubblesort=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_BUBBLESORT],
               [test xbubblesort = xtrue])

AC_ARG_ENABLE([benchmark-cnt],
  [AS_HELP_STRING([--enable-benchmark-cnt],
     [Enable benchmark cnt])],
  [case "${enableval}" in
      yes) benchmark_cnt=true ;;
      no)  benchmark_cnt=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-cnt]) ;;
   esac],
  [benchmark_cnt=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_CNT],
               [test xcnt = xtrue])

AC_ARG_ENABLE([benchmark-compress],
  [AS_HELP_STRING([--enable-benchmark-compress],
     [Enable benchmark compress])],
  [case "${enableval}" in
      yes) benchmark_compress=true ;;
      no)  benchmark_compress=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-compress]) ;;
   esac],
  [benchmark_compress=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_COMPRESS],
               [test xcompress = xtrue])

AC_ARG_ENABLE([benchmark-cover],
  [AS_HELP_STRING([--enable-benchmark-cover],
     [Enable benchmark cover])],
  [case "${enableval}" in
      yes) benchmark_cover=true ;;
      no)  benchmark_cover=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-cover]) ;;
   esac],
  [benchmark_cover=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_COVER],
               [test xcover = xtrue])

AC_ARG_ENABLE([benchmark-crc],
  [AS_HELP_STRING([--enable-benchmark-crc],
     [Enable benchmark crc])],
  [case "${enableval}" in
      yes) benchmark_crc=true ;;
      no)  benchmark_crc=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-crc]) ;;
   esac],
  [benchmark_crc=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_CRC],
               [test xcrc = xtrue])

AC_ARG_ENABLE([benchmark-crc32],
  [AS_HELP_STRING([--enable-benchmark-crc32],
     [Enable benchmark crc32])],
  [case "${enableval}" in
      yes) benchmark_crc32=true ;;
      no)  benchmark_crc32=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-crc32]) ;;
   esac],
  [benchmark_crc32=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_CRC32],
               [test xcrc32 = xtrue])

AC_ARG_ENABLE([benchmark-ctl],
  [AS_HELP_STRING([--enable-benchmark-ctl],
     [Enable benchmark ctl])],
  [case "${enableval}" in
      yes) benchmark_ctl=true ;;
      no)  benchmark_ctl=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-ctl]) ;;
   esac],
  [benchmark_ctl=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_CTL],
               [test xctl = xtrue])

AC_ARG_ENABLE([benchmark-ctl-stack],
  [AS_HELP_STRING([--enable-benchmark-ctl-stack],
     [Enable benchmark ctl-stack])],
  [case "${enableval}" in
      yes) benchmark_ctl_stack=true ;;
      no)  benchmark_ctl_stack=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-ctl-stack]) ;;
   esac],
  [benchmark_ctl_stack=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_CTL_STACK],
               [test xctl_stack = xtrue])

AC_ARG_ENABLE([benchmark-ctl-string],
  [AS_HELP_STRING([--enable-benchmark-ctl-string],
     [Enable benchmark ctl-string])],
  [case "${enableval}" in
      yes) benchmark_ctl_string=true ;;
      no)  benchmark_ctl_string=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-ctl-string]) ;;
   esac],
  [benchmark_ctl_string=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_CTL_STRING],
               [test xctl_string = xtrue])

AC_ARG_ENABLE([benchmark-ctl-vector],
  [AS_HELP_STRING([--enable-benchmark-ctl-vector],
     [Enable benchmark ctl-vector])],
  [case "${enableval}" in
      yes) benchmark_ctl_vector=true ;;
      no)  benchmark_ctl_vector=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-ctl-vector]) ;;
   esac],
  [benchmark_ctl_vector=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_CTL_VECTOR],
               [test xctl_vector = xtrue])

AC_ARG_ENABLE([benchmark-cubic],
  [AS_HELP_STRING([--enable-benchmark-cubic],
     [Enable benchmark cubic])],
  [case "${enableval}" in
      yes) benchmark_cubic=true ;;
      no)  benchmark_cubic=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-cubic]) ;;
   esac],
  [benchmark_cubic=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_CUBIC],
               [test xcubic = xtrue])

AC_ARG_ENABLE([benchmark-dijkstra],
  [AS_HELP_STRING([--enable-benchmark-dijkstra],
     [Enable benchmark dijkstra])],
  [case "${enableval}" in
      yes) benchmark_dijkstra=true ;;
      no)  benchmark_dijkstra=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-dijkstra]) ;;
   esac],
  [benchmark_dijkstra=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_DIJKSTRA],
               [test xdijkstra = xtrue])

AC_ARG_ENABLE([benchmark-dtoa],
  [AS_HELP_STRING([--enable-benchmark-dtoa],
     [Enable benchmark dtoa])],
  [case "${enableval}" in
      yes) benchmark_dtoa=true ;;
      no)  benchmark_dtoa=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-dtoa]) ;;
   esac],
  [benchmark_dtoa=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_DTOA],
               [test xdtoa = xtrue])

AC_ARG_ENABLE([benchmark-duff],
  [AS_HELP_STRING([--enable-benchmark-duff],
     [Enable benchmark duff])],
  [case "${enableval}" in
      yes) benchmark_duff=true ;;
      no)  benchmark_duff=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-duff]) ;;
   esac],
  [benchmark_duff=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_DUFF],
               [test xduff = xtrue])

AC_ARG_ENABLE([benchmark-edn],
  [AS_HELP_STRING([--enable-benchmark-edn],
     [Enable benchmark edn])],
  [case "${enableval}" in
      yes) benchmark_edn=true ;;
      no)  benchmark_edn=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-edn]) ;;
   esac],
  [benchmark_edn=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_EDN],
               [test xedn = xtrue])

AC_ARG_ENABLE([benchmark-expint],
  [AS_HELP_STRING([--enable-benchmark-expint],
     [Enable benchmark expint])],
  [case "${enableval}" in
      yes) benchmark_expint=true ;;
      no)  benchmark_expint=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-expint]) ;;
   esac],
  [benchmark_expint=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_EXPINT],
               [test xexpint = xtrue])

AC_ARG_ENABLE([benchmark-fac],
  [AS_HELP_STRING([--enable-benchmark-fac],
     [Enable benchmark fac])],
  [case "${enableval}" in
      yes) benchmark_fac=true ;;
      no)  benchmark_fac=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-fac]) ;;
   esac],
  [benchmark_fac=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_FAC],
               [test xfac = xtrue])

AC_ARG_ENABLE([benchmark-fasta],
  [AS_HELP_STRING([--enable-benchmark-fasta],
     [Enable benchmark fasta])],
  [case "${enableval}" in
      yes) benchmark_fasta=true ;;
      no)  benchmark_fasta=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-fasta]) ;;
   esac],
  [benchmark_fasta=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_FASTA],
               [test xfasta = xtrue])

AC_ARG_ENABLE([benchmark-fdct],
  [AS_HELP_STRING([--enable-benchmark-fdct],
     [Enable benchmark fdct])],
  [case "${enableval}" in
      yes) benchmark_fdct=true ;;
      no)  benchmark_fdct=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-fdct]) ;;
   esac],
  [benchmark_fdct=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_FDCT],
               [test xfdct = xtrue])

AC_ARG_ENABLE([benchmark-fibcall],
  [AS_HELP_STRING([--enable-benchmark-fibcall],
     [Enable benchmark fibcall])],
  [case "${enableval}" in
      yes) benchmark_fibcall=true ;;
      no)  benchmark_fibcall=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-fibcall]) ;;
   esac],
  [benchmark_fibcall=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_FIBCALL],
               [test xfibcall = xtrue])

AC_ARG_ENABLE([benchmark-fir],
  [AS_HELP_STRING([--enable-benchmark-fir],
     [Enable benchmark fir])],
  [case "${enableval}" in
      yes) benchmark_fir=true ;;
      no)  benchmark_fir=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-fir]) ;;
   esac],
  [benchmark_fir=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_FIR],
               [test xfir = xtrue])

AC_ARG_ENABLE([benchmark-frac],
  [AS_HELP_STRING([--enable-benchmark-frac],
     [Enable benchmark frac])],
  [case "${enableval}" in
      yes) benchmark_frac=true ;;
      no)  benchmark_frac=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-frac]) ;;
   esac],
  [benchmark_frac=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_FRAC],
               [test xfrac = xtrue])

AC_ARG_ENABLE([benchmark-huffbench],
  [AS_HELP_STRING([--enable-benchmark-huffbench],
     [Enable benchmark huffbench])],
  [case "${enableval}" in
      yes) benchmark_huffbench=true ;;
      no)  benchmark_huffbench=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-huffbench]) ;;
   esac],
  [benchmark_huffbench=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_HUFFBENCH],
               [test xhuffbench = xtrue])

AC_ARG_ENABLE([benchmark-insertsort],
  [AS_HELP_STRING([--enable-benchmark-insertsort],
     [Enable benchmark insertsort])],
  [case "${enableval}" in
      yes) benchmark_insertsort=true ;;
      no)  benchmark_insertsort=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-insertsort]) ;;
   esac],
  [benchmark_insertsort=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_INSERTSORT],
               [test xinsertsort = xtrue])

AC_ARG_ENABLE([benchmark-janne_complex],
  [AS_HELP_STRING([--enable-benchmark-janne_complex],
     [Enable benchmark janne_complex])],
  [case "${enableval}" in
      yes) benchmark_janne_complex=true ;;
      no)  benchmark_janne_complex=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-janne_complex]) ;;
   esac],
  [benchmark_janne_complex=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_JANNE_COMPLEX],
               [test xjanne_complex = xtrue])

AC_ARG_ENABLE([benchmark-jfdctint],
  [AS_HELP_STRING([--enable-benchmark-jfdctint],
     [Enable benchmark jfdctint])],
  [case "${enableval}" in
      yes) benchmark_jfdctint=true ;;
      no)  benchmark_jfdctint=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-jfdctint]) ;;
   esac],
  [benchmark_jfdctint=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_JFDCTINT],
               [test xjfdctint = xtrue])

AC_ARG_ENABLE([benchmark-lcdnum],
  [AS_HELP_STRING([--enable-benchmark-lcdnum],
     [Enable benchmark lcdnum])],
  [case "${enableval}" in
      yes) benchmark_lcdnum=true ;;
      no)  benchmark_lcdnum=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-lcdnum]) ;;
   esac],
  [benchmark_lcdnum=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_LCDNUM],
               [test xlcdnum = xtrue])

AC_ARG_ENABLE([benchmark-levenshtein],
  [AS_HELP_STRING([--enable-benchmark-levenshtein],
     [Enable benchmark levenshtein])],
  [case "${enableval}" in
      yes) benchmark_levenshtein=true ;;
      no)  benchmark_levenshtein=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-levenshtein]) ;;
   esac],
  [benchmark_levenshtein=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_LEVENSHTEIN],
               [test xlevenshtein = xtrue])

AC_ARG_ENABLE([benchmark-ludcmp],
  [AS_HELP_STRING([--enable-benchmark-ludcmp],
     [Enable benchmark ludcmp])],
  [case "${enableval}" in
      yes) benchmark_ludcmp=true ;;
      no)  benchmark_ludcmp=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-ludcmp]) ;;
   esac],
  [benchmark_ludcmp=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_LUDCMP],
               [test xludcmp = xtrue])

AC_ARG_ENABLE([benchmark-matmult],
  [AS_HELP_STRING([--enable-benchmark-matmult],
     [Enable benchmark matmult])],
  [case "${enableval}" in
      yes) benchmark_matmult=true ;;
      no)  benchmark_matmult=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-matmult]) ;;
   esac],
  [benchmark_matmult=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_MATMULT],
               [test xmatmult = xtrue])

AC_ARG_ENABLE([benchmark-matmult-float],
  [AS_HELP_STRING([--enable-benchmark-matmult-float],
     [Enable benchmark matmult-float])],
  [case "${enableval}" in
      yes) benchmark_matmult_float=true ;;
      no)  benchmark_matmult_float=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-matmult-float]) ;;
   esac],
  [benchmark_matmult_float=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_MATMULT_FLOAT],
               [test xmatmult_float = xtrue])

AC_ARG_ENABLE([benchmark-matmult-int],
  [AS_HELP_STRING([--enable-benchmark-matmult-int],
     [Enable benchmark matmult-int])],
  [case "${enableval}" in
      yes) benchmark_matmult_int=true ;;
      no)  benchmark_matmult_int=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-matmult-int]) ;;
   esac],
  [benchmark_matmult_int=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_MATMULT_INT],
               [test xmatmult_int = xtrue])

AC_ARG_ENABLE([benchmark-mergesort],
  [AS_HELP_STRING([--enable-benchmark-mergesort],
     [Enable benchmark mergesort])],
  [case "${enableval}" in
      yes) benchmark_mergesort=true ;;
      no)  benchmark_mergesort=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-mergesort]) ;;
   esac],
  [benchmark_mergesort=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_MERGESORT],
               [test xmergesort = xtrue])

AC_ARG_ENABLE([benchmark-miniz],
  [AS_HELP_STRING([--enable-benchmark-miniz],
     [Enable benchmark miniz])],
  [case "${enableval}" in
      yes) benchmark_miniz=true ;;
      no)  benchmark_miniz=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-miniz]) ;;
   esac],
  [benchmark_miniz=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_MINIZ],
               [test xminiz = xtrue])

AC_ARG_ENABLE([benchmark-minver],
  [AS_HELP_STRING([--enable-benchmark-minver],
     [Enable benchmark minver])],
  [case "${enableval}" in
      yes) benchmark_minver=true ;;
      no)  benchmark_minver=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-minver]) ;;
   esac],
  [benchmark_minver=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_MINVER],
               [test xminver = xtrue])

AC_ARG_ENABLE([benchmark-nbody],
  [AS_HELP_STRING([--enable-benchmark-nbody],
     [Enable benchmark nbody])],
  [case "${enableval}" in
      yes) benchmark_nbody=true ;;
      no)  benchmark_nbody=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-nbody]) ;;
   esac],
  [benchmark_nbody=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_NBODY],
               [test xnbody = xtrue])

AC_ARG_ENABLE([benchmark-ndes],
  [AS_HELP_STRING([--enable-benchmark-ndes],
     [Enable benchmark ndes])],
  [case "${enableval}" in
      yes) benchmark_ndes=true ;;
      no)  benchmark_ndes=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-ndes]) ;;
   esac],
  [benchmark_ndes=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_NDES],
               [test xndes = xtrue])

AC_ARG_ENABLE([benchmark-nettle-arcfour],
  [AS_HELP_STRING([--enable-benchmark-nettle-arcfour],
     [Enable benchmark nettle-arcfour])],
  [case "${enableval}" in
      yes) benchmark_nettle_arcfour=true ;;
      no)  benchmark_nettle_arcfour=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-nettle-arcfour]) ;;
   esac],
  [benchmark_nettle_arcfour=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_NETTLE_ARCFOUR],
               [test xnettle_arcfour = xtrue])

AC_ARG_ENABLE([benchmark-nettle-cast128],
  [AS_HELP_STRING([--enable-benchmark-nettle-cast128],
     [Enable benchmark nettle-cast128])],
  [case "${enableval}" in
      yes) benchmark_nettle_cast128=true ;;
      no)  benchmark_nettle_cast128=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-nettle-cast128]) ;;
   esac],
  [benchmark_nettle_cast128=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_NETTLE_CAST128],
               [test xnettle_cast128 = xtrue])

AC_ARG_ENABLE([benchmark-nettle-des],
  [AS_HELP_STRING([--enable-benchmark-nettle-des],
     [Enable benchmark nettle-des])],
  [case "${enableval}" in
      yes) benchmark_nettle_des=true ;;
      no)  benchmark_nettle_des=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-nettle-des]) ;;
   esac],
  [benchmark_nettle_des=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_NETTLE_DES],
               [test xnettle_des = xtrue])

AC_ARG_ENABLE([benchmark-nettle-md5],
  [AS_HELP_STRING([--enable-benchmark-nettle-md5],
     [Enable benchmark nettle-md5])],
  [case "${enableval}" in
      yes) benchmark_nettle_md5=true ;;
      no)  benchmark_nettle_md5=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-nettle-md5]) ;;
   esac],
  [benchmark_nettle_md5=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_NETTLE_MD5],
               [test xnettle_md5 = xtrue])

AC_ARG_ENABLE([benchmark-newlib-exp],
  [AS_HELP_STRING([--enable-benchmark-newlib-exp],
     [Enable benchmark newlib-exp])],
  [case "${enableval}" in
      yes) benchmark_newlib_exp=true ;;
      no)  benchmark_newlib_exp=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-newlib-exp]) ;;
   esac],
  [benchmark_newlib_exp=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_NEWLIB_EXP],
               [test xnewlib_exp = xtrue])

AC_ARG_ENABLE([benchmark-newlib-log],
  [AS_HELP_STRING([--enable-benchmark-newlib-log],
     [Enable benchmark newlib-log])],
  [case "${enableval}" in
      yes) benchmark_newlib_log=true ;;
      no)  benchmark_newlib_log=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-newlib-log]) ;;
   esac],
  [benchmark_newlib_log=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_NEWLIB_LOG],
               [test xnewlib_log = xtrue])

AC_ARG_ENABLE([benchmark-newlib-mod],
  [AS_HELP_STRING([--enable-benchmark-newlib-mod],
     [Enable benchmark newlib-mod])],
  [case "${enableval}" in
      yes) benchmark_newlib_mod=true ;;
      no)  benchmark_newlib_mod=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-newlib-mod]) ;;
   esac],
  [benchmark_newlib_mod=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_NEWLIB_MOD],
               [test xnewlib_mod = xtrue])

AC_ARG_ENABLE([benchmark-newlib-sqrt],
  [AS_HELP_STRING([--enable-benchmark-newlib-sqrt],
     [Enable benchmark newlib-sqrt])],
  [case "${enableval}" in
      yes) benchmark_newlib_sqrt=true ;;
      no)  benchmark_newlib_sqrt=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-newlib-sqrt]) ;;
   esac],
  [benchmark_newlib_sqrt=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_NEWLIB_SQRT],
               [test xnewlib_sqrt = xtrue])

AC_ARG_ENABLE([benchmark-ns],
  [AS_HELP_STRING([--enable-benchmark-ns],
     [Enable benchmark ns])],
  [case "${enableval}" in
      yes) benchmark_ns=true ;;
      no)  benchmark_ns=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-ns]) ;;
   esac],
  [benchmark_ns=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_NS],
               [test xns = xtrue])

AC_ARG_ENABLE([benchmark-nsichneu],
  [AS_HELP_STRING([--enable-benchmark-nsichneu],
     [Enable benchmark nsichneu])],
  [case "${enableval}" in
      yes) benchmark_nsichneu=true ;;
      no)  benchmark_nsichneu=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-nsichneu]) ;;
   esac],
  [benchmark_nsichneu=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_NSICHNEU],
               [test xnsichneu = xtrue])

AC_ARG_ENABLE([benchmark-picojpeg],
  [AS_HELP_STRING([--enable-benchmark-picojpeg],
     [Enable benchmark picojpeg])],
  [case "${enableval}" in
      yes) benchmark_picojpeg=true ;;
      no)  benchmark_picojpeg=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-picojpeg]) ;;
   esac],
  [benchmark_picojpeg=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_PICOJPEG],
               [test xpicojpeg = xtrue])

AC_ARG_ENABLE([benchmark-prime],
  [AS_HELP_STRING([--enable-benchmark-prime],
     [Enable benchmark prime])],
  [case "${enableval}" in
      yes) benchmark_prime=true ;;
      no)  benchmark_prime=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-prime]) ;;
   esac],
  [benchmark_prime=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_PRIME],
               [test xprime = xtrue])

AC_ARG_ENABLE([benchmark-qrduino],
  [AS_HELP_STRING([--enable-benchmark-qrduino],
     [Enable benchmark qrduino])],
  [case "${enableval}" in
      yes) benchmark_qrduino=true ;;
      no)  benchmark_qrduino=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-qrduino]) ;;
   esac],
  [benchmark_qrduino=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_QRDUINO],
               [test xqrduino = xtrue])

AC_ARG_ENABLE([benchmark-qsort],
  [AS_HELP_STRING([--enable-benchmark-qsort],
     [Enable benchmark qsort])],
  [case "${enableval}" in
      yes) benchmark_qsort=true ;;
      no)  benchmark_qsort=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-qsort]) ;;
   esac],
  [benchmark_qsort=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_QSORT],
               [test xqsort = xtrue])

AC_ARG_ENABLE([benchmark-qurt],
  [AS_HELP_STRING([--enable-benchmark-qurt],
     [Enable benchmark qurt])],
  [case "${enableval}" in
      yes) benchmark_qurt=true ;;
      no)  benchmark_qurt=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-qurt]) ;;
   esac],
  [benchmark_qurt=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_QURT],
               [test xqurt = xtrue])

AC_ARG_ENABLE([benchmark-recursion],
  [AS_HELP_STRING([--enable-benchmark-recursion],
     [Enable benchmark recursion])],
  [case "${enableval}" in
      yes) benchmark_recursion=true ;;
      no)  benchmark_recursion=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-recursion]) ;;
   esac],
  [benchmark_recursion=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_RECURSION],
               [test xrecursion = xtrue])

AC_ARG_ENABLE([benchmark-rijndael],
  [AS_HELP_STRING([--enable-benchmark-rijndael],
     [Enable benchmark rijndael])],
  [case "${enableval}" in
      yes) benchmark_rijndael=true ;;
      no)  benchmark_rijndael=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-rijndael]) ;;
   esac],
  [benchmark_rijndael=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_RIJNDAEL],
               [test xrijndael = xtrue])

AC_ARG_ENABLE([benchmark-select],
  [AS_HELP_STRING([--enable-benchmark-select],
     [Enable benchmark select])],
  [case "${enableval}" in
      yes) benchmark_select=true ;;
      no)  benchmark_select=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-select]) ;;
   esac],
  [benchmark_select=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_SELECT],
               [test xselect = xtrue])

AC_ARG_ENABLE([benchmark-sglib-arraybinsearch],
  [AS_HELP_STRING([--enable-benchmark-sglib-arraybinsearch],
     [Enable benchmark sglib-arraybinsearch])],
  [case "${enableval}" in
      yes) benchmark_sglib_arraybinsearch=true ;;
      no)  benchmark_sglib_arraybinsearch=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-sglib-arraybinsearch]) ;;
   esac],
  [benchmark_sglib_arraybinsearch=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_SGLIB_ARRAYBINSEARCH],
               [test xsglib_arraybinsearch = xtrue])

AC_ARG_ENABLE([benchmark-sglib-arrayheapsort],
  [AS_HELP_STRING([--enable-benchmark-sglib-arrayheapsort],
     [Enable benchmark sglib-arrayheapsort])],
  [case "${enableval}" in
      yes) benchmark_sglib_arrayheapsort=true ;;
      no)  benchmark_sglib_arrayheapsort=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-sglib-arrayheapsort]) ;;
   esac],
  [benchmark_sglib_arrayheapsort=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_SGLIB_ARRAYHEAPSORT],
               [test xsglib_arrayheapsort = xtrue])

AC_ARG_ENABLE([benchmark-sglib-arrayquicksort],
  [AS_HELP_STRING([--enable-benchmark-sglib-arrayquicksort],
     [Enable benchmark sglib-arrayquicksort])],
  [case "${enableval}" in
      yes) benchmark_sglib_arrayquicksort=true ;;
      no)  benchmark_sglib_arrayquicksort=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-sglib-arrayquicksort]) ;;
   esac],
  [benchmark_sglib_arrayquicksort=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_SGLIB_ARRAYQUICKSORT],
               [test xsglib_arrayquicksort = xtrue])

AC_ARG_ENABLE([benchmark-sglib-arraysort],
  [AS_HELP_STRING([--enable-benchmark-sglib-arraysort],
     [Enable benchmark sglib-arraysort])],
  [case "${enableval}" in
      yes) benchmark_sglib_arraysort=true ;;
      no)  benchmark_sglib_arraysort=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-sglib-arraysort]) ;;
   esac],
  [benchmark_sglib_arraysort=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_SGLIB_ARRAYSORT],
               [test xsglib_arraysort = xtrue])

AC_ARG_ENABLE([benchmark-sglib-dllist],
  [AS_HELP_STRING([--enable-benchmark-sglib-dllist],
     [Enable benchmark sglib-dllist])],
  [case "${enableval}" in
      yes) benchmark_sglib_dllist=true ;;
      no)  benchmark_sglib_dllist=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-sglib-dllist]) ;;
   esac],
  [benchmark_sglib_dllist=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_SGLIB_DLLIST],
               [test xsglib_dllist = xtrue])

AC_ARG_ENABLE([benchmark-sglib-hashtable],
  [AS_HELP_STRING([--enable-benchmark-sglib-hashtable],
     [Enable benchmark sglib-hashtable])],
  [case "${enableval}" in
      yes) benchmark_sglib_hashtable=true ;;
      no)  benchmark_sglib_hashtable=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-sglib-hashtable]) ;;
   esac],
  [benchmark_sglib_hashtable=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_SGLIB_HASHTABLE],
               [test xsglib_hashtable = xtrue])

AC_ARG_ENABLE([benchmark-sglib-listinsertsort],
  [AS_HELP_STRING([--enable-benchmark-sglib-listinsertsort],
     [Enable benchmark sglib-listinsertsort])],
  [case "${enableval}" in
      yes) benchmark_sglib_listinsertsort=true ;;
      no)  benchmark_sglib_listinsertsort=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-sglib-listinsertsort]) ;;
   esac],
  [benchmark_sglib_listinsertsort=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_SGLIB_LISTINSERTSORT],
               [test xsglib_listinsertsort = xtrue])

AC_ARG_ENABLE([benchmark-sglib-listsort],
  [AS_HELP_STRING([--enable-benchmark-sglib-listsort],
     [Enable benchmark sglib-listsort])],
  [case "${enableval}" in
      yes) benchmark_sglib_listsort=true ;;
      no)  benchmark_sglib_listsort=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-sglib-listsort]) ;;
   esac],
  [benchmark_sglib_listsort=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_SGLIB_LISTSORT],
               [test xsglib_listsort = xtrue])

AC_ARG_ENABLE([benchmark-sglib-queue],
  [AS_HELP_STRING([--enable-benchmark-sglib-queue],
     [Enable benchmark sglib-queue])],
  [case "${enableval}" in
      yes) benchmark_sglib_queue=true ;;
      no)  benchmark_sglib_queue=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-sglib-queue]) ;;
   esac],
  [benchmark_sglib_queue=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_SGLIB_QUEUE],
               [test xsglib_queue = xtrue])

AC_ARG_ENABLE([benchmark-sglib-rbtree],
  [AS_HELP_STRING([--enable-benchmark-sglib-rbtree],
     [Enable benchmark sglib-rbtree])],
  [case "${enableval}" in
      yes) benchmark_sglib_rbtree=true ;;
      no)  benchmark_sglib_rbtree=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-sglib-rbtree]) ;;
   esac],
  [benchmark_sglib_rbtree=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_SGLIB_RBTREE],
               [test xsglib_rbtree = xtrue])

AC_ARG_ENABLE([benchmark-slre],
  [AS_HELP_STRING([--enable-benchmark-slre],
     [Enable benchmark slre])],
  [case "${enableval}" in
      yes) benchmark_slre=true ;;
      no)  benchmark_slre=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-slre]) ;;
   esac],
  [benchmark_slre=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_SLRE],
               [test xslre = xtrue])

AC_ARG_ENABLE([benchmark-sqrt],
  [AS_HELP_STRING([--enable-benchmark-sqrt],
     [Enable benchmark sqrt])],
  [case "${enableval}" in
      yes) benchmark_sqrt=true ;;
      no)  benchmark_sqrt=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-sqrt]) ;;
   esac],
  [benchmark_sqrt=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_SQRT],
               [test xsqrt = xtrue])

AC_ARG_ENABLE([benchmark-st],
  [AS_HELP_STRING([--enable-benchmark-st],
     [Enable benchmark st])],
  [case "${enableval}" in
      yes) benchmark_st=true ;;
      no)  benchmark_st=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-st]) ;;
   esac],
  [benchmark_st=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_ST],
               [test xst = xtrue])

AC_ARG_ENABLE([benchmark-statemate],
  [AS_HELP_STRING([--enable-benchmark-statemate],
     [Enable benchmark statemate])],
  [case "${enableval}" in
      yes) benchmark_statemate=true ;;
      no)  benchmark_statemate=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-statemate]) ;;
   esac],
  [benchmark_statemate=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_STATEMATE],
               [test xstatemate = xtrue])

AC_ARG_ENABLE([benchmark-stb_perlin],
  [AS_HELP_STRING([--enable-benchmark-stb_perlin],
     [Enable benchmark stb_perlin])],
  [case "${enableval}" in
      yes) benchmark_stb_perlin=true ;;
      no)  benchmark_stb_perlin=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-stb_perlin]) ;;
   esac],
  [benchmark_stb_perlin=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_STB_PERLIN],
               [test xstb_perlin = xtrue])

AC_ARG_ENABLE([benchmark-stringsearch1],
  [AS_HELP_STRING([--enable-benchmark-stringsearch1],
     [Enable benchmark stringsearch1])],
  [case "${enableval}" in
      yes) benchmark_stringsearch1=true ;;
      no)  benchmark_stringsearch1=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-stringsearch1]) ;;
   esac],
  [benchmark_stringsearch1=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_STRINGSEARCH1],
               [test xstringsearch1 = xtrue])

AC_ARG_ENABLE([benchmark-strstr],
  [AS_HELP_STRING([--enable-benchmark-strstr],
     [Enable benchmark strstr])],
  [case "${enableval}" in
      yes) benchmark_strstr=true ;;
      no)  benchmark_strstr=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-strstr]) ;;
   esac],
  [benchmark_strstr=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_STRSTR],
               [test xstrstr = xtrue])

AC_ARG_ENABLE([benchmark-tarai],
  [AS_HELP_STRING([--enable-benchmark-tarai],
     [Enable benchmark tarai])],
  [case "${enableval}" in
      yes) benchmark_tarai=true ;;
      no)  benchmark_tarai=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-tarai]) ;;
   esac],
  [benchmark_tarai=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_TARAI],
               [test xtarai = xtrue])

AC_ARG_ENABLE([benchmark-template],
  [AS_HELP_STRING([--enable-benchmark-template],
     [Enable benchmark template])],
  [case "${enableval}" in
      yes) benchmark_template=true ;;
      no)  benchmark_template=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-template]) ;;
   esac],
  [benchmark_template=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_TEMPLATE],
               [test xtemplate = xtrue])

AC_ARG_ENABLE([benchmark-trio],
  [AS_HELP_STRING([--enable-benchmark-trio],
     [Enable benchmark trio])],
  [case "${enableval}" in
      yes) benchmark_trio=true ;;
      no)  benchmark_trio=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-trio]) ;;
   esac],
  [benchmark_trio=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_TRIO],
               [test xtrio = xtrue])

AC_ARG_ENABLE([benchmark-trio-snprintf],
  [AS_HELP_STRING([--enable-benchmark-trio-snprintf],
     [Enable benchmark trio-snprintf])],
  [case "${enableval}" in
      yes) benchmark_trio_snprintf=true ;;
      no)  benchmark_trio_snprintf=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-trio-snprintf]) ;;
   esac],
  [benchmark_trio_snprintf=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_TRIO_SNPRINTF],
               [test xtrio_snprintf = xtrue])

AC_ARG_ENABLE([benchmark-trio-sscanf],
  [AS_HELP_STRING([--enable-benchmark-trio-sscanf],
     [Enable benchmark trio-sscanf])],
  [case "${enableval}" in
      yes) benchmark_trio_sscanf=true ;;
      no)  benchmark_trio_sscanf=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-trio-sscanf]) ;;
   esac],
  [benchmark_trio_sscanf=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_TRIO_SSCANF],
               [test xtrio_sscanf = xtrue])

AC_ARG_ENABLE([benchmark-ud],
  [AS_HELP_STRING([--enable-benchmark-ud],
     [Enable benchmark ud])],
  [case "${enableval}" in
      yes) benchmark_ud=true ;;
      no)  benchmark_ud=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-ud]) ;;
   esac],
  [benchmark_ud=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_UD],
               [test xud = xtrue])

AC_ARG_ENABLE([benchmark-whetstone],
  [AS_HELP_STRING([--enable-benchmark-whetstone],
     [Enable benchmark whetstone])],
  [case "${enableval}" in
      yes) benchmark_whetstone=true ;;
      no)  benchmark_whetstone=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-whetstone]) ;;
   esac],
  [benchmark_whetstone=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_WHETSTONE],
               [test xwhetstone = xtrue])

AC_ARG_ENABLE([benchmark-wikisort],
  [AS_HELP_STRING([--enable-benchmark-wikisort],
     [Enable benchmark wikisort])],
  [case "${enableval}" in
      yes) benchmark_wikisort=true ;;
      no)  benchmark_wikisort=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-benchmark-wikisort]) ;;
   esac],
  [benchmark_wikisort=true])
AM_CONDITIONAL([ENABLED_BENCHMARK_WIKISORT],
               [test xwikisort = xtrue])

# Work out which architecture we need
# Also pass this through to be substituted

arch=$host_cpu

# Option for selecting the target board and check if it exists

AC_ARG_WITH([board],
    [AS_HELP_STRING([--with-board], [Select the board to target])],
    [],
    [with_board=none]
    )
board=$with_board

AC_CHECK_FILE($srcdir/config/$arch/boards/$board,
              [],
	      AC_MSG_ERROR(["$board" board config directory not found])

# Option for selecting the target chip and echeck if it exists

AC_ARG_WITH([chip],
[AS_HELP_STRING([--with-chip], [Select the chip to target])],
    [],
    [with_chip=generic]
    )
chip=$with_chip

AC_CHECK_FILE($srcdir/config/$arch/chips/$chip; then
              [],
	      AC_MSG_ERROR(["$chip" chip config directory not found])

# Execute any architecture, board or chip specific configuration. These can
# set architecture, chip and board CPPFLAGS, CFLAGS and LDFLAGS and exclude
# individual tests by undefining HAVE_BENCHMARK_<bm>.

AC_CHECK_FILE($srcdir/config/$arch/arch.cfg,
              [source $srcdir/config/$arch/arch.cfg],
	      [])
AC_CHECK_FILE($srcdir/config/$arch/boards/$board/board.cfg,
              [source $srcdir/config/$arch/boards/$board/board.cfg],
	      [])
AC_CHECK_FILE($srcdir/config/$arch/chips/$chip/chip.cfg,
              [source $srcdir/config/$arch/chips/$chip/chip.cfg]
	      [])

AM_CONDITIONAL([CHIPSUPPORT_C],
	       [test -f $srcdir/config/$arch/chips/$chip/chipsupport.c])

# Check for support headers

AC_CHECK_FILE($srcdir/config/$arch/boards/$board/boardsupport.h,
              [AC_DEFINE([HAVE_BOARDSUPPORT_H], [1],
	                 [Board support header is present])],
	      [])

AC_CHECK_FILE($srcdir/config/$arch/chips/$chip/chipsupport.h,
              [AC_DEFINE([HAVE_CHIPSUPPORT_H], [1],
	                 [Chip support header is present])],
	      [])

# Test whether we have a calibration file

AC_CHECK_FILE($srcdir/config/$arch/boards/$board/calibration,
              [AC_DEFINE([HAVE_CALIBRATION], [1], [Calibration file is present])
               HAVE_CALIBRATION=yes],
	      [])
AM_CONDITIONAL([CALIBRATION], [test x$HAVE_CALIBRATION == xyes])

# Architecture, board and chip specific CFLAGS and LDFLAGS

# Sometimes we need to have the CFLAGS and LDFLAGS set so that
# the config test pass. We save them first so we can restore them later
confsave_CFLAGS=$CFLAGS
confsave_LDFLAGS=$LDFLAGS

CFLAGS="$CFLAGS $ARCH_CFLAGS $CHIP_CFLAGS $BOARD_CFLAGS"
LDFLAGS="$LDFLAGS $ARCH_LDFLAGS $CHIP_LDFLAGS $BOARD_LDFLAGS"

# If we pass the --host option, then AC_PROG_CC will select the
# correct cross-compiler for us.

AC_PROG_CC
AM_PROG_AS
AC_PROG_CC_C99

# Our custom flags

CPPFLAGS="-I $(top_srcdir)/include $CPPFLAGS"
CPPFLAGS="-I $(top_srcdir)/config/@ARCH@/boards/@BOARD@ $CPPFLAGS"
CPPFLAGS="-I $(top_srcdir)/config/@ARCH@/chips/@CHIP@ $CPPFLAGS"

# Add in the architecture, board and chip specific CPPFLAGS, CFLAGS and LDFLAGS

CPPFLAGS="$CPPFLAGS $ARCH_CFLAGS $CHIP_CFLAGS $BOARD_CFLAGS"
CFLAGS="$CFLAGS $ARCH_CFLAGS $CHIP_CFLAGS $BOARD_CFLAGS"
LDFLAGS="$LDFLAGS $ARCH_CFLAGS $CHIP_CFLAGS $BOARD_CFLAGS"

AC_SUBST([CPPFLAGS])
AC_SUBST([CFLAGS])
AC_SUBST([LDFLAGS])

# Substitute architecture, board and chip (do we really need this)

AC_SUBST(ARCH, $arch)
AC_SUBST(BOARD, $board)
AC_SUBST(CHIP, $chip)

# Safety check we haven't been given a nonsense srcdir

AC_CONFIG_SRCDIR([src/])

# Generate the config.h

AC_CONFIG_HEADERS([config.h])

# Generate makefiles

AC_CONFIG_FILES([Makefile                          \
                 doc/Makefile                      \
                 src/aha-compress/Makefile         \
		 src/aha-mont64/Makefile           \
                 src/bs/Makefile                   \
                 src/bubblesort/Makefile           \
                 src/cnt/Makefile                  \
                 src/compress/Makefile             \
                 src/cover/Makefile                \
                 src/crc/Makefile                  \
                 src/crc32/Makefile                \
                 src/ctl/Makefile                  \
                 src/ctl-stack/Makefile            \
                 src/ctl-string/Makefile           \
                 src/ctl-vector/Makefile           \
                 src/cubic/Makefile                \
                 src/dijkstra/Makefile             \
                 src/dtoa/Makefile                 \
                 src/duff/Makefile                 \
                 src/edn/Makefile                  \
                 src/expint/Makefile               \
                 src/fac/Makefile                  \
                 src/fasta/Makefile                \
                 src/fdct/Makefile                 \
                 src/fibcall/Makefile              \
                 src/fir/Makefile                  \
                 src/frac/Makefile                 \
                 src/huffbench/Makefile            \
                 src/insertsort/Makefile           \
                 src/janne_complex/Makefile        \
                 src/jfdctint/Makefile             \
                 src/lcdnum/Makefile               \
                 src/levenshtein/Makefile          \
                 src/ludcmp/Makefile               \
                 src/matmult/Makefile              \
                 src/matmult-float/Makefile        \
                 src/matmult-int/Makefile          \
                 src/mergesort/Makefile            \
                 src/miniz/Makefile                \
                 src/minver/Makefile               \
                 src/nbody/Makefile                \
                 src/ndes/Makefile                 \
                 src/nettle-arcfour/Makefile       \
                 src/nettle-cast128/Makefile       \
                 src/nettle-des/Makefile           \
                 src/nettle-md5/Makefile           \
                 src/newlib-exp/Makefile           \
                 src/newlib-log/Makefile           \
                 src/newlib-mod/Makefile           \
                 src/newlib-sqrt/Makefile          \
                 src/ns/Makefile                   \
                 src/nsichneu/Makefile             \
                 src/picojpeg/Makefile             \
                 src/prime/Makefile                \
                 src/qrduino/Makefile              \
                 src/qsort/Makefile                \
                 src/qurt/Makefile                 \
                 src/recursion/Makefile            \
                 src/rijndael/Makefile             \
                 src/select/Makefile               \
                 src/sglib-arraybinsearch/Makefile \
                 src/sglib-arrayheapsort/Makefile  \
                 src/sglib-arrayquicksort/Makefile \
                 src/sglib-arraysort/Makefile      \
                 src/sglib-dllist/Makefile         \
                 src/sglib-hashtable/Makefile      \
                 src/sglib-listinsertsort/Makefile \
                 src/sglib-listsort/Makefile       \
                 src/sglib-queue/Makefile          \
                 src/sglib-rbtree/Makefile         \
                 src/slre/Makefile                 \
                 src/sqrt/Makefile                 \
                 src/st/Makefile                   \
                 src/statemate/Makefile            \
                 src/stb_perlin/Makefile           \
                 src/stringsearch1/Makefile        \
                 src/strstr/Makefile               \
                 src/tarai/Makefile                \
                 src/template/Makefile             \
                 src/trio/Makefile                 \
                 src/trio-snprintf/Makefile        \
                 src/trio-sscanf/Makefile          \
                 src/ud/Makefile                   \
                 src/whetstone/Makefile            \
                 src/wikisort/Makefile             \
		 support/Makefile])

# And spit it all out

AC_OUTPUT
