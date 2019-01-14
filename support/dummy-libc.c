/* Dummy standard C library for the benchmarks

   Copyright (C) 2018 Embecosm Limited

   Contributor: Jeremy Bennett <jeremy.bennett@embecosm.com>

   This file is part of the Bristol/Embecosm Embedded Benchmark Suite.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

   SPDX-License-Identifier: GPL-3.0-or-later */

/* The purpose of this library is to measure the size of code excluding target
   dependent C library code. It only makes sense if it is used with
   -gc-sections. */

void * __locale_ctype_ptr;

int __errno;

char *_ctype_;

void __attribute__ ((noreturn))
abort (void)
{
  while (1)
    ;
}


void *
memcpy (void *dest __attribute__ ((unused)),
	const void *src __attribute__ ((unused)),
	unsigned int n __attribute__ ((unused)) )
{
  return  0;
}


void *
memmove(void *dest __attribute__ ((unused)),
	const void *src __attribute__ ((unused)),
	unsigned int n __attribute__ ((unused)) )
{
  return 0;
}


void *
memset(void *s __attribute__ ((unused)),
       int c __attribute__ ((unused)),
       unsigned int n __attribute__ ((unused)) )
{
  return 0;
}

int
memcmp (const void *s1,
	const void *s2,
	unsigned int n)
{
  return 0;
}


int
rand (void)
{
  return 0;
}


void
srand (unsigned int seed __attribute__ ((unused)) )
{
}


void *
calloc (unsigned int nmemb __attribute__ ((unused)),
	unsigned int size __attribute__ ((unused)) )
{
  return 0;
}


void *
malloc (unsigned int size __attribute__ ((unused)) )
{
  return  0;
}


void
free (void *ptr __attribute__ ((unused)) )
{
}


void __attribute__ ((noreturn))
__assert_func (const char *arg1 __attribute__ ((unused)),
	       int arg2 __attribute__ ((unused)),
	       const char *arg3 __attribute__ ((unused)),
	       const char *arg4 __attribute__ ((unused)))
{
  while (1)
    ;
}

unsigned int
strlen(const char *s __attribute__ ((unused)) )
{
  return  0;
}


char *
strcpy (char *dest __attribute__ ((unused)),
	const char *src __attribute__ ((unused)) )
{
  return  0;
}


char *
strchr(const char *s __attribute__ ((unused)),
       int c __attribute__ ((unused)) )
{
  return  0;
}


long int
strtol (const char *nptr __attribute__ ((unused)),
	char **endptr __attribute__ ((unused)),
	int base __attribute__ ((unused)) )
{
  return 0;
}


int
strcmp(const char *s1 __attribute__ ((unused)),
       const char *s2 __attribute__ ((unused)) )
{
  return 0;
}


/*
   Local Variables:
   mode: C++
   c-file-style: "gnu"
   End:
*/
