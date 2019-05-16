package uapiwrapper;

import android.content.res.AssetManager;
import android.util.Log;

/**
 * Created by UEI on 8/1/17.
 */

public class UEISDK {

    static {
        System.loadLibrary("uapi-wrapper");
    }

    private static UEISDK _instance;

    public static UEISDK manager() {
        if (_instance == null) {
            _instance = new UEISDK();
        }
        return _instance;
    }

    private OTACallback registeredCallback;
    private UAPICallback sendUAPI;

    private native String getUpgradeState(int remoteId);

    private native String registerOTACallback();

    private native String upgradeRemote(int remoteId, String filePath, String productName);

    //UAPI Library methods exposed
    public native void initAPI();

    public native void stopAPI();

    public native void registerRemote(int remoteId);

    public native void handleUAPIData(int remoteId, int size, byte[] data);

    public native String getOTAFileVersion(String filePath);

    public OTAUpgradeStatus getUpgradeStatus(int remoteId) {
        String status = getUpgradeState(remoteId);
        return OTAUpgradeStatus.valueOf(status);
    }

    public UAPIStatus startOTAUpgrade(int remoteId, String filePath, String productName) {
        String result = upgradeRemote(remoteId, filePath, productName);
        return UAPIStatus.valueOf(result);
    }

    public UAPIStatus registerOTACallback(OTACallback callback) {
        String uapiResult = registerOTACallback();
        UAPIStatus result = UAPIStatus.valueOf(uapiResult);
        if (result == UAPIStatus.SUCCESS) {
            registeredCallback = callback;
        }
        return result;
    }

    public void registerUAPICallback(UAPICallback callback) {
        sendUAPI = callback;
    }

    private void uapiOTACallback(int remoteId, String otaStatus, int currentByte, int totalBytes) {
        if (registeredCallback != null) {
            OTATransferStatus status = new OTATransferStatus(otaStatus, currentByte, totalBytes);
            OTAData data = new OTAData(remoteId, status);
            registeredCallback.otaCallback(data);
        }
    }

    private void sendUAPIMessage(int remoteId, int size, byte[] data) {
        if (sendUAPI != null) {
            sendUAPI.uapiCallback(remoteId, data);
        }
    }
}
