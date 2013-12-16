#   Analysis Makefile.am, to set up simulation and analysis tools
#
#   Copyright (C) 2013 Embecosm Limited and University of Bristol
#
#   This file is part of the Bristol/Embecosm Energy Efficiency Benchmark
#   Suite.
#
#   Contributor: James Pallister <james.pallister@bristol.ac.uk>
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

EXTRA_DIST = simulate.avr.in

# If creating script for AVR simulator
if SIMULATE_AVR
bin_SCRIPTS=simulate.avr
AVRSIMPATH="simulavr"

simulate.avr: simulate.avr.in Makefile
	sed -e 's,[@]avrsimpath,$(AVRSIMPATH),g' < $(srcdir)/simulate.avr.in > simulate.avr
	chmod +x simulate.avr

endif

# If creating script for Cortex-M0 simulator
if SIMULATE_CORTEX_M0
bin_SCRIPTS=simulate.cortex-m0
CORTEXM0SIMPATH="thumbulator"

simulate.cortex-m0: simulate.cortex-m0.in Makefile
	sed -e 's,[@]cortexm0simpath,$(CORTEXM0SIMPATH),g' < $(srcdir)/simulate.cortex-m0.in > simulate.cortex-m0
	chmod +x simulate.cortex-m0

endif


CLEANFILES=$(bin_SCRIPTS)
