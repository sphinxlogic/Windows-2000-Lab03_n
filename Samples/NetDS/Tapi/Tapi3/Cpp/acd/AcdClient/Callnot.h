////////////////////////////////////////////////////////////////////////////
// TAPIEventNotification.h : Declaration of the CTAPIEventNotification object
//
////////////////////////////////////////////////////////////////////////////
#ifndef __TAPIEventNotification_H__
#define __TAPIEventNotification_H__

/////////////////////////////////////////////////////////////////////////////
// CTAPIEventNotification
class CTAPIEventNotification : public ITTAPIEventNotification
{
private:

    DWORD       m_dwRefCount;

public:

    // CTAPIEventNotification implements ITTAPIEventNotification
    //  Declare ITTAPIEventNotification methods here
    HRESULT STDMETHODCALLTYPE Event(
                                    TAPI_EVENT TapiEvent,
                                    IDispatch * pEvent
                                   );
    
// other COM stuff:
public:

    // constructor
    CTAPIEventNotification(){}
    // destructor
    ~CTAPIEventNotification(){}

    // initialization function
    // this stuff could also be done in the
    // constructor
    HRESULT Initialize( )
    {
        m_dwRefCount = 1;
 
        return S_OK;
    }

    void Shutdown()
    {
    }

    // IUnknown implementation
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void **ppvObject)
    {
        if (iid == IID_ITTAPIEventNotification)
        {
            m_dwRefCount++;
            *ppvObject = (void *)this;
            return S_OK;
        }

        if (iid == IID_IUnknown)
        {
            m_dwRefCount++;            
            *ppvObject = (void *)this;
            return S_OK;
        }

        return E_NOINTERFACE;
    }
	ULONG STDMETHODCALLTYPE AddRef()
    {
        m_dwRefCount++;
        return m_dwRefCount;
    }
    
	ULONG STDMETHODCALLTYPE Release()
    {
        ULONG l;
        
        l  = m_dwRefCount--;

        if ( 0 == m_dwRefCount)
        {
            delete this;
        }
        
        return l;
    }


};

#endif //__TAPIEventNotification_H__


