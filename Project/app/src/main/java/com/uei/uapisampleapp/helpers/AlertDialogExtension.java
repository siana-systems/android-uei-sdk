package com.uei.uapisampleapp.helpers;

import android.app.AlertDialog;
import android.content.Context;
import com.uei.uapisampleapp.R;

/**
 * Created by UEI on 1/23/18.
 */

public class AlertDialogExtension {

    public void showAlert(Context context, String title, String message) {
        AlertDialog.Builder builder = new AlertDialog.Builder(context);
        builder.setTitle(title);
        builder.setMessage(message)
                .setCancelable(true);
        AlertDialog dialog = builder.create();
        dialog.show();
    }
}
