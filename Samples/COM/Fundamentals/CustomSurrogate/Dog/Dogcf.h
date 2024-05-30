extern LONG g_cObjects;

class CClassFactory : public IClassFactory
{
public:
    // IUnknown methods 
    STDMETHOD(QueryInterface)(REFIID riid, LPVOID FAR* ppvObj);
    STDMETHOD_(ULONG, AddRef)(void);
    STDMETHOD_(ULONG, Release)(void); 
    
    // IClassFactory methods
    STDMETHOD(CreateInstance)(IUnknown FAR* punkOuter, REFIID riid, 
                              void FAR* FAR* ppv);
    STDMETHOD(LockServer)(BOOL fLock);    
    
    CClassFactory() {    m_cRef = 0; InterlockedIncrement(&g_cObjects); }
    
private:
    LONG m_cRef;                   // Reference count
};     
