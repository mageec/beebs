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

"""Collect instruction statistics from an instruction trace

Usage:
    instruction_stats.py [options] -p PLATFORM TRACEFILE
    instruction_stats.py -h

Options:
    --help -h                   Show this help message
    --platform -p PLATFORM      The set of regexes to extract instruction details
    --full                      Display the full breakdown
    --quiet -q                  Only output the values at the end

"""

from docopt import docopt

quiet = True

import collections
import re
import sys
import subprocess
import os
import os.path
import itertools

insn_list = {
    'cortex-m0': {
            'integer': ["mov", "movs", "add", "adds", "adcs", "adr", "subs",
                    "sub", "sbcs", "adc", "sbc", "rsbs", "muls", "cmp",
                    "cmn", "ands", "eors", "orrs", "mvns", "bics", "tst",
                    "lsls", "lsrs", "asrs", "rors", "sxth", "sxtb", "uxth",
                    "uxtb", "rev", "rev16", "revsh"],
            'float'  : [""],
            'memory' : ["ldr", "ldrh", "ldrsh", "ldrsb", "ldm", "str",
                    "strh", "strb", "stm", "push", "pop"],
            'branch' : ["b", "beq", "bne", "bcs", "bcc", "bmi", "bpl",
                    "bvs", "bvc", "bhi", "bls", "bge", "blt", "bgt",
                    "ble", "bl", "bx", "blx"],
            'other'  : ["svc", "cpsid", "cpsie", "mrs", "msr", "bkpt",
                    "sev", "wfe", "wfi", "yeild", "nop", "isb", "dmb",
                    "dsb"],
            },
    'cortex-m3': {
            'integer': [],
            'float'  : [],
            'memory' : [],
            'branch' : [],
            'other'  : [],
            },
    'avr': {
            'integer': ["add", "adc", "adiw", "sub", "subi", "sbc", "sbci",
                    "sbiw", "neg", "inc", "dec", "tst", "clr", "set", "mul",
                    "muls", "mulsu", "fmul", "fmuls", "fmulsu", "cp", "cpc",
                    "cpi", "mov", "movw", "ldi", "and", "andi", "or", "ori",
                    "eor", "com", "sbr", "cbr", "sbi", "cbi", "lsl", "lsr",
                    "rol", "ror", "asr", "swap", "bset", "bclr", "bst",
                    "bld", "sec", "clc", "sen", "cln", "sez", "clz", "sei",
                    "cli", "ses", "cls", "sev", "clv", "set", "clt", "seh",
                    "clh"],
            'float'  : [""],
            'memory' : ["ld", "ldd", "lds", "st", "std", "sts", "lpm", "spm",
                    "in", "out", "push", "pop"],
            'branch' : ["rjmp", "ijmp", "jmp", "rcall", "icall", "call",
                    "ret", "reti", "cpse", "sbrc", "sbrs", "sbic", "sbis",
                    "brbs", "brbc", "breq", "brne", "brcs", "brcc", "brsh",
                    "brlo", "brmi", "brpl", "brge", "brlt", "brhs", "brhc",
                    "brts", "brtc", "brvs", "brvc", "brie", "brid"],
            'other'  : ["nop", "sleep", "wdr", "break"],
            },
    }

insn_re_list = {
    'cortex-m0': r'0x........: 0x.... (?P<insn>[^\s]+)\s',
    'cortex-m3': r'0x........: 0x.... (?P<insn>[^\s]+)\s',
    'avr': r'[^ ]+ 0x....: [^ ]+ +(?P<insn>[^ ]+)(?<!CPU-waitstate)',
    }

def progress(obj, obj_len):
    interval = obj_len / 1000
    s = ""
    for i, o in enumerate(obj):
        if i%interval == 0 and not quiet:
            sys.stdout.write("\b"*len(s))
            s = "{:0<3.1f}%".format(float(i)/obj_len*100)
            sys.stdout.write(s)
            sys.stdout.flush()
        yield o

##########################################################################

def count(fname, platform):

    if platform not in insn_re_list:
        print "Error: Unknown platform. Valid platforms:", insn_re_list.keys()

    insn_re = re.compile(insn_re_list[platform])

    if not quiet:
        print "Computing trace length...",

    isCompressed = (os.path.splitext(fname)[1]) == ".xz"

    if isCompressed:
        trace_len = int(subprocess.check_output("xzcat "+fname+" | wc -l", shell=True).split()[0])
    else:
        trace_len = int(subprocess.check_output("wc -l "+fname, shell=True).split()[0])

    if not quiet:
        print trace_len
        print "Counting trace instructions... ",

    if isCompressed:
        p = subprocess.Popen("xzcat "+fname, shell=True, stdout=subprocess.PIPE)
        f = p.stdout
    else:
        f = open(fname)

    insn_types = collections.Counter()

    for line in progress(f.xreadlines(), trace_len):
        m = re.match(insn_re, line)
        if m is not None:
            insn_types[m.group('insn').lower()] += 1
    if not quiet:
        print ""

    return insn_types

def collect(insn_types, platform):

    large_types = collections.Counter()

    for itype, insns in insn_list[platform].items():
        for insn in insns:
            large_types[itype] += insn_types[insn]

    return large_types


if __name__ == "__main__":
    arguments = docopt(__doc__)
    quiet = arguments['--quiet']

    insn_types = count(arguments['TRACEFILE'], arguments['--platform'])

    if arguments['--full']:
        insn_len = max(max(map(len,insn_types.keys())), 4)
        len_len = max(max(map(lambda x: len(str(x)),insn_types.values())), 6)

        print "\nInsn{} Number{}".format(" "*(insn_len-4)," "*(len_len-6))
        print "=" * (insn_len + len_len + 1)

        for insn, n in insn_types.most_common():
            print "{2: <{0}} {3: >{1}}".format(insn_len,len_len,insn,n)

    large_types = collect(insn_types, arguments['--platform'])

    insn_len = max(max(map(len,large_types.keys())), 4)
    len_len = max(max(map(lambda x: len(str(x)),large_types.values())), 6)

    if not quiet:
        print "\nType{} Number{}".format(" "*(insn_len-4)," "*(len_len-6))
        print "=" * (insn_len + len_len + 1)

        for insn, n in large_types.most_common():
            print "{2: <{0}} {3: >{1}}".format(insn_len,len_len,insn,n)
        print ""
    else:
        for insn, n in sorted(large_types.items()):
            print n

