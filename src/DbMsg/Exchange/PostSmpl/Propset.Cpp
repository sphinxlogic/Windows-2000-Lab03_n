//=========================================================================
// PROPSET.CPP
//
// Copyright (C) 1986-1996.  Microsoft Corp.  All Rights Reserved.
//
// Purpose:
//    Provides OLE and MAPI property set routines.
//=========================================================================

#include "stdafx.h"
#include <windowsx.h>
#include <winnls.h>
#include <mapinls.h>
#include "edk.h"
#include "PostSmpl.h"
#include <initguid.h>
#include "freedoc.h"



/*
 * Data Strcuctures
 */

typedef GUID   FMTID;
typedef struct _fmtidoffset
{
   FMTID fmtid;               // FMTID for a section
   DWORD dwOffset;            // offset of section from start of stream
} FMTIDOFFSET;

typedef struct _propsethdr
{
   WORD  wByteOrder;    // Always 0xFFFE
   WORD  wFormat;    // Always 0
   DWORD dwOSVer;    // Hiword: 0=Win16; 1=Mac; 2=Win32
                     // Loword: GetVersion()
   CLSID clsid;         // App CLSID
   DWORD cSections;     // Number of sections
} PROPSETHDR;

typedef DWORD  PID;
typedef struct _pidoffset
{
   PID      pid;              // Property ID
   DWORD dwOffset;            // offset of property from start of section
} PIDOFFSET;

typedef struct _propsectionhdr
{
   DWORD    cbSection;        // Size of this section
   DWORD    cProps;           // Number of properties in this section
} PROPSECTIONHDR;


/*
 * Define some of the guids we use
 */
DEFINE_GUID(FMTID_SumInfo, 0xF29F85E0L, 0x4FF9, 0x1068, 0xAB, 0x91, 0x08, 0x00, 0x2B, 0x27, 0xB3, 0xD9);

typedef struct _mppidmapiprop
{
   WORD     wMapiType;        // MAPI Type
   LPWSTR      szW;           // MAPI Name
} MPPIDMAPIPROP;

enum pidSumInfo {
   PID_TITLE = 2,
   PID_SUBJECT,
   PID_AUTHOR,
   PID_KEYWORDS,
   PID_COMMENTS,
   cpidSumInfoMax
};


typedef struct _propsetstminfo
{
   LPOLESTR       szName;              // stream name
   FMTID const   *pfmtid;              // FMTID of section to promote
   INT            cmppidmapipropMax;      // Mapping for property names
   MPPIDMAPIPROP *mppidmapiprop;
} PROPSETSTMINFO;


// Lego workaround - define the symbols for the array

WCHAR szTitle[]      = L"Title";
WCHAR szSubject[]    = L"Subject";
WCHAR szAuthor[]     = L"Author";
WCHAR szKeywords[]   = L"Keywords";
WCHAR szComments[]   = L"Comments";

MPPIDMAPIPROP mppidmapipropSumInfo[] =
{
   {  PT_NULL,		 NULL        }, // Dictionary
   {  PT_NULL,		 NULL        }, // Code page
   {  PT_STRING8,    szTitle     },
   {  PT_STRING8,    szSubject   },
   {  PT_STRING8,    szAuthor    },
   {  PT_MV_STRING8, szKeywords  }, // Special case VT_LPSTR -> MV
   {  PT_STRING8,    szComments  }
};

OLECHAR szSumInfo[] = OLESTR("\005SummaryInformation");

PROPSETSTMINFO rgpropsetstminfo[] =
{
   {szSumInfo, &FMTID_SumInfo, cpidSumInfoMax, mppidmapipropSumInfo},
   {NULL, NULL, 0, NULL}
};



/*
 * SzDupSz
 *
 * Purpose:
 *    This function allocates a new buffer and copies the
 *    supplied string into it.
 *
 * Parameters:
 *    sz    the string to duplicate
 *
 * Returns:
 *    a pointer to the new string (or NULL on failure)
 */
HRESULT SzDupSz(LPCTSTR sz, LPSTR *lppstr)
{
   INT         cb	 = 0;
   HRESULT	   hr	 = NOERROR;

   if (!sz)
      return hr;

   cb = (lstrlen(sz) + 1) * sizeof(TCHAR);
   if (!SUCCEEDED(hr = MAPIAllocateBuffer(cb, (LPVOID *)lppstr)))
         return hr;

   if (!lstrcpy(*lppstr, sz))
      return hr;

   return hr;
}





/*
 * ScParseKeywords
 *
 * Purpose:
 *    Parses a string of keywords listed by separators in a pval, into a
 *    multi valued property.
 *
 * Arguments:
 *    pval     Contains the keywords list string in pval->Value.lpszA
 *    szDefSep Default list separator
 *
 * Returns:
 *    SCODE    The status code
 */
SCODE ScParseKeywords(LPSPropValue pval, TCHAR * szDefSep)
{
   SCODE    sc			= S_OK;
   LPSTR    szKeywords	= pval->Value.lpszA;
   CHAR *   pch			= szKeywords;
   CHAR *   pchPrev		= NULL;
   LPSTR *  rgsz		= NULL;
   LONG     cKeywords	= 0;
   LONG     isz			= 0;
   TCHAR    szSep[3];
   BOOL     fInWord		= FALSE;
   BOOL     fFakeOneWord= FALSE;
   HRESULT  hr			= NOERROR;

   static TCHAR   szScParseKeywords1[] = TEXT("intl");
   static TCHAR   szScParseKeywords2[] = TEXT("sList");
   static TCHAR   szScParseKeywords3[] = TEXT(",");

   // Get the list separator character
   GetProfileString(szScParseKeywords1, szScParseKeywords2,
         szScParseKeywords3, szSep, sizeof(szSep) / sizeof(TCHAR));


   // Default list separator is the space character
   if (!szDefSep)
      szDefSep = TEXT(" ");

   // Loop through the string zero filling non-keywords
   while (*pch)
   {
#ifdef DBCS
      if (!FGLeadByte(*pch) && (*pch == szDefSep[0] || *pch == szSep[0]))
#else
      if (*pch == szDefSep[0] || *pch == szSep[0])
#endif
      {
         fInWord = FALSE;
      }
      else
      {
         // If we aren't in a word, we are now
         if (!fInWord)
            cKeywords++;
         fInWord = TRUE;
      }

      // Remember this position
      pchPrev = pch;

      // Move forward
#ifdef DBCS
      pch = SzGNext(pch);
#else
      pch = AnsiNext(pch);
#endif

      // If we aren't in a word, zap area from our previous position
      if (!fInWord)
         ZeroMemory(pchPrev, pch - pchPrev);
   }


   // Remove leading and trailing spaces from keywords

   pch = szKeywords;
   isz = cKeywords;
   while (isz)
   {
      isz--;

      // Skip consecutive separators
      while (!*pch)
         pch++;

      if (*pch)
      {
         // Zero out leading spaces
         pchPrev = pch;
         while (isspace(*pch))
            pch = AnsiNext(pch);
         ZeroMemory(pchPrev, pch - pchPrev);

         // Blank keyword
         if (!*pch)
         {
            cKeywords--;
            continue;
         }

         // Go to end of string
         pch = &pch[lstrlen(pch)];

         // Zero out trailing spaces
         pchPrev = AnsiPrev(szKeywords, pch);
         while (isspace(*pchPrev))
            pchPrev = AnsiPrev(szKeywords, pchPrev);
         pchPrev = AnsiNext(pchPrev);
         ZeroMemory(pchPrev, pch - pchPrev);
      }
   }

   // Handle denegerate case where we have no keywords. MAPI requires that
   // there be a value, though, so we fake up a single empty string
   if (!cKeywords)
   {
      cKeywords = 1;
      fFakeOneWord = TRUE;
   }

   // Now that we know how many keywords there are, it's time to allocate
   // space
   pval->Value.MVszA.cValues = cKeywords;
   
   if (!SUCCEEDED(hr = MAPIAllocateBuffer(cKeywords * sizeof(LPSTR), (LPVOID *)&pval->Value.MVszA.lppszA)))
   {
       sc = E_OUTOFMEMORY;
	   goto CleanUp;
   }

   rgsz = pval->Value.MVszA.lppszA;

   if (fFakeOneWord)
   {
      if (!SUCCEEDED(hr = SzDupSz((LPSTR) TEXT(""), &rgsz[0])))
		  sc = E_OUTOFMEMORY;
      goto CleanUp;
   }

   // Find the strings we had left over
   pch = szKeywords;
   while (isz < cKeywords)
   {
	   if (*pch)
	   {
			// Remember the start of the string and then zoom to the end
		   if ( !SUCCEEDED(hr = SzDupSz(pch, &rgsz[isz++])))
		   {
			   sc = E_OUTOFMEMORY;
			   goto CleanUp;
		   }
		   
		   while (*pch)
#ifdef DBCS
            pch = SzGNext(pch);
#else
            ++pch;
#endif
	   }
      ++pch;
   }

CleanUp:
   return sc;
}



/*
 * ScSaveStr
 *
 * Purpose:
 *    Saves a string
 *
 * Arguments:
 *    pstm              The stream to load from
 *    psz               String pointer 
 *
 * Returns:
 *    SCODE             The status code
 */
SCODE ScSaveStr(LPSTREAM pstm, LPCSTR  lpstr)
{
   SCODE	sc		= S_OK;
   HRESULT  hr		= NOERROR;
   DWORD	dwSize	= sizeof(CHAR) * (lstrlen(lpstr) + 1);
   ULONG	cb		= 0;

   // Save string size
   if (hr = pstm->Write(&dwSize, sizeof(DWORD), &cb))
      goto CleanUp;

   // Save the string
   if (dwSize &&
      (hr = pstm->Write(lpstr, dwSize, &cb)))
      goto CleanUp;
   
CleanUp:
   sc = GetScode(hr);
   return sc;
}


/*
 * ScLoadStr
 *
 * Purpose:
 *    Load a string
 *
 * Arguments:
 *    pstm              The stream to load from
 *    psz               String pointer 
 *
 * Returns:
 *    SCODE             The status code
 */
SCODE ScLoadStr(LPSTREAM pstm, CString *lpcstring)
{
   SCODE	sc			= S_OK;
   HRESULT  hr			= NOERROR;
   LPSTR	lpstr		= NULL;
   DWORD    dwSize		= 0;

   
     // Save string size
   if (hr = pstm->Read(&dwSize, sizeof(DWORD), NULL))
      goto CleanUp;

   // Allocate space for string and then load the string
   if (dwSize)
      hr = MAPIAllocateBuffer(dwSize, (LPVOID *)&lpstr);
   else
      hr = SzDupSz((LPTSTR)TEXT(""), &lpstr);

   if (!SUCCEEDED(hr))
   {
      sc = E_OUTOFMEMORY;
      goto CleanUp;
   }

   if (dwSize && (hr = pstm->Read(lpstr, dwSize, NULL)))
   {
      sc = GetScode(hr);
      goto CleanUp;
   }

   *lpcstring = lpstr;

CleanUp:

   MAPIFREEBUFFER(lpstr);

   return sc;
}



/*
 * SetSummaryInfo
 *
 */
STDAPI SetSummaryInfo
   (
   LPSTORAGE pstg,
   LPCSTR	lpsTitle,
   LPCSTR   lpsSubject,
   LPCSTR   lpsAuthor,
   LPCSTR   lpsKeywords,
   LPCSTR   lpsComments
   )
{
   SCODE             sc				= S_OK;
   HRESULT           hr				= NOERROR;
   PROPSETHDR        propsethdr;
   PROPSECTIONHDR    propsectionhdr;
   FMTIDOFFSET*      rgfmtidoffset	= NULL;
   FMTIDOFFSET*      pfmtidoffset	= NULL;
   PIDOFFSET*        rgpidoffset	= NULL;
   PIDOFFSET*        ppidoffset		= NULL;
   PROPSETSTMINFO*   ppropsetstminfo= rgpropsetstminfo;    // point to summary info part
   ULONG             cb				= 0;
   BOOL              fFound			= FALSE;
   BOOL              fSumInfoStm	= FALSE;
   LARGE_INTEGER     li				= {0};
   DWORD             dwType			= 0;
   LPSTREAM          pstm			= NULL;

    // Open the summay info stream
   sc = pstg->OpenStream(ppropsetstminfo->szName,
                         NULL,
                         STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
                         0,
                         &pstm);

	//If doesn't exist, create a new summary info stream
	if (sc == STG_E_FILENOTFOUND)
		sc = pstg->CreateStream(ppropsetstminfo->szName,
                              STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
							  0,
							  0,
							  &pstm);


   if (FAILED(sc))
	   goto CleanUp;

   
    // Write the PropSet header
	propsethdr.cSections	= 1;
	propsethdr.wByteOrder	= 0xFFFE ;
	propsethdr.wFormat		=  0;
	propsethdr.dwOSVer		= MAKELONG(LOWORD(GetVersion()),2);
	//propsethdr.clsid		=;
	
	if (hr = pstm->Write(&propsethdr, sizeof(propsethdr), &cb))
      goto WriteError;

   // Write the FMTID/OFFSET pair
   cb = propsethdr.cSections * sizeof(FMTIDOFFSET);
   
   if (!SUCCEEDED(hr = MAPIAllocateBuffer(cb, (LPVOID *)&rgfmtidoffset)))
   {
      sc = E_OUTOFMEMORY;
	  goto CleanUp;
   }
   
   pfmtidoffset = rgfmtidoffset;
   pfmtidoffset->fmtid = FMTID_SumInfo;
   pfmtidoffset->dwOffset = sizeof(PROPSETHDR) + sizeof(FMTIDOFFSET);
   
   if (hr = pstm->Write(rgfmtidoffset, cb, &cb))
      goto WriteError;

 
   // Seek to that location in the stream
   LISet32(li, pfmtidoffset->dwOffset);
   if (hr = pstm->Seek(li, STREAM_SEEK_SET, NULL))
      goto CleanUp;

   // Write the section header 
   propsectionhdr.cProps = 5;
   propsectionhdr.cbSection = 2 * sizeof(DWORD) +
							  propsectionhdr.cProps * 4 * sizeof(DWORD)+ 
							  sizeof(CHAR) * (lstrlen(lpsSubject) + 1)+
							  sizeof(CHAR) * (lstrlen(lpsTitle) +	1)+
							  sizeof(CHAR) * (lstrlen(lpsComments) + 1)+
							  sizeof(CHAR) * (lstrlen(lpsAuthor) +  1)+
							  sizeof(CHAR) * (lstrlen(lpsKeywords) + 1) ;

   if (hr = pstm->Write(&propsectionhdr, sizeof(propsectionhdr), NULL))
      goto WriteError;
   

   // Write the PID/OFFSET pairs
   cb = propsectionhdr.cProps * sizeof(PIDOFFSET);
   
   
   if (!SUCCEEDED(hr = MAPIAllocateBuffer(cb, (LPVOID *)&rgpidoffset)))
   {
      sc = E_OUTOFMEMORY;
	  goto CleanUp;
   }
   ppidoffset = rgpidoffset;

   ppidoffset->pid = PID_TITLE; 
   ppidoffset->dwOffset = 12 * sizeof(DWORD);
   ppidoffset++;
   ppidoffset->pid = PID_SUBJECT; 
   ppidoffset->dwOffset = (ppidoffset - 1)->dwOffset + 
							sizeof(CHAR) * (lstrlen(lpsTitle) + 1) + sizeof(DWORD)*2;
   ppidoffset++;
   ppidoffset->pid = PID_AUTHOR; 
   ppidoffset->dwOffset = (ppidoffset - 1)->dwOffset + 
							sizeof(CHAR) * (lstrlen(lpsSubject) + 1) + sizeof(DWORD)*2;
   ppidoffset++;
   ppidoffset->pid = PID_COMMENTS; 
   ppidoffset->dwOffset = (ppidoffset - 1)->dwOffset + 
							sizeof(CHAR) * (lstrlen(lpsAuthor) + 1) + sizeof(DWORD)*2;
   ppidoffset++;
   ppidoffset->pid = PID_KEYWORDS; 
   ppidoffset->dwOffset = (ppidoffset - 1)->dwOffset +
							sizeof(CHAR) * (lstrlen(lpsComments) + 1) + sizeof(DWORD)*2;
   ppidoffset = rgpidoffset;

   if (hr = pstm->Write(rgpidoffset, cb, NULL))
      goto WriteError;

   // Go through all the properties
   for (; propsectionhdr.cProps--; ++ppidoffset)
   {
      // Seek to the data
      LISet32(li, ppidoffset->dwOffset + pfmtidoffset->dwOffset);
      if (hr = pstm->Seek(li, STREAM_SEEK_SET, NULL))
         goto CleanUp;

      // Write the type and property value
      hr = NOERROR;
      switch (ppidoffset->pid)
      {
      case PID_TITLE:

		  dwType = PT_STRING8;
		  if (hr = pstm->Write(&dwType, sizeof(DWORD), &cb))
			goto WriteError;
         sc = ScSaveStr(pstm, lpsTitle);
         break;

      case PID_SUBJECT:
		  
		  dwType = PT_STRING8;
		  if (hr = pstm->Write(&dwType, sizeof(DWORD), &cb))
			goto WriteError;

          sc = ScSaveStr(pstm, lpsSubject);
          break;

      case PID_AUTHOR:
         
		  dwType = PT_STRING8;
		  if (hr = pstm->Write(&dwType, sizeof(DWORD), &cb))
			goto WriteError;
		 
		  sc = ScSaveStr(pstm, lpsAuthor);
		  break;

      case PID_KEYWORDS:
		          
		  dwType = PT_MV_STRING8;
		  if (hr = pstm->Write(&dwType, sizeof(DWORD), &cb))
			goto WriteError;
			
		  sc = ScSaveStr(pstm, lpsKeywords);
		  break;

      case PID_COMMENTS:
        
		  dwType = PT_STRING8;
		  if (hr = pstm->Write(&dwType, sizeof(DWORD), &cb))
			  goto WriteError;
			
		  sc = ScSaveStr(pstm, lpsComments);
          break;

      default:
         continue;
         break;
      }
      if (hr) goto WriteError;
   }

   pstm->Commit(STGC_DEFAULT);

   goto CleanUp;

WriteError:
   sc = GetScode(hr);

CleanUp:
   MAPIFREEBUFFER(rgfmtidoffset);
   MAPIFREEBUFFER(rgpidoffset);
   ULRELEASE(pstm);
   return sc;
}




/*
 * GetSummaryInfo
 *
 */
STDAPI GetSummaryInfo
   (
   LPSTORAGE  pstg,
   CString*	  lpsTitle,
   CString*   lpsSubject,
   CString*   lpsAuthor,
   CString*   lpsKeywords,
   CString*   lpsComments
   )
{
   SCODE             sc				= S_OK;
   HRESULT           hr				= NOERROR;
   PROPSETHDR        propsethdr;
   PROPSECTIONHDR    propsectionhdr;
   FMTIDOFFSET*      rgfmtidoffset	= NULL;
   FMTIDOFFSET*      pfmtidoffset	= NULL;
   PIDOFFSET*        rgpidoffset	= NULL;
   PIDOFFSET*        ppidoffset		= NULL;
   PROPSETSTMINFO*   ppropsetstminfo = rgpropsetstminfo;    // point to summary info part
   ULONG             cb				= 0;
   BOOL              fFound			= FALSE;
   BOOL              fSumInfoStm	= FALSE;
   LARGE_INTEGER     li				={0};
   DWORD             dwType			= 0;
   LPSTREAM          pstm			= NULL;

     
   *lpsTitle   		= TEXT("");		
   *lpsSubject 		= TEXT("");
   *lpsAuthor    	= TEXT("");
   *lpsKeywords		= TEXT("");
   *lpsComments		= TEXT("");
   
   // Open the summay info stream
   sc = pstg->OpenStream(ppropsetstminfo->szName,
                         NULL,
                         STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
                         0,
                         &pstm);
   if (FAILED(sc))
      {
      goto CleanUp;
      }

   // Read the header to find out how many sections we need to search
   if (hr = pstm->Read(&propsethdr, sizeof(propsethdr), NULL))
      goto ReadError;
   if (propsethdr.cSections == 0)
      goto CleanUp;

   // Allocate space for the sections list and read it in
   cb = propsethdr.cSections * sizeof(FMTIDOFFSET);
      
   if (!SUCCEEDED(hr = MAPIAllocateBuffer(cb, (LPVOID *)&rgfmtidoffset)))
   {
      sc = E_OUTOFMEMORY;
	  goto CleanUp;
   }
   pfmtidoffset = rgfmtidoffset;

   if (hr = pstm->Read(rgfmtidoffset, cb, NULL))
      goto ReadError;

   // Look for the section with the matching FMTID
   for (fFound = FALSE; propsethdr.cSections--; ++pfmtidoffset)
   {
      if (IsEqualGUID(*ppropsetstminfo->pfmtid, pfmtidoffset->fmtid))
      {
         fFound = TRUE;
         break;
      }
   }
   if (!fFound)
      goto CleanUp;

   // Are we in the SumInfo stream
   fSumInfoStm = IsEqualGUID(*ppropsetstminfo->pfmtid, FMTID_SumInfo);

   // Seek to that location in the stream
   LISet32(li, pfmtidoffset->dwOffset);
   if (hr = pstm->Seek(li, STREAM_SEEK_SET, NULL))
      goto ReadError;

   // Read the section header to find out how many props we need to read
   if (hr = pstm->Read(&propsectionhdr, sizeof(propsectionhdr), NULL))
      goto ReadError;
   if (propsectionhdr.cProps == 0)
      goto CleanUp;

   // Allocate space for the props list and read it in
   cb = propsectionhdr.cProps * sizeof(PIDOFFSET);
      
   if (!SUCCEEDED(hr = MAPIAllocateBuffer(cb, (LPVOID *)&rgpidoffset)))
   {
      sc = E_OUTOFMEMORY;
	  goto CleanUp;
   }

   ppidoffset = rgpidoffset;

   if (hr = pstm->Read(rgpidoffset, cb, NULL))
      goto ReadError;

   // Go through all the properties
   for (; propsectionhdr.cProps--; ++ppidoffset)
   {
      // Seek to the data
      LISet32(li, ppidoffset->dwOffset + pfmtidoffset->dwOffset);
      if (hr = pstm->Seek(li, STREAM_SEEK_SET, NULL))
         goto ReadError;

      // Read the type
      if (hr = pstm->Read(&dwType, sizeof(DWORD), NULL))
         goto ReadError;


	  // Load the data
      hr = NOERROR;
      switch (ppidoffset->pid)
      {
      case PID_TITLE:
         sc = ScLoadStr(pstm, lpsTitle);
         break;

      case PID_SUBJECT:
         sc = ScLoadStr(pstm, lpsSubject);
         break;

      case PID_AUTHOR:
         sc = ScLoadStr(pstm, lpsAuthor);
         break;

      case PID_KEYWORDS:
		 sc = ScLoadStr(pstm, lpsKeywords);
         break;

      case PID_COMMENTS:
         sc = ScLoadStr(pstm, lpsComments);
         break;

      default:
         continue;
         break;
      }
      if (hr) goto ReadError;
   }

   goto CleanUp;

ReadError:
   sc = GetScode(hr);

CleanUp:
   MAPIFREEBUFFER(rgfmtidoffset);
   MAPIFREEBUFFER(rgpidoffset);
   ULRELEASE(pstm);
   return sc;
}



/*
 * PromoteSummaryInfo
 *
 */
 STDAPI PromoteSummaryInfo
   (
   LPMESSAGE   pmsg,
   LPSTR     lpszTitle,
   LPSTR     lpszSubject,
   LPSTR     lpszAuthor,
   LPSTR     lpszKeywords,
   LPSTR     lpszComments
   )
{
   CONST UINT        cProps = 5;
   HRESULT           hr		= E_OUTOFMEMORY;
   UINT              i		= 0;
   MPPIDMAPIPROP*    pmppidmapipropSumInfo = &mppidmapipropSumInfo[2];  // start at szTitle
   LPMAPINAMEID*     rgpmnid = NULL;
   LPMAPINAMEID      rgmnid	 = NULL;
   LPSPropTagArray   ptaga	 = NULL;
   SPropValue        rgvalSumInfo[cProps];

   if (SUCCEEDED(hr = MAPIAllocateBuffer( cProps * sizeof(LPMAPINAMEID), (LPVOID *)&rgpmnid)))
   {
      if (SUCCEEDED(hr = MAPIAllocateBuffer(cProps * sizeof(MAPINAMEID), (LPVOID*)&rgmnid)))
      {
         // Initialize the name id structure and the array of pointers to the name id structurs
         for (i = 0; i < cProps; i++)
         {
            rgmnid[i].lpguid          = (LPGUID)&PS_PUBLIC_STRINGS;
            rgmnid[i].ulKind          = MNID_STRING;
            rgmnid[i].Kind.lpwstrName = pmppidmapipropSumInfo[i].szW;
            rgpmnid[i] = &rgmnid[i];
         }

         if (SUCCEEDED(hr = pmsg->GetIDsFromNames(cProps, rgpmnid, MAPI_CREATE, &ptaga)))
         {
            if (cProps == ptaga->cValues)
            {
               // Plug the IDs into the values
               for (i = 0; i < cProps && SUCCEEDED(hr);  i++)
               {
                  rgvalSumInfo[i].ulPropTag = PROP_TAG(pmppidmapipropSumInfo[i].wMapiType,
                                                       PROP_ID(ptaga->aulPropTag[i]));

                  switch (i)
                  {
                     case 0:
                        rgvalSumInfo[i].Value.lpszA = (LPTSTR)lpszTitle;
                        break;
                     case 1:
                        rgvalSumInfo[i].Value.lpszA = (LPTSTR)lpszSubject;
                        break;
                     case 2:
                        rgvalSumInfo[i].Value.lpszA = (LPTSTR)lpszAuthor;
                        break;
                     case 3:
                     {
                        rgvalSumInfo[i].Value.lpszA = (LPTSTR)lpszKeywords;

                        hr = ScParseKeywords(&rgvalSumInfo[i], TEXT(";"));
                     }
                        break;
                     case 4:
                        rgvalSumInfo[i].Value.lpszA = (LPTSTR)lpszComments;
                        break;
                  }
				            
               }

               if (SUCCEEDED(hr))
               {
                  // Set the values
                  hr = pmsg->SetProps(cProps, rgvalSumInfo, NULL);
               }

               // Free our prop tag array
               MAPIFREEBUFFER(ptaga);
            }
         }
         MAPIFREEBUFFER(rgmnid);
      }
      MAPIFREEBUFFER(rgpmnid);
   }

   return hr;
}





