//-----------------------------------------------------------------------------
// Microsoft OLE DB RowsetViewer
// Copyright (C) 1994 - 1999 By Microsoft Corporation.
//
// @doc
//
// @module CDATASOURCE.H
//
//-----------------------------------------------------------------------------------

#ifndef _CCOMMAND_H_
#define _CCOMMAND_H_


///////////////////////////////////////////////////////////////
// Includes
//
///////////////////////////////////////////////////////////////
#include "CRowset.h"	//CDataAccess



/////////////////////////////////////////////////////////////////
// CCommand class
//
/////////////////////////////////////////////////////////////////
class CCommand : public CDataAccess
{
public:
	//Constructors
	CCommand(CMainWindow* pCMainWindow, CMDIChild* pCMDIChild = NULL);
	virtual ~CCommand();

	//IUnknown Helpers
	virtual HRESULT			AutoQI(DWORD dwCreateOpts);
	virtual HRESULT			AutoRelease();
	virtual IUnknown**		GetInterfaceAddress(REFIID riid);

	//Pure Virtual
	virtual WCHAR*			GetObjectName()			{ return L"Command";		} 
	virtual UINT			GetObjectMenu()			{ return IDM_COMMANDMENU;	}
	virtual REFIID			GetDefaultInterface()	{ return IID_ICommand;		}
	virtual LONG			GetObjectImage()		{ return IMAGE_COMMAND;		}

	//Methods
	virtual HRESULT			Execute(CAggregate* pCAggregate, WCHAR* pwszCommandText, REFIID riid, DBPARAMS* pParams, DBROWCOUNT* pcRowsAffected, IUnknown** ppIUnknown);
	virtual HRESULT			SetCommandText(WCHAR* pwszText, GUID* pGuidDialect = NULL);
	virtual HRESULT			Prepare(ULONG cExpectedRuns);

	virtual HRESULT			SetProperties(ULONG cPropSets, DBPROPSET* rgPropSets);
	virtual HRESULT			GetCurrentCommand(DBID** ppCommandID);
	
	//Helpers
	virtual HRESULT			CreateParamAccessor(DB_UPARAMS cParams, DBPARAMINFO* rgParamInfo);
	virtual HRESULT			SetupBindings(DB_UPARAMS cParams, DBPARAMINFO* rgParamInfo, DBCOUNTITEM* cBindings, DBBINDING** prgBindings, DBLENGTH* pcRowSize = NULL);
	virtual HRESULT			GetParameterInfo(DB_UPARAMS* pcParams, DBPARAMINFO** prgParamInfo, OLECHAR** ppwszNamesBuffer);

	//OLE DB Interfaces

	//[MANDATORY]
//	IAccessor*				m_pIAccessor;				//CDataAccess base class
//	IColumnsInfo*			m_pIColumnsInfo;			//CDataAccess base class
//	IConvertType*			m_pIConvertType;			//CDataAccess base class
	ICommand*				m_pICommand;				//Command interface
	ICommandProperties*		m_pICommandProperties;		//Command interface
	ICommandText*			m_pICommandText;			//Command interface
	
	//[OPTIONAL]
	ICommandPrepare*		m_pICommandPrepare;			//Command interface
	ICommandPersist*		m_pICommandPersist;			//Command interface
	ICommandWithParameters*	m_pICommandWithParameters;	//Command interface

	//Parameters
	DBCOUNTITEM				m_cParamBindings;
	DBBINDING*				m_rgParamBindings;
	DBPARAMS				m_ParamInfo;

	//Data
	GUID					m_guidDialect;
};





#endif	//_CCOMMAND_H_
