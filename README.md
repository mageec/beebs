# BEEBS: Open Benchmarks for Energy Measurements on Embedded Platforms

This repository contains the Bristol Energy Efficiency Benchmark Suite
(BEEBS).These benchmarks are designed to test the performance of deeply
embedded systems, particularly with regard to energy consumed. As such they
assume the presence of no OS and in particular no output stream.



For the paper describing the benchmarks and reasoning behind the choice of
benchmarks see http://arxiv.org/abs/1308.5174.

For an example of their use, see http://arxiv.org/abs/1303.6485.

## Using the tests

All tests provide the functions initialize_trigger (), start_trigger () and
stop_trigger () to control measurement of the test execution (performance,
energy consumed etc). The implementation of these functions should be provided
in platformcode.c.

The number of times each test is run is controlled by the constant
REPEAT_FACTOR set in the file platformcode.h. This should be edited as
required.

An example script to run all the tests is provided in run-all.sh. This script
was written to test the models compiled for the Atmel ATmega128 and running on
a remote target controlled by GDB. It should be modified as required for other
platforms.

## Versions of the tests

Different versions of the tests carry tags, to allow groups to agree on a
precise version used.

release-0.1: This version of BEEBS is described in Pallister, J., Hollis, S.,
& Bennett, J. (2013). BEEBS: Open Benchmarks for Energy Measurements on
Embedded Platforms. Available: http://arxiv.org/abs/1308.5174.

This is also the version used in Pallister, J., Hollis, S., & Bennett J.
(2013). "Identifying Compiler Options to Minimise Energy Consumption for
Embedded Platforms". Available http://arxiv.org/abs/1303.6485.



## Origin of the tests

All of these benchmarks are derived from other benchmark suites:
 * MiBench
 * WCET set of benchmarks
 * DSPstone

All are freely available for use, but some lack specific license
provisions. For the avoidance of doubt, the versions provided here are
explicitly licensed under the GNU General Public License version 3.


## Misc Notes

If build-aux/config.sub is regenerated, the following command needs to be run
to ensure pic32 is recognised as a valid tools prefix.

    sed -i 's/powerpcle \\/powerpcle \\\n    | pic32 \\/' $SCR_DIR/build-aux/config.sub
