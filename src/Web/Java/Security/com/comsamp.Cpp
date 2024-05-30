#define INITGUID 1

#include <windows.h>
#include <olectl.h>

#include "comsamp.h"

TCHAR achSampleProgID[]        = "comntv";
TCHAR achInprocServer32[]      = "InprocServer32";
TCHAR achProgID[]              = "ProgID";
TCHAR achThreadingModel[]      = "ThreadingModel";
TCHAR achBoth[]                = "Both";


DWORD g_ObjectCount = 0;
HINSTANCE ghInstance = 0;



VOID ObjectCreated(VOID)
{
    InterlockedIncrement( (LONG*)&g_ObjectCount );
}



VOID ObjectDestroyed(VOID)
{
    InterlockedDecrement( (LONG*)&g_ObjectCount );
}


HRESULT CheckJavaWriteAccess (BSTR pwszFilename)
{
    // If there is no vm in the process, then we could not have
    // been called directly from java code, and remote calls are
    // implicitly trusted.
    if (GetModuleHandle("MSJAVA") == NULL)
        return S_OK;

    HRESULT hr;

    IMyCOMObjectSecurity *psecurity;

    hr = CoCreateInstance(
            CLSID_CMyCOMObjectSecurity,
            NULL,
            CLSCTX_ALL,
            IID_IMyCOMObjectSecurity,
            (PVOID*)&psecurity
            );
    if (SUCCEEDED(hr))
    {
        hr = psecurity->CheckRead(pwszFilename);
        psecurity->Release();

        // The VM does not convert SecurityException to a useful HRESULT, so do it here.
        if (hr == E_FAIL)
            hr = HRESULT_FROM_WIN32(ERROR_PRIVILEGE_NOT_HELD);
    }

    return hr;
}


class CMyCOMObject : public IMyInterface
{
    ULONG refcount;

public:

    CMyCOMObject ()
    {
        refcount = 1;
    }
    

    // IUnknown methods
    
    HRESULT STDMETHODCALLTYPE QueryInterface (REFIID riid, LPVOID* ppv)
    {
        *ppv = NULL;
        
        if (riid == IID_IUnknown)
        {
            *ppv = (IUnknown*)this;
        }
        else if (riid == IID_IMyInterface)
        {
            *ppv = (IMyInterface*)this;
        }
        
        if (*ppv)
        {
            ((IUnknown*)(*ppv))->AddRef();
            return S_OK;
        }
        
        return E_NOINTERFACE;
    }

    ULONG STDMETHODCALLTYPE AddRef ()
    {
        InterlockedIncrement((LONG*)&refcount);
        return 0xcccccccc;
    }

    ULONG STDMETHODCALLTYPE Release ()
    {
        if (!InterlockedDecrement((LONG*)&refcount))
        {
            delete this;
            return 0;
        }
        
        return 0xcccccccc;
    }


    // IMyInterface methods

    HRESULT STDMETHODCALLTYPE COMCheckedLoad (BSTR pwszFilename, BYTE buffer[], int *bufsize)
    {
        HRESULT hr = CheckJavaWriteAccess(pwszFilename);
        if (SUCCEEDED(hr))
        {
            hr = JavaCheckedLoad(pwszFilename, buffer, bufsize);
        }
        
        return hr;
    }
    
    HRESULT STDMETHODCALLTYPE JavaCheckedLoad (BSTR pwszFilename, BYTE buffer[], int *bufsize)
    {
        if (pwszFilename == NULL || buffer == NULL || bufsize == NULL)
            return E_POINTER;

        if (*bufsize < 0)
            return E_INVALIDARG;

        HRESULT hr = E_FAIL;

        CHAR filename[MAX_PATH];
        int filenamelen = WideCharToMultiByte(
                CP_ACP,
                0,
                pwszFilename,
                -1,
                filename,
                sizeof(filename)-1,
                NULL,
                NULL);
        if (filenamelen != 0)
        {
            filename[filenamelen] = '\0';

            HANDLE file = CreateFile(
                    filename,
                    GENERIC_READ,
                    FILE_SHARE_READ,
                    NULL,
                    OPEN_EXISTING,
                    FILE_FLAG_SEQUENTIAL_SCAN,
                    NULL
                    );
            if (file != INVALID_HANDLE_VALUE)
            {
                DWORD size = GetFileSize(file, NULL);
                if (size != 0xffffffff)
                {
                    DWORD toread = size;
                    if (toread > *bufsize)
                        toread = *bufsize;

                    DWORD read;
                    if (ReadFile(
                            file,
                            buffer,
                            toread,
                            &read,
                            NULL
                            )
                          && read == size
                          )
                    {
                        *bufsize = read;
                        hr = S_OK;
                    }
                }

                CloseHandle(file);
            }
        }

        if (hr == E_FAIL)
            hr = HRESULT_FROM_WIN32(GetLastError());

        return hr;
    }
};



class CMyComObjectClassFactory : public IClassFactory
{
public:

    CMyComObjectClassFactory ()
    {
        ObjectCreated();
    }

    ~CMyComObjectClassFactory ()
    {
        ObjectDestroyed();
    }
    

    // IUnknown methods
    
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, LPVOID* ppv)
    {
        *ppv = NULL;
        if (riid == IID_IUnknown)
        {
            *ppv = (IUnknown*)this;
        }
        else if (riid == IID_IClassFactory)
        {
            *ppv = (IClassFactory*)this;
        }
        if (*ppv)
        {
            ((IUnknown*)(*ppv))->AddRef();
            return S_OK;
        }
        return E_NOINTERFACE;

    }

    ULONG STDMETHODCALLTYPE AddRef ()
    {
        return 0xcccccccc;
    }

    ULONG STDMETHODCALLTYPE Release ()
    {
        return 0xcccccccc;
    }


    // IClassFactory methods
    
    HRESULT STDMETHODCALLTYPE CreateInstance (IUnknown *punkOuter, REFIID riid, VOID **ppv)
    {
        HRESULT hr;
        *ppv = NULL;
        
        if (punkOuter)
        {
            return CLASS_E_NOAGGREGATION;
        }
        
        CMyCOMObject *obj = new CMyCOMObject();
        if (obj == NULL)
        {
            return E_OUTOFMEMORY;
        }
        
        hr = obj->QueryInterface(riid, ppv);
        obj->Release();
        return hr;
    }

    HRESULT STDMETHODCALLTYPE LockServer (BOOL fLock)
    {
        if (fLock)
            ObjectCreated();
        else
            ObjectDestroyed();
        return S_OK;
    }
};


CMyComObjectClassFactory g_CMyCOMObjectFactory;


extern "C"
BOOL WINAPI DllMain (HINSTANCE hmod, DWORD dwReason, PVOID pvReserved)
{
    ghInstance = hmod;
    return TRUE;
}


STDAPI DllGetClassObject (REFCLSID rclsid, REFIID riid, LPVOID *ppv)
{
    *ppv = NULL;
    if (rclsid == CLSID_CMyCOMObject)
    {
        return g_CMyCOMObjectFactory.QueryInterface(riid, ppv);
    }
    else
    {
        return CLASS_E_CLASSNOTAVAILABLE;
    }
}


STDAPI DllCanUnloadNow ()
{
    return g_ObjectCount;
}




// Plagiarized from comsamp.




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




//--------------------------------------------------------------------------
//
//  NTCompatibleRegDeleteKey
//
//--------------------------------------------------------------------------
LONG
NTCompatibleRegDeleteKey(HKEY hKey, LPCTSTR szSubKey)
{
   TCHAR achName[MAX_PATH+1];
   HKEY  hSubkey;

   if (ERROR_SUCCESS != RegOpenKey(hKey, szSubKey, &hSubkey)) {
      return REGDB_E_INVALIDVALUE;
   }

   if (ERROR_SUCCESS == RegEnumKey(hSubkey, 0, achName, sizeof(achName)/sizeof(TCHAR))) {
      RegCloseKey(hSubkey);
      // There's still one subkey: fail the call.
      return REGDB_E_INVALIDVALUE;
   }
   RegCloseKey(hSubkey);
   return RegDeleteKey(hKey, szSubKey);
}



STDAPI DllRegisterServer ()
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
   result = RegCreateKey(HKEY_CLASSES_ROOT, achSampleProgID, &hKey);
   if (result != ERROR_SUCCESS) {
      goto lExit;
   }
   result = RegCreateKey(hKey, TEXT("CLSID"), &hKey2);
   if (result != ERROR_SUCCESS) {
      goto lExit;
   }
   GUID2StringA(CLSID_CMyCOMObject, achCLSID);
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

   result = RegCreateKey(hKey2, achInprocServer32, &hKey3);
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

   result = RegSetValueEx(hKey3, achThreadingModel, 0, REG_SZ, (BYTE*)achBoth, sizeof(achBoth));
   if (result != ERROR_SUCCESS) {
      goto lExit;
   }

   RegCloseKey(hKey3);
   hKey3 = NULL;


   result = RegCreateKey(hKey2, achProgID, &hKey3);
   if (result != ERROR_SUCCESS) {
      goto lExit;
   }
   result = RegSetValue(hKey3, NULL, REG_SZ, achSampleProgID, lstrlen(achSampleProgID));
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



//----------------------------------------------------------------------
// DllUnregisterServer(): Called by OLE.
//----------------------------------------------------------------------
STDAPI DllUnregisterServer(VOID)
{
   HKEY    hKey  = NULL;
   HKEY    hKey2 = NULL;
   DWORD   result;
   HRESULT hr = SELFREG_E_CLASS;
   CHAR    achCLSID[GUIDSTR_MAX];

   // If we fail in the middle, the state of the registry entries
   // is indeterminate (as per Ole specs.)
   GUID2StringA(CLSID_CMyCOMObject, achCLSID);


   result = RegOpenKey(HKEY_CLASSES_ROOT, achSampleProgID, &hKey);
   if (result == ERROR_SUCCESS) {
      NTCompatibleRegDeleteKey(hKey, TEXT("CLSID"));
      RegCloseKey(hKey);
      hKey = NULL;
      NTCompatibleRegDeleteKey(HKEY_CLASSES_ROOT, achSampleProgID);
   }
   // If this fails, it means somebody else added a subkey to this tree.
   // We're not allowed to touch it so ignore the failure.


   result = RegOpenKey(HKEY_CLASSES_ROOT, TEXT("CLSID"), &hKey);
   if (result == ERROR_SUCCESS) {

      result = RegOpenKey(hKey, achCLSID, &hKey2);
      if (result == ERROR_SUCCESS) {
         NTCompatibleRegDeleteKey(hKey2, achInprocServer32);
         NTCompatibleRegDeleteKey(hKey2, achProgID);
         RegCloseKey(hKey2);
         hKey2 = NULL;
         NTCompatibleRegDeleteKey(hKey, achCLSID);
      }

      // If this fails, it means somebody else added a subkey to this tree.
      // We're not allowed to touch it so ignore the failure.

      RegCloseKey(hKey);
      hKey = NULL;
   }


   hr = S_OK;

   return hr;

}

