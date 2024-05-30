/*------------------------------------------------------------------------------
	THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
	ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
	TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
	PARTICULAR PURPOSE.

	Copyright (C) 1998-1999.  Microsoft Corporation.  All rights reserved.

	sample1.h

	header file for sample1.cpp

------------------------------------------------------------------------------*/

#ifndef _SAMPLE1_H_
#define _SAMPLE1_H_

//operations to perform with IScopedOperations
enum ISO_OPS 
{
   ISO_MKDIR,
   ISO_COPY,
   ISO_MOVE,
   ISO_DELETE
};

//Tests:
HRESULT Download(int argc, wchar_t* argv[]);

HRESULT Upload(int argc, wchar_t* argv[]);

HRESULT Enum(int argc, wchar_t* argv[]);

HRESULT Search(int argc, wchar_t* argv[]);

HRESULT ISO(ISO_OPS Op, int argc, wchar_t* argv[]);


//Binding:
HRESULT Bind(      LPWSTR           wszUrl,
                   REFGUID          rguid,
                   REFIID           riid,
                   DWORD            dwFlags,
                   IUnknown**       ppUnk,
                   LPWSTR           wszUserName,
                   LPWSTR           wszPassword,
                   BOOL             fCreate);


//Helpers:
HRESULT EnumerateWithRowsetPointer(
                  IRowset  *pIRowset, 
                  BOOL     fVerbose);

HRESULT EnumerateParent(LPWSTR    wszUrl, 
                        LPWSTR    wszUserName, 
                        LPWSTR    wszPassword);

HRESULT GetParentUrl(LPWSTR    wszUrl,
                     LPWSTR    *ppwchParent);

LPWSTR DuplicateWSTR(LPWSTR wsz);

void PrintUsage();



//IAuthenticate:
class CImpAuth : public IAuthenticate
{
public:

   CImpAuth();

   ~CImpAuth();

   virtual HRESULT STDMETHODCALLTYPE QueryInterface(
         REFIID   iid, 
         void     **ppvObject);

   virtual ULONG STDMETHODCALLTYPE AddRef(void);

   virtual ULONG STDMETHODCALLTYPE Release(void);

   //For IAuthenticate:
   virtual HRESULT STDMETHODCALLTYPE Authenticate(
         /* out */      HWND     *phwnd,
         /* out */      LPWSTR   *pwszUserName,
         /* out */      LPWSTR   *pwszPassword );

   HRESULT  Set(
         /* in */       LPWSTR    wszUserName,
         /* in */       LPWSTR    wszPassword);

private:

        ULONG          m_nRefs;

        LPWSTR         m_wszUserName;
        LPWSTR         m_wszPassword;
};


#endif
