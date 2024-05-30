#ifndef _RMSINK_H
#define _RMSINK_H

//---------------------------------------------------------------------
// Header file definition of the  class CIResourceManagerSink 
// and all of its supporting constants and types.  The class 
// CIResourceManagerSink is the implementation of the resource
// manager interface IResourceManagerSink.
//---------------------------------------------------------------------


//---------------------------------------------------------------------
// CIResourceManagerSink:
//---------------------------------------------------------------------

class CIResourceManagerSink: public IResourceManagerSink
{
public:
	
	// Consructor interface:
	// CIResourceManagerSink object constructor and destructor.
	//		CIResourceManagerSink	--	constructor for the class
	//		~CIResourceManagerSink	--	destructor for the class

	CIResourceManagerSink(void);
	~CIResourceManagerSink(void);


	// IUnknown interface:
	// Definition of the IUnknown interface for CIResourceManagerSink
	// objects.
	//		QueryInterface	-- determines the existence of an interface
	//		AddRef			-- increments interface reference count
	//		Release			-- decrements interface reference count

	STDMETHODIMP			QueryInterface(REFIID i_iid, LPVOID FAR* ppv);
	STDMETHODIMP_ (ULONG)	AddRef(void);
	STDMETHODIMP_ (ULONG)	Release(void);

	// IResourceManagerSink interface:
	// Defines the TMDown interface to notify RM when the transaction 
	// transaction manager is down.
	//		TMDown			-- callback received when the TM goes down

	STDMETHODIMP			TMDown(void);
	
private:
	ULONG	m_cRefs;

}; // CIResourceManagerSink
#endif _RMSINK_H