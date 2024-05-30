/*++

Copyright (c) 1996  Microsoft Corporation

Module Name:

   refcount.hpp

Abstract:

   Reference counting class description.

--*/


#ifndef __REFCOUNT_HPP__
#define __REFCOUNT_HPP__


/* Macros
 *********/

//
// Define generic method delegation from a derived class to a base class.
//
// E.g.,
//
// DEFINE_DELEGATED_METHOD(InprocServerClassFactory, ClassFactory, HRESULT, LockServer, (BOOL bLock), (bLock));
//
// defines a delegated method call from InprocServerClassFactory::LockServer()
// to ClassFactory::LockServer().
//

#define DEFINE_DELEGATED_METHOD(derived_cls, base_cls, result_type, method, derived_paren_args, base_paren_args) \
   result_type STDMETHODCALLTYPE derived_cls::method derived_paren_args \
   { \
      return(base_cls::method base_paren_args); \
   }

#define DEFINE_DELEGATED_REFCOUNT_ADDREF(cls) \
   DEFINE_DELEGATED_METHOD(cls, RefCount, ULONG, AddRef, (void), ())

#define DEFINE_DELEGATED_REFCOUNT_RELEASE(cls) \
   ULONG STDMETHODCALLTYPE cls::Release(void) \
   { \
      ULONG ulcRef; \
   \
      ulcRef = RefCount::DecUsage(); \
   \
      if (! ulcRef) \
         delete(this); \
   \
      return(ulcRef); \
   }


/* Classes
 **********/

// Generic reference counting virtual base class.

class RefCount
{
private:
	/* Fields
	 *********/

   // reference count
   ULONG m_ulcRef;

public:
	/* Methods
	 **********/

   RefCount(void)
   {
      m_ulcRef = 1;

      return;
   }

   ~RefCount(void)
   {
   }

   ULONG STDMETHODCALLTYPE AddRef(void)
   {
      ULONG ulcRef;

      ulcRef = (ULONG)(InterlockedIncrement((LPLONG)(&m_ulcRef)));

      return(ulcRef);
   }

   ULONG STDMETHODCALLTYPE DecUsage(void)
   {
      ULONG ulcRef;

      ulcRef = (ULONG)(InterlockedDecrement((LPLONG)(&m_ulcRef)));

      return(ulcRef);
   }
};


#endif  // ! __REFCOUNT_HPP__

