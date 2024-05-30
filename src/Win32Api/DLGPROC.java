// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


import com.ms.dll.*;

abstract 
public class DLGPROC extends Callback {
	public abstract boolean dlgproc(int hwndDlg, int uMsg, int wParam, int lParam);

	protected boolean callback(int hwndDlg, int uMsg, int wParam, int lParam)
	{
		return dlgproc(hwndDlg, uMsg, wParam, lParam);
	}
}

