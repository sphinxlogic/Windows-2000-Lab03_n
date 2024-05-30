// --form.h-------------------------------------------------------------------
//
//  Declaration for the FRMFAC and FRM classes
//
//	Copyright (C) 1986-1996. Microsoft Corporation.  All Rights Reserved.
//
// ---------------------------------------------------------------------------

#ifndef _FORM_H
	#define	_FORM_H

#include <mapiform.h>
#define INITGUID
#include <initguid.h>
#include <mapix.h>
#include <mapiutil.h>
#include <mapinls.h>
		
#define		kszFormsMessageName		"IPM.ToolForm1"
#define		kszAppName				"Tool Form Sample"
#define		kszAppLoadingTitle		"Tool Form, Loading..."


HRESULT HrStartOleAndRegisterClassFactory(void);
HRESULT HrStopForms(void);

#define NOTPURE
#define MAX_ADVISE 48

#define CbNewFlagList(_cflag) \
	(offsetof(FlagList,ulFlag) + (_cflag)*sizeof(ULONG))

/*
 *  Types
 */

// ----- class factory
class FRMFAC : public IClassFactory
{
public:
    FRMFAC();

    // *** IUnknown methods
    STDMETHOD(QueryInterface)   (THIS_ REFIID riid, LPVOID FAR* ppvObj);
    STDMETHOD_(ULONG,AddRef)    (THIS);
    STDMETHOD_(ULONG,Release)   (THIS);

    // *** IClassFactory methods
    STDMETHOD(CreateInstance)   (THIS_ LPUNKNOWN pUnkOuter, REFIID riid, LPVOID FAR* ppvObject);
    STDMETHOD(LockServer)       (THIS_ BOOL fLock);
protected:
    ULONG       m_cRef;
    CLSID       m_clsid;
};

// ----- The minimal interface a form can support
class FRM : public IPersistMessage, public IMAPIForm
{
  protected:
    ULONG                   m_cRef;               // Reference count
    CLSID                   m_clsid;

    BOOL                    m_fDirty;             // Is our message dirty?
    BOOL                    m_fSentMessage;       // Are we reading a sent message?



    // advise handling

    BOOL                    m_afAdvisee[MAX_ADVISE];
    LPMAPIVIEWADVISESINK    m_aAdvisePtrs[MAX_ADVISE];


    // This is all the data that is specific to this exact form.  To change 
	// the form, edit FormData.c and FormData.h which will be easier than 
	// adding data here.  Also, FormData.h will give instructions on what 
	// modifications are needed when data is added to a form.
	CFormData				m_theFormData;


    ~FRM(void);

  public:
    LPMESSAGE               m_pMessage;
    LPMAPIMESSAGESITE       m_pMessageSite;
    LPMAPISESSION           m_pSession;

    LPMAPIFORMMGR           m_pFormMgr;
    LPMAPIFORMINFO          m_pFormInfo;

    FRM(REFCLSID clsid);

    MAPI_IUNKNOWN_METHODS(NOTPURE)
    MAPI_GETLASTERROR_METHOD(NOTPURE)
    MAPI_IPERSISTMESSAGE_METHODS(NOTPURE)
    MAPI_IMAPIFORM_METHODS(NOTPURE)

    HRESULT ShowCurrentMessage(ULONG ulhwndParent);
    HRESULT LaunchReplyMessage(ULONG ulhwndParent);
    VOID GetFormData(CFormData & theData);
    VOID SetFormData(const CFormData & theData);
    HRESULT Remember(LPMAPIMESSAGESITE pmsite, LPMESSAGE pmsg);
    HRESULT Forget(VOID);
    HRESULT SendForm(VOID);
    HRESULT AddressForm(HWND hwnd, BOOL fDontShowIfRecipsExist);
};

/*
 *  Macros
 */

#define ADVISE(_func)                    \
{                                        \
   for (LONG i = 0; i < MAX_ADVISE; i++) \
      if (m_afAdvisee[i])                \
         m_aAdvisePtrs[i]->_func();      \
}

#define ReleaseObj(_pobj) \
        if (_pobj) \
                (_pobj)->Release()

/*
 *  Dependencies specific to this form
 */

#define PR_FORMDATA					PROP_TAG( PT_BINARY,   0x6800)

typedef HRESULT (FAR PASCAL *LPFNCOREGISTERCLASSOBJECT)(
            REFCLSID rclsid,
            IUnknown FAR * pUnk,
            DWORD dwClsContext,
            DWORD flags,
            LPDWORD lpdwRegister);
#ifdef WIN16
typedef BOOL (FAR PASCAL *LPFNISEQUALGUID)(REFGUID rguid1, REFGUID rguid2);
#undef IsEqualIID
#define IsEqualIID(riid1, riid2) (*lpfnIsEqualGUID)(riid1, riid2)
#endif

typedef HRESULT (FAR PASCAL *LPFNHRQUERYALLROWS)(
            LPMAPITABLE ptable, 
            LPSPropTagArray ptaga, LPSRestriction pres,
            LPSSortOrderSet psos, LONG crowsMax,
            LPSRowSet FAR *pprows);
typedef ULONG   (FAR PASCAL *LPFNMAPIFREEBUFFER)(LPVOID pv);
typedef HRESULT (FAR PASCAL *LPFNMAPIINITIALIZE)(LPVOID lpvReserved);
typedef void    (FAR PASCAL *LPFNMAPIUNINITIALIZE)(VOID);

#ifdef WIN32
#define szOleDll  "ole32.dll"
#define szMapiDll "mapi32.dll"
#else
#define szOleDll  "compobj.dll"
#define szMapiDll "mapi.dll"
#endif

#ifdef WIN16
extern LPFNISEQUALGUID           lpfnIsEqualGUID;
#endif
extern LPFNCOREGISTERCLASSOBJECT lpfnCoRegisterClassObject;
extern LPFNHRQUERYALLROWS        lpfnHrQueryAllRows       ;
extern LPFNMAPIFREEBUFFER        lpfnMAPIFreeBuffer       ;
extern LPFNMAPIINITIALIZE        lpfnMAPIInitialize       ;
extern LPFNMAPIUNINITIALIZE      lpfnMAPIUninitialize     ;

#endif

