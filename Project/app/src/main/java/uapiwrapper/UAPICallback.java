package uapiwrapper;

/**
 * Created by UEI on 9/20/17.
 */

public interface UAPICallback {
    void uapiCallback(int remoteid, byte[] data);
}
