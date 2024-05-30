// --formprst.cpp-------------------------------------------------------------
//
//   Implementation of the FRM class IPersistMessage methods
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

#include "formdata.h"
#include "form.h"
#include "tooldoc.h"
#include "toolform.h"

//$--FRM::GetLastError--------------------------------------------------------
//
//  Purpose:
//      Get the last error
//
//  Returns:
//      HRESULT             NOERROR always.
// ---------------------------------------------------------------------------
STDMETHODIMP
FRM::GetLastError(HRESULT hResult, ULONG ulFlags, LPMAPIERROR FAR * lppMAPIError)
{
    ASSERT(m_cRef > 0);

    if (lppMAPIError)
        *lppMAPIError = NULL;
    return NOERROR;
}

//$--FRM::GetClassID----------------------------------------------------------
//
//  Purpose:
//      Get the class ID associated with this message.
//
//  Returns:
//      HRESULT             NOERROR always.
// ---------------------------------------------------------------------------
STDMETHODIMP
FRM::GetClassID(LPCLSID pclsid) // Where to put the class ID.
{
    ASSERT(m_cRef > 0);

    // The form only plays with things of its own class ID, so
    // this is easy; it's more complicated if code supports multiple
    // classes, or can do "treat as" operations
    if (pclsid)
        *pclsid = m_clsid;

    return NOERROR;
}


//$--FRM::IsDirty-------------------------------------------------------------
//
//  Purpose:
//      Returns whether the object has changed since the last save
//
//  Returns:
//      HRESULT             S_OK if dirty, S_FALSE if not dirty.
// ---------------------------------------------------------------------------
STDMETHODIMP
FRM::IsDirty(void)
{
    ASSERT(m_cRef > 0);
    
    return m_fDirty ? NOERROR : ResultFromScode(S_FALSE);
}


//$--FRM::InitNew-------------------------------------------------------------
//
//  Purpose:
//      Create a new message of our message class in the provided pmsg.
//
//  Returns:
//      HRESULT             S_OK, or error value.
// ---------------------------------------------------------------------------
STDMETHODIMP
FRM::InitNew(LPMAPIMESSAGESITE pmsite,
             LPMESSAGE pmsg)            // Message to create the new form in.
{
    HRESULT             hr              = NOERROR;
    SPropValue          prop            = {0};

    ASSERT(m_cRef > 0);

    // ----- Remember our pointers and such
    hr = Remember(pmsite,pmsg);
    if (FAILED(hr))
    {
        return hr;
    }

    // ----- set our message class
    prop.ulPropTag  = PR_MESSAGE_CLASS;
    prop.Value.LPSZ = TEXT(kszFormsMessageName);
    hr = m_pMessage->SetProps(1, &prop, NULL);
    if (FAILED(hr) )
    {
        return hr;
    }

    // ----- remind ourselves that this new message could not have been sent
    m_fSentMessage = 0;
   
    ADVISE(OnNewMessage);
    return hr;
}


//$--FRM::Load----------------------------------------------------------------
//
//  Purpose:
//      Attaches our object to the provided pmsg.
//
//  Returns:
//      HRESULT             S_OK, or error value.
// ---------------------------------------------------------------------------
STDMETHODIMP
FRM::Load(LPMAPIMESSAGESITE pmsite,
          LPMESSAGE pmsg,           // Our message to remember
          ULONG ulMessageStatus,
          ULONG ulMessageFlags)
{
    ULONG cProps = 0;
    const ULONG ctagMax = 10;
    char rgchTaga[sizeof(SPropTagArray) + (ctagMax * sizeof(ULONG))] = {0};
    LPSPropTagArray ptaga = (LPSPropTagArray) rgchTaga;
    LPSPropValue rgval = NULL;
    LPSPropValue pval = NULL;
    HRESULT         hr=S_OK;

    ASSERT(m_cRef > 0);

    // ----- Remember our pointers and such
    hr = Remember(pmsite,pmsg);
    if (FAILED(hr))
    {
        return hr;
    }

    // ----- If this message has been sent we would like to remember that
    m_fSentMessage = !( ulMessageFlags & MSGFLAG_UNSENT);
    TRACE1("fSentMessage = %d",(int) m_fSentMessage);

    ptaga->cValues = 0;
    ptaga->aulPropTag[ptaga->cValues++] = PR_SUBJECT;
    ptaga->aulPropTag[ptaga->cValues++] = PR_BODY;
    ptaga->aulPropTag[ptaga->cValues++] = PR_FORMDATA;				// Form Specific
 
    hr = pmsg->GetProps(ptaga, 0, &cProps, &rgval);
    if (FAILED(hr) )
    {
        return hr;
    }
    ASSERT(ptaga->cValues <= ctagMax);
    ASSERT(cProps == ptaga->cValues);
    ASSERT(NULL != rgval);

    // ----- set properties to variables

    // point pval at form-specific data
    pval = rgval + 2;

    POSITION pos = theApp.m_pDocTemplate->GetFirstDocPosition();
    ASSERT (pos);

    CToolDoc * pDoc = (CToolDoc*)theApp.m_pDocTemplate->GetNextDoc(pos);
    
    POSITION posVW = pDoc->GetFirstViewPosition();
    ASSERT (posVW);

    CToolForm * pView = (CToolForm*) pDoc->GetNextView (posVW);

    if (NULL != pView)
	{
	    if (pval->Value.bin.cb == sizeof(pDoc->m_theFormData))  // If the data is valid
        {
	        memcpy(&(pDoc->m_theFormData), pval->Value.bin.lpb,(int) pval->Value.bin.cb);
	    	pval++; // CALLERSNAME
		}

		pView->PutDataIntoWindow();
	}

    ASSERT(rgval);
    (*lpfnMAPIFreeBuffer)(rgval);
    ADVISE(OnNewMessage);

    return hr;
}


//$--FRM::Save----------------------------------------------------------------
//
//  Purpose:
//      Writes out our information to the provided pmsg. Does NOT commit
//      changes; this is the responsibility of the caller. Puts the form
//      into no-scribble mode until SaveCompleted is called.
//
//  Returns:
//      HRESULT             S_OK, or error value.
// ---------------------------------------------------------------------------
STDMETHODIMP
FRM::Save(
         LPMESSAGE pmsg,    // Message to write our changes to.
         ULONG fSameAsLoad) // TRUE if this is our home message, FALSE if
                            // this is a different message.
{
    SPropValue prop = {0};
    HRESULT hr = NOERROR;

    ASSERT(m_cRef > 0);
    ASSERT(m_pMessage);

    // ----- If this is the same pmsg as we got back when we loaded ...
    if (fSameAsLoad)
    {
        pmsg = m_pMessage;
    }

    // ----- set our message class
    prop.ulPropTag  = PR_MESSAGE_CLASS;
    prop.Value.LPSZ = TEXT(kszFormsMessageName);
    hr = m_pMessage->SetProps(1, &prop, NULL);
    if (FAILED(hr) )
    {
        return hr;
    }

    POSITION pos = theApp.m_pDocTemplate->GetFirstDocPosition();
    ASSERT (pos);

    CToolDoc * pDoc = (CToolDoc*)theApp.m_pDocTemplate->GetNextDoc(pos);
    
    if (NULL != pDoc)
	{
		//	This will set the Message body to a specific text value in the form.
		//	This will be dependent on the specific form.  The intended use of this
		//	is when a receiver or the form does not have access to the form, then
		//	he/she will view a text version of the form data.  This is the text
		//	version.
		prop.ulPropTag  = PR_BODY;
		prop.Value.lpszA = TEXT("Sorry, no text equivalent of tool form");
		hr = m_pMessage->SetProps(1, &prop, NULL);
		if (FAILED(hr) )
		{
		    return hr;
		}

		prop.ulPropTag = PR_SUBJECT;
		prop.Value.LPSZ = TEXT(pDoc->m_theFormData.m_szTopic);

		hr = m_pMessage->SetProps(1, &prop, NULL);
		if (FAILED(hr))
		{
		   return hr;
		}
		
	    prop.ulPropTag  = PR_FORMDATA;
	    prop.Value.bin.lpb = (unsigned char *) &(pDoc->m_theFormData);
	    prop.Value.bin.cb  = sizeof(pDoc->m_theFormData);
	    hr = m_pMessage->SetProps(1, &prop, NULL);
		if (FAILED(hr))
		{
	        return hr;
    	}
	}
    ADVISE(OnSaved);
    return hr;
}


//$--FRM::SaveCompleted-------------------------------------------------------
//
//  Purpose:
//      Terminates no-scribble and hands-off modes, returning the object
//      to its normal storage mode.
//
//  Returns:
//      HRESULT             S_OK, or error value.
// ---------------------------------------------------------------------------
STDMETHODIMP
FRM::SaveCompleted(LPMESSAGE pmsg)  // Our new home message, if we need to change.
{
    ASSERT(m_cRef > 0);

    // Reset modes
    m_fDirty = FALSE;

    return NOERROR;
}


//$--FRM::HandsOffMessage-----------------------------------------------------
//
//  Purpose:
//      Releases our reference on the message so that a Save As operation
//      can occur.
//
//  Returns:
//      HRESULT             S_OK, or error value.
// ---------------------------------------------------------------------------
STDMETHODIMP
FRM::HandsOffMessage(void)
{
    ASSERT(m_cRef > 0);
    return NOERROR;
}


