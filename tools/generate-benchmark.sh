#!/bin/sh
#  Generate an empty benchmark.
#
#  Copyright (C) 2014 Embecosm Limited and University of Bristol
#
#  This file is part of the Bristol/Embecosm Embedded Benchmark Suite.
#
#  Contributor Pierre Langlois <pierre.langlois@embecosm.com>
#
#  This program is free software: you can redistribute it and/or modify it
#  under the terms of the GNU Lesser General Public License as published by the
#  Free Software Foundation, either version 3 of the License, or (at your
#  option) any later version.
#
#  This program is distributed in the hope that it will be useful, but WITHOUT
#  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
#  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
#  for more details.
#
#  You should have received a copy of the GNU Lesser General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.

usage () {
  cat << EOF
Usage: ./tools/generate-benchmark.sh <benchmark name> [source name]
EOF
}

# Change to the root directory.
cd `git rev-parse --show-toplevel`

if [ $# -eq 0 ]; then
  usage
  exit
fi

BENCH_NAME=$1

AUTHOR_EMAIL=`git config user.email`
AUTHOR_NAME=`git config user.name`
MAKEFILE_AM="src/${BENCH_NAME}/Makefile.am"
MAKEFILE="src/${BENCH_NAME}/Makefile"

if [ $# -gt 1 ]; then
  SOURCE="src/${BENCH_NAME}/${2}.c"
  SOURCE_FILE=$2
else
  SOURCE="src/${BENCH_NAME}/${BENCH_NAME}.c"
  SOURCE_FILE=${BENCH_NAME}
fi

DIR="src/${BENCH_NAME}"

if [ -d ${DIR} ]; then
  echo "Benchmark ${BENCH_NAME} already exists"
  usage
  exit
fi

echo "Generate ${MAKEFILE_AM}"

mkdir ${DIR}

cat > ${MAKEFILE_AM} << EOF
#   Makefile.am for building a BEEBS benchmark
#
#   Copyright (C) 2014 Embecosm Limited and University of Bristol
#
#   This file is part of the Bristol/Embecosm Embedded Benchmark Suite.
#
#   Contributor: ${AUTHOR_NAME} <${AUTHOR_EMAIL}>
#
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.

bin_PROGRAMS=${SOURCE_FILE}
${SOURCE_FILE}_SOURCES=${SOURCE_FILE}.c

include \$(top_srcdir)/src/common.mk.am

${SOURCE_FILE}_SOURCES += \${platform_src}
EOF

echo "Generate ${SOURCE}"

cat > ${SOURCE} << EOF
/* BEEBS ${BENCH_NAME} benchmark

   *** Put any preceding copyright here ***
   Copyright (C) 2014 Embecosm Limited and University of Bristol

   Contributor ${AUTHOR_NAME} <${AUTHOR_EMAIL}>

   This file is part of the Bristol/Embecosm Embedded Benchmark Suite.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program. If not, see <http://www.gnu.org/licenses/>. */

#include "platformcode.h"

/* This scale factor will be changed to equalise the runtime of the
   benchmarks. */
#define SCALE_FACTOR    (REPEAT_FACTOR >> 0)


void
benchmark (void)
{
  /* Code to benchmark goes here */
}


int
main (void)
{
  int i;

  initialise_trigger ();
  start_trigger ();

  for (i = 0; i < SCALE_FACTOR; i++)
    benchmark ();

  stop_trigger ();
  return 0;
}
EOF

echo "Add ${MAKEFILE} to configure.ac"

sed "/# ==== AC_CONFIG_FILES/i AC_CONFIG_FILES([${MAKEFILE}])" configure.ac > \
  configure.ac.tmp
mv configure.ac.tmp configure.ac

echo "Add ${DIR} to Makefile.am"

sed "/# ==== SUBDIRS/i SUBDIRS+=${DIR}" Makefile.am > \
  Makefile.am.tmp
mv Makefile.am.tmp Makefile.am
