#!/bin/bash
# Building ada support for building a BEEBS benchmark
#
# Copyright (C) 2020 AdaCore Limited
#
# This file is part of the Bristol/Embecosm Embedded Benchmark Suite.
#
# Modified by: Kyriakos Georgiou <georgiou@adacore.com>
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

# SPDX-License-Identifier: GPL-3.0-or-later

gnatmake -c fibcall.adb -fpic
gnatbind -Lelaborate -o elaborate.adb fibcall.ali
gnatmake elaborate.adb
ar cr libadaStatic.a elaborate.o fibcall.o
rm -f elaborate.* *.ali fibcall.o  # ensure linkage to .a
