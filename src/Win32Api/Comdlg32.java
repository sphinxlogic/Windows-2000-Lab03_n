// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;

/** @security(checkClassLinking=on) */
public class Comdlg32 {
	/** @dll.import("COMDLG32", auto) */
	public native static boolean ChooseColor (CHOOSECOLOR anon0);

	/** @dll.import("COMDLG32",entrypoint="ChooseFont", auto) */
	private native static boolean ChooseFont_I (CHOOSEFONT anon0);

        public static boolean ChooseFont(CHOOSEFONT cf)
        {
            cf.lpszStyle = (cf.lpszStyle == null ? "" : cf.lpszStyle) + new String(new char[300]);
            return ChooseFont_I(cf);
        }

	/** @dll.import("COMDLG32", auto) */
	public native static int CommDlgExtendedError ();

	/** @dll.import("COMDLG32", auto) */
	public native static int FindText (FINDREPLACE anon0);

	/** @dll.import("COMDLG32", auto) */
	public native static short GetFileTitle (String anon0, StringBuffer anon1, short anon2);

	/** @dll.import("COMDLG32", auto, entrypoint="GetOpenFileName") */
	private native static boolean GetOpenFileName_I (OPENFILENAME anon0);

        public static boolean GetOpenFileName (OPENFILENAME ofn)
        {
            ofn.lpstrFile = (ofn.lpstrFile == null ? "" : ofn.lpstrFile) +
                            new String(new char[ofn.nMaxFile]);


            ofn.lpstrFileTitle = new String(new char[ofn.nMaxFileTitle]);


            boolean result = GetOpenFileName_I(ofn);
            return result;
        }


	/** @dll.import("COMDLG32", auto, entrypoint="GetSaveFileName") */
	private native static boolean GetSaveFileName_I (OPENFILENAME anon0);

        public static boolean GetSaveFileName (OPENFILENAME ofn)
        {
            ofn.lpstrFile = (ofn.lpstrFile == null ? "" : ofn.lpstrFile) +
                            new String(new char[ofn.nMaxFile]);


            ofn.lpstrFileTitle = new String(new char[ofn.nMaxFileTitle]);


            boolean result = GetSaveFileName_I(ofn);
            return result;
        }

	/** @dll.import("COMDLG32", auto) */
	public native static boolean PageSetupDlg (PAGESETUPDLG anon0);

	/** @dll.import("COMDLG32", auto) */
	public native static boolean PrintDlg (PRINTDLG anon0);

	/** @dll.import("COMDLG32", auto) */
	public native static int ReplaceText (FINDREPLACE anon0);
}

