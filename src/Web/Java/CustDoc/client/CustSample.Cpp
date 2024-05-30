/*++

    Copyright (c) 1996-1997  Microsoft Corporation.  All rights reserved.




--*/




#pragma hdrstop


#define INITGUID 1

#include <windows.h>
#include <stdio.h>
#include <olectl.h>          // to get the SELFREF_E_CLASS definition


#define MYCHAR CHAR
#include "debug\\CustSample.h"  // ICustSample defn (generated from CustSample.odl).



//=======================================================================
// CCustSample
//
//   This class implements our COM object which exposes only one interface
//   (ICustSample).
//
//   Strictly speaking, it should also expose IMarshal by aggregating the
//   Ole free-threaded marshaler, since this dll marks itself "Both."
//   For such a simple sample, however, this will not matter.
//=======================================================================
class CCustSample : public ICustSample {
    private:
        ULONG       m_ref;          // Reference count.

    public:
        CCustSample() {
            m_ref = 0;
        }

        //-------------------------------------------------------
        // IUnknown methods.
        //-------------------------------------------------------
        STDMETHOD(QueryInterface) (REFIID riid, LPVOID *ppv) {
            __try {
                *ppv = NULL;
            } __except (EXCEPTION_EXECUTE_HANDLER) {
                return E_POINTER;
            }

            if (riid == IID_IUnknown || riid == IID_ICustSample) {
                AddRef();
                *ppv = (ICustSample*)this;
                return S_OK;
            }
            return E_NOINTERFACE;
        }

        STDMETHOD_(ULONG, AddRef) () {
            InterlockedIncrement( (LONG*)&m_ref );
            return 1;
        }

        STDMETHOD_(ULONG, Release) () {
            LONG ulc;

            ulc = InterlockedDecrement( (LONG*)&m_ref );
            if (ulc < 0) {
                OutputDebugString("Too many releases on CCustSample object!\n");
                DebugBreak();
            }
            if (0 == ulc) {
                OutputDebugString("CCustSample: Destroy\n");
                delete this;
                return 0;
            }
            return 1;
        }


        //-------------------------------------------------------
        // ICustSample methods.
        //-------------------------------------------------------
        STDMETHOD(PassFixedPtIn)(FIXED fp)
        {
            printf("C PassFixedPtIn called: (%ld, %lu)\n",
                   (LONG)(fp.value),
                   (ULONG)(fp.fract));
            return S_OK;
        }

        STDMETHOD(PassPFixedPtOutRetVal)(FIXED *pfp)
        {
            printf("C PassPFixedPtOutRetVal called. Returning 7.25\n");
            pfp->value = 7;
            pfp->fract = 16384;
            return S_OK;
        }

        STDMETHOD(PassPFixedPtIn)(FIXED *pfp)
        {
            printf("C PassPFixedPtIn called: (%ld, %lu)\n",
                   (LONG)(pfp->value),
                   (ULONG)(pfp->fract));
            return S_OK;
        }

        STDMETHOD(PassPFixedPtOut)(FIXED *pfp)
        {
            printf("C PassPFixedPtOut called. Returning 3.25\n");
            pfp->value = 3;
            pfp->fract = 16384;
            return S_OK;
        }

        STDMETHOD(PassPFixedPtInOut)(FIXED *pfp)
        {
            printf("C PassPFixedPtInOut called. Incrementing value by 2.\n");
            pfp->value += 2;
            return S_OK;
        }

        STDMETHOD(PassFixedPtsFromComToJava)(ICustSample *obj)
        {

            // This method demonstrates invoking Java methods from COM.
            // It accepts an ICustSample interface pointer (whose implementation
            // will be in Java, though this method is naturally oblivious
            // to that), and invokes every single method on it.

            HRESULT hr;

            {
                FIXED f = {32768, 4};
                hr = obj->PassFixedPtIn(f);
                if (S_OK != hr) {
                    return hr;
                }
            }

            {
                FIXED f = {0, 0};
                hr = obj->PassPFixedPtOutRetVal(&f);
                if (S_OK != hr) {
                    return hr;
                }
                printf("(%ld, %lu)\n", (LONG)(f.value), (ULONG)(f.fract));
            }
            {
                FIXED f = {32768, 8};
                hr = obj->PassPFixedPtIn(&f);
                if (S_OK != hr) {
                    return hr;
                }
            }
            {
                FIXED f = {0, 0};
                hr = obj->PassPFixedPtOut(&f);
                if (S_OK != hr) {
                    return hr;
                }
                printf("(%ld, %lu)\n", (LONG)(f.value), (ULONG)(f.fract));
            }

            {
                FIXED f = {16384, 8};
                hr = obj->PassPFixedPtInOut(&f);
                if (S_OK != hr) {
                    return hr;
                }
                printf("(%ld, %lu)\n", (LONG)(f.value), (ULONG)(f.fract));
            }


            return S_OK;


        }




        STDMETHOD(PassMyVariantIn)(MYVARIANT v)
        {
            printf("C PassMyVariantIn called: ");
            PrintBSTR(v.bstrVal);
            printf("\n");
            return S_OK;
        }

        STDMETHOD(PassPMyVariantOutRetVal)(MYVARIANT* pv)
        {
            printf("C PassPMyVariantOutRetVal called.\n");
            pv->vt = VT_BSTR;
            pv->bstrVal = NewBSTR(L"If you can read this, PassPMyVariantOutRetVal works.");
            return S_OK;
        }

        STDMETHOD(PassPMyVariantIn)(MYVARIANT *pv)
        {
            printf("C PassPMyVariantIn called: ");
            PrintBSTR(pv->bstrVal);
            printf("\n");
            return S_OK;
        }

        STDMETHOD(PassPMyVariantOut)(MYVARIANT* pv)
        {
            printf("C PassPMyVariantOut called.\n");
            pv->vt = VT_BSTR;
            pv->bstrVal = NewBSTR(L"If you can read this, PassPMyVariantOut works.");
            return S_OK;
        }

        STDMETHOD(PassPMyVariantInOut)(MYVARIANT* pv)
        {
            printf("C PassPMyVariantInOut called: ");
            PrintBSTR(pv->bstrVal);
            printf("\n");

            FreeBSTR(pv->bstrVal);
        
            pv->vt = VT_BSTR;
            pv->bstrVal = NewBSTR(L"If you can read this, the 'out' part of PassPMyVariantInOut works.");
            return S_OK;
        }

        STDMETHOD(PassMyVariantFromComToJava)(ICustSample *obj)
        {

            // This method demonstrates invoking Java methods from COM.
            // It accepts an ICustSample interface pointer (whose implementation
            // will be in Java, though this method is naturally oblivious
            // to that), and invokes every single method on it.

            HRESULT hr;
            {
                MYVARIANT mv;
                mv.vt = VT_BSTR;
                mv.bstrVal = NewBSTR(L"If you can read this, PassMyVariantIn worked.");
                hr = obj->PassMyVariantIn(mv);
                if (S_OK != hr) {
                    return hr;
                }
                FreeBSTR(mv.bstrVal);
            }

            {
                MYVARIANT mv;
                FillMemory(&mv, sizeof(mv), 0xcc);

                hr = obj->PassPMyVariantOutRetVal(&mv);
                if (S_OK != hr) {
                    return hr;
                }
                PrintBSTR(mv.bstrVal);
                printf("\n");
                FreeBSTR(mv.bstrVal);
            }

            {
                MYVARIANT mv;
                mv.vt = VT_BSTR;
                mv.bstrVal = NewBSTR(L"If you can read this, PPassMyVariantIn worked.");
                hr = obj->PassPMyVariantIn(&mv);
                if (S_OK != hr) {
                    return hr;
                }
                FreeBSTR(mv.bstrVal);
            }

            {
                MYVARIANT mv;
                FillMemory(&mv, sizeof(mv), 0xcc);

                hr = obj->PassPMyVariantOut(&mv);
                if (S_OK != hr) {
                    return hr;
                }
                PrintBSTR(mv.bstrVal);
                printf("\n");
                FreeBSTR(mv.bstrVal);
            }
            {
                MYVARIANT mv;
                mv.vt = VT_BSTR;
                mv.bstrVal = NewBSTR(L"If you can read this, the 'in' part of PPassMyVariantInOut worked.");

                hr = obj->PassPMyVariantInOut(&mv);
                if (S_OK != hr) {
                    return hr;
                }
                PrintBSTR(mv.bstrVal);
                printf("\n");
                FreeBSTR(mv.bstrVal);
            }

            return S_OK;
        }


        STDMETHOD(PassPPointOut)(POINT* ppt)
        {
            printf("C PassPPointOut called. Returning [5,6]\n");
            ppt->x = 5;
            ppt->y = 6;
            return S_OK;
        }

        STDMETHOD(PassPPointInOut)(POINT* ppt)
        {
            printf("C PassPPointInOut called. Received [%ld,%ld]. Translating x & y by 3.\n", ppt->x, ppt->y);
            ppt->x += 3;
            ppt->y += 3;
            return S_OK;
        }

        STDMETHOD(PassPointFromComToJava)(ICustSample *obj)
        {

            // This method demonstrates invoking Java methods from COM.
            // It accepts an ICustSample interface pointer (whose implementation
            // will be in Java, though this method is naturally oblivious
            // to that), and invokes every single method on it.

            HRESULT hr;
            {
                POINT p = {-1,-1};
                hr = obj->PassPPointOut(&p);
                if (hr != S_OK) {
                    return hr;
                }
                printf("[%ld,%ld]\n", p.x, p.y);
            }

            {
                POINT p = {10,11};
                hr = obj->PassPPointInOut(&p);
                if (hr != S_OK) {
                    return hr;
                }
                printf("[%ld,%ld]\n", p.x, p.y);
            }
            return S_OK;
        }

        STDMETHOD(PassRectIn)(RECT r)
        {
            printf("C PassRectIn called: ");
            PrintRect(r);
            printf("\n");
            return S_OK;
        }

        STDMETHOD(PassPRectOutRetVal)(RECT *pr)
        {
            RECT r = {4,5,10,11};
            printf("C PassPRectOutRetVal called. Returning ");
            PrintRect(r);
            printf("\n");
            *pr = r;
            return S_OK;
        }

        STDMETHOD(PassPRectIn)(RECT *pr)
        {
            printf("C PassPRectIn called: ");
            PrintRect(*pr);
            printf("\n");
            return S_OK;
        }

        STDMETHOD(PassPRectOut)(RECT *pr)
        {
            RECT r = {7,8,20,31};
            printf("C PassPRectOutRetVal called. Returning ");
            PrintRect(r);
            printf("\n");
            *pr = r;
            return S_OK;
        }

        STDMETHOD(PassPRectInOut)(RECT *pr)
        {
            printf("C PassPRectInOut called. Moving rectangle by (2,2)\n");
            pr->left   += 2;
            pr->top    += 2;
            pr->right  += 2;
            pr->bottom += 2;

            return S_OK;
        }


        STDMETHOD(PassPPRectOutRetVal)(RECT **ppr)
        {

            *ppr = NewRect(6,7,8,9);
            printf("C PassPPRectOutRetVal called. Returning ");
            PrintRect(**ppr);
            printf("\n");
            return S_OK;
        }

        STDMETHOD(PassPPRectIn)(RECT **ppr)
        {
            printf("C PassPPRectIn called: ");
            PrintRect(**ppr);
            printf("\n");
            return S_OK;
        }

        STDMETHOD(PassPPRectOut)(RECT **ppr)
        {

            *ppr = NewRect(13,14,15,16);
            printf("C PassPPRectOutcalled. Returning ");
            PrintRect(**ppr);
            printf("\n");
            return S_OK;
        }

        STDMETHOD(PassPPRectInOut)(RECT **ppr)
        {

            printf("C PassPPRectInOut called: ");
            PrintRect(**ppr);
            printf("\n");

            FreeRect(*ppr);

            *ppr = NewRect(1,2,3,4);
            printf("C PassPPRectInOut called. Returning ");
            PrintRect(**ppr);
            printf("\n");
            return S_OK;
        }

        STDMETHOD(PassRectFromComToJava)(ICustSample *obj)
        {

            // This method demonstrates invoking Java methods from COM.
            // It accepts an ICustSample interface pointer (whose implementation
            // will be in Java, though this method is naturally oblivious
            // to that), and invokes every single method on it.

            HRESULT hr;
            {
                RECT r = {4,5,6,7};
                PrintRect(r);printf("\n");
                hr = obj->PassRectIn(r);
                if (S_OK != hr) {
                    return hr;
                }
            }
            {
                RECT r = {-1,-1,-1,-1};
                hr = obj->PassPRectOutRetVal(&r);
                if (S_OK != hr) {
                    return hr;
                }
                PrintRect(r);printf("\n");
            }
            {
                RECT r = {14,15,16,17};
                PrintRect(r);printf("\n");
                hr = obj->PassPRectIn(&r);
                if (S_OK != hr) {
                    return hr;
                }
            }
            {
                RECT r = {-1,-1,-1,-1};
                hr = obj->PassPRectOut(&r);
                if (S_OK != hr) {
                    return hr;
                }
                PrintRect(r);printf("\n");
            }
            {
                RECT r = {24,25,26,27};
                hr = obj->PassPRectInOut(&r);
                if (S_OK != hr) {
                    return hr;
                }
                PrintRect(r);printf("\n");
            }
            {
                RECT *pr = NULL;
                hr = obj->PassPPRectOutRetVal(&pr);
                if (S_OK != hr) {
                    return hr;
                }
                PrintRect(*pr);printf("\n");
                FreeRect(pr);
            }
            {
                RECT r = {44,45,46,47};
                PRECT pr = &r;
                hr = obj->PassPPRectIn(&pr);
                if (S_OK != hr) {
                    return hr;
                }
            }

            {
                RECT *pr = NULL;
                hr = obj->PassPPRectOut(&pr);
                if (S_OK != hr) {
                    return hr;
                }
                PrintRect(*pr);printf("\n");
                FreeRect(pr);
            }
            {
                RECT *pr = NewRect(55,56,57,58);
                hr = obj->PassPPRectInOut(&pr);
                if (S_OK != hr) {
                    return hr;
                }
                PrintRect(*pr);printf("\n");
                FreeRect(pr);
            }
            return S_OK;
        }


        STDMETHOD(PassPStrIn)(LPSTR pstr)
        {
            printf("C PassPStrIn called: '%s'\n", pstr);
            return S_OK;
        }



        STDMETHOD(PassPPStrOutRetVal)(LPSTR *ppstr)
        {
            *ppstr = NewStr("If you can read this, C PassPPStrOutRetVal works.");
            return S_OK;
        }

        STDMETHOD(PassPPStrIn)(LPSTR *ppstr)
        {
            printf("C PassPPStrIn called: '%s'\n", *ppstr);
            return S_OK;
        }

        STDMETHOD(PassPPStrOut)(LPSTR *ppstr)
        {
            *ppstr = NewStr("If you can read this, C PassPPStrOut works.");
            return S_OK;
        }

        STDMETHOD(PassPPStrInOut)(LPSTR *ppstr)
        {
            printf("C PassPPStrInOut called: '%s'\n", *ppstr);
            FreeStr(*ppstr);
            *ppstr = NewStr("If you can read this, 'out' part of C PassPPStrInOut works.");
            return S_OK;
        }


        STDMETHOD(PassAnsiFromComToJava)(ICustSample *obj)
        {

            // This method demonstrates invoking Java methods from COM.
            // It accepts an ICustSample interface pointer (whose implementation
            // will be in Java, though this method is naturally oblivious
            // to that), and invokes every single method on it.

            HRESULT hr;
            {
                hr = obj->PassPStrIn("If you can read this, Java PassPStrIn works.");
                if (S_OK != hr) {
                    return hr;
                }
            }
            {
                LPSTR pstr = (LPSTR)0xcccccccc;
                hr = obj->PassPPStrOutRetVal(&pstr);
                if (S_OK != hr) {
                    return hr;
                }
                printf("%s\n", pstr);
                FreeStr(pstr);
            }
            {
                LPSTR pstr = "If you can read this, Java PassPPStrIn works.";
                hr = obj->PassPPStrIn(&pstr);
                if (S_OK != hr) {
                    return hr;
                }
            }
            {
                LPSTR pstr = (LPSTR)0xcccccccc;
                hr = obj->PassPPStrOut(&pstr);
                if (S_OK != hr) {
                    return hr;
                }
                printf("%s\n", pstr);
                FreeStr(pstr);
            }
            {
                LPSTR pstr = NewStr("If you can read this, 'in' part of Java PassPPStrInOut works.");
                hr = obj->PassPPStrInOut(&pstr);
                if (S_OK != hr) {
                    return hr;
                }
                printf("%s\n", pstr);
                FreeStr(pstr);
            }

            return S_OK;
        }

    private:

        //------------------------------------------------------------
        // Some simple utilities.
        //------------------------------------------------------------
        BSTR NewBSTR(LPCWSTR sz)
        {
            BSTR bstr = SysAllocString(sz);
            if (!bstr) {
                printf("Out of BSTR heap space.\n");
                exit(1);
            }

            CHAR msg[100];
            wsprintf(msg, "Server allocated BSTR at %lxh\n", bstr);
            OutputDebugString(msg);
            return bstr;
        }

        VOID FreeBSTR(BSTR bstr)
        {
            CHAR msg[100];
            wsprintf(msg, "Server freeing BSTR at %lxh\n", bstr);
            OutputDebugString(msg);

            SysFreeString(bstr);
        }

        VOID PrintBSTR(BSTR bstr)
        {
            DWORD len = SysStringLen(bstr);
            DWORD i;
            putchar('"');
            for (i = 0; i < len; i++) {
                putchar((CHAR)(bstr[i]));
            }
            putchar('"');
        }


        VOID PrintRect(RECT r)
        {
            printf("[x=%ld,y=%ld,width=%ld,height=%ld]",
                   r.left,
                   r.top,
                   r.right - r.left,
                   r.bottom - r.top);
        }

        RECT *NewRect(long x, long y, long width, long height)
        {
            RECT* pr = (RECT*)CoTaskMemAlloc(sizeof(RECT));
            if (!pr) {
                printf("Out of task heap space.\n");
                exit(1);
            }

            pr->left    = x;
            pr->top     = y;
            pr->right   = x + width;
            pr->bottom  = y + height;

            CHAR msg[100];
            wsprintf(msg, "Server allocated RECT at %lxh\n", pr);
            OutputDebugString(msg);


            return pr;
        }

        VOID FreeRect(RECT *pr)
        {
            CHAR msg[100];
            wsprintf(msg, "Server freeing RECT at %lxh\n", pr);
            OutputDebugString(msg);

            CoTaskMemFree(pr);
        }

        LPSTR NewStr(LPCSTR sz)
        {
            LPSTR pstr = (LPSTR)CoTaskMemAlloc(lstrlen(sz));
            if (!pstr) {
                printf("Out of heap space.\n");
                exit(1);
            }

            lstrcpy(pstr, sz);

            CHAR msg[100];
            wsprintf(msg, "Server allocated Str at %lxh\n", pstr);
            OutputDebugString(msg);
            return pstr;
        }

        VOID FreeStr(LPSTR pstr)
        {
            CHAR msg[100];
            wsprintf(msg, "Server freeing Str at %lxh\n", pstr);
            OutputDebugString(msg);

            CoTaskMemFree(pstr);
        }

};


//=======================================================================
// J2CClassFactory
//
//   This class implements the classfactory for our COM server. Since our
//   classfactory has no intrinsic state, we use a static class factory
//   to simplify our implementation.
//   
//=======================================================================
class J2CClassFactory : public IClassFactory
{
    public:

        //-----------------------------------------------------------
        // IUnknown methods.
        //-----------------------------------------------------------
        STDMETHOD(QueryInterface) (REFIID riid, LPVOID *ppv)
        {
            __try {
                *ppv = NULL;
            } __except (EXCEPTION_EXECUTE_HANDLER) {
                return E_POINTER;
            }

            if (riid == IID_IUnknown || riid == IID_IClassFactory) {
                AddRef();
                *ppv = (IClassFactory*)this;
                return S_OK;
            }
            return E_NOINTERFACE;
        }

        STDMETHOD_(ULONG, AddRef) () {
            return 1;
        }

        STDMETHOD_(ULONG, Release) () {
            return 1;
        }

        //-----------------------------------------------------------
        // IClassFactory methods.
        //-----------------------------------------------------------
        STDMETHOD(CreateInstance)(IUnknown *punkOuter, REFIID riid, LPVOID *ppv)
        {
            *ppv = NULL;

            if (punkOuter != NULL) {
                return CLASS_E_NOAGGREGATION;
            }

            CCustSample *pJ2CThing;
            HRESULT hr;

            pJ2CThing = new CCustSample();
            if (!pJ2CThing) {
                return E_OUTOFMEMORY;
            }
        
            pJ2CThing->AddRef();
            hr = pJ2CThing->QueryInterface(riid, ppv);
            pJ2CThing->Release();
            return hr;
        }

        STDMETHOD(LockServer)(BOOL fLock) {
            return S_OK;
            }

};


//===================================================================
// Create our first (and only) classfactory.
//===================================================================
J2CClassFactory g_CF;


// Rememeber our dll's module handle.
HINSTANCE ghInstance;




//===================================================================
// Standard DLL entry point (called by Win32 loader.)
//===================================================================
BOOL WINAPI DllMain(HINSTANCE hmod, DWORD dwReason,
                                PVOID pvReserved)
{
   ghInstance = hmod;

   if (dwReason == DLL_PROCESS_ATTACH) {
        OutputDebugString("CustSample.dll has successfully loaded.\n");
   }

   return TRUE;
}






//===================================================================
// Standard Ole export ("creates" a classfactory.)
//===================================================================
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppv)
{

    HRESULT hr;

    __try {
        *ppv = NULL;
    } __except (EXCEPTION_EXECUTE_HANDLER) {
        return E_POINTER;
    }

    if (rclsid != CLSID_CCustSample) {
        return CLASS_E_CLASSNOTAVAILABLE;
    }

    return g_CF.QueryInterface(riid, ppv);


}




//===================================================================
// Simple GUID unparsing utility (for self-registering code).
//===================================================================


#define GUIDSTR_MAX (1+ 8 + 1 + 4 + 1 + 4 + 1 + 4 + 1 + 12 + 1 + 1)

static const CHAR szDigits[] = "0123456789ABCDEF";
static const BYTE GuidMap[] = { 3, 2, 1, 0, '-', 5, 4, '-', 7, 6, '-',
                                8, 9, '-', 10, 11, 12, 13, 14, 15 };


//--------------------------------------------------------------------------
//
//  Function:   GUID2StringA
//
//  Synopsis:   Convert GUID to string form
//
//  Arguments:  [rguid] - the guid to convert
//              [lpszy] - buffer to hold the results
//
//  Returns:    nothing
//
//  This code is massively plagiarized from the Ole sources.
//--------------------------------------------------------------------------

VOID
GUID2StringA(REFGUID rguid, LPSTR lpsz)
{
    int i;
    LPSTR p = lpsz;

    const BYTE * pBytes = (const BYTE *) &rguid;

    *p++ = '{';

    for (i = 0; i < sizeof(GuidMap); i++)
    {
        if (GuidMap[i] == '-')
        {
            *p++ = '-';
        }
        else
        {
            *p++ = szDigits[ (pBytes[GuidMap[i]] & 0xF0) >> 4 ];
            *p++ = szDigits[ (pBytes[GuidMap[i]] & 0x0F) ];
        }
    }
    *p++ = '}';
    *p   = '\0';
}



const char achTM[] = "Both";
const char achDESC[] = "Sample Custom Marshaling Server.";
const char achPROGID[] = "CCustSample";


//===================================================================
// Standard Ole export (for self-registration a la regsvr32.)
//===================================================================
__declspec(dllexport)
STDAPI
DllRegisterServer(VOID)
{
   HKEY    hKey  = NULL;
   HKEY    hKey2 = NULL;
   HKEY    hKey3 = NULL;
   DWORD   result;
   HRESULT hr = SELFREG_E_CLASS;
   CHAR    achCLSID[GUIDSTR_MAX];
   TCHAR   achModulePathName[MAX_PATH];

   // If we fail in the middle, the state of the registry entries
   // is indeterminate (as per Ole specs.)


   // Create HKEY_CLASSES_ROOT\progid\CLSID
   result = RegCreateKey(HKEY_CLASSES_ROOT, achPROGID, &hKey);
   if (result != ERROR_SUCCESS) {
      goto lExit;
   }
   result = RegSetValue(hKey, NULL, REG_SZ, achDESC, lstrlen(achDESC));
   if (result != ERROR_SUCCESS) {
      goto lExit;
   }
   result = RegCreateKey(hKey, TEXT("CLSID"), &hKey2);
   if (result != ERROR_SUCCESS) {
      goto lExit;
   }
   GUID2StringA(CLSID_CCustSample, achCLSID);
   result = RegSetValue(hKey2, NULL, REG_SZ, achCLSID, GUIDSTR_MAX-1);
   if (result != ERROR_SUCCESS) {
      goto lExit;
   }

   RegCloseKey(hKey);
   RegCloseKey(hKey2);
   hKey = NULL;
   hKey2 = NULL;


   // Create HKEY_CLASSES_ROOT\CLSID\...
   result = RegCreateKey(HKEY_CLASSES_ROOT, TEXT("CLSID"), &hKey);
   if (result != ERROR_SUCCESS) {
      goto lExit;
   }

   result = RegCreateKey(hKey, achCLSID, &hKey2);
   if (result != ERROR_SUCCESS) {
      goto lExit;
   }

   result = RegSetValue(hKey2, NULL, REG_SZ, achDESC, lstrlen(achDESC));
   if (result != ERROR_SUCCESS) {
      goto lExit;
   }

   result = RegCreateKey(hKey2, "InprocServer32", &hKey3);
   if (result != ERROR_SUCCESS) {
      goto lExit;
   }

   result = GetModuleFileName(ghInstance, achModulePathName, sizeof(achModulePathName)/sizeof(TCHAR));
   if (result == 0) {  //No way to detect truncation from GetModuleFileName. 
      goto lExit;
   }

   result = RegSetValue(hKey3, NULL, REG_SZ, achModulePathName, lstrlen(achModulePathName));
   if (result != ERROR_SUCCESS) {
      goto lExit;
   }

   result = RegSetValueEx(hKey3, "ThreadingModel", 0, REG_SZ, (BYTE*)achTM, sizeof(achTM));
   if (result != ERROR_SUCCESS) {
      goto lExit;
   }

   RegCloseKey(hKey3);
   hKey3 = NULL;


   result = RegCreateKey(hKey2, "ProgID", &hKey3);
   if (result != ERROR_SUCCESS) {
      goto lExit;
   }
   result = RegSetValue(hKey3, NULL, REG_SZ, achPROGID, lstrlen(achPROGID));
   if (result != ERROR_SUCCESS) {
      goto lExit;
   }
   RegCloseKey(hKey3);
   hKey3 = NULL;



   hr = S_OK;

 lExit:
   if (hKey) {
      RegCloseKey(hKey);
   }
   if (hKey2) {
      RegCloseKey(hKey2);
   }
   if (hKey3) {
      RegCloseKey(hKey3);
   }
   return hr;

}



//===================================================================
// Standard Ole export (for self-unregistration a la regsvr32.)
//===================================================================
__declspec(dllexport)
STDAPI
DllUnregisterServer(VOID)
{
    return S_OK;
}






