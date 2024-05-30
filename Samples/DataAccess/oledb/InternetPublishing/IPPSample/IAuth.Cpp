/*------------------------------------------------------------------------------
	THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
	ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
	TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
	PARTICULAR PURPOSE.

	Copyright (C) 1998-1999.  Microsoft Corporation.  All rights reserved.

	iauth.cpp

	sample implementation of the IAuthenticate callback
------------------------------------------------------------------------------*/
#include "stdafx.h"


/*------------------------------------------------------------------------------
FUNCTION CImpAuth
------------------------------------------------------------------------------*/
CImpAuth::CImpAuth()
{
   m_nRefs = 0;
   m_wszUserName = NULL;
   m_wszPassword = NULL;
}

/*------------------------------------------------------------------------------
FUNCTION ~CImpAuth
------------------------------------------------------------------------------*/
CImpAuth::~CImpAuth()
{
   if(NULL != m_wszUserName)
   {
      delete [] m_wszUserName;
   }

   if(NULL != m_wszPassword)
   {
      delete [] m_wszPassword;
   }
}

/*------------------------------------------------------------------------------
FUNCTION QueryInterface
------------------------------------------------------------------------------*/
HRESULT CImpAuth::QueryInterface(REFIID iid, void ** ppvObject)
{
   if(NULL == ppvObject)
   {
      return E_INVALIDARG;
   }

   if((IID_IAuthenticate == iid)
      || (IID_IUnknown == iid))
   {
      *ppvObject = this;
      m_nRefs++;

      return S_OK;
   }
   else
   {
      *ppvObject = NULL;
      return E_NOINTERFACE;
   }
}

/*------------------------------------------------------------------------------
FUNCTION AddRef
------------------------------------------------------------------------------*/
ULONG CImpAuth::AddRef(void)
{
   return (++m_nRefs);
}

/*------------------------------------------------------------------------------
FUNCTION Release
------------------------------------------------------------------------------*/
ULONG CImpAuth::Release(void)
{
   ULONG nRef = (--m_nRefs);

   if(0 >= nRef)
   {
      delete this;
   }

   return nRef;
}

/*------------------------------------------------------------------------------
FUNCTION Authenticate

  The only useful method in the IAuthenticate interface.  We do not display a 
  UI.  We just return the username and password.  If this object is not 
  initialized with Set(), we return empty strings.

  Consumers of MSDAIPP are encouraged to implement this differently and pass
  their window handle to the provider.  MSDAIPP has built in ability to display
  a dialog to interactively ask the username and password from the users.

------------------------------------------------------------------------------*/
HRESULT STDMETHODCALLTYPE CImpAuth::Authenticate(
      /* out */      HWND     *phwnd,
      /* out */      LPWSTR   *pwszUserName,
      /* out */      LPWSTR   *pwszPassword )
{
   if(   (NULL == phwnd)
      || (NULL == pwszUserName)
      || (NULL == pwszPassword) )
   {
      return E_INVALIDARG;
   }

   if( (NULL == m_wszUserName) || (NULL == m_wszPassword) )
   {
      *phwnd = GetDesktopWindow();

      *pwszUserName = NULL;

      *pwszPassword = NULL;
   }
   else
   {
      *phwnd = (HWND)INVALID_HANDLE_VALUE;

      *pwszUserName = (LPWSTR)CoTaskMemAlloc(
                                 (wcslen(m_wszUserName) + 1) * sizeof(WCHAR));
      if(NULL == *pwszUserName)
      {
         *pwszUserName = NULL;

         return E_OUTOFMEMORY;
      }

      *pwszPassword = (LPWSTR)CoTaskMemAlloc(
                                 (wcslen(m_wszPassword) + 1) * sizeof(WCHAR));
      if(NULL == *pwszPassword)
      {
         CoTaskMemFree(*pwszUserName);
         *pwszUserName=NULL;

         return E_OUTOFMEMORY;
      }

      wcscpy(*pwszUserName, m_wszUserName);

      wcscpy(*pwszPassword, m_wszPassword);
   }

   return S_OK;
}

/*------------------------------------------------------------------------------
Function Set

  This function is for initializing this object with the username and password.

  It cannot be safely done in the constructor because we need to return failure
  when neccessary.
------------------------------------------------------------------------------*/
HRESULT  CImpAuth::Set(
      /* in */       LPWSTR    wszUserName,
      /* in */       LPWSTR    wszPassword)
{
   if((NULL == wszUserName)
      || (NULL == wszPassword))
   {
      return E_INVALIDARG;
   }

   m_wszUserName = DuplicateWSTR(wszUserName);
   if(NULL == m_wszUserName)
   {
      return E_OUTOFMEMORY;
   }

   m_wszPassword = DuplicateWSTR(wszPassword);
   if(NULL == m_wszPassword)
   {
      delete [] m_wszPassword;
      return E_OUTOFMEMORY;
   }

   return S_OK;
}
