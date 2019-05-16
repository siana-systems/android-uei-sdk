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
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.os.Bundle;
import android.os.IBinder;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;


import com.uei.uapisampleapp.ble.BluetoothDeviceExtension;
import com.uei.uapisampleapp.ble.SendBLEDataTask;
import com.uei.uapisampleapp.constants.BLEAttributes;
import com.uei.uapisampleapp.constants.Constants;
import com.uei.uapisampleapp.helpers.HexHelper;
import com.uei.uapisampleapp.helpers.ProgressBarHandler;

import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.Arrays;

import static com.google.android.gms.internal.zzs.TAG;

/**
 * Created by UEI on 9/11/17.
 */

public class UnderUCGActivity extends ListActivity implements SendBLEDataTask.BLECallback {
    private FileListAdapter mFileListAdapter;
    private BluetoothService mBluetoothService;
    private ArrayList<String> connectedDevices  = new ArrayList<String>();
    private ProgressBarHandler mProgressBar;

    private Boolean sendString = false;
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

    // Handles various events fired by the BluetoothService.
    private final BroadcastReceiver mGattUpdateReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            Log.w(TAG, "****** onReceive (BroadcastReceiver) executed");
            final String action = intent.getAction();
            if (action == null)
                return;
            switch (action) {
                case BluetoothService.ERROR_SENDING_DATA:
                    dismissProgressBar();
                    break;
            }
        }
    };

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getActionBar().setTitle(R.string.title_under_ucg);

        // Bind to BLE service
        Intent gattServiceIntent = new Intent(this, BluetoothService.class);
        bindService(gattServiceIntent, mServiceConnection, BIND_AUTO_CREATE);

        mProgressBar = new ProgressBarHandler(this);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        unbindService(mServiceConnection);
        mBluetoothService = null;
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.ucg_menu, menu);

        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.send_string:
                sendString = true;
                setConnectedDevices();
                selectRemote();
                break;
        }
        return true;
    }

    private void showInputDialog() {
        LayoutInflater layoutInflater = LayoutInflater.from(UnderUCGActivity.this);
        View promptView = layoutInflater.inflate(R.layout.input_dialog, null);
        AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(UnderUCGActivity.this);
        alertDialogBuilder.setView(promptView);

        final EditText editText = (EditText) promptView.findViewById(R.id.text_input);
        // setup a dialog window
        alertDialogBuilder.setCancelable(false)
                .setPositiveButton(R.string.send_button, new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int id) {
                        String stringToSend = editText.getText().toString().replace(" ", "");
                        Log.d("String entered", stringToSend);
                        byte[] hexString = HexHelper.hexStringToByteArray(stringToSend);
                        sendDataUnderUCG(hexString);
                    }
                })
                .setNegativeButton(R.string.cancel_button,
                        new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog, int id) {
                                dialog.cancel();
                            }
                        });

        AlertDialog alert = alertDialogBuilder.create();
        alert.show();
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
        AlertDialog.Builder builder = new AlertDialog.Builder(UnderUCGActivity.this);
        builder.setTitle(R.string.title_error);
        builder.setMessage(R.string.no_devices)
                .setCancelable(true);
        AlertDialog dialog = builder.create();
        dialog.show();
    }

    private void showAlertWithItems(final String[] listItems) {
        AlertDialog.Builder builder = new AlertDialog.Builder(UnderUCGActivity.this);
        builder.setTitle(R.string.title_select_remote_send);
        builder.setItems(listItems, new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                dialog.dismiss();
                selectedDevice = listItems[which];
                if (sendString)
                    showInputDialog();
                else
                    sendFileUnderUCG(fileToSend);
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
                if (device != null)
                    connectedDevices.add(device.getAddress());
            }
        }
    }

    private void sendDataUnderUCG(byte[] data) {
        if (mBluetoothService != null)
            mBluetoothService.send(selectedDevice, this, data, BLEAttributes.UCG_OUT, BLEAttributes.UCG_SERVICE_UUID);
    }

    private void sendFileUnderUCG(String fileName) {
        mProgressBar.show(this);
        try {
            InputStream is = getAssets().open(Constants.BLE_FILE_FOLDER + "/" + fileName);
            int size = is.available();
            byte[] buffer = new byte[size];
            is.read(buffer);
            is.close();
            sendDataUnderUCG(buffer);
        } catch (Exception ex) {
            ex.printStackTrace();
            mProgressBar.hide(this);
        }
    }

    @Override
    protected void onListItemClick(ListView l, View v, int position, long id) {
        final String fileName = mFileListAdapter.getFile(position);
        if (fileName == null) return;

        sendString = false;
        fileToSend = fileName;
        setConnectedDevices();
        selectRemote();
    }

    @Override
    public void onSendCompleted(final Boolean success, byte[] data) { // Called when sending data via bluetooth has finished
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                mProgressBar.hide(UnderUCGActivity.this);
                if (success) {
                    Toast.makeText(UnderUCGActivity.this, R.string.data_sent, Toast.LENGTH_LONG).show();
                }
            }
        });
    }

    // Adapter for files.
    private class FileListAdapter extends BaseAdapter {
        private ArrayList<String> mFiles;
        private LayoutInflater mInflator;

        public FileListAdapter() {
            super();
            mFiles = new ArrayList<String>();
            mInflator = UnderUCGActivity.this.getLayoutInflater();
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
            UnderUCGActivity.ViewHolder viewHolder;
            if (view == null) {
                view = mInflator.inflate(R.layout.list_item_file, null);
                viewHolder = new ViewHolder();
                viewHolder.fileName = (TextView) view.findViewById(R.id.file_name);
                view.setTag(viewHolder);
            } else {
                viewHolder = (UnderUCGActivity.ViewHolder) view.getTag();
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
            list = getAssets().list(Constants.BLE_FILE_FOLDER);
            mFileListAdapter.setFiles(list);
        } catch (IOException e) {}
    }

    @Override
    protected void onResume() {
        super.onResume();

        // Initializes list view adapter
        mFileListAdapter = new FileListAdapter();
        getLocalFiles();

        setListAdapter(mFileListAdapter);
        registerReceiver(mGattUpdateReceiver, makeGattUpdateIntentFilter());
    }

    @Override
    protected void onPause() {
        super.onPause();
        mFileListAdapter.clear();
        unregisterReceiver(mGattUpdateReceiver);
    }

    private void dismissProgressBar() {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if (mProgressBar != null)
                    mProgressBar.hide(UnderUCGActivity.this);
            }
        });
    }

    private static IntentFilter makeGattUpdateIntentFilter() {
        final IntentFilter intentFilter = new IntentFilter();
        intentFilter.addAction(BluetoothService.ERROR_SENDING_DATA);
        return intentFilter;
    }
}
