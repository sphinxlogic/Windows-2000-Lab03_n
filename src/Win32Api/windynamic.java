// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;

// This class constants "constants" that require loadtime
// initalizations. We isolate these in one class for perf reasons:
// callers of "win.class" can use them via inheritance, but only
// "windynamic" needs to be loaded at runtime.
public interface windynamic {

  int CBEM_GETITEM = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.CBEM_GETITEMA : win.CBEM_GETITEMW;
  int CBEM_SETITEM = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.CBEM_SETITEMA : win.CBEM_SETITEMW;
  int CBEN_ENDEDIT = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.CBEN_ENDEDITA : win.CBEN_ENDEDITW;
  int CBEM_INSERTITEM = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.CBEM_INSERTITEMA : win.CBEM_INSERTITEMW;
  int LVM_GETITEMTEXT = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.LVM_GETITEMTEXTA : win.LVM_GETITEMTEXTW;
  int LVM_SETITEMTEXT = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.LVM_SETITEMTEXTA : win.LVM_SETITEMTEXTW;
  int ACM_OPEN = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.ACM_OPENA : win.ACM_OPENW;
  int DTM_SETFORMAT = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.DTM_SETFORMATA : win.DTM_SETFORMATW;
  int DTN_USERSTRING = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.DTN_USERSTRINGA : win.DTN_USERSTRINGW;
  int DTN_WMKEYDOWN = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.DTN_WMKEYDOWNA : win.DTN_WMKEYDOWNW;
  int DTN_FORMAT = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.DTN_FORMATA : win.DTN_FORMATW;
  int DTN_FORMATQUERY = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.DTN_FORMATQUERYA : win.DTN_FORMATQUERYW;
  int EMR_EXTTEXTOUT = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.EMR_EXTTEXTOUTA : win.EMR_EXTTEXTOUTW;
  int EMR_POLYTEXTOUT = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.EMR_POLYTEXTOUTA : win.EMR_POLYTEXTOUTW;
  int HDM_INSERTITEM = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.HDM_INSERTITEMA : win.HDM_INSERTITEMW;
  int HDM_GETITEM = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.HDM_GETITEMA : win.HDM_GETITEMW;
  int HDM_SETITEM = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.HDM_SETITEMA : win.HDM_SETITEMW;
  int HDN_ITEMCHANGING = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.HDN_ITEMCHANGINGA : win.HDN_ITEMCHANGINGW;
  int HDN_ITEMCHANGED = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.HDN_ITEMCHANGEDA : win.HDN_ITEMCHANGEDW;
  int HDN_ITEMCLICK = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.HDN_ITEMCLICKA : win.HDN_ITEMCLICKW;
  int HDN_ITEMDBLCLICK = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.HDN_ITEMDBLCLICKA : win.HDN_ITEMDBLCLICKW;
  int HDN_DIVIDERDBLCLICK = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.HDN_DIVIDERDBLCLICKA : win.HDN_DIVIDERDBLCLICKW;
  int HDN_BEGINTRACK = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.HDN_BEGINTRACKA : win.HDN_BEGINTRACKW;
  int HDN_ENDTRACK = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.HDN_ENDTRACKA : win.HDN_ENDTRACKW;
  int HDN_TRACK = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.HDN_TRACKA : win.HDN_TRACKW;
  int HDN_GETDISPINFO = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.HDN_GETDISPINFOA : win.HDN_GETDISPINFOW;
  int LVM_GETITEM = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.LVM_GETITEMA : win.LVM_GETITEMW;
  int LVM_SETITEM = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.LVM_SETITEMA : win.LVM_SETITEMW;
  int LVM_INSERTITEM = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.LVM_INSERTITEMA : win.LVM_INSERTITEMW;
  int LVM_FINDITEM = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.LVM_FINDITEMA : win.LVM_FINDITEMW;
  int LVM_GETSTRINGWIDTH = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.LVM_GETSTRINGWIDTHA : win.LVM_GETSTRINGWIDTHW;
  int LVM_EDITLABEL = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.LVM_EDITLABELA : win.LVM_EDITLABELW;
  int LVM_GETCOLUMN = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.LVM_GETCOLUMNA : win.LVM_GETCOLUMNW;
  int LVM_SETCOLUMN = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.LVM_SETCOLUMNA : win.LVM_SETCOLUMNW;
  int LVM_GETISEARCHSTRING = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.LVM_GETISEARCHSTRINGA : win.LVM_GETISEARCHSTRINGW;
  int LVN_BEGINLABELEDIT = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.LVN_BEGINLABELEDITA : win.LVN_BEGINLABELEDITW;
  int LVN_ENDLABELEDIT = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.LVN_ENDLABELEDITA : win.LVN_ENDLABELEDITW;
  int LVN_ODFINDITEM = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.LVN_ODFINDITEMA : win.LVN_ODFINDITEMW;
  int LVN_GETDISPINFO = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.LVN_GETDISPINFOA : win.LVN_GETDISPINFOW;
  int LVN_SETDISPINFO = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.LVN_SETDISPINFOA : win.LVN_SETDISPINFOW;
  int PSM_SETTITLE = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.PSM_SETTITLEA : win.PSM_SETTITLEW;
  int PSM_SETFINISHTEXT = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.PSM_SETFINISHTEXTA : win.PSM_SETFINISHTEXTW;
  int RB_INSERTBAND = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.RB_INSERTBANDA : win.RB_INSERTBANDW;
  int RB_SETBANDINFO = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.RB_SETBANDINFOA : win.RB_SETBANDINFOW;
  int SB_SETTEXT = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.SB_SETTEXTA : win.SB_SETTEXTW;
  int SB_GETTEXT = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.SB_GETTEXTA : win.SB_GETTEXTW;
  int SB_GETTEXTLENGTH = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.SB_GETTEXTLENGTHA : win.SB_GETTEXTLENGTHW;
  int TB_SAVERESTORE = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.TB_SAVERESTOREA : win.TB_SAVERESTOREW;
  int TB_ADDSTRING = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.TB_ADDSTRINGA : win.TB_ADDSTRINGW;
  int TB_GETBUTTONTEXT = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.TB_GETBUTTONTEXTA : win.TB_GETBUTTONTEXTW;
  int TBN_GETBUTTONINFO = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.TBN_GETBUTTONINFOA : win.TBN_GETBUTTONINFOW;
  int TTM_ADDTOOL = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.TTM_ADDTOOLA : win.TTM_ADDTOOLW;
  int TTM_DELTOOL = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.TTM_DELTOOLA : win.TTM_DELTOOLW;
  int TTM_NEWTOOLRECT = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.TTM_NEWTOOLRECTA : win.TTM_NEWTOOLRECTW;
  int TTM_GETTOOLINFO = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.TTM_GETTOOLINFOA : win.TTM_GETTOOLINFOW;
  int TTM_SETTOOLINFO = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.TTM_SETTOOLINFOA : win.TTM_SETTOOLINFOW;
  int TTM_HITTEST = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.TTM_HITTESTA : win.TTM_HITTESTW;
  int TTM_GETTEXT = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.TTM_GETTEXTA : win.TTM_GETTEXTW;
  int TTM_UPDATETIPTEXT = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.TTM_UPDATETIPTEXTA : win.TTM_UPDATETIPTEXTW;
  int TTM_ENUMTOOLS = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.TTM_ENUMTOOLSA : win.TTM_ENUMTOOLSW;
  int TTM_GETCURRENTTOOL = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.TTM_GETCURRENTTOOLA : win.TTM_GETCURRENTTOOLW;
  int TTN_GETDISPINFO = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.TTN_GETDISPINFOA : win.TTN_GETDISPINFOW;
  int TTN_NEEDTEXT = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.TTN_NEEDTEXTA : win.TTN_NEEDTEXTW;
  int TVM_INSERTITEM = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.TVM_INSERTITEMA : win.TVM_INSERTITEMW;
  int TVM_GETITEM = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.TVM_GETITEMA : win.TVM_GETITEMW;
  int TVM_SETITEM = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.TVM_SETITEMA : win.TVM_SETITEMW;
  int TVM_EDITLABEL = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.TVM_EDITLABELA : win.TVM_EDITLABELW;
  int TVM_GETISEARCHSTRING = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.TVM_GETISEARCHSTRINGA : win.TVM_GETISEARCHSTRINGW;
  int TVN_SELCHANGING = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.TVN_SELCHANGINGA : win.TVN_SELCHANGINGW;
  int TVN_SELCHANGED = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.TVN_SELCHANGEDA : win.TVN_SELCHANGEDW;
  int TVN_GETDISPINFO = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.TVN_GETDISPINFOA : win.TVN_GETDISPINFOW;
  int TVN_SETDISPINFO = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.TVN_SETDISPINFOA : win.TVN_SETDISPINFOW;
  int TVN_ITEMEXPANDING = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.TVN_ITEMEXPANDINGA : win.TVN_ITEMEXPANDINGW;
  int TVN_ITEMEXPANDED = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.TVN_ITEMEXPANDEDA : win.TVN_ITEMEXPANDEDW;
  int TVN_BEGINDRAG = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.TVN_BEGINDRAGA : win.TVN_BEGINDRAGW;
  int TVN_BEGINRDRAG = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.TVN_BEGINRDRAGA : win.TVN_BEGINRDRAGW;
  int TVN_DELETEITEM = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.TVN_DELETEITEMA : win.TVN_DELETEITEMW;
  int TVN_BEGINLABELEDIT = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.TVN_BEGINLABELEDITA : win.TVN_BEGINLABELEDITW;
  int TVN_ENDLABELEDIT = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.TVN_ENDLABELEDITA : win.TVN_ENDLABELEDITW;
  int TCM_GETITEM = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.TCM_GETITEMA : win.TCM_GETITEMW;
  int TCM_SETITEM = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.TCM_SETITEMA : win.TCM_SETITEMW;
  int TCM_INSERTITEM = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.TCM_INSERTITEMA : win.TCM_INSERTITEMW;
  int CP_WINNEUTRAL = com.ms.dll.DllLib.systemDefaultCharSize == 1 ? win.CP_WINANSI : win.CP_WINUNICODE;

}
