
//=--------------------------------------------------------------------------=
//  (C) Copyright 1996-1999 Microsoft Corporation. All Rights Reserved.
//=--------------------------------------------------------------------------=
// CBindStatusCallback2 -- we want a little more info than it is giving us, such as 
//      C&P'ed from ATL -- see ADDED below for additions, CHANGED for changes...

// PreBindMoniker() & OnBindingFailure() must be implemented in using class T
// public IBindStatusCallbackImpl<T>

template <class T>
class ATL_NO_VTABLE CBindStatusCallback2 :
	public CComObjectRootEx<T::_ThreadModel::ThreadModelNoCS>,
	public IBindStatusCallback
{
	// CHANGED from CBindStatusCallback
	typedef void (T::*ATL_PDATAAVAILABLE)(CBindStatusCallback2<T>* pbsc, BYTE* pBytes, DWORD dwSize,
			DWORD grfBSCF, FORMATETC *pformatetc, STGMEDIUM *pstgmed);
	// -------						

public:

BEGIN_COM_MAP(CBindStatusCallback2<T>)
	COM_INTERFACE_ENTRY_IID(IID_IBindStatusCallback, IBindStatusCallback)
//	COM_INTERFACE_ENTRY_IID(IID_IBindStatusCallback, IBindStatusCallbackImpl<T>)
END_COM_MAP()


	CBindStatusCallback2()
	{
		m_pT = NULL;
		m_pFunc = NULL;
	}
	~CBindStatusCallback2()
	{
		ATLTRACE(_T("~CBindStatusCallback2\n"));
	}

	STDMETHOD(OnStartBinding)(DWORD dwReserved, IBinding *pBinding)
	{
		ATLTRACE(_T("CBindStatusCallback2::OnStartBinding\n"));
		m_spBinding = pBinding;
		return S_OK;
	}

	STDMETHOD(GetPriority)(LONG *pnPriority)
	{
		ATLTRACENOTIMPL(_T("CBindStatusCallback2::GetPriority"));
	}

	STDMETHOD(OnLowResource)(DWORD reserved)
	{
		ATLTRACENOTIMPL(_T("CBindStatusCallback2::OnLowResource"));
	}

	STDMETHOD(OnProgress)(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, LPCWSTR szStatusText)
	{
		//ATLTRACENOTIMPL(_T("CBindStatusCallback2::OnProgress"));
		ATLTRACE(_T("CBindStatusCallback2::OnProgress : progress=%d / %d - status=%x\n"), ulProgress, ulProgressMax, ulStatusCode);
		_bstr_t strStatusText = szStatusText;
		ATLTRACE(_T("     status-text=%s\n"),(LPCTSTR)strStatusText);
		return E_NOTIMPL;
	}

	STDMETHOD(OnStopBinding)(HRESULT hresult, LPCWSTR szError)
	{
		ATLTRACE(_T("CBindStatusCallback2::OnStopBinding\n"));

		if (FAILED(hresult))
			m_pT->OnBindingFailure(hresult, szError);

		m_spBinding.Release();	// ADDED
		m_spBindCtx.Release();		
		m_spMoniker.Release();		

		return S_OK;
	}

	STDMETHOD(GetBindInfo)(DWORD *pgrfBINDF, BINDINFO *pbindInfo)
	{
		ATLTRACE(_T("CBindStatusCallback2::GetBindInfo\n"));
		if (!pbindInfo || !pbindInfo->cbSize || !pgrfBINDF)
			return E_INVALIDARG;
		*pgrfBINDF = BINDF_ASYNCHRONOUS | BINDF_ASYNCSTORAGE |
			BINDF_GETNEWESTVERSION | BINDF_NOWRITECACHE;
		
		// NOTE: BINDINFO has changed sizes between IE3 and IE4
		// Relying on a compiled sizeof(BINDINFO) can cause trouble.
		// The following changes will propagate to later versions of
		// ATL.

		// Remember incoming cbSize
		ULONG cbSize = pbindInfo->cbSize;

		memset(pbindInfo, 0, cbSize);

		// Restore cbSize
		pbindInfo->cbSize = cbSize;
		pbindInfo->dwBindVerb = BINDVERB_GET;

		return S_OK;
	}

	STDMETHOD(OnDataAvailable)(DWORD grfBSCF, DWORD dwSize, FORMATETC *pformatetc, STGMEDIUM *pstgmed)
	{
		ATLTRACE(_T("CBindStatusCallback2::OnDataAvailable\n"));
		HRESULT hr = S_OK;

		// Get the Stream passed
		if (BSCF_FIRSTDATANOTIFICATION & grfBSCF)
		{
			if (!m_spStream && pstgmed->tymed == TYMED_ISTREAM)
			{
				m_spStream = pstgmed->pstm;
/*				if (m_spStream)
					m_spStream->AddRef();*/ // CHANGED
			}
		}

		DWORD dwRead = dwSize - m_dwTotalRead; // Minimum amount available that hasn't been read
		DWORD dwActuallyRead = 0;              // Placeholder for amount read during this pull

		// If there is some data to be read then go ahead and read them
		if (m_spStream)
		{
			if (dwRead > 0)
			{
				BYTE* pBytes = NULL;
				ATLTRY(pBytes = new BYTE[dwRead + 1]);
				if (pBytes == NULL)
					return S_FALSE;
				hr = m_spStream->Read(pBytes, dwRead, &dwActuallyRead);
				if (SUCCEEDED(hr))
				{
					pBytes[dwActuallyRead] = 0;
					if (dwActuallyRead>0)
					{
						// CHANGED
						(m_pT->*m_pFunc)(this, pBytes, dwActuallyRead, grfBSCF, pformatetc, pstgmed);
						// -------						
						m_dwTotalRead += dwActuallyRead;
					}
				}
				delete[] pBytes;
			}
		}

		if (BSCF_LASTDATANOTIFICATION & grfBSCF)
			m_spStream.Release();
		return hr;
	}

	STDMETHOD(OnObjectAvailable)(REFIID riid, IUnknown *punk)
	{
		ATLTRACENOTIMPL(_T("CBindStatusCallback2::OnObjectAvailable"));
	}

	HRESULT _StartAsyncDownload(BSTR bstrURL, IUnknown* pUnkContainer, BOOL bRelative)
	{
		m_dwTotalRead = 0;
		m_dwAvailableToRead = 0;
		HRESULT hr = S_OK;
		CComQIPtr<IServiceProvider, &IID_IServiceProvider> spServiceProvider(pUnkContainer);
		CComPtr<IBindHost> spBindHost;
		if (spServiceProvider)
			spServiceProvider->QueryService(SID_IBindHost, IID_IBindHost, (void**)&spBindHost);

		if (spBindHost == NULL)
		{
			if (bRelative)
				return E_NOINTERFACE;  // relative asked for, but no IBindHost
			hr = CreateURLMoniker(NULL, bstrURL, &m_spMoniker);

			if (SUCCEEDED(hr))
				hr = CreateBindCtx(0, &m_spBindCtx);

			if (SUCCEEDED(hr))
				//hr = RegisterBindStatusCallback(m_spBindCtx, reinterpret_cast<IBindStatusCallback*>(static_cast<IBindStatusCallbackImpl<T>*>(this)), 0, 0L);
			    hr = RegisterBindStatusCallback(m_spBindCtx, reinterpret_cast<IBindStatusCallback*>(static_cast<IBindStatusCallback*>(this)), 0, 0L);
			else
				m_spMoniker.Release();

			// ADDED to CBindStatusCallback
			if (SUCCEEDED(hr))
				hr = m_pT->PreBindMoniker(m_spBindCtx, m_spMoniker);
			// -----

			if (SUCCEEDED(hr))
			{
				IStream* pStream;
				hr = m_spMoniker->BindToStorage(m_spBindCtx, 0, IID_IStream, (void**)&pStream);
				if (pStream != NULL) // ADDED
					pStream->Release();
			}
		}
		else
		{
			hr = CreateBindCtx(0, &m_spBindCtx);

			/*if (SUCCEEDED(hr))
				hr = RegisterBindStatusCallback(m_spBindCtx, reinterpret_cast<IBindStatusCallback*>(static_cast<IBindStatusCallbackImpl<T>*>(this)), 0, 0L);*/
				// If we're working through the IBindHost interface, we should specify the
				// IBSC on MonikerBindToStorage, not registered on the IBindCtx

			if (SUCCEEDED(hr))
			{
				if (bRelative)
					hr = spBindHost->CreateMoniker(bstrURL, m_spBindCtx, &m_spMoniker, 0);
				else
					hr = CreateURLMoniker(NULL, bstrURL, &m_spMoniker);
			}

			// ADDED
			if (SUCCEEDED(hr))
				hr = m_pT->PreBindMoniker(m_spBindCtx, m_spMoniker);
			// -----

			if (SUCCEEDED(hr))
			{
				IStream* pStream;
				hr = spBindHost->MonikerBindToStorage(m_spMoniker, m_spBindCtx, reinterpret_cast<IBindStatusCallback*>(static_cast<IBindStatusCallback*>(this)), IID_IStream, (void**)&pStream);
				//hr = spBindHost->MonikerBindToStorage(m_spMoniker, m_spBindCtx, reinterpret_cast<IBindStatusCallback*>(static_cast<IBindStatusCallbackImpl<T>*>(this)), IID_IStream, (void**)&pStream);
				if (pStream != NULL) // ADDED
					pStream->Release();
				ATLTRACE(_T("Bound"));
			}
		}
		return hr;
	}

	HRESULT StartAsyncDownload(T* pT, ATL_PDATAAVAILABLE pFunc, BSTR bstrURL, IUnknown* pUnkContainer = NULL, BOOL bRelative = FALSE)
	{
		m_pT = pT;
		m_pFunc = pFunc;
		return  _StartAsyncDownload(bstrURL, pUnkContainer, bRelative);
	}

	static HRESULT Download(T* pT, ATL_PDATAAVAILABLE pFunc, BSTR bstrURL, IUnknown* pUnkContainer = NULL, BOOL bRelative = FALSE)
	{
		CComObject<CBindStatusCallback2<T> > *pbsc;
		HRESULT hRes = CComObject<CBindStatusCallback2<T> >::CreateInstance(&pbsc);
		if (FAILED(hRes))
			return hRes;
		return pbsc->StartAsyncDownload(pT, pFunc, bstrURL, pUnkContainer, bRelative);
	}

	CComPtr<IMoniker> m_spMoniker;
	CComPtr<IBindCtx> m_spBindCtx;
	CComPtr<IBinding> m_spBinding;
	CComPtr<IStream> m_spStream;
	T* m_pT;
	ATL_PDATAAVAILABLE m_pFunc;
	DWORD m_dwTotalRead;
	DWORD m_dwAvailableToRead;
};

