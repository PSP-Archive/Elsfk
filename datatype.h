#ifndef	_DATATYPES_H_
#define	_DATATYPES_H_

#include <pspdebug.h>

#ifndef uLong
typedef unsigned long uLong;
#endif

#ifndef bool
typedef int bool;
#endif

#ifndef BOOL
typedef int BOOL;
#endif

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef null
#define null ((void *)0)
#endif

#ifndef min
#define min(a,b) (((a)<(b))?(a):(b))
#endif

#ifndef max
#define max(a,b) (((a)<(b))?(a):(b))
#endif

#ifndef print
#define print pspDebugScreenPrintf
#endif

#endif

