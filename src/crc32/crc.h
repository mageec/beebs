/*
 **  CRC.H - header file for SNIPPETS CRC and checksum functions
 */

#ifndef CRC__H
#define CRC__H

typedef unsigned char  BYTE;
typedef unsigned long  DWORD;
typedef unsigned short WORD;

/*
 **  File: CRC_32.C
 */

#define UPDC32(octet,crc) (crc_32_tab[((crc)^((BYTE)octet)) & 0xff] ^ ((crc) >> 8))

DWORD updateCRC32(unsigned char ch, DWORD crc);

#endif /* CRC__H */

/* vim: set ts=3 sw=3 et: */
