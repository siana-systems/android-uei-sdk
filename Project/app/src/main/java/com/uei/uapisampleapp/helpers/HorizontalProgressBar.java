package com.uei.uapisampleapp.helpers;

import android.app.ProgressDialog;

import android.content.Context;

/**
 * Created by UEI on 12/12/17.
 */

public class HorizontalProgressBar {
    private ProgressDialog progressBar;
    private int progressBarStatus = 0;

    public HorizontalProgressBar (Context context, String title) {
        progressBar = new ProgressDialog(context);
        progressBar.setCancelable(false);
        progressBar.setMessage(title);
        progressBar.setProgressStyle(ProgressDialog.STYLE_HORIZONTAL);
        progressBar.setProgress(0);
        progressBar.show();

        progressBarStatus = 0;
    }

    public void updateProgressBar(int progress, int total) {
        if (total == 0)
            return;

        progressBarStatus = (progress * 100) / total;
        progressBar.setProgress(progressBarStatus);
    }

    public void dismissHorizontalProgressBar() {
        progressBar.dismiss();
    }
}
