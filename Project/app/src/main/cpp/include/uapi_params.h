/**
 * @file        uapi_params.h
 * @brief       This header file contains definitions for the various configuration parameters
 *              for UAPI
 * 
 */


/*===================================================================
 COPYRIGHT 2010 UNIVERSAL ELECTRONICS INC (UEI).
 These materials are provided under license by UEI.  UEI licenses
 this file to you under the Universal Remote Control API (UAPI)
 License accompanying the UEI libuapi Software (the "License").
 You may not use this file except in compliance with the License.
 You may obtain a copy of the License from UEI. Unless required by
 applicable law or agreed to in writing, all materials distributed
 under the License is distributed on an "AS IS" BASIS, WITHOUT
 WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions
 and limitations under the License.
===================================================================*/


#ifndef __UAPI_PARAMS_H__
#define __UAPI_PARAMS_H__
#ifdef __cplusplus
extern "C"{
#endif


#include "uapi_defs.h"

/* List of all configurable parameters for each feature */

/**
 * @ brief This enumeration defines the various parameters that are configurable for Relative Motion in a UAPI enabled remote control
 */
typedef enum
{
    /** This field enables or disables Relative Motion. This field is 8 bits */
    RelMotionEnable                               = 0x00,
    /** This field enables or disables Relative Motion Acceleration. This field is 8 bits */
    RelMotionAccelEnable                          = 0x01,
    /** This field enables or disables Relative Motion Deceleration. This field is 8 bits */
    RelMotionDecelEnable                          = 0x02,
    /** This field controls the number of physical steps required to map to logical steps. This field is 16 bits */
    RelMotionPhysicalToLogical                    = 0x03, /* 2 byte data */
    /** This field controls the Relative Motion Traverse Time. This field is 16 bits */
    RelMotionTraverseTime                         = 0x04,
    /** This field controls the Relative Motion Deceleration Sample Time. This field is 16 bits */
    RelMotionDecelSampleTime                      = 0x05, /* 2 byte data */
    /** This field controls the Relative Motion Transmit Interval (ms). This field is 16 bits */
    RelMotionTxIntervalMs                         = 0x06, /* 2 byte data */
    /** This field controls the Relative Motion Deceleration Coeffieicent. This field is 16 bits */
    RelMotionDecelCoefficient                     = 0x07, /* 2 byte data */
    /** This field enables or disables Relative Motion Finger Presence Notification. This field is 8 bits */
    RelMotionFingerPresenceNotifyEnable           = 0x08,  /*1 byte data */
    /** This field specifies the finger duration that will be interpreted as a tap (ms) This field is 16 bits*/
    RelMotionTapDuration                          = 0x09,
    /** This field enables or disables relative orientation. This field is 8 bits */
    RelMotionRelativeOrientation                  = 0x0A,
    /** This field enables or disables sending of click as left mouse. This field is 8 bits*/
    RelMotionSendMouseClick                       = 0x0B,
    /** This field enables or disables sending of click as URC select/ok key. This field is 8 bits */
    RelMotionSendSelectKey                        = 0x0C,
    /** This field is the acceleration scale factor. This field is 16 bits */
    RelMotionAccelCoefficient                     = 0x0D,
    /** This field enables or disables the sending of a click as an enter key TextEntry. This field is 8 bits */
    RelMotionSendEnterKey                         = 0x0E,
    /** This field controls the physical to logical conversion for first touch. This field is 16 bits */
    RelMotionFirstPhysicalToLogical 		  = 0x0F,
    /** This field controls the physical to logical conversion for deceleration. This field is 16 bits */
    RelMotionDecelPhysicalToLogical		  = 0x10

} RelativeMotionConfigParameter_t;

/**
 * @ brief This enumeration defines the various parameters that are configurable for Absolute Motion in a UAPI enabled remote control
 */
typedef enum
{
    /** This field enables or disasbles Absolute Position. This field is 8 bits. It is RW */
    AbsMotionEnable	                              = 0, // 1 byte data
     /** This field indicates Min X Value */
    AbsMotionMinX				  			  = 0xF0,  // 2 byte data
     /** This field indicates Max X Value */
    AbsMotionMaxX				  			  = 0xF1,  // 2 byte data
      /** This field indicates Min Y Value */
    AbsMotionMinY				  			  = 0xF2,  // 2 byte data
     /** This field indicates Max Y Value */
    AbsMotionMaxY				  			  = 0xF3,  // 2 byte data
         /** This field indicates Report Rate Value in Hz */
    AbsMotionReportRate				  		  = 0xF4,  // 2 byte data
      /** This field indicates Report Rate Value in Hz */
    AbsMotionSensitivity				  		  = 0xF5,  // 2 byte data
} AbsolutePositionConfigParameter_t;

/**
 * @ brief This enumeration defines the various parameters that are configurable for Remote API in a UAPI enabled remote control
 */
typedef enum
{
    /** This field enables or disables Remote API functionality. It is an 8 bit field. It is RW */
    RemoteAPIEnable				                  = 0 //1 byte data

} RemoteAPIConfigParameter_t;

/**
 * @ brief This enumeration defines the various parameters that are configurable for orientation on a UAPI enabled remote control
 */
typedef enum
{
    /** This field enables or disables orientation reporting. It is an 8 bit field. It is RW */
    OrientationEnable			                  = 0 //1 byte data

} OrientationConfigParameter_t;

/**
 * @ brief This enumeration defines the various parameters that are configurable for URC key presses on a UAPI enabled remote control
 */
typedef enum
{
    /** This field enables or disables User Activity reporting. It is an 8 bit field. It is RW */
    UserActivityEnable			                  = 0 //1 byte data

} UserActivityConfigParameter_t;



/** 
 * @brief These parameters contain information regarding UAPI 
 **/
typedef enum {
 	/** This field indicates TV Key Presses. */
	UapiTVKeyPresses				  = 0xF0,  //1 2 byte data
	/** This field Number of STB Key presses **/
	UapiSTBKeyPresses				  = 0xF1,  //1 2 byte data
	/** This field Number of Touchpad touches **/
	UapiTouchPadTouches				  = 0xF2,  //1 2 byte data
	/** This field Number of Slider touches **/
	UapiSliderTouches			  = 0xF3,  //1 2 byte data
	/** This field indicates StandBy Mode. */
	UapiRemoteStandbyMode		= 0xF4,  //1 1 byte data

	/** Enables Finger Sensor **/
	UapiEnableFingerSensor			= 0xF5,
	/** Enroll User */
	UapiEnrollUser					= 0xF6,
	/** Identify Finger Print**/
	UapiIdentifyFingerPrint			= 0xF7,
	/** Delete Template ID**/
	UapiDeleteTemplateID			= 0xF8,
	/** Delete all TemplateID**/
	UapiDeleteAllTemplateID			= 0xF9,

} UAPIAttributeID_t;

/**
 * @brief This enumeration defines the various parameters that are configurable for the Raw Accelerometer feature on a UAPI enabled remote control
 * */
typedef enum {
    /** This field enables or disables Raw Accelerometer, if equipped. It is an 8 bit field, it is RW */
    RawAccelerometerEnable                            = 0,
    /** This field sets the DataTxInterval value . It is a 16 bit field, it is R */
    DataTxInterval                                = 1,
    /** This field sets the ReportResolution value  . It is a 8 bit field, it is R */
   ReportResolution                                 = 2,
    /** This field sets the ReportRate value  . It is a 8 bit field, it is R */
   ReportRate                                = 0xF4,

} UAPIRawAccelerometerConfigParameter_t;

/**
 * @ brief This enumeration defines the various parameters that are configurable for Any Motion feature on a UAPI enabled remote control
 */
typedef enum
{
    /** This field enables or disables Any Motion reporting. It is an 8 bit field. It is RW */
    AnyMotionEnable				                  = 0 //1 byte data

}AnyMotionConfigParameter_t;

/**
 * @ brief This enumeration defines the various parameters that are configurable for Audio feature on a UAPI enabled remote control
 */
typedef enum
{
    /** This field enables or disables Audio reporting. It is an 8 bit field. It is RW */
    AudioEnable				                  = 0 //1 byte data

}AudioConfigParameter_t;


/*! \def MAX_UAPI_PARAM_DATA
 *   The maximum uapi parameter data length is defined as 16
 */
#define MAX_UAPI_PARAM_DATA 16

/*! \def MAX_PRODUCT_NAME
 *  *   The maximum product name length is defined as 10
 *   */
#define MAX_PRODUCT_NAME 10

/**
 * @ brief This structure contains both the remote control firmware version and the product name of the remote control */
typedef struct UAPIProductInfo_s{
	/** software version of remote firmware */
    unsigned int swVersion;
    /** product name of remote control */
	char productName[MAX_PRODUCT_NAME];//10 byte name of remote
}UAPI_productInfo_t;

/**
 * @ brief This structure is used to store information for a single parameter
 */
typedef struct configParam_s
{
	/** action to be taken for each parameter. set/get/reset */
    unsigned char action;
    /** attribute to be modified */
    unsigned char attributeId;
    /** union of different data types that can be collected */
    union
	{
        /** product information */
		UAPI_productInfo_t productInfo;
        /** 1 byte data storage for parameters with 8 bit data */
        unsigned char   UINT8_data;  /*1 byte data*/
        /** 2 byte data storage for parameters with 16 bit data */
        unsigned short  UINT16_data; /*2 byte data*/
        /** 4 byte data storage for parameters with 32 bit data */
        unsigned int    UINT32_data; /*4 byte data*/
        /** 16 byte data storage for bytestream data */
		unsigned char   bytestring_data[MAX_UAPI_PARAM_DATA]; /*byte string max 16 bytes*/
        /** 16 byte data storage for string data */
        char            charstring_data[MAX_UAPI_PARAM_DATA]; /*character string max 16 bytes*/
    }value;
}UAPI_configParam_t;

/**
 * @ brief This structure is used to store parameters for Raw Sensor Data 
 * */
typedef enum {
    RawSensorDataEnable                           = 0,
    RawSensorDataSuspend                          = 1,
    RawSensorDataNumSensors                       = 2
} RawSensorDataParameter_t;

/**
 * @ brief This structure is used to store a parameter list for a specific feature specified by featureId. It should contain numParams parameters
 */
typedef struct configParamStruct_s{
    /** feature this configuration structure is intended for */
    unsigned char featureId;
    /** the number of parameters in the structure */
    unsigned char numParams;
    /** pointer to UAPI configuration parameter structure */
    UAPI_configParam_t* param;
}UAPI_configParamStruct_t;

/**
 * @brief This structure is used to store a parameter list for a given remote Id
 * */
typedef struct remoteParam_s{
    /** The remote id these parameters are received from */
    unsigned char remoteId;
    /** The parameter list received from the device and remote id specified above */
    UAPI_configParamStruct_t* remoteParams;
}UAPI_remoteParams_t;


//////////////////////////////////////////////////
// new defines to handle configuration, minchun
////////////////////////////////////////////////
#define UAPI_CONFIG_PRODUCT_SPECIFIC_PARAM_START		0xF0    //attrId starts from 0xF0
#define UAPI_CONFIG_PRODUCT_SPECIFIC_PARAM_END			0xFF    //attrId starts from 0xFF
#define UAPI_CONFIG_PRODUCT_SPECIFIC_PARAM_MAX			16    //from 0xF0 to 0xFF

#define UAPI_CONFIG_PARAM_RXED_MAX						64   //max number of params in a rxed uapi message

typedef enum
{
	UAPI_CONFIG_ACTION_ID_GET			= 0,
	UAPI_CONFIG_ACTION_ID_SET			= 1,
	UAPI_CONFIG_ACTION_ID_SET_FROM_NVM	= 2,
	UAPI_CONFIG_ACTION_ID_ERROR			= 3

} UAPI_config_action_id_t;

typedef enum
{
	UAPI_CONFIG_DATATYPE_BOOL			= 0,
	UAPI_CONFIG_DATATYPE_STRING			= 1,
	UAPI_CONFIG_DATATYPE_BYTEARRAY		= 2,
	UAPI_CONFIG_DATATYPE_INT			= 3,

} UAPI_config_datatype_t;


typedef union __attribute__((packed))
{
	struct __attribute__((packed))
	{
		unsigned char len		:4;
		unsigned char dataType	:2;
		unsigned char action	:2;
	} bits;

	unsigned char byte;

} UAPI_config_config_t;

typedef struct __attribute__((packed))
{
	UAPI_config_config_t 	config;
	unsigned char			attrId;
	unsigned char			data0; //first byte of data
} UAPI_config_param_t;

typedef struct __attribute__((packed))
{
	unsigned char len;
	unsigned char data[MAX_UAPI_PARAM_DATA]; /*byte string max 16 bytes*/
} UAPI_config_product_specific_param_t;

typedef struct __attribute__((packed))
{
	unsigned char remoteId;
	unsigned char appId;
	unsigned char num;
	unsigned char list[UAPI_CONFIG_PARAM_RXED_MAX]; //list of param attrId
} UAPI_config_rxed_param_list_t;

//--------------------------------------
//Core/GneralService 0x00 parameters
typedef enum
{
	UAPI_CORE_PARAM_ID_ENABLE			= 0,	//1 byte,indicates if UAPI is enabled in the remote control
	UAPI_CORE_PARAM_ID_VERSIONINFO		= 1, 	//4 bytes, ReadOnly
	UAPI_CORE_PARAM_ID_PRODUCTINFO		= 2, 	//4-16 bytes, ReadOnly, null terminated
	UAPI_CORE_PARAM_ID_POLLING_RATE		= 3, 	//4 bytes, RW
	UAPI_CORE_PARAM_ID_CPU_HW_INFO		= 4,	//4 byte,ReadOnly
	UAPI_CORE_PARAM_ID_POLLING_STATE	= 5,	//1 byte, RW, enables or disables auto poll in the remote control
	UAPI_CORE_PARAM_ID_LOADER_VER_INFO	= 6,	//4 bytes, R
	UAPI_CORE_PARAM_ID_MAX_PAYLOAD		= 7,	//1 byte Max Payload Size
	UAPI_CORE_PARAM_ID_SECURED			= 8,	//1 byte,  if network used to transfer UAPI messages is secured
	UAPI_CORE_PARAM_ID_MTU_SIZE			= 9,	//1 byte, underlying NW MTU Size

	UAPI_CORE_PARAM_ID_MAX			= 10

} UAPI_core_config_param_id_t;

typedef struct
{
	BOOL	enable			;
	UINT32	verInfo			;
	UINT8	prodInfo[17]	;
	UINT32	pollingRate		;
	UINT32	hwInfo			;
	UINT8	pollingState	;
	UINT32	loaderVerInfo	;
	UINT8	maxPayload		;
	UINT8	secured			;
	UINT8	mtu				;
} UAPI_core_config_param_data_t;

typedef struct __attribute__((packed))
{
	UINT32 ver; //0xbbbbmmMM
	char name[MAX_PRODUCT_NAME] ;
} UAPI_product_info_t;

//--------------------------------------
//OTA parameters
typedef enum
{
	UAPI_OTA_PARAM_ID_ENABLE		= 0,	//RW  Enable / Disable **/
	UAPI_OTA_PARAM_ID_DEFAULT_LEN	= 1, 	//RW 2bytes default to 64
	UAPI_OTA_PARAM_ID_RCU_TIMEOUT	= 2,	//RW 2bytes RC timeout in ms
	UAPI_OTA_PARAM_ID_HOST_TIMEOUT	= 3,	//RW 2bytes Host timeout in ms

	UAPI_OTA_PARAM_ID_MAX = 4

} UAPI_ota_config_param_id_t;

typedef struct __attribute__((packed))
{
	BOOL	enable			;
	UINT16	defaultLen		;
	UINT16	rcuTimeout		;
	UINT16	hostTimeout		;
} UAPI_ota_config_param_data_t;


//--------------------------------------
//Quickset 0x13 parameters
typedef enum
{
	UAPI_QS_PARAM_ID_ENABLE				= 0,	/*  Enable / Disable Quickset **/
	UAPI_QS_PARAM_ID_FLAGS				= 1, 	/* RF or IR Supported Flag */
	UAPI_QS_PARAM_ID_SUPPORTED_ENC		= 2, 	/* Supported Encryption Methods */
	UAPI_QS_PARAM_ID_ENC_METHOD			= 3, 	/* Encryption Method to be Used */
	UAPI_QS_PARAM_ID_RF_SLOTS			= 4, 	/* Encryption Method to be Used */
	UAPI_QS_PARAM_ID_SESSION_TIMEOUT	= 5,	/* Session Time out in milliseconds */
	UAPI_QS_PARAM_ID_MAX_RECORD_SIZE	= 6,	/* Maximum record payload Size Supported */
	UAPI_QS_PARAM_ID_MIN_RECORDID		= 7,	/* Minimum record ID Available */
	UAPI_QS_PARAM_ID_MAX_RECORDID		= 8,	/* Maximum Record ID Available */
	UAPI_QS_PARAM_ID_ACTIVE_KEYMAP		= 9,
	UAPI_QS_PARAM_ID_RF_VERSION			= 10,

	UAPI_QS_PARAM_ID_MAX = 11 //standard IDs for all the products

} UAPI_quickset_config_param_id_t;

typedef struct __attribute__((packed))
{
	BOOL	enable			;
	BOOL	flags			;
	UINT8	supportedEnc	;
	UINT8	encMethod		;
	UINT32	rfSlots			;
	UINT32	sessionTimeOut	;
	UINT16	maxRecordSize	;
	UINT16	minRecordID		;
	UINT16	maxRecordID		;
	UINT16	activeKeymap	;
	UINT16	rfVersion		;
} UAPI_quickset_config_param_data_t;


//--------------------------------------
//RFDB
typedef enum
{
	UAPI_RFDB_PARAM_ID_ENABLE 				= 0, // This Field enables or disables Display
	UAPI_RFDB_PARAM_ID_AUTH_METHOD 			= 1, //Enables or Disables Authentication Handshake
	UAPI_RFDB_PARAM_ID_ENCRYPTION_METHOD 	= 2, //Enables or Disables Encryption of the PayLoad
	UAPI_RFDB_PARAM_ID_DISCOVERY_TIMEOUT 	= 3, //
	UAPI_RFDB_PARAM_ID_TRANSACTION_TIMEOUT 	= 4,  //
	UAPI_RFDB_PARAM_ID_MAX = 5
} UAPI_rfdb_config_param_id_t;

typedef struct __attribute__((packed))
{
	BOOL	enable	 			;
	UINT8	authMethod 			;
	UINT8	encryptionMethod 	;
	UINT32	discoveryTimeOut 	;
	UINT32	transactionTimeOut	;
} UAPI_rfdb_config_param_data_t;
//--------------------------------------
//Battery
typedef enum
{
	UAPI_BATTERY_PARAM_ID_ENABLE 			= 0, //It is an 8 bit field, it is RW
	UAPI_BATTERY_PARAM_ID_REPORTING_MASK	= 1, // one byte
	UAPI_BATTERY_PARAM_ID_CRITICAL_THR 		= 2, //2 bytes
	UAPI_BATTERY_PARAM_ID_WARNING_THR 		= 3, //2 bytes
	UAPI_BATTERY_PARAM_ID_FULL_THR 			= 4, //2 bytes
	UAPI_BATTERY_PARAM_ID_MAX = 5,

} UAPI_battery_config_param_id_t;

typedef struct __attribute__((packed))
{
	BOOL	enable	 		;
	UINT8	reportingMask 	;
	UINT16	criticalThr 	;
	UINT16	warningThr 		;
	UINT16	fullThr		 	;
} UAPI_battery_config_param_data_t;

//--------------------------------------
//Finder
typedef enum
{
	UAPI_FEEDBACK_PARAM_ID_ENABLE 			= 0,//It is an 8 bit field, it is RW
	UAPI_FEEDBACK_PARAM_ID_GENERIC_TIMEOUT 	= 1,	// 16 bit field, it is RW in units of 62.5ms
	UAPI_FEEDBACK_PARAM_ID_FINDER_TIMEOUT 	= 2,	// 16 bit field, it is RW in units of 62.5ms
	UAPI_FEEDBACK_PARAM_ID_LED_TIMEOUT 		= 3,	// 16 bit field, it is RW in units of 62.5ms
	UAPI_FEEDBACK_PARAM_ID_TONE_TIMEOUT 	= 4,	// 16 bit field, it is RW in units of 62.5ms
	UAPI_FEEDBACK_PARAM_ID_MAX = 5

	//UAPI_FEEDBACK_PARAM_ID_BUZZER_DUTYCYCLE	= 0XF0,	//16 bit field, it is RW
	//UAPI_FEEDBACK_PARAM_ID_BUZER_PERIOD 	= 0XF1			//16 bit field, it is RW

}UAPI_feedback_config_param_id_t;

typedef struct __attribute__((packed))
{
	BOOL	enable	 		;
	UINT16	genericTimeout 	;
	UINT16	finderTimeout 	;
	UINT16	ledTimeout 		;
	UINT16	toneTimeout 	;
} UAPI_feedback_config_param_data_t;

//--------------------------------------
//URC Key
typedef enum
{
	UAPI_URCKEY_PARAM_ID_ENABLE 	= 0, //1 byte data
	UAPI_URCKEY_PARAM_ID_MULTIKEY 	= 1,
	UAPI_URCKEY_PARAM_ID_MAX = 2
}UAPI_urckey_config_param_id_t;

typedef struct __attribute__((packed))
{
	BOOL	enable	 	;
	UINT8	multiKey 	;
} UAPI_urckey_config_param_data_t;


//--------------------------------------
//Storage
typedef enum
{
	UAPI_STORAGE_PARAM_ID_ENABLE 		= 0, //1 byte data
	UAPI_STORAGE_PARAM_ID_ERASEREQUIRED = 1, //1
	UAPI_STORAGE_PARAM_ID_PAGE_SIZE 	= 2, //2 bytes
	UAPI_STORAGE_PARAM_ID_LENGTH 		= 3, //4bytes
	UAPI_STORAGE_PARAM_ID_MAX = 4
}UAPI_storage_config_param_id_t;

typedef struct __attribute__((packed))
{
	BOOL	enable;
	UINT8	eraseRequired;
	UINT16	pageSize;
	UINT32	length;
} UAPI_storage_config_param_data_t;

//--------------------------------------
//Text Entry 0x22
typedef enum
{
	UAPI_TEXTENTRY_PARAM_ID_ENABLE 			= 0, //1 byte data
	UAPI_TEXTENTRY_PARAM_ID_SYM_SHIFT_MODE 	= 1, //1
	UAPI_TEXTENTRY_PARAM_ID_CAP_MODE 		= 2, //1 byte
	UAPI_TEXTENTRY_PARAM_ID_ALT_MODE 		= 3, //1 byte
	UAPI_TEXTENTRY_PARAM_ID_MAX = 4
}UAPI_textentry_config_param_id_t;

typedef struct __attribute__((packed))
{
	BOOL	enable;
	UINT8	symShiftMode;
	UINT16	capMode;
	UINT32	altMode;
} UAPI_textentry_config_param_data_t;


//--------------------------------------
//Rawsensor 0x44 UAPIFeatureIDRawSensorData
typedef enum
{
	UAPI_RAWSENSOR_PARAM_ID_ENABLE	= 0, //1 byte data
	UAPI_RAWSENSOR_PARAM_ID_MASK 	= 1, //1
	UAPI_RAWSENSOR_PARAM_ID_MAX = 2
}UAPI_rawsensor_config_param_id_t;

typedef struct __attribute__((packed))
{
	BOOL	enable;
	UINT8	mask;
} UAPI_rawsensor_config_param_data_t;


/**
 * @brief This enumeration defines the various parameters that are configurable for the Raw Sensor feature on a UAPI enabled remote control
 * */
typedef enum {
    /** This field enables or disables Remote finder, if equipped. It is an 8 bit field, it is RW */
    RawSensorEnable                            = 0,
    /** This field sets the bit mask for tap directions to be reported. It is a 8 bit field, it is RW */
    RawSensorMask                                = 1,

} RawSensorConfigParameter_t;

#ifdef __cplusplus
}
#endif


#endif
