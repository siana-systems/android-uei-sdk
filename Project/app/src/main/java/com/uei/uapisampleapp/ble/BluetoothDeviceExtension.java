package com.uei.uapisampleapp.ble;

import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;

/**
 * Created by UEI on 1/16/18.
 */

public class BluetoothDeviceExtension {
    public String swVersion = "";
    public BluetoothGatt mBluetoothGatt;
    public BluetoothDevice scanResult;

    public BluetoothDeviceExtension(BluetoothGatt mBluetoothGatt) {
        this.mBluetoothGatt = mBluetoothGatt;
    }

    public BluetoothDeviceExtension(BluetoothDevice scanResult) {
        this.scanResult = scanResult;
    }

    public BluetoothDevice getInnerDevice() {
        return mBluetoothGatt != null ? mBluetoothGatt.getDevice() : null;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == null)
            return false;

        if (!BluetoothDeviceExtension.class.isAssignableFrom(obj.getClass()))
            return false;

        final BluetoothDeviceExtension other = (BluetoothDeviceExtension) obj;
        BluetoothDevice thisDevice = this.getInnerDevice();
        BluetoothDevice otherDevice = other.getInnerDevice();

        if (thisDevice != null && otherDevice != null)
            return thisDevice.getAddress().equals(otherDevice.getAddress());

        return this.scanResult.getAddress().equals(other.scanResult.getAddress());
    }
}
