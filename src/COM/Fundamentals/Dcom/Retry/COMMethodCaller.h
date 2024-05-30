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

#pragma once

namespace MS_CMC {

//*********************************************************************************
//*
//* Base class to keep the CLSID, time delay between retries and number of retries.
//*
//*********************************************************************************

class CCOMMethodCallerBase
{
   public: 
      CCOMMethodCallerBase( const CLSID & clsid, DWORD dwTimeDelay, WORD wMaxRetries ) ;

      CCOMMethodCallerBase & operator = ( const CCOMMethodCallerBase & cmcb ) ;

      const CLSID & GetCLSID() const { return m_clsid ; }
      DWORD GetTimeDelay() const     { return m_dwTimeDelay ; }
      WORD GetMaxRetries() const     { return m_wMaxRetries ; } 

      void SetDefaultTimeDelay( DWORD dw ) { sm_dwDefaultTimeDelay = dw ; }
      void DefaulMaxRetries( WORD w )      { sm_wDefaulMaxRetries = w ; }

      bool RetryHelper( const _com_error & e, int * piRetry ) const ;

   protected:
      const CLSID & m_clsid ;
      DWORD         m_dwTimeDelay ;
      WORD          m_wMaxRetries ;

      static DWORD sm_dwDefaultTimeDelay ;
      static WORD  sm_wDefaulMaxRetries ;
} ;

//*********************************************************
//*
//* Base template class to keep the Smart Interface Pointer
//*
//*********************************************************

template <class SIP>
class CCOMMethodCaller : public CCOMMethodCallerBase
{
   public:
      CCOMMethodCaller( const CLSID & clsid, SIP & sip, DWORD dwTimeDelay, WORD wMaxRetries )
         :CCOMMethodCallerBase( clsid, dwTimeDelay, wMaxRetries ), m_sip(sip) {} ;

	   CCOMMethodCaller<SIP> & operator=( const CCOMMethodCaller<SIP> & cmc ) throw()
      {  // Never called but not explicitly defining it generates a warning
         if ( this != & cmc )
            sip = cmc.sip ;
		   return *this;
	   }

      bool NoInstance() const           { return m_sip == NULL ; }
      HRESULT CreateInstance() throw () { return m_sip.CreateInstance(m_clsid) ; }
      void ReleaseInstance() throw()    { m_sip.Release() ; }

   protected:
      SIP & m_sip ;
} ;

//********************************
//*
//* The actual retry logic is here
//*
//********************************

template < class CMC >
CMC::ResultType ActuallyCallMethodAndRetry( CMC & cmc ) throw()
{
   for( int i = 0 ; i <= cmc.GetMaxRetries() ; i++ )
      try
      {
         if ( cmc.NoInstance() )
            cmc.CreateInstance() ;
         return cmc.ActuallyCallMethod() ;
      }
      catch( const _com_error & e )
      {
         if ( cmc.RetryHelper( e, & i ) )
            cmc.ReleaseInstance() ;
         else
            throw ;
      }

   return CMC::ResultType() ;
}

//*************************************
//*
//* Support for method with no argument
//*
//*************************************

template < class SIP, class IP, typename RT >
class CCOMMethodCaller0 : public CCOMMethodCaller<SIP>
{
   public:
      typedef RT ResultType ;

      CCOMMethodCaller0( const CLSID & clsid, SIP & sip, RT (IP::*pM) (), DWORD dwTimeDelay, WORD wMaxRetries )
         :CCOMMethodCaller<SIP>( clsid, sip, dwTimeDelay, wMaxRetries ), m_pM(pM) {} ;

      RT operator () () throw()
      {
         return ActuallyCallMethodAndRetry( *this ) ;
      }

      RT ActuallyCallMethod() throw() { return (m_sip->*m_pM) () ; }

   protected:
      RT (IP::* m_pM ) () ;
} ;

template< class SIP, class IP, typename RT>
CCOMMethodCaller0<SIP,IP,RT> GetComMethodCaller( const CLSID & clsid, SIP & sip, RT (IP::*pM) (), DWORD dwTimeDelay = CCOMMethodCallerBase::sm_dwDefaultTimeDelay, WORD wMaxRetries = CCOMMethodCallerBase::sm_wDefaulMaxRetries ) throw()
{
   return CCOMMethodCaller0<SIP,IP,RT>( clsid, sip, pM, dwTimeDelay, wMaxRetries ) ;
}

//**************************************
//*
//* Support for method with one argument
//*
//**************************************

template < class SIP, class IP, typename RT, typename P >
class CCOMMethodCaller1 : public CCOMMethodCaller<SIP>
{
   public:
      typedef RT ResultType ;

      CCOMMethodCaller1( const CLSID & clsid, SIP & sip, RT (IP::*pM) ( P ), DWORD dwTimeDelay, WORD wMaxRetries )
         :CCOMMethodCaller<SIP>( clsid, sip, dwTimeDelay, wMaxRetries ), m_pM(pM) {} ;

      RT operator () ( P p ) throw()
      {
         m_p = p ;
         return ActuallyCallMethodAndRetry( *this ) ;
      }

      RT ActuallyCallMethod() throw() { return (m_sip->*m_pM) (m_p) ; }

   protected:
      RT (IP::* m_pM ) (P) ;
      P         m_p ;
} ;

template< class SIP, class IP, typename RT, typename P >
CCOMMethodCaller1<SIP,IP,RT,P> GetComMethodCaller( const CLSID & clsid, SIP & sip, RT (IP::*pM) (P), DWORD dwTimeDelay = CCOMMethodCallerBase::sm_dwDefaultTimeDelay, WORD wMaxRetries = CCOMMethodCallerBase::sm_wDefaulMaxRetries ) throw()
{
   return CCOMMethodCaller1<SIP,IP,RT,P>( clsid, sip, pM, dwTimeDelay, wMaxRetries ) ;
}

//***************************************
//*
//* Support for method with two arguments
//*
//***************************************

template < class SIP, class IP, typename RT, typename P1, typename P2 >
class CCOMMethodCaller2 : public CCOMMethodCaller<SIP>
{
   public:
      typedef RT ResultType ;

      CCOMMethodCaller2( const CLSID & clsid, SIP & sip, RT (IP::*pM) (P1,P2), DWORD dwTimeDelay, WORD wMaxRetries )
         :CCOMMethodCaller<SIP>( clsid, sip, dwTimeDelay, wMaxRetries ), m_pM(pM) {}

      RT operator () ( P1 p1, P2 p2 ) throw()
      {
         m_p1 = p1 ;
         m_p2 = p2 ;
         return ActuallyCallMethodAndRetry( *this ) ;
      }

      RT ActuallyCallMethod() throw() { return (m_sip->*m_pM) (m_p1,m_p2) ; }

   protected:
      RT (IP::* m_pM ) (P1,P2) ;
      P1        m_p1 ;
      P2        m_p2 ;
} ;

template< class SIP, class IP, typename RT, typename P1, typename P2 >
CCOMMethodCaller2<SIP,IP,RT,P1,P2> GetComMethodCaller( const CLSID & clsid, SIP & sip, RT (IP::*pM) (P1,P2), DWORD dwTimeDelay = CCOMMethodCallerBase::sm_dwDefaultTimeDelay, WORD wMaxRetries = CCOMMethodCallerBase::sm_wDefaulMaxRetries ) throw()
{
   return CCOMMethodCaller2<SIP,IP,RT,P1,P2>( clsid, sip, pM, dwTimeDelay, wMaxRetries ) ;
}

//*****************************************
//*
//* Support for method with three arguments
//*
//*****************************************

template < class SIP, class IP, typename RT, typename P1, typename P2, typename P3 >
class CCOMMethodCaller3 : public CCOMMethodCaller<SIP>
{
   public:
      typedef RT ResultType ;

      CCOMMethodCaller3( const CLSID & clsid, SIP & sip, RT (IP::*pM) (P1,P2,P3), DWORD dwTimeDelay, WORD wMaxRetries )
         :CCOMMethodCaller<SIP>( clsid, sip, dwTimeDelay, wMaxRetries ), m_pM(pM) {} ;

      RT operator () ( P1 p1, P2 p2, P3 p3 ) throw()
      {
         m_p1 = p1 ;
         m_p2 = p2 ;
         m_p3 = p3 ;
         return ActuallyCallMethodAndRetry( *this ) ;
      }

      RT ActuallyCallMethod() throw() { return (m_sip->*m_pM) (m_p1,m_p2,m_p3) ; }

   protected:
      RT (IP::* m_pM ) (P1,P2,P3) ;
      P1        m_p1 ;
      P2        m_p2 ;
      P3        m_p3 ;
} ;

template< class SIP, class IP, typename RT, typename P1, typename P2, typename P3 >
CCOMMethodCaller3<SIP,IP,RT,P1,P2,P3> GetComMethodCaller( const CLSID & clsid, SIP & sip, RT (IP::*pM) (P1,P2,P3), DWORD dwTimeDelay = CCOMMethodCallerBase::sm_dwDefaultTimeDelay, WORD wMaxRetries = CCOMMethodCallerBase::sm_wDefaulMaxRetries ) throw()
{
   return CCOMMethodCaller3<SIP,IP,RT,P1,P2,P3>( clsid, sip, pM, dwTimeDelay, wMaxRetries ) ;
}
//*****************************************
//*
//* Support for method with four arguments
//*
//*****************************************

template < class SIP, class IP, typename RT, typename P1, typename P2, typename P3, typename P4 >
class CCOMMethodCaller4 : public CCOMMethodCaller<SIP>
{
   public:
      typedef RT ResultType ;

      CCOMMethodCaller4( const CLSID & clsid, SIP & sip, RT (IP::*pM) (P1,P2,P3,P4), DWORD dwTimeDelay, WORD wMaxRetries )
         :CCOMMethodCaller<SIP>( clsid, sip, dwTimeDelay, wMaxRetries ), m_pM(pM) {} ;

      RT operator () ( P1 p1, P2 p2, P3 p3, P4 p4 ) throw()
      {
         m_p1 = p1 ;
         m_p2 = p2 ;
         m_p3 = p3 ;
         m_p4 = p4 ;
         return ActuallyCallMethodAndRetry( *this ) ;
      }

      RT ActuallyCallMethod() throw() { return (m_sip->*m_pM) (m_p1,m_p2,m_p3,m_p4) ; }

   protected:
      RT (IP::* m_pM ) (P1,P2,P3,P4) ;
      P1        m_p1 ;
      P2        m_p2 ;
      P3        m_p3 ;
      P4        m_p4 ;
} ;

template< class SIP, class IP, typename RT, typename P1, typename P2, typename P3, typename P4 >
CCOMMethodCaller4<SIP,IP,RT,P1,P2,P3,P4> GetComMethodCaller( const CLSID & clsid, SIP & sip, RT (IP::*pM) (P1,P2,P3,P4), DWORD dwTimeDelay = CCOMMethodCallerBase::sm_dwDefaultTimeDelay, WORD wMaxRetries = CCOMMethodCallerBase::sm_wDefaulMaxRetries ) throw()
{
   return CCOMMethodCaller4<SIP,IP,RT,P1,P2,P3,P4>( clsid, sip, pM, dwTimeDelay, wMaxRetries ) ;
}


} // end namespace