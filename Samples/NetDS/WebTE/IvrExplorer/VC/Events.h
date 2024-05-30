// ChildFrm.h : interface of the DEventsClass class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef EVENTS_H_INCLUDED
#define EVENTS_H_INCLUDED

class CIvrExplorerView;
class DEventsClass : public IDispatch
{
    

    public:
        DEventsClass() {};
        ~DEventsClass(void);

        void                 SetContainer(CIvrExplorerView *pContainer)
                                 { m_pContainer = pContainer; }

        //IUnknown members
        STDMETHODIMP         QueryInterface(REFIID, void **);
        STDMETHODIMP_(DWORD) AddRef(void);
        STDMETHODIMP_(DWORD) Release(void);

        //IDispatch members
        STDMETHODIMP_(long)  GetTypeInfoCount(UINT *pctinfo);

        STDMETHODIMP         GetTypeInfo(UINT iTInfo,
                                         LCID lcid,
                                         ITypeInfo **ppTInfo);

        STDMETHODIMP         GetIDsOfNames(REFIID riid,
                                           LPOLESTR *rgszNames,
                                           UINT cNames,
                                           LCID lcid,
                                           DISPID *rgDispId);

        STDMETHODIMP         Invoke(DISPID dispIdMember,
                                    REFIID riid,
                                    LCID lcid,
                                    WORD wFlags,
                                    DISPPARAMS *pDispParams,
                                    VARIANT *pVarResult,
                                    EXCEPINFO *pExcepInfo,
                                    UINT *puArgErr);

    private:
        ULONG        m_cRef;     //Reference count
        CIvrExplorerView *m_pContainer;
};

#endif // EVENTS_H_INCLUDED