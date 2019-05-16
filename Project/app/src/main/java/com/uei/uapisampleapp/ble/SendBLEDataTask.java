package com.uei.uapisampleapp.ble;

import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattService;
import android.os.AsyncTask;
import android.util.Log;

import java.util.Arrays;
import java.util.UUID;

/**
 * Created by UEI on 9/13/17.
 */

public class SendBLEDataTask extends AsyncTask<Void, Void, Boolean> {
    public BluetoothGattCharacteristic mCharacteristic;
    public BluetoothGatt mBluetoothGatt;
    public DataTask dataTask;
    public BLECallback callerCallback;

    public interface BLECallback {
        void onSendCompleted(Boolean success, byte[] data);
    }

    public SendBLEDataTask(BLECallback activityCallback, BluetoothGatt gatt, DataTask dataToSend, BluetoothGattCharacteristic characteristic) {
        mBluetoothGatt = gatt;
        dataTask = dataToSend;
        mCharacteristic = characteristic;
        callerCallback = activityCallback;
    }

    private Boolean send(DataTask dataTask, BluetoothGattCharacteristic characteristic) {
        characteristic.setValue(dataTask.getData());
        characteristic.setWriteType(BluetoothGattCharacteristic.WRITE_TYPE_NO_RESPONSE);
        return mBluetoothGatt.writeCharacteristic(characteristic);
    }

    @Override
    protected Boolean doInBackground(Void... params) {
        return send(dataTask, mCharacteristic);
    }

    @Override
    protected void onCancelled(Boolean result) {
        Log.d("Send Task ", "Cancelled");
        callerCallback.onSendCompleted(result, dataTask.getData());
    }
}
