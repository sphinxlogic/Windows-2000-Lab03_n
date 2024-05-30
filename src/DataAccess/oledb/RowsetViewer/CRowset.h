//-----------------------------------------------------------------------------
// Microsoft OLE DB RowsetViewer
// Copyright (C) 1994 - 1999 By Microsoft Corporation.
//
// @doc
//
// @module CROWSET.H
//
//-----------------------------------------------------------------------------------

#ifndef _CROWSET_H_
#define _CROWSET_H_


//////////////////////////////////////////////////////////////////////////////
// Defines
//
//////////////////////////////////////////////////////////////////////////////
enum BINDCOLS
{
	BIND_ALLCOLS				= 0x00000001,
	BIND_ALLCOLSEXPECTBOOKMARK	= 0x00000002,
	BIND_UPDATEABLECOLS			= 0x00000004
};


//////////////////////////////////////////////////////////////////////////////
// Forwards
//
//////////////////////////////////////////////////////////////////////////////
class CMainWindow;
class CMDIChild;


//////////////////////////////////////////////////////////////////////////////
// Includes
//
//////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
// CDataAccess
//
/////////////////////////////////////////////////////////////////
class CDataAccess : public CAsynchBase
{
public:
	//Constructors
	CDataAccess(SOURCE eObjectType, CMainWindow* pCMainWindow, CMDIChild* pCMDIChild = NULL);
	virtual ~CDataAccess();
	
	//IUnknown Helpers
	virtual HRESULT			AutoQI(DWORD dwCreateOpts);
	virtual HRESULT			AutoRelease();
	virtual IUnknown**		GetInterfaceAddress(REFIID riid);

	//Members
	virtual HRESULT			GetColInfo();
	virtual HRESULT			GetColInfo(DBORDINAL* pcColumns, DBCOLUMNINFO** prgColumnInfo, WCHAR** ppStringBuffer, ULONG* pcHiddenColumns);
	virtual DBCOLUMNINFO*	GetColInfo(DBORDINAL iOrdinal);
	virtual INT				GetColumnImage(DBCOLUMNINFO* pColInfo, DBSTATUS dbStatus = DBSTATUS_S_OK);
	virtual DBBINDING*		GetBinding(DBORDINAL iOrdinal);

	virtual HRESULT			ValidateAccessor(HACCESSOR hAccessor, ULONG ulRefCount = 1);
	virtual HRESULT			SetColumnData(DBBINDING* pBinding, void* pData, DBSTATUS   dbStatus, DBLENGTH   dbLength, WCHAR* pwszValue, DWORD dwFlags, DBTYPE wBackendType);
	virtual HRESULT			GetColumnData(DBBINDING* pBinding, void* pData, DBSTATUS* pdbStatus, DBLENGTH* pdbLength, DBTYPE* pwSubType, WCHAR* pwszValue, ULONG ulMaxSize, DWORD dwFlags, DBTYPE wBackendType);

	virtual HRESULT			CreateAccessors(BINDCOLS eBindCols);
	virtual HRESULT			CreateAccessor(DBACCESSORFLAGS dwAccessorFlags, DBCOUNTITEM cBindings, DBBINDING* rgBindings, DBLENGTH cRowSize, HACCESSOR* phAccessor);
	virtual HRESULT			SetupBindings(BINDCOLS eBindCols, DBCOUNTITEM* cBindings, DBBINDING** prgBindings, DBLENGTH* pcRowSize = NULL);

	virtual HRESULT			AddRefAccessor(HACCESSOR hAccessor);
	virtual HRESULT			ReleaseAccessor(HACCESSOR* phAccessor, BOOL fReleaseAlways = FALSE);
	virtual HRESULT			GetColumnsRowset(CAggregate* pCAggregate, BOOL fOptColumns, REFIID riid, ULONG cPropSets, DBPROPSET* rgPropSets, IUnknown** ppIUnknown);

	//Rowset
	//[MANADATORY]
	IAccessor*					m_pIAccessor;
	IColumnsInfo*				m_pIColumnsInfo;
	IConvertType*				m_pIConvertType;

	//[OPTIONAL]
	IColumnsRowset*				m_pIColumnsRowset;

	//ColInfo
	DBORDINAL					m_cColInfo;
	DBCOLUMNINFO*				m_rgColumnInfo;
	WCHAR*						m_pStringBuffer;
	ULONG						m_cHiddenColumns;	//DBPROP_HIDDENCOLUMNS

	//Accessor
	DBCOUNTITEM					m_cBindings;
	DBBINDING*					m_rgBindings;
	HACCESSOR					m_hAccessor;
	ULONG						m_cbRowSize;
	void*						m_pData;
	
	//Bookmark Accessor
	HACCESSOR					m_hBmkAccessor;
	BOOL						m_bSchemaRowset;
};


////////////////////////////////////////////////////////////////
// CRowset 
//
/////////////////////////////////////////////////////////////////
class CRowset : public CDataAccess
{
public:
	//Constructors
	CRowset(CMainWindow* pCMainWindow, CMDIChild* pCMDIChild = NULL);
	virtual ~CRowset();
	
	//IUnknown Helpers
	virtual HRESULT			AutoQI(DWORD dwCreateOpts);
	virtual HRESULT			AutoRelease();
	virtual IUnknown**		GetInterfaceAddress(REFIID riid);
 	
	//Pure Virtual
	virtual WCHAR*			GetObjectName()			{ return m_hChapter ? L"Chapter" : L"Rowset";		} 
	virtual UINT			GetObjectMenu()			{ return IDM_ROWSETMENU;							}
	virtual LONG			GetObjectImage()		{ return m_hChapter ? IMAGE_CHAPTER : IMAGE_TABLE;	}
	virtual REFIID			GetDefaultInterface()	{ return IID_IRowset;								}

	virtual WCHAR*			GetObjectDesc();
	virtual HRESULT			DisplayObject();

	//Members
	virtual HRESULT			ValidateRow(HROW hRow, ULONG ulRefCount = 1);

	virtual HRESULT			GetData(REFIID riidSource, HROW hRow, HACCESSOR hAccessor = NULL, void* pData = NULL);
	virtual HRESULT			GetBookmark(HROW hRow, DBBKMARK* pcbBookmark, BYTE** ppBookmark);
	virtual HRESULT			GetChapter(HROW hRow, DBORDINAL iOrdinal, HCHAPTER* phChapter);

	virtual HRESULT			RestartPosition();
	virtual HRESULT			GetNextRows(DBROWOFFSET lOffset, DBROWCOUNT cRows, DBCOUNTITEM* pcRowsObtained, HROW** prghRows);
	virtual HRESULT			AddRefRows(DBROWCOUNT cRows, HROW* rghRows, ULONG* rgRefCounts = NULL);
	virtual HRESULT			ReleaseRows(DBROWCOUNT cRows, HROW* rghRows, ULONG* rgRefCounts = NULL);
	virtual HRESULT			GetRowFromHROW(CAggregate* pCAggregate, HROW hRow, REFIID riid, IUnknown** ppIUnknown);

#ifdef INTERNAL_ONLY
	//Services
	virtual HRESULT			InvokeCursorEngine(IUnknown* pIUnkRowset, ULONG cPropSets, DBPROPSET* rgPropSets, REFIID riid, IUnknown** ppIUnkCERowset = NULL);
#endif //INTERNAL_ONLY

	//Rowset
	//[MANADATORY]
	IRowset*					m_pIRowset;
	IRowsetInfo*				m_pIRowsetInfo;

	//[OPTIONAL]
	IRowsetChange*				m_pIRowsetChange;
	IRowsetIdentity*			m_pIRowsetIdentity;
	IRowsetLocate*				m_pIRowsetLocate;
	IRowsetFind*				m_pIRowsetFind;
	IRowsetView*				m_pIRowsetView;
	IChapteredRowset*			m_pIChapteredRowset;
	IRowsetResynch*				m_pIRowsetResynch;
	IRowsetRefresh*				m_pIRowsetRefresh;
	IRowsetScroll*				m_pIRowsetScroll;
	IRowsetUpdate*				m_pIRowsetUpdate;
	IGetRow*					m_pIGetRow;

	DWORD						m_dwCookieRowsetNotify;

	//Chapters
	HCHAPTER					m_hChapter;
};


#endif //_CROWSET_H_
