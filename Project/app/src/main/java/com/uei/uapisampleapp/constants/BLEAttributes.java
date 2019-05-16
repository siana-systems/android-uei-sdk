package com.uei.uapisampleapp.constants;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

/**
 * Created by UEI on 8/29/17.
 */

public class BLEAttributes {
    private static HashMap<String, String> writableCharacteristics = new HashMap();
    private static HashMap<String, String> readableCharacteristics = new HashMap();
    private static HashMap<String, String> services = new HashMap();

    // General
    public final static String ADVERTISED_SERVICE = "2141e110-213a-11e6-b67b-9e71128cae77";

    public final static String DEVICE_INFO_SERVICE = "0000180A-0000-1000-8000-00805F9B34FB";
    public final static String VERSION_INFO_CHARACTERISTIC = "00002A28-0000-1000-8000-00805F9B34FB";

    public final static String REVERSE_BYTE_ADVERTISED_SERVICE = "77ae8c12-719e-7bb6-e611-3a2110e14121";
    public final static String DESCRIPTOR_CONFIG_UUID = "00002902-0000-1000-8000-00805f9b34fb";

    // UCG
    public final static String UCG_IN = "2141e111-213a-11e6-b67b-9e71128cae77";
    public final static String UCG_OUT = "2141e112-213a-11e6-b67b-9e71128cae77";
    public final static String UCG_SERVICE_UUID = "2141e110-213a-11e6-b67b-9e71128cae77";

    // UUG
    public final static String UAPI_IN = "2141e101-213a-11e6-b67b-9e71128cae77";
    public final static String UAPI_OUT = "2141e102-213a-11e6-b67b-9e71128cae77";
    public final static String UAPI_SERVICE_UUID = "2141e100-213a-11e6-b67b-9e71128cae77";

    static {
        // Services
        services.put(UCG_SERVICE_UUID, "UCG Module Service");
        services.put(UAPI_SERVICE_UUID, "UUG Service");

        // Characteristics
        readableCharacteristics.put(UCG_IN, UCG_SERVICE_UUID);
        writableCharacteristics.put(UCG_OUT, UCG_SERVICE_UUID);
        readableCharacteristics.put(UAPI_IN, UAPI_SERVICE_UUID);
        writableCharacteristics.put(UAPI_OUT, UAPI_SERVICE_UUID);
    }

    public static Boolean isReadableCharacteristic(String uuid) {
        return readableCharacteristics.containsKey(uuid);
    }

    public static Boolean isWritableCharacteristic(String uuid) {
        return writableCharacteristics.containsKey(uuid);
    }

    public static List<String> getReadableCharacteristics() {
        List<String> uuids = new ArrayList<String>(readableCharacteristics.keySet());
        return uuids;
    }

    public static String getServicesForCharacteristic(String uuid) {
        if (readableCharacteristics.containsKey(uuid)) {
            return readableCharacteristics.get(uuid);
        } else {
            return writableCharacteristics.get(uuid);
        }
    }
}
