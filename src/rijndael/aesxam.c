/* BEEBS rijndael benchmark

   Copyright (C) 2014 Embecosm Limited and University of Bristol

   This file is part of the Bristol/Embecosm Embedded Benchmark Suite.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program. If not, see <http://www.gnu.org/licenses/>. */

/* The original version of this file was released with the following
   copyright, license and disclaimer:

   -----------------------------------------------------------------------
   Copyright (c) 2001 Dr Brian Gladman <brg@gladman.uk.net>, Worcester, UK

   TERMS

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:
   1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
   2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

   This software is provided 'as is' with no guarantees of correctness or
   fitness for purpose.
   -----------------------------------------------------------------------
   */

/* Example of the use of the AES (Rijndael) algorithm for file  */
/* encryption.  Note that this is an example application, it is */
/* not intended for real operational use.  The Command line is: */
/*                                                              */
/* aesxam input_file_name output_file_name [D|E] hexadecimalkey */
/*                                                              */
/* where E gives encryption and D decryption of the input file  */
/* into the output file using the given hexadecimal key string  */
/* The later is a hexadecimal sequence of 32, 48 or 64 digits   */
/* Examples to encrypt or decrypt aes.c into aes.enc are:       */
/*                                                              */
/* aesxam file.c file.enc E 0123456789abcdeffedcba9876543210    */
/*                                                              */
/* aesxam file.enc file2.c D 0123456789abcdeffedcba9876543210   */
/*                                                              */
/* which should return a file 'file2.c' identical to 'file.c'   */

/* The BEEBS version of this code uses its own version of rand, to
   avoid library/architecture variation. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "aes.h"
#include "support.h"

/* This scale factor will be changed to equalise the runtime of the
   benchmarks. */
#define LOCAL_SCALE_FACTOR 4

#ifndef fpos_t
   #define fpos_t size_t
#endif

#define FLEN flen

#define RAND(a,b) (((a = 36969 * (a & 65535) + (a >> 16)) << 16) + (b = 18000 * (b & 65535) + (b >> 16))  )

static unsigned long fr_a[2], fr_mt, fr_count;
static char          fr_r[4];

void
initrand (void)
{
  memset (fr_a, 0, 2 * sizeof (fr_a[0]));
  memset (fr_r, 0, 4 * sizeof (fr_r[0]));
  fr_mt = 0L;
  fr_count = 0L;
}

void fillrand(byte *buf, int len)
{
   int                  i;

   if(fr_mt) {
      fr_mt = 0;
      /*cycles(fr_a);*/
      fr_a[0]=0xeaf3;
      fr_a[1]=0x35fe;
   }

   for(i = 0; i < len; ++i)
   {
      if(fr_count == 4)
      {
         *(unsigned long*)fr_r = RAND(fr_a[0], fr_a[1]);
         fr_count = 0;
      }

      buf[i] = fr_r[fr_count++];
   }
}

int encfile(aes *ctx, byte *outbuf)
{
   byte            inbuf[16];
   fpos_t          flen;
   unsigned long   i=0, j, k;

   fillrand(outbuf, 16);           /* set an IV for CBC mode           */
   FLEN = 4096;
   fillrand(inbuf, 1);             /* make top 4 bits of a byte random */
   /* block in the lower 4 bits        */
   inbuf[0] = ((char)FLEN & 15) | (inbuf[0] & ~15);

   for(j = 0; j <256; j++)
   {                               /* input 1st 16 bytes to buf[1..16] */
      for(k = 0; k < 16; ++k)
         inbuf[k] = rand_beebs();

      for(i = 0; i < 16; ++i)         /* xor in previous cipher text  */
         inbuf[i] ^= outbuf[i];

      encrypt(inbuf, outbuf, ctx);    /* and do the encryption        */
      /* in all but first round read 16   */
   }

   return 0;
}

int decfile(aes *ctx, byte *outbuf)
{
   byte    inbuf1[16], inbuf2[16], *bp1, *bp2, *tp;
   int     i,j, k;

   fillrand(inbuf1, 16);           /* set an IV for CBC mode           */

   for(k = 0; k < 16; ++k)
      inbuf2[k] = rand_beebs();

   decrypt(inbuf2, outbuf, ctx);   /* decrypt it                       */

   for(i = 0; i < 16; ++i)         /* xor with previous input          */
      outbuf[i] ^= inbuf1[i];

   bp1 = inbuf1;           /* set up pointers to two input buffers     */
   bp2 = inbuf2;

   for(j = 0; j < 256; ++j)
   {
      for(k = 0; k < 16; ++k)
         bp1[k] = rand_beebs();

      decrypt(bp1, outbuf, ctx);  /* decrypt the new input block and  */

      for(i = 0; i < 16; ++i)     /* xor it with previous input block */
         outbuf[i] ^= bp2[i];

      /* Swap buffer pointers.  */

      tp = bp1, bp1 = bp2, bp2 = tp;
   }

   return 0;
}

char *presetkey="ABCDEF1234567890ABCDEF1234567890";

byte    encoutbuf[16], decoutbuf[16];

int
verify_benchmark (int res)
{
  static const byte enc_exp[16] = {
    0x8d, 0xc4, 0x5d, 0x44, 0x9b, 0x2d, 0x53, 0xec,
    0xf6, 0x65, 0x64, 0x1a, 0x3f, 0xc8, 0x52, 0x69
  };
  static const byte dec_exp[16] = {
    0x2a, 0xe1, 0x24, 0x42, 0x91, 0x4b, 0xd6, 0x4a,
    0xf5, 0x45, 0xaf, 0xc2, 0x84, 0xa9, 0x02, 0x55
  };

  return (0 == res)
    && (0 == memcmp (enc_exp, encoutbuf, 16 * sizeof (enc_exp[0])))
    && (0 == memcmp (dec_exp, decoutbuf, 16 * sizeof (dec_exp[0])));
}


void
initialise_benchmark (void)
{
}



int benchmark()
{
  static const aes ctx_ref = {0};
  int  err;
  int  i;

  for (i = 0; i < (LOCAL_SCALE_FACTOR * REPEAT_FACTOR); i++)
    {
      aes     ctx;
      char    *cp=0, ch=0;
      byte key[32]={0};
      int     i=0, by=0, key_len=0;

      srand_beebs (0);
      initrand ();
      memset (encoutbuf, 0, 16 * sizeof (encoutbuf[0]));
      memset (decoutbuf, 0, 16 * sizeof (decoutbuf[0]));

      err = 0;
      ctx = ctx_ref;
      by=0; key_len=0; err = 0;
      cp = presetkey;   /* this is a pointer to the hexadecimal key digits  */
      i = 0;          /* this is a count for the input digits processed   */

      while(i < 64 && *cp)    /* the maximum key length is 32 bytes and   */
	{                       /* hence at most 64 hexadecimal digits      */
	  ch = *cp++;            /* process a hexadecimal digit  */
	  if(ch >= '0' && ch <= '9')
	    by = (by << 4) + ch - '0';
	  else if(ch >= 'A' && ch <= 'F')
	    by = (by << 4) + ch - 'A' + 10;
	  else                            /* error if not hexadecimal     */
	    return -2;

	  /* store a key byte for each pair of hexadecimal digits         */
	  if(i++ & 1)
	    key[i / 2 - 1] = by & 0xff;
	}

      if(*cp)
	return -3;
      else if(i < 32 || (i & 15))
	return -4;

      key_len = i / 2;

      set_key(key, key_len, enc, &ctx);
      err = encfile(&ctx, encoutbuf);
      set_key(key, key_len, dec, &ctx);
      err = decfile(&ctx, decoutbuf);
    }

  return err;
}


/* vim: set ts=3 sw=3 et: */
