// --formmapi.cpp-------------------------------------------------------------
//
//    Implementation of the FRM class MAPI methods
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// ---------------------------------------------------------------------------

#include "stdafx.h"
#include "tool.h"

#include "formdata.h"
#include "form.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define new DEBUG_NEW

//$--FRM::DoVerb--------------------------------------------------------------
//
//  Purpose:
//      Performs the specified verb on the message.
//
//  Returns:
//      HRESULT             S_OK, or error value.
//----------------------------------------------------------------------------
STDMETHODIMP
FRM::DoVerb(
         LONG iVerb,                // What to do.
         LPMAPIVIEWCONTEXT pmvc,    // Our view context.
         ULONG ulhwndParent,        // Our parent window.
         LPCRECT prcPosRect)        // Where we should display ourselves given
                                    // a choice.
{
    ASSERT(m_cRef > 0);

    switch (iVerb)
    {
    default:
    case OLEIVERB_HIDE:
    case OLEIVERB_DISCARDUNDOSTATE:
        return ResultFromScode(E_NOTIMPL);

    case OLEIVERB_UIACTIVATE:
    case OLEIVERB_INPLACEACTIVATE:
        if (iVerb < 0)
            return ResultFromScode(E_NOTIMPL);
        return ResultFromScode(OLEOBJ_S_INVALIDVERB);

    case OLEIVERB_SHOW:
        ShowCurrentMessage(ulhwndParent);
        return NOERROR;

    case OLEIVERB_OPEN:
    case OLEIVERB_PRIMARY:
        if (m_fSentMessage)
		{	
            LaunchReplyMessage(ulhwndParent);
		}
        else
		{
			ShowCurrentMessage(ulhwndParent);
		}

        return NOERROR;
    }
}


//$--FRM::ShutdownForm--------------------------------------------------------
//
//  Purpose:
//      Closes down any UI associated with the form.
//
//  Arguments:
//      DWORD               
//
//  Returns:
//      HRESULT             S_OK, or error value.
//----------------------------------------------------------------------------
STDMETHODIMP
FRM::ShutdownForm(
         DWORD dwSaveOptions) // One of OLECLOSE_SAVEIFDIRTY, OLECLOSE_NOSAVE,
                              // or OLECLOSE_PROMPTSAVE.
{
    ASSERT(m_cRef > 0);

    HRESULT hr = NOERROR;

    // ----- don't close if we're in a modal dialog
    //       especially if the modal dialog occurs in a remoted interface
	if (!AfxGetMainWnd()->IsWindowEnabled())
        return ResultFromScode(E_ABORT);

    // ----- be kind, and save ourself  
    switch (dwSaveOptions)
    {
        case OLECLOSE_NOSAVE:
            break;

        case OLECLOSE_SAVEIFDIRTY:
            if (m_fDirty)
                hr = m_pMessageSite->SaveMessage();
            break;

        default:
        case OLECLOSE_PROMPTSAVE:
            if (m_fDirty)
			{
                if (IDYES == AfxMessageBox("Save changes?", MB_YESNO))
             	{
                    hr = m_pMessageSite->SaveMessage();
				}
			}
            break;

    }

    if (NOERROR == hr)
    {
        // ----- let everyone know we're shutting down
        ADVISE(OnShutdown);

        // ----- Release everything we have remembered thus far
        Forget();

        // ----- make sure everyone has Unadvised
        ASSERT(0==m_afAdvisee[0]);
        ASSERT(0==m_afAdvisee[1]);
        ASSERT(0==m_afAdvisee[2]);
        ASSERT(0==m_afAdvisee[3]);

        // ----- post a quit message to our UI
        AfxGetMainWnd()->SendMessage(WM_CLOSE);
    }

    return hr;
}

//$--FRM::SetViewContext------------------------------------------------------
//
//  Puspose:
//      View context is used for next and previous behavior
//      The tools form does not do next and previous because
//      there is not a standard read note.  It is always in 
//      reply mode.
//----------------------------------------------------------------------------
STDMETHODIMP
FRM::SetViewContext(LPMAPIVIEWCONTEXT pViewContextNew)
{
    ASSERT(m_cRef > 0);
    ASSERT(pViewContextNew);

    return NOERROR;
}

//$--FRM::GetViewContext------------------------------------------------------
//
// Purpose:
//      Get the view context
//
//  Returns:
//      HRESULT
//----------------------------------------------------------------------------
STDMETHODIMP
FRM::GetViewContext(LPMAPIVIEWCONTEXT FAR * ppViewContext)
{
    ASSERT(m_cRef > 0,);
    ASSERT(ppViewContext);

    if (ppViewContext)
        *ppViewContext = NULL;      // not supported

    return NOERROR;
}

//$--FRM::Advise--------------------------------------------------------------
//
//  Purpose:
//
//  Returns:
//      HRESULT
//----------------------------------------------------------------------------
STDMETHODIMP
FRM::Advise(LPMAPIVIEWADVISESINK pAdvise, ULONG FAR * pdwStatus)
{
    LONG i = 0;

    ASSERT(m_cRef > 0);
    ASSERT(pdwStatus);
    ASSERT(pAdvise);

    // ----- remember who to advise    
    for (i=0; i<MAX_ADVISE; i++)
    {
        if (!m_afAdvisee[i])
        {
            m_aAdvisePtrs[i] = pAdvise;
            m_afAdvisee[i] = 1;
            *pdwStatus = i + 1;     // ulConnection of zero is not valid
            pAdvise->AddRef();
            return NOERROR;
        }
    }

    // ----- bad news
    ASSERT(FALSE);
    return ResultFromScode(E_FAIL);
}

//$--FRM::Unadvise------------------------------------------------------------
//
//  Purpose:
//
//  Returns:
//      HRESULT
//----------------------------------------------------------------------------
STDMETHODIMP
FRM::Unadvise(ULONG ulConnection)
{
    ASSERT(m_cRef > 0);
    ASSERT(ulConnection < MAX_ADVISE && ulConnection >= 0);
    ASSERT(ulConnection);

    // ----- forget about advising this guy
    --ulConnection; // remember, we added one in advise
    
    ASSERT(m_afAdvisee[(int) ulConnection]);
    m_afAdvisee[(int) ulConnection] = 0;
    m_aAdvisePtrs[(int) ulConnection]->Release();
    
    return NOERROR;
}
