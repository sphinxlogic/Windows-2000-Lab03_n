/**
 * Copyright (C) 1997 Microsoft Corporation. All rights reserved.
 *
 *  This application is similar to the GUIDGEN utility which
 *  generates unique guids and puts them on the clipboard.
 *  Unlike GUIDGEN, this version parses the GUID without
 *  braces (useful for pasting into IDL files.)
 *
 *  In addition to showing how to use the "ole" keyword to
 *  assist with Ole's special calling conventions, it shows how
 *  even raw memory access, when necessary, can be made easy
 *  using @dll.import.
 */


import com.ms.dll.*;
import com.ms.com._Guid;


// Use the "auto" linktype on all methods except where specifically
// overridden.
/** @dll.import(auto) */
public class NewGuid
{

    public static void main(String args[])
    {
        _Guid g = CoCreateGuid();
        String text = StringFromIID(g);
        text = text.substring(1);
        text = text.substring(0, text.indexOf("}"));
        System.out.println("Copying \"" + text + "\" to clipboard.");

        int hglobal = GlobalAlloc(GMEM_FIXED|GMEM_DDESHARE,
                                  text.length() + 1);
        if (0 == hglobal) {
            System.err.println("GlobalAlloc failed.");
        }
        int hptr = GlobalLock(hglobal);
        if (0 == hptr) {
            System.err.println("GlobalLock failed.");
        }
        lstrcpyA(hptr, text);
        GlobalUnlock(hglobal);

        if (!OpenClipboard(0)) {
            System.err.println("OpenClipboard failed.");
        }
        try {
            EmptyClipboard();
            if (0 == SetClipboardData(CF_TEXT, hglobal)) {
                System.err.println("SetClipboardData failed.");
            }
        } finally {
            CloseClipboard();
        }

    }



    /** @dll.import("OLE32",ole) */
    static native _Guid CoCreateGuid();

    /** @dll.import("OLE32",ole) */
    static native String StringFromIID(_Guid g);

    /** @dll.import("KERNEL32") */
    static native int GlobalAlloc(int flags, int cb);
    /** @dll.import("KERNEL32") */
    static native int GlobalLock(int hglob);
    /** @dll.import("KERNEL32") */
    static native int GlobalUnlock(int hglob);
    /** @dll.import("KERNEL32", ansi) */
    static native void lstrcpyA(int hptr, String text);

    static final int GMEM_FIXED    = 0;
    static final int GMEM_DDESHARE = 0x2000;


    /** @dll.import("USER32") */
    static native boolean OpenClipboard(int hwnd);
    /** @dll.import("USER32") */
    static native boolean CloseClipboard();
    /** @dll.import("USER32") */
    static native int     SetClipboardData(int fmt, int hData);
    /** @dll.import("USER32") */
    static native boolean EmptyClipboard();

    static final int CF_TEXT = 1;
}




