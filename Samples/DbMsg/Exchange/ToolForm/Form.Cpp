// --form.cpp-----------------------------------------------------------------
//
//   Implementation of the FRM class
//
//   Implements a simple form that holds information about a software 
//   testing/development tool.  This form can be installed in 
//   a public folder, and then forms of this type can be placed in 
//   the public folder to create a database of software tools.
//   Th form holds the following information:
//
//   * A topic, giving a brief description of the tool, which 
//     appears as the subject in the folder list.
//   * Name of the tool
//   * The platform the tool runs on
//   * The type of tool
//   * The Operating System the tool runs under
//   * Who developed the tool
//   * The location of the tool
//   * An introduction, giving a longer description of the tool.
//   
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// ---------------------------------------------------------------------------

#include "stdafx.h"
#include "tool.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define new DEBUG_NEW

#include <ole2.h>
DEFINE_GUID(CLSID_MyFormsClsId,  0x861E4010, 0x5030, 0xFEDC, 0x99, 0x12, 0x00, 0x0a, 0x00, 0x38, 0x90, 0x1b);

#include "formdata.h"
#include "form.h"
#include "tooldoc.h"
#include "toolform.h"

HINSTANCE hinstOle   = NULL;
HINSTANCE hinstMapi  = NULL;

#ifdef WIN16
LPFNISEQUALGUID           lpfnIsEqualGUID;
#endif
LPFNCOREGISTERCLASSOBJECT lpfnCoRegisterClassObject;
LPFNHRQUERYALLROWS        lpfnHrQueryAllRows       ;
LPFNMAPIFREEBUFFER        lpfnMAPIFreeBuffer       ;
LPFNMAPIINITIALIZE        lpfnMAPIInitialize       ;
LPFNMAPIUNINITIALIZE      lpfnMAPIUninitialize     ;
FRMFAC *                  g_pfrmfac = NULL;


//$--HrStartOleAndRegisterClassFactory----------------------------------------
//
//  Purpose:
//      Initialize OLE, MAPI, and the Forms Interface
//      Should be called from WinMain() or InitApplication() in an SDI app
//
//      This function LoadLibraries the neccessary DLLs rather than
//      linking with them.  This permits the form to run as a stand-
//      alone executable even when MAPI and OLE are not installed.
//
//  Returns:
//      HRESULT
// ---------------------------------------------------------------------------
HRESULT HrStartOleAndRegisterClassFactory(void)
{
    HRESULT     hr      = NOERROR;

    // ----- LoadLibrary the essentials
    hinstOle   = LoadLibrary(szOleDll);
    hinstMapi  = LoadLibrary(szMapiDll);
    #ifdef WIN16
    if (hinstOle   < HINSTANCE_ERROR) hinstOle   = 0;
    if (hinstMapi  < HINSTANCE_ERROR) hinstMapi  = 0;
    #endif
    if (0 == hinstOle || 0 == hinstMapi)
    {
        return ResultFromScode(E_FAIL);
    }
        

    // ----- Setup a few function pointers
    lpfnCoRegisterClassObject = (LPFNCOREGISTERCLASSOBJECT) GetProcAddress(hinstOle,  "CoRegisterClassObject");
	lpfnHrQueryAllRows        = (LPFNHRQUERYALLROWS       ) GetProcAddress(hinstMapi,"HrQueryAllRows");
	if (NULL == lpfnHrQueryAllRows)
	{
		lpfnHrQueryAllRows    = (LPFNHRQUERYALLROWS       ) GetProcAddress(hinstMapi,"HrQueryAllRows@24");
	}
#ifndef WIN32
    lpfnIsEqualGUID           = (LPFNISEQUALGUID          ) GetProcAddress(hinstOle,  "IsEqualGUID");
#endif
    lpfnMAPIFreeBuffer        = (LPFNMAPIFREEBUFFER       ) GetProcAddress(hinstMapi,"MAPIFreeBuffer");
    lpfnMAPIInitialize        = (LPFNMAPIINITIALIZE       ) GetProcAddress(hinstMapi,"MAPIInitialize");
    lpfnMAPIUninitialize      = (LPFNMAPIUNINITIALIZE     ) GetProcAddress(hinstMapi,"MAPIUninitialize");

    ASSERT(lpfnCoRegisterClassObject);
    ASSERT(lpfnHrQueryAllRows);
    ASSERT(lpfnMAPIFreeBuffer);
    ASSERT(lpfnMAPIInitialize);
    ASSERT(lpfnMAPIUninitialize);

    if (NULL == lpfnCoRegisterClassObject ||
        NULL == lpfnHrQueryAllRows        ||
        NULL == lpfnMAPIFreeBuffer        ||
        NULL == lpfnMAPIInitialize        ||
        NULL == lpfnMAPIUninitialize      )
    {
        return ResultFromScode(E_FAIL);
    }    

    // ----- Initialize MAPI
    hr = lpfnMAPIInitialize(NULL);

    if (FAILED(hr))
    {
        return hr;
    }

    // ----- Allocate Memory for our class factory
    TRY
    {
        g_pfrmfac = new FRMFAC;
    }
    CATCH(CMemoryException, e)
    {
        hr = ResultFromScode(E_OUTOFMEMORY);
        return hr;
    }
    END_CATCH

    // ----- Register our class object(s)
    DWORD dwRegMyForm = 0;
    hr = lpfnCoRegisterClassObject(CLSID_MyFormsClsId, (LPUNKNOWN)g_pfrmfac,
            CLSCTX_LOCAL_SERVER, REGCLS_SINGLEUSE,
            &dwRegMyForm); /* switch singleuse to multipleuse if you are an MDI app */

    return hr;
}


//$--HrStopForms--------------------------------------------------------------
//
//  Purpose:
//      UnInitialize OLE, MAPI, and the Forms Interface
//
//  Returns:
//      HRESULT == 0
// ---------------------------------------------------------------------------
HRESULT HrStopForms(void)
{
    HRESULT hr = ResultFromScode(S_OK);

    if (g_pfrmfac)
        delete g_pfrmfac;

    if (lpfnMAPIUninitialize)
        lpfnMAPIUninitialize();

    FreeLibrary(hinstOle);
    FreeLibrary(hinstMapi);

    return hr;
}

// Tool form specific methods follow ///////////////////////////


//$--FRM::FRM-----------------------------------------------------------------
//
//  Purpose:
//      Initialize or new form object
//
//----------------------------------------------------------------------------
FRM::FRM(REFCLSID clsid)
{
    LONG i;

    m_cRef = 1;
    m_clsid = clsid;

    m_pMessage = NULL;
    m_pMessageSite = NULL;
    m_pSession = NULL;

    m_pFormMgr = NULL;
    m_pFormInfo = NULL;

    m_fDirty = FALSE;

    for (i=0; i<MAX_ADVISE; i++)
    {
        m_aAdvisePtrs[i] = NULL;
        m_afAdvisee[i] = 0;
    }
}


//$--FRM::~FRM----------------------------------------------------------------
//
//  Purpose:
//      Destroy our form object
//
//----------------------------------------------------------------------------
FRM::~FRM()
{
    ASSERT(0 == m_cRef);
    ASSERT(NULL == m_pMessage);
    ASSERT(NULL == m_pMessageSite);
    ASSERT(NULL == m_pSession);
}


//$--FRM::SendForm------------------------------------------------------------
//  
//
//  Purpose:
//      Have the message site send us
//      (also tries to send the message using mapi if message site fails)
//
//  Returns:
//      HRESULT             Error status.
//----------------------------------------------------------------------------
HRESULT FRM::SendForm(VOID)
{
    HRESULT hr = S_OK;

    ASSERT(m_cRef > 0);
    ASSERT(m_pMessageSite);
    ASSERT(m_pMessage);

    // ----- Submit message
    hr = m_pMessageSite->SubmitMessage(0);

    if (FAILED(hr))
    {
        return hr;
    }
    // ----- advise everyone of what we just did
    ADVISE(OnSubmitted);

    return hr;
}


//$--FRM::LaunchReplyMessage--------------------------------------------------
//  
//  Purpose:
//      Construct a reply to PR_SENDER* (note: ignoring sent representing)
//      Display any form user interface on the existing form
//
//  Returns:
//      HRESULT             Error status.
//----------------------------------------------------------------------------
HRESULT
FRM::LaunchReplyMessage(ULONG ulhwndParent) // Parent window
{
    ULONG itaga;
    ADRLIST al = {1,0}; /* our adrlist will have exactly one entry */
    HRESULT hr = S_OK;
    LPMAPIMESSAGESITE pNewMessageSite;
    LPMAPIVIEWCONTEXT pNewMapiViewContext;
    LPMESSAGE pNewMessage;

    SizedSPropTagArray(6,tagaSender) =
        { 6,
        { PR_RECIPIENT_TYPE,
            PR_SENDER_NAME,
            PR_SENDER_ADDRTYPE,
            PR_SENDER_ENTRYID,
            PR_SENDER_EMAIL_ADDRESS,
            PR_SENDER_SEARCH_KEY } };
    SizedSPropTagArray(6,tagaRepliee) =
        { 6,
        { PR_RECIPIENT_TYPE,
            PR_DISPLAY_NAME,
            PR_ADDRTYPE,
            PR_ENTRYID,
            PR_EMAIL_ADDRESS,
            PR_SEARCH_KEY
        } };
    static SizedSPropTagArray(26,tagaRemoveFromNewReply) =
        { 26,
        {   // Stuff you would typically want to remove on reply
            PR_MESSAGE_FLAGS,               // Want unsent compose note
            PR_MESSAGE_RECIPIENTS,          // Will generate new recip list
            PR_SENDER_ENTRYID,              // Clear sender/recipient info
            PR_SENDER_NAME,                 //
            PR_RECEIVED_BY_ENTRYID,         //
            PR_RECEIVED_BY_NAME,            //
            PR_SENT_REPRESENTING_ENTRYID,   // Clear delegate access stuff
            PR_SENT_REPRESENTING_NAME,      //
            PR_SENT_REPRESENTING_ADDRTYPE,  // 10961
            PR_SENT_REPRESENTING_EMAIL_ADDRESS,
            PR_RCVD_REPRESENTING_ENTRYID,   // 
            PR_RCVD_REPRESENTING_NAME,      //
            PR_READ_RECEIPT_ENTRYID,        // Clear destination overrides
            PR_REPORT_ENTRYID,              //
            PR_REPLY_RECIPIENT_ENTRIES,     //
            PR_REPLY_RECIPIENT_NAMES,       //
            PR_ORIGINATOR_DELIVERY_REPORT_REQUESTED, // Clear delivery receipt
            PR_READ_RECEIPT_REQUESTED,      // Clear read receipt
            PR_CLIENT_SUBMIT_TIME,          // Clear submit time
            PR_MESSAGE_ATTACHMENTS,         // Drop attachments on reply
            PR_ORIGINAL_AUTHOR_ENTRYID,     // Keep original author information
            PR_ORIGINAL_AUTHOR_NAME,        //  on forwards
            PR_ORIGINAL_SUBMIT_TIME,        // Keep original time on forwards
            PR_IMPORTANCE,                  // Lose importance on reply
            PR_PRIORITY,                    // Lose priority on reply
            PR_SENSITIVITY                  // Lose sensitivity on reply
        } };

    ASSERT(m_cRef > 0);
    ASSERT(m_pMessageSite);
    ASSERT(m_pSession);
    ASSERT(m_pMessage);

    // ----- Create the reply message
    hr = m_pMessageSite->NewMessage(0,NULL,
        this, &pNewMessage,&pNewMessageSite,&pNewMapiViewContext);
    if (FAILED(hr))
    {
        return hr;
    }

    ASSERT(pNewMessage);
    ASSERT(pNewMessageSite);
    ASSERT(pNewMapiViewContext);

    // ----- Copy current message to new message
    hr = m_pMessage->CopyTo(0, NULL, (LPSPropTagArray)&tagaRemoveFromNewReply, 0, NULL,
                                    (LPIID) &IID_IMessage, pNewMessage, 0, NULL);
    if (FAILED(hr))
    {
        return hr;
    }

    // ----- who sent this to us?
    hr = m_pMessage->GetProps((LPSPropTagArray) &tagaSender, 0, &al.aEntries[0].cValues, &al.aEntries[0].rgPropVals);
    
    ASSERT(ResultFromScode(MAPI_W_ERRORS_RETURNED) == hr);

    // ----- Make the sender the recipient
    if (al.aEntries && al.aEntries[0].rgPropVals)
    {
        al.aEntries[0].rgPropVals[0].ulPropTag = PR_RECIPIENT_TYPE;
        al.aEntries[0].rgPropVals[0].Value.ul = MAPI_TO;
    }
    else
    {
        return ResultFromScode(E_FAIL);
    }

    // ----- Set our new recipients properties to their expected property ids
    itaga = 1;

    for (itaga = 1; itaga < tagaRepliee.cValues; itaga++)
    {
        al.aEntries[0].rgPropVals[itaga].ulPropTag =
            PROP_TAG(PROP_TYPE(al.aEntries[0].rgPropVals[itaga].ulPropTag),
                PROP_ID(tagaRepliee.aulPropTag[itaga]));


        ASSERT(SUCCEEDED(al.aEntries[0].rgPropVals[itaga].Value.ul));
    }

    // ----- Save out addresses
    ASSERT(1 == al.cEntries);
    hr = pNewMessage->ModifyRecipients(0, &al);
    if (FAILED(hr) )
    {
        return hr;
    }

    // ----- Call Load (this makes the current form the new form)
    hr = Load(pNewMessageSite,pNewMessage,0,MSGFLAG_UNSENT);
    if (FAILED(hr))
    {
        return hr;
    }


    // ----- Call DoVerb So we can see the reply form
    hr = DoVerb(OLEIVERB_PRIMARY,NULL,ulhwndParent,NULL);
    if (FAILED(hr))
    {
        return hr;
    }

    // ----- release stuff
    pNewMessage->Release();
    pNewMessageSite->Release();
    pNewMapiViewContext->Release();
    lpfnMAPIFreeBuffer(al.aEntries[0].rgPropVals);

    return hr;

}

//$--FRM::GetFormData---------------------------------------------------------
//
//  Purpose:
//      Allows anyone to query the form for it's current data
//
//  Returns:
//      void
//----------------------------------------------------------------------------
VOID FRM::GetFormData(CFormData& theLocalFormData)
{
    ASSERT(m_cRef > 0);

	theLocalFormData = m_theFormData;
}


//$--FRM::SetFormData---------------------------------------------------------
//  
//
//  Purpose:
//      Allows anyone to set the forms current data members
//
//  Returns:
//      void
//----------------------------------------------------------------------------
VOID FRM::SetFormData(const CFormData& theLocalFormData)
{
    ASSERT(m_cRef > 0);

	m_theFormData = theLocalFormData;

    m_fDirty = TRUE;
}


//$--FRM::AddressForm---------------------------------------------------------
//  
//  Purpose:
//      Add the address "Tools" to the "To:" list for the form.
//
//  Returns:
//      HRESULT Error Status.
//----------------------------------------------------------------------------
HRESULT
FRM::AddressForm(
         HWND hwnd,                     // parent
         BOOL fDontShowIfRecipsExist)   // true if no user interface should
                                        // be presented when recipients are
                                        // already present
{
    LPADRBOOK		pAdrBook	= NULL;
	ULONG			cbeid		= 0;
	LPENTRYID		lpeid		= NULL;
    ULONG			ulUIParam = (ULONG) (UINT) hwnd;
    HRESULT			hr = S_OK;    
    LPADRLIST		pal = NULL;
	LPSPropValue	rgAdrProps	= NULL;

    ASSERT(m_cRef > 0);
    ASSERT(m_pMessageSite);
    ASSERT(m_pSession);
    ASSERT(m_pMessage);

    // ----- remember address book from the session
    hr = m_pSession->OpenAddressBook(0, NULL, AB_NO_DIALOG, &pAdrBook);
	if (FAILED(hr))
    {
        goto cleanup;
    }

	hr = MAPIAllocateBuffer(CbNewADRLIST(1), (LPVOID FAR *)&pal);
	if (FAILED(hr))
	{
		goto cleanup;
	}

	pal->cEntries = 1;

	pal->aEntries[0].ulReserved1 = 0;
	pal->aEntries[0].cValues = 2;
	pal->aEntries[0].rgPropVals = NULL;

	// Allocate memory for the recipient properties
	hr = MAPIAllocateBuffer(2*sizeof(SPropValue), (LPVOID *)&rgAdrProps);

	if (FAILED(hr))
	{
		printf("MAPIAllocateBuffer() failed\n");
		goto cleanup;
	}

	pal->aEntries[0].rgPropVals = rgAdrProps;

	rgAdrProps[0].ulPropTag = PR_DISPLAY_NAME;
	rgAdrProps[0].Value.LPSZ = "Tools";

	rgAdrProps[1].ulPropTag = PR_RECIPIENT_TYPE;
	rgAdrProps[1].Value.l = MAPI_TO;				

	hr = pAdrBook->ResolveName(0,
							   MAPI_DIALOG,
							   NULL,
							   pal);

	if (FAILED(hr))
	{
		goto cleanup;
	}	

	hr = m_pMessage->ModifyRecipients(MODRECIP_ADD, pal);
	
    // ----- Release the address book, adrlist, and clean up
cleanup:
    if (pAdrBook)
    {
        pAdrBook->Release();
    }
    if (pal)
    {
        lpfnMAPIFreeBuffer(pal->aEntries[0].rgPropVals);
        lpfnMAPIFreeBuffer(pal);
    }

    return hr;
}


//$--FRM::Remember------------------------------------------------------------
//  
//  Purpose:
//      Store and addref the message site, the message, and the session
//      for later use
//
//  Returns:
//      HRESULT Error Status.
//----------------------------------------------------------------------------
HRESULT FRM::Remember(LPMAPIMESSAGESITE pmsite, LPMESSAGE pmsg)
{
    HRESULT hr;

    ASSERT(m_cRef > 0);
    ASSERT(pmsite);
    ASSERT(pmsg);

    // ----- remember our message site object
    if(!m_pMessageSite)
    {
        m_pMessageSite = pmsite;
        m_pMessageSite->AddRef();
    }

    // ----- remember our message
    if(!m_pMessage)
    {
        m_pMessage = pmsg;
        m_pMessage->AddRef();
    }

    // ----- remember mapi session
    if(!m_pSession)
    {
        hr = m_pMessageSite->GetSession(&m_pSession);
    }

    return hr;

}


//$--FRM::Forget--------------------------------------------------------------
//
//  Purpose:
//      Release the message site, the message, and the session
//
//  Returns:
//      HRESULT Error Status.
//----------------------------------------------------------------------------
HRESULT FRM::Forget(VOID)
{
    if (m_pMessage)
        m_pMessage->Release();
    if (m_pMessageSite)
        m_pMessageSite->Release();
    if (m_pSession)
        m_pSession->Release();

    m_pMessage = NULL;
    m_pMessageSite = NULL;
    m_pSession = NULL;

    return NOERROR;
}

//$--FRM::ShowCurrentMessage--------------------------------------------------
//
//  Purpose:
//      Display any form user interface on a form
//
//  Returns:
//      HRESULT             Error status.
//----------------------------------------------------------------------------
HRESULT FRM::ShowCurrentMessage(ULONG ulhwndParent) // Parent window
{
    HRESULT hr = NOERROR;

	ASSERT(m_cRef > 0);
    ASSERT(m_pMessageSite);
    ASSERT(m_pSession);
    ASSERT(m_pMessage);

    // ----- Give our user access to our form interface
	if ((NULL != m_pMessageSite) && (NULL != m_pSession) && (NULL != m_pMessage))
	{
		g_pForm = this;

        g_pForm->AddRef();
	}

    return hr;
}

