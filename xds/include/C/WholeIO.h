/* XDS v2.60: Copyright (c) 1999-2011 Excelsior, LLC. All Rights Reserved. */
/* Generated by XDS Modula-2 to ANSI C v4.20 translator */

#ifndef WholeIO_H_
#define WholeIO_H_
#ifndef X2C_H_
#include "X2C.h"
#endif
#ifndef IOChan_H_
#include "IOChan.h"
#endif

extern void WholeIO_ReadInt(IOChan_ChanId, X2C_INT32 *);

extern void WholeIO_WriteInt(IOChan_ChanId, X2C_INT32, X2C_CARD32);

extern void WholeIO_ReadCard(IOChan_ChanId, X2C_CARD32 *);

extern void WholeIO_WriteCard(IOChan_ChanId, X2C_CARD32, X2C_CARD32);


extern void WholeIO_BEGIN(void);


#endif /* WholeIO_H_ */