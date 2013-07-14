#include <stdio.h>
#include <stdlib.h>

#ifdef ARM
#include "platformcode.h"
#else
#define REPEAT_FACTOR (4096)
#endif /* ARM */

#include "blowfish.h"

char *ckey= "ABCDEF1234567890";

int main(int argc, char *argv[])
{
	BF_KEY key;
	unsigned char ukey[8];
	unsigned char indata[40],outdata[40],ivec[8];
	int num;
	int by=0,i=0;
	int encordec=-1;
	char *cp,ch;
	int n, n2;

#ifdef ARM
	initialise_trigger();
	start_trigger();
#endif /* ARM */

	for(n = 0; n < REPEAT_FACTOR>>11; ++n)
	{
		encordec = 1;
		num=0;

		/* Read the key */
		cp = ckey;
		while(i < 64 && *cp)    /* the maximum key length is 32 bytes and   */
		{                       /* hence at most 64 hexadecimal digits      */
			ch = *cp++;            /* process a hexadecimal digit  */
			if(ch >= '0' && ch <= '9')
				by = (by << 4) + ch - '0';
			else if(ch >= 'A' && ch <= 'F')
				by = (by << 4) + ch - 'A' + 10;
			else                            /* error if not hexadecimal     */
			{
				// printf("key must be in hexadecimal notation\n");
				exit(-1);
			}

			/* store a key byte for each pair of hexadecimal digits         */
			if(i++ & 1)
				ukey[i / 2 - 1] = by & 0xff;
		}

		BF_set_key(&key,8,ukey);

		if(*cp)
		{
			//printf("Bad key value.\n");
			exit(-1);
		}

		i=0;
		for(n2 = 0; n2 < 256; ++n2)
		{
			int j;
			while(i<40)
				indata[i++]=rand();

			BF_cfb64_encrypt(indata,outdata,i,&key,ivec,&num,encordec);
			encordec = 1-encordec;
			BF_cfb64_encrypt(outdata,indata,i,&key,ivec,&num,encordec);

			i=0;
		}
	}

#ifdef ARM
	stop_trigger();
#endif /* ARM */

	return 0;
}



