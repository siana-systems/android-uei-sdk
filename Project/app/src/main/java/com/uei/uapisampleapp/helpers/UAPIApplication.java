package com.uei.uapisampleapp.helpers;

import android.app.Application;
import android.content.Context;

/**
 * Created by UEI on 10/13/17.
 */

public class UAPIApplication extends Application {
    private static Application instance;

    @Override
    public void onCreate() {
        super.onCreate();
        instance = this;
    }

    public static Context getContext() {
        return instance.getApplicationContext();
    }
}
