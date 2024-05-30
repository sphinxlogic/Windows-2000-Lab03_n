#include "idog.h"

extern LONG g_cObjects;
class CDog : public IDog
{
public:
    // IUnknown  
    STDMETHOD(QueryInterface)(REFIID riid, LPVOID FAR* ppvObj);
    STDMETHOD_(ULONG, AddRef)(void);
    STDMETHOD_(ULONG, Release)(void);
    
    // IDog 
    STDMETHOD(Bark)();
    STDMETHOD(Scratch)();    
    
    CDog() { m_cRef = 0; InterlockedIncrement(&g_cObjects); }
    ~CDog() { InterlockedDecrement(&g_cObjects); }
private:
    LONG m_cRef;                   // Reference count
};     
