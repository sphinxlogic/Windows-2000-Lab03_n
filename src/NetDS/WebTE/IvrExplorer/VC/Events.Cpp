//
// CDWebBrowserEvents implementing IDispatch..
//
#include "stdafx.h"
#include <mshtml.h>

DEventsClass::~DEventsClass(void)
{
    //
    // Check if the interface was released properly.
    //
    return;
}

STDMETHODIMP
DEventsClass::QueryInterface(REFIID riid, LPVOID *ppv)
{
    if (IID_IUnknown==riid || IID_IDispatch==riid || riid ==DIID_IWebIvrConnectionEvents)
    {
        *ppv=this;
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
    }

    *ppv=NULL;
    return E_NOINTERFACE;
}

STDMETHODIMP_(ULONG)
DEventsClass::AddRef(void)
{
    return ++m_cRef;
}

STDMETHODIMP_(ULONG)
DEventsClass::Release(void)
{
    if (0!=--m_cRef)
        return m_cRef;

    // We do not delete the object because we didn't allocate it.
    return 0;
}

STDMETHODIMP
DEventsClass::GetTypeInfoCount(UINT *pctinfo)
{
    return NOERROR;
}

STDMETHODIMP
DEventsClass::GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo)
{
    return NOERROR;
}

STDMETHODIMP
DEventsClass::GetIDsOfNames(REFIID riid,
                                  LPOLESTR *rgszNames,
                                  UINT cNames,
                                  LCID lcid,
                                  DISPID *rgDispId)
{
    return NOERROR;
}

STDMETHODIMP
DEventsClass::Invoke(DISPID dispIdMember,
                           REFIID riid,
                           LCID lcid,
                           WORD wFlags,
                           DISPPARAMS *pDispParams,
                           VARIANT *pVarResult,
                           EXCEPINFO *pExcepInfo,
                           UINT *puArgErr)
{
    //
    // See which event we got..
    //
    CString  cs;
    TCHAR    sz[10];

    switch (dispIdMember)
    {
    case wteDispidApplicationEventOnOffering:
        {
            IExOM    *pExOM;
            BSTR      bstrSessionName;
            ISession *pSession;

            cs = "Offering session name=";
            m_pContainer->GetApp()->get_ExtendedObjectModel(&pExOM);
            pExOM->get_Session(&pSession);
            pExOM->Release();

            pSession->get_SessionName(&bstrSessionName);
            pSession->Release();

            cs += bstrSessionName;
            SysFreeString(bstrSessionName);
        }
        break;

    case wteDispidApplicationEventOnConnected:
        {
            cs = "Connected";
        }
        break;

    case wteDispidApplicationEventOnDisconnected:
        {
            IExOM    *pExOM;
            ISession *pSession;
            BSTR      bstrSessionState;

            cs = "Disconnected session state=";
            m_pContainer->GetApp()->get_ExtendedObjectModel(&pExOM);
            pExOM->get_Session(&pSession);
            pExOM->Release();

            pSession->get_SessionState(&bstrSessionState);
            pSession->Release();

            cs += bstrSessionState;
            SysFreeString(bstrSessionState);
        }        
        break;

    case wteDispidApplicationEventOnBeforeNavigate:
        {
            cs = "      Before navigate to ";
            cs += pDispParams->rgvarg[0].bstrVal;
        }
        break;

    case wteDispidApplicationEventOnNavigateComplete:
        {
            cs = "      Navigate complete to ";
            cs += pDispParams->rgvarg[0].bstrVal;
        }
        break;

    case wteDispidApplicationEventOnDocumentComplete:
        {
            cs = "      Document complete to ";
            cs += pDispParams->rgvarg[0].bstrVal;
        }
        break;

    case wteDispidApplicationEventOnTagBegin:
        {
            long          lIndex;
            IHTMLElement *pElem;
            BSTR          bstrTagName = NULL;

            cs = "                  Got to tag ";
            pDispParams->rgvarg[0].pdispVal->QueryInterface(IID_IHTMLElement,
                                                            (void **)&pElem);

            pElem->get_tagName(&bstrTagName);
            pElem->get_sourceIndex(&lIndex);
            pElem->Release();

            _itot(lIndex, sz, 10);
            cs += bstrTagName;
            cs += " (tag index - ";
            cs += sz;
            cs += ")";
            SysFreeString(bstrTagName);
        }
        break;

    case wteDispidApplicationEventOnTagEnd:
        {
            IHTMLElement *pElem;
            BSTR          bstrTagName = NULL;

            cs = "                  Tag ";
            pDispParams->rgvarg[0].pdispVal->QueryInterface(IID_IHTMLElement,
                                                            (void **)&pElem);
            pElem->get_tagName(&bstrTagName);
            pElem->Release();

            cs += bstrTagName;
            cs += " ended";
            SysFreeString(bstrTagName);
        }
        break;

    case wteDispidApplicationEventOnTelephonyStepEnd:
        {
            ITelephonyStepConstrains *pConstrains;
            ITelephonyStep         *pTO;
            IHTMLElement           *pElem;
            BSTR                    bstrTagName = NULL;
            long                    lType;
            long                    lMenuItemsLength;
            long                    lAudioItemsLength;

            cs = "            Telephony step ended ";

            if (pDispParams->rgvarg[2].pdispVal)
            {
                pDispParams->rgvarg[2].pdispVal->QueryInterface(IID_IHTMLElement, (void **)&pElem);
                pElem->get_tagName(&bstrTagName);
                pElem->Release();
            }

            switch (pDispParams->rgvarg[1].lVal)
            {
            case wteEndReasonScopeEnd:

                cs += "as the menu owner ";
                cs += bstrTagName;
                cs += " ended";            
                break;

            case wteEndReasonCutThroughChanged:

                cs += "as the cut-through mode changed on tag ";
                cs += bstrTagName;
                break;

            case wteEndReasonIntrinsicControl:

                cs += "as the intrinsic control tag ";
                cs += bstrTagName;
                cs += " broke the menu";
                break;

            case wteEndReasonTable:

                cs += "as a table brokew the menu";
                break;

            case wteEndReasonIncompatibleMenuItemType:

                cs += "as the menu item ";
                cs += bstrTagName;
                cs += " is different then the current menu type";
                break;

            case wteEndReasonForm:

                cs += "as a form broke the telephony object";
                break;

            case wteEndReasonPageEnd:

                cs += "as the page ended";
                break;

            case wteEndReasonSelectionTimeout:

                cs  = "            Menu timeout passed, re-offering the menu";
                break;

            case wteEndReasonSelectionError:

                cs =  "            Illegal digit detected, re-offering the menu";
                break;            
            }// switch (pDispParams->rgvarg[0].lVal)

            SysFreeString(bstrTagName);
            m_pContainer->AddLine(&cs);

            //
            // Check the constrains.
            //
            pDispParams->rgvarg[0].pdispVal->QueryInterface(IID_ITelephonyStepConstrains,
                                                            (void **)&pConstrains);
            pConstrains->get_Type(&lType);

            m_pContainer->GetApp()->get_TelephonyStep(&pTO);
            pTO->get_MenuItemsLength(&lMenuItemsLength);
            pTO->get_AudioItemsLength(&lAudioItemsLength);

            //
            // Print number of menu items.
            //
            if (lMenuItemsLength && (lType != wteConsNone))
            {
                if (lMenuItemsLength == 1)
                {
                    cs = "            There is 1 menu item";
                }
                else
                {
                    cs = "            There are ";
                    _itot(lMenuItemsLength, sz, 10);
                    cs += sz;
                    cs += " menu items";
                }
                m_pContainer->AddLine(&cs);
            }

            //
            // Print number & audio items.
            if (lAudioItemsLength)
            {
                BOOL fMode = FALSE;

                if (lType == wteConsNone)
                {
                    pTO->get_CutThroughMode(&fMode);
                }

                if (!fMode)
                {
                    if (lAudioItemsLength == 1)
                    {
                        cs = "            There is 1 audio item:";
                    }
                    else
                    {
                        cs = "            There are ";
                        _itot(lAudioItemsLength, sz, 10);
                        cs += sz;
                        cs += " audio items:";
                    }
                    m_pContainer->AddLine(&cs);

                    for (long l=0; l<lAudioItemsLength; l++)
                    {
                        BSTR bstrAudioItem;

                        pTO->GetAudioItem(l, &bstrAudioItem);

                        cs = "                       ";
                        cs += bstrAudioItem;
                        m_pContainer->AddLine(&cs);
                        SysFreeString(bstrAudioItem);
                    }
                }
            }

            pTO->Release();

            //
            // Print constrains.
            //
            if (lType & wteConsLegalDigits)
            {
                BSTR bstrLegalDigits;
                pConstrains->get_LegalDigits(&bstrLegalDigits);

                if (lstrlen(bstrLegalDigits))
                {
                    cs = "            Constrains - Legal digits ";
                    cs += bstrLegalDigits;
                }
                else
                {
                    cs = "            No constrains - playing an announcement";
                }
            }
            else if (lType & wteConsBoundaries)
            {
                long lBoundry;

                cs = "            Constrains - Boundries.  Lower boundry=";
                pConstrains->get_LowerBoundary(&lBoundry);
                _itot(lBoundry, sz, 10);
                cs += sz;
                cs += ", Upper boundry=";
                pConstrains->get_UpperBoundary(&lBoundry);
                _itot(lBoundry, sz, 10);
                cs += sz;

                if (lType & wteConsTerminator)
                {
                    long lBoundry2;

                    pConstrains->get_LowerBlocked(&lBoundry);
                    pConstrains->get_UpperBlocked(&lBoundry2);

                    if (lBoundry < lBoundry2)
                    {
                        _itot(lBoundry, sz, 10);
                        cs += ", Lower blocked=";
                        cs += sz;
                        cs += ", Upper blocked=";
                        _itot(lBoundry2, sz, 10);
                        cs += sz;
                    }
                }
            }
            else if (lType == wteConsTerminator)
            {
                BSTR bstrAppString;

                cs = "            Constrains - Termination string ";
                pConstrains->get_TerminationString(&bstrAppString);
                cs += bstrAppString;
            }
            else if (lType == wteConsNone)
            {
                cs = "            An automatically clicked button - clicking on it";
            }
        }
        break;

    case wteDispidApplicationEventOnDigit:
        {
            cs = "            Digit detected : ";
            cs += pDispParams->rgvarg[0].bstrVal;
        }
        break;

    case wteDispidApplicationEventOnDigitsUsed:
        {
            cs = "            Digits used : ";
            cs += pDispParams->rgvarg[0].bstrVal;
        }
        break;

    case wteDispidApplicationEventOnSessionEnd:
        {
            IExOM    *pExOM;
            BSTR      bstrSessionName;
            ISession *pSession;

            cs = "Session ";
            m_pContainer->GetApp()->get_ExtendedObjectModel(&pExOM);
            pExOM->get_Session(&pSession);
            pExOM->Release();

            pSession->get_SessionName(&bstrSessionName);
            pSession->Release();

            cs += bstrSessionName;
            SysFreeString(bstrSessionName);

            cs += " ended";
            m_pContainer->AddLine(&cs);
            cs ="";    
        }
    }// switch (dispIdMember)

    m_pContainer->AddLine(&cs);
    return S_OK;
}