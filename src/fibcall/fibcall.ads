-- BEEBS fibcall benchmark

-- Copyright (C) 2020 AdaCore

-- Contributor Kyriakos Georgiou <georgiou@adacore.com>

-- This file is part of the Bristol/Embecosm Embedded Benchmark Suite.

-- This program is free software: you can redistribute it and/or modify
-- it under the terms of the GNU General Public License as published by
-- the Free Software Foundation, either version 3 of the License, or
-- (at your option) any later version.

-- This program is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
-- GNU General Public License for more details.

-- You should have received a copy of the GNU General Public License
-- along with this program. If not, see <http://www.gnu.org/licenses/>.
-- SPDX-License-Identifier: GPL-3.0-or-later

package fibcall with
SPARK_Mode => on
is


   subtype Fibonacci_Argument_Type is Integer range 0 .. 30;

   -- It can be shown that the value returned by the mathematical Fibonacci function is the
   -- integer closest to \frac{\phi^n}{\sqrt{5}} where \phi is the Golden Ratio given by
   -- (1 + \sqrt{5})/2. See:
   -- http://www-personal.umich.edu/~copyrght/image/books/Spatial%20Synthesis2/s01math55fibo.pdf
   -- Thus we should be able to assert that Fib'Result < (1.6181**N)/2.2360 + 1.0. This is
   -- needed to prove freedom from overflow in function Fibonacci when Old + Temp is computed.
   --
   function Fib(N : Fibonacci_Argument_Type) return Natural is
     (case N is
         when 0 | 1  => N,
         when others => Fib(N - 1) + Fib(N - 2))
       with
         Ghost,
         Pre => N <= Fibonacci_Argument_Type'Last,
         Post => Float(Fib'Result) < (1.6181**N)/2.2360 + 1.0;
--     pragma Annotate (GNATprove, Terminating, Fib);


   function Fibonacci (N : Fibonacci_Argument_Type) return Fibonacci_Argument_Type with
--       Global => null,
     Post => Fibonacci'Result = Fib(N);
   pragma Export (C, Fibonacci, "fib");

end fibcall;
