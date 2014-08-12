# Analysis Makefile.am, to set up simulation and analysis tools
#
# Copyright (C) 2013 Embecosm Limited and University of Bristol
#
# This file is part of the Bristol/Embecosm Embedded Benchmark Suite.
#
# Contributor: James Pallister <james.pallister@bristol.ac.uk>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# TODO rename simulator command scripts after platform name, rather than
# the host triple

ANALYSIS=instruction_stats.py all_stats.py
EXTRA_DIST= $(ANALYSIS) simulator.in cmd.arm-none-eabi cmd.avr-unknown-none
bin_SCRIPTS=

do_subst = sed -e '/@simulatorcommands@/{r $(srcdir)/cmd.$(host)'$$'\n''d}' \
		       -e 's,[@]simulator[@],$(SIMULATORPATH),g'


# If creating script for simulator
if SIMULATE
bin_SCRIPTS+=simulate

simulate: $(srcdir)/simulator.in $(srcdir)/cmd.$(host) Makefile
	$(do_subst) < $(srcdir)/simulator.in > simulate
	chmod +x simulate

endif

CLEANFILES=$(bin_SCRIPTS)
