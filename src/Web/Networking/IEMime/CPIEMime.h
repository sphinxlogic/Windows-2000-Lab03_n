
//=--------------------------------------------------------------------------=
//  (C) Copyright 1996-1999 Microsoft Corporation. All Rights Reserved.
//=--------------------------------------------------------------------------=
//////////////////////////////////////////////////////////////////////////////
// CProxyDIEMimeEvents
template <class T>
class CProxyDIEMimeEvents : public IConnectionPointImpl<T, &DIID__IEMimeEvents, CComDynamicUnkArray>
{
public:
//methods:
//DIEMimeEvents : IDispatch
public:
	void Fire_Complete()
	{
		VARIANT varResult;
		VariantInit(&varResult);
		T* pT = (T*)this;
		pT->Lock();
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				DISPPARAMS disp = { NULL, NULL, 0, 0 };
				IDispatch* pDispatch = reinterpret_cast<IDispatch*>(*pp);
				pDispatch->Invoke(0x1, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
			}
			pp++;
		}
		pT->Unlock();
	}

};

