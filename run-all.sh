#!/bin/sh
# Script to run all the benchmarks

# Copyright (C) 2013  Embecosm Limited <info@embecosm.com>

# Contributor Jeremy Bennett <jeremy.bennett@embecosm.com>

# This file is part of the low power benchmark

# This program is free software: you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as published by the
# Free Software Foundation, either version 3 of the License, or (at your
# option) any later version.

# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
# for more details.

# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# Function to run one of the benchmarks
# @param $1 The benchmark directory
runone () {
    d=$1
    cd ${d}

    # Compile all the tests
    for f in *.c
    do
	if ! ${CC} -g -c ${CFLAGS} -I.. ${f} >> ${logf} 2>&1
	then
	    echo "ERROR: Failed to compile ${d}/${f}"
	    exit 1
	fi
    done

    # Link the test
    if ! ${CC} -g ${LDFLAGS} -o ${d} *.o ../platformcode.o >> ${logf} 2>&1
    then
	echo "ERROR: Failed to link ${d}/${d}"
	exit 1
    fi

    # Measure all the sizes. First line is header to be discarded, then do
    # tidy output.
    avr-size *.o | sed -n -e '2,$p' > ${tmpf}
    text=`cut -c 1-7 ${tmpf} | sed -e '2,$s/$/ +/' -e '$s/$/ p/' | dc`
    data=`cut -c 9-15 ${tmpf} | sed -e '2,$s/$/ +/' -e '$s/$/ p/' | dc`
    bss=`cut -c 17-23 ${tmpf} | sed -e '2,$s/$/ +/' -e '$s/$/ p/' | dc`

    printf "%-15s %7d %7d %7d" "${d}" ${text} ${data} ${bss} | tee -a ${resf}

    # Now check if we are too big to run.
    avr-size *.o > ${tmpf}
    text=`tail -1 ${tmpf} | cut -c 1-7 | sed -e 's/$/ p/' | dc`
    data=`tail -1 ${tmpf} | cut -c 9-15 | sed -e 's/$/ p/' | dc`
    bss=`tail -1 ${tmpf} | cut -c 17-23 | sed -e 's/$/ p/' | dc`
    ro=${text}
    rw=`echo ${data} ${bss} + p | dc`

    if [ \( ${ro} -gt ${MAX_ROM} \) -a \( ${rw} -gt ${MAX_RAM} \) ]
    then
	printf "           - program and data too large\n" | tee -a ${resf}
    elif [ ${ro} -gt ${MAX_ROM} ]
    then
	printf "           - program too large\n" | tee -a ${resf}
    elif [ ${rw} -gt ${MAX_RAM} ]
    then
	printf "           - data too large\n" | tee -a ${resf}
    else
        # Run the test and count the cycles, then do tidy output
	if ! avr-gdb ${d} \
	    -ex 'target remote :51000' \
	    -ex 'hbreak _exit' \
	    -ex 'monitor reset' \
	    -ex 'load' \
	    -ex 'continue' \
	    -ex 'monitor timestamp' \
	    -ex 'detach' \
	    -ex 'quit' 2>&1 | tee -a ${logf} > ${tmpf}
	then
	    echo "ERROR: Failed to run ${d}/${d}"
	    exit 1
	fi

	cycles=`sed -n -e 's/Cycles since last call: //p' ${tmpf}`
	printf " %11d\n" ${cycles} | tee -a ${resf}
    fi

    # Back to parent directory
    cd ..
}

# Function to run all the tests
# @param $* benchmarks to run
runall () {

    # The platform support functions.
    if ! ${CC} -g ${CFLAGS} -c platformcode.c
    then
	echo "ERROR: Failed to compile platform code"
	exit 1
    fi

    # The header
    builddate=`${CC} --version | sed -n -e 's/^.*built \([0-9]*\).*$/\1/p'`
    echo "$CC built ${builddate}" | tee -a ${resf}
    echo "  CFLAGS  = ${CFLAGS}" | tee -a ${resf}
    echo "  LDFLAGS = ${LDFLAGS}" | tee -a ${resf}
    echo "benchmark          text    data     bss      cycles" | tee -a ${resf}
    echo "=========          ====    ====     ===      ======" | tee -a ${resf}

    # The benchmarks
    for d in $*
    do
	runone $d
    done
}

# Set up a results file
resd=`pwd`/results
mkdir -p ${resd}
resf=${resd}/res-$(date +%F-%H%M%S)

# Define MAX_RAM, MAX_ROM, CC, CFLAGS and LDFLAGS as appropriate. Defaults are
# for AVR8, which has 128KB of Flash and 4KB of RAM (256 bytes used for system
# and min 256 bytes for heap and stack).
MAX_RAM=3584
MAX_ROM=131072
CC=avr-gcc
logf=/dev/null
tmpf=/tmp/run-all-$$

# The benchmarks to use
benchmarks="2dfir blowfish crc32 cubic dijkstra fdct float_matmult int_matmult \
           rijndael sha"

# Initial message
cat > ${tmpf} <<EOF
			 Low power benchmark results
			 ===========================

The text data and BSS sizes shown for each benchmark are for the compiled
files of the benchmark only, prior to linking with the library.  The decision
whether to run is based on the size after linking, which may be considerably
larger.

EOF
cat ${tmpf}

# Baseline benchmarks
CFLAGS="-O0 -mmcu=atmega128"
LDFLAGS="-O0 -mmcu=atmega128"
runall $benchmarks
echo

# Benchmarks with small size
CFLAGS="-Os -mmcu=atmega128"
LDFLAGS="-Os -mmcu=atmega128"
runall $benchmarks
echo

# Benchmarks with optimization
CFLAGS="-O2 -mmcu=atmega128"
LDFLAGS="-O2 -mmcu=atmega128"
runall $benchmarks
echo

# Benchmarks with maximum optimization
CFLAGS="-O3 -mmcu=atmega128"
LDFLAGS="-O3 -mmcu=atmega128"
runall $benchmarks
echo | tee -a ${resf}

rm ${tmpf}
