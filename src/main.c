// Common main.c for the benchmarks
//
// Copyright (C) 2014 Embecosm Limited and University of Bristol
//
// This file is part of the Bristol/Embecosm Embedded Benchmark Suite.
//
// Contributor: James Pallister <james.pallister@bristol.ac.uk>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "support.h"

#pragma weak main
#pragma weak initialise_benchmark
#pragma weak verify_benchmark

int initialise_benchmark()
{
    return 0;
}

// each benchmark will need to override this function
// otherwise this function returns -1 to indicate no verification done
int verify_benchmark(int unused)
{
    return -1;
}

int
main (void)
{
  int i;
  volatile int result;
  int correct;

  initialise_board ();
  initialise_benchmark ();
  start_trigger ();

  for (i = 0; i < REPEAT_FACTOR; i++) {
    initialise_benchmark ();
    result = benchmark ();
  }

  stop_trigger ();

  // bmarks that use arrays will check a global array rather than int result
  correct = verify_benchmark(result);

  return (!correct);
}

