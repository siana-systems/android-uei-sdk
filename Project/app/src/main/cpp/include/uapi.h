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
 * @brief       The main API header file for the UAPI library.
 *
 **/

#ifndef __UAPI_H__
#define __UAPI_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#include "uapi_params.h"
#include "uapi_defs.h"
#include "uapi_types.h"

/*! \def UAPI_GENERALSERVICES_NAME
 *   The UAPI General Services Notification is GeneralServices
 */
#define UAPI_GENERALSERVICES_NAME "GeneralServices"
/*! \def UAPI_REMOTEAPI_NAME
 *   The UAPI Remote API Notification is RemoteAPI
 */
#define UAPI_REMOTEAPI_NAME "RemoteAPI"
/*! \def UAPI_USERACTIVITY_NAME
 *   The UAPI User Activity Notification is UserActivity
 */
#define UAPI_USERACTIVITY_NAME "UserActivity"
/*! \def UAPI_URCKEY_NAME
 *   The UAPI URC KEY Notification is UrcKey
 */
#define UAPI_URCKEY_NAME "UrcKey"
/*! \def UAPI_TEXTENTRY_NAME
 *   The UAPI Text Entry Notificadtion is TextEntry
 */
#define UAPI_TEXTENTRY_NAME "TextEntry"
/*! \def UAPI_ORIENTATION_NAME
 *   The UAPI Orientation Notification is Orientation
 */
#define UAPI_ORIENTATION_NAME "Orientation"

/*! \def XMP_RELATIVEMOTION_Slider_NAME
 *  *   The XMP Relative Motion Slider Notification is XMPRelativeMotionSlider
 *   */
#define XMP_RELATIVEMOTION_Slider_NAME "XMPRelativeMotionSlider"

/*! \def UAPI_RELATIVEMOTION_NAME
 *   The UAPI Relative Motion Notification is RelativeMotion
 */
#define UAPI_RELATIVEMOTION_NAME "RelativeMotion"
/*! \def UAPI_HIGHRESRELATIVEMOTION_NAME
 *  *   The UAPI High Resolution Relative Motion Notification is RelativeMotion
 *   */
#define UAPI_HIGHRESRELATIVEMOTION_NAME "HighResRelativeMotion"
/*! \def UAPI_ABSOLUTEPOSITION_NAME
 *   The UAPI Absolute Position Notification is AbsolutePosition
 */
#define UAPI_ABSOLUTEPOSITION_NAME "AbsolutePosition"
/*! \def UAPI_HIGHRESABSOLUTEPOSITION_NAME
 *  *   The UAPI Absolute Position Notification is AbsolutePosition
 *   */
#define UAPI_HIGHRESABSOLUTEPOSITION_NAME "HighResAbsolutePosition"
/*! \def UAPI_BATTERYSTATUS_NAME
 *   The UAPI Battery Status Notification is BatteryStatus
 */
#define UAPI_BATTERYSTATUS_NAME "BatteryStatus"

/*! \def UAPI_RAWSENSORDATA_NAME
 *  *  *   The UAPI Raw Sensor Data Notification is RawSensorData
 *   *   */
#define UAPI_RAWSENSORDATA_NAME "RawSensorData"
/*! \def UAPI_CONFIGURATION_NAME
 *   Ths UAPI Configuration Notification is Configuration
 */
#define UAPI_CONFIGURATION_NAME "Configuration"
/*! \def UAPI_ERROR_NAME
 *   The UAPI Errors Notification is Errors
 */
#define UAPI_ERROR_NAME "Errors"
/*! \def UAPI_OTA_NAME
 *   The UAPI OTA Server Notification is OTA
 */
#define UAPI_OTA_NAME "OTA"

/*! \def UAPI_TESTMODE_NAME
 *   The UAPI TestMode Server Notification is TestMode
 */
#define UAPI_TESTMODE_NAME "TestMode"

/*! \def UAPI_RAWACCELEROMETER_NAME
 *  *   The UAPI Raw Accelerometer Data Notification is RawAccelerometer
 *   */
#define UAPI_RAWACCELEROMETER_NAME "RawAccelerometer"

/*! \def UAPI_ANYMOTION_NAME
 *  *   The UAPI Any Motion Data Notification is AnyMotion
 *   */
#define UAPI_ANYMOTION_NAME "AnyMotion"

/*! \def UAPI_FEEDBACK_NAME
 *   Ths UAPI Feedback  Notification is Feedback
 */
#define UAPI_FEEDBACK_NAME "Feedback"

/*! \def UAPI_AUDIO_NAME
 *   Ths UAPI Audio  Notification is Audio
 */
#define UAPI_AUDIO_NAME "Audio"

/*! \def UAPI_STORAGE_NAME
 *   Ths UAPI Storage  Notification is Storage
 */
#define UAPI_STORAGE_NAME "Storage"
/*! \def UAPI_RFDB_NAME
 *   Ths UAPI RFDB  Notification is RFDB
 */
#define UAPI_RFDB_NAME "RFDB"

/*! \def UAPI_QUICKSET_NAME
 *   Ths UAPI QuickSet Notification is QuickSet
 */
#define UAPI_QUICKSET_NAME "QuickSet"

#if 0
/*! \def UAPIFeature_Core
 *   The UAPI Core ID is 0x00
 */

#define UAPIFeature_Core 		 	 0x00

/*! \def UAPIFeature_OTA
 *   The UAPI OTA ID is 0x01
 */
#define UAPIFeature_OTA 		 	 0x01

/*! \def UAPIFeature_RemoteAPI
 *   The UAPI Feature Remote API ID is 0x11
 */
#define UAPIFeature_RemoteAPI        0x11
/*! \def UAPIFeature_RFDB
 *   The UAPI RFDB API ID is 0x12
 */
#define UAPIFeature_RFDB        0x12
/*! \def UAPIFeature_UserActivity
 *   The UAPI Feature UserActivity ID is 0x20
 */
#define UAPIFeature_UserActivity 	 0x20
/*! \def UAPIFeature_UrcKey
 *   The UAPI Feature UrcKey ID is 0x21
 */
#define UAPIFeature_UrcKey		     0x21
/*! \def UAPIFeature_Text
 *   The UAPI Feature Text ID is 0x22
 */
#define UAPIFeature_Text		     0x22

/*! \def UAPIFeature_Finder
 *   The UAPI Feature Finder ID is 0x25
 */
#define UAPIFeature_Finder		     0x25

/*! \def UAPIFeature_AnyMotion
 *   The UAPI Feature AnyMotion ID is 0x30
 */
#define UAPIFeature_AnyMotion	     0x30

/*! \def UAPIFeature_Orientation
 *   The UAPI Feature Orientation ID is 0x31
 */
#define UAPIFeature_Orientation	     0x31
/*! \def UAPIFeature_RelativeMotion
 *   The UAPI Feature Relative Motion ID is 0x32
 */
#define UAPIFeature_RelativeMotion   0x32
/*! \def UAPIFeature_AbsolutePosition
 *   The UAPI Feature Absolute Position ID is 0x34
 */
#define UAPIFeature_AbsolutePosition 0x34

/*! \def UAPIFeature_HiResAbsolutePosition
 *   The UAPI Feature Absolute Position ID is 0x35
 */
#define UAPIFeature_HiResAbsolutePosition 0x35

/*! \def UAPIFeature_Audio
 *   The UAPI Feature Audio ID is 0x36
 */
#define UAPIFeature_Audio    0x36

/*! \def UAPIFeature_Storage
 *   The UAPI Feature Storage ID is 0x37
 */
#define UAPIFeature_Storage          0x37

/*! \def UAPIFeature_BatteryStatus
 *   The UAPI Feature Battery Status ID is 0x43
 */
#define UAPIFeature_BatteryStatus    0x43

/*! \def UAPIFeature_OTA
 *   The UAPI OTA ID is 0x01
 */
#define UAPIFeature_TestMode 		 	0x50

/*! \def UAPIFeature_RawAccelerometer
 *   The UAPI Feature RawAccelerometer ID is 0x41
 */
#define UAPIFeature_RawAccelerometer  0x41
#endif

/*! \def MAX_UAPI_REMOTES
 *   The maximum number of remote controls that this library can support
 */
#define MAX_UAPI_REMOTES            10
#define UAPI_MAX_DUTY_CYCLE 		100
#define UAPI_HDR_SIZE (sizeof(UAPIHdr_t))


#ifdef UAPI_ENABLE_OPUS
#define CHANNELS		1		// Number of audio channels.
#define SAMPLE_RATE		16000	// Audio sampling rate.
#define MAX_FRAME_SIZE	640		// Maximum PCM frame size decoded from an Opus frame.
#endif // UAPI_ENABLE_OPUS

/**
 * @brief        initializes UAPI library
 *
 * @return       uapi_success if UAPI library is initialized successfully
 *
 **/
void UAPI_Init(void);

/**
 * @brief        deinitializes the UAPI library
 *
 * @return       uapi_success if UAPI library is de-initialized successfully
 **/
void UAPI_Stop(void);

/**
 * @brief        entry point for raw data into UAPI
 *
 * @param        msgData the wrapped UAPI data packet to be processed by the UAPI library
 *
 * @return       none
 **/
void UAPI_DeMultiplexer(UAPIDataPkt *msgData);

/**
 * @brief        entry point for XMP1 data into UAPI
 *
 * @param        xmp1Data - raw xmp1 data to be handled by UAPI library
 *
 * @return       uapi_status_t
 **/
uapi_status_t ProcessXMP1Data(XMP1Data_t* xmp1Data);

/**
 * @brief       registration call to associate registry packets with XMP1 data
 *
 * @param       registry number of note, UAPI feature name associated with that particular feature
 * @param       featureName  XMP feature to register callbacks with
 *
 * @return      uapi_status_t
 **/
uapi_status_t RegisterXMP1Registry(unsigned int registry, const char* featureName);

/**
 * @brief        creates a configuration parameter structure list
 *
 * @param        thing pointer to the data structure that needs to be created
 * @param        numParams the number of parameters to be stored in the parameter list
 * @param        featureId the UAPIFeature that should be configured
 *
 * @return       a valid pointer to the configuration parameter structure, NULL if
 *               the structure was unable to be created.
 *
 **/
UAPI_configParamStruct_t* UAPI_CreateParamStruct(UAPI_configParamStruct_t* thing, unsigned char numParams, unsigned char featureId);

/**
 * @brief        destroys a configuration parameter structure
 *
 * @param        params pointer to the configuration parameter structure to be destroyed
 *
 * @return       none
 **/
void UAPI_DestroyParamStruct(UAPI_configParamStruct_t* params);

/**
 * @brief        sets a value in a configuration parameter structure list
 *
 * @param        paramStruct pointer to configuration parameter structure to populate
 * @param        index the index of the parameter in the structure
 * @param        attribute the ID of the attribute to be configured
 * @param        value pointer to the data to be stored in the configuration parameter structure
 * @param        size the sizeof of the value datatype
 *
 * @return       uapi_success if successful, error code detailing failure if not
 **/
uapi_status_t UAPI_SetParam(UAPI_configParamStruct_t* paramStruct, unsigned char index, unsigned char attribute, void* value, int size);

/**
 * @brief        gets a value in a configuration parameter structure list
 *
 * @param        paramStruct point to configuration parameter structure list to retrieve value from
 * @param        attribute the ID of the attribute to retrieve
 * @param        value pointer to data for storage from the configuration parameter structure list
 *
 * @return       uapi_success if value is valid
 **/
uapi_status_t UAPI_GetParam(UAPI_configParamStruct_t* paramStruct, unsigned char attribute, void* value);

/**
 * @brief        gets an action in a configuration parameter structure list
 *
 * @param        paramStruct point to configuration parameter structure list to retrieve action from
 * @param        attribute the ID of the attribute action to retrieve
 * @param        action pointer to data for storage from the configuration parameter structure list
 *
 * @return       uapi_success if action is valid
 **/
uapi_status_t UAPI_GetAction(UAPI_configParamStruct_t* paramStruct, unsigned char attribute, void *action);



/**
 * @brief This routine sends UAPI Get Param  to remote.
 *
 * @param remote ID -- Remote ID
 * @param attribute -- Param ID
 *
 * @return uapi_status_t
 */

uapi_status_t UAPI_GetRemoteParam(UAPI_RemoteID_t remoteId, unsigned char attribute);


/**
 * @brief        registers a callback to be notified when the appropriate data is received from the remote
 *
 * @param        featureName see defines for feature names
 * @param        FuncPtr function pointer to be called when notification arrives
 *
 * @return       uapi_success if registration succeeds
 **/
uapi_status_t UAPI_RegisterCallback( const char* featureName, void (*FuncPtr)(void*) );

/**
 * @brief        sends configuration parameters to remote specified by remoteId
 *
 * @param        params parameter list created by UAPI_createParamStruct
 * @param        remoteId the remote to send the parameters to
 *
 * @return       uapi_success if the request is successfully queued up
 **/
uapi_status_t UAPI_ConfigureFeature(void* params, UAPI_RemoteID_t remoteId);

/**
 * @brief        Announce the Pending Messages in DTE_HOST
 * @param        Pending msgCnt in DTE_HOST
 * @param        remoteId the ID of the desired remote
 *
 * @return       returns uapi_success successfully sent
 **/
uapi_status_t UAPI_MsgPendingAnnounce (UINT16 msgCnt, UAPI_RemoteID_t remoteId);

/**
 * @brief        get info of the specified feature from the remote connected
 * @param        featureId see defines of UAPIFeature_ IDs for featureIds
 * @param        remoteId the ID of the desired remote
 *
 * @return       returns uapi_success if request is successfully queued up
 **/
uapi_status_t UAPI_GetInfo (UINT8 featureId, UAPI_RemoteID_t remoteId);

/**
 * @brief        queues request to get remote control feature list. When remote responds, user will be notified through callback
 *
 * @param        remoteId the simple ID of the desired remote
 *
 * @return       UAPI_SUCCESS if request is successfully queued
 */
uapi_status_t UAPI_GetRemoteFeatures(UAPI_RemoteID_t remoteId);

/**
 * @brief This routine sends UAPI Echo Request  to remote.
 *
 * @param buf -- Echo request message
 * @param bufLen -- Echo request message length
 * @param remoteId -- remote id
 *
 * @return uapi_status_t
 */
uapi_status_t UAPI_SendEchoRequest(UINT8 *buf, UINT8 bufLen, UAPI_RemoteID_t remoteId );

/**
 * @brief        retrieves the version of the UAPI library
 *
 * @param        libraryVersion pointer to a unsigned 32bit variable to store the library version
 *
 * @return       uapi_success if the version request was successful, libraryVersion will be invalid if not.
 **/
uapi_status_t UAPI_GetVersion (UINT32* libraryVersion);

/**
 * @brief	Flush the message queue.
 *
 * @param	rid -- Remote ID.
 *
 * @return	None.
*********************************************************************/
void UAPI_flushMsgQ(UAPI_RemoteID_t rid);

/**
 * @brief        upgrades remote specified by remoteId
 *
 * @param        remoteId simple pairing reference of remote control to communicate upgrade information to.
 * @param        params OTA parameters specifying filename, version information, product information
 * @param        flags to specify if the file should be stored in memory or in file
 *
 * @return       uapi_success if request and processing of file data is successful.
 **/
uapi_status_t UAPI_UpgradeRemote (UAPI_RemoteID_t remoteId, UAPI_OTAUpdateParams_t* params, UINT8 flags);

/**
 * @brief This function will cancel an upgrade in progress
 *
 * @param remoteId -- remote id
 *
 * @return uapi_status_t
 */
uapi_status_t UAPI_UpgradeCancel( UAPI_RemoteID_t remoteId );
/**
 * @brief	This function sends an NIA message to a remote.
 *
 * @param	remoteId	 -- Remote ID
 * @param	pImageFile	 -- OTA file name
 * @param	forcedUpdate -- forced Update flag
 *
 * @return	A UAPI success or error code.
*********************************************************************/
uapi_status_t UAPI_ota_SendUpdateImage(UAPI_RemoteID_t remoteId, char *pImageFile, UINT8 forcedUpdate);

UAPI_OTADownloadStatus_t  UAPI_GetUpgradeState( UAPI_RemoteID_t remoteId);
uapi_status_t UAPI_ota_RemoveAllFiles( void );
uapi_status_t UAPI_ota_ShowAllFileDetails( void );
uapi_status_t UAPI_ota_GetFileInfo(char *fileName, UAPI_OTAUpdateParams_t *pInfo);

/**
 * @brief        retrieves the amount of free space currently available for storage
 *
 * @param        remoteId the simple ID of the desired remote
 * @param        FreeSpace pointer to a signed 32 bit integer to store the amount of free space
 *
 * @return       uapi_success if free space request was successful
 *
 */
uapi_status_t UAPI_StorageGetFreeSpace( UAPI_RemoteID_t remoteId, INT32* FreeSpace);
/**
 * @brief        retrieves the total size of the storage area in the remote control
 *
 * @param        remoteId the simple ID of the desired remote
 * @param        TotalSpace pointer to a signed 32 bit integer to store the amount of totalspace
 *
 * @return       uapi_success if space request is successful
 */
uapi_status_t UAPI_StorageGetTotalSize(UAPI_RemoteID_t remoteId, INT32* TotalSpace);
/**
 * @brief        retrieves data from storage area based on File ID
 *
 * @param        remoteId the simple ID of the desired remote
 * @param        ID requested ID of file to retrieve
 * @param        *data pointer to buffer to store retrieved data
 * @param        *length pointer to length variable to store size of retrieve data.
 *
 * @return       will return UAPI_SUCCESS when retrieval completes or times out. This is a blocking function
 *
 */
uapi_status_t UAPI_StorageReadData (INT8 remoteId, UINT8 ID, UINT8* data, INT16* length);

/**
 * @brief        retrieves data from storage area based on File ID
 *
 * @param        remoteId the simple ID of the desired remote
 * @param        *entries pointer to entries list, will be created by this function and returned
 * @param        *num_entries the number of entries in the returned list
 *
 * @return       will return a valid pointer to the list of entries, it needs to be freed by the caller. Will be NULL if a failure occured.
 *               num_entries will only be valid if the return of this function is non NULL.
 **/
UAPI_Storage_BAT_entry_t* UAPI_StorageGetBATList( UAPI_RemoteID_t remoteId, UAPI_Storage_BAT_entry_t* entries, UINT8* num_entries);
/**
 * @brief        delete data from storage area based on File ID
 *
 * @param        remoteId the simple ID of the desired remote
 * @param        ID requested ID of file to delete
 *
 * @return       will return UAPI_SUCCESS when retrieval completes or times out. This is a blocking function
 * */
uapi_status_t UAPI_StorageDeleteBATEntry( UAPI_RemoteID_t remoteId, UINT8 ID);

/**
 * @brief        defragments the storage are of any "deleted" data and compacts storage area
 *
 * @param        remoteId the simple ID of the desired remote
 *
 * @return       will return UAPI_SUCCESS when retrieval completes or times out. This is a blocking function
 **/
uapi_status_t UAPI_StorageDefrag( UAPI_RemoteID_t remoteId );

/**
 * @brief        writes data requested by user to remote control
 *
 * @param        remoteId the simple ID of the desired remote
 * @param        *ID pointer to store ID after write is successful
 * @param        *data pointer to buffer with data to write
 * @param        length denoting the amount of data to be written
 *
 * @return       will return UAPI_SUCCESS when write completes or times out, will return UAPI_STORAGE_FULL if storage area becomes full
 **/
uapi_status_t UAPI_StorageWriteData (UAPI_RemoteID_t remoteId, UINT8 *ID, UINT8* data, INT16 length);

/**
 * @brief        queues request to get remote control battery status.
 *
 * @param        remoteId the simple ID of the desired remote
 *
 * @return       UAPI_SUCCESS if request is successfully queued
 */

uapi_status_t UAPI_BatteryStatusRequest(UAPI_RemoteID_t remoteId );

/**
 * @brief        queues request to send QuickSet related data to remote control
 *
 * @param        *message buffer with QuickSet data to be sent to remote control
 * @param        size length of QuickSet data to be sent
 * @param        remoteId the simple ID of the desired remote
 *
 * @return       UAPI_SUCCESS if request is successfully queued
 */
uapi_status_t UAPI_SendRAPIMsgToRemote(UINT8* message, INT16 size, UAPI_RemoteID_t remoteId);

/**
 * @brief        announce remote has been paired. will clear remote settings for remoteId
 *
 * @param        remoteId the simple ID of the desired remote
 *
 * @return       UAPI_SUCCESS
 *          */
uapi_status_t UAPI_AnnouncePairedRemote(UAPI_RemoteID_t remoteId);
/**
 * @brief        announce remote has been unpaired. will clear remote settings for remoteId
 *
 * @param        remoteId the simple ID of the desired remote
 *
 * @return       UAPI_SUCCESS
 */
uapi_status_t UAPI_AnnounceUnpairedRemote(UAPI_RemoteID_t remoteId);

/**
 * @brief        Raw Sensor Calibration request. Used to gather calibration data from remote control
 *               if using raw sensor data callbacks directly. not needed if using integrated MotionEngine
 *
 * @param        remoteId the simple ID of the desired remote
 *
 * @return       UAPI_SUCCESS
 */
uapi_status_t UAPI_RawSensorCalibrationRequest( UAPI_RemoteID_t remoteId );

/**
 * @brief        Sets the Debug level for UAPI Library
 *
 * @param      dLevel -- Debug Level( 1 - Error Messages, 2- Informatory Messages, 3- Verbose)
 *
 * @return       None
 **/

void UAPI_SetDebugLevel(int dLevel);

/**
 * @brief        Queues Remote Finder request
 *
 * @param        remoteId simple pairing reference of remote control to communicate request to
 * @param        finderCondition -termination condition for finder
 * @param        timeOut - timeout if termination condition contains timeout
 *
 * @return       uapi_success if request queued successfully
 **/
uapi_status_t UAPI_StartRemoteFinder ( INT8 remoteId, UINT8 finderCondition, UINT16 timeOut );

/**
 * @brief        LED Feedback Message
 *
 * @param        remoteId simple pairing reference of remote control to communicate upgrade information to.
 * @param        LED color
 * @param        duty cycle
 * @param        period
 * @param        Finder Condition
 * @param        Timeout Value -- incase of timer condition as timeout
 *
 * @return       uapi_success if request and processing of file data is successful.
 **/
uapi_status_t UAPI_LEDFeedback( INT8 remoteId,
		UINT8 color, UINT8 dutycycle, UINT16 period,
		UINT8 finderCondition, UINT16 timeout );

/**
 * @brief        Finder Feedback Message
 *
 * @param        remoteId simple pairing reference of remote control to communicate upgrade information to.
 * @param        Finder Condition
 * @param        Timeout Value -- incase of timer condition as timeout
 *
 * @return       uapi_success if request and processing of file data is successful.
 **/
uapi_status_t UAPI_FinderFeedback( INT8 remoteId, UINT8 finderCondition, UINT16 timeout );

/**
 * @brief        Sends a request to RCU to cancel the Feedback
 *
 * @param        remoteId simple pairing reference of remote control .
 *
 * @return       uapi_success if request is queued successfully
 */
uapi_status_t UAPI_CancelFeedback( INT8 remoteId);

/**
 * @brief        Sends an RAPI Get record packet to RCU
 *
 * @param        remoteId simple pairing reference of remote control .
 * @param	   searchFlg -- FDRA Search Flag
 * @param	   recType -- FDRA Record Type
 * @param	  recFlag    -- FDRA Record Flag
 * @param	   modeKey -- Mode Key
 * @param	   regKey -- Regular Key
 * @return        uapi_success if request is sent successfully
 */
uapi_status_t UAPI_RAPIGetRecord( UAPI_RemoteID_t remoteId, UINT8 searchFlg, UINT8 recType, UINT8 recFlag, UINT8 modeKey, UINT8 regKey );
/**
 * @brief        Sends an RAPI Set record packet to RCU
 *
 * @param        remoteId simple pairing reference of remote control .
 * @param	   pUserRecord -- FDRA Record
 * @param	  dataLen  -- Record Length
 * @return        uapi_success if request is sent successfully
 */
uapi_status_t UAPI_RAPISetRecord(UAPI_RemoteID_t remoteId, UINT8 * pUserRecord, UINT16 dataLen);
/**
 * @brief	This function sends Remove record message to Remote
 *
 * @param	remoteId	-- Remote ID.
 * @param	searchFlg	-- Search flag.
 * @param	nextRecord	-- Offset to next record.
 * @param	recType		-- Record Type.
 * @param	recFlag		-- Record  Flag.
 * @param	modeKey		-- Mode Key.
 * @param	regularKey	-- Regular Key.
 *
 * @return	A UAPI success or error code.
*********************************************************************/
uapi_status_t UAPI_RAPIRemoveRecord(UAPI_RemoteID_t remoteId, UINT8 searchFlg, UINT16 nextRecord, UINT8 recType,
									UINT8 recFlag, UINT8 modeKey, UINT8 regularKey);
/**
 * @brief        Sends an RAPI Test Device Code packet to RCU
 *
 * @param        remoteId simple pairing reference of remote control .
 * @param	   devType -- Device Type
 * @param	  devCode  -- Device Code
 * @return        uapi_success if request is sent successfully
 */
uapi_status_t UAPI_RAPITestDeviceCode(UAPI_RemoteID_t remoteId, UINT8 devType, UINT16 devCode);
/**
 * @brief        Removes an upgraded image from RCU
 *
 * @param        remoteId simple pairing reference of remote control .
 * @param	   devType -- Device Type
 * @param	  devCode  -- Device Code
 * @return        uapi_success if request is sent successfully
 */
uapi_status_t UAPI_RAPIRemoveUpgrade(UAPI_RemoteID_t remoteId, UINT8 devType, UINT16 devCode);
/**
 * @brief        Sends a message to list all the upgraded code sets
 *
 * @param        remoteId simple pairing reference of remote control .
 * @param	   devType -- Device Type
 * @return        uapi_success if request is sent successfully
 */

uapi_status_t UAPI_RAPIListUpgrade(UAPI_RemoteID_t remoteId, UINT8 devType);

uapi_status_t UAPI_RAPISendCmdData( UAPI_RemoteID_t remoteId, UINT8 cmdCode, UINT8 *pData, UINT16 len);

/**
 * @brief        	This routine decodes the compressed audio data
 *
 * @param    	adpcmData -- Encoded data
 * @param    	adpcmDataSize -- Encoded data size
 * @param    	pcmData -- Decoded data
 * @param    	pcmDataSize -- Decoded data size
 *
 * @return    	None
 */
void UAPI_DecodeAudio(UAPI_RemoteID_t remoteId, UINT8* adpcmData, short* pcmData, int adpcmDataSize);

/**
 * @brief        Sends a message to Confirm StartAudio
 *
 * @param        remoteId -- simple pairing reference of remote control .
 * @param	  confirmStartAudio -- Confirm Audio Payload
 * @return        uapi_success if request is sent successfully
 */

uapi_status_t UAPI_ConfirmStartAudio(UAPI_RemoteID_t remoteId, UAPI_StartAudioPayload_t *confirmStartAudio);
/**
 * @brief        Sends a message to  Request Audio
 *
 * @param        remoteId -- simple pairing reference of remote control .
 * @param	  requestAudio -- Request Audio Payload
 * @return        uapi_success if request is sent successfully
 */

uapi_status_t UAPI_RequestStartAudio(UAPI_RemoteID_t remoteId, UAPI_StartAudioPayload_t *requestAudio);
/**
 * @brief        Sends a message to Request Stop Audio
 *
 * @param        remoteId -- simple pairing reference of remote control .
 * @return        uapi_success if request is sent successfully
 */

uapi_status_t UAPI_RequestStopAudio(UAPI_RemoteID_t remoteId);
/**
 * @brief        Sends a message to query audio support capabilities of remote
 *
 * @param        remoteId -- simple pairing reference of remote control .
 * @return        uapi_success if request is sent successfully
 */

uapi_status_t UAPI_QueryAudioSupport(UAPI_RemoteID_t remoteId);

/**
 * @brief        Sets the cursor bounds for the screen resolution requested by user
 *
 * @param
 *
 * @return       None
 */
void UAPI_RawSensorSetCursorBounds (int osd_x, int osd_y, int osd_height, int osd_width, int limit_x, int limit_y, int limit_height, int limit_width);

/**
 * @brief        Sets the cursor type as absolute or relative
 *
 * @param      cursorType -- Raw sensor cursor type
 *
 * @return       None
 */
void UAPI_RawSensorSetCursorType(int cursorType);

/**
 * @brief Sets the FME calibration storage path
 *
 * @param filePathToSave -- FME Storage file path
 *
 * @return None
 */
void UAPI_RawSensorSetPath( const char* filePathToSave);

uapi_status_t UAPI_TestMode_SetDescriptor( UAPI_RemoteID_t remoteId, UINT8 *pPayload, int len);
uapi_status_t UAPI_TestMode_RequestStart( UAPI_RemoteID_t remoteId, UAPI_TestMode_Start_t *pPayload);
uapi_status_t UAPI_TestMode_RequestStop( UAPI_RemoteID_t remoteId);
uapi_status_t UAPI_TestMode_SetParamRqst(UAPI_RemoteID_t remoteId, UINT8 *pPayload, int len);
uapi_status_t UAPI_TestMode_GetParamRqst(UAPI_RemoteID_t remoteId, UINT8 *pPayload, int len);
uapi_status_t UAPI_TestMode_ClearDescriptor(UAPI_RemoteID_t remoteId);

uapi_status_t UAPI_SendRawData(UAPI_RemoteID_t remoteId,
				UINT8 opt, UINT8 appId, UINT8 opCode, UINT32 dataLen, UINT8 *pPayload);

uapi_status_t UAPI_set_remote_attr(UAPI_RemoteID_t rid, UAPI_nif_attr_id_t attr, void *pVal);
uapi_status_t UAPI_get_remote_attr(UAPI_RemoteID_t rid, UAPI_nif_attr_id_t attr, void *pVal);


#ifdef      UAPI_ENABLE_BRCM_MSBC

void UAPI_MSBCDecStart(UAPI_RemoteID_t remoteId);
void UAPI_MSBCDecStop(UAPI_RemoteID_t remoteId);
void UAPI_MSBCDecode(UAPI_RemoteID_t remoteId, const uint8_t *msbc_data, uint16_t msbc_data_size, uint8_t *pcm_data, uint16_t *pcm_buff_len);

#endif      /* UAPI_ENABLE_BRCM_MSBC */


#ifdef UAPI_ENABLE_OPUS
void UAPI_OpusDecStart(UAPI_RemoteID_t remoteId);
void UAPI_OpusDecStop(UAPI_RemoteID_t remoteId);
uapi_status_t UAPI_OpusDecode(UAPI_RemoteID_t remoteId, const UINT8 *opus_data, UINT16 opus_data_size,
							  UINT8 *pcm_data, INT32 *pcm_buff_len);
#endif // UAPI_ENABLE_OPUS


uapi_status_t UAPI_RfdbStartDataRequest(UAPI_RemoteID_t remoteId, UINT8 *pData, int len, UINT8 cmdId);
uapi_status_t UAPI_RfdbEndDataRequest(UAPI_RemoteID_t remoteId);
uapi_status_t UAPI_RfdbDataTransfer(UAPI_RemoteID_t remoteId, UINT8 *rfdbData, int rfdbDataLen);
uapi_status_t UAPI_RfdbSendCommand(UAPI_RemoteID_t remoteId, UINT8 cmdId);
uapi_status_t UAPI_RfdbSendStartDataAck(UAPI_RemoteID_t remoteId, UINT8 *pData, int len);

uapi_status_t UAPI_QuickSetSendStartSession(UAPI_RemoteID_t remoteId);
uapi_status_t UAPI_QuickSetSendEndSession(UAPI_RemoteID_t remoteId);
uapi_status_t UAPI_QuickSetListAllRecords(UAPI_RemoteID_t remoteId);
uapi_status_t UAPI_QuickSetWriteRecord(UAPI_RemoteID_t remoteId, UINT8 *quickSetData, int quickSetDataLen);
uapi_status_t UAPI_QuickSetDeleteRecord(UAPI_RemoteID_t remoteId, UINT8 *quickSetData, int quickSetDataLen);
uapi_status_t UAPI_QuickSetReadRecord(UAPI_RemoteID_t remoteId, UINT8 *quickSetData, int quickSetDataLen);

uapi_status_t UAPI_QuickSetStartDiscovery( UAPI_RemoteID_t remoteId, UINT8 *pData, int len);
uapi_status_t UAPI_QuickSetStopDiscovery( UAPI_RemoteID_t remoteId);
uapi_status_t UAPI_QuickSetSetConfig( UAPI_RemoteID_t remoteId, UINT8 *pData, int len);
uapi_status_t UAPI_QuickSetGetRemoteStatus(UAPI_RemoteID_t remoteId);
uapi_status_t UAPI_QuickSetSendKeyCommand( UAPI_RemoteID_t remoteId, UINT8 *pData, int len);
UINT8 UAPI_GetAudioCompression(UAPI_RemoteID_t remoteId);
uapi_status_t UAPI_qs_writeRecord2NVM(UAPI_RemoteID_t remoteId, UINT16 recId, UINT8 *pData, INT32 dataLen);
uapi_status_t UAPI_qs_writeRecord2RAM(UAPI_RemoteID_t remoteId, UINT16 recId, UINT8 *pData, INT32 dataLen);


UINT8 UAPI_GetAudioCompression(UAPI_RemoteID_t remoteId);

void UAPI_MSBCDecStart(UAPI_RemoteID_t remoteId);
void UAPI_MSBCDecStop(UAPI_RemoteID_t remoteId);
void UAPI_MSBCDecode(UAPI_RemoteID_t remoteId, const UINT8 *msbc_data, UINT16 msbc_data_size, UINT8 *pcm_data,
					 UINT16 *pcm_buff_len);

/** Function Name Aliases. The Alias names will be removed in future **/
#define UAPIDeMultiplexer 					UAPI_DeMultiplexer
#define UAPI_createParamStruct				UAPI_CreateParamStruct
#define UAPI_destroyParamStruct				UAPI_DestroyParamStruct
#define UAPI_setParam						UAPI_SetParam
#define UAPI_getParam						UAPI_GetParam
#define UAPIRegisterCallback 				UAPI_RegisterCallback
#define UAPIConfigureFeature 				UAPI_ConfigureFeature
#define UAPIGetInfo 						UAPI_GetInfo
#define UAPIMsgPendingAnnounce 				UAPI_MsgPendingAnnounce
#define UAPIGetVersion 						UAPI_GetVersion
#define UAPIUpgradeRemote 					UAPI_UpgradeRemote
#define UAPI_Storage_GetFreeSpace 			UAPI_StorageGetFreeSpace
#define UAPI_Storage_GetTotalSize 			UAPI_StorageGetTotalSize
#define UAPI_Storage_ReadData 				UAPI_StorageReadData
#define UAPI_Storage_Get_BAT_List 			UAPI_StorageGetBATList
#define UAPI_Storage_Delete_BAT_Entry 		UAPI_StorageDeleteBATEntry
#define UAPI_Storage_Defrag 				UAPI_StorageDefrag
#define UAPI_Storage_WriteData 				UAPI_StorageWriteData
#define UAPIGetRemoteFeatures 				UAPI_GetRemoteFeatures
#define UAPIBatteryStatusRequest 			UAPI_BatteryStatusRequest
#define UAPIQSSendToRemote 					UAPI_SendRAPIMsgToRemote
#define UAPIRawSensorCalibrationRequest 	UAPI_RawSensorCalibrationRequest
#define UAPIStartRemoteFinder 				UAPI_StartRemoteFinder
#define UAPILEDFeedback 					UAPI_LEDFeedback
#define UAPIFinderFeedback 					UAPI_FinderFeedback
#define UAPICancelFeedback 					UAPI_CancelFeedback
#define UAPIDecodeAudio						UAPI_DecodeAudio
#define UAPIConfirmStartAudio				UAPI_ConfirmStartAudio
#define UAPIRequestStartAudio				UAPI_RequestStartAudio
#define UAPIRequestStopAudio				UAPI_RequestStopAudio
#define UAPIQueryAudioSupport				UAPI_QueryAudioSupport
#define UAPI_FMESetPath 					UAPI_RawSensorSetPath
#define UAPI_FMEsetCursorBounds 			UAPI_RawSensorSetCursorBounds

#define UAPI_HIGHRES_ABSOLUTEPOSITION_NAME	UAPI_HIGHRESABSOLUTEPOSITION_NAME


uapi_status_t UAPI_SetRemoteConfigData(UAPI_RemoteID_t remoteId, UAPIFeatureID_t appId, UINT8 attrId, UINT8 len, void *pData);
uapi_status_t UAPI_GetRxedConfigData(UAPI_RemoteID_t remoteId, UAPIFeatureID_t appId, UINT8 attrId, void *pData);


#ifdef __cplusplus
}
#endif

#endif /* __UAPI_H__ */
