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
 * @file        uapi.h
 * @brief      This .h file contains all the typedefintions of the standard data types
 *
**/

#ifndef __UAPI_DEFS_H__
#define __UAPI_DEFS_H__

#ifdef __cplusplus
extern "C"{
#endif

/*! \typedef UINT8
 *   UINT8 is defined as unsigned 8 bit
 */
typedef  unsigned char UINT8;
/*! \typedef INT8
 *   INT8 is defined as signed 8 bit
 */
typedef  char INT8;
/*! \typedef UINT16
 *   UINT16 is defined as unsigned 16 bit
 */
typedef  unsigned short UINT16;
/*! \typedef INT16
 *   INT16 is defined as signed 16 bit
 */
typedef  short INT16;
/*! \typedef INT32
 *   INT32 is defined as signed 32 bit
 */
typedef  int INT32;
/*! \typedef UINT32
 *   UINT32 is defined as unsigned 32 bit
 */
typedef  unsigned int UINT32;

typedef  unsigned char BOOL;

/*! \def TRUE
 *   TRUE is defined as 1
 */
#ifndef TRUE
#define TRUE 1
#endif

/*! \def FALSE
 *   FALSE is defined as 0
 */
 #ifndef FALSE
#define FALSE 0
#endif

#ifdef __cplusplus
}
#endif
#endif
