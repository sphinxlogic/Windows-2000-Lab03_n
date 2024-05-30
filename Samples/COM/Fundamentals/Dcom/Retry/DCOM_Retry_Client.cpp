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

#include "stdafx.h"
#include <tchar.h>
#include "COMMethodCaller.h"
using namespace MS_CMC ;

// The folowing line must be modified to reflect the actual location of Installation_Verification\VCAcct.dll
#import "..\..\..\Installation_Verification\VCAcct.dll" no_namespace

static void ReportError( const _com_error & e )
{
   cout << "HRESULT : "   << e.Error() << " ( 0x" <<  setiosflags( ios::hex | ios::uppercase ) << e.Error() << " )" << endl ;
   cout << "Message : \"" << e.ErrorMessage() << "\"" << endl ;
}

int main( int /*argc*/, char * * /*argv*/ )
{
   if ( FAILED(CoInitialize(NULL)) )
   {
      cerr << "CoInitialize() failed !" << endl ;
      return -1 ;
   }

   try
   {
      IAccountPtr p(__uuidof(CAccount)) ;
      cout << "Calling GetComMethodCaller(__uuidof(CAccount), p, IAccount::Post ) ( 1, 14 )" << endl ;
      _bstr_t s = GetComMethodCaller(__uuidof(CAccount), p, IAccount::Post ) ( 1, 14 ) ;
      cout << "Result: \"" << s << "\"." << endl ;
   }
   catch( const _com_error & e )
   {
      ReportError(e) ;
   }

   cout << endl ;

   try
   {
      IMoveMoneyPtr p ;
      cout << "Calling GetComMethodCaller(__uuidof(CMoveMoney), p, IMoveMoney::Perform, 10000, 2 ) ( 1, 2, 14, 3 )" << endl ;
      _bstr_t s = GetComMethodCaller(__uuidof(CMoveMoney), p, IMoveMoney::Perform, 10000, 2 ) ( 1, 2, 14, 3 ) ;
      cout << "Result: \"" << s << "\"." << endl ;
   }
   catch( const _com_error & e )
   {
      ReportError(e) ;
   }


   cout << endl ;

   CoUninitialize() ;

   cout << "Press any key." << endl ;
   _kbhit() ; getch() ;

	return 0 ;
}