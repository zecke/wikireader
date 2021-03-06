/*-------------------------------------------*/
/* Integer type definitions for FatFs module */
/*-------------------------------------------*/

#ifndef _INTEGER

#ifndef _ITRON_H_

/* These types must be 16-bit, 32-bit or larger integer */
typedef signed int      INT;
typedef unsigned int	UINT;

/* Boolean type */
typedef enum { FALSE = 0, TRUE } BOOL;

#endif

/* These types must be 8-bit integer */
typedef signed char		CHAR;
typedef unsigned char	UCHAR;
typedef unsigned char	BYTE;

/* These types must be 16-bit integer */
typedef short			SHORT;
typedef unsigned short	USHORT;
typedef unsigned short	WORD;

/* These types must be 32-bit integer */
typedef long			LONG;
typedef unsigned long	ULONG;
typedef unsigned long	DWORD;

#define _INTEGER
#endif
