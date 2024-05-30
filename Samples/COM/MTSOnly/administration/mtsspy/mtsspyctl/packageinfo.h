
/******************************************************************************\
********************************************************************************
* Filename: PackageInfo.h
*
* Description:  contains the definition of an object which holds information
				about package specific information
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
#ifndef __PACKAGE_INFO_H__
#define __PACKAGE_INFO_H__

class CMtsSink;
class CPackageSink;
class CMtsSpy;

class CPackageInfo
{
private:
	bool m_bReadyForDelete;
	IConnectionPointContainer * m_pContainer;
	SinkList * m_pList;		
	CComObject <CPackageSink> * m_pPackageSink;
	CComBSTR m_sPackageName;

public:
	
	CComBSTR & PackageName(){return m_sPackageName;}
	SinkList * List(){return m_pList;}
	void SetShowPackageEvent(BOOL bShow)
	{
		m_pPackageSink -> SetShowEvent(bShow);		
	}

	BOOL GetShowPackageEvent()
	{
		return m_pPackageSink -> GetShowEvent();
	}

	IConnectionPointContainer * CPContainer()
	{
		return m_pContainer;
	}

	CPackageInfo()
	{
		_ASSERTE(0); // don't use this ctor!
		m_pContainer = NULL;
		m_pList = NULL;
		m_bReadyForDelete = FALSE;
		m_pPackageSink = NULL;


	}
	CPackageInfo(IConnectionPointContainer * pCon, LPWSTR sPackageName, CMtsSpy * pSpy)
	{
		m_pContainer = pCon;
		m_sPackageName = sPackageName;
		m_pContainer -> AddRef();
		m_pList = new SinkList;
		m_bReadyForDelete = FALSE;	
		_ASSERTE(pSpy);

		HRESULT hr;
	//
	// we always set up an advise sink for the Package events in order to
	// get the event that the ASP is shutting down
	//
		hr = CComObject<CPackageSink>::CreateInstance(&m_pPackageSink);				
		_ASSERTE(hr == S_OK);

		// the class factory doesn't do an AddRef() because it expects
		// a QI to come after the CreateInstance(), so we have to do an
		// AddRef() here

		m_pPackageSink -> AddRef();
		m_pPackageSink -> Init(pCon, m_sPackageName.m_str);
		m_pPackageSink -> Advise();	
		m_pPackageSink -> SetShowEvent(FALSE);
		m_pPackageSink -> SetSpyObj(pSpy);

	}
	~CPackageInfo()
	{
		SinkList::iterator item;
		IMtsSink * pSink;
		ULONG refcount;
		m_pPackageSink -> DAdvise();
		refcount = m_pPackageSink -> Release();
		m_pPackageSink = NULL;

		for (item=m_pList -> begin(); item != m_pList -> end(); ++item)
		{		
			pSink = *item;
			if (pSink)
			{
				pSink -> DAdvise();
				refcount = pSink -> Release();
				_ASSERTE(refcount == 0);
				pSink = NULL;		
			}
		}

		SafeRelease(m_pContainer);
		m_pList -> clear();
		delete m_pList;
		m_pList = NULL;
	}

	void SetDeleteFlag(bool bDelete)
	{
		m_bReadyForDelete = bDelete;

	}
	bool IsReadyForDelete()
	{
		return m_bReadyForDelete;
	}
	
};

#endif
