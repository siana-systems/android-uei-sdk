package com.uei.uapisampleapp;

import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.app.Activity;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;

import uapiwrapper.UAPICallback;
import uapiwrapper.UEISDK;

import android.util.Log;
import android.view.View;
import android.widget.Toast;
import android.widget.TextView;

import com.uei.uapisampleapp.ble.SendBLEDataTask;
import com.uei.uapisampleapp.constants.BLEAttributes;
import com.uei.uapisampleapp.constants.UEIRemote;
import com.uei.uapisampleapp.helpers.HexHelper;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Timer;
import java.util.TimerTask;

public class MainActivity extends Activity implements SendBLEDataTask.BLECallback {

    // BLE Service
    private BluetoothService mBluetoothService;

    private String lastHex = "";
    private Timer servicesTimer;

    private HashMap<String, Long> discoveringServicesDevices = new HashMap();

    private final ServiceConnection mServiceConnection = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName componentName, IBinder service) {
            mBluetoothService = ((BluetoothService.LocalBinder) service).getService();
            if (!mBluetoothService.initialize()) {
                finish();
            }
        }

        @Override
        public void onServiceDisconnected(ComponentName componentName) {
            mBluetoothService = null;
        }
    };

    // Handles various events fired by the BluetoothService.
    private final BroadcastReceiver mGattUpdateReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            final String action = intent.getAction();
            if (action == null)
                return;
            switch (action) {
                case BluetoothService.ACTION_DATA_AVAILABLE:
                    String fromCharacteristic = intent.getStringExtra(BluetoothService.CHARACTERISTIC_UUID);
                    String stringReceived = intent.getStringExtra(BluetoothService.EXTRA_DATA);
                    String hexReceived = intent.getStringExtra(BluetoothService.HEX_DATA);
                    if (fromCharacteristic.equals(BLEAttributes.UCG_IN) && stringReceived != null && stringReceived.length() > 0) {
                        showReceivedData(stringReceived);
                    } else if (fromCharacteristic.equals(BLEAttributes.UAPI_IN) && hexReceived != null && hexReceived.length() > 0) {
                        handleUAPIMessage(hexReceived);
                    }
                    break;
                case BluetoothService.ACTION_GATT_CONNECTED:
                    String deviceConnected = intent.getStringExtra(BluetoothService.DEVICE_DATA);
                    if (deviceConnected != null)
                        onGATTConnectedDevice(deviceConnected);

                    break;
                case BluetoothService.ACTION_GATT_SERVICES_DISCOVERED:
                    String deviceAddress = intent.getStringExtra(BluetoothService.DEVICE_DATA);
                    if (deviceAddress != null)
                        onServiceDiscovered(deviceAddress);

                    break;
                case BluetoothService.ACTION_GATT_FINISHED_SUBSCRIBING:
                    String addressDevice = intent.getStringExtra(BluetoothService.DEVICE_DATA);
                    if (addressDevice != null)
                        onCharacteristicsSubscribed(addressDevice);

                    break;
                case BluetoothService.ERROR_SENDING_DATA:
                    showSendDataError();
                    break;
                case BluetoothDevice.ACTION_BOND_STATE_CHANGED:
                    Integer bondState = intent.getIntExtra(BluetoothDevice.EXTRA_BOND_STATE, 0);
                    BluetoothDevice bondedDevice = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
                    if (bondState == BluetoothDevice.BOND_BONDED && bondedDevice.getAddress() != null)
                        onDeviceBonded(bondedDevice.getAddress());

                    break;
            }
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        String versionName = getResources().getString(R.string.title_version) + BuildConfig.VERSION_NAME;
        TextView textView = (TextView) findViewById(R.id.version_label);
        textView.setText(versionName);

        UEISDK.manager().initAPI();

        OTAManager.shared().registerOTACallback();

        UEISDK.manager().registerUAPICallback(new UAPICallback() {
            @Override
            public void uapiCallback(int remoteid, byte[] data) {
                sendUAPIMessage(data);
            }
        });

        Intent gattServiceIntent = new Intent(this, BluetoothService.class);
        bindService(gattServiceIntent, mServiceConnection, BIND_AUTO_CREATE);

        registerReceiver(mGattUpdateReceiver, makeGattUpdateIntentFilter());
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        unbindService(mServiceConnection);
        unregisterReceiver(mGattUpdateReceiver);
        cancelTimers();
        mBluetoothService = null;
    }

    private void sendUAPIMessage(byte[] data) {
        if (mBluetoothService != null) {
            // Send message specified by UAPI library to module under BLE
            String hexString = HexHelper.getHexStringFromData(data);
            String fullHex = HexHelper.appendLengthToHexString(hexString);
            byte[] finalData = HexHelper.hexStringToByteArray(fullHex);
            mBluetoothService.send(OTAManager.shared().getDeviceForOTA(), this, finalData, BLEAttributes.UAPI_OUT,
                    BLEAttributes.UAPI_SERVICE_UUID);
        }
    }

    synchronized void handleUAPIMessage(final String hexString) {
            byte[] fullHexData = HexHelper.hexStringToByteArray(hexString.replace(" ", ""));
            byte[] hexData = Arrays.copyOfRange(fullHexData, 1, fullHexData.length);

            // To prevent duplicated messages to be enqueued and processed by UAPI library
            if (!lastHex.equalsIgnoreCase(hexString)) {
                lastHex = hexString;
                UEISDK.manager().handleUAPIData(UEIRemote.defaultId, hexData.length, hexData);
            }
    }

    public void goToDevicePairing(View v) {
        final Intent intent = new Intent(this, CentralPairingActivity.class);
        startActivity(intent);
    }

    public void goToOTASelection(View v) {
        final Intent intent = new Intent(this, OTAUpgradeActivity.class);
        startActivity(intent);
    }

    public void goToSendUnderUCG(View v) {
        final Intent intent = new Intent(this, UnderUCGActivity.class);
        startActivity(intent);
    }

    private void showSendDataError() {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Toast.makeText(MainActivity.this,
                        getResources().getString(R.string.error_sending_data),
                        Toast.LENGTH_LONG).show();
            }
        });
    }

    private void showReceivedData(final String data) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Toast.makeText(MainActivity.this, data, Toast.LENGTH_LONG).show();
            }
        });
    }

    private void onServiceDiscovered(final String deviceAddress) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if (mBluetoothService != null) {
                    mBluetoothService.subscribeCharacteristics(deviceAddress);
                }
            }
        });
    }

    private void onDeviceBonded(final String deviceAddress) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if (mBluetoothService != null) {
                    mBluetoothService.startServiceDiscovery(deviceAddress);
                }
            }
        });
    }

    private void onCharacteristicsSubscribed(final String deviceAddress) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                discoveringServicesDevices.remove(deviceAddress); // Full connection has been established
                manageServicesDiscoveredTimer(false);
                if (mBluetoothService != null)
                    mBluetoothService.checkVersionInfo(deviceAddress);
            }
        });
    }

    private void onGATTConnectedDevice(final String deviceAddress) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                manageServicesDiscoveredTimer(true);
                discoveringServicesDevices.put(deviceAddress, System.currentTimeMillis());
            }
        });
    }

    private void cancelTimers() {
        if (servicesTimer != null) {
            servicesTimer.cancel();
            servicesTimer = null;
        }
    }

    // Called on connection established, to check if services get discovered after
    private void startServicesDiscoveredTimer() {
        TimerTask timerTask = new TimerTask() {
            @Override
            public void run() {
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        checkIfReconnectionNeededBecauseServiceNotFound();
                    }
                });
            }
        };

        servicesTimer = new Timer();
        servicesTimer.scheduleAtFixedRate(timerTask, 25000, 25000);
    }

    private void checkIfReconnectionNeededBecauseServiceNotFound() {
        if (mBluetoothService == null)
            return;

        for(String address: discoveringServicesDevices.keySet()){
            Long timestamp = discoveringServicesDevices.get(address);
            Long timeDif = System.currentTimeMillis() - timestamp;
            if (timeDif > 120000) { // Too many tries to reconnect
                discoveringServicesDevices.remove(address);
                String message = getResources().getString(R.string.stopping_reconnection_tries) + " " + address;
                Toast.makeText(MainActivity.this, message,
                        Toast.LENGTH_LONG).show();
            } else if (timeDif > 25000) {
                discoveringServicesDevices.remove(address);
                mBluetoothService.tryToReconnect(address);
                String message = getResources().getString(R.string.no_services) + " " + address;
                Toast.makeText(MainActivity.this, message,
                        Toast.LENGTH_LONG).show();
                return;
            }
        }
    }

    private void stopServicesDiscoveredTimer() {
        servicesTimer.cancel();
        servicesTimer = null;
    }

    private void manageServicesDiscoveredTimer(Boolean shouldStart) {
        if (discoveringServicesDevices.isEmpty()) {
            if (shouldStart)
                startServicesDiscoveredTimer();
            else
                stopServicesDiscoveredTimer();
        }
    }

    @Override
    public void onSendCompleted(Boolean success, byte[] data) {}

    private static IntentFilter makeGattUpdateIntentFilter() {
        final IntentFilter intentFilter = new IntentFilter();
        intentFilter.addAction(BluetoothService.ACTION_DATA_AVAILABLE);
        intentFilter.addAction(BluetoothService.ACTION_GATT_SERVICES_DISCOVERED);
        intentFilter.addAction(BluetoothDevice.ACTION_ACL_CONNECTED);
        intentFilter.addAction(BluetoothDevice.ACTION_BOND_STATE_CHANGED);
        intentFilter.addAction(BluetoothService.ERROR_ON_SERVICE_DISCOVERY);
        intentFilter.addAction(BluetoothService.ACTION_GATT_FINISHED_SUBSCRIBING);
        intentFilter.addAction(BluetoothService.ACTION_GATT_CONNECTED);
        intentFilter.addAction(BluetoothService.ACTION_GATT_DISCONNECTED);
        intentFilter.addAction(BluetoothService.ERROR_SENDING_DATA);
        return intentFilter;
    }
}
