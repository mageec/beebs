# Low Power Benchmarks

These tests are designed to test the performance of deeply embedded system,
particularly with regard to energy consumed. As such they assume the presence
of no OS and in particular no output stream.

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

## Origin of the tests

All of these benchmarks are derived from other benchmark suites:
 * MiBench
 * WCET set of benchmarks

All are freely available for use, but some lack specific license
provisions. For the avoidance of doubt, the versions provided here are
explicitly licensed under the GNU General Public License version 3.
