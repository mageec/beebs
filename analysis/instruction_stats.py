#!/bin/python

"""Collect instruction statistics from an instruction trace

Usage:
    instruction_stats.py [options] -p PLATFORM TRACEFILE
    instruction_stats.py -h

Options:
    --help -h                   Show this help message
    --platform -p PLATFORM      The set of regexes to extract instruction details
    --full                      Display the full breakdown

"""

from docopt import docopt
arguments = docopt(__doc__)

import collections
import re
import sys
import subprocess

insn_list = {
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
    'cortex-m3': r'',
    'avr': r'(?P<insn>[a-z]+)\s+',
    }

def progress(obj, obj_len):
    interval = obj_len / 1000
    s = ""
    for i, o in enumerate(obj):
        if i%interval == 0:
            sys.stdout.write("\b"*len(s))
            s = "{:0<3.1f}%".format(float(i)/obj_len*100)
            sys.stdout.write(s)
            sys.stdout.flush()
        yield o

##########################################################################

if arguments['--platform'] not in insn_re_list:
    print "Error: Unknown platform. Valid platforms:", insn_re_list.keys()

insn_re = re.compile(insn_re_list[arguments['--platform']])

print "Computing trace length..."
trace_len = int(subprocess.check_output("wc -l "+arguments['TRACEFILE'], shell=True).split()[0])

print "Counting trace instructions... ",
with open(arguments['TRACEFILE']) as f:
    insn_types = collections.Counter()

    for line in progress(f.xreadlines(), trace_len):
        m = re.match(insn_re, line)
        if m is not None:
            insn_types[m.group('insn')] += 1
print ""

if arguments['--full']:
    insn_len = max(max(map(len,insn_types.keys())), 4)
    len_len = max(max(map(lambda x: len(str(x)),insn_types.values())), 6)

    print "\nInsn{} Number{}".format(" "*(insn_len-4)," "*(len_len-6))
    print "=" * (insn_len + len_len + 1)

    for insn, n in insn_types.most_common():
        print "{2: <{0}} {3: >{1}}".format(insn_len,len_len,insn,n)

large_types = collections.Counter()


for itype, insns in insn_list[arguments['--platform']].items():
    for insn in insns:
        large_types[itype] += insn_types[insn]

insn_len = max(max(map(len,large_types.keys())), 4)
len_len = max(max(map(lambda x: len(str(x)),large_types.values())), 6)

print "\nType{} Number{}".format(" "*(insn_len-4)," "*(len_len-6))
print "=" * (insn_len + len_len + 1)

for insn, n in large_types.most_common():
    print "{2: <{0}} {3: >{1}}".format(insn_len,len_len,insn,n)
print ""
