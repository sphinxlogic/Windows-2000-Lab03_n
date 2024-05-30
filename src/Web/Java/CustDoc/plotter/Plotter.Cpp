/*++

Copyright (c) 1996-1997  Microsoft Corporation.  All rights reserved.


--*/


#pragma hdrstop


#define INITGUID 1

#include <windows.h>
#include <stdio.h>
#include <olectl.h>          // to get the SELFREF_E_CLASS definition


#include "debug\\Plotter.h"  // IPlotter defn (generated from Plotter.odl).



//=======================================================================
// CPlotter
//
//   This class implements our COM object which exposes only one interface
//   (IPlotter).
//
//   Strictly speaking, it should also expose IMarshal by aggregating the
//   Ole free-threaded marshaler, since this dll marks itself "Both."
//   For such a simple sample, however, this will not matter.
//=======================================================================

class CPlotter : public IPlotter {
    private:
        ULONG       m_ref;          // Reference count.

    public:
        CPlotter() {
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

            if (riid == IID_IUnknown || riid == IID_IPlotter) {
                AddRef();
                *ppv = (IPlotter*)this;
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
                OutputDebugString("Too many releases on CPlotter object!\n");
                DebugBreak();
            }
            if (0 == ulc) {
                OutputDebugString("CPlotter: Destroy\n");
                delete this;
                return 0;
            }
            return 1;
        }


        //-------------------------------------------------------
        // IPlotter methods.
        //-------------------------------------------------------
        STDMETHOD(DrawLine)(POINT *start, POINT *end)
        {
            printf("DrawLine called: start = (%ld,%ld), end = (%ld,%ld)\n",
                   start->x,
                   start->y,
                   end->x,
                   end->y);
            return S_OK;
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

            CPlotter *pJ2CThing;
            HRESULT hr;

            pJ2CThing = new CPlotter();
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
        OutputDebugString("Plotter.dll has successfully loaded.\n");
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

    if (rclsid != CLSID_CPlotter) {
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
const char achPROGID[] = "CPlotter";


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
   GUID2StringA(CLSID_CPlotter, achCLSID);
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






