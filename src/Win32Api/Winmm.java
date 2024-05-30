// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;

/** @security(checkClassLinking=on) */
public class Winmm {
        /** @dll.import("WINMM",auto) */
        public native static int CloseDriver (int hDriver, int lParam1, int lParam2);

        /** @dll.import("WINMM",auto) */
        public native static int DefDriverProc (int dwDriverIdentifier, int hdrvr, int uMsg, int lParam1, int lParam2);

        /** @dll.import("WINMM",auto) */
        public native static int DrvGetModuleHandle (int hDriver);

        /** @dll.import("WINMM",auto) */
        public native static int GetDriverModuleHandle (int hDriver);

        /** @dll.import("WINMM", auto) */
        public native static int OpenDriver (String szDriverName, String szSectionName, int lParam2);

        /** @dll.import("WINMM", auto) */
        public native static boolean PlaySound (String pszSound, int hmod, int fdwSound);

        /** @dll.import("WINMM",auto) */
        public native static int SendDriverMessage (int hDriver, int message, int lParam1, int lParam2);

        /** @dll.import("WINMM",auto) */
        public native static int auxGetDevCaps (int uDeviceID, AUXCAPS pac, int cbac);

        /** @dll.import("WINMM",auto) */
        public native static int auxGetNumDevs ();

        /** @dll.import("WINMM",auto) */
        public native static int auxGetVolume (int uDeviceID, int[] pdwVolume);

        /** @dll.import("WINMM",auto) */
        public native static int auxOutMessage (int uDeviceID, int uMsg, int dw1, int dw2);

        /** @dll.import("WINMM",auto) */
        public native static int auxSetVolume (int uDeviceID, int dwVolume);

        /** @dll.import("WINMM",auto) */
        public native static int joyGetDevCaps (int uJoyID, JOYCAPS pjc, int cbjc);

        /** @dll.import("WINMM",auto) */
        public native static int joyGetNumDevs ();

        /** @dll.import("WINMM",auto) */
        public native static int joyGetPos (int uJoyID, JOYINFO pji);

        /** @dll.import("WINMM",auto) */
        public native static int joyGetPosEx (int uJoyID, JOYINFOEX pji);

        /** @dll.import("WINMM",auto) */
        public native static int joyGetThreshold (int uJoyID, int[] puThreshold);

        /** @dll.import("WINMM",auto) */
        public native static int joyReleaseCapture (int uJoyID);

        /** @dll.import("WINMM",auto) */
        public native static int joySetCapture (int hwnd, int uJoyID, int uPeriod, boolean fChanged);

        /** @dll.import("WINMM",auto) */
        public native static int joySetThreshold (int uJoyID, int uThreshold);

        /** @dll.import("WINMM",auto) */
        public native static int mciGetCreatorTask (int mciId);

        /** @dll.import("WINMM", auto) */
        public native static int mciGetDeviceIDFromElementID (int dwElementID, String lpstrType);

        /** @dll.import("WINMM", auto) */
        public native static int mciGetDeviceID (String pszDevice);

        /** @dll.import("WINMM", auto) */
        public native static boolean mciGetErrorString (int mcierr, StringBuffer pszText, int cchText);

        /** @dll.import("WINMM",auto) */
        public native static int mciGetYieldProc (int mciId, int[] pdwYieldData);

        /** @dll.import("WINMM",auto) */
        public native static boolean mciExecute (String cmd);

        /** @dll.import("WINMM",auto) */
        public native static int mciSendCommand (int mciId, int uMsg, int dwParam1, int dwParam2);

        /** @dll.import("WINMM",auto) */
        public native static int mciSendCommand (int mciId, int uMsg, int dwParam1, Object dwParam2);

        /** @dll.import("WINMM",auto) */
        public native static int mciSendCommand (int mciId, int uMsg, int dwParam1, byte[] dwParam2);

        /** @dll.import("WINMM", auto) */
        public native static int mciSendString (String lpstrCommand, StringBuffer lpstrReturnString, int uReturnLength, int hwndCallback);

        /** @dll.import("WINMM",auto) */
        public native static boolean mciSetYieldProc (int mciId, YIELDPROC fpYieldProc, int dwYieldData);

        /** @dll.import("WINMM",auto) */
        public native static int midiConnect (int hmi, int hmo, int pReserved);

        /** @dll.import("WINMM",auto) */
        public native static int midiDisconnect (int hmi, int hmo, int pReserved);

        /** @dll.import("WINMM",auto) */
        public native static int midiInAddBuffer (int hmi, MIDIHDR pmh, int cbmh);

        /** @dll.import("WINMM",auto) */
        public native static int midiInClose (int hmi);

        /** @dll.import("WINMM",auto) */
        public native static int midiInGetDevCaps (int uDeviceID, MIDIINCAPS pmic, int cbmic);

        /** @dll.import("WINMM", auto) */
        public native static int midiInGetErrorText (int mmrError, StringBuffer pszText, int cchText);

        /** @dll.import("WINMM",auto) */
        public native static int midiInGetID (int hmi, int[] puDeviceID);

        /** @dll.import("WINMM",auto) */
        public native static int midiInGetNumDevs ();

        /** @dll.import("WINMM",auto) */
        public native static int midiInMessage (int hmi, int uMsg, int dw1, int dw2);

        /** @dll.import("WINMM",auto) */
        public native static int midiInOpen (int phmi[], int uDeviceID, int dwCallback, int dwInstance, int fdwOpen);

        /** @dll.import("WINMM",auto) */
        public native static int midiInPrepareHeader (int hmi, MIDIHDR pmh, int cbmh);

        /** @dll.import("WINMM",auto) */
        public native static int midiInReset (int hmi);

        /** @dll.import("WINMM",auto) */
        public native static int midiInStart (int hmi);

        /** @dll.import("WINMM",auto) */
        public native static int midiInStop (int hmi);

        /** @dll.import("WINMM",auto) */
        public native static int midiInUnprepareHeader (int hmi, MIDIHDR pmh, int cbmh);

        /** @dll.import("WINMM",auto) */
        public native static int midiOutCacheDrumPatches (int hmo, int uPatch, short[] pwkya, int fuCache);

        /** @dll.import("WINMM",auto) */
        public native static int midiOutCachePatches (int hmo, int uBank, short[] pwpa, int fuCache);

        /** @dll.import("WINMM",auto) */
        public native static int midiOutClose (int hmo);

        /** @dll.import("WINMM",auto) */
        public native static int midiOutGetDevCaps (int uDeviceID, MIDIOUTCAPS pmoc, int cbmoc);

        /** @dll.import("WINMM", auto) */
        public native static int midiOutGetErrorText (int mmrError, StringBuffer pszText, int cchText);

        /** @dll.import("WINMM",auto) */
        public native static int midiOutGetID (int hmo, int[] puDeviceID);

        /** @dll.import("WINMM",auto) */
        public native static int midiOutGetNumDevs ();

        /** @dll.import("WINMM",auto) */
        public native static int midiOutGetVolume (int hmo, int[] pdwVolume);

        /** @dll.import("WINMM",auto) */
        public native static int midiOutLongMsg (int hmo, MIDIHDR pmh, int cbmh);

        /** @dll.import("WINMM",auto) */
        public native static int midiOutMessage (int hmo, int uMsg, int dw1, int dw2);

        /** @dll.import("WINMM",auto) */
        public native static int midiOutOpen (int phmo[], int uDeviceID, int dwCallback, int dwInstance, int fdwOpen);

        /** @dll.import("WINMM",auto) */
        public native static int midiOutPrepareHeader (int hmo, MIDIHDR pmh, int cbmh);

        /** @dll.import("WINMM",auto) */
        public native static int midiOutReset (int hmo);

        /** @dll.import("WINMM",auto) */
        public native static int midiOutSetVolume (int hmo, int dwVolume);

        /** @dll.import("WINMM",auto) */
        public native static int midiOutShortMsg (int hmo, int dwMsg);

        /** @dll.import("WINMM",auto) */
        public native static int midiOutUnprepareHeader (int hmo, MIDIHDR pmh, int cbmh);

        /** @dll.import("WINMM",auto) */
        public native static int midiStreamClose (int hms);

        /** @dll.import("WINMM",auto) */
        public native static int midiStreamOpen (int phms[], int[] puDeviceID, int cMidi, int dwCallback, int dwInstance, int fdwOpen);

        /** @dll.import("WINMM",auto) */
        public native static int midiStreamOut (int hms, MIDIHDR pmh, int cbmh);

        /** @dll.import("WINMM",auto) */
        public native static int midiStreamPause (int hms);


        /** @dll.import("WINMM",auto) */
        public native static int midiStreamProperty (int hms, Object lppropdata, int dwProperty);

        /** @dll.import("WINMM",auto) */
        public native static int midiStreamRestart (int hms);

        /** @dll.import("WINMM",auto) */
        public native static int midiStreamStop (int hms);

        /** @dll.import("WINMM",auto) */
        public native static int mixerClose (int hmx);

        /** @dll.import("WINMM",auto) */
        public native static int mixerGetDevCaps (int uMxId, MIXERCAPS pmxcaps, int cbmxcaps);

        /** @dll.import("WINMM",auto) */
        public native static int mixerGetID (int hmxobj, int[] puMxId, int fdwId);

        /** @dll.import("WINMM",auto) */
        public native static int mixerGetLineInfo (int hmxobj, MIXERLINE pmxl, int fdwInfo);

        /** @dll.import("WINMM",auto) */
        public native static int mixerGetNumDevs ();

        /** @dll.import("WINMM",auto) */
        public native static int mixerMessage (int hmx, int uMsg, int dwParam1, int dwParam2);

        /** @dll.import("WINMM",auto) */
        public native static int mixerOpen (int phmx[], int uMxId, int dwCallback, int dwInstance, int fdwOpen);


        /** @dll.import("WINMM",auto) */
        public native static int mmioAdvance (int hmmio, MMIOINFO pmmioinfo, int fuAdvance);

        /** @dll.import("WINMM",auto) */
        public native static int mmioAscend (int hmmio, MMCKINFO pmmcki, int fuAscend);

        /** @dll.import("WINMM",auto) */
        public native static int mmioClose (int hmmio, int fuClose);

        /** @dll.import("WINMM",auto) */
        public native static int mmioCreateChunk (int hmmio, MMCKINFO pmmcki, int fuCreate);

        /** @dll.import("WINMM",auto) */
        public native static int mmioDescend (int hmmio, MMCKINFO pmmcki, MMCKINFO pmmckiParent, int fuDescend);

        /** @dll.import("WINMM",auto) */
        public native static int mmioFlush (int hmmio, int fuFlush);

        /** @dll.import("WINMM",auto) */
        public native static int mmioGetInfo (int hmmio, MMIOINFO pmmioinfo, int fuInfo);

        /** @dll.import("WINMM",auto) */
        public native static int mmioInstallIOProc (int fccIOProc, LPMMIOPROC pIOProc, int dwFlags);

        /** @dll.import("WINMM", auto) */
        public native static int mmioOpen (String pszFileName, MMIOINFO pmmioinfo, int fdwOpen);

        /** @dll.import("WINMM",auto) */
        public native static int mmioRead (int hmmio, byte[] pch, int cch);

        /** @dll.import("WINMM", auto) */
        public native static int mmioRename (String pszFileName, String pszNewFileName, MMIOINFO pmmioinfo, int fdwRename);

        /** @dll.import("WINMM",auto) */
        public native static int mmioSeek (int hmmio, int lOffset, int iOrigin);

        /** @dll.import("WINMM",auto) */
        public native static int mmioSendMessage (int hmmio, int uMsg, int lParam1, int lParam2);

        /** @dll.import("WINMM", ansi) */
        public native static int mmioSetBuffer (int hmmio, int pchBuffer, int cchBuffer, int fuBuffer);

        /** @dll.import("WINMM",auto) */
        public native static int mmioSetInfo (int hmmio, MMIOINFO pmmioinfo, int fuInfo);

        /** @dll.import("WINMM", auto) */
        public native static int mmioStringToFOURCC (String sz, int uFlags);

        /** @dll.import("WINMM",auto) */
        public native static int mmioWrite (int hmmio, byte[] pch, int cch);

        /** @dll.import("WINMM", auto) */
        public native static boolean sndPlaySound (String pszSound, int fuSound);

        /** @dll.import("WINMM",auto) */
        public native static int timeBeginPeriod (int uPeriod);

        /** @dll.import("WINMM",auto) */
        public native static int timeEndPeriod (int uPeriod);

        /** @dll.import("WINMM",auto) */
        public native static int timeGetDevCaps (TIMECAPS ptc, int cbtc);


        /** @dll.import("WINMM",auto) */
        public native static int timeGetTime ();

        /** @dll.import("WINMM",auto) */
        public native static int timeKillEvent (int uTimerID);

        /** @dll.import("WINMM",auto) */
        public native static int timeSetEvent (int uDelay, int uResolution, LPTIMECALLBACK fptc, int dwUser, int fuEvent);

        /** @dll.import("WINMM",auto) */
        public native static int waveInAddBuffer (int hwi, WAVEHDR pwh, int cbwh);

        /** @dll.import("WINMM",auto) */
        public native static int waveInClose (int hwi);

        /** @dll.import("WINMM",auto) */
        public native static int waveInGetDevCaps (int uDeviceID, WAVEINCAPS pwic, int cbwic);

        /** @dll.import("WINMM", auto) */
        public native static int waveInGetErrorText (int mmrError, StringBuffer pszText, int cchText);

        /** @dll.import("WINMM",auto) */
        public native static int waveInGetID (int hwi, int[] puDeviceID);

        /** @dll.import("WINMM",auto) */
        public native static int waveInGetNumDevs ();

        /** @dll.import("WINMM",auto) */
        public native static int waveInMessage (int hwi, int uMsg, int dw1, int dw2);

        /** @dll.import("WINMM",auto) */
        public native static int waveInOpen (int[] phwi, int uDeviceID, WAVEFORMATEX pwfx, int dwCallback, int dwInstance, int fdwOpen);

        /** @dll.import("WINMM",auto) */
        public native static int waveInPrepareHeader (int hwi, WAVEHDR pwh, int cbwh);

        /** @dll.import("WINMM",auto) */
        public native static int waveInReset (int hwi);

        /** @dll.import("WINMM",auto) */
        public native static int waveInStart (int hwi);

        /** @dll.import("WINMM",auto) */
        public native static int waveInStop (int hwi);

        /** @dll.import("WINMM",auto) */
        public native static int waveInUnprepareHeader (int hwi, WAVEHDR pwh, int cbwh);

        /** @dll.import("WINMM",auto) */
        public native static int waveOutBreakLoop (int hwo);

        /** @dll.import("WINMM",auto) */
        public native static int waveOutClose (int hwo);

        /** @dll.import("WINMM",auto) */
        public native static int waveOutGetDevCaps (int uDeviceID, WAVEOUTCAPS pwoc, int cbwoc);

        /** @dll.import("WINMM", auto) */
        public native static int waveOutGetErrorText (int mmrError, StringBuffer pszText, int cchText);

        /** @dll.import("WINMM",auto) */
        public native static int waveOutGetID (int hwo, int[] puDeviceID);

        /** @dll.import("WINMM",auto) */
        public native static int waveOutGetNumDevs ();

        /** @dll.import("WINMM",auto) */
        public native static int waveOutGetPitch (int hwo, int[] pdwPitch);

        /** @dll.import("WINMM",auto) */
        public native static int waveOutGetPlaybackRate (int hwo, int[] pdwRate);

        /** @dll.import("WINMM",auto) */
        public native static int waveOutGetVolume (int hwo, int[] pdwVolume);

        /** @dll.import("WINMM",auto) */
        public native static int waveOutMessage (int hwo, int uMsg, int dw1, int dw2);

        /** @dll.import("WINMM",auto) */
        public native static int waveOutOpen (int[] phwo, int uDeviceID, WAVEFORMATEX pwfx, int dwCallback, int dwInstance, int fdwOpen);

        /** @dll.import("WINMM",auto) */
        public native static int waveOutPause (int hwo);

        /** @dll.import("WINMM",auto) */
        public native static int waveOutPrepareHeader (int hwo, WAVEHDR pwh, int cbwh);

        /** @dll.import("WINMM",auto) */
        public native static int waveOutReset (int hwo);

        /** @dll.import("WINMM",auto) */
        public native static int waveOutRestart (int hwo);

        /** @dll.import("WINMM",auto) */
        public native static int waveOutSetPitch (int hwo, int dwPitch);

        /** @dll.import("WINMM",auto) */
        public native static int waveOutSetPlaybackRate (int hwo, int dwRate);

        /** @dll.import("WINMM",auto) */
        public native static int waveOutSetVolume (int hwo, int dwVolume);

        /** @dll.import("WINMM",auto) */
        public native static int waveOutUnprepareHeader (int hwo, WAVEHDR pwh, int cbwh);

        /** @dll.import("WINMM",auto) */
        public native static int waveOutWrite (int hwo, WAVEHDR pwh, int cbwh);
}

