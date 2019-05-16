//
// Created by Camila Moscatelli on 7/31/17.
//

/* C Version */
#include <string.h>
#include <jni.h>
#include "include/crc.h"
#include "include/uapi.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//Global vars needed for callbacks
static JavaVM *jvm;
jobject g_sendUAPIObject;
jobject g_registerCallbackObject;
pthread_key_t current_jni_env;

// Constants and macros
#define INTELFORMAT_MAX_LINE 300
#define INTELHEX_RECORDTYPE_BYTE_INDEX 8
#define INTELHEX_RECORDTYPE_DATA '0'

//Structures
typedef struct {
    UAPI_OTADownloadStatus_t status;
    /** Bytes transferred so far */
    int currentByte;
    /** File size in bytes */
    int totalBytes;
    /** New Product Version if upgrade is completed */
    char* prodVersion;
} otaTransferStatus;

typedef struct {
    unsigned char remoteId;
    /** the data from the remote control */
    otaTransferStatus remoteData;
} otaData;

//Parse UAPI response methods
jstring parseOTAState(JNIEnv *env, UAPI_OTADownloadStatus_t state) {
    switch (state) {
        case OTA_UPGRADE_NONE:
            return  (*env)->NewStringUTF(env, "NONE");
        case OTA_UPGRADE_STARTED:
            return  (*env)->NewStringUTF(env, "STARTED");
        case OTA_UPGRADE_IN_PROGRESS:
            return  (*env)->NewStringUTF(env, "INPROGRESS");
        case OTA_UPGRADE_COMPLETE:
            return  (*env)->NewStringUTF(env, "COMPLETED");
        case OTA_UPGRADE_FAILED:
            return  (*env)->NewStringUTF(env, "FAILED");
        case OTA_UPGRADE_FAILED_LOW_BATTERY:
            return  (*env)->NewStringUTF(env, "FAILEDLOWBATTERY");
        case OTA_UPGRADE_CANCELLED:
            return  (*env)->NewStringUTF(env, "CANCELLED");
        case OTA_UPGRADE_TIMEDOUT:
            return  (*env)->NewStringUTF(env, "TIMEDOUT");
        default:
            return  (*env)->NewStringUTF(env, "FORCED");
    }
}

jstring parseUAPIStatus(JNIEnv *env, uapi_status_t state) {
    switch (state) {
        case UAPI_SUCCESS:
            return  (*env)->NewStringUTF(env, "SUCCESS");
        case UAPI_OTA_IN_PROGRESS:
            return  (*env)->NewStringUTF(env, "INPROGRESS");
        case UAPI_OTA_FILE_EXISTS:
            return  (*env)->NewStringUTF(env, "FILEEXISTS");
        default:
            return  (*env)->NewStringUTF(env, "FAILURE");
    }
}

static void detach_current_thread (void *env) {
    (*jvm)->DetachCurrentThread (jvm);
}

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv* env = NULL;
    jvm = vm;
    if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        return 0;
    }

    pthread_key_create(&current_jni_env, detach_current_thread);

    return JNI_VERSION_1_4;
}

static JNIEnv* get_jni_env() {
    JNIEnv* env = pthread_getspecific(current_jni_env);
    if (env == NULL) {
        (*jvm)->AttachCurrentThread(jvm, &env, NULL);
        pthread_setspecific(current_jni_env, env);
    }

    return env;
}

//Internal methods for handling UAPI lib response
otaData convertOtaData(void* data) {
    otaData dataToReturn;
    UAPIFeatureData_t* feature = (UAPIFeatureData_t *) data;
    dataToReturn.remoteId = feature->remoteId;

    UAPI_OTAStatus_t* otaDataReceived = (UAPI_OTAStatus_t *) feature->featureData;
    otaTransferStatus otaStatus;
    otaStatus.status = otaDataReceived->status;

    otaStatus.currentByte = otaDataReceived->current_byte;
    otaStatus.totalBytes = otaDataReceived->total_bytes;

    dataToReturn.remoteData = otaStatus;

    return dataToReturn;
}

static void callbackOTA(void* data) {
    JNIEnv* g_registerCallbackEnv = get_jni_env();
    if (g_registerCallbackEnv != NULL && g_registerCallbackObject != NULL) {
        otaData callbackData = convertOtaData(data);

        jstring otaStatus = parseOTAState(g_registerCallbackEnv, callbackData.remoteData.status);

        //Call UEISDK registered callback
        jclass objectClass = (*g_registerCallbackEnv)->GetObjectClass(g_registerCallbackEnv, g_registerCallbackObject);
        jmethodID registerCallbackMethod = (*g_registerCallbackEnv)->GetMethodID(g_registerCallbackEnv, objectClass, "uapiOTACallback", "(ILjava/lang/String;II)V");
        if (registerCallbackMethod == NULL) return;
        (*g_registerCallbackEnv)->CallVoidMethod(g_registerCallbackEnv, g_registerCallbackObject, registerCallbackMethod,
                                                 callbackData.remoteId, otaStatus, callbackData.remoteData.currentByte, callbackData.remoteData.totalBytes);

        (*g_registerCallbackEnv)->DeleteLocalRef(g_registerCallbackEnv, otaStatus);
    }
}

static INT16 sendUAPIData(UAPIDataPkt* pkt) {
    JNIEnv* g_sendUAPIEnv = get_jni_env();
    if (g_sendUAPIEnv != NULL) {
        UINT8 data[1024];
        int size;
        int hdrLen = sizeof(UAPIHdr_t);

        memcpy(data, &(pkt->uapiHdr), hdrLen);
        memcpy(data+hdrLen, pkt->data, pkt->dataLength);
        size = pkt->dataLength + hdrLen;

        jbyteArray bytesArrayData = (*g_sendUAPIEnv)->NewByteArray(g_sendUAPIEnv, size);
        (*g_sendUAPIEnv)->SetByteArrayRegion(g_sendUAPIEnv, bytesArrayData, 0, size, (jbyte*) (data));

        //Call UEISDK sendUAPI
        jclass objectClass = (*g_sendUAPIEnv)->GetObjectClass(g_sendUAPIEnv, g_sendUAPIObject);
        jmethodID sendUAPI = (*g_sendUAPIEnv)->GetMethodID(g_sendUAPIEnv, objectClass, "sendUAPIMessage", "(II[B)V");
        if (sendUAPI == NULL) return UAPI_FAILURE;
        (*g_sendUAPIEnv)->CallVoidMethod(g_sendUAPIEnv, g_sendUAPIObject, sendUAPI,
                                                 pkt->remoteId, size, bytesArrayData);

        (*g_sendUAPIEnv)->DeleteLocalRef(g_sendUAPIEnv, bytesArrayData);
    }

    return UAPI_SUCCESS;
}

UAPI_OTAUpdateParams_t* getOTAParams(char* filePath, char* productName, int forcedUpgrade) {
    FILE* fp;
    int num_bytes = 0;
    unsigned int address = 0;
    unsigned int type = 0;
    char data[INTELFORMAT_MAX_LINE];
    char line[INTELFORMAT_MAX_LINE];
    char* ptr;
    unsigned char d[32];
    int i;

    fp = fopen(filePath, "rb");

    if(NULL == fp) {
        printf("Can't open OTA file: %s\n", filePath);
        return NULL;
    }

    fgets(line, INTELFORMAT_MAX_LINE, fp);
    if (line[INTELHEX_RECORDTYPE_BYTE_INDEX] != INTELHEX_RECORDTYPE_DATA) {
        fgets(line, INTELFORMAT_MAX_LINE, fp);
    }

    if(line[0] == ':') {
        sscanf(line, ":%2x%4x%2x%s", (unsigned int*)&num_bytes, &address, &type, data);
    }
    fclose(fp);

    //decode line into params
    ptr = data;
    memset (d, 0, sizeof(d));
    for (i = 0; i < num_bytes; i++) {
        sscanf(ptr, "%2x", (UINT32*) &d[i]);
        ptr += 2;
    }

    UAPI_OTAUpdateParams_t* otaParams = malloc(sizeof(UAPI_OTAUpdateParams_t));
    otaParams->flags = d[0];
    otaParams->type = d[1];
    if (!forcedUpgrade) {
        otaParams->flags |= 0x40;
    } else {
        otaParams->flags &= 0xBF;
    }

    otaParams->majorVersionNum = d[4];
    otaParams->minorVersionNum = d[5];
    otaParams->swReleaseNum = d[6] + (d[7]<<8);
    otaParams->hexFileSz = d[8] + (d[9]<<8) + (d[10]<<16) + (d[11]<<24);
    otaParams->CRC = d[12] + (d[13]<<8);
    otaParams->hwRev = 0;
    strncpy((char*)otaParams->productName, (const char*) productName, UAPI_PRODUCT_NAME_SIZE);
    strncpy((char*)otaParams->hexFileName, (const char*) filePath, 256);

    return otaParams;
}

void UIF_intf_RxedUAPIDataHandler(UINT8 rid, UINT8* pData, UINT8 length) {
    UAPIDataPkt s_rxedUapiPkt;
    UINT8 s_rxedData[1024];

    s_rxedUapiPkt.remoteId = rid;
    s_rxedUapiPkt.dataLength = length - sizeof(UAPIHdr_t);
    s_rxedUapiPkt.uapiHdr.UAPIOptions = pData[0];
    s_rxedUapiPkt.uapiHdr.seqNum = pData[1];
    s_rxedUapiPkt.uapiHdr.appID = pData[2];
    s_rxedUapiPkt.uapiHdr.opCode = pData[3];

    memcpy(s_rxedData, pData + sizeof(UAPIHdr_t), s_rxedUapiPkt.dataLength);
    s_rxedUapiPkt.data = s_rxedData;

    UAPI_DeMultiplexer(&s_rxedUapiPkt);
}

//UAPI Library methods for OTA
void Java_uapiwrapper_UEISDK_initAPI(JNIEnv *env, jobject obj) {
    UAPI_Init();
}

void Java_uapiwrapper_UEISDK_stopAPI(JNIEnv *env, jobject obj) {
    UAPI_Stop();
}

jstring Java_uapiwrapper_UEISDK_getUpgradeState(JNIEnv *env, jobject obj, UINT8 remoteId) {
    UAPI_OTADownloadStatus_t state = UAPI_GetUpgradeState(remoteId);

    return parseOTAState(env, state);
}

jstring Java_uapiwrapper_UEISDK_registerOTACallback(JNIEnv *env, jobject obj) {
    uapi_status_t registerResult = UAPI_RegisterCallback(UAPI_OTA_NAME, callbackOTA);
    if (registerResult == UAPI_SUCCESS) {
        g_registerCallbackObject = (*env)->NewGlobalRef(env, obj);
    }

    return parseUAPIStatus(env, registerResult);
}

void Java_uapiwrapper_UEISDK_registerRemote(JNIEnv *env, jobject obj, UINT8 remoteId) {
    (*env)->GetJavaVM(env, &jvm);
    g_sendUAPIObject = (*env)->NewGlobalRef(env, obj);

    UAPI_nif_id_t nif = UAPI_BLE_NIF;
    unsigned char bypass = 1;
    UINT16 mtu = 19;

    UAPI_set_remote_attr(remoteId, UAPI_NIF_ATTR_ID, (void *)&nif);
    UAPI_set_remote_attr(remoteId, UAPI_NIF_ATTR_MTU, (void *)&mtu);
    UAPI_set_remote_attr(remoteId, UAPI_NIF_ATTR_BYPASSQUEUE, (void *)&bypass);
    UAPI_set_remote_attr(remoteId, UAPI_NIF_ATTR_SENDER, (void *)sendUAPIData);
}

void Java_uapiwrapper_UEISDK_handleUAPIData(JNIEnv *env, jobject obj, UINT8 remoteId, UINT8 size, jbyteArray data) {
    unsigned char* cData = (unsigned char*)(*env)->GetByteArrayElements(env, data, NULL);
    UIF_intf_RxedUAPIDataHandler(remoteId, cData, size);
    (*env)->ReleaseByteArrayElements(env, data, cData, JNI_ABORT);
}

jstring Java_uapiwrapper_UEISDK_upgradeRemote(JNIEnv *env, jobject obj, UINT8 remoteId, jstring filePath, jstring productName) {
    char* cFilePath = (char*)(*env)->GetStringUTFChars(env, filePath, 0);

    uapi_status_t status = UAPI_ota_SendUpdateImage(remoteId, cFilePath, 0);

    (*env)->ReleaseStringUTFChars(env, filePath, cFilePath);

    return parseUAPIStatus(env, status);
}

jstring Java_uapiwrapper_UEISDK_getOTAFileVersion(JNIEnv *env, jobject obj, jstring filePath) {
    UAPI_OTAUpdateParams_t *pInfo = malloc(sizeof(UAPI_OTAUpdateParams_t));
    char *cFilePath = (char *) (*env)->GetStringUTFChars(env, filePath, 0);

    uapi_status_t result = UAPI_ota_GetFileInfo(cFilePath, pInfo);
    jstring version = "";

    if (result == UAPI_SUCCESS) {
        char swVerStr[64];
        sprintf(swVerStr, "%x%02x",
                ((pInfo->swReleaseNum >>0)&0xFF),
                ((pInfo->swReleaseNum >>8)&0xFF));
        version = swVerStr;
    }

    (*env)->ReleaseStringUTFChars(env, filePath, cFilePath);

    return (*env)->NewStringUTF(env, version);
}