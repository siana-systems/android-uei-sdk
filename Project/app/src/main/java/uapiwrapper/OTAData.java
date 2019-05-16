package uapiwrapper;

/**
 * Created by UEI on 8/28/17.
 */

public class OTAData {
    public int remoteId;
    /** the data from the remote control */
    public OTATransferStatus remoteData;

    public OTAData(int remoteId, OTATransferStatus remoteData) {
        this.remoteId = remoteId;
        this.remoteData = remoteData;
    }
}
