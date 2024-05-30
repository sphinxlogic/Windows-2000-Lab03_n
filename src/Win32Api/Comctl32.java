// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;

/** @security(checkClassLinking=on) */
public class Comctl32 {
	public static int Animate_Create(int hwndP, int id, int dwStyle, int hInstance)
	{
		return User32.CreateWindow("SysAnimate32", null, dwStyle, 0, 0, 0, 0, hwndP, id, hInstance, win.NULL);
	}
	
	/** @dll.import("COMCTL32", auto) */
	public native static int CreateMappedBitmap (int hInstance, int idBitmap, int wFlags, COLORMAP lpColorMap, int iNumMaps);


	/** @dll.import("COMCTL32", auto) */
	public native static int CreateStatusWindow (int style, String lpszText, int hwndParent, int wID);

	/** @dll.import("COMCTL32", auto) */
	public native static int CreateToolbarEx (int hwnd, int ws, int wID, int nBitmaps, int hBMInst, int wBMID, Object lpButtons, int iNumButtons, int dxButton, int dyButton, int dxBitmap, int dyBitmap, int uStructSize);

	/** @dll.import("COMCTL32", auto) */
	public native static int CreateUpDownControl (int dwStyle, int x, int y, int cx, int cy, int hParent, int nID, int hInst, int hBuddy, int nUpper, int nLower, int nPos);

	public static int DateTime_GetMonthCal (int hdp)
	{
		return User32.SendMessage(hdp, win.DTM_GETMONTHCAL, 0, 0);
	}

	public static int DateTime_GetMonthCalColor (int hdp, int iColor)
	{
		return User32.SendMessage(hdp, win.DTM_GETMCCOLOR, iColor, 0);
	}

	public static int DateTime_GetMonthCalFont (int hdp)
	{
		return User32.SendMessage(hdp, win.DTM_GETMCFONT, 0, 0);
	}

	public static int DateTime_GetRange (int hdp, int rgst)
	{
		return User32.SendMessage(hdp, win.DTM_GETRANGE, 0, rgst);
	}

	public static int DateTime_GetSystemtime (int hdp, SYSTEMTIME pst)
	{
		return User32.SendMessage(hdp, win.DTM_GETSYSTEMTIME, 0, pst);
	}

	public static boolean DateTime_SetFormat (int hdp, String sz)
	{
		return 0 != User32.SendMessage(hdp, win.DTM_SETFORMAT, 0, sz);
	}

	public static int DateTime_SetMonthCalColor (int hdp, int iColor, int clr)
	{
		return User32.SendMessage(hdp, win.DTM_SETMCCOLOR, iColor, clr);
	}

	public static int DateTime_SetMonthCalFont (int hdp, int hfont, int fRedraw)
	{
		return User32.SendMessage(hdp, win.DTM_SETMCFONT, hfont, fRedraw);
	}

	public static boolean DateTime_SetRange (int hdp, int gd, int rgst)
	{
		return 0 != User32.SendMessage(hdp, win.DTM_SETRANGE, gd, rgst);
	}

	public static boolean DateTime_SetSystemtime (int hdp, int gd, SYSTEMTIME pst)
	{
		return 0 != User32.SendMessage(hdp, win.DTM_SETSYSTEMTIME, gd, pst);
	}

	/** @dll.import("COMCTL32", auto) */
	public native static boolean DestroyPropertySheetPage (int anon0);

	/** @dll.import("COMCTL32", auto) */
	public native static void DrawInsert (int handParent, int hLB, int nItem);

	/** @dll.import("COMCTL32", auto) */
	public native static void DrawStatusText (int hDC, RECT lprc, String pszText, int uFlags);

	/** @dll.import("COMCTL32", auto) */
	public native static void GetEffectiveClientRect (int hWnd, RECT lprc, int[] lpInfo);
	
	// Represent ImageList's only as ints.
	public static int Header_CreateDragImage (int hwndHD, int i)
	{
		return User32.SendMessage(hwndHD, win.HDM_CREATEDRAGIMAGE, i, 0);
	}
	
	public static boolean Header_DeleteItem (int hwndHD, int i)
	{
		return (0 != User32.SendMessage(hwndHD, win.HDM_DELETEITEM, i, 0) ? true : false);
	}
	
	public static int Header_GetImageList (int hwndHD)
	{
		return User32.SendMessage(hwndHD, win.HDM_GETIMAGELIST, 0, 0);
	}

	public static boolean Header_GetItem (int hwndHD, int i, int phdi)
	{
		return (0 != User32.SendMessage(hwndHD, win.HDM_GETITEM, i, phdi) ? true : false);
	}
	
	public static int Header_GetItemCount (int hwndHD)
	{
		return User32.SendMessage(hwndHD, win.HDM_GETITEMCOUNT, 0, 0);
	}
	
	public static boolean Header_GetItemRect (int hwndHD, int iItem, RECT lprc)
	{
		return (0 != User32.SendMessage(hwndHD, win.HDM_GETITEMRECT, iItem, lprc) ? true : false);
	}

	public static int Header_GetOrderArray (int hwndHD, int iCount, int[] lpi)
	{
		return User32.SendMessage(hwndHD, win.HDM_GETORDERARRAY, iCount, lpi);
	}
	
	public static int Header_InsertItem (int hwndHD, int i, HDITEM phdi)
	{
		return User32.SendMessage(hwndHD, win.HDM_INSERTITEM, i, phdi);
	}
	
	public static boolean Header_Layout (int hwndHD, HDLAYOUT playout)
	{
		return (0 != User32.SendMessage(hwndHD, win.HDM_LAYOUT, 0, playout) ? true : false);
	}
	
	public static int Header_OrderToIndex (int hwndHD, int i)
	{
		return User32.SendMessage(hwndHD, win.HDM_ORDERTOINDEX, i, 0);
	}
	
	public static int Header_SetImageList (int hwndHD, int himl)
	{
		return User32.SendMessage(hwndHD, win.HDM_SETIMAGELIST, 0, himl);
	}
	
	public static boolean Header_SetItem (int hwndHD, int i, HDITEM phdi)
	{
		return (0 != User32.SendMessage(hwndHD, win.HDM_SETITEM, i, phdi) ? true : false);
	}

	public static int Header_SetHotDivider (int hwndHD, int fPos, int dw)
	{
		return User32.SendMessage(hwndHD, win.HDM_SETHOTDIVIDER, fPos, dw);
	}

	public static int Header_SetOrderArray (int hwndHD, int iCount, int[] lpi)
	{
		return User32.SendMessage(hwndHD, win.HDM_SETORDERARRAY, iCount, lpi);
	}
	
	/** @dll.import("COMCTL32", auto) */
	public native static int ImageList_Add (int himl, int hbmImage, int hbmMask);
	
	/** @dll.import("COMCTL32", auto) */
	public native static int ImageList_AddMasked (int himl, int hbmImage, int crMask);
	
	/** @dll.import("COMCTL32", auto) */
	public native static boolean ImageList_BeginDrag (int himlTrack, int iTrack, int dxHotspot, int dyHotspot);
	
	/** @dll.import("COMCTL32", auto) */
	public native static boolean ImageList_Copy (int himlDst, int iDst, int himlSrc, int iSrc, int uFlags);
	
	/** @dll.import("COMCTL32", auto) */
	public native static int ImageList_Create (int cx, int cy, int flags, int cInitial, int cGrow);
	
	/** @dll.import("COMCTL32", auto) */
	public native static boolean ImageList_Destroy (int himl);
	
	/** @dll.import("COMCTL32", auto) */
	public native static boolean ImageList_DragEnter (int hwndLock, int x, int y);

	/** @dll.import("COMCTL32", auto) */
	public native static boolean ImageList_DragLeave (int hwndLock);

	/** @dll.import("COMCTL32", auto) */
	public native static boolean ImageList_DragMove (int x, int y);

	/** @dll.import("COMCTL32", auto) */
	public native static boolean ImageList_DragShowNolock (boolean fShow);

	/** @dll.import("COMCTL32", auto) */
	public native static boolean ImageList_Draw (int himl, int i, int hdcDst, int x, int y, int fStyle);

	/** @dll.import("COMCTL32", auto) */
	public native static boolean ImageList_DrawEx (int himl, int i, int hdcDst, int x, int y, int dx, int dy, int rgbBk, int rgbFg, int fStyle);

	/** @dll.import("COMCTL32", auto) */
	public native static boolean ImageList_EndDrag ();

	/** @dll.import("COMCTL32", auto) */
	public native static int ImageList_GetBkColor (int himl);

	/** @dll.import("COMCTL32", auto) */
	public native static int ImageList_GetDragImage (POINT ppt, POINT pptHotspot);

	/** @dll.import("COMCTL32", auto) */
	public native static int ImageList_GetIcon (int himl, int i, int flags);

	/** @dll.import("COMCTL32", auto) */
	public native static boolean ImageList_GetIconSize (int himl, int[] cx, int[] cy);

	/** @dll.import("COMCTL32", auto) */
	public native static int ImageList_GetImageCount (int himl);

	/** @dll.import("COMCTL32", auto) */
	public native static boolean ImageList_GetImageInfo (int himl, int i, IMAGEINFO pImageInfo);

	/** @dll.import("COMCTL32", auto) */
	public native static int ImageList_LoadImage (int hi, String lpbmp, int cx, int cGrow, int crMask, int uType, int uFlags);

	/** @dll.import("COMCTL32", auto) */
	public native static int ImageList_Merge (int himl1, int i1, int himl2, int i2, int dx, int dy);



	/** @dll.import("COMCTL32", auto) */
	public native static boolean ImageList_Remove (int himl, int i);

	/** @dll.import("COMCTL32", auto) */
	public native static boolean ImageList_Replace (int himl, int i, int hbmImage, int hbmMask);

	/** @dll.import("COMCTL32", auto) */
	public native static int ImageList_ReplaceIcon (int himl, int i, int hicon);

	/** @dll.import("COMCTL32", auto) */
	public native static int ImageList_SetBkColor (int himl, int clrBk);

	/** @dll.import("COMCTL32", auto) */
	public native static boolean ImageList_SetDragCursorImage (int himlDrag, int iDrag, int dxHotspot, int dyHotspot);

	/** @dll.import("COMCTL32", auto) */
	public native static boolean ImageList_SetIconSize (int himl, int cx, int cy);

	/** @dll.import("COMCTL32", auto) */
	public native static boolean ImageList_SetImageCount (int himl, int uNewCount);

	/** @dll.import("COMCTL32", auto) */
	public native static boolean ImageList_SetOverlayImage (int himl, int iImage, int iOverlay);



	/** @dll.import("COMCTL32", auto) */
	public native static void InitCommonControls ();

	/** @dll.import("COMCTL32", auto) */
	public native static boolean InitCommonControlsEx (INITCOMMONCONTROLSEX anon0);

	/** @dll.import("COMCTL32", auto) */
	public native static int LBItemFromPt (int hLB, int x, int y, boolean bAutoScroll);

	public static int LBItemFromPt (int hLB, POINT pt, boolean bAutoScroll)
	{
		return LBItemFromPt(hLB, pt.x, pt.y, bAutoScroll);
	}

	public static int ListView_ApproximateViewRect (int hwnd, short iWidth, short iHeight, int iCount)
	{
		return User32.SendMessage(hwnd, win.LVM_APPROXIMATEVIEWRECT, 0, (((int)iWidth) & 0xffff) | (((int)iHeight)<<16));
	}

	public static boolean ListView_Arrange (int hwndLV, int code)
	{
		return 0 != User32.SendMessage(hwndLV, win.LVM_ARRANGE, code, 0);
	}

	public static int ListView_CreateDragImage (int hwnd, int i, POINT lpptUpLeft)
	{
		return User32.SendMessage(hwnd, win.LVM_CREATEDRAGIMAGE, i, lpptUpLeft);
	}

	public static int ListView_DeleteAllItems (int hwnd)
	{
		return User32.SendMessage(hwnd, win.LVM_DELETEALLITEMS, 0, 0);
	}

	public static boolean ListView_DeleteColumn (int hwnd, int iCol)
	{
		return 0 != User32.SendMessage(hwnd, win.LVM_DELETECOLUMN, iCol, 0);
	}

	public static boolean ListView_DeleteItem (int hwnd, int i)
	{
		return 0 != User32.SendMessage(hwnd, win.LVM_DELETEITEM, i, 0);
	}

	public static int ListView_EditLabel (int hwndLV, int i)
	{
		return User32.SendMessage(hwndLV, win.LVM_EDITLABEL, i, 0);
	}

	public static boolean ListView_EnsureVisible (int hwndLV, int i, boolean fPartialOk)
	{
		return 0 != User32.SendMessage(hwndLV, win.LVM_ENSUREVISIBLE, i, (fPartialOk ? 1 : 0));
	}

	public static int ListView_FindItem (int hwnd, int iStart, LVFINDINFO plvfi)
	{
		return User32.SendMessage(hwnd, win.LVM_FINDITEM, iStart, plvfi);
	}

	public static int ListView_GetBkColor (int hwnd)
	{
		return User32.SendMessage(hwnd, win.LVM_GETBKCOLOR, 0, 0);
	}

	public static int ListView_GetCallbackMask (int hwnd)
	{
		return User32.SendMessage(hwnd, win.LVM_GETCALLBACKMASK, 0, 0);
	}

	public static int ListView_GetCheckState (int hwndLV, int i)
	{
		return (User32.SendMessage(hwndLV, win.LVM_GETITEMSTATE, i, win.LVIS_STATEIMAGEMASK) >> 12) - 1;
	}

	public static boolean ListView_GetColumn (int hwndLV, int iCol, LVCOLUMN pcol)
	{
		return 0 != User32.SendMessage(hwndLV, win.LVM_GETCOLUMN, iCol, pcol);
	}

	public static boolean ListView_GetColumnOrderArray (int hwndLV, int iCount, int[] pi)
	{
		return 0 != User32.SendMessage(hwndLV, win.LVM_GETCOLUMNORDERARRAY, iCount, pi);
	}

	public static int ListView_GetColumnWidth (int hwnd, int iCol)
	{
		return User32.SendMessage(hwnd, win.LVM_GETCOLUMNWIDTH, iCol, 0);
	}

	public static int ListView_GetCountPerPage (int hwndLV)
	{
		return User32.SendMessage(hwndLV, win.LVM_GETCOUNTPERPAGE, 0, 0);
	}

	public static int ListView_GetEditControl (int hwndLV)
	{
		return User32.SendMessage(hwndLV, win.LVM_GETEDITCONTROL, 0, 0);
	}

	public static int ListView_GetExtendedListViewStyle (int hwndLV)
	{
		return User32.SendMessage(hwndLV, win.LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0);
	}

	public static int ListView_GetHeader (int hwnd)
	{
		return User32.SendMessage(hwnd, win.LVM_GETHEADER, 0, 0);
	}

	public static int ListView_GetHotCursor (int hwnd)
	{
		return User32.SendMessage(hwnd, win.LVM_GETHOTCURSOR, 0, 0);
	}

	public static int ListView_GetHotItem (int hwnd)
	{
		return User32.SendMessage(hwnd, win.LVM_GETHOTITEM, 0, 0);
	}

	public static int ListView_GetImageList (int hwnd, int iImageList)
	{
		return User32.SendMessage(hwnd, win.LVM_GETIMAGELIST, iImageList, 0);
	}

	public static int ListView_GetISearchString (int hwndLV, StringBuffer lpsz)
	{
		return User32.SendMessage(hwndLV, win.LVM_GETISEARCHSTRING, 0, lpsz);
	}

	public static boolean ListView_GetItem (int hwnd, LVITEM pitem)
	{
		return 0 != User32.SendMessage(hwnd, win.LVM_GETITEM, 0, pitem);
	}

	public static int ListView_GetItemCount (int hwnd)
	{
		return User32.SendMessage(hwnd, win.LVM_GETITEMCOUNT, 0, 0);
	}

	public static boolean ListView_GetItemPosition (int hwnd, int i, POINT ppt)
	{
		return 0 != User32.SendMessage(hwnd, win.LVM_GETITEMPOSITION, i, ppt);
	}

	public static boolean ListView_GetItemRect (int hwnd, int i, RECT prc, int code)
	{
		if(prc!=null)
			prc.left = code;
		return 0 != User32.SendMessage(hwnd, win.LVM_GETITEMRECT, i, prc);
	}

	public static int ListView_GetItemSpacing (int hwndLV, int fSmall)
	{
		return User32.SendMessage(hwndLV, win.LVM_GETITEMSPACING, fSmall, 0);
	}

	public static int ListView_GetItemState (int hwndLV, int i, int mask)
	{
		return User32.SendMessage(hwndLV, win.LVM_GETITEMSTATE, i, mask);
	}

	public static void ListView_GetItemText (int hwndLV, int i, int iSubItem_, int pszText_, int cchTextMax_)
	{
		LVITEM ms_lvi = new LVITEM();
		ms_lvi.iSubItem = iSubItem_;
		ms_lvi.cchTextMax = cchTextMax_;
		ms_lvi.pszText = pszText_;
		User32.SendMessage(hwndLV, win.LVM_GETITEMTEXT, i, ms_lvi);
	}

	public static void ListView_GetItemText (int hwndLV, int i, int iSubItem_, StringBuffer pszText_, int cchTextMax_)
	{
                int nchars = pszText_.capacity();
                int buffer = com.ms.dll.DllLib.allocHGlobal(com.ms.dll.DllLib.systemDefaultCharSize *
                                                            (nchars + 1));

                try {
                        LVITEM ms_lvi = new LVITEM();
        		ms_lvi.iSubItem = iSubItem_;
        		ms_lvi.cchTextMax = cchTextMax_;
        		ms_lvi.pszText = buffer;
                        User32.SendMessage(hwndLV, win.LVM_GETITEMTEXT, i, ms_lvi);
                        pszText_.setLength(0);
                        pszText_.append(com.ms.dll.DllLib.ptrToString(buffer));
                } finally {
                        com.ms.dll.DllLib.freeHGlobal(buffer);
                }
	}

	public static int ListView_GetNextItem (int hwnd, int i, short flags)
	{
		return User32.SendMessage(hwnd, win.LVM_GETNEXTITEM, i, (int)flags);
	}

	public static boolean ListView_GetOrigin (int hwndLV, POINT ppt)
	{
		return 0 != User32.SendMessage(hwndLV, win.LVM_GETORIGIN, 0, ppt);
	}

	public static int ListView_GetSelectedCount (int hwndLV)
	{
		return User32.SendMessage(hwndLV, win.LVM_GETSELECTEDCOUNT, 0, 0);
	}
	
	// Pass in a pointer to a C string and get width
	public static int ListView_GetStringWidth (int hwndLV, String psz)
	{
		return User32.SendMessage(hwndLV, win.LVM_GETSTRINGWIDTH, null, psz);
	}
	
	public static int ListView_GetSubItemHitTest (int hwnd, LVHITTESTINFO plvhti)
	{
		return User32.SendMessage(hwnd, win.LVM_SUBITEMHITTEST, 0, plvhti);
	}

	public static boolean ListView_GetSubItemRect (int hwnd, int iItem, int iSubItem, int code, RECT prc)
	{
		if(prc!=null) {
			prc.top = iSubItem;
			prc.left = code;
		}
		return 0 != User32.SendMessage(hwnd, win.LVM_GETSUBITEMRECT, iItem, prc);
	}
	
	public static int ListView_GetTextBkColor (int hwnd)
	{
		return User32.SendMessage(hwnd, win.LVM_GETTEXTBKCOLOR, 0, 0);
	}

	public static int ListView_GetTextColor (int hwnd)
	{
		return User32.SendMessage(hwnd, win.LVM_GETTEXTCOLOR, 0, 0);
	}

	public static int ListView_GetTopIndex (int hwndLV)
	{
		return User32.SendMessage(hwndLV, win.LVM_GETTOPINDEX, 0, 0);
	}

	public static boolean ListView_GetViewRect (int hwnd, RECT prc)
	{
		return 0 != User32.SendMessage(hwnd, win.LVM_GETVIEWRECT, 0, prc);
	}

	public static int ListView_HitTest (int hwndLV, LVHITTESTINFO pinfo)
	{
		return User32.SendMessage(hwndLV, win.LVM_HITTEST, 0, pinfo);
	}

	public static int ListView_InsertColumn (int hwnd, int iCol, LVCOLUMN pcol)
	{
		return User32.SendMessage(hwnd, win.LVM_INSERTCOLUMN, iCol, pcol);
	}

	public static int ListView_InsertItem (int hwnd, LVITEM pitem)
	{
		return User32.SendMessage(hwnd, win.LVM_INSERTITEM, 0, pitem);
	}

	public static boolean ListView_RedrawItems (int hwndLV, int iFirst, int iLast)
	{
		return 0 != User32.SendMessage(hwndLV, win.LVM_REDRAWITEMS, iFirst, iLast);
	}

	public static boolean ListView_Scroll (int hwndLV, int dx, int dy)
	{
		return 0 != User32.SendMessage(hwndLV, win.LVM_SCROLL, dx, dy);
	}

	public static boolean ListView_SetBkColor (int hwnd, int clrBk)
	{
		return 0 != User32.SendMessage(hwnd, win.LVM_SETBKCOLOR, 0, clrBk);
	}

	public static boolean ListView_SetCallbackMask (int hwnd, int mask)
	{
		return 0 != User32.SendMessage(hwnd, win.LVM_SETCALLBACKMASK, mask, 0);
	}

	public static boolean ListView_SetColumn (int hwndLV, int iCol, LVCOLUMN pcol)
	{
		return 0 != User32.SendMessage(hwndLV, win.LVM_SETCOLUMN, iCol, pcol);
	}

	public static boolean ListView_SetColumnOrderArray (int hwndLV, int iCount, int[] pi)
	{
		return 0 != User32.SendMessage(hwndLV, win.LVM_SETCOLUMNORDERARRAY, iCount, pi);
	}

	public static boolean ListView_SetColumnWidth (int hwnd, int iCol, short cx)
	{
		return 0 != User32.SendMessage(hwnd, win.LVM_SETCOLUMNWIDTH, iCol, (int)cx);
	}

	public static int ListView_SetExtendedListViewStyle (int hwndLV, int dw)
	{
		return User32.SendMessage(hwndLV, win.LVM_SETEXTENDEDLISTVIEWSTYLE, 0, dw);
	}

	public static int ListView_SetHotCursor (int hwnd, int hcur)
	{
		return User32.SendMessage(hwnd, win.LVM_SETHOTCURSOR, 0, hcur);
	}

	public static int ListView_SetHotItem (int hwnd, int i)
	{
		return User32.SendMessage(hwnd, win.LVM_SETHOTITEM, i, 0);
	}

	public static int ListView_SetImageList (int hwnd, int himl, int iImageList)
	{
		return User32.SendMessage(hwnd, win.LVM_SETIMAGELIST, iImageList, himl);
	}

	public static int ListView_SetIconSpacing (int hwndLV, short cx, short cy)
	{
		return User32.SendMessage(hwndLV, win.LVM_SETICONSPACING, 0, (((int) cx) & 0xffff) | (((int)cy) << 16));
	}

	public static boolean ListView_SetItem (int hwnd, LVITEM pitem)
	{
		return 0 != User32.SendMessage(hwnd, win.LVM_SETITEM, 0, pitem);
	}

	public static int ListView_SetItemCount (int hwnd, int cItems)
	{
		return User32.SendMessage(hwnd, win.LVM_SETITEMCOUNT, cItems, 0);
	}

	public static int ListView_SetItemCountEx (int hwnd, int cItems, int dwFlags)
	{
		return User32.SendMessage(hwnd, win.LVM_SETITEMCOUNT, cItems, dwFlags);
	}

	public static boolean ListView_SetItemPosition (int hwnd, int i, short x, short y)
	{
		return 0 != User32.SendMessage(hwnd, win.LVM_SETITEMPOSITION, i, (((int) x) & 0xffff) | ((int)y<<16));
	}

	public static void ListView_SetItemPosition32 (int hwnd, int i, int x, int y)
	{
		POINT ptNewPos = new POINT();
		ptNewPos.x = x;
		ptNewPos.y = y;
		User32.SendMessage(hwnd, win.LVM_SETITEMPOSITION32, i, ptNewPos);
	}

	public static int ListView_SetItemState (int hwndLV, int i, int data, int mask)
	{
		LVITEM ms_lvi = new LVITEM();
		ms_lvi.stateMask = mask;
		ms_lvi.state = data;
		return User32.SendMessage(hwndLV, win.LVM_SETITEMSTATE, i, ms_lvi);
	}

	public static void ListView_SetItemText (int hwndLV, int i, int iSubItem_, String pszText_)
	{
		LVITEM ms_lvi = new LVITEM();
		ms_lvi.iSubItem = iSubItem_;
                int pszText = com.ms.dll.DllLib.stringToHGlobal(pszText_);

                try {
                  ms_lvi.pszText = pszText;
		  User32.SendMessage(hwndLV, win.LVM_SETITEMTEXT, i, ms_lvi);
                } finally {
                  com.ms.dll.DllLib.freeHGlobal(pszText);
                }
                
	}
	
	public static boolean ListView_SetTextBkColor (int hwnd, int clrTextBk)
	{
		return 0 != User32.SendMessage(hwnd, win.LVM_SETTEXTBKCOLOR, 0, clrTextBk);
	}
	
	public static boolean ListView_SetTextColor (int hwnd, int clrText)
	{
		return 0 != User32.SendMessage(hwnd, win.LVM_SETTEXTCOLOR, 0, clrText);
	}
	
	public static void ListView_SetWorkArea (int hwndLV, RECT prc)
	{
		User32.SendMessage(hwndLV, win.LVM_SETWORKAREA, 0, prc);
	}

	public static boolean ListView_SortItems (int hwndLV, PFNLVCOMPARE _pfnCompare, int _lPrm)
	{
		return 0 != User32.SendMessage(hwndLV, win.LVM_SORTITEMS, _lPrm, _pfnCompare);
	}

	public static boolean ListView_Update (int hwndLV, int i)
	{
		return 0 != User32.SendMessage(hwndLV, win.LVM_UPDATE, i, 0);
	}

	/** @dll.import("COMCTL32", auto) */
	public native static boolean MakeDragList (int hLB);

	/** @dll.import("COMCTL32", auto) */
	public native static void MenuHelp (int uMsg, int wParam, int lParam, int hMainMenu, int hInst, int hwndStatus, int[] lpwIDs);

	public static int MonthCal_GetColor (int hmc, int iColor)
	{
		return User32.SendMessage(hmc, win.MCM_GETCOLOR, iColor, 0);
	}

	public static boolean MonthCal_GetCurSel (int hmc, SYSTEMTIME pst)
	{
		return 0 != User32.SendMessage(hmc, win.MCM_GETCURSEL, 0, pst);
	}

	public static int MonthCal_GetFirstDayOfWeek (int hmc)
	{
		return User32.SendMessage(hmc, win.MCM_GETFIRSTDAYOFWEEK, 0, 0);
	}

	public static int MonthCal_GetMaxSelCount (int hmc)
	{
		return User32.SendMessage(hmc, win.MCM_GETMAXSELCOUNT, 0, 0);
	}

	public static int MonthCal_GetMinReqRect (int hmc, RECT prc)
	{
		return User32.SendMessage(hmc, win.MCM_GETMINREQRECT, 0, prc);
	}

	public static int MonthCal_GetMonthDelta (int hmc)
	{
		return User32.SendMessage(hmc, win.MCM_GETMONTHDELTA, 0, 0);
	}

	public static int MonthCal_GetMonthRange (int hmc, int gmr, SYSTEMTIMEPAIR rgst)
	{
		return User32.SendMessage(hmc, win.MCM_GETMONTHRANGE, gmr, rgst);
	}

	public static int MonthCal_GetRange (int hmc, SYSTEMTIMEPAIR rgst)
	{
		return User32.SendMessage(hmc, win.MCM_GETRANGE, 0, rgst);
	}

	public static int MonthCal_GetSelRange (int hmc, SYSTEMTIMEPAIR rgst)
	{
		return User32.SendMessage(hmc, win.MCM_GETSELRANGE, 0, rgst);
	}

	public static boolean MonthCal_GetToday (int hmc, SYSTEMTIME pst)
	{
		return 0 != User32.SendMessage(hmc, win.MCM_GETTODAY, 0, pst);
	}

	public static int MonthCal_HitTest (int hmc, MCHITTESTINFO pinfo)
	{
		return User32.SendMessage(hmc, win.MCM_HITTEST, 0, pinfo);
	}

	public static int MonthCal_SetColor (int hmc, int iColor, int clr)
	{
		return User32.SendMessage(hmc, win.MCM_SETCOLOR, iColor, clr);
	}

	public static boolean MonthCal_SetCurSel (int hmc, SYSTEMTIME pst)
	{
		return 0 != User32.SendMessage(hmc, win.MCM_SETCURSEL, 0, pst);
	}

	public static boolean MonthCal_SetDayState (int hmc, int cbds, int[] rgds)
	{
		return 0 != User32.SendMessage(hmc, win.MCM_SETDAYSTATE, cbds, rgds);
	}

	public static int MonthCal_SetFirstDayOfWeek (int hmc, int iDay)
	{
		return User32.SendMessage(hmc, win.MCM_SETFIRSTDAYOFWEEK, 0, iDay);
	}

	public static boolean MonthCal_SetMaxSelCount (int hmc, int n)
	{
		return 0 != User32.SendMessage(hmc, win.MCM_SETMAXSELCOUNT, n, 0);
	}

	public static int MonthCal_SetMonthDelta (int hmc, int n)
	{
		return User32.SendMessage(hmc, win.MCM_SETMONTHDELTA, n, 0);
	}

	public static boolean MonthCal_SetRange (int hmc, int gd, SYSTEMTIMEPAIR rgst)
	{
		return 0 != User32.SendMessage(hmc, win.MCM_SETRANGE, gd, rgst);
	}

	public static boolean MonthCal_SetSelRange (int hmc, SYSTEMTIMEPAIR rgst)
	{
		return 0 != User32.SendMessage(hmc, win.MCM_SETSELRANGE, 0, rgst);
	}

	public static int MonthCal_SetToday (int hmc, SYSTEMTIME pst)
	{
		return User32.SendMessage(hmc, win.MCM_SETTODAY, 0, pst);
	}

	/** @dll.import("COMCTL32", auto) */
	public native static boolean ShowHideMenuCtl (int hWnd, int uFlags, int[] lpInfo);

	public static int TabCtrl_AdjustRect (int hwnd, boolean bLarger, RECT prc)
	{
		return User32.SendMessage(hwnd, win.TCM_ADJUSTRECT, (bLarger?1:0), prc);
	}

	public static boolean TabCtrl_DeleteItem (int hwnd, int i)
	{
		return 0 != User32.SendMessage(hwnd, win.TCM_DELETEITEM, i, 0);
	}

	public static boolean TabCtrl_DeleteAllItems (int hwnd)
	{
		return 0 != User32.SendMessage(hwnd, win.TCM_DELETEALLITEMS, 0, 0);
	}

	public static void TabCtrl_DeselectAll (int hwnd, int fExcludeFocus)
	{
		User32.SendMessage(hwnd, win.TCM_DESELECTALL, fExcludeFocus, 0);
	}

	public static int TabCtrl_GetCurFocus (int hwnd)
	{
		return User32.SendMessage(hwnd, win.TCM_GETCURFOCUS, 0, 0);
	}

	public static int TabCtrl_GetCurSel (int hwnd)
	{
		return User32.SendMessage(hwnd, win.TCM_GETCURSEL, 0, 0);
	}

	public static int TabCtrl_GetImageList (int hwnd)
	{
		return User32.SendMessage(hwnd, win.TCM_GETIMAGELIST, 0, 0);
	}

	public static boolean TabCtrl_GetItem (int hwnd, int iItem, TCITEM pItem)
	{
		return 0 != User32.SendMessage(hwnd, win.TCM_GETITEM, iItem, pItem);
	}

	public static int TabCtrl_GetItemCount (int hwnd)
	{
		return User32.SendMessage(hwnd, win.TCM_GETITEMCOUNT, 0, 0);
	}

	public static boolean TabCtrl_GetItemRect (int hwnd, int i, RECT prc)
	{
		return 0 != User32.SendMessage(hwnd, win.TCM_GETITEMRECT, i, prc);
	}

	public static int TabCtrl_GetRowCount (int hwnd)
	{
		return User32.SendMessage(hwnd, win.TCM_GETROWCOUNT, 0, 0);
	}

	public static int TabCtrl_GetToolTips (int hwnd)
	{
		return User32.SendMessage(hwnd, win.TCM_GETTOOLTIPS, 0, 0);
	}

	public static int TabCtrl_HitTest (int hwndTC, TCHITTESTINFO pinfo)
	{
		return User32.SendMessage(hwndTC, win.TCM_HITTEST, 0, pinfo);
	}

	public static int TabCtrl_InsertItem (int hwnd, int iItem, TCITEM pItem)
	{
		return User32.SendMessage(hwnd, win.TCM_INSERTITEM, iItem, pItem);
	}

	public static void TabCtrl_RemoveImage (int hwnd, int i)
	{
		User32.SendMessage(hwnd, win.TCM_REMOVEIMAGE, i, 0);
	}

	public static int TabCtrl_SetCurFocus (int hwnd, int i)
	{
		return User32.SendMessage(hwnd, win.TCM_SETCURFOCUS, i, 0);
	}

	public static int TabCtrl_SetCurSel (int hwnd, int i)
	{
		return User32.SendMessage(hwnd, win.TCM_SETCURSEL, i, 0);
	}

	public static int TabCtrl_SetImageList (int hwnd, int himl)
	{
		return User32.SendMessage(hwnd, win.TCM_SETIMAGELIST, 0, himl);
	}

	public static boolean TabCtrl_SetItem (int hwnd, int iItem, TCITEM pItem)
	{
		return 0 != User32.SendMessage(hwnd, win.TCM_SETITEM, iItem, pItem);
	}

	public static boolean TabCtrl_SetItemExtra (int hwndTC, int cb)
	{
		return 0 != User32.SendMessage(hwndTC, win.TCM_SETITEMEXTRA, cb, 0);
	}

	public static int TabCtrl_SetItemSize (int hwnd, short x, short y)
	{
		return User32.SendMessage(hwnd, win.TCM_SETIMAGELIST, 0, (((int) x) & 0xffff) | (((int) y)<<16));
	}

	public static int TabCtrl_SetMinTabWidth (int hwnd, int x)
	{
		return User32.SendMessage(hwnd, win.TCM_SETMINTABWIDTH, 0, x);
	}

	public static void TabCtrl_SetPadding (int hwnd, short cx, short cy)
	{
		User32.SendMessage(hwnd, win.TCM_SETPADDING, 0, (((int) cx) & 0xffff) | (((int) cy)<<16));
	}

	public static void TabCtrl_SetToolTips (int hwnd, int hwndTT)
	{
		User32.SendMessage(hwnd, win.TCM_SETTOOLTIPS, hwndTT, 0);
	}

	public static int TreeView_CreateDragImage (int hwnd, int hitem)
	{
		return User32.SendMessage(hwnd, win.TVM_CREATEDRAGIMAGE, 0, hitem);
	}

	public static boolean TreeView_DeleteAllItems (int hwnd)
	{
		return 0 != User32.SendMessage(hwnd, win.TVM_DELETEITEM, 0, win.TVI_ROOT);
	}

	public static boolean TreeView_DeleteItem (int hwnd, int hitem)
	{
		return 0 != User32.SendMessage(hwnd, win.TVM_DELETEITEM, 0, hitem);
	}

	public static int TreeView_EditLabel(int hwnd, int hitem)
	{
		return User32.SendMessage(hwnd, win.TVM_EDITLABEL, 0, hitem);
	}

	public static boolean TreeView_EndEditLabelNow (int hwnd, int fCancel)
	{
		return 0 != User32.SendMessage(hwnd, win.TVM_ENDEDITLABELNOW, fCancel, 0);
	}

	public static boolean TreeView_EnsureVisible (int hwnd, int hitem)
	{
		return 0 != User32.SendMessage(hwnd, win.TVM_ENSUREVISIBLE, 0, hitem);
	}

	public static boolean TreeView_Expand (int hwnd, int hitem, int code)
	{
		return 0 != User32.SendMessage(hwnd, win.TVM_EXPAND, code, hitem);
	}

	public static int TreeView_GetChild(int hwnd, int hitem)
	{
		return TreeView_GetNextItem(hwnd, hitem, win.TVGN_CHILD);
	}

	public static int TreeView_GetCount (int hwnd)
	{
		return User32.SendMessage(hwnd, win.TVM_GETCOUNT, 0, 0);
	}

	public static int TreeView_GetDropHilight(int hwnd)
	{
		return TreeView_GetNextItem(hwnd, win.NULL, win.TVGN_DROPHILITE);
	}

	public static int TreeView_GetEditControl (int hwnd)
	{
		return User32.SendMessage(hwnd, win.TVM_GETEDITCONTROL, 0, 0);
	}

	public static int TreeView_GetFirstVisible(int hwnd)
	{
		return TreeView_GetNextItem(hwnd, win.NULL, win.TVGN_FIRSTVISIBLE);
	}

	public static int TreeView_GetImageList (int hwnd, int iImage)
	{
		return User32.SendMessage(hwnd, win.TVM_GETIMAGELIST, iImage, 0);
	}

	public static int TreeView_GetIndent (int hwnd)
	{
		return User32.SendMessage(hwnd, win.TVM_GETINDENT, 0, 0);
	}

	public static int TreeView_GetISearchString (int hwndTV, StringBuffer lpsz)
	{
		return User32.SendMessage(hwndTV, win.TVM_GETISEARCHSTRING, 0, lpsz);
	}

	public static boolean TreeView_GetItem (int hwnd, TV_ITEM pitem)
	{
		return 0 != User32.SendMessage(hwnd, win.TVM_GETITEM, 0, pitem);
	}

	public static boolean TreeView_GetItemRect (int hwnd, int hitem, RECT prc, int code)
	{
		prc.left = hitem;
		return 0 != User32.SendMessage(hwnd, win.TVM_GETITEMRECT, code, prc);
	}

	public static int TreeView_GetNextItem (int hwnd, int hitem, int code)
	{
		return User32.SendMessage(hwnd, win.TVM_GETNEXTITEM, code, hitem);
	}

	public static int TreeView_GetNextSibling(int hwnd, int hitem)
	{
		return TreeView_GetNextItem(hwnd, hitem, win.TVGN_NEXT);
	}

	public static int TreeView_GetNextVisible(int hwnd, int hitem)
	{
		return TreeView_GetNextItem(hwnd, hitem, win.TVGN_NEXTVISIBLE);
	}

	public static int TreeView_GetParent(int hwnd, int hitem)
	{
		return TreeView_GetNextItem(hwnd, hitem, win.TVGN_PARENT);
	}

	public static int TreeView_GetPrevSibling(int hwnd, int hitem)
	{
		return TreeView_GetNextItem(hwnd, hitem, win.TVGN_PREVIOUS);
	}

	public static int TreeView_GetPrevVisible(int hwnd, int hitem)
	{
		return TreeView_GetNextItem(hwnd, hitem, win.TVGN_PREVIOUSVISIBLE);
	}

	public static int TreeView_GetRoot(int hwnd)
	{
		return TreeView_GetNextItem(hwnd, win.NULL, win.TVGN_ROOT);
	}

	public static int TreeView_GetSelection(int hwnd)
	{
		return TreeView_GetNextItem(hwnd, win.NULL, win.TVGN_CARET);
	}

	public static int TreeView_GetVisibleCount (int hwnd)
	{
		return User32.SendMessage(hwnd, win.TVM_GETVISIBLECOUNT, 0, 0);
	}

	public static int TreeView_HitTest (int hwnd, TV_HITTESTINFO lpht)
	{
		return User32.SendMessage(hwnd, win.TVM_HITTEST, 0, lpht);
	}

	public static int TreeView_InsertItem (int hwnd, TV_INSERTSTRUCT lpis)
	{
		return User32.SendMessage(hwnd, win.TVM_INSERTITEM, 0, lpis);
	}

	public static int TreeView_Select(int hwnd, int hitem, int code)
	{
		return User32.SendMessage(hwnd, win.TVM_SELECTITEM, code, hitem);
	}

	public static int TreeView_SelectDropTarget(int hwnd, int hitem)
	{
		return TreeView_Select(hwnd, hitem, win.TVGN_DROPHILITE);
	}

	public static int TreeView_SelectItem(int hwnd, int hitem)
	{
		return TreeView_Select(hwnd, hitem, win.TVGN_CARET);
	}

	public static int TreeView_SelectSetFirstVisible(int hwnd, int hitem)
	{
		return TreeView_Select(hwnd, hitem, win.TVGN_FIRSTVISIBLE);
	}

	public static int TreeView_SetImageList (int hwnd, int himl, int iImage)
	{
		return User32.SendMessage(hwnd, win.TVM_SETIMAGELIST, iImage, himl);
	}

	public static boolean TreeView_SetIndent (int hwnd, int indent)
	{
		return 0 != User32.SendMessage(hwnd, win.TVM_SETINDENT, indent, 0);
	}

	public static boolean TreeView_SetItem (int hwnd, TV_ITEM pitem)
	{
		return 0 != User32.SendMessage(hwnd, win.TVM_SETITEM, 0, pitem);
	}

	public static boolean TreeView_SortChildren (int hwnd, int hitem, int recurse)
	{
		return 0 != User32.SendMessage(hwnd, win.TVM_SORTCHILDREN, recurse, hitem);
	}

	public static boolean TreeView_SortChildrenCB (int hwnd, TV_SORTCB psort, int recurse)
	{
		return 0 != User32.SendMessage(hwnd, win.TVM_SORTCHILDRENCB, recurse, psort);
	}

	/** @dll.import("COMCTL32", auto) */
	public native static boolean _TrackMouseEvent (TRACKMOUSEEVENT lpEventTrack);
}

