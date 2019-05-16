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
 * @file        uapi_types.h
 * @brief       This file contains the structure definitions used by UAPI
 **/

#ifndef __UAPI_INTERFACE_H__
#define __UAPI_INTERFACE_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include "uapi_defs.h"

typedef UINT8 UAPI_RemoteID_t;
typedef UINT8 UAPI_nif_id_t; enum
{
	UAPI_RF4CE_NIF = 0x00,
	UAPI_BLE_NIF = 0x01,
	UAPI_WFD_NIF = 0x02,
	UAPI_HID_NIF = 0x03,
	UAPI_ETH_NIF = 0x04,
	UAPI_ZRC2_NIF = 0x05,

	UAPI_NIF_MAX = 0x06,
	UAPI_NIF_INVALID = UAPI_NIF_MAX
} __attribute__ ((packed));

/*! \def UAPI_VERSION_SIZE
 *  *   The maximum size of UAPI version information is 4 bytes
 *   */
#define UAPI_VERSION_SIZE       0x04

/*! \def UAPI_PRODUCT_NAME_SIZE
 *  *   The maximum size of UAPI product name information is 10 bytes
 *   */
#define UAPI_PRODUCT_NAME_SIZE  10

/*! \def MAX_REMOTEAPI_DATA_SIZE
 *   The maximum remote API data size is 1040
 */
#define MAX_REMOTEAPI_DATA_SIZE 1040

/*! \def UAPI_MAX_NUM_OF_RAW_ACCELEROMTERS
* The maximum Number of Raw accerometer sensors are 7
*/
#define UAPI_MAX_NUM_OF_RAW_ACCELEROMTERS 	7

/*! \def MAX_PCM_DATA
 *   The maximum size of decoded PCM data
 *   Increased to accommodate bigger packets for rf4ce
 */
#define	MAX_PCM_DATA				1024

#define DBUS_ERROR					-1
#define TIMEOUT_INFINITE			-1

typedef UINT8 UAPI_appid_index_t; enum
{
	UAPI_APPID_INDEX_GENERALSERVICE 		= 0,
	UAPI_APPID_INDEX_RAPI 					= 1,
	UAPI_APPID_INDEX_URCKEY 				= 2,
	UAPI_APPID_INDEX_USERACTIVITY 			= 3,
	UAPI_APPID_INDEX_TEXTENTRY 				= 4,
	UAPI_APPID_INDEX_ORIENTATION 			= 5,
	UAPI_APPID_INDEX_RELATIVEMOTION 		= 6,
	UAPI_APPID_INDEX_BATTERYSTATUS 			= 7,
	UAPI_APPID_INDEX_ABSOLUTEPOSITION 		= 8,
	UAPI_APPID_INDEX_SETTING_NOOPTESTMODE 	= 9,
	UAPI_APPID_INDEX_ERROR_NOOP 			= 10,
	UAPI_APPID_INDEX_HIRES_RELATIVEMOTION 	= 11,
	UAPI_APPID_INDEX_HIRES_ABSOLUTEPOSITION = 12,
	UAPI_APPID_INDEX_RAWSENSENSORDATA 		= 13,
	UAPI_APPID_INDEX_OTA 					= 14,
	UAPI_APPID_INDEX_ANYMOTION 				= 15,
	UAPI_APPID_INDEX_RAWACCELEROMETER 		= 16,
	UAPI_APPID_INDEX_REMOTEFINDER 			= 17,
	UAPI_APPID_INDEX_AUDIO 					= 18,
	UAPI_APPID_INDEX_STORAGE 				= 19,
	UAPI_APPID_INDEX_TESTMODE 				= 20,
	UAPI_APPID_INDEX_RFDB	 				= 21,
	UAPI_APPID_INDEX_QUICKSET 				= 22,

	UAPI_APPID_INDEX_max 					= 23,
} __attribute__ ((packed));

/**
 * @brief       defines enum of all features available in UAPI
 */
typedef enum __attribute__ ((packed))
{
	UAPIFeatureIDGeneralServices 			= 0x00,
	UAPIFeatureIDOTA 						= 0x01,
	UAPIFeatureIDRemoteAPI 					= 0x11,
	UAPIFeatureIDRFDB						= 0x12,
	UAPIFeatureIDQuickSet					= 0x13,
	UAPIFeatureIDUserActivity 				= 0x20,
	UAPIFeatureIDUrcKey 					= 0x21,
	UAPIFeatureIDText 						= 0x22,
	UAPIFeatureIDRemoteFinder 				= 0x25,
	UAPIFeatureIDAnyMotion 					= 0x30,
	UAPIFeatureIDOrientation 				= 0x31,
	UAPIFeatureIDRelativeMotion 			= 0x32,
	UAPIFeatureIDHighResRelativeMotion 		= 0x33,
	UAPIFeatureIDAbsolutePosition 			= 0x34,
	UAPIFeatureIDHighResAbsolutePosition	= 0x35,
	UAPIFeatureIDAudio 						= 0x36,
	UAPIFeatureIDStorage 					= 0x37,
	UAPIFeatureIDRawAccelerometer 			= 0x41,
	UAPIFeatureIDBatteryStatus 				= 0x43,
	UAPIFeatureIDRawSensorData 				= 0x44,
	UAPIFeatureIDTestMode 					= 0x50,

}UAPIFeatureID_t;

typedef enum __attribute__ ((packed)) UAPIFeedbackType_s
{

	UAPI_FEEDBACK_TYPE_NEGATIVE = 0,
	UAPI_FEEDBACK_TYPE_NEUTRAL = 1,
	UAPI_FEEDBACK_TYPE_POSITIVE = 2

}UAPIFeedbackType_t;

typedef enum __attribute__ ((packed)) UAPIFeedbackSeverity_s
{

	UAPI_FEEDBACK_SEVERITY_LOW = 0,
	UAPI_FEEDBACK_SEVERITY_MEDIUM = 127,
	UAPI_FEEDBACK_SEVERITY_HIGH = 255

}UAPIFeedbackSeverity_t;

typedef enum __attribute__ ((packed)) UAPIFeedbackModality_s
{

	UAPI_FEEDBACK_MODALITY_AUDIBLE = 1,
	UAPI_FEEDBACK_MODALITY_VISIBLE = 2,
	UAPI_FEEDBACK_MODALITY_TACTILE = 4

}UAPIFeedbackModality_t;
/**
 * @brief       defines enum of all feedback conditions supported by Feedback App Id
 */

typedef enum __attribute__ ((packed)) UAPIFeedbackCondition_s
{
	/** Any Key press Termination Condition  */
	UAPI_FEEDBACK_CONDITION_ANYKEYPRESS = 1,
	/** Any Motion Termination Condition  */
	UAPI_FEEDBACK_CONDITION_ANYMOTION = 2,
	/** Timeout Termination Condition  */
	UAPI_FEEDBACK_CONDITION_TIMEOUT = 4,
	/** Any of the above Termination Conditions  */
	UAPI_FEEDBACK_CONDITION_ANY = 7,
}UAPIFeedbackCondition_t;

/**
 * @brief       defines enum of all LED colors supported by Feedback App Id
 */

typedef enum __attribute__ ((packed)) UAPIFeedbackColor_s
{

	UAPI_FEEDBACK_RED = 0,
	UAPI_FEEDBACK_ORANGE ,
	UAPI_FEEDBACK_AMBER ,
	UAPI_FEEDBACK_YELLOW ,
	UAPI_FEEDBACK_GREEN ,
	UAPI_FEEDBACK_BLUE ,
	UAPI_FEEDBACK_WHITE ,
	UAPI_FEEDBACK_BACKLIGHT =128
}UAPIFeedbackColor_t;

/**
 * @brief       defines structure provided when keys are pressed on remote
 */
typedef struct __attribute__ ((packed))
{
	/** release (0), press (1), or repeat (2) */
	UINT8 eventType;
	/** USB HID Usage table */
	UINT8 usagePage;
	/** ID of key */
	UINT16 keyID;
}UAPI_URCKeyPress_t;

/**
 * @brief       defines structure provided when text entry data is generated
 */
typedef struct __attribute__ ((packed))
{
	/** press (0), release (1) */
	UINT8 eventType;
	/** UTF8 (1), UTF16 (2), UTF32 (3) */
	UINT8 charType;
	/** UTF string */
	UINT8 *UTFchar;
}UAPI_TextEntry_t;

/**
 * @brief       defines structure showing button mapping
 *
 */
typedef struct __attribute__ ((packed))
{
	/** 1 bit for button 1 */
	INT8 button1;
	/** 1 bit for button 2 */
	INT8 button2;
	/** 1 bit for button 3 */
	INT8 button3;
	/** 4 bits reserved */
	INT8 reserved;
	/** 1 bit for finger present */
	INT8 fingerPresent;
}UAPI_ButtonInfo_t;

/**
 * @brief       defines structure provided when relative motion data is generated
 *
 */

typedef struct __attribute__ ((packed))
{
	/** button mapping */
	UAPI_ButtonInfo_t buttonInfo;
	/** displacement relative to direction of travel on X axis */
	INT8 xDisplacement;
	/** displacement relative to direction of travel on Y axis */
	INT8 yDisplacement;
	/** vertical scroll value */
	INT8 verticalScroll;
	/** horizontal scroll value */
	INT8 horizontalPan;
}UAPI_RelativeMotion_t;

/**
 * @brief       defines structure provided when high resolution relative motion data is generated
 */
typedef struct __attribute__ ((packed))
{
	/** button mapping info */
	UAPI_ButtonInfo_t buttonInfo;
	/** displacement relative to direction of travel on X axis */
	INT16 xDisplacement;
	/** displacement relative to direction of travel on Y axis */
	INT16 yDisplacement;
	/** vertical scroll value */
	INT8 verticalScroll;
	/** horizontal scroll value */
	INT8 horizontalPan;
}UAPI_HighResRelativeMotion_t;

/**
 * @brief       defines structure provided when absolute motion data is generated
 *
 */
typedef struct __attribute__ ((packed))
{
	/** button mapping info */
	UAPI_ButtonInfo_t buttonInfo;
	/** absolute position of finger on X axis */
	UINT8 xPosition;
	/** absolute position of finger on Y axis */
	UINT8 yPosition;
}UAPI_AbsoluteMotion_t;

/**
 * @brief       defines structure provided when high resolution absolute motion is generated
 */
typedef struct __attribute__ ((packed))
{
	/** button mapping info */
	UAPI_ButtonInfo_t buttonInfo;
	/** absolute position of finger on X axis */
	UINT16 xPosition;
	/** absolute position of finger on Y axis */
	UINT16 yPosition;
}UAPI_HighResAbsoluteMotion_t;

/**
 * @brief       defines structure provided when Any Motion data is generated
 *
 */
typedef struct __attribute__ ((packed))
{
	/** Acceleraion on any axis */
	UINT32 Accel:1;
	/** Tap or double Tap detected */
	UINT32 Tap:1;
	/** Any Rotation */
	UINT32 Rotate:1;
	/** reserved */
	UINT32 Reserved:3;
	/** Sensor used for Navigation */
	UINT32 NAV:1;
	/** Motion Start/Stop */
	UINT32 AnyMotion:1;
}UAPI_AnyMotion_t;

/**
 * @brief       defines sub structure provided for Raw accelerometer data
 *
 */
typedef struct __attribute__ ((packed))
{
	/** X axis Raw accel */
	UINT8 xAccel;
	/** Y axis Raw accel */
	UINT8 yAccel;
	/** Z axis Raw accel */
	UINT8 zAccel;
}UAPI_Accel_t;

/**
 * @brief       defines structure provided when Raw accelerometer data is generated
 *
 */
typedef struct __attribute__ ((packed))
{
	/** Number of Sensors  */
	UINT8 numSensors;
	/** Acceerometer Datal */
	UAPI_Accel_t rawAccelData[UAPI_MAX_NUM_OF_RAW_ACCELEROMTERS];
}UAPI_RawAccelerometerData_t;

/**
 * @brief       defines structure provided when orientation data is generated
 *
 */
typedef struct __attribute__ ((packed))
{
	/** download facing */
	UINT32 Down:1;
	/** upward facing */
	UINT32 Up:1;
	/** portrait facing down */
	UINT32 PortraitDown:1;
	/** portrait facing up */
	UINT32 PortraitUp:1;
	/** landscape facing right */
	UINT32 LandscapeRight:1;
	/** landscape facing left */
	UINT32 LandscapeLeft:1;
	/** reserved */
	UINT32 Reserved:2;
}UAPI_Orientation_t;

/**
 * @brief       defines structure provided when user activity data is generated
 *
 */
typedef struct __attribute__ ((packed))
{
	/** feature ID generating the wakeup */
	UINT16 featureID;
}UAPI_UserActivity_t;
/**
 * @brief       defines structure provided when Remote API data is generated
 *
 */
typedef struct __attribute__ ((packed))
{
	/** record length of Remote API data */
	UINT16 recordLength;
	/** remote API data */
	UINT8 remoteAPIdata[MAX_REMOTEAPI_DATA_SIZE];
}UAPI_RemoteAPI_t;
/**
 * @brief       defines structure provided when battery status data is generated
 *
 */
typedef struct __attribute__ ((packed))
{
	/** OK, Warning, Critical, Unknown (0x00, 0x01, 0x02, 0xFF) */
	UINT8 status;
	/** level, in percentage */
	UINT8 level;
	/** voltage/2048 = actual voltage */
	UINT16 voltage;
}UAPI_BatteryStatus_t;

/////////////////////////////////////////////////////////
// AUDIO defines
////////////////////////////////////////////////////////
typedef UINT8 UAPI_audio_msg_t; enum
//typedef enum __attribute__ ((packed))
{
	UAPI_MSG_STARTAUDIO 	= 0,
	UAPI_MSG_AUDIOSUPPORT	= 1,
	UAPI_MSG_AUDIOSTATE		= 2, //rxed state from other side
	UAPI_MSG_AUDIODATA		= 3,
	UAPI_MSG_STOPAUDIO		= 4,
	UAPI_MSG_LOCAL_STATE	= 5,	// local codec state

	UAPI_MSG_UNKNOWN		= 0xFF,
} __attribute__ ((packed));
//UAPI_AudioMessageType_e;

typedef UINT8 UAPI_audio_bps_t; enum
{
	UAPI_AUDIO_BPS_8		= 8,
	UAPI_AUDIO_BPS_16		= 16
} __attribute__ ((packed)) ;
typedef UINT8 UAPI_audio_compression_t; enum
{
	UAPI_AUDIO_COMPRESSION_NONE		= 0,
	UAPI_AUDIO_COMPRESSION_A_LAW	= 1,
	UAPI_AUDIO_COMPRESSION_MU_LAW	= 2,
	UAPI_AUDIO_COMPRESSION_IMA_ADPCM= 3,
	UAPI_AUDIO_COMPRESSION_MSBC		= 4,
	UAPI_AUDIO_COMPRESSION_OPUS		= 5,

	UAPI_AUDIO_COMPRESSION_MAX	= 6
} __attribute__ ((packed));

typedef struct __attribute__ ((packed))
{
	UINT8 bps:7;
	UINT8 Signed:1;
}UAPI_AudioSigned_BPS_t;

/**
 * @brief       defines structure provided when Start Audio Payload data is generated
 *
 */
typedef struct __attribute__ ((packed))
{
	UINT16 					 samplingFrequency; //Sampling Frequency in Hz
	UAPI_AudioSigned_BPS_t 	 Signed_BPS; 		//signed
	UAPI_audio_compression_t compression; 		//Compression
} UAPI_StartAudioPayload_t;

typedef struct __attribute__ ((packed))
{
	UINT32 AUDIO_RSVD	: 2;
	UINT32 AUDIO_16BPS	: 1;
	UINT32 AUDIO_8BPS	: 1;
	UINT32 AUDIO_UNSIGNED: 1;
	UINT32 AUDIO_SIGNED	: 1;
	UINT32 AUDIO_SOURCE	: 1;
	UINT32 AUDIO_SINK	: 1;

} UAPI_AudioSupportResponse_Byte1;

typedef struct __attribute__ ((packed))
{
	UINT8 AUDIO_RSVD	: 2;
	UINT8 AUDIO_16BPS	: 1;
	UINT8 AUDIO_8BPS	: 1;
	UINT8 AUDIO_UNSIGNED: 1;
	UINT8 AUDIO_SIGNED	: 1;
	UINT8 AUDIO_SOURCE	: 1;
	UINT8 AUDIO_SINK	: 1;

} UAPI_support_flags_t;

/**
 * @brief       defines structure provided when  Audio Support Payload data is generated
 *
 */
typedef struct __attribute__ ((packed))
{
	UAPI_support_flags_t 		flags;
	UINT8 						numSupportedFrequencies;//NF Value
	UINT16 						samplingFrequency;		//Sampling Frequency in Hz
	UINT8 						numCodecs;				//Number of Codec
	UAPI_audio_compression_t 	compression; 			//Compression
} UAPI_AudioSupportPayload_t;

typedef struct __attribute__ ((packed))
{
	UINT16 	sampleCounter;
	UINT16 	prevSample;
	UINT8 	index;
} UAPI_audio_adpcm_hdr_t;

typedef struct __attribute__ ((packed))
{
	UAPI_audio_adpcm_hdr_t 	hdr;
	UINT8 					*sampleData; //comrpessed data
} UAPI_audio_dpcm_data_t;


/**
 * @brief       defines structure provided when  Audio State Payload data is generated
 *
 */
typedef struct __attribute__ ((packed))
{
	/** Codec State **/
	UINT16 codecState;
	/** Dropped Samples **/
	UINT8 numDroppedSamples;
}UAPI_AudioStatePayload_t_notUsed;


typedef struct __attribute__ ((packed))
{
	INT16 	sample;		//one 16-bit sample value
	UINT8 	index;		//codesc index
	UINT16 	lostCnt;	//lost count
} UAPI_audio_state_t;

/**
 * @brief       defines structure provided when  Audio data samples are generated
 *
 */
typedef struct __attribute__ ((packed))
{
	/** Audio Data Length **/
	UINT16 audioDataLength;
	/** decoded Data **/
	UINT16 audioData[MAX_PCM_DATA];
} UAPI_AudioData_t;

/**
 * @brief       defines structure provided when Audio data is generated
 *
 */
typedef struct __attribute__ ((packed))
{
	/** StartAudio, AudioSupport, AudioState, AudioData, StopAudio, Unknown (0x00, 0x01, 0x02, 0x03, 0x04, 0xFF) */
	UAPI_audio_msg_t audioMessageType;
	union
	{
		UAPI_StartAudioPayload_t 	startAudioPayload	; 	//Payload for Start Audio Message
		UAPI_AudioSupportPayload_t 	audioSupportPayload	; 	//Payload for Audio Support
//		UAPI_AudioStatePayload_t 	audioStatePayload	; 	//Payload for Audio state
		UAPI_AudioData_t 			audioDataPayload	; 	//Payload for Audio data
		UAPI_audio_state_t			audioState			;	//Audio state
	};
} UAPI_Audio_t;

////////////// End of Audio Defines ////////////////////

typedef enum __attribute__ ((packed))
{
	UAPI_MSG_RFDB_DATA_TRANS_ACK	= 0x00,
	UAPI_MSG_RFDB_DATA_TRANSFER 	= 0x01,
	UAPI_MSG_RFDB_DATA_TRANS_END 	= 0x02,
	UAPI_MSG_RFDB_COMMAND		= 0x03,
	UAPI_MSG_RFDB_UNKNOWN		= 0xFF
} UAPI_RfdbMessageType_t;

/**
 * @brief       defines structure for RFDB
 *
 */

typedef struct __attribute__ ((packed))
{
	UINT8 rfdbCommand;
	UINT16 payloadLength;
	UINT8 discNodeParams[256];
} UAPI_RFDB_t;

/**
 * @brief       defines structure for RFDB
 *
 */

typedef struct __attribute__ ((packed))
{
	UINT8 rfdbCommand;
	UINT8 Status;
} UAPI_RFDB_Status_t;

/* End of RFDB */

typedef enum __attribute__ ((packed))
{
	UAPI_MSG_QUICKSET_START_SESSION		= 0x00,
	UAPI_MSG_QUICKSET_END_SESSION 			= 0x01,
	UAPI_MSG_QUICKSET_START_DISC 			= 0x02,
	UAPI_MSG_QUICKSET_STOP_DISC				= 0x03,
	UAPI_MSG_QUICKSET_REPORT_NODES		= 0x04,
	UAPI_MSG_QUICKSET_REPORT_TIMEOUT		= 0x05,
	UAPI_MSG_QUICKSET_SET_CONFIG			= 0x06,
	UAPI_MSG_QUICKSET_REPORT_IEEE_ADDR   	= 0x07,
	UAPI_MSG_QUICKSET_WRITE_RESULT			= 0x08,
	UAPI_MSG_QUICKSET_WRITE_RECORD			= 0x09,
	UAPI_MSG_QUICKSET_DELETE_RECORD		= 0x0A,
	UAPI_MSG_QUICKSET_READ_RECORD			= 0x0B,
	UAPI_MSG_QUICKSET_RECORD_DATA			= 0x0C,
	UAPI_MSG_QUICKSET_LIST_ALL_RECORDS		= 0x0D,
	UAPI_MSG_QUICKSET_RECORD_LIST			= 0x0E,
	UAPI_MSG_QUICKSET_READ_RESIDENT_SETUP	= 0x0F,
	UAPI_MSG_QUICKSET_RESIDENT_SETUP		= 0x10,
	UAPI_MSG_QUICKSET_RESULT				= 0x11,
	UAPI_MSG_QUICKSET_REMOTE_STATUS_RESP  = 0x12
}UAPI_QuickSetMessageType_t;



typedef struct __attribute__ ((packed))
{
	UINT8 quickSetCmd;
	UINT16 payloadLength;
	UINT8 *dataPtr;
} UAPI_QuickSet_t;


/**
 * @brief       defines structure provided when UAPI data is generated from the remote
 *
 */
typedef struct __attribute__ ((packed))
{
	/** logical ID of remote generating data */
	UAPI_RemoteID_t remoteId;
	/** feature generating the data */
	UAPIFeatureID_t featureId;
	/** the data from the remote control */
	void* featureData;
}UAPIFeatureData_t;

/**
 * @brief UAPI Header structure
 * **/
typedef struct __attribute__ ((packed))
{
	/** UAPI Options */
	UINT8 UAPIOptions;
	/** sequence number */
	UINT8 seqNum;
	/** feature ID */
	UINT8 appID;
	/** UAPI code */
	UINT8 opCode;
}UAPIHdr_t;

/**
 * @ brief      UAPI Data packet structure
 * **/
typedef struct __attribute__ ((packed))
{
	/** logical ID of remote */
	UINT8 remoteId;
	/** length of the data */
	UINT16 dataLength;
	/** UAPI header */
	UAPIHdr_t uapiHdr;
	/** pointer to data */
	UINT8 *data;
}UAPIDataPkt;

/**
 * @brief      XMP1 data packet structure
 *
 * **/
typedef struct __attribute__ ((packed))
{
	/** 4 byte registry packet */
	UINT8 registryPacket[4];
	/** 4 byte data packet */
	UINT8 XMP1DataPacket[4];

}XMP1Data_t;
/**
 * @brief      Data structure containing detailed information regarding remote platform
 * **/
typedef struct __attribute__ ((packed))
{
	/** remote control uapi version */
	UINT8 rcu_uapi_version[UAPI_VERSION_SIZE];
	/** remote control software version */
	UINT8 rcu_sw_version[UAPI_VERSION_SIZE];
	/** remote control product name */
	UINT8 rcu_product_name[UAPI_PRODUCT_NAME_SIZE];
	/** remote control hardware revision */
	UINT8 rcu_hw_info;
	/** remote control IR support */
	UINT8 rcu_ir_info;
	/** remote control RF support */
	UINT8 rcu_rf_info;
	/** remote control CPU speed */
	UINT8 rcu_cpu_info;
	/** remote control Bootloader version */
	UINT8 rcu_bl_version[UAPI_VERSION_SIZE];
#if 0
	/** remote control Max Payload */
	UINT16 rcu_max_payload;
	/** remote control Network security flag */
	UINT8 rcu_NW_secured;
#endif

}UAPI_RemoteInfo_t;

/**
 * @brief   Enumeration for OTA Upgrade status
 */
typedef enum __attribute__ ((packed))
{
	OTA_UPGRADE_NONE = 0x00,
	OTA_UPGRADE_STARTED,
	OTA_UPGRADE_IN_PROGRESS,
	OTA_UPGRADE_COMPLETE,
	OTA_UPGRADE_FAILED,
	OTA_UPGRADE_FAILED_LOW_BATTERY,
	OTA_UPGRADE_CANCELLED,
	OTA_UPGRADE_TIMEDOUT,
	OTA_UPGRADE_FORCED = 0x400
}UAPI_OTADownloadStatus_t;

/**
 * @brief      Data structure containing detailed information regarding OTA Transfer
 * **/
typedef struct __attribute__ ((packed))
{
	/** Downloading status */
	UAPI_OTADownloadStatus_t status;
	/** Bytes transferred so far */
	INT32 current_byte;
	/** File size in bytes */
	INT32 total_bytes;
	/** New Product Version **/
	UINT8 swVersion[4];
}UAPI_OTAStatus_t;

/** UAPI Error codes **/
typedef enum __attribute__ ((packed))
{
	UAPI_SUCCESS 					= 0x00, // no error
	UAPI_EPERM 						= 0x01, //permissions error
	UAPI_INVALID_FEATURE			= 0x02, //invalid feature error
	UAPI_ESRCH 						= 0x03, //no valid handler error
	UAPI_INVALID_PARAMETER			= 0x04, //invalid parameter
	UAPI_OUT_OF_MEMORY				= 0x05, //out of memory error
	UAPI_NOT_NULL					= 0x06, //not null error
	UAPI_E2BIG 						= 0x07, //too big error
	UAPI_ENOEXEC 					= 0x08, //no application  error
	UAPI_INVALID_OPCODE 			= 0x09, //invalid opcode error
	UAPI_INVALID_INDEX				= 0x0A, //invalid index error
	UAPI_EAGAIN 					= 0x0B, //try again error
	UAPI_ENOMEM 					= 0x0C, //error no memory error
	UAPI_EACCES 					= 0x0D, //error access permissions error
	UAPI_EFAULT 					= 0x0E, //broken error
	UAPI_EMPTY_PARAMETER_LIST 		= 0x0F, //empty parameter list error
	UAPI_EBUSY 						= 0x10, // busy error
	UAPI_EEXIST 					= 0x11, //already exists error
	UAPI_ATTRIBUTE_NOT_FOUND		= 0x12, //attribute not available error
	UAPI_ENODEV 					= 0x13,
	UAPI_INVALID_PARAMETER_VALUE 	= 0x14,
	UAPI_EINVAL 					= 0x16,
	UAPI_ENOSPC 					= 0x1C,

	UAPI_ENAMETOOLONG 				= 0x24,
	UAPI_ENOSYS 					= 0x26,
	UAPI_ENOMSG 					= 0x2A,

	UAPI_EBADRQC 					= 0x38,
	UAPI_ENODATA 					= 0x3D,
	UAPI_ETIME 						= 0x3E,

	UAPI_ECOMM 						= 0x46,
	UAPI_EPROTO 					= 0x47,
	UAPI_EBADMSG 					= 0x4A,
	UAPI_EOVERFLOW 					= 0x4B,

	UAPI_EILSEQ 					= 0x54,
	UAPI_FAILURE					= 0x55,
	UAPI_UNSUPPORTED_XMP_FEATURE 	= 0x56,
	UAPI_XMP1_BAD_CHECKSUM 			= 0x57,
	UAPI_UNSUPPORTED_NIF			= 0x58,
	UAPI_FILE_ERROR					= 0x59,
	UAPI_EMSGSIZE 					= 0x5A,
	UAPI_ENOPROTOOPT 				= 0x5C,
	UAPI_EPROTONOSUPPORT 			= 0x5D,

	UAPI_EPFNOSUPPORT 				= 0x60,
	UAPI_ENETDOWN 					= 0x64,
	UAPI_ENETUNREACH 				= 0x65,
	UAPI_ENETRESET 					= 0x66,
	UAPI_ECONNRESET 				= 0x68,
	UAPI_ENOBUFS 					= 0x69,
	UAPI_ETIMEDOUT 					= 0x6E,
	UAPI_ECONNREFUSED 				= 0x6F,
	UAPI_EHOSTDOWN 					= 0x70,
	UAPI_STORAGE_FILE_NOT_FOUND		= 0x71,
	UAPI_STORAGE_BAD_CHECKSUM		= 0x72,
	UAPI_STORAGE_OFFSET_MISMATCH	= 0x73,
	UAPI_STORAGE_FULL				= 0x74,
	UAPI_INVALID_REMOTE				= 0x75,
	UAPI_VERSION_NOT_SUPPORTED		= 0x76,
	UAPI_OTA_IN_PROGRESS			= 0x77,
	UAPI_OTA_FILE_EXISTS			= 0x78,
	UAPI_FILE_OPEN_ERROR			= 0x79,
	UAPI_FILE_CRC_ERROR				= 0x7A,

}uapi_status_t;

/** Ack Response codes **/
typedef enum __attribute__ ((packed))
{
	UAPI_ACK_RESP_SUCCESS = 0,
	UAPI_ACK_RESP_FAILURE = 1,
	UAPI_ACK_RESP_TIMEOUT = 2
}uapi_ackresp_t;

/**
 * @brief        UAPI error structure
 *
 * */
typedef struct __attribute__ ((packed))
{
	/** feature error pertains to*/
	UINT8 featureId;
	/** remoteId generating error */
	UAPI_RemoteID_t remoteId;
	/** error code generated */
	uapi_status_t error_code;
	/** datalength of data if there is additional data */
	UINT8 dataLength;
	/** contents of error message */
	UINT8 *data;
}UAPIError_t;

/**
 *
 * @brief UAPI feature list structure
 *
 * */
typedef struct __attribute__ ((packed))
{
	/** if set to true, Core UAPI features supported bye remote */
	UINT8 feature_Core;
	/** if set to true, QuickSet feature is supported by remote */
	UINT8 feature_QuickSet;
	/** if set to true, User Activity wakeup is supported by remote*/
	UINT8 feature_UserActivity;
	/** if set to true, URC Key is supported by remote*/
	UINT8 feature_UrcKey;
	/** if set to true, text entry is supported by remote */
	UINT8 feature_Text;
	/** if set to true, orientation is supported by remote */
	UINT8 feature_Orientation;
	/** if set to true, relative motion is supported by remote */
	UINT8 feature_RelativeMotion;
	/** if set to true, absolute position is supported by remote */
	UINT8 feature_AbsolutePosition;
	/** if set to true, battery status is supported by remote */
	UINT8 feature_BatteryStatus;
	/** if set to true, Over the Air Update is supported by remote */
	UINT8 feature_OTA;
	/** if set to true, remote finder is supported by remote */
	UINT8 feature_RemoteFinder;
	/** if set to true, high resolution relative motion is supported by remote */
	UINT8 feature_HighResRelativeMotion;
	/** if set to true, high resolution absolute position is supported by remote*/
	UINT8 feature_HighResAbsolutePosition;
	/** if set to true, raw sensor data is supported by remote*/
	UINT8 feature_RawSensorData;
	/** if set to true, Storage is supported by remote */
	UINT8 feature_Storage;
	/** if set to true, Any Motion is supported by remote*/
	UINT8 feature_AnyMotion;
	/** if set to true, Raw accelerometer  is supported by remote*/
	UINT8 feature_RawAccelerometer;
	/** if set to true, Audio  is supported by remote*/
	UINT8 feature_Audio;

	UINT8 feature_TestMode; //if set to true, TestMode is supported by remote
	UINT8 feature_QS13; //if set to true, Quickset AppId 0x13 is supported by remote
	UINT8 feature_RFDB; //if set to true, RFDB is supported by remote

}UAPIRemoteFeatureList_t;

/**
 * @brief UAPI Core Data report
 ***/
typedef struct __attribute__ ((packed))
{
	/** ID of remote control generating report*/
	UAPI_RemoteID_t remoteId;
	/** feature list report */
	UAPIRemoteFeatureList_t features;
}UAPICoreData_t;

/**
 *
 * @brief remote finder timeout conditions
 *
 * */
typedef enum __attribute__ ((packed)) UAPI_RemoteFinderCond_s
{
	/** remote finder will cease based on timeout*/
	UAPI_REMOTEFINDER_TIMEOUT =1,
	/** remote finder will cease based on keypress*/
	UAPI_REMOTEFINDER_KEYPRESS = 2,
	/** remote finder will cease based on any motion */
	UAPI_REMOTEFINDER_ANY_MOTION = 4,
	/** remote finder will cease based on timeout or keypress */
	UAPI_REMOTEFINDER_TIMEOUT_KEYPRESS = 3,
	/** remote finder will cease based on timeout or any motion */
	UAPI_REMOTEFINDER_TIMEOUT_MOTION = 5,
	/** remote finder will cease based on keypress or any motion*/
	UAPI_REMOTEFINDER_KEYPRESS_MOTION = 6,
	/** remote finder will cease based on all conditions */
	UAPI_REMOTEFINDER_ALL_COND = 7
}UAPIRemoteFinderCond_t;

/**
 *
 * @brief       over the air update information
 *
 * */
typedef struct __attribute__ ((packed)) UAPI_OTAUpdateParams_s
{
	UINT8 flags;
	/** specify the file type, binary, image */
	UINT8 type;
	/** absolute path to hex file upgrade */
	INT8 hexFileName[512];
	/** size of upgrade file */
	UINT32 hexFileSz;
	/** major version number of upgrade image*/
	UINT8 majorVersionNum;
	/** minor version number of upgrade image */
	UINT8 minorVersionNum;
	/** release number of upgrade image */
	UINT16 swReleaseNum;
	/** hardware revision of remote targetted */
	char hwRev;
	/** CRC of file */
	INT16 CRC;
	/** product name of remote targetted */
	char productName[UAPI_PRODUCT_NAME_SIZE];
}UAPI_OTAUpdateParams_t;

/**
 *  * @brief       defines structure showing button mapping
 *   *
 *    */
typedef struct __attribute__ ((packed))
{
	/** 6 bits reserved */
	UINT32 reserved:6;
	/** 1 bit for button released */
	UINT32 button_released:1;
	/** 1 bit for button pressed */
	UINT32 button_pressed:1;

}UAPI_RawSensorButtonInfo_t;

/**
 *
 * @brief   Raw Sensor Data Packet
 *
 * */
typedef struct __attribute__ ((packed)) UAPI_RawSensorData_s
{
	/** sequence number for raw sensor data **/
	UINT16 seqNum;
	/** button information */
	UAPI_RawSensorButtonInfo_t button;
	/** length of sensor data */
	UINT16 length;
	/** array of sensor data */
	UINT8* sensorData;
}UAPI_RawSensorData_t;

/*! \def UAPI_MAX_CAL_NAME
 *  *  *   The maximum size of the calibration name is 8 bytes
 *   *   */
#define UAPI_MAX_CAL_NAME 8

/**
 *
 *  @brief   Raw Sensor Calibration Packet data
 *
 **/
typedef struct __attribute__ ((packed)) UAPI_RawSensorCalibration_s
{
	/** name of the calibration data packet */
	INT8 CalibrationName[UAPI_MAX_CAL_NAME];
	/** array of calibration data */
	UINT8* CalibrationData;
}UAPI_RawSensorCalibration_t;

/**
 *
 *  @brief   Storage entry structure
 *
 **/
typedef struct __attribute__ ((packed))
{
	/** File Identifier maximum of 254 */
	UINT8 ID;
	/** length of file */
	INT16 length;
}UAPI_Storage_BAT_entry_t;

/***************************************************
 *  Test Mode Defines
 ***************************************************/
typedef UINT8 UAPI_TestMode_FeatureId_t; enum
{
	UAPI_TESTMODE_FEATUREID_KEY = 0x10,
	UAPI_TESTMODE_FEATUREID_IR_1 = 0x20,
	UAPI_TESTMODE_FEATUREID_RF_1 = 0x30,
	UAPI_TESTMODE_FEATUREID_APP_1 = 0x40,
} __attribute__ ((packed));

typedef UINT8 UAPI_TestMode_Cmd_t; enum
{
	UAPI_TESTMODE_CMD_SETPARAM_ = 0x00,
	UAPI_TESTMODE_CMD_SETPARAM_REQUEST = 0x01,
	UAPI_TESTMODE_CMD_SETPARAM_RESPONSE = 0x02,
	UAPI_TESTMODE_CMD_GETPARAM_REQUEST = 0x03,
	UAPI_TESTMODE_CMD_GETPARAM_RESPONSE = 0x04,
	UAPI_TESTMODE_CMD_SETPARAM_TRIGACTION = 0x05
} __attribute__ ((packed));

typedef UINT8 UAPI_TestMode_StartTestRsp_t; enum
{
	UAPI_TESTMODE_START_SUCCESS = 0x00,
	UAPI_TESTMODE_START_ERROR = 0x01,
	UAPI_TESTMODE_START_RESERVED = 0x10,
} __attribute__ ((packed));

#define UAPI_DELAY_UNIT_MS			0
#define UAPI_DELAY_UNIT_SECODS		1
#define UAPI_DELAY_UNIT_MINUTES		2
#define UAPI_DELAY_UNIT_HOURS		3

#define UAPI_TESTMODE_DELAY_OPT_FROM_START		0
#define UAPI_TESTMODE_DELAY_OPT_FROM_END		1

typedef struct __attribute__ ((packed))
{
	UINT8 subModuleFlag : 1; //indicates if the feature has sub-module or not
	UINT8 id : 7;//test feature feature id
}UAPI_TestMode_Feature_t;

typedef struct __attribute__ ((packed))
{
	UINT16 data : 14; //delay data
	UINT16 unit : 2;//delay unit
}UAPI_TestMode_Delay_t;

typedef struct __attribute__ ((packed))
{
	UINT16 repetition; //number of repeating tests
}UAPI_TestMode_Start_t;

typedef UINT8 UAPI_TestMode_Delay_Option_t;

typedef struct __attribute__ ((packed))
{
	UAPI_TestMode_Feature_t feature;
	UINT8 cmd_id;
	UINT8 param_size;
	UINT8 *param_data;
	UAPI_TestMode_Delay_Option_t delayOpt;
	UAPI_TestMode_Delay_t delay;
	UINT16 repetition; //number of repeating tests
}UAPI_TestMode_Descriptor_t;
typedef struct __attribute__ ((packed))
{
	UINT8 reportSize;
	UINT8 *reportData;
}UAPI_TestMode_Report_t;

typedef INT16 (* UAPI_NIFSendHandler_t)( UAPIDataPkt *uPkt );

typedef enum __attribute__ ((packed))
{
	UAPI_NIF_ATTR_ID 			= 0,
	UAPI_NIF_ATTR_MTU 			= 1,
	UAPI_NIF_ATTR_BYPASSQUEUE 	= 2,
	UAPI_NIF_ATTR_SENDER 		= 3,
	UAPI_NIF_ATTR_OTA_ENABLED	= 4,
	UAPI_NIF_ATTR_RAPI_EANBLED	= 5,

	UAPI_NIF_ATTR_MAX = 6
}UAPI_nif_attr_id_t;

uapi_status_t UAPI_set_nif_attr(UAPI_RemoteID_t remoteId, UAPI_nif_attr_id_t attr, void *pVal);
uapi_status_t UAPI_get_nif_attr(UAPI_RemoteID_t remoteId, UAPI_nif_attr_id_t attr, void *pVal);

/***************************************************
 *  RFDB Mode Defines
 ***************************************************/
typedef enum __attribute__ ((packed))
{
	RFDB_CMDID_START_DISCOVERY 		= 0,
	RFDB_CMDID_REPORT_NODES	   		= 1,
	RFDB_CMDID_SET_CONFIG			= 2
}UAPI_rfdb_startTransfer_cmd_t;

typedef enum __attribute__ ((packed))
{
	RFDB_CMDID_REPORT_TIMEOUT	= 2,
	RFDB_CMDID_STOP_DISCOVERY  	= 3
} UAPI_rfdb_cmd_t;

#ifdef __cplusplus
}
#endif

#endif
