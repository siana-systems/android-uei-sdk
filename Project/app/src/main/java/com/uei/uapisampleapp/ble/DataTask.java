package com.uei.uapisampleapp.ble;

import android.bluetooth.BluetoothGattCharacteristic;

/**
 * Created by UEI on 10/16/17.
 */

public class DataTask {
    private byte[] data;
    private boolean lastSlice = false;

    public DataTask(byte[] data, boolean lastSlice) {
        this.data = data;
        this.lastSlice = lastSlice;
    }

    public Boolean isLastSlice() {
        return lastSlice;
    }

    public byte[] getData() {
        return data;
    }
}
