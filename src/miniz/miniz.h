/* For more compatibility with zlib, miniz.c uses unsigned long for
   some parameters/struct members. Beware: mz_ulong can be either 32
   or 64-bits!  */
typedef unsigned long mz_ulong;

/* Forward declaration of function: Single-call decompression.
   Returns MZ_OK on success, or one of the error codes from
   mz_inflate() on failure.  */
int mz_uncompress(unsigned char *pDest, mz_ulong *pDest_len,
		  const unsigned char *pSource, mz_ulong source_len);
