package com.uei.uapisampleapp.helpers;


/**
 * Created by UEI on 10/9/17.
 */

public class HexHelper {
    public static String getHexStringFromData(byte[] data) {
        final StringBuilder stringBuilder = new StringBuilder(data.length);
        for(byte byteChar: data)
            stringBuilder.append(String.format("%02X", byteChar));
        return stringBuilder.toString().replace(" ", "");
    }

    public static byte[] hexStringToByteArray(String s) {
        int len = s.length();
        if ((len & 1) != 0)
            return new byte[0];

        byte[] data = new byte[len/2];
        for(int i = 0; i < len; i += 2)
            data[i/2] =  (byte) ((Character.digit(s.charAt(i), 16) << 4) + Character.digit(s.charAt(i+1), 16));

        return data;
    }

    public static String appendLengthToHexString(String hexString) {
        Integer length = hexString.length()/2;
        String hexLength = Integer.toHexString(length);
        if (length < 10)
            hexLength = "0" + hexLength;

        return hexLength + hexString;
    }
}
