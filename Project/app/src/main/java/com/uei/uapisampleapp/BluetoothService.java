package com.uei.uapisampleapp;

import android.app.Service;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCallback;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattDescriptor;
import android.bluetooth.BluetoothGattService;
import android.bluetooth.BluetoothManager;
import android.bluetooth.BluetoothProfile;
import android.content.Context;
import android.content.Intent;
import android.os.Binder;
import android.os.IBinder;
import android.os.Looper;
import android.os.ParcelUuid;
import android.util.Log;

import com.uei.uapisampleapp.ble.BluetoothDeviceExtension;
import com.uei.uapisampleapp.ble.DataTask;
import com.uei.uapisampleapp.ble.DeviceConnectionState;
import com.uei.uapisampleapp.ble.SendBLEDataTask;
import com.uei.uapisampleapp.constants.BLEAttributes;
import com.uei.uapisampleapp.helpers.HexHelper;

import java.io.UnsupportedEncodingException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Queue;
import java.util.Set;
import java.util.UUID;
import java.util.concurrent.LinkedBlockingQueue;

import android.os.Handler;

import static android.bluetooth.BluetoothDevice.BOND_BONDED;
import static android.bluetooth.BluetoothDevice.BOND_NONE;
import static android.bluetooth.BluetoothGattCharacteristic.PROPERTY_INDICATE;

/**
 * Created by UEI on 8/29/17.
 * Service for managing connection and data communication with a given BLE device.
 */
public class BluetoothService extends Service {
    private final static String TAG = BluetoothService.class.getSimpleName();

    private BluetoothManager mBluetoothManager;
    private BluetoothAdapter mBluetoothAdapter;
    private static HashMap<String, BluetoothDeviceExtension> mBluetoothDevices = new HashMap();
    // HashMap mCharacteristicForDevices saves for each device the list of pending characteristics
    // that needs to be subscribed to, until they finally are subscribed.
    private static HashMap<String, List<String>> mCharacteristicsForDevice = new HashMap();

    private int MTU = 20;
    private final static int GATT_STATUS_TIME_OUT = 133;

    // Queue of pending transmissions
    private Queue<SendBLEDataTask> pendingSendDataTasks = new LinkedBlockingQueue<SendBLEDataTask>();
    private SendBLEDataTask currentTask;
    private boolean pendingTasksProcessing = false;

    public final static String ACTION_GATT_CONNECTED = "com.uei.bluetooth.le.ACTION_GATT_CONNECTED";
    public final static String ACTION_GATT_DISCONNECTED = "com.uei.bluetooth.le.ACTION_GATT_DISCONNECTED";
    public final static String ACTION_GATT_SERVICES_DISCOVERED = "com.uei.bluetooth.le.ACTION_GATT_SERVICES_DISCOVERED";
    public final static String ACTION_GATT_FINISHED_SUBSCRIBING = "com.uei.bluetooth.le.ACTION_GATT_FINISHED_SUBSCRIBING";
    public final static String ACTION_DATA_AVAILABLE = "com.uei.bluetooth.le.ACTION_DATA_AVAILABLE";
    public final static String NO_CHARACTERISTIC_FOUND = "com.uei.bluetooth.le.NO_CHARACTERISTIC_FOUND";
    public final static String ERROR_ON_SERVICE_DISCOVERY = "com.uei.bluetooth.le.ERROR_ON_SERVICE_DISCOVERY";
    public final static String ERROR_SENDING_DATA = "com.uei.bluetooth.le.ERROR_SENDING_DATA";
    public final static String EXTRA_DATA = "com.uei.bluetooth.le.EXTRA_DATA";
    public final static String DEVICE_DATA = "com.uei.bluetooth.le.DEVICE_DATA";
    public final static String HEX_DATA = "com.uei.bluetooth.le.HEX_DATA";
    public final static String CHARACTERISTIC_UUID = "com.uei.bluetooth.le.CHARACTERISTIC_UUID";

    Handler handler = new Handler(Looper.getMainLooper());


    // Implements callback methods for GATT events
    private final BluetoothGattCallback mGattCallback = new BluetoothGattCallback() {
        @Override
        public void onConnectionStateChange(final BluetoothGatt gatt, int status, int newState) {
            // Once connected we can bond
            if (newState == BluetoothProfile.STATE_CONNECTED) {
                broadcastUpdate(ACTION_GATT_CONNECTED, gatt.getDevice().getAddress());

                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }

                if (gatt.getDevice().getBondState() == BOND_BONDED) {
                    runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            gatt.discoverServices();
                        }
                    });
                } else {
                    bondDevice(gatt.getDevice().getAddress());
                }
            } else if (newState == BluetoothProfile.STATE_DISCONNECTED) {
                if (status == GATT_STATUS_TIME_OUT) { // Connection times out
                    initiateBackgroundConnection(gatt); // To face race condition issue
                } else {
                    broadcastUpdate(ACTION_GATT_DISCONNECTED, gatt.getDevice().getAddress());
                    close(gatt.getDevice().getAddress());
                }
            }
        }

        @Override
        public void onServicesDiscovered(BluetoothGatt gatt, int status) {
            if (status == BluetoothGatt.GATT_SUCCESS) {
                checkServicesAndCharacteristics(gatt);
            }
        }

        @Override
        public void onCharacteristicRead(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic, int status) {
            if (status == BluetoothGatt.GATT_SUCCESS) {
                if (characteristic.getUuid().toString().equalsIgnoreCase(BLEAttributes.VERSION_INFO_CHARACTERISTIC)
                        && characteristic.getValue() != null) {
                    parseRemoteVersion(gatt, characteristic.getValue());
                } else {
                    broadcastUpdate(ACTION_DATA_AVAILABLE, characteristic);
                }
            }
        }

        @Override
        public void onCharacteristicChanged(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic) {
            broadcastUpdate(ACTION_DATA_AVAILABLE, characteristic);
        }

        @Override
        public void onCharacteristicWrite(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic, int status) {
            if (status == BluetoothGatt.GATT_SUCCESS) {
                processDataTasks();
                if (currentTask.dataTask.isLastSlice()) {
                    currentTask.callerCallback.onSendCompleted(true, currentTask.dataTask.getData());
                }
            } else {
                cleanDataTasks();
                currentTask.callerCallback.onSendCompleted(false, currentTask.dataTask.getData());
            }
        }

        @Override
        public void onDescriptorWrite(BluetoothGatt gatt, BluetoothGattDescriptor descriptor,
                          int status) {
            if (status == BluetoothGatt.GATT_SUCCESS)
                updateCharacteristicsForDevice(gatt.getDevice().getAddress(), descriptor.getCharacteristic());
        }
    };

    private void runOnUiThread(Runnable runnable) {
        handler.post(runnable);
    }

    private void broadcastUpdate(final String action) {
        final Intent intent = new Intent(action);
        sendBroadcast(intent);
    }

    private void broadcastUpdate(final String action, final String deviceMac) {
        final Intent intent = new Intent(action);
        intent.putExtra(DEVICE_DATA, deviceMac);
        sendBroadcast(intent);
    }

    private void broadcastUpdate(final String action, final BluetoothGattCharacteristic characteristic) {
        final Intent intent = new Intent(action);

        // Writes the data formatted in HEX.
        final byte[] data = characteristic.getValue();
        if (data != null && data.length > 0) {
            final StringBuilder stringBuilder = new StringBuilder(data.length);
            for(byte byteChar: data)
                stringBuilder.append(String.format("%02X ", byteChar));
            intent.putExtra(EXTRA_DATA, new String(data) + "\n" + stringBuilder.toString());
            intent.putExtra(HEX_DATA, stringBuilder.toString());
        }

        intent.putExtra(CHARACTERISTIC_UUID, characteristic.getUuid().toString());
        sendBroadcast(intent);
    }

    public class LocalBinder extends Binder {
        BluetoothService getService() {
            return BluetoothService.this;
        }
    }

    @Override
    public IBinder onBind(Intent intent) {
        return mBinder;
    }

    @Override
    public boolean onUnbind(Intent intent) {
        closeAllConnections();
        return super.onUnbind(intent);
    }

    private final IBinder mBinder = new LocalBinder();

    private BluetoothGatt getGattDevice(String address) {
        if (mBluetoothDevices.get(address) != null) {
            return mBluetoothDevices.get(address).mBluetoothGatt;
        }

        return null;
    }

    private void closeAllConnections() {
        for (String address: mBluetoothDevices.keySet()) {
            close(address);
        }
    }

    private void checkServicesAndCharacteristics(BluetoothGatt mBluetoothGatt) {
        BluetoothGattService ucgService = mBluetoothGatt.getService(UUID.fromString(BLEAttributes.UCG_SERVICE_UUID));
        BluetoothGattService uugService = mBluetoothGatt.getService(UUID.fromString(BLEAttributes.UAPI_SERVICE_UUID));

        if (ucgService != null  && uugService != null) {
            BluetoothGattCharacteristic ucgIn = ucgService.getCharacteristic(UUID.fromString(BLEAttributes.UCG_IN));
            BluetoothGattCharacteristic ucgOut = ucgService.getCharacteristic(UUID.fromString(BLEAttributes.UCG_OUT));
            BluetoothGattCharacteristic uapiIn = uugService.getCharacteristic(UUID.fromString(BLEAttributes.UAPI_IN));
            BluetoothGattCharacteristic uapiOut = uugService.getCharacteristic(UUID.fromString(BLEAttributes.UAPI_OUT));

            if (ucgIn != null && ucgOut != null && uapiIn != null && uapiOut != null) {
                broadcastUpdate(ACTION_GATT_SERVICES_DISCOVERED, mBluetoothGatt.getDevice().getAddress());
            } else {
                broadcastUpdate(ERROR_ON_SERVICE_DISCOVERY, mBluetoothGatt.getDevice().getAddress());
            }
        }
    }

    public void checkVersionInfo(String address) {
        BluetoothGatt mBluetoothGatt = getGattDevice(address);
        if (mBluetoothGatt == null)
            return;

        BluetoothGattService deviceInfo = mBluetoothGatt.getService(UUID.fromString(BLEAttributes.DEVICE_INFO_SERVICE));

        if (deviceInfo != null) {
            BluetoothGattCharacteristic versionCharacteristic =
                    deviceInfo.getCharacteristic(UUID.fromString(BLEAttributes.VERSION_INFO_CHARACTERISTIC));
            byte[] versionData = versionCharacteristic.getValue();
            if (versionData == null) {
                read(mBluetoothGatt, versionCharacteristic);
                return;
            }
            parseRemoteVersion(mBluetoothGatt, versionData);
        }
    }

    private void parseRemoteVersion(BluetoothGatt mBluetoothGatt, byte[] versionData) {
        try {
            String version = new String(versionData, "UTF-8");
            BluetoothDeviceExtension device = mBluetoothDevices.get(mBluetoothGatt.getDevice().getAddress());
            device.swVersion = version;
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }
    }

    private void read(BluetoothGatt mBluetoothGatt, BluetoothGattCharacteristic characteristic) {
        mBluetoothGatt.readCharacteristic(characteristic);
    }

    private void updateCharacteristicsForDevice(String address, BluetoothGattCharacteristic characteristic) {
        if (mCharacteristicsForDevice.containsKey(address)) {
            List<String> characteristicsList = mCharacteristicsForDevice.get(address);
            if (characteristicsList == null || characteristicsList.isEmpty())
                return;

            characteristicsList.remove(characteristic.getUuid().toString());
            subscribeToNextCharacteristic(address);
            if (characteristicsList.isEmpty()) // Successful subscription to all characteristics of interest
                broadcastUpdate(ACTION_GATT_FINISHED_SUBSCRIBING, address);
        }
    }

    private BluetoothGattCharacteristic getCharacteristicFromService(String address, String characteristicUUID,
                                                                     String serviceUUID) {
        BluetoothGatt mBluetoothGatt = getGattDevice(address);
        if (mBluetoothGatt == null)
            return null;

        BluetoothGattService mBluetoothGattService = mBluetoothGatt.getService(UUID.fromString(serviceUUID));

        if (mBluetoothGattService == null)
            return null;

        BluetoothGattCharacteristic characteristic =  mBluetoothGattService.getCharacteristic(UUID.fromString(characteristicUUID));

        if (characteristic == null)
            broadcastUpdate(NO_CHARACTERISTIC_FOUND, address);

        return characteristic;
    }

    //BLE methods
    public boolean initialize() {
        if (mBluetoothManager == null) {
            mBluetoothManager = (BluetoothManager) getSystemService(Context.BLUETOOTH_SERVICE);
            if (mBluetoothManager == null)
                return false;
        }

        mBluetoothAdapter = mBluetoothManager.getAdapter();
        if (mBluetoothAdapter == null) {
            Log.e(TAG, "Unable to obtain a BluetoothAdapter.");
            return false;
        }

        return true;
    }

    // Workaround for race condition issue when using connectGatt
    // explained here https://issuetracker.google.com/issues/36995652
    private void initiateBackgroundConnection(final BluetoothGatt mBluetoothGatt) {
        if (mBluetoothGatt != null) {
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    mBluetoothGatt.connect();
                }
            });
        }
    }

    public boolean connect(final String address) {
        if (mBluetoothAdapter == null || address == null)
            return false;

        // Try to reconnect to previously connected device
        BluetoothGatt mBluetoothGatt = getGattDevice(address);
        if (mBluetoothGatt != null && !isDeviceConnected(address)) {
            Log.w("******* RECONNECTION", "Reconnecting to device");
            return mBluetoothGatt.connect();
        }

        final BluetoothDevice device = mBluetoothAdapter.getRemoteDevice(address);
        if (device == null) {
            Log.w(TAG, "Device not found. Unable to connect.");
            return false;
        }

        // Auto connect set to false to face race condition issue https://issuetracker.google.com/issues/36995652
        if (mBluetoothGatt == null) {
            BluetoothGatt newBluetoothGatt = device.connectGatt(this, false, mGattCallback);
            BluetoothDeviceExtension newDevice = new BluetoothDeviceExtension(newBluetoothGatt);
            mBluetoothDevices.put(address, newDevice);
        }

        return true;
    }

    public void disconnect(String address) {
        BluetoothGatt mBluetoothGatt = getGattDevice(address);
        if (mBluetoothAdapter == null || mBluetoothGatt == null) {
            Log.w(TAG, "BluetoothAdapter not initialized");
            return;
        }

        mBluetoothGatt.disconnect();
        mBluetoothGatt.close();
        mBluetoothDevices.remove(address);
        mCharacteristicsForDevice.remove(address);
    }

    public void startServiceDiscovery(String address) {
        BluetoothGatt mBluetoothGatt = getGattDevice(address);
        if (mBluetoothAdapter == null || mBluetoothGatt == null) {
            Log.w(TAG, "BluetoothAdapter not initialized");
            return;
        }

        mBluetoothGatt.discoverServices();
    }

    public void tryToReconnect(String address) {
        disconnect(address);

        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        connect(address);
    }

    public void tryConnectToBondedDevices() {
        for (BluetoothDevice device: getBondedDevices()) {
            connect(device.getAddress());
        }
    }

    public void bondDevice(String address) {
        if (mBluetoothAdapter == null || address == null) {
            Log.w(TAG, "BluetoothAdapter not initialized or unspecified address.");
            return;
        }

        final BluetoothDevice device = mBluetoothAdapter.getRemoteDevice(address);
        if (device.getBondState() == BOND_NONE)
            device.createBond();
    }

    public void removeBond(String address) {
        if (mBluetoothAdapter == null || address == null) {
            Log.w(TAG, "BluetoothAdapter not initialized or unspecified address.");
            return;
        }

        final BluetoothDevice device = mBluetoothAdapter.getRemoteDevice(address);
        try {
            Method m = device.getClass()
                    .getMethod("removeBond", (Class[]) null);
            m.invoke(device, (Object[]) null);
        } catch (Exception e) {
            Log.e("Fail to call method", e.getMessage());
        }
    }

    public List<BluetoothDeviceExtension> getConnectedDevices() {
        List<BluetoothDeviceExtension> devices = new ArrayList<BluetoothDeviceExtension>();
        if (mBluetoothDevices != null)
            devices = new ArrayList<BluetoothDeviceExtension>(mBluetoothDevices.values());
        return devices;
    }

    private List<BluetoothDevice> getGattConnectedDevices() {
        List<BluetoothDevice> devices = new ArrayList<BluetoothDevice>();
        if (mBluetoothManager != null)
            devices = mBluetoothManager.getConnectedDevices(BluetoothProfile.GATT);
        return devices;
    }

    public List<BluetoothDevice> getBondedDevices() {
        List<BluetoothDevice> bondedDevices = new ArrayList<BluetoothDevice>();
        if (mBluetoothAdapter != null) {
            Set<BluetoothDevice> bonded = mBluetoothAdapter.getBondedDevices();
            if (bonded != null) {
                for (BluetoothDevice bondedDevice: bonded) {
                    if (hasAdvertisedService(bondedDevice))
                        bondedDevices.add(bondedDevice);
                }
            }
        }
        return bondedDevices;
    }

    private boolean hasAdvertisedService(BluetoothDevice device) {
        ParcelUuid[] serviceUUIDs = device.getUuids();
        if (serviceUUIDs!= null && serviceUUIDs.length > 0) {
            for (ParcelUuid uuid: serviceUUIDs) {
                if (uuid.toString().equalsIgnoreCase(BLEAttributes.REVERSE_BYTE_ADVERTISED_SERVICE))
                    return true;
            }
        }
        return false;
    }

    public boolean isDeviceConnected(String deviceAddress) {
        List<BluetoothDevice> devices = getGattConnectedDevices();
        for (BluetoothDevice device: devices) {
            if (device.getAddress().equals(deviceAddress))
                return true;
        }
        return false;
    }

    public boolean isDeviceReady(String address) {
        return (mCharacteristicsForDevice.get(address) != null &&
                mCharacteristicsForDevice.get(address).isEmpty());
    }

    public DeviceConnectionState getDeviceState(String deviceAddress) {
        List<BluetoothDevice> devices = getGattConnectedDevices();
        for (BluetoothDevice device: devices) {
            if (device.getAddress().equals(deviceAddress)) {
                if (isDeviceReady(deviceAddress))
                    return DeviceConnectionState.CONNECTED;
                else
                    return DeviceConnectionState.CONNECTING;
            }
        }
        return DeviceConnectionState.DISCONNECTED;
    }

    public void close(String address) {
        BluetoothGatt mBluetoothGatt = getGattDevice(address);
        if (mBluetoothGatt == null) {
            return;
        }

        mBluetoothGatt.close();

        mBluetoothDevices.remove(address);
        mCharacteristicsForDevice.remove(address);
    }

    public void readCharacteristic(String address, String characteristicUUID, String serviceUUID) {
        if (!BLEAttributes.isReadableCharacteristic(characteristicUUID)) {
            Log.w(TAG, "Characteristic is not readable");
        }

        BluetoothGatt mBluetoothGatt = getGattDevice(address);
        if (mBluetoothAdapter == null || mBluetoothGatt == null) {
            Log.w(TAG, "BluetoothAdapter not initialized");
            return;
        }

        BluetoothGattCharacteristic characteristic = getCharacteristicFromService(address, characteristicUUID, serviceUUID);

        if (characteristic != null) {
            broadcastUpdate(ACTION_DATA_AVAILABLE, characteristic);
        }
    }

    public void setCharacteristicNotification(String address, BluetoothGattCharacteristic characteristic,
                                              boolean enabled) {
        BluetoothGatt mBluetoothGatt = getGattDevice(address);
        if (mBluetoothAdapter == null || mBluetoothGatt == null) {
            Log.w(TAG, "BluetoothAdapter not initialized");
            return;
        }

        mBluetoothGatt.setCharacteristicNotification(characteristic, enabled);
        BluetoothGattDescriptor descriptor = characteristic.getDescriptor(
                UUID.fromString(BLEAttributes.DESCRIPTOR_CONFIG_UUID));
        if (descriptor != null) {
            final int properties = characteristic.getProperties();
            byte[] characteristicType = ((properties & BluetoothGattCharacteristic.PROPERTY_INDICATE) != 0) ?
                    BluetoothGattDescriptor.ENABLE_INDICATION_VALUE : BluetoothGattDescriptor.ENABLE_NOTIFICATION_VALUE;
            descriptor.setValue(characteristicType);
            mBluetoothGatt.writeDescriptor(descriptor);
        }
    }

    // Add a data task to transaction queue
    private synchronized void addToPendingSendQueue(SendBLEDataTask dataTask) {
        pendingSendDataTasks.add(dataTask);

        // If there is no other transmission processing, go on with next task
        if (!pendingTasksProcessing) {
            processDataTasks();
        }
    }

    // Call when a transmission has been completed, will process next task if queued
    private void processDataTasks() {
        if (pendingSendDataTasks.size() <= 0)  {
            pendingTasksProcessing = false;
            return;
        }

        pendingTasksProcessing = true;
        currentTask = pendingSendDataTasks.remove();
        currentTask.execute();
    }

    private void cleanDataTasks() {
        pendingSendDataTasks.clear();
    }

    public void send(String address, SendBLEDataTask.BLECallback callback, byte[] data, String characteristicUUID, String serviceUUID) {
        if (!isDeviceReady(address)) {
            broadcastUpdate(ERROR_SENDING_DATA);
            return;
        }

        if (!BLEAttributes.isWritableCharacteristic(characteristicUUID)) {
            Log.w(TAG, "Characteristic is not writable");
            callback.onSendCompleted(false, null);
            return;
        }

        BluetoothGattCharacteristic characteristic =  getCharacteristicFromService(address, characteristicUUID, serviceUUID);

        BluetoothGatt mBluetoothGatt = getGattDevice(address);
        if (characteristic == null || mBluetoothGatt == null) {
            callback.onSendCompleted(false, null);
            return;
        }

        boolean remainingData = true;
        int offset = 0;
        while (remainingData) {
            int endSlice = Math.min(data.length, offset + MTU);
            byte[] sliceToSend = Arrays.copyOfRange(data, offset, endSlice);
            offset = offset + MTU;
            remainingData = offset < data.length;

            DataTask dataTask = new DataTask(sliceToSend, !remainingData);
            SendBLEDataTask sendTask = new SendBLEDataTask(callback, mBluetoothGatt, dataTask, characteristic);

            addToPendingSendQueue(sendTask);
        }
    }

    public void subscribeCharacteristics(String address) {
        if (mCharacteristicsForDevice.containsKey(address))
            return;

        mCharacteristicsForDevice.put(address, BLEAttributes.getReadableCharacteristics());
        subscribeToNextCharacteristic(address);
    }

    private void subscribeToNextCharacteristic(final String address) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                List<String> characteristicsList = mCharacteristicsForDevice.get(address);
                if (characteristicsList == null || characteristicsList.isEmpty())
                    return;

                String characteristicUUID = characteristicsList.get(0);
                String serviceUUID = BLEAttributes.getServicesForCharacteristic(characteristicUUID);
                final BluetoothGattCharacteristic characteristic = getCharacteristicFromService(address, characteristicUUID, serviceUUID);
                if (characteristic != null)
                    setCharacteristicNotification(address, characteristic, true);
            }
        });
    }
}
