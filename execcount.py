#!/usr/bin/env python3

from subprocess import Popen, PIPE, TimeoutExpired
import codecs
import logging
import os
import sys

benchmarks = [ 'crc' ]

# Commands sent to GDB. In order to avoid complicated interaction with GDB,
# we just shove everything into the buffer and then read everything out
# and wait for termination (with the Popen.communicate() method). This works
# because we don't have too much input, but adding more might result in
# blocking / deadlock (possibly - I have not checked whether Popen.write()
# could risk this).

commands = [
    b'-target-select remote :51000',
    b'load',
    b'cont',
    b'quit'
]

# Set up logging
log = logging.getLogger()

def setup_logging(logfile):
    log.setLevel(logging.DEBUG)
    ch = logging.StreamHandler(sys.stdout)
    ch.setLevel(logging.INFO)
    log.addHandler(ch)
    fh = logging.FileHandler(logfile)
    fh.setLevel(logging.DEBUG)
    log.addHandler(fh)

class GdbParsingError(RuntimeError):
    """Exception raised for errors in parsing interactions with gdb."""

    def __init__(self, message):
        self.message = message
        super().__init__(message)

def execute(executable, commands):
    gdbservercmd = ['riscv32-gdbserver', '51000']
    log.debug('\nLaunching GDB server...')
    gdbserver = Popen(gdbservercmd, stdout=PIPE, stderr=PIPE, stdin=PIPE)

    gdbcmd = ['riscv32-unknown-elf-gdb', '--interpreter=mi', \
        executable]
    log.debug('\nLaunching gdb...')
    debugger = Popen(gdbcmd, stdin=PIPE, stdout=PIPE, stderr=PIPE)

    log.debug('\nCommunicating with gdb...')
    # Handle timeouts as prescribed in:
    # https://docs.python.org/3/library/subprocess.html#subprocess.Popen.communicate
    try:
        stdout, stderr = debugger.communicate(input=b'\n'.join(commands),
            timeout=10)
        log.debug('\n... Finished communicating with gdb.')
    except TimeoutExpired:
        log.debug('\nExecution failed - timeout reached.')
        debugger.kill()
        stdout, stderr = debugger.communicate()
    except GdbParsingError as gpe:
        log.debug('Error parsing output from GDB: %s' % gpe.message)

    log.debug('\nStandard output from gdb:\n')
    log.debug(codecs.decode(stdout, 'utf-8'))
    log.debug('\nStandard error from gdb:\n')
    log.debug(codecs.decode(stderr, 'utf-8'))

    log.debug('\nKilling gdbserver...')
    log.debug('gdbserver return code %s' % gdbserver.returncode)
    stdout, stderr = gdbserver.communicate(input='', timeout=10)

    gdbserver_output = stdout.decode()

    log.debug('\nStandard output from gdbserver:\n')
    log.debug(gdbserver_output)
    log.debug('\nStandard error from gdbserver:\n')
    log.debug(stderr.decode())

    return gdbserver_output

def parse_output(output):
    seen_start = False
    seen_stop = False
    seen_exit = False
    for line in output.split('\n'):
        if not seen_start:
            if "Start" in line:
                start = int(line.split()[4].strip())
                seen_start = True

        if not seen_stop:
            if "Stop" in line:
                stop = int(line.split()[4].strip())
                seen_stop = True

        if not seen_exit:
            if "Exit" in line:
                exit_code = int(line.split()[4].strip())
                seen_exit = True

    if not seen_start:
        raise GdbParsingError('Did not find start trigger cycle count')

    if not seen_stop:
        raise GdbParsingError('Did not find stop trigger cycle count')

    if not seen_exit:
        raise GdbParsingError('Did not find exit code')

    cycle_count = stop - start
    return cycle_count, exit_code

def run_benchmark(bm):
    executable = os.path.join('src', bm, bm)
    try:
        output = execute(executable, commands)
        cycle_count, exit_code = parse_output(output)
    except GdbParsingError as gpe:
        log.debug('Error parsing output from GDB for %s: %s' % (bm, gpe.message))
        cycle_count = -1
        exit_code = -1

    print('%s\t%s\t%s' % (bm, cycle_count, exit_code))

def run_benchmarks():
    setup_logging('beebs-riscv32.log')
    for bm in benchmarks:
        run_benchmark(bm)

if __name__ == '__main__':
    sys.exit(run_benchmarks())
