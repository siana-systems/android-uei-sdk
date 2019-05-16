package uapiwrapper;

/**
 * Created by UEI on 8/3/17.
 */

public class OTATransferStatus {
    public OTAUpgradeStatus status;
    /** Bytes transferred so far */
    public int currentByte;
    /** File size in bytes */
    public int totalBytes;

    public OTATransferStatus(String status, int currentByte, int totalBytes) {
        this.status = OTAUpgradeStatus.valueOf(status);
        this.currentByte = currentByte;
        this.totalBytes = totalBytes;
    }
}
