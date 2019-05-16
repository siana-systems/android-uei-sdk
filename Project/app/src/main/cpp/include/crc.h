/*****************************************************************************
 * COPYRIGHT 2017 UNIVERSAL ELECTRONICS INC ("UEI"). ALL RIGHTS RESERVED.
 * These materials ("Materials") are the intellectual property of UEI, and are
 * provided by UEI on an "As-Is" basis without warranties or representations.
 * The Materials are provided to the direct recipient of the Materials
 * ("Recipient") and such Recipient's authorized partners and customers for
 * internal development, evaluation and implementation purposes, as well as any
 * other purpose or use specifically authorized by any license agreements
 * between UEI and Recipient ("Authorized Purpose"). Except as specifically
 * authorized or licensed under a separate agreement between UEI and Recipient,
 * the user of the Materials may not: (i) modify or create any derivative works
 * of the Materials; (ii) decompile, disassemble, reverse engineer, or otherwise
 * attempt to derive or extract any part of the Materials; or
 * (iii) redistribute, sell, lease, sublicense, or otherwise transfer ownership
 * of the Materials without the prior express written consent of UEI. By
 * accessing and using the Materials, the user agrees to use the Materials
 * solely for the Authorized Purpose only.
 *****************************************************************************/


/**
 * @file
 *
 * @brief	CRC16 supporting defines.
 *
 */

#ifndef CRC_H
#define CRC_H
#ifdef __cplusplus
extern "C"{
#endif


/*-----------------------------------------------------------------------------
						 INCLUDE FILES
-----------------------------------------------------------------------------*/
#include "uapi_defs.h"


/*-----------------------------------------------------------------------------
                    	CONSTANTS AND MACROS
-----------------------------------------------------------------------------*/
#define CRC_INIT 0xFFFF
#define GOOD_CRC 0xf0b8				// Good final FCS value.
#define CRC(crcval,newchar, table)	crcval = (crcval >> 8) ^ \
									table[(crcval ^ newchar) & 0x00ff]

#define FINALIZE_CRC(x)				(x) = (x)^ CRC_INIT


/*-----------------------------------------------------------------------------
                                TYPES
-----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
                              FUNCTION PROTOTYPES
-----------------------------------------------------------------------------*/
void	crcappend(UINT8 *message, UINT16 length);
UINT8	MessageCrcverify(const UINT8 *message, UINT8 length);
UINT16	ComputeCRC16(UINT16 originalCRC, const UINT8 *message, UINT16 length);
UINT16	FinalizeCRC(UINT16 crc);
UINT8	ValidateCRC(UINT16 crc, UINT16 originalCRC);
#ifdef __cplusplus
}
#endif

#endif // CRC_H
