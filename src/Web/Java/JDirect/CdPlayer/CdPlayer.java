/* Copyright (C) 1997 Microsoft Corporation. All rights reserved.
 *
 * This application calls the MCI interface to drive an Audio CD-ROM.
 * Before executing it, make sure there is an Audio CD in the CD drive.
 *
 */


import java.applet.Applet;
import java.awt.*;

public class CdPlayer extends Applet implements Constants {
    public static void main(String args[]) {
        try {
            CdPlayerFrame uiframe = new CdPlayerFrame("CD Player");
            uiframe.setBackground(Color.lightGray);

            // Must show Frame before we size it so insets() will return 
            // valid values
            uiframe.show();
            uiframe.setVisible(false);
            Insets insets = uiframe.insets();
            uiframe.setSize(insets.left + insets.right  + 300,
                            insets.top  + insets.bottom + 100);
            uiframe.show();
        } catch (Exception e) { 
            e.printStackTrace(); 
        }
    }

    public void init() {
        setLayout(new BorderLayout(0, 0));
        setFont(new Font("Dialog", Font.BOLD, 12));
        add("Center", new CdPlayerPanel());
    }
}



class CdPlayerFrame extends Frame implements Constants {
    CdPlayerPanel cdPanel;

    public CdPlayerFrame(String str) {
        super (str);
        setLayout(new BorderLayout(0, 0));
        setFont(new Font("Dialog", Font.BOLD, 12));

        cdPanel = new CdPlayerPanel();
        add("Center", cdPanel);
    }

    public boolean handleEvent(Event evt) {
        switch (evt.id) {
            case Event.WINDOW_DESTROY:
                cdPanel.media.ExitMedia();
                System.exit(0);
                return true;

            default:
                return super.handleEvent(evt);
        }                        
    }
}



class CdPlayerPanel extends Panel implements Constants {
    Button btnStop, btnPlay, btnSkip;
    MediaAccess media; 

    CdPlayerPanel() {

        media = new MediaAccess();

        btnStop = new Button("Stop");
        btnStop.setEnabled(false);

        btnPlay = new Button("Play");

        btnSkip = new Button("Skip");
        btnSkip.setEnabled(false);



        add(btnStop);
        add(btnPlay);
        add(btnSkip);

    }

    public boolean action(Event e, Object arg) {
        if (arg.equals("Stop")) {
            btnStop.setEnabled(false);
            btnPlay.setEnabled(true);
            btnSkip.setEnabled(false);

            media.StopCD();
        }

        if (arg.equals("Play")) {
            btnStop.setEnabled(true);
            btnPlay.setEnabled(false);
            btnSkip.setEnabled(true);

            media.PlayCD(1);
        }

        if (arg.equals("Skip")) {
            int curTrack=media.GetCurrentTrack(), 
                totTracks=media.GetTotalTracks();
        
            if (curTrack == totTracks)
                media.PlayCD(1);
            else
                media.PlayCD(curTrack+1);
        }

        return(false);
    }
}



interface Constants {

    public static final int STOP   = 0;
    public static final int SKIP   = 1;
    public static final int PLAY   = 2;
        

    static final int MCI_OPEN = 0x0803, 
            MCI_SET_TIME_FORMAT = 0x00000400,
            MCI_CLOSE = 0x0804,
            MCI_STOP = 0x0808,
            MCI_PLAY = 0x0806,
            MCI_SET = 0x080D,
            MCI_STATUS = 0x0814,
            MCI_FROM = 0x00000004,
            MCI_OPEN_TYPE = 0x00002000, 
            MCI_OPEN_ELEMENT = 0x00000200,
            MCI_OPEN_ALIAS = 0x00000400,
            MCI_STATUS_ITEM = 0x00000100,
            MCI_TRACK = 0x00000010,
            MCI_CDA_STATUS_TYPE_TRACK = 0x00004001,
            MCI_STATUS_MEDIA_PRESENT = 0x00000005,
            MCI_STATUS_NUMBER_OF_TRACKS = 0x00000003,
            MCI_STATUS_CURRENT_TRACK = 0x00000008,
            MCI_FORMAT_TMSF = 10,
            MCI_OPEN_SHAREABLE = 0x00000100;
}

/** @dll.struct() */
class MCI_SET_PARMS {
    int dwCallback;
    int dwTimeFormat;
    int dwAudio;
}

/** @dll.struct() */
class MCI_STATUS_PARMS {
    int dwCallback;
    int dwReturn;
    int dwItem;
    int dwTrack;
}

/** @dll.struct() */
class MCI_GENERIC_PARMS {
    int dwCallback;
}

/** @dll.struct() */
class MCI_PLAY_PARMS {
    int dwCallback;
    int dwFrom;
    int dwTo;
}

/** @dll.struct() */
class MCI_OPEN_PARMS {
    int dwCallback;
    int wDeviceID;
  
    String lpstrDeviceType;
    String lpstrElementName;
    String lpstrAlias;
}

class MediaAccess implements Constants {
    static MCI_OPEN_PARMS open_parms = new MCI_OPEN_PARMS();
    static int wDeviceID = 0;
    static boolean MediaPlaying = false;

    public MediaAccess() {
        if ((wDeviceID = FindDevice()) < 0) {
            System.out.println("Error: CD-ROM device either not installed or is being used by another application.");
            System.exit(0);
        }
        CloseDevice();
    }

    public static int FindDevice() {
        int iDrive, mciError;

        open_parms.lpstrDeviceType = "cdaudio";
        open_parms.lpstrAlias = "myalias";
        for (iDrive=0; iDrive<26; ++iDrive) {
            Character tChar = new Character((char)('A' + iDrive));
            open_parms.wDeviceID = 0;
            open_parms.lpstrElementName = tChar.toString() + ":";

            mciError = mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE|MCI_OPEN_SHAREABLE|MCI_OPEN_ELEMENT|MCI_OPEN_ALIAS, open_parms);
            if (mciError == 0) {
                return(open_parms.wDeviceID);
            }
        }
        return (-1);
    }

    public static void printMCIError(int mciError) {
        StringBuffer sbuf = new StringBuffer(512);
        boolean flag;

        flag = mciGetErrorString(mciError, sbuf, sbuf.capacity()+1);
        if (flag) System.out.println(sbuf);
        else System.out.println("Call to mciGetErrorString() failed");
    }

    public static boolean SetTimeFormat() {
        int mciError;
        MCI_SET_PARMS set_parms = new MCI_SET_PARMS();
        
        set_parms.dwTimeFormat = MCI_FORMAT_TMSF;
        
        mciError = mciSendCommand(wDeviceID, MCI_SET, MCI_SET_TIME_FORMAT, set_parms);

        if (mciError != 0) {
            printMCIError(mciError);
            return(false);
        }
        return(true);
    }

    public static void ExitMedia() {
        if (MediaPlaying) {
            StopCD();
        }
    }

    public static void CloseDevice() {
        int mciError;

        mciError = mciSendCommand(wDeviceID, MCI_CLOSE, 0, 0);

        if (mciError != 0) {
            printMCIError(mciError);
        }
    }

    public static void OpenDevice() {
        int mciError;

        mciError = mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE|MCI_OPEN_SHAREABLE|MCI_OPEN_ELEMENT|MCI_OPEN_ALIAS, open_parms);
        SetTimeFormat();

        if (mciError != 0) {
            printMCIError(mciError);
        }
    }

    public static int GetTotalTracks() {
        int mciError, dwFlags;
        MCI_STATUS_PARMS status_parms = new MCI_STATUS_PARMS();

        OpenDevice();
        dwFlags = MCI_STATUS_ITEM;
        status_parms.dwItem = MCI_STATUS_NUMBER_OF_TRACKS;

        mciError = mciSendCommand(wDeviceID, MCI_STATUS, dwFlags, status_parms);

        if (mciError != 0) {
            printMCIError(mciError);
            CloseDevice();
            return(0);
        }

        CloseDevice();
        return(status_parms.dwReturn);
    }

    public static int GetCurrentTrack() {
        int mciError, dwFlags;
        MCI_STATUS_PARMS status_parms = new MCI_STATUS_PARMS();

        OpenDevice();
        dwFlags = MCI_STATUS_ITEM;
        status_parms.dwItem = MCI_STATUS_CURRENT_TRACK;

        mciError = mciSendCommand(wDeviceID, MCI_STATUS, dwFlags, status_parms);

        if (mciError != 0) {
            printMCIError(mciError);
            CloseDevice();
            return(0);
        }

        CloseDevice();
        return(status_parms.dwReturn);
    }

    public static void PlayCD (int track) {
        int mciError;
        MCI_PLAY_PARMS play_parms = new MCI_PLAY_PARMS();

        OpenDevice();
        play_parms.dwFrom = track;
        mciError = mciSendCommand(wDeviceID, MCI_PLAY, MCI_FROM, play_parms);

        if (mciError != 0) {
            printMCIError(mciError);
        }
        MediaPlaying = true;

        CloseDevice();
    }

    public static void StopCD () {
        int mciError;
        MCI_GENERIC_PARMS generic_parms = new MCI_GENERIC_PARMS();

        OpenDevice();
        mciError = mciSendCommand(wDeviceID, MCI_STOP, 0, generic_parms);

        if (mciError != 0) {
            printMCIError(mciError);
        }
        MediaPlaying = false;

        CloseDevice();
    }

    /** @dll.import("WINMM") */
    static native int mciSendCommand(int mciId, int uMsg, int dwParam1, MCI_SET_PARMS set_parms);

    /** @dll.import("WINMM") */
    static native int mciSendCommand(int mciId, int uMsg, int dwParam1, MCI_STATUS_PARMS status_parms);

    /** @dll.import("WINMM") */
    static native int mciSendCommand(int mciId, int uMsg, int dwParam1, MCI_PLAY_PARMS play_parms);

    /** @dll.import("WINMM") */
    static native int mciSendCommand(int mciId, int uMsg, int dwParam1, MCI_OPEN_PARMS open_parms);

    /** @dll.import("WINMM") */
    static native int mciSendCommand(int mciId, int uMsg, int dwParam1, MCI_GENERIC_PARMS generic_parms);

    /** @dll.import("WINMM") */
    static native int mciSendCommand(int mciId, int uMsg, int dwParam1, int dwParam2);

    /** @dll.import("WINMM") */
    static native boolean mciGetErrorString(int fdwError, StringBuffer lpstrErrorText, int cchErrorText);
}

