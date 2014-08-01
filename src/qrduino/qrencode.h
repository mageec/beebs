#define PROGMEM
#define memcpy_P memcpy
#define __LPM(x) *x
#define pgm_read_word(x) *x

// malloc-ed by initframe, free manually
extern unsigned char *strinbuf; // string iput buffer
extern unsigned char *qrframe;
// setup the base frame structure - can be reused
void initframe(void);
// free the basic frame malloced structures
void freeframe(void);
// these resturn maximum string size to send in
unsigned initeccsize(unsigned char ecc, unsigned size);
unsigned initecc(unsigned char level,unsigned char version);

extern unsigned char  WD, WDB;
#include "qrbits.h"

// strinbuf in, qrframe out
void qrencode(void);

void freeecc();
