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

package body fibcall
with SPARK_Mode => on
is
   function Fibonacci (N : Fibonacci_Argument_Type) return Fibonacci_Argument_Type is
      Fold : Natural := 0;
      Fnew : Natural := 1;
      Tmp  : Positive;
      I    : Natural := 2;
      Ans  : Natural;
   begin
      if N <= 1 then return N; end if;
      loop
         if I > 30 or I > N then
            exit;
         end if;
         pragma Loop_Invariant (I <= 30 and I <= N and Fnew = Fib(I - 1)
                                and Fold = Fib(I - 2));
         Tmp  := Fnew;
         Fnew := Fnew + Fold;
         Fold := Tmp;

         I := I + 1;
      end loop;
      Ans := Fnew;
      return Ans;
   end Fibonacci;
end fibcall;
