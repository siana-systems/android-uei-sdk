package com.uei.uapisampleapp;

import android.Manifest;
import android.app.Activity;
import android.app.AlertDialog;
import android.app.ListActivity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothManager;
import android.bluetooth.le.BluetoothLeScanner;
import android.bluetooth.le.ScanCallback;
import android.bluetooth.le.ScanFilter;
import android.bluetooth.le.ScanResult;
import android.bluetooth.le.ScanSettings;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.IntentSender;
import android.content.ServiceConnection;
import android.content.pm.PackageManager;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.os.ParcelUuid;
import android.support.annotation.NonNull;
import android.support.v13.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.common.api.PendingResult;
import com.google.android.gms.common.api.ResultCallback;
import com.google.android.gms.common.api.Status;
import com.google.android.gms.location.LocationRequest;
import com.google.android.gms.location.LocationServices;
import com.google.android.gms.location.LocationSettingsRequest;
import com.google.android.gms.location.LocationSettingsResult;
import com.google.android.gms.location.LocationSettingsStatusCodes;
import com.uei.uapisampleapp.ble.BluetoothDeviceExtension;
import com.uei.uapisampleapp.ble.DeviceConnectionState;
import com.uei.uapisampleapp.constants.BLEAttributes;

import java.util.ArrayList;
import java.util.List;

import static com.google.android.gms.internal.zzs.TAG;

/**
 * Activity for scanning and displaying available Bluetooth LE devices.
 */
public class CentralPairingActivity extends ListActivity {
    private LeDeviceListAdapter mLeDeviceListAdapter;
    private BluetoothAdapter mBluetoothAdapter;
    private BluetoothLeScanner bluetoothLeScanner;
    private BluetoothService mBluetoothService;
    private boolean mScanning;
    private boolean listConnectedDevices = false;
    private Handler mHandler;

    private static final int REQUEST_ENABLE_BT = 1;
    private static final long SCAN_PERIOD = 10000;
    private static final int PERMISSION_REQUEST_COARSE_LOCATION = 456;
    protected static final int REQUEST_CHECK_SETTINGS = 0x1;

    // Code to manage Service lifecycle.
    private final ServiceConnection mServiceConnection = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName componentName, IBinder service) {
            mBluetoothService = ((BluetoothService.LocalBinder) service).getService();
            if (listConnectedDevices) {
                listConnectedDevices = false;
                setConnectedDevices();
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
                case BluetoothService.ACTION_GATT_CONNECTED: // App is locally connected but characteristics and services still need to be discovered
                    case BluetoothService.ACTION_GATT_DISCONNECTED:
                    case BluetoothService.ACTION_GATT_FINISHED_SUBSCRIBING: // App is fully connected to device
                        String deviceAddress = intent.getStringExtra(BluetoothService.DEVICE_DATA);
                        if (deviceAddress != null)
                            updateConnectionState(action.equalsIgnoreCase(BluetoothService.ACTION_GATT_DISCONNECTED), deviceAddress);
                        break;
                case BluetoothService.ACTION_DATA_AVAILABLE:
                    String fromCharacteristic = intent.getStringExtra(BluetoothService.CHARACTERISTIC_UUID);
                    String received = intent.getStringExtra(BluetoothService.EXTRA_DATA);
                    if (fromCharacteristic.equals(BLEAttributes.UCG_IN) && received != null && received.length() > 0) {
                        showReceivedData(received);
                    }
                    break;
            }
        }
    };

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getActionBar().setTitle(R.string.title_central_pairing);
        mHandler = new Handler();

        // Check whether BLE is supported on the device
        if (!getPackageManager().hasSystemFeature(PackageManager.FEATURE_BLUETOOTH_LE)) {
            Toast.makeText(this, R.string.ble_not_supported, Toast.LENGTH_SHORT).show();
            finish();
        }

        ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.ACCESS_FINE_LOCATION}, PERMISSION_REQUEST_COARSE_LOCATION);
        displayLocationSettingsRequest(this);

        // Initializes a Bluetooth adapter
        final BluetoothManager bluetoothManager = (BluetoothManager) getSystemService(Context.BLUETOOTH_SERVICE);
        mBluetoothAdapter = bluetoothManager.getAdapter();

        bluetoothLeScanner = mBluetoothAdapter.getBluetoothLeScanner();

        // Checks if Bluetooth is supported on the device.
        if (mBluetoothAdapter == null) {
            Toast.makeText(this, R.string.error_bluetooth_not_supported, Toast.LENGTH_SHORT).show();
            finish();
            return;
        }

        // Bind to BLE service
        Intent gattServiceIntent = new Intent(this, BluetoothService.class);
        bindService(gattServiceIntent, mServiceConnection, BIND_AUTO_CREATE);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        unbindService(mServiceConnection);
        mBluetoothService = null;
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.main, menu);
        if (!mScanning) {
            menu.findItem(R.id.menu_stop).setVisible(false);
            menu.findItem(R.id.menu_scan).setVisible(true);
            menu.findItem(R.id.menu_refresh).setActionView(null);
        } else {
            menu.findItem(R.id.menu_stop).setVisible(true);
            menu.findItem(R.id.menu_scan).setVisible(false);
            menu.findItem(R.id.menu_refresh).setActionView(R.layout.actionbar_indeterminate_progress);
        }
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.menu_scan:
                scanLeDevice(true);
                break;
            case R.id.menu_stop:
                scanLeDevice(false);
                break;
            case R.id.menu_read:
                selectRemoteToReadFrom();
                break;
        }
        return true;
    }

    @Override
    protected void onResume() {
        super.onResume();

        // If Bluetooth is not currently enabled, displays dialog asking the user to grant permission to enable it
        if (!mBluetoothAdapter.isEnabled()) {
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
        }

        // Initializes list view adapter
        mLeDeviceListAdapter = new LeDeviceListAdapter();
        setConnectedDevices();

        setListAdapter(mLeDeviceListAdapter);
        scanLeDevice(true);

        registerReceiver(mGattUpdateReceiver, makeGattUpdateIntentFilter());
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (requestCode == REQUEST_ENABLE_BT && resultCode == Activity.RESULT_CANCELED) {
            finish();
            return;
        }
        super.onActivityResult(requestCode, resultCode, data);
    }

    @Override
    protected void onPause() {
        super.onPause();
        scanLeDevice(false);
        mLeDeviceListAdapter.clear();

        unregisterReceiver(mGattUpdateReceiver);
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String permissions[], @NonNull int[] grantResults) {
        switch (requestCode) {
            case PERMISSION_REQUEST_COARSE_LOCATION: {
                if (grantResults[0] != PackageManager.PERMISSION_GRANTED) {
                    ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.ACCESS_COARSE_LOCATION}, PERMISSION_REQUEST_COARSE_LOCATION);
                }
            }
        }
    }

    private void displayLocationSettingsRequest(Context context) {
        GoogleApiClient googleApiClient = new GoogleApiClient.Builder(context)
                .addApi(LocationServices.API).build();
        googleApiClient.connect();

        LocationRequest locationRequest = LocationRequest.create();
        locationRequest.setPriority(LocationRequest.PRIORITY_HIGH_ACCURACY);
        locationRequest.setInterval(10000);
        locationRequest.setFastestInterval(10000 / 2);

        LocationSettingsRequest.Builder builder = new LocationSettingsRequest.Builder().addLocationRequest(locationRequest);
        builder.setAlwaysShow(true);

        PendingResult<LocationSettingsResult> result = LocationServices.SettingsApi.checkLocationSettings(googleApiClient, builder.build());
        result.setResultCallback(new ResultCallback<LocationSettingsResult>() {
            @Override
            public void onResult(LocationSettingsResult result) {
                final Status status = result.getStatus();
                switch (status.getStatusCode()) {
                    case LocationSettingsStatusCodes.SUCCESS:
                        Log.i(TAG, "All location settings are satisfied.");
                        break;
                    case LocationSettingsStatusCodes.RESOLUTION_REQUIRED:
                        Log.i(TAG, "Location settings are not satisfied. Show the user a dialog to upgrade location settings ");

                        try {
                            status.startResolutionForResult(CentralPairingActivity.this, REQUEST_CHECK_SETTINGS);
                        } catch (IntentSender.SendIntentException e) {
                            Log.i(TAG, "PendingIntent unable to execute request.");
                        }
                        break;
                    case LocationSettingsStatusCodes.SETTINGS_CHANGE_UNAVAILABLE:
                        Log.i(TAG, "Location settings are inadequate, and cannot be fixed here. Dialog not created.");
                        break;
                }
            }
        });
    }

    @Override
    protected void onListItemClick(ListView l, View v, int position, long id) {
        final BluetoothDeviceExtension deviceExtension = mLeDeviceListAdapter.getDevice(position);
        if (deviceExtension == null) return;

        if (mBluetoothService != null) {
            mScanning = false;
            bluetoothLeScanner.stopScan(scanCallback);
            invalidateOptionsMenu();
            mBluetoothService.connect(deviceExtension.scanResult.getAddress());
        }
    }

    private void setConnectedDevices() {
        if (mBluetoothService != null)
            mLeDeviceListAdapter.setDevices(mBluetoothService.getConnectedDevices());
        else
            listConnectedDevices = true;
    }

    private void scanLeDevice(final boolean enable) {
        if (bluetoothLeScanner == null) { return; }
        if (enable) {
            // Stops scanning after a pre-defined scan period.
            mHandler.postDelayed(new Runnable() {
                @Override
                public void run() {
                    mScanning = false;
                    bluetoothLeScanner.stopScan(scanCallback);
                    invalidateOptionsMenu();
                }
            }, SCAN_PERIOD);

            mScanning = true;
            // Scans for specified service only
            ParcelUuid uuid = ParcelUuid.fromString(BLEAttributes.ADVERTISED_SERVICE);
            ScanFilter scanFilter = new ScanFilter.Builder().setServiceUuid(uuid).build();

            List<ScanFilter> scanFilters = new ArrayList<ScanFilter>();
            scanFilters.add(scanFilter);

            ScanSettings settings = new ScanSettings.Builder().build();
            bluetoothLeScanner.startScan(scanFilters, settings, scanCallback);
        } else {
            mScanning = false;
            bluetoothLeScanner.stopScan(scanCallback);
        }
        invalidateOptionsMenu();
    }

    // Adapter for holding devices found through scanning.
    private class LeDeviceListAdapter extends BaseAdapter {
        private ArrayList<BluetoothDeviceExtension> mLeDevices;
        private LayoutInflater mInflator;

        public LeDeviceListAdapter() {
            super();
            mLeDevices = new ArrayList<BluetoothDeviceExtension>();
            mInflator = CentralPairingActivity.this.getLayoutInflater();
        }

        public void addDevice(BluetoothDeviceExtension device) {
            if(!mLeDevices.contains(device)) {
                mLeDevices.add(device);
            }
            notifyDataSetChanged();
        }

        public void setDevices(List<BluetoothDeviceExtension> devices) {
            mLeDevices = new ArrayList<BluetoothDeviceExtension>(devices);
            notifyDataSetChanged();
        }

        public BluetoothDeviceExtension getDevice(int position) {
            return mLeDevices.get(position);
        }

        public void clear() {
            mLeDevices.clear();
            notifyDataSetChanged();
        }

        public void removeDevice(String address) {
            for (BluetoothDeviceExtension deviceExtension: mLeDevices) {
                if (getDeviceFromExtended(deviceExtension).getAddress().equalsIgnoreCase(address)) {
                    mLeDevices.remove(deviceExtension);
                    break;
                }
            }
            notifyDataSetChanged();
        }

        @Override
        public int getCount() {
            return mLeDevices.size();
        }

        @Override
        public Object getItem(int i) {
            return mLeDevices.get(i);
        }

        @Override
        public long getItemId(int i) {
            return i;
        }

        @Override
        public View getView(int i, View view, ViewGroup viewGroup) {
            ViewHolder viewHolder;
            if (view == null) {
                view = mInflator.inflate(R.layout.list_item_device, null);
                viewHolder = new ViewHolder();
                viewHolder.deviceAddress = (TextView) view.findViewById(R.id.device_address);
                viewHolder.deviceName = (TextView) view.findViewById(R.id.device_name);
                viewHolder.deviceStatus = (TextView) view.findViewById(R.id.connection_state);
                view.setTag(viewHolder);
            } else {
                viewHolder = (ViewHolder) view.getTag();
            }

            BluetoothDeviceExtension deviceExtension = mLeDevices.get(i);
            BluetoothDevice device = getDeviceFromExtended(deviceExtension);

            final String deviceName = device.getName();
            if (deviceName != null && deviceName.length() > 0)
                viewHolder.deviceName.setText(deviceName);
            else
                viewHolder.deviceName.setText(R.string.unknown_device);

            String statusLabelText = getResources().getString(R.string.disconnected);
            int statusLabelColor = R.color.colorDisconnected;
            if (mBluetoothService != null) {
                DeviceConnectionState deviceState = mBluetoothService.getDeviceState(device.getAddress());
                switch (deviceState) {
                    case CONNECTED:
                        statusLabelText = getResources().getString(R.string.connected);
                        statusLabelColor = R.color.colorConnected;
                        break;
                    case CONNECTING:
                        statusLabelText = getResources().getString(R.string.connecting);
                        statusLabelColor = R.color.colorConnecting;
                        break;
                }
            }

            viewHolder.deviceStatus.setText(statusLabelText);
            viewHolder.deviceStatus.setTextColor(ContextCompat.getColor(viewHolder.deviceStatus.getContext(),
                    statusLabelColor));

            viewHolder.deviceAddress.setText(device.getAddress());

            return view;
        }
    }

    // Device scan callback.
    private ScanCallback scanCallback = new ScanCallback() {
        @Override
        public void onScanResult(int callbackType, final ScanResult result) {
            super.onScanResult(callbackType, result);

            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    BluetoothDeviceExtension deviceExtension = new BluetoothDeviceExtension(result.getDevice());
                    mLeDeviceListAdapter.addDevice(deviceExtension);
                }
            });
        }

        @Override
        public void onBatchScanResults(final List<ScanResult> results) {
            super.onBatchScanResults(results);

            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    for (ScanResult result : results) {
                        BluetoothDeviceExtension deviceExtension = new BluetoothDeviceExtension(result.getDevice());
                        mLeDeviceListAdapter.addDevice(deviceExtension);
                    }
                }
            });
        }

        @Override
        public void onScanFailed(int errorCode) {
            super.onScanFailed(errorCode);
        }
    };

    static class ViewHolder {
        TextView deviceName;
        TextView deviceAddress;
        TextView deviceStatus;
    }

    private void updateConnectionState(final boolean disconnect, final String address) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if (disconnect)
                    mLeDeviceListAdapter.removeDevice(address);
                else
                    mLeDeviceListAdapter.notifyDataSetChanged();
            }
        });
    }

    private void showReceivedData(final String data) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Toast.makeText(CentralPairingActivity.this, data, Toast.LENGTH_LONG).show();
            }
        });
    }

    private void selectRemoteToReadFrom() {
        ArrayList<String> connectedDevices = getConnectedDevices();
        String[] listItems = connectedDevices.toArray(new String[connectedDevices.size()]);
        if (listItems.length == 0) {
            showAlertForNoItems();
        } else {
            showAlertWithItems(listItems);
        }
    }

    private ArrayList<String> getConnectedDevices() {
        ArrayList<String> connectedDevices  = new ArrayList<String>();
        if (mBluetoothService != null) {
            for (BluetoothDeviceExtension deviceExtension: mBluetoothService.getConnectedDevices()) {
                connectedDevices.add(getDeviceFromExtended(deviceExtension).getAddress());
            }
        }
        return connectedDevices;
    }

    private void showAlertForNoItems() {
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setTitle(R.string.title_error);
        builder.setMessage(R.string.no_devices)
                .setCancelable(true);
        AlertDialog dialog = builder.create();
        dialog.show();
    }

    private void showAlertWithItems(final String[] listItems) {
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setTitle(R.string.title_select_remote_read);
        builder.setItems(listItems, new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                dialog.dismiss();
                String deviceAddress = listItems[which];
                mBluetoothService.readCharacteristic(deviceAddress, BLEAttributes.UCG_IN, BLEAttributes.UCG_SERVICE_UUID);
            }
        }).setNegativeButton(R.string.cancel_button,
                new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int id) {
                        dialog.cancel();
                    }
                });
        AlertDialog dialog = builder.create();
        ListView listView = dialog.getListView();
        listView.setDivider(new ColorDrawable(Color.LTGRAY));
        listView.setDividerHeight(1);
        dialog.show();
    }

    private BluetoothDevice getDeviceFromExtended(BluetoothDeviceExtension deviceExtension) {
        BluetoothDevice device = deviceExtension.getInnerDevice();
        return device != null ? device : deviceExtension.scanResult;
    }

    private static IntentFilter makeGattUpdateIntentFilter() {
        final IntentFilter intentFilter = new IntentFilter();
        intentFilter.addAction(BluetoothService.ACTION_GATT_CONNECTED);
        intentFilter.addAction(BluetoothService.ACTION_GATT_SERVICES_DISCOVERED);
        intentFilter.addAction(BluetoothService.ACTION_GATT_DISCONNECTED);
        intentFilter.addAction(BluetoothService.ACTION_DATA_AVAILABLE);
        intentFilter.addAction(BluetoothDevice.ACTION_BOND_STATE_CHANGED);
        intentFilter.addAction(BluetoothService.ACTION_GATT_FINISHED_SUBSCRIBING);
        return intentFilter;
    }
}
