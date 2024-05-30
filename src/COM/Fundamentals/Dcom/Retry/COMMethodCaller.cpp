//==============================================================================
//
// This file is part of the Microsoft COM+ Samples
//
// Copyright (C) 1995-1999 Microsoft Corporation. All rights reserved
//
// This source code is intended only as a supplement to Microsoft
// Development Tools and/or on-line documentation.  See these other
// materials for detailed information reagrding Microsoft code samples.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
//==============================================================================

#include <comdef.h>
#include <crtdbg.h>
#include <tchar.h>

#include "COMMethodCaller.h"
using namespace MS_CMC ;

/*static*/ DWORD CCOMMethodCallerBase::sm_dwDefaultTimeDelay = 5000 ; // Time Delay between retries
/*static*/ WORD  CCOMMethodCallerBase::sm_wDefaulMaxRetries = 2 ; // Maximum number of retries

CCOMMethodCallerBase::CCOMMethodCallerBase( const CLSID & clsid, 
                                            DWORD dwTimeDelay, 
                                            WORD wMaxRetries )
                     :m_clsid(clsid), m_dwTimeDelay(dwTimeDelay), m_wMaxRetries(wMaxRetries)
{
}

CCOMMethodCallerBase & CCOMMethodCallerBase::operator = ( const CCOMMethodCallerBase & cmcb )
{
   if ( this != & cmcb )
      *this = cmcb ; // Never called but compiler complains (warning) if not defined.
   return *this ;
}

bool CCOMMethodCallerBase::RetryHelper( const _com_error & e, int * piRetry ) const
{ 
   if (    m_wMaxRetries == 0 
        || (    e.Error() != MAKE_HRESULT( SEVERITY_ERROR, FACILITY_WIN32, RPC_S_SERVER_UNAVAILABLE ) 
             && e.Error() != MAKE_HRESULT( SEVERITY_ERROR, FACILITY_WIN32, RPC_S_CALL_FAILED ) ) )
      return false ;

   if ( *piRetry < m_wMaxRetries )
      ::Sleep( m_dwTimeDelay ) ;
   else
   {
      DWORD dwT0 = GetTickCount() ;
	   TCHAR szAppName[_MAX_PATH] ;
		GetModuleFileName( NULL, szAppName, _MAX_PATH ) ;
      LPOLESTR  pszProgID = NULL ;
      ::ProgIDFromCLSID( m_clsid, & pszProgID ) ;
      LPOLESTR pszClsID = NULL ;
      ::StringFromCLSID( m_clsid, & pszClsID ) ;
      TCHAR szText[256] ;

      ::wsprintf( szText, 
                  _T("Error calling a COM object! (%s)\n\nClass ID =\t%ls\nProgrammatic ID =\t\"%ls\"\n\nDo you want to retry?"),
                  e.ErrorMessage(), 
                  pszClsID == NULL ? L"?" : pszClsID,
                  pszProgID == NULL ? L"?" : pszProgID ) ;
      ::CoTaskMemFree( pszProgID ) ;
      ::CoTaskMemFree( pszClsID ) ;
	   if ( IDYES == ::MessageBox( NULL, szText, szAppName, MB_YESNO | MB_ICONERROR |  MB_DEFAULT_DESKTOP_ONLY | MB_TASKMODAL ) )
      {
         *piRetry = m_wMaxRetries - 1 ; // Force one more iteration
         int iDelay = m_dwTimeDelay - static_cast<DWORD>(GetTickCount() - dwT0) ;
         if ( iDelay > 0 )
            ::Sleep( static_cast<DWORD>(iDelay) ) ;
      }
      else
         return false ;
   }

   return true ;
}
