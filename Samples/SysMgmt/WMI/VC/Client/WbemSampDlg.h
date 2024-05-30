// **************************************************************************
// Copyright (c) 1997-1999 Microsoft Corporation.
//
// File:  WBEMSampDlg.h
//
// Description:
//	This file declares the CWBEMSampleDlg dialog class. It is the main
//		dialog for the tutorial.
// 
// Part of: WMI Tutorial #1.
//
// Used by: CWBEMSampleApp::InitInstance().
//
// History:
//
// **************************************************************************

#if !defined(AFX_HMMENUMDLG_H__6AC7FBF9_FE04_11D0_AD84_00AA00B8E05A__INCLUDED_)
#define AFX_HMMENUMDLG_H__6AC7FBF9_FE04_11D0_AD84_00AA00B8E05A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <wbemcli.h>     // WMI interface declarations
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CWBEMSampleDlg dialog
class CAsyncQuerySink;
class CEventSink;

class CWBEMSampleDlg : public CDialog
{
// Construction
public:
	CWBEMSampleDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CWBEMSampleDlg();

// Dialog Data
	//{{AFX_DATA(CWBEMSampleDlg)
	enum { IDD = IDD_WBEMSAMPLE_DIALOG };
	CButton	m_diskDescriptions;
	CListBox	m_eventList;
	CButton	m_perm;
	CButton	m_temp;
	CButton	m_addEquipment;
	CButton	m_enumServicesAsync;
	CButton	m_enumServices;
	CButton	m_enumDisks;
	CButton	m_diskDetails;
	CButton	m_connect;
	CListBox	m_outputList;
	CString	m_namespace;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWBEMSampleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWBEMSampleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnAddEquipment();
	afx_msg void OnConnect();
	afx_msg void OnEnumdisks();
	afx_msg void OnEnumservices();
	afx_msg void OnDiskdetails();
	afx_msg void OnEnumservicesasync();
	afx_msg void OnRegPerm();
	afx_msg void OnRegTemp();
	virtual void OnCancel();
	afx_msg void OnDiskPropsDescriptions();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:

	BOOL m_regPerm, m_regTemp;

	CAsyncQuerySink *m_pQueryCallback;
	IWbemServices *m_pIWbemServices;
	IWbemServices *m_pOfficeService;

	void SetBlanket(void);
	BOOL EnsureOfficeNamespace(void);
	BOOL CheckOfficeNamespace(void);

	void AssociateToMachine(IWbemClassObject *pEquipInst);
	HRESULT GetCompSysRef(VARIANT *v);

	// event related.
	CEventSink *m_pEventSink;
	BOOL PermRegistered();
	BOOL OnTempRegister();
	void OnTempUnregister();
	BOOL OnPermRegister();
	void OnPermUnregister();

	// SampleViewer.mof 'creates' the consumer.
	BOOL GetConsumer(IWbemClassObject **pConsumer);
	BOOL AddFilter(IWbemClassObject **pFilter);
	BOOL AddBinding(IWbemClassObject *pConsumer, 
					IWbemClassObject *pFilter);

};
LPWSTR ValueToString(VARIANT *pValue, WCHAR **pbuf);
LPCTSTR ErrorString(SCODE sc);


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HMMENUMDLG_H__6AC7FBF9_FE04_11D0_AD84_00AA00B8E05A__INCLUDED_)
