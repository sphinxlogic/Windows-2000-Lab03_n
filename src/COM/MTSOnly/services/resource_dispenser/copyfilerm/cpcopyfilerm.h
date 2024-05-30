
/******************************************************************************\
********************************************************************************
* Filename: CPCopyFileRm.h
*
* Description:
*
* This file is provided as part of the Microsoft Transaction Server
* Software Development Kit
*
*THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT 
*WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, 
*INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES 
*OF MERCHANTABILITY AND/OR FITNESS FOR A  PARTICULAR 
*PURPOSE.
*
* Copyright (C) 1997 Microsoft Corporation, All rights reserved
********************************************************************************
\******************************************************************************/

//////////////////////////////////////////////////////////////////////////////
// CProxyIFileRm
template <class T>
class CProxyIFileRm : public IConnectionPointImpl<T, &IID_IFileRm, CComDynamicUnkArray>
{
public:

//IFileRm : IUnknown
public:
	HRESULT Fire_CopyListTx(
		long lConHandle)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				IFileRm* pIFileRm = reinterpret_cast<IFileRm*>(*pp);
				ret = pIFileRm->CopyListTx(lConHandle);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_Disconnect(
		long ulConnHandle)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				IFileRm* pIFileRm = reinterpret_cast<IFileRm*>(*pp);
				ret = pIFileRm->Disconnect(ulConnHandle);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_Connect(
		BSTR sAppName,
		long * ulConnHandle)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				IFileRm* pIFileRm = reinterpret_cast<IFileRm*>(*pp);
				ret = pIFileRm->Connect(sAppName, ulConnHandle);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_FileCopyTx(
		long lConHandle,
		BSTR sSource,
		BSTR sDestination,
		long bFailIfExists)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				IFileRm* pIFileRm = reinterpret_cast<IFileRm*>(*pp);
				ret = pIFileRm->FileCopyTx(lConHandle, sSource, sDestination, bFailIfExists);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_FileRenameTx(
		long lConHandle,
		BSTR sSource,
		BSTR sDestination)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				IFileRm* pIFileRm = reinterpret_cast<IFileRm*>(*pp);
				ret = pIFileRm->FileRenameTx(lConHandle, sSource, sDestination);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_AddFile(
		long lConHandle,
		BSTR sSource,
		BSTR sDestination)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				IFileRm* pIFileRm = reinterpret_cast<IFileRm*>(*pp);
				ret = pIFileRm->AddFile(lConHandle, sSource, sDestination);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_CopyDirTx(
		long lConHandle,
		BSTR sSource,
		BSTR sDestination)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				IFileRm* pIFileRm = reinterpret_cast<IFileRm*>(*pp);
				ret = pIFileRm->CopyDirTx(lConHandle, sSource, sDestination);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_FileMoveTxt(
		long lConHandle,
		BSTR sSource,
		BSTR sDestination)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				IFileRm* pIFileRm = reinterpret_cast<IFileRm*>(*pp);
				ret = pIFileRm->FileMoveTxt(lConHandle, sSource, sDestination);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_FileDeleteTx(
		long lConHandle,
		BSTR sFileName)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				IFileRm* pIFileRm = reinterpret_cast<IFileRm*>(*pp);
				ret = pIFileRm->FileDeleteTx(lConHandle, sFileName);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_GetTmWhereabouts(
		long lConHandle,
		unsigned char * * rgbTmAddr,
		unsigned long * pcbTmAddr)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				IFileRm* pIFileRm = reinterpret_cast<IFileRm*>(*pp);
				ret = pIFileRm->GetTmWhereabouts(lConHandle, rgbTmAddr, pcbTmAddr);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ExportTx(
		long lConHandle,
		unsigned long cbTranCookie,
		unsigned char * rgbTranCookie)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				IFileRm* pIFileRm = reinterpret_cast<IFileRm*>(*pp);
				ret = pIFileRm->ExportTx(lConHandle, cbTranCookie, rgbTranCookie);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_SetVisible(
		int bVisible)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				IFileRm* pIFileRm = reinterpret_cast<IFileRm*>(*pp);
				ret = pIFileRm->SetVisible(bVisible);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ResetConnection(
		long lConHandle)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				IFileRm* pIFileRm = reinterpret_cast<IFileRm*>(*pp);
				ret = pIFileRm->ResetConnection(lConHandle);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_MarshalPointer(
		IStream * * ppStream)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				IFileRm* pIFileRm = reinterpret_cast<IFileRm*>(*pp);
				ret = pIFileRm->MarshalPointer(ppStream);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
};

