/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* "@(#)xrBlockManager.c Feb  3 14:30:28 2012" */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#define X2C_int32
#define X2C_index32
#ifndef xrBlockManager_H_
#include "xrBlockManager.h"
#endif
#define xrBlockManager_C_
#ifndef xosMalloc_H_
#include "xosMalloc.h"
#endif
#ifndef xosBalls_H_
#include "xosBalls.h"
#endif
#ifndef xosMem_H_
#include "xosMem.h"
#endif

#define xrBlockManager_bitsPerSet 32

#define xrBlockManager_bytesPerSet 4

static X2C_CARD32 xrBlockManager_busySet = 0xFFFFFFFFUL;

static X2C_ADDRESS heapBase;

static X2C_CARD32 bSize;

static X2C_CARD32 * map;

static X2C_CARD32 nSets;

static X2C_CARD32 hint4Search;


static void initMap(X2C_CARD32 numbersets)
{
   X2C_CARD32 i;
   X2C_CARD32 tmp;
   nSets = numbersets;
   map = (X2C_CARD32 *)X2C_malloc(nSets*4UL);
   tmp = nSets-1UL;
   i = 0UL;
   if (i<=tmp) for (;; i++) {
      map[i] = 0UL;
      if (i==tmp) break;
   } /* end for */
   hint4Search = 0UL;
} /* end initMap() */


static X2C_ADDRESS findBlock_markBusy(void)
{
   X2C_CARD32 i;
   i = hint4Search;
   while (map[i]==0xFFFFFFFFUL) {
      ++i;
      if (i==nSets) return 0;
   }
   hint4Search = i;
   i = 0UL;
   while (X2C_IN(i,32,map[hint4Search])) ++i;
   map[hint4Search] |= (1UL<<i);
   return (X2C_ADDRESS)((X2C_ADDRESS)heapBase+(X2C_INT32)(X2C_INT32)
                ((hint4Search*32UL+i)*bSize));
} /* end findBlock_markBusy() */


static void markBlockFree(X2C_CARD32 offset)
{
   X2C_CARD32 i;
   offset = offset/bSize;
   i = offset/32UL;
   map[i] &= ~(1UL<<(offset&31UL));
   if (i<hint4Search) hint4Search = i;
} /* end markBlockFree() */


extern X2C_BOOLEAN xrBlockManager_init(X2C_CARD32 blockSize)
{
   X2C_CARD32 nBlocks;
   X2C_CARD32 nSets0;
   bSize = blockSize;
   nBlocks = ((1073741824UL+bSize)-1UL)/bSize;
   nSets0 = ((nBlocks+32UL)-1UL)/32UL;
   heapBase = X2C_initBalls(nSets0*32UL, blockSize);
   initMap(nSets0);
   return 1;
} /* end init() */


extern X2C_ADDRESS xrBlockManager_alloc(void)
{
   X2C_ADDRESS adr;
   adr = findBlock_markBusy();
   adr = X2C_allocBlock(adr);
   return adr;
} /* end alloc() */


extern void xrBlockManager_free(X2C_ADDRESS adr)
{
   markBlockFree(adr-heapBase);
   X2C_freeBlock(adr);
} /* end free() */


extern void xrBlockManager_exit(void)
{
   X2C_freeAll();
} /* end exit() */


extern void xrBlockManager_BEGIN(void)
{
   static int xrBlockManager_init = 0;
   if (xrBlockManager_init) return;
   xrBlockManager_init = 1;
}
