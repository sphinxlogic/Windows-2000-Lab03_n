#include "stdafx.h"
#include "initguid.h"
#include    <txdtc.h>
#include	<xolehlp.h>
#include	<txcoord.h>
#include	"rmsink.h"


//
// CIResourceManagerSink class implementation:
//

CIResourceManagerSink::CIResourceManagerSink(void)
{
	m_cRefs = 0;						// Initialize the reference 
										// count.
} // CIResourceManagerSink::CIResourceManagerSink()


CIResourceManagerSink::~CIResourceManagerSink(void)
{
	// Do nothing.
} // CIResourceManagerSink::~CIResourceManagerSink()


STDMETHODIMP CIResourceManagerSink::QueryInterface(REFIID i_iid, LPVOID *ppv)
{
	*ppv = 0;						// Initialize interface pointer.

	
	if (IID_IUnknown == i_iid || IID_IResourceManagerSink == i_iid)
	{								// IID supported return interface.
		*ppv = this;
	} // if

	
	if (0 == *ppv)					// Check for null interface pointer.
	{										
		return ResultFromScode (E_NOINTERFACE);
									// Neither IUnknown nor 
									// IResourceManagerSink supported--
									// so return no interface.
	} // if

	((LPUNKNOWN) *ppv)->AddRef();	// Interface is supported. Increment
									// its usage count.
	
	return S_OK;

} // CIResourceManagerSink::QueryInterface()



STDMETHODIMP_ (ULONG) CIResourceManagerSink::AddRef(void)
{
	
	return ++m_cRefs;				// Increment interface usage count.
	
} // CIResourceManagerSink::AddRef()



STDMETHODIMP_ (ULONG) CIResourceManagerSink::Release(void)
{

	--m_cRefs;						// Decrement usage reference count.

	if (0 != m_cRefs)				// Is anyone using the interface?
	{								// The interface is in use.
		return m_cRefs;				// Return the number of references.
	} // if

	delete this;					// Interface not in use -- delete!

	return 0;						// Zero references returned.
				
} // CIResourceManagerSink::Release()

//
//	TMDown should trigger a recover.  It is called when DTC goes down
//	we should go into recovery mode.
//
//	
//
STDMETHODIMP CIResourceManagerSink::TMDown(void)
{
	return S_OK;				
								
} // CIResourceManagerSink::TMDown()
