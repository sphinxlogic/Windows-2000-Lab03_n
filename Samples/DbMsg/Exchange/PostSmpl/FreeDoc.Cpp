//=========================================================================
// FREEDOC.CPP
//
// Copyright (C) 1986-1996.  Microsoft Corp.  All Rights Reserved.
//
// Purpose:
//    Provides free-floating document routines.
//
//=========================================================================

#include "stdafx.h"
#include <windowsx.h>
#include <winnls.h>
#include <mapinls.h>

#include "PostSmpl.h"
#include "freedoc.h"
#include "PostData.h"
#include "edk.h"

#define cbReadMax         8192
#define cchPathNameMax    320



enum {
   ivalAttAttachMethod,
   ivalAttRenderingPosition,
   ivalAttAttachRendering,
   ivalAttAttachFilename,
   ivalAttAttachLongFilename,
   ivalAttCreationTime,
   ivalAttLastModificationTime,
   cvalAttMax
};

/*
 * CREATEFREEDOC declarations
 */
enum {
   ivalMsgSubject,
   ivalMsgSenderName,
   ivalMsgSentRepresentingName,
   ivalMsgClientSubmitTime,
   ivalMsgMessageDeliveryTime,
   ivalMsgMessageClass,
   ivalMsgMessageFlags,
   ivalMsgSentRepresentingEntryid,
   ivalMsgSenderEntryid,
   ivalMsgSentRepresentingSearchKey,
   ivalMsgSenderSearchKey,
   ivalMsgIcon,
   ivalMsgImportance,
   ivalMsgPriority,
   ivalMsgSensitivity,
   ivalMsgLastModificationTime,
   cvalMsgMax
};


typedef struct
{
   LPTSTR         lpszPathName;
   LPTSTR         lpszFileName;
   LPMESSAGE      pmsg;
   LPATTACH       patt;
   SPropValue     rgvalAtt[cvalAttMax];
   SPropValue     rgvalMsg[cvalMsgMax];
   
} CREATEFREEDOC;


// Added to PROPSET.CPP
STDAPI PromoteSummaryInfo
   (
   LPMESSAGE   pmsg,
   LPSTR     lpszTitle,
   LPSTR     lpszSubject,
   LPSTR     lpszAuthor,
   LPSTR     lpszKeywords,
   LPSTR     lpszComments
   );


// Commonly used LARGE_INTEGER
static LARGE_INTEGER liZero = { 0 };
// Message classes: note class and IPM root class
CONST CHAR szIPMDocument[] = TEXT("IPM.Document");

static SCODE ScLoadAttachDataFromFile(LPSTORAGE pstg, LPTSTR lpszFileName, LPATTACH patt);
static BOOL FGetFileTimes(LPTSTR lpszPathName, FILETIME * pftCreate, FILETIME * pftModify);
static HRESULT HrInitAttachment(
      LPMESSAGE pmsg,
      LPATTACH * ppatt,
      LPSPropValue rgvalAtt,
      LPTSTR lpszPathName,
      LPTSTR lpszFileName);
      
static HGLOBAL HmfpGetIconForFile(LPTSTR lpszPathName, LPTSTR lpszFileName);
static SCODE   ScGetRenderBits(HGLOBAL hmfp, ULONG * pcb, LPBYTE * ppb);
static void    OleUIMetafilePictIconFree(HGLOBAL);


/*
 * HrInitAttachment
 *
 * Purpose:
 *    Initialize a message with a file attachment
 *
 * Arguments:
 *    pmsg           Message to add the attachment to
 *    ppatt          Where to put the attachment
 *    rgvalAtt       Properties for the attachment
 *    lpszFileName        Name of the file
 
 *
 * Returns:
 *    SCODE       the status code;
 */
HRESULT HrInitAttachment(
      LPMESSAGE pmsg,
      LPATTACH * ppatt,
      LPSPropValue rgvalAtt,
      LPTSTR lpszPathName,
      LPTSTR lpszFileName)
 
{
   HRESULT        hr;
   ULONG       ulAttachNum;
   SYSTEMTIME     st;
   SCODE       sc;
   HGLOBAL        hmfp = NULL;

   rgvalAtt[ivalAttAttachRendering].Value.bin.lpb = NULL;
  
   // Copy the file as an attachment
   if (FAILED(hr = pmsg->CreateAttach(
         NULL,
         MAPI_DEFERRED_ERRORS,
         &ulAttachNum,
         ppatt)))
   {
      #ifdef _DEBUG
	  afxDump << TEXT("HrInitAttachment():CreateAttach() failed");
	  #endif

      goto CleanUp;
   }

   
   GetSystemTime(&st);
   SystemTimeToFileTime(&st, &rgvalAtt[ivalAttCreationTime].Value.ft);

   // Make assumptions about the file time properties
   rgvalAtt[ivalAttCreationTime].ulPropTag = PR_CREATION_TIME;
   rgvalAtt[ivalAttLastModificationTime].ulPropTag = PR_LAST_MODIFICATION_TIME;
   rgvalAtt[ivalAttLastModificationTime].Value.ft =
         rgvalAtt[ivalAttCreationTime].Value.ft;

   // Save various properties
   rgvalAtt[ivalAttAttachMethod].ulPropTag = PR_ATTACH_METHOD;
   rgvalAtt[ivalAttAttachMethod].Value.l = ATTACH_BY_VALUE;
   rgvalAtt[ivalAttRenderingPosition].ulPropTag = PR_RENDERING_POSITION;
   rgvalAtt[ivalAttRenderingPosition].Value.l = -1;
   rgvalAtt[ivalAttAttachFilename].ulPropTag = PR_ATTACH_FILENAME;
   rgvalAtt[ivalAttAttachFilename].Value.LPSZ = lpszFileName;
   rgvalAtt[ivalAttAttachLongFilename].ulPropTag = PR_ATTACH_LONG_FILENAME;
   rgvalAtt[ivalAttAttachLongFilename].Value.LPSZ = lpszFileName;

   // Also need to set icon for the attachment
   // Determine the icon to use with this file
   rgvalAtt[ivalAttAttachRendering].ulPropTag = PR_ATTACH_RENDERING;
   hmfp = HmfpGetIconForFile(lpszPathName, lpszFileName);
   if (!hmfp)
   {
      hr = ResultFromScode(E_OUTOFMEMORY);
      goto CleanUp;
   }
   if (sc = ScGetRenderBits(hmfp,
                     &rgvalAtt[ivalAttAttachRendering].Value.bin.cb,
                     &rgvalAtt[ivalAttAttachRendering].Value.bin.lpb))
   {
      hr = ResultFromScode(sc);
      goto CleanUp;
   }

CleanUp:

   OleUIMetafilePictIconFree(hmfp);

   return hr;
}


/*
 * HrInitCFD
 *
 * Purpose:
 *    Initialize the contents of CFD.
 *
 * Arguments:
 *    pcfd        pointer to a CFD
 *
 * Returns:
 *    HRESULT        Any error that has occured
 */

HRESULT HrInitCFD(LPMAPIFOLDER pfld, CREATEFREEDOC* pcfd)
{
   HRESULT        hr;
   LPSPropValue   rgvalMsg = pcfd->rgvalMsg;
   LPSPropValue   rgvalAtt = pcfd->rgvalAtt;

   // Create a new message for the docfile
   if (FAILED(hr = pfld->CreateMessage(
         NULL,
         MAPI_DEFERRED_ERRORS,
         &pcfd->pmsg)))
   {
      #ifdef _DEBUG
	  afxDump << TEXT("HrInitCFD():CreateMessage() failed");
	  #endif

      goto Cleanup;
   }

   // Get the initalize attachment settings
   if (FAILED(hr = HrInitAttachment(
         pcfd->pmsg,
         &pcfd->patt,
         rgvalAtt,
         pcfd->lpszPathName,
         pcfd->lpszFileName
         )))
   {
      goto Cleanup;
   }

   // Set up the delivery time
   rgvalMsg[ivalMsgMessageDeliveryTime].Value.ft =
      rgvalAtt[ivalAttCreationTime].Value.ft;

Cleanup:
   return hr;
}

/*
 * ReleaseCFD
 *
 * Purpose:
 *    Clean up the contents of a CFD
 *
 * Arguments:
 *    pcfd        pointer to a CFD
 *
 * Returns:
 *    None.
 */
VOID ReleaseCFD(CREATEFREEDOC* pcfd)
{
   ULRELEASE(pcfd->pmsg);
   ULRELEASE(pcfd->patt);
   MAPIFREEBUFFER(pcfd->rgvalAtt[ivalAttAttachRendering].Value.bin.lpb);
   
}


/*
 * ScCreateFreeDocFinal
 *
 * Purpose:
 *    Common code that takes care of setting message properties
 *
 * Arguments:
 *    pfld        the folder where to create the FreeDoc
 *    lpszFileName     the filename
 *
 * Returns:
 *    SCODE       the status code
 */
SCODE ScCreateFreeDocFinal
   (
   CREATEFREEDOC* pcfd,
   LPSTR        lpszTitle,
   LPSTR        lpszSubject,
   LPSTR        lpszAuthor,
   LPSTR        lpszKeywords,
   LPSTR        lpszComments
   )
{
   HRESULT        hr;
   SCODE		  sc = S_OK;
   LPSPropValue   rgvalMsg	= pcfd->rgvalMsg;
   LPSPropValue   rgvalAtt	= pcfd->rgvalAtt;
   LPSPropValue   pvalName	= NULL;
   LPSPropValue   pvalKey	= NULL;
   LPTSTR         lpszProgId= NULL;
   LPTSTR         lpszClass = NULL;
   ULONG		  cbEid		= 0;
   LPENTRYID      peid		= NULL;
   ULONG		  ulObjType = 0;
   LPMAPIPROP     pmp		= NULL;
   LPMAPISESSION  pses		= NULL;
   ULONG		  cvalMsg	= cvalMsgMax - 1;  
   LPBYTE         lpbDest	= NULL;
   SHFILEINFO     sfi		= {0};


   static CHAR   szScCreateFreeDocFinal1[] = TEXT("%s.%s");


   // Set the properties
   if (sc = ((LPMAPIPROP)pcfd->patt)->SetProps(cvalAttMax, rgvalAtt, NULL))
      goto CleanUp;

   // Default the times
   rgvalMsg[ivalMsgClientSubmitTime].Value.ft =
                        rgvalAtt[ivalAttCreationTime].Value.ft;
   rgvalMsg[ivalMsgLastModificationTime].Value.ft =
                        rgvalAtt[ivalAttLastModificationTime].Value.ft;

   
   // Find out the app name
   if (lpszProgId)
   {
	  sc = MAPIAllocateBuffer((lstrlen(szIPMDocument) + lstrlen(lpszProgId) + 2) * sizeof(CHAR), (LPVOID *)&lpszClass);
	  if (FAILED(sc))
      {
         sc = E_OUTOFMEMORY;
         goto CleanUp;
      }
      wsprintf(lpszClass, szScCreateFreeDocFinal1, szIPMDocument, lpszProgId);
      rgvalMsg[ivalMsgMessageClass].Value.LPSZ = lpszClass;
   }
   else
      rgvalMsg[ivalMsgMessageClass].Value.LPSZ = (LPTSTR) szIPMDocument;

   // Save the changes to the attachment
   if (sc = pcfd->patt->SaveChanges(0))
   {
      #ifdef _DEBUG
	  afxDump << TEXT("ScCreateFreeDocFinal:SaveChanges() failed");
	  #endif

      goto CleanUp;
   }

   //Shared folder doesn't like us keeping the attachment open
   pcfd->patt->Release();
   pcfd->patt = NULL;

   // Find out the user's name
   // AddRefObj(pses = CENT(pses));
   pses = PostData.m_lpSession;
   pses->AddRef();

   if (pses)
   {
      // Determine our identity
      if (FAILED(hr = pses->QueryIdentity(&cbEid, &peid)))
      {
		 #ifdef _DEBUG
		 afxDump << TEXT("ScCreateFreeDocFinal:QueryIdentity() failed");
		 #endif


         goto CleanUp;
      }

      // Get the object referring to our identity
      if (hr = pses->OpenEntry(cbEid, peid, NULL, MAPI_DEFERRED_ERRORS,
                               &ulObjType, (LPUNKNOWN *) &pmp))
      {
         #ifdef _DEBUG
		 afxDump << TEXT("ScCreateFreeDocFinal:OpenEntry() failed");
		 #endif

         goto CleanUp;
      }

      // Get the display name
      if (sc = HrGetOneProp(pmp, PR_DISPLAY_NAME, &pvalName))
         goto CleanUp;
      if (sc = HrGetOneProp(pmp, PR_SEARCH_KEY, &pvalKey))
         goto CleanUp;
   }

	//If subject is not specified then use file's displayname as default subject
	if (!lpszSubject)
	{
		if (SHGetFileInfo(
			 pcfd->lpszPathName,
			0,
			&sfi,
			sizeof(SHFILEINFO),
			SHGFI_DISPLAYNAME))
		{
			lpszSubject = sfi.szDisplayName;
		}
		else
		{
			lpszSubject = pcfd->lpszFileName;
		}
	}

   // Set up the propvals
   rgvalMsg[ivalMsgSubject].ulPropTag = PR_SUBJECT;
   rgvalMsg[ivalMsgSubject].Value.LPSZ = lpszSubject;
   rgvalMsg[ivalMsgSenderName].ulPropTag = PR_SENDER_NAME;
   rgvalMsg[ivalMsgSentRepresentingName].ulPropTag = PR_SENT_REPRESENTING_NAME;
   rgvalMsg[ivalMsgSenderName].Value.LPSZ =
   rgvalMsg[ivalMsgSentRepresentingName].Value.LPSZ =
                        pvalName ? pvalName->Value.LPSZ : (LPTSTR) "";
   rgvalMsg[ivalMsgClientSubmitTime].ulPropTag = PR_CLIENT_SUBMIT_TIME;
   rgvalMsg[ivalMsgMessageDeliveryTime].ulPropTag = PR_MESSAGE_DELIVERY_TIME;
   rgvalMsg[ivalMsgMessageClass].ulPropTag = PR_MESSAGE_CLASS;
   rgvalMsg[ivalMsgMessageFlags].ulPropTag = PR_MESSAGE_FLAGS;
   rgvalMsg[ivalMsgMessageFlags].Value.l = 0;
   rgvalMsg[ivalMsgSentRepresentingEntryid].ulPropTag =
                        PR_SENT_REPRESENTING_ENTRYID;
   rgvalMsg[ivalMsgSenderEntryid].ulPropTag = PR_SENDER_ENTRYID;
   rgvalMsg[ivalMsgSentRepresentingEntryid].Value.bin.cb =
   rgvalMsg[ivalMsgSenderEntryid].Value.bin.cb = cbEid;
   rgvalMsg[ivalMsgSentRepresentingEntryid].Value.bin.lpb =
   rgvalMsg[ivalMsgSenderEntryid].Value.bin.lpb = (LPBYTE) peid;
   rgvalMsg[ivalMsgSentRepresentingSearchKey].ulPropTag = PR_SENT_REPRESENTING_SEARCH_KEY;
   rgvalMsg[ivalMsgSenderSearchKey].ulPropTag = PR_SENDER_SEARCH_KEY;
   rgvalMsg[ivalMsgSentRepresentingSearchKey].Value.bin.cb =
   rgvalMsg[ivalMsgSenderSearchKey].Value.bin.cb = pvalKey ? pvalKey->Value.bin.cb : 0;
   rgvalMsg[ivalMsgSentRepresentingSearchKey].Value.bin.lpb =
   rgvalMsg[ivalMsgSenderSearchKey].Value.bin.lpb = pvalKey ? pvalKey->Value.bin.lpb : NULL;
   rgvalMsg[ivalMsgIcon].ulPropTag = PR_ICON;
   rgvalMsg[ivalMsgIcon].Value = rgvalAtt[ivalAttAttachRendering].Value;
   rgvalMsg[ivalMsgImportance].ulPropTag = PR_IMPORTANCE;
   rgvalMsg[ivalMsgImportance].Value.l = IMPORTANCE_NORMAL;
   rgvalMsg[ivalMsgPriority].ulPropTag = PR_PRIORITY;
   rgvalMsg[ivalMsgPriority].Value.l = PRIO_NORMAL;
   rgvalMsg[ivalMsgSensitivity].ulPropTag = PR_SENSITIVITY;
   rgvalMsg[ivalMsgSensitivity].Value.l = SENSITIVITY_NONE;
   rgvalMsg[ivalMsgLastModificationTime].ulPropTag = PR_LAST_MODIFICATION_TIME;


   // Set the message properties
   if (sc = ((LPMAPIPROP)pcfd->pmsg)->SetProps(cvalMsg, pcfd->rgvalMsg, NULL))
      goto CleanUp;

      
   // Set the summary info properties if they have been specified
   if (lpszTitle
         || lpszSubject
         || lpszAuthor
         || lpszKeywords
         || lpszComments)
      {
   
		PromoteSummaryInfo(pcfd->pmsg, lpszTitle, lpszSubject, lpszAuthor, lpszKeywords, lpszComments);
   
      }

   sc = pcfd->pmsg->SaveChanges(0);

CleanUp:
   
   MAPIFREEBUFFER(lpbDest);
   MAPIFREEBUFFER(peid);
   MAPIFREEBUFFER(pvalName);
   MAPIFREEBUFFER(pvalKey);
   MAPIFREEBUFFER(lpszProgId);
   MAPIFREEBUFFER(lpszClass);
   ULRELEASE(pmp);
   ULRELEASE(pses);
   return sc;
}


/*
 * ScCreateFreeDoc
 *
 * Purpose:
 *    Creates a FreeDoc out of a file
 *
 * Arguments:
 *    pfld        the folder where to create the FreeDoc
 *    lpszFileName     the filename
 *
 * Returns:
 *    SCODE       the status code
 */
SCODE ScCreateFreeDoc
   (
   LPSTORAGE	  pstg,
   LPMAPIFOLDER   pfld,
   LPSTR          lpszPathName,
   LPSTR		  lpszFileName,
   LPSTR          lpszTitle,
   LPSTR          lpszSubject,
   LPSTR          lpszAuthor,
   LPSTR          lpszKeywords,
   LPSTR          lpszComments
   )
{
   CREATEFREEDOC  cfd;
   SCODE       sc = S_OK;


   ZeroMemory(&cfd, sizeof(CREATEFREEDOC));

   // Make sure we aren't trying to attach a directory
   if (GetFileAttributes(lpszPathName) & FILE_ATTRIBUTE_DIRECTORY)
   {
     #ifdef _DEBUG
	 afxDump << TEXT("ScCreateFreeDoc:Trying to attach a directory");
	 #endif
	 goto CleanUp;
   }


   cfd.lpszPathName = lpszPathName;
   cfd.lpszFileName = lpszFileName;

   if (sc = GetScode(HrInitCFD(pfld, &cfd)))
      goto CleanUp;

   // Load the file into the attachment
   if (FAILED(sc = ScLoadAttachDataFromFile(pstg, lpszPathName, cfd.patt)))
   {
      goto CleanUp;
   }

   // Get the file time properties
   FGetFileTimes(lpszPathName, &cfd.rgvalAtt[ivalAttCreationTime].Value.ft,
               &cfd.rgvalAtt[ivalAttLastModificationTime].Value.ft);

   

   if (SUCCEEDED(sc))
   {
      sc = ScCreateFreeDocFinal(&cfd,
                                lpszTitle,
                                lpszSubject,
                                lpszAuthor,
                                lpszKeywords,
                                lpszComments);
   }

CleanUp:
   ReleaseCFD(&cfd);
   return sc;
}



/*
 * ScLoadAttachDataFromFile
 *
 * Purpose:
 *    Reads in a file into the attachment's data stream
 *
 * Arguments:
 *    lpszFileName     the file to be read in
 *    patt        the attachment
 *
 * Returns:
 *    SCODE       S_OK or an error code
 */
SCODE ScLoadAttachDataFromFile(LPSTORAGE pstg, LPTSTR lpszPathName, LPATTACH patt)
{
   SCODE       sc		= E_FAIL; // MAIL_E_STREAMINFILE;
   HRESULT     hr		= NOERROR;
   LPSTREAM    pstm		= NULL;
   UINT        cbRead	= 0;
   ULONG       cbWritten= 0;
   
   
   // Get a stream interface from the attachment data
   if (hr = patt->OpenProperty(PR_ATTACH_DATA_BIN,
         (LPIID) &IID_IStream, STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
         MAPI_CREATE | MAPI_MODIFY | MAPI_DEFERRED_ERRORS,
         (LPUNKNOWN *) &pstm))
   {
      #ifdef _DEBUG
	  afxDump << TEXT(" ScLoadAttachDataFromFile:OpenProperty() failed");
	  #endif
	  goto CleanUp;
   }

   
   // Reset the destination stream to the start
   if (hr = pstm->Seek(liZero, STREAM_SEEK_SET, NULL))
   {
      #ifdef _DEBUG
	  afxDump << TEXT(" ScLoadAttachDataFromFile:pstm->Seek failed");
	  #endif
      goto CleanUp;
   }

   cbRead = sizeof(CHAR)*(lstrlen(theApp.m_lpBuffer) + 1);
   if (hr = pstm->Write(theApp.m_lpBuffer, cbRead, &cbWritten))
   {
        #ifdef _DEBUG
		afxDump << TEXT(" ScLoadAttachDataFromFile:pstm->Write() failed");
		#endif
		goto CleanUp;
	}

   sc = S_OK;
   goto CleanUp;

CleanUp:
   ULRELEASE(pstm);
   return sc;

}



/*
 * FGetFileTimes
 *
 * Purpose:
 *    Gets a file's create and modify times
 *
 * Arguments:
 *    szPathName        The file name
 *    pftCreate         The creation time
 *    pftModify         The modify time
 *
 * Returns:
 *    BOOL           TRUE on success
 */
BOOL FGetFileTimes(LPTSTR lpszPathName, FILETIME * pftCreate,
               FILETIME * pftModify)
{
   BOOL     fSuccess = FALSE;
   FILETIME ftBlank = { 0 };

   HANDLE   hFile;

   if (pftCreate)
      *pftCreate = ftBlank;
   if (pftModify)
      *pftModify = ftBlank;
   hFile = CreateFile(lpszPathName, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
                  OPEN_EXISTING, 0, NULL);
   if (hFile)
      fSuccess = GetFileTime(hFile, pftCreate, NULL, pftModify);

   CloseHandle(hFile);


   // Try putting in last modify if can't get create time
   if (pftCreate &&
      pftModify &&
      !pftCreate->dwLowDateTime &&
      !pftCreate->dwHighDateTime)
      *pftCreate = *pftModify;
   return fSuccess;
}


/*
 * HmfpGetIconForFile
 *
 * Purpose:
 *    A centralized place to create a metafile picture of an icon and label
 *
 * Arguments:
 *    lpszPathName     The path to the file we need an icon for
 *    lpszFileName     The filename which becomes the label
 *
 * Returns:
 *    HGLOBAL        Handle to METAFILEPICT metafile with icon and label
 */

HGLOBAL HmfpGetIconForFile(LPTSTR lpszPathName, LPTSTR lpszFileName)
{
   HGLOBAL  hmfp;
   HICON hicon = NULL;
   CHAR szDllName[cchPathNameMax];
   UINT  iIcon = 0;
   UsesMakeOLESTR;

   
   // Use filename if no pathname supplied
   if (!lpszPathName)
      lpszPathName = lpszFileName;

   szDllName[0] = 0;
   
   hmfp = OleGetIconOfFile(MakeOLESTR(lpszPathName), FALSE);
   return hmfp;
}


/*
 * ScGetRenderBits
 *
 * Purpose:
 *    Prepares a transportable metafile picture
 *
 * Arguments:
 *    hmfp        The metafile picture
 *    pcb            The size of the transportable data
 *    ppb            Pointer to the data
 *
 * Returns:
 *    SCODE       The status code
 */
SCODE ScGetRenderBits(HGLOBAL hmfp, ULONG * pcb, LPBYTE * ppb)
{
   SCODE          sc = S_OK;
   LPMETAFILEPICT    pmfp = NULL;
   HMETAFILE         hmf = NULL;
   UINT           cbMF = 0;
   WORD           wCheck = 0;

   // Clear out our out parameters
   *pcb = 0;
   *ppb = NULL;

   // Lock down our data
   pmfp = (LPMETAFILEPICT)GlobalLock(hmfp);
   if (!pmfp)
      goto MemErr;

   // How much room do we need
   hmf = pmfp->hMF;

   cbMF = GetMetaFileBitsEx(hmf, 0, NULL);
   if (!cbMF)
   {
      sc = E_FAIL;
      goto CleanUp;
   }

   *pcb = cbMF;

   // Allocate that space
    sc = MAPIAllocateBuffer(*pcb, (LPVOID *)ppb);
	if (FAILED(sc))
		goto MemErr;

   // Put together the header


   // Get the data for real
#ifdef DEBUG
   cbMF =
#endif
   GetMetaFileBitsEx(hmf, cbMF, *ppb);
   


   goto CleanUp;

MemErr:
   sc = E_OUTOFMEMORY;

CleanUp:
   if (pmfp)
      GlobalUnlock(hmfp);
   return sc;
}




/*
 * OleUIMetafilePictIconFree
 *
 * Purpose:
 *  Deletes the metafile contained in a METAFILEPICT structure and
 *  frees the memory for the structure itself.
 *
 * Parameters:
 *  hMetaPict       HGLOBAL metafilepict structure created in
 *                  OleMetafilePictFromIconAndLabel
 *
 * Return Value:
 *  None
 */

void OleUIMetafilePictIconFree(HGLOBAL hMetaPict)
   {

   LPMETAFILEPICT      pMF;

   if (NULL==hMetaPict)
      return;

   pMF=(LPMETAFILEPICT)GlobalLock(hMetaPict);

   if (NULL!=pMF)
      {
      if (NULL!=pMF->hMF)
         DeleteMetaFile(pMF->hMF);
      }

   GlobalUnlock(hMetaPict);
   GlobalFree(hMetaPict);

   return;
   }


