// -----------------------------------------------------------------------------
// Helpers.h: Template Class that wraps MAPI buffers or interfaces so that you
//            don't have to concern yourself with freeing or releasing them.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef _HELPERS_H_
#define _HELPERS_H_

// -----------------------------------------------------------------------------
// Use this class to wrap a pointer to a mapi buffer.  It will automaticly get 
// freed when it goes out of scope.  Use the instance of this just as you would
// its base type.  Example:
//     CMAPIBuffer< LPENTRYID>  lpeid;
//     HRESULT hr = HrMAPIFindDefaultMsgStore( m_pMAPISession, &cbeid, &lpeid);
//     hr = m_pMAPISession->OpenMsgStore( 0, cbeid, lpeid, ...
//
// The intended use of this class is for declaring mapi buffer pointers on the
// stack or inside of another class or structure.  There is NO value in creating
// an instance of this class on the heap with new().  It's sole purpose in life
// is to keep you from having to remember to free the buffer.
//
// If you need to reuse the pointer be sure to call MAPIFREEBUFFER before 
// reusing it.  Example:
//     CMAPIBuffer< LPENTRYID>  lpeid;
//     HRESULT hr = HrMAPIFindDefaultMsgStore( m_pMAPISession, &cbeid, &lpeid);
//     ... // Do some other work... 
//     MAPIFREEBUFFER( lpeid);
//     hr = HrGetSomeOtherEID( &cbeid, &lpeid);
// -----------------------------------------------------------------------------

template< class TYPE>
class CMAPIBuffer
{
public:
    CMAPIBuffer( TYPE ptr = NULL)   { m_ptr = ptr;}
    ~CMAPIBuffer()                  { MAPIFREEBUFFER( m_ptr);}

    // Returns a pointer to the TYPE by just specifying the object.
    operator TYPE() {return( m_ptr);}

    // Returns the address of the object correct for the base type.
    TYPE* operator &() {return( &m_ptr);}

    void operator =(LPVOID lpv)  {m_ptr = (TYPE) lpv;}

protected:
    TYPE m_ptr;
};

// -----------------------------------------------------------------------------
// Use this class to wrap a pointer to a mapi interface.  It is nearly identical
// to the above class except that it releases the interface pointer when the 
// instance of the object goes out of scope.
//
// The intended use of this class is for declaring mapi interface pointers on the
// stack or inside of another class or structure.  There is NO value in creating
// an instance of this class on the heap with new().  It's sole purpose in life
// is to keep you from having to remember to release the interface.
// -----------------------------------------------------------------------------

template< class TYPE>
class CMAPIInterface
{
public:
    CMAPIInterface( TYPE ptr = NULL)   { m_ptr = ptr;}
    ~CMAPIInterface()                  { ULRELEASE( m_ptr);}

    // Returns a pointer to the TYPE by just specifying the object.
    operator TYPE()         {return( m_ptr);}

    // Returns the address of the object correct for the base type.
    TYPE* operator &() {return( &m_ptr);}

    // Returns a pointer to the TYPE for -> operations.
    TYPE operator ->()      {return( m_ptr);}

    void operator =(LPVOID lpv)  {m_ptr = (TYPE) lpv;}

protected:
    TYPE m_ptr;
};

// $--CMAPIIsInitialized--------------------------------------------------------
// Initialize MAPI using MAPIInitialize().  If it is successful then create an
// instance of this object which will uninitialize MAPI at destruction.
// -----------------------------------------------------------------------------

class CMAPIIsInitialized
{
public:
    ~CMAPIIsInitialized()     {MAPIUninitialize();}
};

// $--CMAPISession--------------------------------------------------------------
// Works just like CMAPIInterface but it also Logs off at destruction.
// -----------------------------------------------------------------------------

class CMAPISession : public CMAPIInterface< LPMAPISESSION>
{
public:
    // DESTRUCTOR logs off of the MAPI session and releases the session handle.
    ~CMAPISession() 
    {
        if( m_ptr)
            m_ptr->Logoff( 0L, 0L, 0L);
    }
};

// -----------------------------------------------------------------------------

#endif // _HELPERS_H_
