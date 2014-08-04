/*****************************************************************************
 * FILE: ctl.h                                                               *
 * AUTHOR: Toni Schornboeck <schornboeck@c-plusplus.de>                      *
 *****************************************************************************
 * Das zentrale File der CTL                                                 *
 *****************************************************************************
 * Diese Datei darf frei unter der                                           *
 * GPL (http://www.gnu.org/copyleft/gpl.html) verwendet werden.              *
 *****************************************************************************/

#ifndef CTL_STANDARD_HEADER__
#define CTL_STANDARD_HEADER__
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#ifndef CTL_SIZE
#define	CTL_SIZE			100
#endif

#ifndef CTL_GROWFACTOR
#define CTL_GROWFACTOR		0.7
#endif

#ifdef	CTL_NORANGECHECK
#define	CTL_RANGE(x)		if(0)
#else
#define	CTL_RANGE(x)		if(x)
#endif

#define	CTL_OUT_OF_MEMORY	100
#define	CTL_WRONG_VALUE		101
#define	CTL_OUT_OF_RANGE	102
#define CTL_NOT_FOUND		103

struct CTL_STRUCT {
	size_t	BlockSize;
};
typedef struct CTL_STRUCT ctl_struct;

unsigned int ctl_errno;
unsigned int ctl_warning;

int ctl_SetBlockSize(ctl_struct* its, size_t BlockSize)
{
	if(BlockSize<1)
	{
		ctl_errno=CTL_WRONG_VALUE;
		return 1;
	}
	its->BlockSize=BlockSize;
	return 0;
}

#define CTL_GROW_ALLOC_SIZE(its) its->BlockSize=((size_t)(its->alloc+its->alloc*CTL_GROWFACTOR))

#endif
