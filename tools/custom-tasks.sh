#!/usr/bin/env bash

export ANDROID_HOME=/opt/android-sdk-linux

# custom tasks for RCS UAPI app
apk add ninja
rm $ANDROID_HOME/cmake/3.6.4111459/bin/ninja
ln -s /usr/bin/ninja $ANDROID_HOME/cmake/3.6.4111459/bin/ninja

# get older NDK and replace it
wget https://dl.google.com/android/repository/android-ndk-r15c-linux-x86_64.zip
unzip android-ndk-r15c-linux-x86_64.zip
rm android-ndk-r15c-linux-x86_64.zip
mv android-ndk-r15c/toolchains/mips64el-linux-android-4.9 $ANDROID_HOME/ndk-bundle/toolchains
mv android-ndk-r15c/toolchains/mipsel-linux-android-4.9 $ANDROID_HOME/ndk-bundle/toolchains
rm -rf android-ndk-r15c
