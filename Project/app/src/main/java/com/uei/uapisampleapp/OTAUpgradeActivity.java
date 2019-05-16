package com.uei.uapisampleapp;

import android.app.AlertDialog;
import android.app.ListActivity;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.content.res.AssetManager;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.os.Bundle;
import android.os.IBinder;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import com.uei.uapisampleapp.ble.BluetoothDeviceExtension;
import com.uei.uapisampleapp.constants.Constants;
import com.uei.uapisampleapp.constants.UEIRemote;
import com.uei.uapisampleapp.constants.VersionControl;
import com.uei.uapisampleapp.helpers.AlertDialogExtension;
import com.uei.uapisampleapp.helpers.HorizontalProgressBar;
import com.uei.uapisampleapp.notifications.NotificationCenter;
import com.uei.uapisampleapp.notifications.NotificationType;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import uapiwrapper.OTAUpgradeStatus;
import uapiwrapper.UEISDK;

import static com.google.android.gms.internal.zzs.TAG;

/**
 * Created by UEI on 9/26/17.
 */

public class OTAUpgradeActivity extends ListActivity {
    private OTAUpgradeActivity.FileListAdapter mFileListAdapter;
    private BluetoothService mBluetoothService;
    private ArrayList<String> connectedDevices = new ArrayList<String>();
    private ArrayList<BluetoothDeviceExtension> fullDevices = new ArrayList<BluetoothDeviceExtension>();
    private HorizontalProgressBar mProgressBar;

    private String fileToSend = "";
    private String selectedDevice = "";

    // Code to manage Service lifecycle.
    private final ServiceConnection mServiceConnection = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName componentName, IBinder service) {
            mBluetoothService = ((BluetoothService.LocalBinder) service).getService();
        }

        @Override
        public void onServiceDisconnected(ComponentName componentName) {
            mBluetoothService = null;
        }
    };

    private BroadcastReceiver otaReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            updateOTAStatus();
        }
    };

    // Handles various events fired by the BluetoothService.
    private final BroadcastReceiver mGattUpdateReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            Log.w(TAG, "****** onReceive (BroadcastReceiver) executed");
            final String action = intent.getAction();
            if (action == null)
                return;
            switch (action) {
                case BluetoothService.ERROR_SENDING_DATA: case BluetoothService.ACTION_GATT_DISCONNECTED:
                    dismissOTAProgress();
                    break;
            }
        }
    };

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getActionBar().setTitle(R.string.title_start_ota);

        // Bind to BLE service
        Intent gattServiceIntent = new Intent(this, BluetoothService.class);
        bindService(gattServiceIntent, mServiceConnection, BIND_AUTO_CREATE);

        // Subscribe to ota notifications
        NotificationCenter.addObserver(this, NotificationType.OTA_STATUS_CHANGED, otaReceiver);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        unbindService(mServiceConnection);
        mBluetoothService = null;

        // Unsubscribe to ota notifications
        NotificationCenter.removeObserver(this, otaReceiver);
    }

    private void selectRemote() {
        String[] listItems = connectedDevices.toArray(new String[connectedDevices.size()]);
        if (listItems.length == 0) {
            showAlertForNoItems();
        } else {
            showAlertWithItems(listItems);
        }
    }

    private void showAlertForNoItems() {
        AlertDialog.Builder builder = new AlertDialog.Builder(OTAUpgradeActivity.this);
        builder.setTitle(R.string.title_error);
        builder.setMessage(R.string.no_devices)
                .setCancelable(true);
        AlertDialog dialog = builder.create();
        dialog.show();
    }

    private void showConfirmationDialog(final String file) {
        AlertDialog.Builder builder = new AlertDialog.Builder(OTAUpgradeActivity.this);
        builder.setTitle(R.string.title_ota_confirm);
        String message = "Should we start OTA upgrade with " + file + " file";
        builder.setMessage(message)
                .setPositiveButton(R.string.start_button,
                        new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog, int id) {
                                saveOTAFile(file);
                                if (Constants.VERSION_CONTROL_ENABLED)
                                    prepareOTA(selectedDevice, file);
                                else
                                    startOTAUpgrade(file);
                            }
                        })
                .setNegativeButton(R.string.cancel_button,
                        new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog, int id) {
                                dialog.cancel();
                            }
                });
        AlertDialog dialog = builder.create();
        dialog.show();
    }

    private void showAlertWithItems(final String[] listItems) {
        AlertDialog.Builder builder = new AlertDialog.Builder(OTAUpgradeActivity.this);
        builder.setTitle(R.string.title_select_remote_send);
        builder.setItems(listItems, new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                dialog.dismiss();
                selectedDevice = listItems[which];
                showConfirmationDialog(fileToSend);
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

    private void setConnectedDevices() {
        if (mBluetoothService != null) {
            connectedDevices  = new ArrayList<String>();
            for (BluetoothDeviceExtension deviceExtension: mBluetoothService.getConnectedDevices()) {
                BluetoothDevice device = deviceExtension.getInnerDevice();
                if (device != null) {
                    connectedDevices.add(device.getAddress());
                    fullDevices.add(deviceExtension);
                }
            }
        }
    }

    public String getDeviceVersion(String deviceAddress) {
        for (BluetoothDeviceExtension deviceExtension: fullDevices) {
            BluetoothDevice device = deviceExtension.getInnerDevice();
            if (device != null && device.getAddress().equals(deviceAddress))
                return deviceExtension.swVersion;
        }
        return "";
    }

    private void prepareOTA(String remoteAddress, String fileName) {
        String path = getFileFullPath(fileName);
        String swVersion = getDeviceVersion(remoteAddress);
        VersionControl versionResult = OTAManager.shared().controlVersion(path, swVersion);
        switch (versionResult) {
            case LOWER_EQUAL:
                AlertDialogExtension noticeAlert = new AlertDialogExtension();
                String noticeTitle = getResources().getString(R.string.title_notice);
                noticeAlert.showAlert(this, noticeTitle,
                        getResources().getString(R.string.already_updated));
                break;
            case HIGHER:
                startOTAUpgrade(fileName);
                break;
            case NONE:
                AlertDialogExtension errorAlert = new AlertDialogExtension();
                String errorTitle = getResources().getString(R.string.title_error);
                errorAlert.showAlert(this, errorTitle,
                        getResources().getString(R.string.no_version));
        }
    }

    private String getFileFullPath(String fileName) {
        return getApplicationContext().getFilesDir().toString() + "/" + fileName;
    }

    private Boolean saveOTAFile(String fileName) {
        String fromPath = Constants.OTA_FILE_FOLDER + "/" + fileName;
        return  OTAManager.shared().saveFileForUAPI(OTAUpgradeActivity.this, fromPath, fileName);
    }

    private void startOTAUpgrade(String fileName) {
        mProgressBar = new HorizontalProgressBar(this, getResources().getString(R.string.title_ota_progress));

        UEISDK.manager().registerRemote(UEIRemote.defaultId);
        String path = getFileFullPath(fileName);
        OTAManager.shared().registerDeviceForOTA(selectedDevice);
        UEISDK.manager().startOTAUpgrade(UEIRemote.defaultId, path, UEIRemote.productName);
    }

    @Override
    protected void onListItemClick(ListView l, View v, int position, long id) {
        final String fileName = mFileListAdapter.getFile(position);
        if (fileName == null) return;

        fileToSend = fileName;
        setConnectedDevices();
        selectRemote();
    }

    // Adapter for files.
    private class FileListAdapter extends BaseAdapter {
        private ArrayList<String> mFiles;
        private LayoutInflater mInflator;

        public FileListAdapter() {
            super();
            mFiles = new ArrayList<String>();
            mInflator = OTAUpgradeActivity.this.getLayoutInflater();
        }

        public void addFile(String fileName) {
            if(!mFiles.contains(fileName)) {
                mFiles.add(fileName);
            }
            notifyDataSetChanged();
        }

        public void setFiles(String [] files) {
            mFiles = new ArrayList<String>(Arrays.asList(files));
            notifyDataSetChanged();
        }

        public String getFile(int position) {
            return mFiles.get(position);
        }

        public void clear() {
            mFiles.clear();
            notifyDataSetChanged();
        }

        @Override
        public int getCount() {
            return mFiles.size();
        }

        @Override
        public Object getItem(int i) {
            return mFiles.get(i);
        }

        @Override
        public long getItemId(int i) {
            return i;
        }

        @Override
        public View getView(int i, View view, ViewGroup viewGroup) {
            OTAUpgradeActivity.ViewHolder viewHolder;
            if (view == null) {
                view = mInflator.inflate(R.layout.list_item_file, null);
                viewHolder = new OTAUpgradeActivity.ViewHolder();
                viewHolder.fileName = (TextView) view.findViewById(R.id.file_name);
                view.setTag(viewHolder);
            } else {
                viewHolder = (OTAUpgradeActivity.ViewHolder) view.getTag();
            }

            String fileName = mFiles.get(i);
            viewHolder.fileName.setText(fileName);

            return view;
        }
    }

    private static class ViewHolder {
        TextView fileName;
    }

    private void getLocalFiles() {
        try {
            String [] list;
            list = getAssets().list(Constants.OTA_FILE_FOLDER);
            mFileListAdapter.setFiles(list);
        } catch (IOException e) {}
    }

    private void dismissOTAProgress() {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if (mProgressBar != null)
                    mProgressBar.dismissHorizontalProgressBar();
            }
        });
    }

    @Override
    protected void onResume() {
        super.onResume();

        // Initializes list view adapter
        mFileListAdapter = new OTAUpgradeActivity.FileListAdapter();
        getLocalFiles();

        setListAdapter(mFileListAdapter);

        updateOTAStatus();

        registerReceiver(mGattUpdateReceiver, makeGattUpdateIntentFilter());
    }

    private void updateOTAStatus() {
        if (mProgressBar == null)
            mProgressBar = new HorizontalProgressBar(this, getResources().getString(R.string.title_ota_progress));

        OTAUpgradeStatus status = OTAManager.shared().getUpgradeStatus();
        int progress = OTAManager.shared().getUpgradeProgress();
        int totalSize = OTAManager.shared().getTotalOTAFileSize();
        switch (status) {
            case STARTED: case INPROGRESS:
                mProgressBar.updateProgressBar(progress, totalSize);
                break;
            case COMPLETED:
                mProgressBar.dismissHorizontalProgressBar();
                Toast.makeText(this, R.string.ota_completed, Toast.LENGTH_LONG).show();
                OTAManager.shared().cleanOTAStatus();
                break;
            case FAILED: case FAILEDLOWBATTERY: case CANCELLED:
                mProgressBar.dismissHorizontalProgressBar();
                Toast.makeText(this, R.string.ota_failed, Toast.LENGTH_LONG).show();
                OTAManager.shared().cleanOTAStatus();
                break;
            default:
                mProgressBar.dismissHorizontalProgressBar();
                OTAManager.shared().cleanOTAStatus();
                break;
        }
    }

    @Override
    protected void onPause() {
        super.onPause();
        mFileListAdapter.clear();

        unregisterReceiver(mGattUpdateReceiver);
    }

    private static IntentFilter makeGattUpdateIntentFilter() {
        final IntentFilter intentFilter = new IntentFilter();
        intentFilter.addAction(BluetoothService.ERROR_SENDING_DATA);
        intentFilter.addAction(BluetoothService.ACTION_GATT_DISCONNECTED);
        return intentFilter;
    }
}
