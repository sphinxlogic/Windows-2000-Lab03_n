//-----------------------------------------------------------------------------
// Microsoft OLE DB RowsetViewer
// Copyright (C) 1994 - 1999 By Microsoft Corporation.
//
// @doc
//
// @module CDATASOURCE.H
//
//-----------------------------------------------------------------------------------

#ifndef _CDATASOURCE_H_
#define _CDATASOURCE_H_


///////////////////////////////////////////////////////////////
// Includes
//
///////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
// CDataSource class
//
/////////////////////////////////////////////////////////////////
class CDataSource : public CPropertiesBase
{
public:
	//Constructors
	CDataSource(CMainWindow* pCMainWindow, CMDIChild* pCMDIChild = NULL);
	virtual ~CDataSource();

	//IUnknown Helpers
	virtual HRESULT			AutoQI(DWORD dwCreateOpts);
	virtual HRESULT			AutoRelease();
	virtual IUnknown**		GetInterfaceAddress(REFIID riid);

	//Pure Virtual
	virtual WCHAR*			GetObjectName()			{ return L"DataSource";				}
	virtual UINT			GetObjectMenu()			{ return IDM_DATASOURCEMENU;		}
	virtual REFIID			GetDefaultInterface()	{ return IID_IDBProperties;			}
	virtual WCHAR*			GetObjectDesc();

#ifdef INTERNAL_ONLY
	virtual LONG			GetObjectImage()	{ return (m_dwPoolState & DRAWN_FROMPOOL) ? IMAGE_DRAWNPOOL : IMAGE_DATASOURCE;	}
#else
	virtual LONG			GetObjectImage()	{ return IMAGE_DATASOURCE;			}
#endif //INTERNAL_ONLY

	//Members

	//Helpers
	virtual HRESULT			CreateSession(CAggregate* pCAggregate, REFIID riid, IUnknown** ppIUnknown);
	virtual HRESULT			AdminCreateDataSource(CAggregate* pCAggregate, ULONG cPropSets, DBPROPSET* rgPropSets, REFIID riid, IUnknown** ppIUnknown);
	virtual HRESULT			GetClassID(CLSID* pclsid, WCHAR** ppwszProgID = NULL);

	//Pooling
#ifdef INTERNAL_ONLY
	virtual HRESULT			GetPool(IPoolInfo** ppIPoolInfo);
	virtual HRESULT			GetPoolState(DWORD* pdwPoolState);

	DWORD						m_dwPoolState;
	IGetPool*					m_pIGetPool;					//Service Interface
#endif	//INTERNAL_ONLY


	//OLE DB Interfaces
	//[MANADATORY]
	IDBCreateSession*			m_pIDBCreateSession;			//DataSource interface
	IPersist*					m_pIPersist;					//DataSource interface

	//[OPTIONAL]
	IDBDataSourceAdmin*			m_pIDBDataSourceAdmin;			//DataSource interface
	IDBInfo*					m_pIDBInfo;						//DataSource interface
	IPersistFile*				m_pIPersistFile;				//DataSource interface

	//Services
	IServiceProvider*			m_pIServiceProvider;			//Service Interface

	//DataSource info
	BSTR						m_bstrDataSource;
	BSTR						m_bstrDBMS;
	BSTR						m_bstrDBMSVer;

	BSTR						m_bstrProviderName;
	BSTR						m_bstrProviderDesc;
	LONG						m_lDataSourceType;
};


#endif	//_CDATASOURCE_H_
