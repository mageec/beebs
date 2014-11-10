#!/bin/bash

# Script to extract the scale factor used for each individual benchmark
#
# Before this script is run, BEEBS should be configured and built with
# -save-temps in order to generate preprocessed main.i files. This script
# should then be run from the base of this build directory and will emit a
# python fragment which will populate a dictionary of the scale factors
#
# This script is *very* fragile as it makes a lot of assumptions about the
# structure of main because it assumes that it is generated from a script.
#
# Copyright (C) 2014  Embecosm Limited <info@embecosm.com>
#
# This file is part of the low power benchmark
#
# This program is free software: you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as published by the
# Free Software Foundation, either version 3 of the License, or (at your
# option) any later version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
# for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.


# search from the current directory to find all BEEBS benchmark main.i files
for file in `find . -name 'main.i'`; do
    # Extract the expanded preprocessor token for the scale factor and the
    # benchmark it corresponds to
    scale_factor=`sed -n 's/for (i = 0\; i < \(.*\)\; i++)/\1/p' ${file}`
    dir_name=`dirname ${file} | cut -c 3-`

    # Evaluate the expanded token as a python expression, and output a python
    # fragment to place this into a dictionary.
    python -c "print \"test_factor[\'${dir_name}/$(basename ${dir_name})\'] = 4096. / \" + str(${scale_factor})"
done

