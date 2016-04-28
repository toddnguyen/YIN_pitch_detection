/****************************************************************************
 * 
 *   Functions to determine machine byte-order (endianness) and to swap
 *   little-endian data into big-endian representation, and vice versa.
 *
 *   'SNDAN' analysis files are always big-endian for consistency across
 *   platforms, whereas 'WAVE' files are always little-endian.
 *
 *   Changes:                        
 *	08/12/94 jwb	For DEC Alpha: insert byte swapping code.
 *	10/31/97 zheng	Add byte_order() to decide machine byte order
 *      01/29/98 jjjm   Move these functions from 'header.c' to this file,
 *                      and separate the test for the machine's byte order
 *                      from the decision about whether or not to byte-reverse
 *                      the sound data (in order to support WAVE files).
 *****************************************************************************/


void byteswap2(short *dat)
{
  unsigned char *byte, temp;
  byte = (unsigned char *)dat;
  temp = byte[1]; byte[1] = byte[0]; byte[0] = temp;
}


void byteswap4(int *dat)
{
  unsigned char *byte, temp;
  byte = (unsigned char *)dat;
  temp = byte[3]; byte[3] = byte[0]; byte[0] = temp;
  temp = byte[2]; byte[2] = byte[1]; byte[1] = temp;
}


/* Return 0 if the host architecture is big-endian, 1 if little-endian. */

int byte_order()					/* zheng 10/29/97 */
{						    /* rev. jjjm 01/29/98 */
  int   one = 1;
  char* endptr = (char *) &one;
  return (*endptr);
} /* end of function byte_order */


