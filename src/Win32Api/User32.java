// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;

/** @security(checkClassLinking=on) */
public class User32 {
        /** @dll.import("USER32",auto) */
        public native static int ActivateKeyboardLayout (int hkl, int Flags);

        /** @dll.import("USER32",auto) */
        public native static boolean AdjustWindowRect (RECT lpRect, int dwStyle, boolean bMenu);

        /** @dll.import("USER32",auto) */
        public native static boolean AdjustWindowRectEx (RECT lpRect, int dwStyle, boolean bMenu, int dwExStyle);

        /** @dll.import("USER32",auto) */
        public native static boolean AnyPopup ();

        /** @dll.import("USER32", auto) */
        public native static boolean AppendMenu (int hMenu, int uFlags, int uIDNewItem, String lpNewItem);

        /** @dll.import("USER32",auto) */
        public native static int ArrangeIconicWindows (int hWnd);

        /** @dll.import("USER32",auto) */
        public native static boolean AttachThreadInput (int idAttach, int idAttachTo, boolean fAttach);

        /** @dll.import("USER32",auto) */
        public native static int BeginDeferWindowPos (int nNumWindows);

        /** @dll.import("USER32",auto) */
        public native static int BeginPaint (int hWnd, PAINTSTRUCT lpPaint);

        /** @dll.import("USER32",auto) */
        public native static boolean BringWindowToTop (int hWnd);

        /** @dll.import("USER32",auto) */
        public native static int BroadcastSystemMessage (int anonymous0, int[] anonymous1, int anonymous2, int anonymous3, int anonymous4);

        /** @dll.import("USER32",auto) */
        public native static boolean CallMsgFilter (MSG lpMsg, int nCode);

        /** @dll.import("USER32",auto) */
        public native static int CallWindowProc (int lpPrevWndFunc, int hWnd, int Msg, int wParam, int lParam);

        /** @dll.import("USER32",auto) */
        public native static short CascadeWindows (int hwndParent, int wHow, RECT lpRect, int cKids, int[] lpKids);

        /** @dll.import("USER32",auto) */
        public native static boolean ChangeClipboardChain (int hWndRemove, int hWndNewNext);

        /** @dll.import("USER32", auto) */
        public native static int ChangeDisplaySettingsEx (String lpszDeviceName, DEVMODE lpDevMode, int hwnd, int dwflags, int lParam);

        /** @dll.import("USER32",auto) */
        public native static int ChangeDisplaySettings (DEVMODE lpDevMode, int dwFlags);

        /** @dll.import("USER32", auto) */
        public native static boolean ChangeMenu (int hMenu, int cmd, String lpszNewItem, int cmdInsert, int flags);

        /** @dll.import("USER32", auto) */
        public native static int CharLowerBuff (StringBuffer lpsz, int cchLength);

        /** @dll.import("USER32", auto) */
        public native static int CharLower (StringBuffer lpsz);

        /** @dll.import("USER32", ansi) */
        public native static int CharNextExA (short CodePage, int lpCurrentChar, int dwFlags);

        /** @dll.import("USER32", auto) */
        public native static int CharNext (int lpsz);

        /** @dll.import("USER32", ansi) */
        public native static int CharPrevExA (short CodePage, int lpStart, int lpCurrentChar, int dwFlags);

        /** @dll.import("USER32", auto) */
        public native static int CharPrev (int lpszStart, int lpszCurrent);

        /** @dll.import("USER32", ansi) */
        public native static boolean CharToOemBuff (String lpszSrc, StringBuffer lpszDst, int cchDstLength);

        /** @dll.import("USER32", ansi) */
        public native static boolean CharToOem (String lpszSrc, StringBuffer lpszDst);

        /** @dll.import("USER32", auto) */
        public native static int CharUpperBuff (StringBuffer lpsz, int cchLength);

        /** @dll.import("USER32", auto) */
        public native static int CharUpper (StringBuffer lpsz);

        /** @dll.import("USER32",auto) */
        public native static boolean CheckDlgButton (int hDlg, int nIDButton, int uCheck);

        /** @dll.import("USER32",auto) */
        public native static int CheckMenuItem (int hMenu, int uIDCheckItem, int uCheck);

        /** @dll.import("USER32",auto) */
        public native static boolean CheckMenuRadioItem (int anonymous0, int anonymous1, int anonymous2, int anonymous3, int anonymous4);

        /** @dll.import("USER32",auto) */
        public native static boolean CheckRadioButton (int hDlg, int nIDFirstButton, int nIDLastButton, int nIDCheckButton);

        /** @dll.import("USER32",entrypoint="ChildWindowFromPoint") */
        private native static int ChildWindowFromPoint_I (int hWndParent, int Point_x, int Point_y);

        public static int ChildWindowFromPoint (int hWndParent, POINT pt)
		{
		   return ChildWindowFromPoint_I(hWndParent, pt.x, pt.y);
		}

        /** @dll.import("USER32",entrypoint="ChildWindowFromPointEx") */
        private native static int ChildWindowFromPointEx_I (int hWndParent, int Point_x, int Point_y, int uFlags);

        public static int ChildWindowFromPointEx (int hWndParent, POINT pt, int uFlags)
		{
		   return ChildWindowFromPointEx_I(hWndParent, pt.x, pt.y, uFlags);
		}

        /** @dll.import("USER32",auto) */
        public native static boolean ClientToScreen (int hWnd, POINT lpPoint);

        /** @dll.import("USER32",auto) */
        public native static boolean ClipCursor (RECT lpRect);

        /** @dll.import("USER32",auto) */
        public native static boolean CloseClipboard ();

        /** @dll.import("USER32",auto) */
        public native static boolean CloseDesktop (int hDesktop);

        /** @dll.import("USER32",auto) */
        public native static boolean CloseWindow (int hWnd);

        /** @dll.import("USER32",auto) */
        public native static boolean CloseWindowStation (int hWinSta);

        /** @dll.import("USER32",auto) */
        public native static int CopyAcceleratorTable (int hAccelSrc, ACCEL lpAccelDst, int cAccelEntries);

        /** @dll.import("USER32",auto) */
        public native static int CopyIcon (int hIcon);

        /** @dll.import("USER32",auto) */
        public native static int CopyImage (int anonymous0, int anonymous1, int anonymous2, int anonymous3, int anonymous4);

        /** @dll.import("USER32",auto) */
        public native static boolean CopyRect (RECT lprcDst, RECT lprcSrc);

        /** @dll.import("USER32",auto) */
        public native static int CountClipboardFormats ();

        /** @dll.import("USER32",auto) */
        public native static int CreateAcceleratorTable (ACCEL anonymous0, int anonymous1);

        /** @dll.import("USER32",auto) */
        public native static boolean CreateCaret (int hWnd, int hBitmap, int nWidth, int nHeight);

        /** @dll.import("USER32",auto) */
        public native static int CreateCursor (int hInst, int xHotSpot, int yHotSpot, int nWidth, int nHeight, byte[] pvANDPlane, byte[] pvXORPlane);

        /** @dll.import("USER32", auto) */
        public native static int CreateDesktop (String lpszDesktop, String lpszDevice, DEVMODE pDevmode, int dwFlags, int dwDesiredAccess, SECURITY_ATTRIBUTES lpsa);

        /** @dll.import("USER32",auto) */
        public native static int CreateDialogIndirectParam (int hInstance, DLGTEMPLATE lpTemplate, int hWndParent, DLGPROC lpDialogFunc, int dwInitParam);

        /** @dll.import("USER32", auto) */
        public native static int CreateDialogParam (int hInstance, String lpTemplateName, int hWndParent, DLGPROC lpDialogFunc, int dwInitParam);

        /** @dll.import("USER32",auto) */
        public native static int CreateIcon (int hInstance, int nWidth, int nHeight, byte cPlanes, byte cBitsPixel, byte[] lpbANDbits, byte[] lpbXORbits);

        /** @dll.import("USER32",auto) */
        public native static int CreateIconFromResource (Object presbits, int dwResSize, boolean fIcon, int dwVer);

        /** @dll.import("USER32",auto) */
        public native static int CreateIconFromResourceEx (Object presbits, int dwResSize, boolean fIcon, int dwVer, int cxDesired, int cyDesired, int Flags);

        /** @dll.import("USER32",auto) */
        public native static int CreateIconIndirect (ICONINFO piconinfo);

        /** @dll.import("USER32", auto) */
        public native static int CreateMDIWindow (String lpClassName, String lpWindowName, int dwStyle, int X, int Y, int nWidth, int nHeight, int hWndParent, int hInstance, int lParam);

        /** @dll.import("USER32",auto) */
        public native static int CreateMenu ();

        /** @dll.import("USER32",auto) */
        public native static int CreatePopupMenu ();

        public static int CreateWindow(String lpszClassName,
                                       String lpszWindowName,
                                       int    style,
                                       int    x,
                                       int    y,
                                       int    nWidth,
                                       int    nHeight,
                                       int    hwndParent,
                                       int    hMenu,
                                       int    hInst,
                                       int    pvParam)
        {
                return CreateWindowEx(0, lpszClassName, lpszWindowName, style,
                                      x, y, nWidth, nHeight, hwndParent, hMenu, hInst,
                                      pvParam);
        }


                /** @dll.import("USER32", auto) */
        public native static int CreateWindowEx (int dwExStyle, String lpClassName, String lpWindowName, int dwStyle, int X, int Y, int nWidth, int nHeight, int hWndParent, int hMenu, int hInstance, int lpParam);

        /** @dll.import("USER32", auto) */
        public native static int CreateWindowStation (String lpwinsta, int dwReserved, int dwDesiredAccess, SECURITY_ATTRIBUTES lpsa);

        /** @dll.import("USER32",auto) */
        public native static int DefDlgProc (int hDlg, int Msg, int wParam, int lParam);

        /** @dll.import("USER32",auto) */
        public native static int DefFrameProc (int hWnd, int hWndMDIClient, int uMsg, int wParam, int lParam);

        /** @dll.import("USER32",auto) */
        public native static int DefMDIChildProc (int hWnd, int uMsg, int wParam, int lParam);

        /** @dll.import("USER32",auto) */
        public native static int DefWindowProc (int hWnd, int Msg, int wParam, int lParam);

        /** @dll.import("USER32",auto) */
        public native static int DeferWindowPos (int hWinPosInfo, int hWnd, int hWndInsertAfter, int x, int y, int cx, int cy, int uFlags);

        /** @dll.import("USER32",auto) */
        public native static boolean DeleteMenu (int hMenu, int uPosition, int uFlags);

        /** @dll.import("USER32",auto) */
        public native static boolean DestroyAcceleratorTable (int hAccel);

        /** @dll.import("USER32",auto) */
        public native static boolean DestroyCaret ();

        /** @dll.import("USER32",auto) */
        public native static boolean DestroyCursor (int hCursor);

        /** @dll.import("USER32",auto) */
        public native static boolean DestroyIcon (int hIcon);

        /** @dll.import("USER32",auto) */
        public native static boolean DestroyMenu (int hMenu);

        /** @dll.import("USER32",auto) */
        public native static boolean DestroyWindow (int hWnd);

        /** @dll.import("USER32",auto) */
        public native static int DialogBoxIndirectParam (int hInstance, DLGTEMPLATE hDialogTemplate, int hWndParent, DLGPROC lpDialogFunc, int dwInitParam);

        /** @dll.import("USER32", auto) */
        public native static int DialogBoxParam (int hInstance, String lpTemplateName, int hWndParent, DLGPROC lpDialogFunc, int dwInitParam);

        /** @dll.import("USER32",auto) */
        public native static int DispatchMessage (MSG lpMsg);

        /** @dll.import("USER32", auto) */
        public native static int DlgDirListComboBox (int hDlg, StringBuffer lpPathSpec, int nIDComboBox, int nIDStaticPath, int uFiletype);

        /** @dll.import("USER32", auto) */
        public native static int DlgDirList (int hDlg, StringBuffer lpPathSpec, int nIDListBox, int nIDStaticPath, int uFileType);

        /** @dll.import("USER32", auto) */
        public native static boolean DlgDirSelectComboBoxEx (int hDlg, StringBuffer lpString, int nCount, int nIDComboBox);

        /** @dll.import("USER32", auto) */
        public native static boolean DlgDirSelectEx (int hDlg, StringBuffer lpString, int nCount, int nIDListBox);

        /** @dll.import("USER32",entrypoint="DragDetect") */
        private native static boolean DragDetect_I (int hWnd, int Point_x, int Point_y);
		  
        public static boolean DragDetect (int hWnd, POINT p)
		{
		   return DragDetect_I(hWnd, p.x, p.y);
		}

        /** @dll.import("USER32",auto) */
        public native static int DragObject (int anonymous0, int anonymous1, int anonymous2, int anonymous3, int anonymous4);

        /** @dll.import("USER32",auto) */
        public native static boolean DrawAnimatedRects (int hwnd, int idAni, RECT lprcFrom, RECT lprcTo);

        /** @dll.import("USER32",auto) */
        public native static boolean DrawCaption (int anonymous0, int anonymous1, RECT anonymous2, int anonymous3);

        /** @dll.import("USER32",auto) */
        public native static boolean DrawEdge (int hdc, RECT qrc, int edge, int grfFlags);

        /** @dll.import("USER32",auto) */
        public native static boolean DrawFocusRect (int hDC, RECT lprc);

        /** @dll.import("USER32",auto) */
        public native static boolean DrawFrameControl (int anonymous0, RECT anonymous1, int anonymous2, int anonymous3);

        /** @dll.import("USER32",auto) */
        public native static boolean DrawIcon (int hDC, int X, int Y, int hIcon);

        /** @dll.import("USER32",auto) */
        public native static boolean DrawIconEx (int hdc, int xLeft, int yTop, int hIcon, int cxWidth, int cyWidth, int istepIfAniCur, int hbrFlickerFreeDraw, int diFlags);

        /** @dll.import("USER32",auto) */
        public native static boolean DrawMenuBar (int hWnd);

        /** @dll.import("USER32",auto) */
        public native static boolean DrawState (int hdc, int hbr, DRAWSTATEPROC lpOutputFunc, int lData, int wData, int x, int y, int cx, int cy, int fuFlags);

        /** @dll.import("USER32", auto) */
        public native static int DrawTextEx (int anonymous0, String anonymous1, int anonymous2, RECT anonymous3, int anonymous4, DRAWTEXTPARAMS anonymous5);

        /** @dll.import("USER32", auto) */
        public native static int DrawText (int hDC, String lpString, int nCount, RECT lpRect, int uFormat);

        /** @dll.import("USER32",auto) */
        public native static boolean EmptyClipboard ();

        /** @dll.import("USER32",auto) */
        public native static boolean EnableMenuItem (int hMenu, int uIDEnableItem, int uEnable);

        /** @dll.import("USER32",auto) */
        public native static boolean EnableScrollBar (int hWnd, int wSBflags, int wArrows);

        /** @dll.import("USER32",auto) */
        public native static boolean EnableWindow (int hWnd, boolean bEnable);

        /** @dll.import("USER32",auto) */
        public native static boolean EndDeferWindowPos (int hWinPosInfo);

        /** @dll.import("USER32",auto) */
        public native static boolean EndDialog (int hDlg, int nResult);

        /** @dll.import("USER32",auto) */
        public native static boolean EndPaint (int hWnd, PAINTSTRUCT lpPaint);

        /** @dll.import("USER32",auto) */
        public native static boolean EnumChildWindows (int hWndParent, WNDENUMPROC lpEnumFunc, int lParam);

        /** @dll.import("USER32",auto) */
        public native static int EnumClipboardFormats (int format);

        /** @dll.import("USER32",auto) */
        public native static boolean EnumDesktopWindows (int hDesktop, WNDENUMPROC lpfn, int lParam);

        /** @dll.import("USER32",auto) */
        public native static boolean EnumDesktops (int hwinsta, DESKTOPENUMPROC lpEnumFunc, int lParam);

        /** @dll.import("USER32", auto) */
        public native static boolean EnumDisplaySettings (String lpszDeviceName, int iModeNum, DEVMODE lpDevMode);

        /** @dll.import("USER32",auto) */
        public native static int EnumPropsEx (int hWnd, PROPENUMPROCEX lpEnumFunc, int lParam);

        /** @dll.import("USER32",auto) */
        public native static int EnumProps (int hWnd, PROPENUMPROC lpEnumFunc);

        /** @dll.import("USER32",auto) */
        public native static boolean EnumThreadWindows (int dwThreadId, WNDENUMPROC lpfn, int lParam);

        /** @dll.import("USER32",auto) */
        public native static boolean EnumWindowStations (WINSTAENUMPROC lpEnumFunc, int lParam);

        /** @dll.import("USER32",auto) */
        public native static boolean EnumWindows (WNDENUMPROC lpEnumFunc, int lParam);

        /** @dll.import("USER32",auto) */
        public native static boolean EqualRect (RECT lprc1, RECT lprc2);

        /** @dll.import("USER32",auto) */
        public native static int ExcludeUpdateRgn (int hDC, int hWnd);

        /** @dll.import("USER32",auto) */
        public native static boolean ExitWindowsEx (int uFlags, int dwReserved);

        /** @dll.import("USER32",auto) */
        public native static int FillRect (int hDC, RECT lprc, int hbr);

        /** @dll.import("USER32", auto) */
        public native static int FindWindowEx (int anonymous0, int anonymous1, String anonymous2, String anonymous3);

        /** @dll.import("USER32", auto) */
        public native static int FindWindow (String lpClassName, String lpWindowName);

        /** @dll.import("USER32",auto) */
        public native static boolean FlashWindow (int hWnd, boolean bInvert);

        /** @dll.import("USER32",auto) */
        public native static int FrameRect (int hDC, RECT lprc, int hbr);

        /** @dll.import("USER32",auto) */
        public native static int GetActiveWindow ();

        /** @dll.import("USER32",auto) */
        public native static short GetAsyncKeyState (int vKey);

        /** @dll.import("USER32",auto) */
        public native static int GetCapture ();

        /** @dll.import("USER32",auto) */
        public native static int GetCaretBlinkTime ();

        /** @dll.import("USER32",auto) */
        public native static boolean GetCaretPos (POINT lpPoint);

        /** @dll.import("USER32", auto, entrypoint="GetClassInfoEx") */
        private native static boolean GetClassInfoEx_I (int hInstance, String lpszClass, WNDCLASSEX_I lpwcxi);

        public static boolean GetClassInfoEx (int hInstance, String lpszClass, WNDCLASSEX lpwcx)
		  {
			  WNDCLASSEX_I wcx = new WNDCLASSEX_I();
			  wcx.cbSize = com.ms.dll.DllLib.sizeOf(wcx);
			  boolean r = GetClassInfoEx_I(hInstance, lpszClass, wcx);
			  lpwcx.style = wcx.style;
			  lpwcx.lpfnWndProc = wcx.lpfnWndProc;
			  lpwcx.cbClsExtra = wcx.cbClsExtra;
			  lpwcx.cbWndExtra = wcx.cbWndExtra;
			  lpwcx.hInstance = wcx.hInstance;
			  lpwcx.hIcon = wcx.hIcon;
			  lpwcx.hCursor = wcx.hCursor;
			  lpwcx.hbrBackground = wcx.hbrBackground;
			  lpwcx.lpszMenuName = com.ms.dll.DllLib.ptrToString(wcx.lpszMenuName);
			  lpwcx.lpszClassName = com.ms.dll.DllLib.ptrToString(wcx.lpszClassName);
			  lpwcx.hIconSm = wcx.hIconSm;
			  return r;
		  }

        /** @dll.import("USER32", auto, entrypoint="GetClassInfo") */
        private native static boolean GetClassInfo_I (int hInstance, String lpszClass, WNDCLASS_I lpWndClassi);

        public static boolean GetClassInfo (int hInstance, String lpszClass, WNDCLASS lpWndClass)
		  {
			  WNDCLASS_I wc = new WNDCLASS_I();
			  boolean r = GetClassInfo_I(hInstance, lpszClass, wc);
			  lpWndClass.style = wc.style;
			  lpWndClass.lpfnWndProc = wc.lpfnWndProc;
			  lpWndClass.cbClsExtra = wc.cbClsExtra;
			  lpWndClass.cbWndExtra = wc.cbWndExtra;
			  lpWndClass.hInstance = wc.hInstance;
			  lpWndClass.hIcon = wc.hIcon;
			  lpWndClass.hCursor = wc.hCursor;
			  lpWndClass.hbrBackground = wc.hbrBackground;
			  lpWndClass.lpszMenuName = com.ms.dll.DllLib.ptrToString(wc.lpszMenuName);
			  lpWndClass.lpszClassName = com.ms.dll.DllLib.ptrToString(wc.lpszClassName);
			  return r;
		  }

        /** @dll.import("USER32",auto) */
        public native static int GetClassLong (int hWnd, int nIndex);

        /** @dll.import("USER32", auto) */
        public native static int GetClassName (int hWnd, StringBuffer lpClassName, int nMaxCount);

        /** @dll.import("USER32",auto) */
        public native static short GetClassWord (int hWnd, int nIndex);

        /** @dll.import("USER32",auto) */
        public native static boolean GetClientRect (int hWnd, RECT lpRect);

        /** @dll.import("USER32",auto) */
        public native static boolean GetClipCursor (RECT lpRect);

        /** @dll.import("USER32",auto) */
        public native static int GetClipboardData (int uFormat);

        /** @dll.import("USER32", auto) */
        public native static int GetClipboardFormatName (int format, StringBuffer lpszFormatName, int cchMaxCount);

        /** @dll.import("USER32",auto) */
        public native static int GetClipboardOwner ();

        /** @dll.import("USER32",auto) */
        public native static int GetClipboardViewer ();

        /** @dll.import("USER32",auto) */
        public native static int GetCursor ();

        /** @dll.import("USER32",auto) */
        public native static boolean GetCursorPos (POINT lpPoint);

        /** @dll.import("USER32",auto) */
        public native static int GetDC (int hWnd);

        /** @dll.import("USER32",auto) */
        public native static int GetDCEx (int hWnd, int hrgnClip, int flags);

        /** @dll.import("USER32",auto) */
        public native static int GetDesktopWindow ();

        /** @dll.import("USER32",auto) */
        public native static int GetDialogBaseUnits ();

        /** @dll.import("USER32",auto) */
        public native static int GetDlgCtrlID (int hWnd);

        /** @dll.import("USER32",auto) */
        public native static int GetDlgItem (int hDlg, int nIDDlgItem);

        /** @dll.import("USER32",auto) */
        public native static int GetDlgItemInt (int hDlg, int nIDDlgItem, boolean[] lpTranslated, boolean bSigned);

        /** @dll.import("USER32", auto) */
        public native static int GetDlgItemText (int hDlg, int nIDDlgItem, StringBuffer lpString, int nMaxCount);

        /** @dll.import("USER32",auto) */
        public native static int GetDoubleClickTime ();

        /** @dll.import("USER32",auto) */
        public native static int GetFocus ();

        /** @dll.import("USER32",auto) */
        public native static int GetForegroundWindow ();

        /** @dll.import("USER32",auto) */
        public native static boolean GetIconInfo (int hIcon, ICONINFO piconinfo);

        /** @dll.import("USER32",auto) */
        public native static boolean GetInputState ();

        /** @dll.import("USER32",auto) */
        public native static int GetKBCodePage ();

        /** @dll.import("USER32", auto) */
        public native static int GetKeyNameText (int lParam, StringBuffer lpString, int nSize);

        /** @dll.import("USER32",auto) */
        public native static short GetKeyState (int nVirtKey);

        /** @dll.import("USER32",auto) */
        public native static int GetKeyboardLayout (int dwLayout);

        /** @dll.import("USER32",auto) */
        public native static int GetKeyboardLayoutList (int nBuff, int[] lpList);

        /** @dll.import("USER32", auto) */
        public native static boolean GetKeyboardLayoutName (StringBuffer pwszKLID);

        /** @dll.import("USER32",auto) */
        public native static boolean GetKeyboardState (byte[] lpKeyState);

        /** @dll.import("USER32",auto) */
        public native static int GetKeyboardType (int nTypeFlag);

        /** @dll.import("USER32",auto) */
        public native static int GetLastActivePopup (int hWnd);

        /** @dll.import("USER32",auto) */
        public native static int GetMenu (int hWnd);

        /** @dll.import("USER32",auto) */
        public native static int GetMenuCheckMarkDimensions ();

        /** @dll.import("USER32",auto) */
        public native static int GetMenuContextHelpId (int anonymous0);

        /** @dll.import("USER32",auto) */
        public native static int GetMenuDefaultItem (int hMenu, int fByPos, int gmdiFlags);

        /** @dll.import("USER32",auto) */
        public native static int GetMenuItemCount (int hMenu);

        /** @dll.import("USER32",auto) */
        public native static int GetMenuItemID (int hMenu, int nPos);

        /** @dll.import("USER32",auto) */
        public native static boolean GetMenuItemInfo (int anonymous0, int anonymous1, boolean anonymous2, MENUITEMINFO anonymous3);

        /** @dll.import("USER32",auto) */
        public native static boolean GetMenuItemRect (int hWnd, int hMenu, int uItem, RECT lprcItem);

        /** @dll.import("USER32",auto) */
        public native static int GetMenuState (int hMenu, int uId, int uFlags);

        /** @dll.import("USER32", auto) */
        public native static int GetMenuString (int hMenu, int uIDItem, StringBuffer lpString, int nMaxCount, int uFlag);

        /** @dll.import("USER32",auto) */
        public native static int GetMessageExtraInfo ();

        /** @dll.import("USER32",auto) */
        public native static int GetMessagePos ();

        /** @dll.import("USER32",auto) */
        public native static int GetMessageTime ();

        /** @dll.import("USER32",auto,entrypoint="GetMessage") */
        private native static int GetMessage_I (MSG lpMsg, int hWnd, int wMsgFilterMin, int wMsgFilterMax);

        public static boolean GetMessage (MSG lpMsg, int hWnd, int wMsgFilterMin, int wMsgFilterMax)
        {
           int result = GetMessage_I(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax);
           if (result == -1) {
               throw new IllegalArgumentException("GetMessage returned error code.");
           }
           return result != 0;
        }

        /** @dll.import("USER32",auto) */
        public native static int GetNextDlgGroupItem (int hDlg, int hCtl, boolean bPrevious);

        /** @dll.import("USER32",auto) */
        public native static int GetNextDlgTabItem (int hDlg, int hCtl, boolean bPrevious);

        /** @dll.import("USER32",auto) */
        public native static int GetOpenClipboardWindow ();

        /** @dll.import("USER32",auto) */
        public native static int GetParent (int hWnd);

        /** @dll.import("USER32",auto) */
        public native static int GetPriorityClipboardFormat (int[] paFormatPriorityList, int cFormats);

        /** @dll.import("USER32", auto) */
        public native static int GetProp (int hWnd, String lpString);

        /** @dll.import("USER32",auto) */
        public native static int GetQueueStatus (int flags);

        /** @dll.import("USER32",auto) */
        public native static boolean GetScrollInfo (int anonymous0, int anonymous1, SCROLLINFO anonymous2);

        /** @dll.import("USER32",auto) */
        public native static int GetScrollPos (int hWnd, int nBar);

        /** @dll.import("USER32",auto) */
        public native static boolean GetScrollRange (int hWnd, int nBar, int[] lpMinPos, int[] lpMaxPos);

        /** @dll.import("USER32",auto) */
        public native static int GetSubMenu (int hMenu, int nPos);

        /** @dll.import("USER32",auto) */
        public native static int GetSysColor (int nIndex);

        /** @dll.import("USER32",auto) */
        public native static int GetSysColorBrush (int nIndex);

        /** @dll.import("USER32",auto) */
        public native static int GetSystemMenu (int hWnd, boolean bRevert);

        /** @dll.import("USER32",auto) */
        public native static int GetSystemMetrics (int nIndex);

        /** @dll.import("USER32", auto) */
        public native static int GetTabbedTextExtent (int hDC, String lpString, int nCount, int nTabPositions, int[] lpnTabStopPositions);

        /** @dll.import("USER32",auto) */
        public native static int GetTopWindow (int hWnd);

        /** @dll.import("USER32",auto) */
        public native static boolean GetUpdateRect (int hWnd, RECT lpRect, boolean bErase);

        /** @dll.import("USER32",auto) */
        public native static int GetUpdateRgn (int hWnd, int hRgn, boolean bErase);

        /** @dll.import("USER32",auto) */
        public native static boolean GetUserObjectInformation (int hObj, int nIndex, Object pvInfo, int nLength, int[] lpnLengthNeeded);

        /** @dll.import("USER32",auto) */
        public native static int GetWindow (int hWnd, int uCmd);

        /** @dll.import("USER32",auto) */
        public native static int GetWindowContextHelpId (int anonymous0);

        /** @dll.import("USER32",auto) */
        public native static int GetWindowDC (int hWnd);

        /** @dll.import("USER32",auto) */
        public native static int GetWindowLong (int hWnd, int nIndex);

        /** @dll.import("USER32",auto) */
        public native static boolean GetWindowPlacement (int hWnd, WINDOWPLACEMENT lpwndpl);

        /** @dll.import("USER32",auto) */
        public native static boolean GetWindowRect (int hWnd, RECT lpRect);

        /** @dll.import("USER32",auto) */
        public native static int GetWindowRgn (int hWnd, int hRgn);

        /** @dll.import("USER32",auto) */
        public native static int GetWindowTextLength (int hWnd);

        /** @dll.import("USER32", auto) */
        public native static int GetWindowText (int hWnd, StringBuffer lpString, int nMaxCount);

        /** @dll.import("USER32",auto) */
        public native static int GetWindowThreadProcessId (int hWnd, int[] lpdwProcessId);

        /** @dll.import("USER32",auto) */
        public native static short GetWindowWord (int hWnd, int nIndex);

        /** @dll.import("USER32",auto) */
        public native static boolean GrayString (int hDC, int hBrush, GRAYSTRINGPROC lpOutputFunc, int lpData, int nCount, int X, int Y, int nWidth, int nHeight);

        /** @dll.import("USER32",auto) */
        public native static boolean HideCaret (int hWnd);

        /** @dll.import("USER32",auto) */
        public native static boolean HiliteMenuItem (int hWnd, int hMenu, int uIDHiliteItem, int uHilite);

        /** @dll.import("USER32",auto) */
        public native static boolean InSendMessage ();

        /** @dll.import("USER32",auto) */
        public native static boolean InflateRect (RECT lprc, int dx, int dy);

        /** @dll.import("USER32",auto) */
        public native static boolean InsertMenuItem (int anonymous0, int anonymous1, boolean anonymous2, MENUITEMINFO anonymous3);

        /** @dll.import("USER32", auto) */
        public native static boolean InsertMenu (int hMenu, int uPosition, int uFlags, int uIDNewItem, String lpNewItem);

        /** @dll.import("USER32",auto) */
        public native static boolean IntersectRect (RECT lprcDst, RECT lprcSrc1, RECT lprcSrc2);

        /** @dll.import("USER32",auto) */
        public native static boolean InvalidateRect (int hWnd, RECT lpRect, boolean bErase);

        /** @dll.import("USER32",auto) */
        public native static boolean InvalidateRgn (int hWnd, int hRgn, boolean bErase);

        /** @dll.import("USER32",auto) */
        public native static boolean InvertRect (int hDC, RECT lprc);

        /** @dll.import("USER32", auto) */
        public native static boolean IsCharAlphaNumeric (char ch);

        /** @dll.import("USER32", auto) */
        public native static boolean IsCharAlpha (char ch);

        /** @dll.import("USER32", auto) */
        public native static boolean IsCharLower (char ch);

        /** @dll.import("USER32", auto) */
        public native static boolean IsCharUpper (char ch);

        /** @dll.import("USER32",auto) */
        public native static boolean IsChild (int hWndParent, int hWnd);

        /** @dll.import("USER32",auto) */
        public native static boolean IsClipboardFormatAvailable (int format);

        /** @dll.import("USER32",auto) */
        public native static boolean IsDialogMessage (int hDlg, MSG lpMsg);

        /** @dll.import("USER32",auto) */
        public native static int IsDlgButtonChecked (int hDlg, int nIDButton);

        /** @dll.import("USER32",auto) */
        public native static boolean IsIconic (int hWnd);

        /** @dll.import("USER32",auto) */
        public native static boolean IsMenu (int hMenu);

        /** @dll.import("USER32",auto) */
        public native static boolean IsRectEmpty (RECT lprc);

        /** @dll.import("USER32",auto) */
        public native static boolean IsWindow (int hWnd);

        /** @dll.import("USER32",auto) */
        public native static boolean IsWindowEnabled (int hWnd);

        /** @dll.import("USER32",auto) */
        public native static boolean IsWindowUnicode (int hWnd);

        /** @dll.import("USER32",auto) */
        public native static boolean IsWindowVisible (int hWnd);

        /** @dll.import("USER32",auto) */
        public native static boolean IsZoomed (int hWnd);

        /** @dll.import("USER32",auto) */
        public native static boolean KillTimer (int hWnd, int uIDEvent);

        /** @dll.import("USER32", auto) */
        public native static int LoadAccelerators (int hInstance, int lpTableName);

        /** @dll.import("USER32", auto) */
        public native static int LoadAccelerators (int hInstance, String lpTableName);

        /** @dll.import("USER32", auto) */
        public native static int LoadBitmap (int hInstance, int lpBitmapName);

        /** @dll.import("USER32", auto) */
        public native static int LoadBitmap (int hInstance, String lpBitmapName);

        /** @dll.import("USER32", auto) */
        public native static int LoadCursorFromFile (String lpFileName);

        /** @dll.import("USER32", auto) */
        public native static int LoadCursor (int hInstance, int lpCursorName);

        /** @dll.import("USER32", auto) */
        public native static int LoadCursor (int hInstance, String lpCursorName);

        /** @dll.import("USER32", auto) */
        public native static int LoadIcon (int hInstance, int lpIconName);

        /** @dll.import("USER32", auto) */
        public native static int LoadIcon (int hInstance, String lpIconName);

        /** @dll.import("USER32", auto) */
        public native static int LoadImage (int anonymous0, String anonymous1, int anonymous2, int anonymous3, int anonymous4, int anonymous5);

        /** @dll.import("USER32", auto) */
        public native static int LoadKeyboardLayout (String pwszKLID, int Flags);

        /** @dll.import("USER32",auto) */
        public native static int LoadMenuIndirect (int lpMenuTemplate);

        /** @dll.import("USER32", auto) */
        public native static int LoadMenu (int hInstance, int lpMenuName);

        /** @dll.import("USER32", auto) */
        public native static int LoadMenu (int hInstance, String lpMenuName);

        /** @dll.import("USER32", auto) */
        public native static int LoadString (int hInstance, int uID, StringBuffer lpBuffer, int nBufferMax);

        /** @dll.import("USER32",auto) */
        public native static boolean LockWindowUpdate (int hWndLock);

        /** @dll.import("USER32",auto) */
        public native static int LookupIconIdFromDirectory (Object presbits, boolean fIcon);

        /** @dll.import("USER32",auto) */
        public native static int LookupIconIdFromDirectoryEx (Object presbits, boolean fIcon, int cxDesired, int cyDesired, int Flags);

        /** @dll.import("USER32",auto) */
        public native static boolean MapDialogRect (int hDlg, RECT lpRect);

        /** @dll.import("USER32",auto) */
        public native static int MapVirtualKeyEx (int uCode, int uMapType, int dwhkl);

        /** @dll.import("USER32",auto) */
        public native static int MapVirtualKey (int uCode, int uMapType);

        /** @dll.import("USER32",auto) */
        public native static int MapWindowPoints (int hWndFrom, int hWndTo, int[] lpPoints, int cPoints);

        /** @dll.import("USER32",entrypoint="MenuItemFromPoint") */
        private native static int MenuItemFromPoint_I (int hWnd, int hMenu, int ptScreen_x, int ptStreen_y);
		  
        public static int MenuItemFromPoint (int hWnd, int hMenu, POINT ptScreen)
		  {
			  return MenuItemFromPoint_I(hWnd, hMenu, ptScreen.x, ptScreen.y);
		  }

        /** @dll.import("USER32",auto) */
        public native static boolean MessageBeep (int uType);

        /** @dll.import("USER32", auto) */
        public native static int MessageBoxEx (int hWnd, String lpText, String lpCaption, int uType, short wLanguageId);

        /** @dll.import("USER32",auto) */
        public native static int MessageBoxIndirect (MSGBOXPARAMS anonymous0);

        /** @dll.import("USER32", auto) */
        public native static int MessageBox (int hWnd, String lpText, String lpCaption, int uType);

        /** @dll.import("USER32", auto) */
        public native static boolean ModifyMenu (int hMnu, int uPosition, int uFlags, int uIDNewItem, String lpNewItem);

        /** @dll.import("USER32",auto) */
        public native static boolean MoveWindow (int hWnd, int X, int Y, int nWidth, int nHeight, boolean bRepaint);

        /** @dll.import("USER32",auto) */
        public native static int MsgWaitForMultipleObjects (int nCount, int[] pHandles, boolean fWaitAll, int dwMilliseconds, int dwWakeMask);

        /** @dll.import("USER32",auto) */
        public native static int MsgWaitForMultipleObjectsEx (int nCount, int[] pHandles, int dwMilliseconds, int dwWakeMask, int dwFlags);

        /** @dll.import("USER32",auto) */
        public native static int OemKeyScan (short wOemChar);

        /** @dll.import("USER32", auto) */
        public native static boolean OemToCharBuff (String lpszSrc, StringBuffer lpszDst, int cchDstLength);

        /** @dll.import("USER32", auto) */
        public native static boolean OemToChar (String lpszSrc, StringBuffer lpszDst);

        /** @dll.import("USER32",auto) */
        public native static boolean OffsetRect (RECT lprc, int dx, int dy);

        /** @dll.import("USER32",auto) */
        public native static boolean OpenClipboard (int hWndNewOwner);

        /** @dll.import("USER32", auto) */
        public native static int OpenDesktop (String lpszDesktop, int dwFlags, boolean fInherit, int dwDesiredAccess);

        /** @dll.import("USER32",auto) */
        public native static boolean OpenIcon (int hWnd);

        /** @dll.import("USER32",auto) */
        public native static int OpenInputDesktop (int dwFlags, boolean fInherit, int dwDesiredAccess);

        /** @dll.import("USER32", auto) */
        public native static int OpenWindowStation (String lpszWinSta, boolean fInherit, int dwDesiredAccess);

        /** @dll.import("USER32",auto) */
        public native static boolean PaintDesktop (int hdc);

        /** @dll.import("USER32",auto) */
        public native static boolean PeekMessage (MSG lpMsg, int hWnd, int wMsgFilterMin, int wMsgFilterMax, int wRemoveMsg);

        /** @dll.import("USER32",auto) */
        public native static boolean PostMessage (int hWnd, int Msg, int wParam, int lParam);

        /** @dll.import("USER32",auto) */
        public native static boolean PostMessage (int hWnd, int Msg, int wParam, Object lParam);

        /** @dll.import("USER32",auto) */
        public native static boolean PostMessage (int hWnd, int Msg, Object wParam, Object lParam);


        /** @dll.import("USER32",auto) */
        public native static void PostQuitMessage (int nExitCode);

        /** @dll.import("USER32",auto) */
        public native static boolean PostThreadMessage (int idThread, int Msg, int wParam, int lParam);

        /** @dll.import("USER32",auto) */
        public native static boolean PostThreadMessage (int idThread, int Msg, int wParam, Object lParam);

        /** @dll.import("USER32",auto) */
        public native static boolean PostThreadMessage (int idThread, int Msg, Object wParam, Object lParam);

        /** @dll.import("USER32",entrypoint="PtInRect") */
        private native static boolean PtInRect_I (RECT lprc, int pt_x, int pt_y);

        public static boolean PtInRect (RECT lprc, POINT pt)
		  {
			  return PtInRect_I(lprc, pt.x, pt.y);
		  }

        /** @dll.import("USER32",auto) */
        public native static boolean RedrawWindow (int hWnd, RECT lprcUpdate, int hrgnUpdate, int flags);

        /** @dll.import("USER32",auto) */
        public native static short RegisterClassEx (WNDCLASSEX lpcwcx);

        /** @dll.import("USER32",auto) */
        public native static short RegisterClass (WNDCLASS lpWndClass);

        /** @dll.import("USER32", auto) */
        public native static int RegisterClipboardFormat (String lpszFormat);

        /** @dll.import("USER32",auto) */
        public native static boolean RegisterHotKey (int hWnd, int id, int fsModifiers, int vk);

        /** @dll.import("USER32", auto) */
        public native static int RegisterWindowMessage (String lpString);

        /** @dll.import("USER32",auto) */
        public native static boolean ReleaseCapture ();

        /** @dll.import("USER32",auto) */
        public native static int ReleaseDC (int hWnd, int hDC);

        /** @dll.import("USER32",auto) */
        public native static boolean RemoveMenu (int hMenu, int uPosition, int uFlags);

        /** @dll.import("USER32", auto) */
        public native static int RemoveProp (int hWnd, String lpString);

        /** @dll.import("USER32",auto) */
        public native static boolean ReplyMessage (int lResult);

        /** @dll.import("USER32",auto) */
        public native static boolean ScreenToClient (int hWnd, POINT lpPoint);

        /** @dll.import("USER32",auto) */
        public native static boolean ScrollDC (int hDC, int dx, int dy, RECT lprcScroll, RECT lprcClip, int hrgnUpdate, RECT lprcUpdate);

        /** @dll.import("USER32",auto) */
        public native static boolean ScrollWindow (int hWnd, int XAmount, int YAmount, RECT lpRect, RECT lpClipRect);

        /** @dll.import("USER32",auto) */
        public native static int ScrollWindowEx (int hWnd, int dx, int dy, RECT prcScroll, RECT prcClip, int hrgnUpdate, RECT prcUpdate, int flags);

        /** @dll.import("USER32",auto) */
        public native static int SendDlgItemMessage (int hDlg, int nIDDlgItem, int Msg, int wParam, int lParam);

        /** @dll.import("USER32",auto) */
        public native static int SendDlgItemMessage (int hDlg, int nIDDlgItem, int Msg, Object wParam, Object lParam);

        /** @dll.import("USER32",auto) */
        public native static boolean SendMessageCallback (int hWnd, int Msg, int wParam, int lParam, SENDASYNCPROC lpResultCallBack, int dwData);

        /** @dll.import("USER32",auto) */
        public native static boolean SendMessageCallback (int hWnd, int Msg, Object wParam, Object lParam, SENDASYNCPROC lpResultCallBack, Object dwData);

        /** @dll.import("USER32",auto) */
        public native static int SendMessageTimeout (int hWnd, int Msg, int wParam, int lParam, int fuFlags, int uTimeout, int[] lpdwResult);

        /** @dll.import("USER32",auto) */
        public native static int SendMessageTimeout (int hWnd, int Msg, Object wParam, Object lParam, int fuFlags, int uTimeout, int[] lpdwResult);

        /** @dll.import("USER32",auto) */
        public native static int SendMessage (int hWnd, int Msg, int wParam, int lParam);

        /** @dll.import("USER32",auto) */
        public native static int SendMessage (int hWnd, int Msg, int wParam, Object lParam);

        /** @dll.import("USER32",auto) */
        public native static int SendMessage (int hWnd, int Msg, Object wParam, Object lParam);

        /** @dll.import("USER32",auto) */
        public native static boolean SendNotifyMessage (int hWnd, int Msg, int wParam, int lParam);

        /** @dll.import("USER32",auto) */
        public native static boolean SendNotifyMessage (int hWnd, int Msg, Object wParam, Object lParam);

        /** @dll.import("USER32",auto) */
        public native static int SetActiveWindow (int hWnd);

        /** @dll.import("USER32",auto) */
        public native static int SetCapture (int hWnd);

        /** @dll.import("USER32",auto) */
        public native static boolean SetCaretBlinkTime (int uMSeconds);

        /** @dll.import("USER32",auto) */
        public native static boolean SetCaretPos (int X, int Y);

        /** @dll.import("USER32",auto) */
        public native static int SetClassLong (int hWnd, int nIndex, int dwNewLong);

        /** @dll.import("USER32",auto) */
        public native static short SetClassWord (int hWnd, int nIndex, short wNewWord);

        /** @dll.import("USER32",auto) */
        public native static int SetClipboardData (int uFormat, int hMem);

        /** @dll.import("USER32",auto) */
        public native static int SetClipboardViewer (int hWndNewViewer);

        /** @dll.import("USER32",auto) */
        public native static int SetCursor (int hCursor);

        /** @dll.import("USER32",auto) */
        public native static boolean SetCursorPos (int X, int Y);

        /** @dll.import("USER32",auto) */
        public native static void SetDebugErrorLevel (int dwLevel);

        /** @dll.import("USER32",auto) */
        public native static boolean SetDlgItemInt (int hDlg, int nIDDlgItem, int uValue, boolean bSigned);

        /** @dll.import("USER32", auto) */
        public native static boolean SetDlgItemText (int hDlg, int nIDDlgItem, String lpString);

        /** @dll.import("USER32",auto) */
        public native static boolean SetDoubleClickTime (int anonymous0);

        /** @dll.import("USER32",auto) */
        public native static int SetFocus (int hWnd);

        /** @dll.import("USER32",auto) */
        public native static boolean SetForegroundWindow (int hWnd);

        /** @dll.import("USER32",auto) */
        public native static boolean SetKeyboardState (byte[] lpKeyState);

        /** @dll.import("USER32",auto) */
        public native static void SetLastErrorEx (int dwErrCode, int dwType);

        /** @dll.import("USER32",auto) */
        public native static boolean SetMenu (int hWnd, int hMenu);

        /** @dll.import("USER32",auto) */
        public native static boolean SetMenuContextHelpId (int anonymous0, int anonymous1);

        /** @dll.import("USER32",auto) */
        public native static boolean SetMenuDefaultItem (int hMenu, int uItem, int fByPos);

        /** @dll.import("USER32",auto) */
        public native static boolean SetMenuItemBitmaps (int hMenu, int uPosition, int uFlags, int hBitmapUnchecked, int hBitmapChecked);

        /** @dll.import("USER32",auto) */
        public native static boolean SetMenuItemInfo (int anonymous0, int anonymous1, boolean anonymous2, MENUITEMINFO anonymous3);

        /** @dll.import("USER32",auto) */
        public native static int SetMessageExtraInfo (int lParam);

        /** @dll.import("USER32",auto) */
        public native static boolean SetMessageQueue (int cMessagesMax);

        /** @dll.import("USER32",auto) */
        public native static int SetParent (int hWndChild, int hWndNewParent);

        /** @dll.import("USER32",auto) */
        public native static boolean SetProcessWindowStation (int hWinSta);

        /** @dll.import("USER32", auto) */
        public native static boolean SetProp (int hWnd, String lpString, int hData);

        /** @dll.import("USER32",auto) */
        public native static boolean SetRect (RECT lprc, int xLeft, int yTop, int xRight, int yBottom);

        /** @dll.import("USER32",auto) */
        public native static boolean SetRectEmpty (RECT lprc);

        /** @dll.import("USER32",auto) */
        public native static int SetScrollInfo (int anonymous0, int anonymous1, SCROLLINFO anonymous2, boolean anonymous3);

        /** @dll.import("USER32",auto) */
        public native static int SetScrollPos (int hWnd, int nBar, int nPos, boolean bRedraw);

        /** @dll.import("USER32",auto) */
        public native static boolean SetScrollRange (int hWnd, int nBar, int nMinPos, int nMaxPos, boolean bRedraw);

        /** @dll.import("USER32",auto) */
        public native static boolean SetSysColors (int cElements, int[] lpaElements, int[] lpaRgbValues);

        /** @dll.import("USER32",auto) */
        public native static boolean SetSystemCursor (int hcur, int id);

        /** @dll.import("USER32",auto) */
        public native static boolean SetThreadDesktop (int hDesktop);

        /** @dll.import("USER32",auto) */
        public native static int SetTimer (int hWnd, int nIDEvent, int uElapse, TIMERPROC lpTimerFunc);

        /** @dll.import("USER32",auto) */
        public native static boolean SetUserObjectInformation (int hObj, int nIndex, Object pvInfo, int nLength);

        /** @dll.import("USER32",auto) */
        public native static boolean SetWindowContextHelpId (int hwnd, int dwContextHelpid);

        /** @dll.import("USER32",auto) */
        public native static int SetWindowLong (int hWnd, int nIndex, int dwNewLong);

        /** @dll.import("USER32",auto) */
        public native static int SetWindowLong (int hWnd, int nIndex, Object dwNewLong);

        /** @dll.import("USER32",auto) */
        public native static boolean SetWindowPlacement (int hWnd, WINDOWPLACEMENT lpwndpl);

        /** @dll.import("USER32",auto) */
        public native static boolean SetWindowPos (int hWnd, int hWndInsertAfter, int X, int Y, int cx, int cy, int uFlags);

        /** @dll.import("USER32",auto) */
        public native static int SetWindowRgn (int hWnd, int hRgn, boolean bRedraw);

        /** @dll.import("USER32", auto) */
        public native static boolean SetWindowText (int hWnd, String lpString);

        /** @dll.import("USER32",auto) */
        public native static short SetWindowWord (int hWnd, int nIndex, short wNewWord);

        /** @dll.import("USER32",auto) */
        public native static boolean ShowCaret (int hWnd);

        /** @dll.import("USER32",auto) */
        public native static int ShowCursor (boolean bShow);

        /** @dll.import("USER32",auto) */
        public native static boolean ShowOwnedPopups (int hWnd, boolean fShow);

        /** @dll.import("USER32",auto) */
        public native static boolean ShowScrollBar (int hWnd, int wBar, boolean bShow);

        /** @dll.import("USER32",auto) */
        public native static boolean ShowWindow (int hWnd, int nCmdShow);

        /** @dll.import("USER32",auto) */
        public native static boolean ShowWindowAsync (int hWnd, int nCmdShow);

        /** @dll.import("USER32",auto) */
        public native static boolean SubtractRect (RECT lprcDst, RECT lprcSrc1, RECT lprcSrc2);

        /** @dll.import("USER32",auto) */
        public native static boolean SwapMouseButton (boolean fSwap);

        /** @dll.import("USER32",auto) */
        public native static boolean SwitchDesktop (int hDesktop);

        /** @dll.import("USER32",auto) */
        public native static boolean SystemParametersInfo (int uiAction, int uiParam, int[] pvParam, int fWinIni);

        /** @dll.import("USER32",auto) */
        public native static boolean SystemParametersInfo (int uiAction, int uiParam, boolean[] pvParam, int fWinIni);

        /** @dll.import("USER32",auto) */
        public native static boolean SystemParametersInfo (int uiAction, int uiParam, ACCESSTIMEOUT pvParam, int fWinIni);

        /** @dll.import("USER32",auto) */
        public native static boolean SystemParametersInfo (int uiAction, int uiParam, ANIMATIONINFO pvParam, int fWinIni);

        /** @dll.import("USER32",auto) */
        public native static boolean SystemParametersInfo (int uiAction, int uiParam, FILTERKEYS pvParam, int fWinIni);

        /** @dll.import("USER32",entrypoint="SystemParametersInfo") */
        private native static boolean SystemParametersInfo_I (int uiAction, int uiParam, Object pvParam, int fWinIni);

        public static boolean SystemParametersInfo (int uiAction, int uiParam, HIGHCONTRAST pvParam, int fWinIni)
        {
            boolean result;
            if (uiAction == 66 /* SPI_GETHIGHCONTRAST */) {
                    HIGHCONTRAST_I hi = new HIGHCONTRAST_I();
                    hi.cbSize = com.ms.dll.DllLib.sizeOf(hi.getClass());
                    result = SystemParametersInfo_I(uiAction, uiParam, hi, fWinIni);
        
                    if (result) {
                        pvParam.dwFlags = hi.dwFlags;
                        pvParam.lpszDefaultScheme = com.ms.dll.DllLib.ptrToString(hi.lpszDefaultScheme);
                    }
            } else {
                    result = SystemParametersInfo_I(uiAction, uiParam, pvParam, fWinIni);
            }
            return result;
        }


        /** @dll.import("USER32",auto) */
        public native static boolean SystemParametersInfo (int uiAction, int uiParam, ICONMETRICS pvParam, int fWinIni);

        /** @dll.import("USER32",auto) */
        public native static boolean SystemParametersInfo (int uiAction, int uiParam, MINIMIZEDMETRICS pvParam, int fWinIni);

        /** @dll.import("USER32",auto) */
        public native static boolean SystemParametersInfo (int uiAction, int uiParam, MOUSEKEYS pvParam, int fWinIni);

        /** @dll.import("USER32",auto) */
        public native static boolean SystemParametersInfo (int uiAction, int uiParam, NONCLIENTMETRICS pvParam, int fWinIni);

        /** @dll.import("USER32",auto) */
        public native static boolean SystemParametersInfo (int uiAction, int uiParam, SERIALKEYS pvParam, int fWinIni);

        /** @dll.import("USER32",auto) */
        public native static boolean SystemParametersInfo (int uiAction, int uiParam, SOUNDSENTRY pvParam, int fWinIni);

        /** @dll.import("USER32",auto) */
        public native static boolean SystemParametersInfo (int uiAction, int uiParam, STICKYKEYS pvParam, int fWinIni);

        /** @dll.import("USER32",auto) */
        public native static boolean SystemParametersInfo (int uiAction, int uiParam, TOGGLEKEYS pvParam, int fWinIni);

        /** @dll.import("USER32", auto) */
        public native static int TabbedTextOut (int hDC, int X, int Y, String lpString, int nCount, int nTabPositions, int[] lpnTabStopPositions, int nTabOrigin);

        /** @dll.import("USER32",auto) */
        public native static short TileWindows (int hwndParent, int wHow, RECT lpRect, int cKids, int[] lpKids);

        /** @dll.import("USER32",auto) */
        public native static int ToAscii (int uVirtKey, int uScanCode, byte[] lpKeyState, short[] lpChar, int uFlags);

        /** @dll.import("USER32",auto) */
        public native static int ToAsciiEx (int uVirtKey, int uScanCode, byte[] lpKeyState, short[] lpChar, int uFlags, int dwhkl);

        /** @dll.import("USER32", unicode) */
        public native static int ToUnicode (int wVirtKey, int wScanCode, byte[] lpKeyState, StringBuffer pwszBuff, int cchBuff, int wFlags);

        /** @dll.import("USER32", unicode) */
        public native static int ToUnicodeEx (int wVirtKey, int wScanCode, byte[] lpKeyState, StringBuffer pwszBuff, int cchBuff, int wFlags, int dwhkl);

        /** @dll.import("USER32",auto) */
        public native static boolean TrackMouseEvent (TRACKMOUSEEVENT lpEventTrack);

        /** @dll.import("USER32",auto) */
        public native static int TrackPopupMenu (int hMenu, int uFlags, int x, int y, int nReserved, int hWnd, RECT prcRect);

        /** @dll.import("USER32",auto) */
        public native static int TrackPopupMenuEx (int anonymous0, int anonymous1, int anonymous2, int anonymous3, int anonymous4, TPMPARAMS anonymous5);

        /** @dll.import("USER32",auto) */
        public native static int TranslateAccelerator (int hWnd, int hAccTable, MSG lpMsg);

        /** @dll.import("USER32",auto) */
        public native static boolean TranslateMDISysAccel (int hWndClient, MSG lpMsg);

        /** @dll.import("USER32",auto) */
        public native static boolean TranslateMessage (MSG lpMsg);

        /** @dll.import("USER32",auto) */
        public native static boolean UnionRect (RECT lprcDst, RECT lprcSrc1, RECT lprcSrc2);

        /** @dll.import("USER32",auto) */
        public native static boolean UnloadKeyboardLayout (int hkl);

        /** @dll.import("USER32", auto) */
        public native static boolean UnregisterClass (String lpClassName, int hInstance);

        /** @dll.import("USER32",auto) */
        public native static boolean UnregisterHotKey (int hWnd, int id);

        /** @dll.import("USER32",auto) */
        public native static boolean UpdateWindow (int hWnd);

        /** @dll.import("USER32",auto) */
        public native static boolean ValidateRect (int hWnd, RECT lpRect);

        /** @dll.import("USER32",auto) */
        public native static boolean ValidateRgn (int hWnd, int hRgn);

        /** @dll.import("USER32", auto) */
        public native static short VkKeyScanEx (char ch, int dwhkl);

        /** @dll.import("USER32", auto) */
        public native static short VkKeyScan (char ch);

        /** @dll.import("USER32",auto) */
        public native static int WaitForInputIdle (int hProcess, int dwMilliseconds);

        /** @dll.import("USER32",auto) */
        public native static boolean WaitMessage ();

        /** @dll.import("USER32", auto) */
        public native static boolean WinHelp (int hWndMain, String lpszHelp, int uCommand, int dwData);

        /** @dll.import("USER32",auto) */
        public native static int WindowFromDC (int hDC);

        /** @dll.import("USER32",entrypoint="WindowFromPoint") */
        private native static int WindowFromPoint_I (int Point_x, int Point_y);
		  
        public static int WindowFromPoint (POINT pt)
		  {
			  return WindowFromPoint_I(pt.x, pt.y);
		  }

        /** @dll.import("USER32",auto) */
        public native static void keybd_event (byte bVk, byte bScan, int dwFlags, int dwExtraInfo);

        /** @dll.import("USER32",auto) */
        public native static void mouse_event (int dwFlags, int dx, int dy, int dwData, int dwExtraInfo);
}

