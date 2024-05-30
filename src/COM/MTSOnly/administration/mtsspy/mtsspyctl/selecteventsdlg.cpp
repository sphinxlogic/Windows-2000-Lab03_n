
/******************************************************************************\
********************************************************************************
* Filename: SelectEventsDlg.cpp
*
* Description:  Dialog to select which events to sink to.  Selecting a sink
				causes the sink to be established.
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
// SelectEventsDlg.cpp : Implementation of CSelectEventsDlg
#include "stdafx.h"
#include "mtsspyctl.h"
#include "mtsevents.h"
#include "MtsAudit.h"
#include "MTSSpy.h"
#include "MtsSink.h"
#include "TxSink.h"
#include "objsink.h"
#include "threadsink.h"
#include "instancesink.h"
#include "resourcesink.h"
#include "packagesink.h"
#include "usersink.h"
#include "PackageInfo.h"
#include "SelectEventsDlg.h"
#include <algorithm>
#include "methodsink.h"
#include "MtsGrp.h"
#include "MtsGrp_i.c"
#include "eventcpts.h"
#include "securitysink.h"


typedef struct _EVENT_SINK_INFO
{
	TCHAR * sDisplayName;
	EventEnum eEvent;
}EVENT_SINK_INFO;

EVENT_SINK_INFO EventInfo[] =	{
								_T("Package"),		Package, 
								_T("Thread"),		Thread, 
								_T("Instance"),		Instance,
								_T("Transaction"),	Transaction,
								_T("Method"),		Method,
								_T("Object"),		Object,
								_T("Resource"),		Resource,
							    _T("UserDefined"),	User,
								_T("Security"),		Security
								};

CSelectEventsDlg::CSelectEventsDlg()
{
	
}

CSelectEventsDlg::~CSelectEventsDlg()
{
}

LRESULT CSelectEventsDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ResetEventList();
	GetRunningAsps();
	return 1;  // Let the system set the focus
}

LRESULT CSelectEventsDlg::OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	EndDialog(wID);
	return 0;
}

LRESULT CSelectEventsDlg::OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	EndDialog(wID);
	return 0;
}

LRESULT CSelectEventsDlg::OnDestroyDlg(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{

	bHandled = FALSE;
	return 0;
}

//
//	
//	get the IMtsEvents interface, get the Package Name
//	and add it to the combo box
//
BOOL CSelectEventsDlg::GetRunningAsps()
{
	HRESULT hr = E_FAIL;
	IMtsGrp * pMtsGrp = NULL;
	hr = CoCreateInstance (CLSID_MtsGrp, NULL, CLSCTX_ALL, IID_IMtsGrp, (void **)&pMtsGrp);
	if (!pMtsGrp)
	{
		_ASSERTE(0);
		return FALSE;
	}

	long lPackages;
	pMtsGrp -> get_Count(&lPackages);
	IUnknown * pUnk = NULL;
	IMtsEvents * pEvents = NULL;
	USES_CONVERSION;
	int nIndex;
	for (int i=0; i<lPackages; i++)
	{

		pMtsGrp -> Item(i, &pUnk);
		pEvents = NULL;
		pUnk -> QueryInterface(IID_IMtsEvents, (void **)&pEvents);
		_ASSERTE(pEvents);		
		CComBSTR sName;
		CPackageInfo * pInfo = NULL;			
		pEvents -> get_PackageName(&sName.m_str);					
		IConnectionPointContainer * pContainer=NULL;
		hr = pEvents -> QueryInterface(IID_IConnectionPointContainer, (void **)&pContainer);
		_ASSERTE(hr == S_OK);
		if (SUCCEEDED(hr))
		{
			LPSTR p = W2A(sName.m_str);
			pInfo = (*m_map)[p];
			if (!pInfo)
			{
				_ASSERTE(m_pSpyObj);
				pInfo = new CPackageInfo(pContainer, sName.m_str, m_pSpyObj); // this will register for the package events
				_ASSERTE(pInfo);
				(*m_map)[p] = pInfo;
			}					
			nIndex = SendDlgItemMessage(IDC_PACKAGES, CB_ADDSTRING, 0, (LPARAM)sName.m_str);
			if (nIndex != CB_ERR)
			{																	
				SendDlgItemMessage(IDC_PACKAGES, CB_SETITEMDATA, nIndex, (DWORD)pInfo);																
			}	
			else
				_ASSERTE(0);
		}

		SafeRelease(pEvents);
		SafeRelease(pUnk);
		SafeRelease(pContainer);					
	}

	SafeRelease(pMtsGrp);				
	
	SendDlgItemMessage(IDC_PACKAGES, CB_SETCURSEL, 0);
	int bHandled = TRUE;
	OnSelectPackages(CBN_SELCHANGE,0,NULL, bHandled);
	return TRUE;
	
}
//
//	the user selects a package from the drop down list box.
//	
LRESULT CSelectEventsDlg::OnSelectPackages(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (wNotifyCode == CBN_SELCHANGE)
	{
		
		// get the package name
		int nSel = SendDlgItemMessage(IDC_PACKAGES, CB_GETCURSEL, 0, 0L);			   
		if (nSel != CB_ERR)
		{
			
			// we store the CPackageInfo structure in the item data...
			CPackageInfo * pInfo = NULL;
			pInfo = (CPackageInfo *)SendDlgItemMessage(IDC_PACKAGES, CB_GETITEMDATA, nSel);
			_ASSERTE(pInfo);

			// update the list of sinks
			ResetEventList();

			// interate through the list and make sure that the list boxes reflects what's going on				
			SinkList::iterator item;
			EventEnum nType;
			IMtsSink * pSink;
			int nIndex;
			DWORD dwItemData;
			TCHAR sz[32];
			CComBSTR sDisplayName;
			for (item = pInfo -> List() -> begin(); item != pInfo -> List() -> end(); item++)
			{
				
				pSink = *item;
				if (pSink)
				{
					pSink -> GetSinkType(&nType);
					GetDisplayName(nType, &sDisplayName);
					nIndex = SendDlgItemMessage(IDC_EVENTS, LB_FINDSTRING, 0,  (LPARAM)sDisplayName.m_str);
					if (nIndex != LB_ERR)
					{
						// move it to the other list
						memset(&sz[0], NULL, 32*sizeof(TCHAR));
						SendDlgItemMessage(IDC_EVENTS, LB_GETTEXT, nIndex, (LPARAM)sz);
						dwItemData = SendDlgItemMessage(IDC_EVENTS, LB_GETITEMDATA, nIndex);
						SendDlgItemMessage(IDC_EVENTS, LB_DELETESTRING, nIndex);
						nIndex = SendDlgItemMessage(IDC_SINKS, LB_ADDSTRING, 0, (LPARAM)sz);
						SendDlgItemMessage(IDC_SINKS, LB_SETITEMDATA, nIndex, (LPARAM)dwItemData);

					}
					else
						_ASSERTE(0);
				}

			}
			

			// we do special processing for the package event, since we are always sinked to it

			 if (pInfo -> GetShowPackageEvent())
			 {
				nIndex = SendDlgItemMessage(IDC_EVENTS, LB_FINDSTRING, 0,  (LPARAM)_T("Package"));
				// move it to the other list
				memset(&sz[0], NULL, 32*sizeof(TCHAR));
				SendDlgItemMessage(IDC_EVENTS, LB_GETTEXT, nIndex, (LPARAM)sz);
				dwItemData = SendDlgItemMessage(IDC_EVENTS, LB_GETITEMDATA, nIndex);
				SendDlgItemMessage(IDC_EVENTS, LB_DELETESTRING, nIndex);
				nIndex = SendDlgItemMessage(IDC_SINKS, LB_ADDSTRING, 0, (LPARAM)sz);
				SendDlgItemMessage(IDC_SINKS, LB_SETITEMDATA, nIndex, (LPARAM)dwItemData);
			 }
		
			// if the count on the left hand side == 0, disable the add sink button
				::EnableWindow(GetDlgItem(IDC_ADD_SINK), SendDlgItemMessage(IDC_EVENTS, LB_GETCOUNT));
			// if there are no sinks, don't enable the remove sink button
				::EnableWindow(GetDlgItem(IDC_REMOVE_FROM_SINK), SendDlgItemMessage(IDC_SINKS, LB_GETCOUNT));


		}
		else
		{
			
			::EnableWindow(GetDlgItem(IDC_ADD_SINK), FALSE);
			::EnableWindow(GetDlgItem(IDC_REMOVE_FROM_SINK), FALSE);
		}

	}

	return 0;
}

//
//	the user is adding one or more sinks for the selected (running) package
//
LRESULT CSelectEventsDlg::OnAddSink(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{

	if (wNotifyCode == BN_CLICKED)
	{
		//we are a multi-select list box...
		int nCount = SendDlgItemMessage(IDC_EVENTS, LB_GETSELCOUNT);
		if (nCount != LB_ERR && nCount)
		{

			int nSel = SendDlgItemMessage(IDC_PACKAGES, CB_GETCURSEL, 0, 0L);			   
			if (nSel == CB_ERR)
			{
				_ASSERTE(0);
				return 0;
			}

			// get the information for the current package
			CPackageInfo * pInfo = NULL;
			pInfo = (CPackageInfo *)SendDlgItemMessage(IDC_PACKAGES, CB_GETITEMDATA, nSel);
			_ASSERTE(pInfo);

			int * nSelItems = new int[nCount];
			SendDlgItemMessage(IDC_EVENTS,LB_GETSELITEMS, nCount, (LPARAM)nSelItems);	
			int i;
			WCHAR sz[16];
			DWORD dwItemData;
			int nItem;
			MapStringToPackageInfo::iterator iter;
			HRESULT hr;
			USES_CONVERSION;
			IMtsSink * pMtsSink = NULL;
			for (i=0;i<nCount;i++)
			{
				
				// move string and item data to the other list box
				memset(&sz[0], NULL, 16*sizeof(TCHAR));
				SendDlgItemMessage(IDC_EVENTS, LB_GETTEXT, nSelItems[i], (LPARAM)sz);
				dwItemData = SendDlgItemMessage(IDC_EVENTS, LB_GETITEMDATA, nSelItems[i]);
				nItem = SendDlgItemMessage(IDC_SINKS, LB_ADDSTRING, 0, (LPARAM)sz);
				SendDlgItemMessage(IDC_SINKS, LB_SETITEMDATA, nItem, (LPARAM)dwItemData);
				
				// find out what type of sink has been requested, and create the appropriate object
				EventEnum  event = (EventEnum) dwItemData;										
				switch (event)
				{
					case Security:
					{						

						CComObject <CSecuritySink> * pSink = NULL;
						hr = CComObject<CSecuritySink>::CreateInstance(&pSink);				
						pSink -> SetSpyObj(m_pSpyObj);
						_ASSERTE(pSink);
						pSink -> QueryInterface(IID_IMtsSink, (void **)&pMtsSink);		
						_ASSERTE(pSink);

					}
					break;
					case Transaction:
					{
						CComObject <CTxSink> * pSink;
						hr = CComObject<CTxSink>::CreateInstance(&pSink);				
						pSink -> SetSpyObj(m_pSpyObj);
						_ASSERTE(pSink);
						pSink -> QueryInterface(IID_IMtsSink, (void **)&pMtsSink);								
						_ASSERTE(pSink);
						break;
					}
					case Resource:
					{						
						CComObject <CResourceSink> * pSink;
						hr = CComObject<CResourceSink>::CreateInstance(&pSink);				
						pSink -> SetSpyObj(m_pSpyObj);
						_ASSERTE(pSink);
						pSink -> QueryInterface(IID_IMtsSink, (void **)&pMtsSink);					
						_ASSERTE(pSink);
					}
					break;
					case Object:
					{						
						CComObject <CObjSink> * pSink;
						hr = CComObject<CObjSink>::CreateInstance(&pSink);				
						pSink -> SetSpyObj(m_pSpyObj);
						_ASSERTE(pSink);
						pSink -> QueryInterface(IID_IMtsSink, (void **)&pMtsSink);						
						_ASSERTE(pSink);
						break;
					}
					break;
					case Thread:
					{						
						CComObject <CThreadSink> * pSink;
						hr = CComObject<CThreadSink>::CreateInstance(&pSink);				
						pSink -> SetSpyObj(m_pSpyObj);
						_ASSERTE(pSink);
						pSink -> QueryInterface(IID_IMtsSink, (void **)&pMtsSink);		
						_ASSERTE(pSink);
					}
					break;
					case Instance:
					{						
						CComObject <CInstanceSink> * pSink;
						hr = CComObject<CInstanceSink>::CreateInstance(&pSink);				
						pSink -> SetSpyObj(m_pSpyObj);
						_ASSERTE(pSink);					
						pSink -> QueryInterface(IID_IMtsSink, (void **)&pMtsSink);
						_ASSERTE(pSink);
						break;
					}
					break;
					//
					// package events are "special" -- we've already sinked to them
					//
					case Package:
					{						
						pInfo -> SetShowPackageEvent(TRUE);
						break;
					}
					case Method:
					{						
						CComObject <CMethodSink> * pSink;
						hr = CComObject<CMethodSink>::CreateInstance(&pSink);				
						pSink -> SetSpyObj(m_pSpyObj);
						_ASSERTE(pSink);
						pSink -> QueryInterface(IID_IMtsSink, (void **)&pMtsSink);
						_ASSERTE(pSink);
					}
					break;
					case User:
					{						
						CComObject <CUserSink> * pSink;
						hr = CComObject<CUserSink>::CreateInstance(&pSink);				
						pSink -> SetSpyObj(m_pSpyObj);
						_ASSERTE(pSink);
						pSink -> QueryInterface(IID_IMtsSink, (void **)&pMtsSink);		
						_ASSERTE(pSink);
					}
					break;
					default:
						pMtsSink = NULL;						
						ATLTRACE(L"Object type not implemented yet\n");
						_ASSERTE(0);
						break;
				}
				if (pMtsSink) // we've successfully created the sink
				{
					
					// initialize it
					pMtsSink -> Init(pInfo -> CPContainer(), pInfo -> PackageName());
					pMtsSink -> Advise();						
					_ASSERTE(pInfo);
					pInfo -> List() -> insert (pInfo -> List() ->end(), pMtsSink);									
					pMtsSink = NULL;
				}

			
			}
			// remove from listbox in reverse order
			for (i=nCount-1;i>=0;i--)
			{
				SendDlgItemMessage(IDC_EVENTS, LB_DELETESTRING, nSelItems[i]);
			}


			delete [] nSelItems;
		

			// if the count on the left hand side == 0, disable the add sink button
				::EnableWindow(GetDlgItem(IDC_ADD_SINK), SendDlgItemMessage(IDC_EVENTS, LB_GETCOUNT));
			// if there are no sinks, don't enable the remove sink button
				::EnableWindow(GetDlgItem(IDC_REMOVE_FROM_SINK), SendDlgItemMessage(IDC_SINKS, LB_GETCOUNT));

		}

	}

	return 0;
	
}
//
//	remove one or more sinks
//
LRESULT CSelectEventsDlg::OnRemoveSink(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (wNotifyCode == BN_CLICKED)
	{

		int nCount = SendDlgItemMessage(IDC_SINKS, LB_GETSELCOUNT);
		if (nCount != LB_ERR && nCount)
		{

			// get package name
			int nSel = SendDlgItemMessage(IDC_PACKAGES, CB_GETCURSEL, 0, 0L);			   
			if (nSel == CB_ERR)
			{
				_ASSERTE(0);
				return 0;
			}

			CPackageInfo * pInfo = NULL;
			pInfo = (CPackageInfo *)SendDlgItemMessage(IDC_PACKAGES, CB_GETITEMDATA, nSel);
			_ASSERTE(pInfo);

			MapStringToPackageInfo::iterator iter;		
			int * nSelItems = new int[nCount];
			 SendDlgItemMessage(IDC_SINKS,LB_GETSELITEMS, nCount, (LPARAM)nSelItems);	
			int i;
			WCHAR sz[16];
			DWORD dwItemData;
			int nItem;
			SinkList::iterator iterSink;
			IMtsSink * pSink;
			EventEnum eSinkType;
			for (i=0;i<nCount;i++)
			{
				
				memset(&sz[0], NULL, 16*sizeof(TCHAR));
				SendDlgItemMessage(IDC_SINKS, LB_GETTEXT, nSelItems[i], (LPARAM)sz);
				dwItemData = SendDlgItemMessage(IDC_SINKS, LB_GETITEMDATA, nSelItems[i]);				
				if (dwItemData == Package) // package sink
					pInfo -> SetShowPackageEvent(FALSE);
				nItem  = SendDlgItemMessage(IDC_EVENTS, LB_ADDSTRING, 0, (LPARAM)sz);
				SendDlgItemMessage(IDC_EVENTS, LB_SETITEMDATA, nItem, (LPARAM)dwItemData);
				//iterate through the list looking for matching item data and sink id
				for (iterSink=pInfo -> List() -> begin(); iterSink != pInfo -> List() -> end(); ++iterSink)
				{		
					pSink = *iterSink;
					if (pSink)
					{
						pSink -> GetSinkType(&eSinkType);
						if (eSinkType == (EventEnum)dwItemData)
						{							
							pSink -> DAdvise();
							pSink -> Release();
							pInfo -> List() -> erase(iterSink++);														
							break;

						}
						
					}
					
				}
									
			}
			// remove strings from list in reverse order
			for (i=nCount-1;i >= 0;i--)
			{
				SendDlgItemMessage(IDC_SINKS, LB_DELETESTRING, nSelItems[i]);
			}


			delete [] nSelItems;

			
			
			// if the count on the left hand side == 0, disable the add sink button
			::EnableWindow(GetDlgItem(IDC_ADD_SINK), SendDlgItemMessage(IDC_EVENTS, LB_GETCOUNT));
			// if there are no sinks, don't enable the remove sink button
			::EnableWindow(GetDlgItem(IDC_REMOVE_FROM_SINK), SendDlgItemMessage(IDC_SINKS, LB_GETCOUNT));

		}

	}

	return 0;
}

void CSelectEventsDlg::ResetEventList()
{
	SendDlgItemMessage(IDC_EVENTS, LB_RESETCONTENT);
	SendDlgItemMessage(IDC_SINKS, LB_RESETCONTENT);

	int i;
	// fill the Possible Events list
	int nIndex;
	for (i=0; i<sizeof(EventInfo)/sizeof(EventInfo[0]); i++)
	{
		nIndex = SendDlgItemMessage(IDC_EVENTS, LB_ADDSTRING, 0,  (LPARAM)EventInfo[i].sDisplayName);
		SendDlgItemMessage(IDC_EVENTS, LB_SETITEMDATA, nIndex,  (LPARAM)EventInfo[i].eEvent);
	}
}

//
//	do the right thing when the user double clicks on the list box
//
LRESULT CSelectEventsDlg::EventListHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{

	if (wNotifyCode == LBN_DBLCLK)
	{
		HWND hWndAddSinkButton = GetDlgItem(IDC_ADD_SINK);
		if (::IsWindowEnabled( hWndAddSinkButton ))
			OnAddSink(BN_CLICKED, IDC_ADD_SINK, hWndAddSinkButton, bHandled);

	}

	bHandled = FALSE;
	return 0;
}
//
//	do the right thing when the user double clicks on the list box
//
LRESULT CSelectEventsDlg::SinkListHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{

	if (wNotifyCode == LBN_DBLCLK)
	{
		HWND hWndRemoveSinkButton = GetDlgItem(IDC_REMOVE_FROM_SINK);
		if (::IsWindowEnabled( hWndRemoveSinkButton ))
			OnRemoveSink(BN_CLICKED, IDC_REMOVE_FROM_SINK, hWndRemoveSinkButton, bHandled);

	}

	bHandled = FALSE;
	return 0;
}
// 
//	given an EventEnum, get the display Name
HRESULT CSelectEventsDlg::GetDisplayName(EventEnum e, BSTR * sDisplayName)
{	
	int i;
	for (i = 0; i< sizeof(EventInfo)/sizeof(EventInfo[0]); i++)
	{

		if (EventInfo[i].eEvent == e)
		{
			*sDisplayName = ::SysAllocString(EventInfo[i].sDisplayName);
			return S_OK;
		}
	}
	return E_FAIL;
}
