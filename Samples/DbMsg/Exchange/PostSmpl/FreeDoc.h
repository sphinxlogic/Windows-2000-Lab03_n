//=========================================================================
// FREEDOC.H
//
// Copyright (C) 1986-1996.  Microsoft Corp.  All Rights Reserved.
//
// Purpose:
//    Defines and prototypes for free-floating document routines.
//=========================================================================

#ifndef _FREEDOC_H_
#define _FREEDOC_H_


// Helper to convert from A to W #if !defined(RC_INVOKED) && !defined(MakeOLESTR)
#if !defined(RC_INVOKED) && !defined(MakeOLESTR)
#     define CchSzAToSzW(_szA, _szW, _cbSzW) \
         MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, (_szA), -1, (_szW),   \
                        (_cbSzW) / sizeof(WCHAR))

#     define CchSzWToSzA(_szW, _szA, _cbSzA) \
         WideCharToMultiByte(CP_ACP, 0, (_szW), -1, (_szA), (_cbSzA),   \
                        NULL, NULL)

#     define UsesMakeOLESTRX(_cchMax)  OLECHAR szWT[_cchMax]
#     define UsesMakeOLESTR         UsesMakeOLESTRX(MAX_PATH)
#     define MakeOLESTR(_szA)       \
         (CchSzAToSzW((_szA), szWT, sizeof(szWT)) ? szWT : NULL)

#     define UsesMakeANSIX(_cchMax)    CHAR szAT[_cchMax * 2]
#     define UsesMakeANSI           UsesMakeANSIX(MAX_PATH)
#     define MakeANSI(_szW)         \
         (CchSzWToSzA((_szW), szAT, sizeof(szAT)) ? szAT : NULL)
#endif



extern SCODE ScCreateFreeDoc(LPSTORAGE		pstg,
							 LPMAPIFOLDER   pfld,
							 LPSTR			szPathName,
							 LPSTR			lpszFileName,
							 LPSTR			lpszTitle,
							 LPSTR			lpszSubject,
							 LPSTR			lpszAuthor,
							 LPSTR			lpszKeywords,
							 LPSTR			lpszComments);



STDAPI GetSummaryInfo
   (
   LPSTORAGE  pstg,
   CString*   lpsTitle,
   CString*   lpsSubject,
   CString*   lpsAuthor,
   CString*   lpsKeywords,
   CString*   lpsComments
   ) ;

STDAPI SetSummaryInfo
   (
   LPSTORAGE  pstg,
   LPCSTR   psTitle,
   LPCSTR   psSubject,
   LPCSTR   psAuthor,
   LPCSTR   psKeywords,
   LPCSTR   psComments
   ) ;


#endif // _FREEDOC_H_
