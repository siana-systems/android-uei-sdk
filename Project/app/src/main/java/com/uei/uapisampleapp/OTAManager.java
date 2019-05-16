package com.uei.uapisampleapp;

import android.content.Context;
import android.content.res.AssetManager;
import android.util.Log;

import com.uei.uapisampleapp.constants.UEIRemote;
import com.uei.uapisampleapp.constants.VersionControl;
import com.uei.uapisampleapp.helpers.HexHelper;
import com.uei.uapisampleapp.helpers.UAPIApplication;
import com.uei.uapisampleapp.notifications.NotificationCenter;
import com.uei.uapisampleapp.notifications.NotificationType;

import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.util.HashMap;

import uapiwrapper.OTACallback;
import uapiwrapper.OTAData;
import uapiwrapper.OTAUpgradeStatus;
import uapiwrapper.UEISDK;

/**
 * Created by UEI on 9/26/17.
 */

public class OTAManager {
    //General OTA properties
    private static final OTAManager _instance = new OTAManager();
    private OTAUpgradeStatus upgradeStatus = OTAUpgradeStatus.NONE;
    private OTAData otaData;
    private String deviceToUpgrade = "";

    //Used for logging times
    private long timeBetweenMessages;
    private long totalTime;
    private long totalMessages;

    public static OTAManager shared() {
        return _instance;
    }

    public void registerOTACallback() {
        UEISDK.manager().registerOTACallback(new OTACallback() {
            @Override
            public void otaCallback(OTAData data) {
                upgradeStatus = data.remoteData.status;
                otaData = data;
                broadcastUpdate(upgradeStatus.name());
            }
        });
    }

    //OTA upgrade
    public OTAUpgradeStatus getUpgradeStatus() {
        return UEISDK.manager().getUpgradeStatus(UEIRemote.defaultId);
    }

    public int getUpgradeProgress() {
        if (otaData != null)
            return otaData.remoteData.currentByte;

        return 0;
    }

    public int getTotalOTAFileSize() {
        if (otaData != null)
            return otaData.remoteData.totalBytes;

        return 0;
    }

    public void registerDeviceForOTA(String deviceAddress) {
        deviceToUpgrade = deviceAddress;
    }

    public void cleanOTAStatus() {
        upgradeStatus = OTAUpgradeStatus.NONE;
    }

    public String getDeviceForOTA() {
        return deviceToUpgrade;
    }

    public boolean saveFileForUAPI(Context context, String sourceFileName, String destFileName) {
        clearUAPIFiles(context);
        AssetManager assetManager = context.getAssets();

        try {
            InputStream is = assetManager.open(sourceFileName);
            FileOutputStream fos = context.openFileOutput(destFileName, Context.MODE_PRIVATE);

            int size = is.available();
            int bytes_read;
            byte[] buffer = new byte[size];
            while ((bytes_read = is.read(buffer)) != -1)
                fos.write(buffer, 0, bytes_read);

            is.close();
            fos.flush();
            fos.close();

            return true;
        }
        catch (Exception e) {
            e.printStackTrace();
        }

        return false;
    }

    private void clearUAPIFiles(Context context) {
        File[] files = context.getFilesDir().listFiles();
        if (files != null)
            for (File file: files)
                file.delete();
    }

    private void broadcastUpdate(String status) {
        HashMap<String,String> params = new HashMap<String, String>();
        params.put("Status", status);
        NotificationCenter.postNotification(UAPIApplication.getContext(), NotificationType.OTA_STATUS_CHANGED, params);
    }

    //OTA version control
    private VersionControl compare(String fileVersion, String remoteVersion) {
        if (fileVersion.isEmpty() || remoteVersion.isEmpty())
            return VersionControl.NONE;

        Integer fileVer = Integer.parseInt(fileVersion);
        Integer remoteVer = Integer.parseInt(remoteVersion);

        return fileVer > remoteVer ? VersionControl.HIGHER : VersionControl.LOWER_EQUAL;
    }

    private String checkOTAFileVersion(String fileName) {
        return UEISDK.manager().getOTAFileVersion(fileName);
    }

    public VersionControl controlVersion(String file, String remoteVersion) {
        String fVersion = checkOTAFileVersion(file);
        String[] rVersionParts = remoteVersion.split("\\.");
        String rVersion = rVersionParts.length > 2 ? rVersionParts[1] + rVersionParts[2] : "";
        return compare(fVersion, rVersion);
    }

    //In case OTA times need to be logged
    public void logOTATime(String msg) {
        long currentTime = System.currentTimeMillis();
        long inBetweenTime = currentTime - timeBetweenMessages;
        totalTime = totalTime + inBetweenTime;
        totalMessages =+ 1;

        if (timeBetweenMessages != 0)
            Log.w(msg, String.valueOf(inBetweenTime));

        timeBetweenMessages = currentTime;
    }
}
