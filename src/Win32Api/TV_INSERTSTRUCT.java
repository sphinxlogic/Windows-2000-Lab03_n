// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


/** @dll.struct(pack=1, auto) */
public class TV_INSERTSTRUCT {
	public int	hParent;
	public int	hInsertAfter;
	public int	item_mask;
	public int	item_hItem;
	public int	item_state;
	public int	item_stateMask;
	public int /* LPWSTR */	item_pszText;
	public int	item_cchTextMax;
	public int	item_iImage;
	public int	item_iSelectedImage;
	public int	item_cChildren;
	public int	item_lParam;
}

