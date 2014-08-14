#!/usr/bin/python

# Copyright (C) 2013 Embecosm Limited and University of Bristol
#
# Contributor James Pallister <james.pallister@bristol.ac.uk>
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

"""Collect instruction statistics from all instruction traces.

This program assumes that the trace file have been saved with filename format:
    benchmark.platform.trace[.xz]
If .xz is detected, the script will attempt to decompress the trace on the fly

Usage:
    all_stats.py [options] PLATFORM
    all_stats.py -h

Options:
    --help -h                   Show this help message
    --full                      Display the full breakdown
    --quiet -q                  Only output the values at the end

"""

from docopt import docopt
import instruction_stats
import os
import glob

if __name__ == "__main__":
    arguments = docopt(__doc__)
    quiet = arguments['--quiet']

    instruction_stats.quiet = quiet

    files = glob.glob("*.{}.trace*".format(arguments['PLATFORM']))
    files.sort()

    # Compute the benchmark names from the file names
    names = {f: f.split('.')[0] for f in files}

    if not quiet:
        print "Analysing",len(files),"files\n"

    individual_results = {}
    grouped_results = {}

    # Collect instruction stats for each trace and store
    for f in files:
        if not quiet:
            print "Analysing", f
        insn_types = instruction_stats.count(f, arguments['PLATFORM'])
        large_types = instruction_stats.collect(insn_types, arguments['PLATFORM'])
        if not quiet:
            print ""

        individual_results[f] = insn_types
        grouped_results[f] = large_types

    # If we want to display every instrution, do this
    if arguments['--full']:
        all_insns = set()

        # Compute the union of all individual instructions
        for insn_res in individual_results.values():
            map(all_insns.add, insn_res.keys())

        # Find the largest number of characters needed to display each column
        lens = {}
        for f in files:
            lens[f] = max(map(lambda x: len(str(x)), individual_results[f].values()))
            lens[f] = max(lens[f], len(names[f]))

        # Display the headings and underline
        print "Instruction",
        for f in files:
            print "{1: <{0}}".format(lens[f],names[f]),
        print ""

        print "=" * (11 + sum(lens.values()) + len(files))

        # Display each instruction and counts
        for insn in sorted(all_insns):
            print "{0: <11}".format(insn),
            for f in files:
                print "{1: >{0}}".format(lens[f], individual_results[f][insn]),
            print ""
        print ""

    # Compute the column widths needed
    lens = {}
    for f in files:
        lens[f] = max(map(lambda x: len(str(x)), grouped_results[f].values()))
        lens[f] = max(lens[f], len(names[f]))

    # Display the headings and underline
    print "Group  ",
    for f in files:
        print "{1: <{0}}".format(lens[f],names[f]),
    print ""
    print "=" * (8 + sum(lens.values()) + len(files) - 1)

    # Display the groupings and size
    for group in grouped_results.values()[0].keys():
        print "{0: <7}".format(group),
        for f in files:
            print "{1: >{0}}".format(lens[f], grouped_results[f][group]),
        print ""
    print ""
