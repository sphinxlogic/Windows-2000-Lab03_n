//-----------------------------------------------------------------------------
// Microsoft OLE DB RowsetViewer
// Copyright (C) 1994 - 1999 By Microsoft Corporation.
//	  
// @doc
//												  
// @module CDIALOGLITE.H
//
//-----------------------------------------------------------------------------------


//////////////////////////////////////////////////////////////////////////
// Defines
//
//////////////////////////////////////////////////////////////////////////
#ifndef __CDIALOGLITE_H__
#define __CDIALOGLITE_H__


//////////////////////////////////////////////////////////////////////////
// Macros
//
//////////////////////////////////////////////////////////////////////////
#define ON_COMMAND(ID, func)			case ID: (func); return TRUE;
#define ON_COMMAND_UI(ID, flags)		case ID: (*pdwFlags = (flags)); return TRUE;
#define ON_COMMAND_UI_ENABLED(ID, func)	ON_COMMAND_UI(ID, (func) ? MF_ENABLED : MF_GRAYED)
#define ON_COMMAND_UI_CHECKED(ID, func)	ON_COMMAND_UI(ID, (func) ? MF_CHECKED : MF_UNCHECKED)

#define STATEIMAGEINDEX(iImage)			INDEXTOSTATEIMAGEMASK(iImage+1)
#define BST2STATE(dwValue)				((dwValue) ? BST_CHECKED : BST_UNCHECKED)
#define BST3STATE(dwValue)				((dwValue) ? ((dwValue) == BST_INDETERMINATE ? (dwValue) : BST_CHECKED) : BST_UNCHECKED)

//INDEX
typedef LRESULT	INDEX;
const INDEX		INVALID_INDEX	= -1;


//////////////////////////////////////////////////////////////////////////
// Includes
//
//////////////////////////////////////////////////////////////////////////
#include <richedit.h>
#include "Error.h"


//////////////////////////////////////////////////////////////////////////
// Typedefs
//
//////////////////////////////////////////////////////////////////////////
#define REFPOINTS	const POINTS &
#define REFRECT		const RECT &


//////////////////////////////////////////////////////////////////////////
// Forwards
//
//////////////////////////////////////////////////////////////////////////
class CPropSheetLite;
class CFrameWndLite;
class CAppLite;


//////////////////////////////////////////////////////////////////////////
// Globals
//
//////////////////////////////////////////////////////////////////////////
CAppLite*		GetAppLite();
void			SetAppLite(CAppLite* pCAppLite);

BOOL			DisplayContextMenu(HWND hWnd, UINT iID, REFPOINTS pts, HWND hWndParent, BOOL fRelCords = FALSE);
LRESULT			DisplayDialog(UINT uID, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM lParam);


/////////////////////////////////////////////////////////////////////
// CAppLite
//
/////////////////////////////////////////////////////////////////////
class CAppLite
{
public:
	CAppLite(UINT nAppID);
	virtual ~CAppLite();

	BOOL			AppInitialize(HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR* pszCmdLine, INT nCmdShow);
	virtual BOOL	InitInstance();
	virtual int		ExitInstance();
	virtual int		Run();

//protected:
	//data
	HINSTANCE		m_hInstance;
	HINSTANCE		m_hPrevInstance;
	CHAR*			m_pszCmdLine;
	INT				m_nCmdShow;

	UINT			m_nAppID;

	static	HWND			m_hWndModeless;
	static	CFrameWndLite*	m_pCMainWindow;
};


/////////////////////////////////////////////////////////////////////
// CWndLite
//
/////////////////////////////////////////////////////////////////////
class CWndLite
{
public:
	//constructors
	CWndLite(HWND hWndParent = NULL, UINT nID = 0);
	virtual ~CWndLite();

	//Window Proc
	static LRESULT WINAPI	WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual BOOL			HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT			UnhandledMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	//Inline helpers, (that deal with hWnds)
	HWND	GetDlgItem(INT iResourceID)					{ return ::GetDlgItem(m_hWnd, iResourceID);					}
	UINT	IsDlgButtonChecked(INT iResourceID)			{ return ::IsDlgButtonChecked(m_hWnd, iResourceID);			}
	BOOL	CheckDlgButton(INT iResourceID, UINT uCheck){ ASSERT(uCheck == BST_CHECKED || uCheck == BST_UNCHECKED || BST_INDETERMINATE); return ::CheckDlgButton(m_hWnd, iResourceID, uCheck);		}

	BOOL	IsVisible()									{ return ::IsWindowVisible(m_hWnd);							}
	HFONT	GetFont()									{ return (HFONT)::SendMessage(m_hWnd, WM_GETFONT, 0, 0);	}
	void	SetFont(HFONT hFont)						{ ::SendMessage(m_hWnd, WM_SETFONT, (WPARAM)hFont, 0);		}
	BOOL	EnableWindow(BOOL bEnable = TRUE)			{ return ::EnableWindow(m_hWnd, bEnable);					}
	HWND	SetFocus()									{ return ::SetFocus(m_hWnd);								}

	HWND	GetWnd()									{ /*ASSERT(m_hWnd);*/ return m_hWnd;						}
	BOOL	GetWindowPlacement()						{ memset(&m_wndPlacement, 0, sizeof(WINDOWPLACEMENT)); m_wndPlacement.length	= sizeof(WINDOWPLACEMENT); return ::GetWindowPlacement(m_hWnd, &m_wndPlacement); } 
	BOOL	SetWindowPlacement()						{ m_wndPlacement.length	= sizeof(WINDOWPLACEMENT); return ::SetWindowPlacement(m_hWnd, &m_wndPlacement); } 
	
	WCHAR*	GetWindowText()										{ return wGetWindowText(m_hWnd);										}
	LRESULT	GetWindowText(WCHAR* pwszBuffer, ULONG ulMaxSize)	{ return wSendMessage(m_hWnd, WM_GETTEXT, ulMaxSize, pwszBuffer);		}
	BOOL	SetWindowText(WCHAR* pwszString)					{ return (BOOL)wSendMessage(m_hWnd, WM_SETTEXT, 0,		 pwszString);		}

	LONG	ShowWindow(UINT nCmdShow)					{ return ::ShowWindow(m_hWnd, nCmdShow);										}
	LONG	UpdateWindow()								{ return ::UpdateWindow(m_hWnd);												}

//protected:
	virtual BOOL	PreCreateWindow(CREATESTRUCTW& cs);
	virtual	BOOL	Create(HWND hWndParent, WCHAR* pwszClassName,
								WCHAR* pwszWindowName, UINT uID,
								DWORD dwStyle = WS_TABSTOP | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_HSCROLL, 
								DWORD dwExStyle = WS_EX_CLIENTEDGE,
								int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, 
								int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT);

	virtual BOOL	CreateIndirect(HWND hWndParent, UINT nID);
	virtual BOOL	OnInitialUpdate();
	virtual	BOOL	DestroyWindow();
	virtual BOOL	SubClassWindow(WNDPROC pWndProc);

	virtual BOOL	OnMenuSelect(UINT uID);
	virtual BOOL	OnInitMenuPopup(HMENU hMenu, UINT uPos, BOOL fSysMenu);
	virtual BOOL	HandleMenuPos(HMENU hMenu, UINT uPos, DWORD* pdwFlags);

	virtual BOOL	OnCreate(CREATESTRUCT* pCREATESTRUCT);
	virtual BOOL	OnCommand(UINT iID, HWND hWndCtrl);
	virtual BOOL	OnCommandNotify(INT wNotifyCode, INT iID, HWND hWndCtrl);
	virtual BOOL	OnNotify(INT idCtrl, NMHDR* pNMHDR);
	virtual BOOL	OnUpdateCommand(HMENU hMenu, UINT nID, DWORD* pdwFlags);

	virtual BOOL	OnActivate(UINT fActive, UINT fMinimized, HWND hWndPrevious);
	virtual BOOL	OnClose();
	virtual BOOL	OnDestroy();
	virtual BOOL	OnTimer(WPARAM nIDEvent);
	virtual BOOL	OnDropFiles(HDROP hDrop);
	virtual BOOL	OnSysCommand(WPARAM nCmdType, REFPOINTS pts);

	virtual BOOL	OnSize(WPARAM nType, REFPOINTS pts);
	virtual BOOL	OnSizing(WPARAM nType, REFPOINTS pts);
	virtual BOOL	OnMove(REFPOINTS pts);
	virtual BOOL	OnMouseMove(WPARAM nHittest, REFPOINTS pts);
	
	virtual BOOL	OnDblclk(WPARAM fwKeys, REFPOINTS pts);
	virtual BOOL	OnLButtonDown(WPARAM fwKeys, REFPOINTS pts);
	virtual BOOL	OnLButtonUp(WPARAM fwKeys, REFPOINTS pts);
	virtual BOOL	OnRButtonDown(WPARAM fwKeys, REFPOINTS pts);
	virtual BOOL	OnRButtonUp(WPARAM fwKeys, REFPOINTS pts);
	virtual BOOL	OnSetCursor(HWND hWnd, INT nHittest, INT nMouseMsg);
	
	virtual BOOL	OnContextMenu(HWND hWnd, REFPOINTS pts);
	virtual BOOL	OnChar(TCHAR chCharCode, LPARAM lKeyData);
	virtual BOOL	OnKeyDown(WPARAM nVirtKey, LPARAM lKeyData);
	virtual BOOL	OnSysKeyDown(WPARAM nVirtKey, LPARAM lKeyData);
	virtual BOOL	OnVScroll(int nScrollCode, int nPos, HWND hWnd);
	virtual BOOL	OnHScroll(int nScrollCode, int nPos, HWND hWnd);
	virtual BOOL	OnNCMouseMove(WPARAM nHittest, REFPOINTS pts);
	virtual BOOL	OnNCButtonDown(WPARAM nHittest, REFPOINTS pts);
	virtual BOOL	OnSetFocus(HWND hWndPrevFocus);

	//Data
	HWND			m_hWnd;
	HWND			m_hWndParent;
	WINDOWPLACEMENT	m_wndPlacement;
	WCHAR*			m_pwszClassName;
	UINT			m_nID;

	//SubClass
	WNDPROC			m_pSubClassProc;
};



/////////////////////////////////////////////////////////////////////
// CMDIChildLite
//
/////////////////////////////////////////////////////////////////////
class CMDIChildLite : public CWndLite
{
public:
	//Constructors
	CMDIChildLite();
	virtual ~CMDIChildLite();

	//Window Proc
	static LRESULT WINAPI	MDIWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual BOOL			HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT			UnhandledMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	//Messages
	virtual BOOL			OnMDIActivate(BOOL bActivate, HWND hWndActivate, HWND hWndDeactivate);

	//Helpers
	virtual BOOL			AutoPosition(BOOL fDefaultPosition = TRUE);

//protected:
	virtual	BOOL			Create(HWND hWndParent, WCHAR* pwszClassName,
								WCHAR* pwszWindowName, UINT uID, HICON hIcon,
								DWORD dwStyle = WS_TABSTOP | WS_CHILD | WS_VISIBLE | WS_BORDER, 
								DWORD dwExStyle = WS_EX_CLIENTEDGE,
								int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, 
								int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT);

//protected:
	//data
};


/////////////////////////////////////////////////////////////////////
// CFrameWndLite
//
/////////////////////////////////////////////////////////////////////
class CFrameWndLite : public CWndLite
{
public:
	//constructors
	CFrameWndLite();
	virtual ~CFrameWndLite();

	virtual	BOOL	Create(HWND hWndParent, WCHAR* pwszClassName,
								WCHAR* pwszWindowName, UINT uID, HICON hIcon,
								DWORD dwStyle = WS_OVERLAPPEDWINDOW, 
								DWORD dwExStyle = WS_EX_APPWINDOW,
								int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, 
								int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT);
	
	virtual BOOL	PreTranslateMessage(MSG* pmsg);

	//Messages
	virtual BOOL	OnNotify(INT idCtrl, NMHDR* pNMHDR);
	virtual BOOL	OnClose();
	virtual BOOL	OnDestroy();

	//Messages
	virtual void	OnToolTip(INT idCtrl, NMHDR* pNMHDR);
};



/////////////////////////////////////////////////////////////////////
// CMDIFrameLite
//
/////////////////////////////////////////////////////////////////////
class CMDIFrameLite : public CFrameWndLite
{
public:
	//constructors
	CMDIFrameLite();
	virtual ~CMDIFrameLite();

	//Overloads
	virtual LRESULT	UnhandledMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual BOOL	PreTranslateMessage(MSG* pmsg);

	//Overloads
	virtual BOOL	OnCommand(UINT iID, HWND hWndCtrl);
	virtual BOOL	OnCommandNotify(INT wNotifyCode, INT iID, HWND hWndCtrl);
	virtual BOOL	OnNotify(INT idCtrl, NMHDR* pNMHDR);
	virtual BOOL	OnUpdateCommand(HMENU hMenu, UINT nID, DWORD* pdwFlags);

	//Messages
	virtual BOOL	OnCreate(CREATESTRUCT* pCREATESTRUCT);
	virtual BOOL	OnCreateClient(CREATESTRUCT* pCREATESTRUCT);
	virtual BOOL	OnDestroy();

	//Helpers
	virtual void	OnAutoPosition();

	//Helpers
	virtual void	MDIActivate(HWND hWnd)	{ SendMessage(m_hWndMDIClient, WM_MDIACTIVATE, (WPARAM)hWnd, 0);	} 
	virtual void	MDIDestroy(HWND hWnd)	{ SendMessage(m_hWndMDIClient, WM_MDIDESTROY, (WPARAM)hWnd, 0);		}

	//Helpers
	virtual CMDIChildLite* GetActiveWindow(WCHAR* pwszClassName = NULL);
	virtual CMDIChildLite* FindWindow(WCHAR* pwszClassName = NULL);

//protected:
	//Data
	HWND	m_hWndMDIClient;
};


/////////////////////////////////////////////////////////////////////
// CDialogLite
//
/////////////////////////////////////////////////////////////////////
class CDialogLite : public CWndLite
{
public:
	//constructors
	CDialogLite(UINT uIDD);
	virtual ~CDialogLite();

	//members
	virtual LRESULT			DoModal(HWND hWndParent);		//Modal
	virtual HWND			CreateDlg(HWND hWndParent);		//Modeless (non-Modal)
	virtual void			EndDialog(int nResult);

	//Dialog Proc
	static	INT_PTR WINAPI	DlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual BOOL			HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//protected:
	virtual BOOL			OnInitDialog();
	virtual BOOL			OnActivate(UINT fActive, UINT fMinimized, HWND hWndPrevious);

	virtual BOOL			OnOK();
	virtual BOOL			OnCancel();
	
	//Data
	UINT			m_uIDD;
	BOOL			m_fModal;
};



/////////////////////////////////////////////////////////////////////
// CSplitterLite
//
/////////////////////////////////////////////////////////////////////
class CSplitterLite	: public CWndLite
{
public:
	//constructors
	CSplitterLite(HWND hWndParent = NULL, UINT nID = 0);

	//Helpers
	virtual BOOL	SetSplitter(CSplitterLite* pCWndTop, CSplitterLite* pCWndBottom = NULL, CSplitterLite* pCWndLeft = NULL, CSplitterLite* pCWndRight = NULL);
	virtual BOOL	StartTracking(REFPOINTS ptsScreen, REFRECT rectLeft, REFRECT rectRight, BOOL fVertical, POINT* pPoint);
	virtual BOOL	DrawSplitter(HDC hDC, BOOL fVertical, REFRECT rectLeft, REFRECT rectRight, REFPOINTS ptsClient);
	
	//Messages
	virtual BOOL	OnNCMouseMove(WPARAM nHittest, REFPOINTS pts);
	virtual BOOL	OnNCButtonDown(WPARAM nHittest, REFPOINTS pts);
	virtual BOOL	OnBorder(REFPOINTS pts, INT iBorder);

//protected:
	//Data
	CSplitterLite*	m_pCWndTop;
	CSplitterLite*	m_pCWndBottom;
	CSplitterLite*	m_pCWndLeft;
	CSplitterLite*	m_pCWndRight;

	HCURSOR			m_hCursorOld;
	HCURSOR			m_hCursorTop;
	HCURSOR			m_hCursorRight;

	INT				m_iBorderCX;
	INT				m_iBorderCY;
};


/////////////////////////////////////////////////////////////////////
// CEditBoxLite
//
/////////////////////////////////////////////////////////////////////
class CEditBoxLite : public CSplitterLite
{
public:
	//constructors
	CEditBoxLite(HWND hWndParent = NULL, UINT nID = 0);
	virtual ~CEditBoxLite();

	//Messages
	virtual BOOL	OnCreate(CREATESTRUCT* pCREATESTRUCT);

	//Interface
	virtual void	SetSel(INDEX iMin, INDEX iMax)							{ SendMessage(m_hWnd, EM_SETSEL, (WPARAM)iMin, (LPARAM)iMax);	}
	virtual BOOL	GetSel(INDEX* piMin, INDEX* piMax)						{ CHARRANGE cr; SendMessage(m_hWnd, EM_GETSEL, (WPARAM)&cr.cpMin, (LPARAM)&cr.cpMax); if(piMin) *piMin = cr.cpMin;  if(piMax) *piMax = cr.cpMax; return cr.cpMin != cr.cpMax;	}

	//Inline helpers, (that deal with hWnds)
	BOOL			SetReadOnly(BOOL bReadOnly)								{ return (BOOL)SendMessage(m_hWnd, EM_SETREADONLY, bReadOnly, 0L);								}
	INDEX			LineIndex(INDEX nLine) 									{ return (INDEX)SendMessage(m_hWnd, EM_LINEINDEX, nLine, 0);									}
	INDEX			LineLength(INDEX nStartChar)							{ return (INDEX)SendMessage(m_hWnd, EM_LINELENGTH, nStartChar, 0);								}
	void			LineScroll(INDEX nLines, INDEX nChars = 0)				{ SendMessage(m_hWnd, EM_LINESCROLL, nChars, nLines);											}
	LRESULT			SetOptions(UINT dwOptions, UINT fOperation = ECOOP_OR)	{ return SendMessage(m_hWnd, EM_SETOPTIONS, fOperation, dwOptions);								}
	
	BOOL			CanPaste()												{ return (BOOL)SendMessage(m_hWnd, EM_CANPASTE, 0, 0);											}
	void			Cut()													{ SendMessage(m_hWnd, WM_CUT, 0, 0);															}
	void			Copy()													{ SendMessage(m_hWnd, WM_COPY, 0, 0);															}	
	void			Paste()													{ SendMessage(m_hWnd, WM_PASTE, 0, 0);															}	
	BOOL			ScrollCaret()											{ return (BOOL)SendMessage(m_hWnd, EM_SCROLLCARET, 0, 0);										}

	virtual void	ReplaceSel(WCHAR* pwszString, BOOL bCanUndo)			{ wSendMessage(m_hWnd, EM_REPLACESEL, (WPARAM) bCanUndo, pwszString);							}
	virtual void	ReplaceAll(WCHAR* pwszString, BOOL bReplaceAll = FALSE, BOOL fHighlight = FALSE);

	INDEX			GetLineCount()											{ return (INDEX)SendMessage(m_hWnd, EM_GETLINECOUNT, 0, 0);										}
	INDEX			GetLine(INDEX iLine, CHAR* pszBuffer, ULONG ulMaxSize);
	INDEX			GetTextRange(CHARRANGE& cr, WCHAR* pwszBuffer);
	INDEX			GetTextRange(CHARRANGE& cr, CHAR* pszBuffer);

	//Helpers
	BOOL			Save(WCHAR* pwszFileName);

//protected:
	//data
};


/////////////////////////////////////////////////////////////////////
// CRichEditLite
//
/////////////////////////////////////////////////////////////////////
class CRichEditLite : public CEditBoxLite
{
public:
	//constructors
	CRichEditLite(HWND hWndParent = NULL, UINT nID = 0);
	virtual ~CRichEditLite();

	//Messages
	virtual BOOL	OnCreate(CREATESTRUCT* pCREATESTRUCT);
	virtual BOOL	OnNotify(INT idCtrl, NMHDR* pNMHDR);
	virtual BOOL	SetWordWrap(BOOL fWordWrap);

	//Messages
	virtual BOOL	OnLink(INT idCtrl, ENLINK* pEnLink);

	//Interface
	//NOTE: We overload Get and Set since for RichEdit controls these have different messages for > 64k
	virtual void	SetSel(INDEX iMin, INDEX iMax)							{ CHARRANGE cr = { (LONG)iMin, (LONG)iMax }; SendMessage(m_hWnd, EM_EXSETSEL, 0, (LPARAM)&cr);	}
	virtual BOOL	GetSel(INDEX* piMin, INDEX* piMax)						{ CHARRANGE cr;  SendMessage(m_hWnd, EM_EXGETSEL, 0, (LPARAM)&cr); if(piMin) *piMin = cr.cpMin;  if(piMax) *piMax = cr.cpMax; return cr.cpMin != cr.cpMax;	}

	//Inline helpers, (that deal with hWnds)
	INDEX			LineFromChar(INDEX nIndex)								{ return (INDEX)SendMessage(m_hWnd, EM_EXLINEFROMCHAR, 0, nIndex);			}
	
	BOOL			SetEffects(DWORD dwMask, DWORD	dwEffects, COLORREF	crTextColor);
	BOOL			SetCharFormat(DWORD dwMask, CHARFORMATW& charFormatW);

	virtual void	ReplaceSel(WCHAR* pwszString, BOOL bCanUndo)			{ wSendMessage(m_hWnd, EM_REPLACESEL, (WPARAM) bCanUndo, pwszString);		}
	virtual void	ReplaceSel(WCHAR* pwszString, BOOL bCanUndo, DWORD dwMask, DWORD dwColor);

	//Helpers
	LRESULT			SetDefaultFont();
	WCHAR*			GetSelectedText(BOOL fEntireLine = TRUE);


//protected:
	//data
};



/////////////////////////////////////////////////////////////////////
// CScrollBarLite
//
/////////////////////////////////////////////////////////////////////
class CScrollBarLite : public CSplitterLite
{
public:
	//constructors
	CScrollBarLite();
	virtual ~CScrollBarLite();

	//Messages

	//Inline helpers, (that deal with hWnds)
	virtual INT		SetScrollPos( int nPos, BOOL bRedraw = TRUE )				{ return ::SetScrollPos(m_hWnd, SB_CTL, nPos, bRedraw);			}
	virtual INT		GetScrollPos()												{ return ::GetScrollPos(m_hWnd, SB_CTL);						}

	virtual BOOL	SetScrollRange( int nMin, int nMax, BOOL bRedraw = TRUE )	{ return ::SetScrollRange(m_hWnd, SB_CTL, nMin, nMax, bRedraw);	}
	virtual BOOL	GetScrollRange( int* pnMin, int* pnMax )					{ return ::GetScrollRange(m_hWnd, SB_CTL, pnMin, pnMax);		}

	//Helpers
	virtual INT		SetScroll( int nPos, BOOL bRedraw = TRUE );
	virtual INT		SetScrollInfo(INT iPos, INT iRangeSize, INT iPageSize, BOOL fRedraw = TRUE);
	virtual BOOL	GetScrollInfo(INT* piPos, INT* piRangeSize, INT* piPageSize);

//protected:
	//data
};


/////////////////////////////////////////////////////////////////////
// CListBoxLite
//
/////////////////////////////////////////////////////////////////////
class CListBoxLite : public CWndLite
{
public:
	//constructors
	CListBoxLite(HWND hWndParent = NULL, UINT nID = 0);
	virtual ~CListBoxLite();

	//Messages
	virtual BOOL	OnCommandNotify(INT wNotifyCode, INT iID, HWND hWndCtrl);

	//Overloads
	virtual BOOL	OnDblClk(INT iID, HWND hWndCtrl);

	//Inline helpers, (that deal with hWnds)
	virtual INDEX	GetCurSel() const							{ return (INDEX)::SendMessage(m_hWnd,	LB_GETCURSEL, 0, 0);						}
	virtual INDEX	AddString(WCHAR* pwszString)				{ return (INDEX)wSendMessage(m_hWnd,	LB_ADDSTRING,	0, pwszString);				}
	virtual INDEX	GetText(INDEX nIndex, WCHAR* pwszBuffer)	{ return (INDEX)wSendMessage(m_hWnd,	LB_GETTEXT, nIndex, pwszBuffer);			}
	
	//Helpers
	
//protected:
	//data
};


/////////////////////////////////////////////////////////////////////
// CListViewLite
//
/////////////////////////////////////////////////////////////////////
class CListViewLite : public CSplitterLite
{
public:
	//constructors
	CListViewLite(HWND hWndParent = NULL, UINT nID = 0);
	virtual ~CListViewLite();

	//Messages
	virtual BOOL	OnCreate(CREATESTRUCT* pCREATESTRUCT);
	virtual BOOL	OnNotify(INT idCtrl, NMHDR* pNMHDR);

	virtual BOOL	OnColumnClick(INT idCtrl, NMLISTVIEW* pNMListView);
	virtual BOOL	OnItemActivate(INT idCtrl, NMLISTVIEW* pNMListView);
	virtual BOOL	OnItemChanged(INT idCtrl, NMLISTVIEW* pNMListView);

	//Inline helpers, (that deal with hWnds)
	BOOL			DeleteColumn(INDEX nCol)								{ return (BOOL)SendMessage(m_hWnd, LVM_DELETECOLUMN, nCol, 0);								}
	BOOL			DeleteAllItems()										{ return (BOOL)SendMessage(m_hWnd, LVM_DELETEALLITEMS, 0, 0L);								}
	INDEX			GetNextItem(INDEX iItem, INT nFlags)					{ return (INDEX)SendMessage(m_hWnd, LVM_GETNEXTITEM, iItem, MAKELPARAM(nFlags, 0));			}
	INDEX			GetColumnWidth(INDEX nCol)								{ return (INDEX)SendMessage(m_hWnd, LVM_GETCOLUMNWIDTH, nCol, 0);							}
	BOOL			SetColumnWidth(INDEX nCol, INT cx)						{ return (BOOL)SendMessage(m_hWnd, LVM_SETCOLUMNWIDTH, nCol, MAKELPARAM(cx, 0));			}
	UINT			GetItemState(INDEX iItem, UINT nMask)					{ return (UINT)SendMessage(m_hWnd, LVM_GETITEMSTATE, iItem, nMask);							}
	BOOL			EnsureVisible(INDEX iItem, BOOL fPartialOK = FALSE)		{ return (BOOL)SendMessage(m_hWnd, LVM_ENSUREVISIBLE, iItem, MAKELPARAM(fPartialOK, 0));	}
	INDEX			GetItemCount()											{ return (INDEX)SendMessage(m_hWnd, LVM_GETITEMCOUNT, 0, 0);								}
	INDEX			GetCountPerPage()										{ return (INDEX)SendMessage(m_hWnd, LVM_GETCOUNTPERPAGE, 0, 0);								}

	//Helpers
	LPARAM			GetItemParam(INDEX iItem);
	INDEX			GetItemText(INDEX iItem, INDEX iSubItem, WCHAR* wszName, ULONG ulMaxChars);
	INDEX			InsertColumn(INDEX iColumn, WCHAR* wszName, INT iImage = IMAGE_NONE);
	BOOL			SetColumn(INDEX iColumn, WCHAR* wszName, INT iImage = IMAGE_NONE);

	INDEX			InsertItem(INDEX iItem, INDEX iSubItem, WCHAR* wszName, LPARAM lParam = PARAM_NONE, INT iImage = IMAGE_NONE, UINT iState = IMAGE_NONE, UINT iStateMask = IMAGE_NONE);
	BOOL			SetItemText(INDEX iItem, INDEX iSubItem, WCHAR* pwszName);
	BOOL			SetItemState(INDEX iItem, INDEX iSubItem, UINT iState, UINT iStateMask);
	INDEX			HitTest(REFPOINTS pts, UINT* pFlags = NULL);
	
	INT				GetItemImage(INDEX iItem, INDEX iSubItem = 0);
	BOOL			SetItemImage(INDEX iItem, INDEX iSubItem, INT iImage);
	BOOL			SetItemParam(INDEX iItem, INDEX iSubItem, LPARAM lParam);
};



/////////////////////////////////////////////////////////////////////
// CTreeViewLite
//
/////////////////////////////////////////////////////////////////////
class CTreeViewLite : public CSplitterLite
{
public:
	//constructors
	CTreeViewLite(HWND hWndParent = NULL, UINT nID = 0);
	virtual ~CTreeViewLite();

	//Messages
	virtual BOOL	OnCreate(CREATESTRUCT* pCREATESTRUCT);
	virtual BOOL	OnNotify(INT idCtrl, NMHDR* pNMHDR);

	virtual BOOL	OnSelChanged(INT idCtrl, NMTREEVIEW* pNMTreeView);
	virtual BOOL	OnBeginLabelEdit(INT idCtrl, NMTVDISPINFO* ptvdi);
	virtual BOOL	OnEndLabelEdit(INT idCtrl, NMTVDISPINFO* ptvdi);
	virtual BOOL	OnBeginDrag(INT idCtrl, NMTREEVIEW* pNMTreeView);
	virtual BOOL	OnMouseMove(WPARAM nHittest, REFPOINTS pts);
	virtual BOOL	OnLButtonUp(WPARAM fwKeys, REFPOINTS pts);

	//Inline helpers, (that deal with hWnds)
	BOOL			SelectItem(HTREEITEM hItem)								{ ASSERT(IsWindow(m_hWnd));		return (BOOL)SendMessage(m_hWnd, TVM_SELECTITEM, TVGN_CARET, (LPARAM)hItem);		}
	HTREEITEM		GetSelectedItem()										{ ASSERT(IsWindow(m_hWnd));		return (HTREEITEM)SendMessage(m_hWnd, TVM_GETNEXTITEM, TVGN_CARET, 0);				}
	BOOL			DeleteAllItems()										{ ASSERT(IsWindow(m_hWnd));		return (BOOL)SendMessage(m_hWnd, TVM_DELETEITEM, 0, (LPARAM)TVI_ROOT);				}
	HTREEITEM		GetNextItem(HTREEITEM hItem, UINT nCode = TVGN_NEXT)	{ ASSERT(IsWindow(m_hWnd));		return (HTREEITEM)SendMessage(m_hWnd, TVM_GETNEXTITEM, nCode, (LPARAM)hItem);		}
	HTREEITEM		GetChildItem(HTREEITEM hItem)							{ ASSERT(IsWindow(m_hWnd));		return (HTREEITEM)SendMessage(m_hWnd, TVM_GETNEXTITEM, TVGN_CHILD, (LPARAM)hItem);	}
	HTREEITEM		GetParentItem(HTREEITEM hItem) 							{ ASSERT(IsWindow(m_hWnd));		return (HTREEITEM)SendMessage(m_hWnd, TVM_GETNEXTITEM, TVGN_PARENT, (LPARAM)hItem);	}
	BOOL			DeleteItem(HTREEITEM hItem)								{ ASSERT(IsWindow(m_hWnd));		return (BOOL)SendMessage(m_hWnd, TVM_DELETEITEM, 0, (LPARAM)hItem);					}
	BOOL			EnsureVisible(HTREEITEM hItem)							{ ASSERT(IsWindow(m_hWnd));		return (BOOL)SendMessage(m_hWnd, TVM_ENSUREVISIBLE, 0, (LPARAM)hItem);				}
	BOOL			Expand(HTREEITEM hItem, UINT flag = TVE_EXPAND)			{ ASSERT(IsWindow(m_hWnd));		return (BOOL)SendMessage(m_hWnd, TVM_EXPAND, flag, (LPARAM)hItem);					}

	//Helpers
	LPARAM			GetItemParam(HTREEITEM hItem);
	HTREEITEM		HitTest(REFPOINTS pts, UINT* pFlags = NULL);
	BOOL			SetItemState(HTREEITEM hItem, UINT iState, UINT iStateMask);
	BOOL			SetItemImage(HTREEITEM hItem, INT iImage, INT iSelectedImage);
	BOOL			SetItemParam(HTREEITEM hItem, LPARAM lParam);

	HTREEITEM		InsertItem(HTREEITEM hParent, HTREEITEM hInsAfter, WCHAR* wszName, LPARAM lParam = PARAM_NONE, INT iImage = IMAGE_NONE, INT iSelectedImage = IMAGE_NONE, UINT iState = IMAGE_NONE, UINT iStateMask = IMAGE_NONE);
	BOOL			SetItemText(HTREEITEM hItem, WCHAR* pwszText);

protected:
	//Data
	HTREEITEM		m_hDraggingItem;
};



/////////////////////////////////////////////////////////////////////
// CComboBoxLite
//
/////////////////////////////////////////////////////////////////////
class CComboBoxLite : public CWndLite
{
public:
	//constructors
	CComboBoxLite(HWND hWndParent = NULL, UINT nID = 0);
	virtual ~CComboBoxLite();

	//Messages
	virtual BOOL		OnCommandNotify(INT wNotifyCode, INT iID, HWND hWndCtrl);

	//Overloads
	virtual BOOL		OnSelChange(INT iID, HWND hWndCtrl);
	virtual BOOL		OnDropDown(INT iID, HWND hWndCtrl);

	//Inline helpers, (that deal with hWnds)
	virtual INDEX		GetCount()										{ return (INDEX)::SendMessage(m_hWnd,	CB_GETCOUNT, 0, 0);					}
	virtual INDEX		GetCurSel() const								{ return (INDEX)::SendMessage(m_hWnd,	CB_GETCURSEL, 0, 0);				}
	virtual INDEX		SetCurSel(WPARAM nSelect)						{ return (INDEX)::SendMessage(m_hWnd,	CB_SETCURSEL, nSelect, 0);			}
	
	virtual INDEX		AddString(WCHAR* pwszString)					{ return (INDEX)::wSendMessage(m_hWnd,	CB_ADDSTRING,	0, pwszString);		}
	virtual INDEX		DeleteString(INDEX nIndex)						{ return (INDEX)::SendMessage(m_hWnd,	CB_DELETESTRING, nIndex, 0);		}
	virtual BOOL		SetItemData(INDEX nIndex, LPARAM lParam)		{ return ::SendMessage(m_hWnd,	CB_SETITEMDATA, nIndex, lParam) != CB_ERR;	}
	virtual void		ResetContent()									{ ::SendMessage(m_hWnd,	CB_RESETCONTENT, 0, 0);								}		

	virtual LPARAM		GetItemParam(INDEX nIndex) const					{ return ::SendMessage(m_hWnd,	CB_GETITEMDATA, nIndex, 0);					}
	virtual LRESULT		GetTextLength(INDEX nIndex)						{ return ::SendMessage(m_hWnd,	CB_GETLBTEXTLEN, nIndex, 0);				}
	virtual INDEX		GetText(INDEX nIndex, WCHAR* pwszBuffer)		{ return (INDEX)::wSendMessage(m_hWnd,	CB_GETLBTEXT, nIndex, pwszBuffer);	}
	virtual INDEX		FindString(WCHAR* pwszString, INDEX nStartIndex = -1)				{ return (INDEX)wSendMessage(m_hWnd,	CB_FINDSTRING,		nStartIndex, pwszString);		}
	virtual INDEX		FindStringExact(WCHAR* pwszString, INDEX nStartIndex = -1)			{ return (INDEX)wSendMessage(m_hWnd,	CB_FINDSTRINGEXACT,	nStartIndex, pwszString);		}
	
	//Helpers
	virtual INDEX		GetSelText(WCHAR* pwszBuffer, ULONG ulMaxSize);
	virtual INDEX		SetSelText(WCHAR* pwszBuffer, BOOL fAddItem = FALSE);
	virtual INDEX		SetSelValue(LPARAM lParam);
	virtual INDEX		AddString(WCHAR* pwszString, LPARAM lParam);
	
	//Helpers
	virtual INDEX		SaveSelection()									{ return m_iSavedSel = GetCurSel();											}
	virtual	INDEX		RestoreSelection()								{ return SetCurSel(m_iSavedSel);											}
	virtual BOOL		Populate(ULONG cItems, const WIDENAMEMAP* rgItems);


//protected:
	//data
	INDEX		m_iSavedSel;
};


/////////////////////////////////////////////////////////////////////
// CComboBoxEx
//
/////////////////////////////////////////////////////////////////////
class CComboBoxEx : public CComboBoxLite
{
public:
	//constructors
	CComboBoxEx(HWND hWndParent = NULL, UINT nID = 0);
	virtual ~CComboBoxEx();

	//Overrides
	virtual BOOL		OnInitialUpdate();
	
	//Messages
	INDEX				InsertItem(INDEX iItem, WCHAR* pwszName, LPARAM lParam = PARAM_NONE, INT iIndent = PARAM_NONE, INT iImage = IMAGE_NONE, UINT iSelectedImage = IMAGE_NONE);

	//Inline helpers, (that deal with hWnds)
	//NOTE: AddString is not processed by ComboBoxEx so we have to fabricate the functionality
	virtual INDEX		AddString(WCHAR* pwszString)										{ return InsertItem(-1/*iItem*/, pwszString);								}
	virtual INDEX		AddString(WCHAR* pwszString, LPARAM lParam)							{ return InsertItem(-1/*iItem*/, pwszString, lParam);						}

	virtual BOOL		SetUnicodeFormat(BOOL fUnicode = TRUE)								{ return (BOOL)::SendMessage(m_hWnd, CBEM_SETUNICODEFORMAT, fUnicode, 0);	}
	
	//NOTE: FindString is not processed by ComboBoxEx, but FindStringExact is...
	virtual INDEX		FindString(WCHAR* pwszString, INDEX nStartIndex = -1)				{ ASSERT(!L"FindString is not processed by ComboBoxEx, change code to use FindStringExact.");   return FindStringExact(pwszString, nStartIndex);	}

	//protected:
	//data
};


/////////////////////////////////////////////////////////////////////
// CToolBarLite
//
/////////////////////////////////////////////////////////////////////
class CToolBarLite : public CWndLite
{
public:
	//constructors
	CToolBarLite();
	virtual ~CToolBarLite();

	virtual BOOL Create(HWND hWndParent, UINT nID,  UINT nBitmapID, UINT cButtons, TBBUTTON* rgButtons, DWORD dwStyle = WS_CHILD | WS_VISIBLE | TBSTYLE_TOOLTIPS /*| TBSTYLE_WRAPABLE | TBSTYLE_ALTDRAG | CCS_ADJUSTABLE*/);

	//Helpers
	virtual BOOL EnableButton(UINT nID, BOOL fEnable)			{ return (BOOL)SendMessage(m_hWnd, TB_ENABLEBUTTON, nID, fEnable);				}
};


/////////////////////////////////////////////////////////////////////
// CStatusBarLite
//
/////////////////////////////////////////////////////////////////////
class CStatusBarLite : public CWndLite
{
public:
	//constructors
	CStatusBarLite();
	virtual ~CStatusBarLite();

	//Creation
	virtual BOOL Create(HWND hWndParent, UINT nID,  WCHAR* pwszText = L"", DWORD dwStyle = WS_CHILD | WS_VISIBLE);

	//Helpers
	virtual BOOL SetText(WCHAR* pwszText, int nPane, int nType)	{ return (BOOL)wSendMessage(m_hWnd, SB_SETTEXTW, (nPane|nType), pwszText);		}
	virtual BOOL SetParts(int nParts, int* pWidths)				{ return (BOOL)SendMessage(m_hWnd, SB_SETPARTS, nParts, (LPARAM)pWidths);		}
};


/////////////////////////////////////////////////////////////////////
// CPropPageLite
//
/////////////////////////////////////////////////////////////////////
class CPropPageLite : public CDialogLite
{
public:
	//constructors
	CPropPageLite(UINT uIDD, TCHAR* ptszTitle = NULL);
	virtual ~CPropPageLite();

	//Dialog Proc
	static INT_PTR WINAPI	PropPageProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual BOOL			HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	//Interface
	virtual void				SetParent(CPropSheetLite* pCPropSheetLite);
	virtual CPropSheetLite*		GetParent()	{ return m_pCPropSheet; }

//protected:
	virtual BOOL	OnSetActive();
	virtual BOOL	OnKillActive();

	virtual BOOL	OnOK();
	virtual BOOL	OnApply();

	virtual BOOL	OnCancel();
	virtual BOOL	OnReset();
	
	//Data
	PROPSHEETPAGE   m_psPage;

	//Parent Property Sheet
	CPropSheetLite*	m_pCPropSheet;
};


/////////////////////////////////////////////////////////////////////
// CPropSheetLite
//
/////////////////////////////////////////////////////////////////////
class CPropSheetLite : public CWndLite
{
public:
	//constructors
	CPropSheetLite(TCHAR* ptszTitle = NULL, HICON hIcon = NULL);
	virtual ~CPropSheetLite();

//protected:
	virtual void		AddPage(CPropPageLite* pCPropPageLite);
	virtual LRESULT		DoModal(HWND hWndParent, INT nStartPage = 0);

	//Data
	PROPSHEETHEADER m_psHeader;
};



//////////////////////////////////////////////////////////////////////////
// CCmdLineLite
//
//////////////////////////////////////////////////////////////////////////
class CCmdLineLite
{
protected:

	// Attributes
public:
	CCmdLineLite();
	virtual ~CCmdLineLite();

// Operations
	virtual void ResetParser();

//protected:
	virtual void ParseParam(WCHAR* pwszParam, BOOL bFlag, BOOL bLast );
	virtual BOOL ParseCommandLine();
	virtual BOOL ParseFile(WCHAR* pwszFileName);

	WCHAR	m_wszLastCmd[MAX_QUERY_LEN];
};


/////////////////////////////////////////////////////////////////////
// CWaitCursor
//
/////////////////////////////////////////////////////////////////////
class CWaitCursor
{
public:
	//Constructors
	CWaitCursor();
	virtual ~CWaitCursor();

	//Helpers
	void WaitCursor();
	void RestoreCursor();

protected:
	//Data
	HCURSOR m_hPrevCursor;
};


/////////////////////////////////////////////////////////////////////
// CFileLite
//
/////////////////////////////////////////////////////////////////////
class CFileLite
{
public:
	//constructor
	CFileLite();
	virtual ~CFileLite();

	//helpers
	virtual HRESULT Open(WCHAR* pwszFileName, DWORD dwDesiredAccess, DWORD dwShareMode, DWORD dwCreationDisposition, BOOL fDisplayDialog = FALSE);
	virtual HRESULT Read(ULONG cbBytes, WCHAR* pwszText, ULONG* pcbRead = NULL);
	virtual HRESULT Read(ULONG cbBytes, CHAR* pszText, ULONG* pcbRead = NULL);
	
	virtual HRESULT Write(WCHAR* pwszText, ULONG* pcbWritten = NULL);
	virtual HRESULT Write(CHAR* pszText, ULONG* pcbWritten = NULL);
	virtual HRESULT WriteQuoted(WCHAR* pwszText);
	virtual HRESULT WriteFmt(WCHAR* pwszFmt, ...);

	virtual HRESULT Flush();
	virtual HRESULT Close();
	virtual DWORD	Seek(DWORD dwOffset, DWORD dwOrigin);

	//Interface
	virtual BOOL	IsOpen()	{ return m_hFile != NULL;	}
	virtual BOOL    IsEOF()		{ return m_bEOF;			}

private:
	//Data
	HANDLE	m_hFile;
	BOOL	m_bEOF;
};


/////////////////////////////////////////////////////////////////////
// CDropObject
//
/////////////////////////////////////////////////////////////////////
class CDropObject : public IDataObject
{
public:
	//constructor
	CDropObject();
	virtual ~CDropObject();

	//IUnknown
	STDMETHODIMP			QueryInterface(REFIID riid, void** ppvObject);
    STDMETHODIMP_(ULONG)	AddRef();
    STDMETHODIMP_(ULONG)	Release();

	//Interface
    STDMETHODIMP			GetData(FORMATETC* pformatetcIn, STGMEDIUM* pmedium);
    STDMETHODIMP			GetDataHere(FORMATETC* pformatetc, STGMEDIUM* pmedium);
    STDMETHODIMP			QueryGetData(FORMATETC* pformatetc);
    STDMETHODIMP			GetCanonicalFormatEtc(FORMATETC* pformatectIn, FORMATETC* pformatetcOut);
    STDMETHODIMP			SetData(FORMATETC* pformatetc, STGMEDIUM* pmedium, BOOL fRelease);
    STDMETHODIMP			EnumFormatEtc(DWORD dwDirection, IEnumFORMATETC** ppenumFormatEtc);
    STDMETHODIMP			DAdvise(FORMATETC* pformatetc, DWORD advf, IAdviseSink* pAdvSink, DWORD* pdwConnection);
    STDMETHODIMP			DUnadvise(DWORD dwConnection);
    STDMETHODIMP			EnumDAdvise(IEnumSTATDATA** ppenumAdvise);

private:
	//Data

	//IUnknown
	ULONG					m_cRef;
};


/////////////////////////////////////////////////////////////////////
// CDropSource
//
/////////////////////////////////////////////////////////////////////
class CDropSource : public IDropSource
{
public:
	//constructor
	CDropSource();
	virtual ~CDropSource();

	//IUnknown
	STDMETHODIMP			QueryInterface(REFIID riid, void** ppvObject);
    STDMETHODIMP_(ULONG)	AddRef();
    STDMETHODIMP_(ULONG)	Release();

	//Interface
    STDMETHODIMP			QueryContinueDrag(BOOL fEscapePressed, DWORD grfKeyState);
    STDMETHODIMP			GiveFeedback(DWORD dwEffect);

private:
	//Data

	//IUnknown
	ULONG					m_cRef;
};


/////////////////////////////////////////////////////////////////////
// CDropTarget
//
/////////////////////////////////////////////////////////////////////
class CDropTarget : public IDropTarget
{
public:
	//constructor
	CDropTarget();
	virtual ~CDropTarget();

	//IUnknown
	STDMETHODIMP			QueryInterface(REFIID riid, void** ppvObject);
    STDMETHODIMP_(ULONG)	AddRef();
    STDMETHODIMP_(ULONG)	Release();

	//Interface
    STDMETHODIMP			DragEnter(IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect);
    STDMETHODIMP			DragOver(DWORD grfKeyState, POINTL pt, DWORD* pdwEffect);
    STDMETHODIMP			DragLeave();
    STDMETHODIMP			Drop(IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect);

private:
	//Data

	//IUnknown
	ULONG					m_cRef;
};


/////////////////////////////////////////////////////////////////////
// ListView Helpers
//
/////////////////////////////////////////////////////////////////////
INDEX		LV_InsertColumn(HWND hWnd, INDEX iColumn, WCHAR* wszName, INT iImage = IMAGE_NONE);
INDEX		LV_InsertItem(HWND hWnd, INDEX iItem, INDEX iSubItem, WCHAR* wszName, LPARAM lParam = PARAM_NONE, INT iImage = IMAGE_NONE, UINT iState = IMAGE_NONE, UINT iStateMask = IMAGE_NONE);

BOOL		LV_SetItemState(HWND hWnd, INDEX iItem, INDEX iSubItem, UINT iState, UINT iStateMask);
BOOL		LV_SetItemText(HWND hWnd, INDEX iItem, INDEX iSubItem, WCHAR* pwszName);
BOOL		LV_SetItemImage(HWND hWnd, INDEX iItem, INDEX iSubItem, INT iImage);
BOOL		LV_SetItemParam(HWND hWnd, INDEX iItem, INDEX iSubItem, LPARAM lParam);

INDEX		LV_GetItemText(HWND hWnd, INDEX iItem, INDEX iSubItem, WCHAR* pwszName, ULONG ulMaxSize);
UINT		LV_GetItemState(HWND hWnd, INDEX iItem, UINT iMask = 0);
INT			LV_GetItemImage(HWND hWnd, INDEX iItem, INDEX iSubItem);
LPARAM		LV_GetItemParam(HWND hWnd, INDEX iItem, INDEX iSubItem);

INDEX		LV_FindItem(HWND hWnd, LPARAM lParam, INDEX iStart = -1);
														 
LRESULT		LV_GetSelItems(HWND hWnd, INDEX* pcItems = NULL, INDEX** prgSelItems = NULL, LPARAM** prgSelParams = NULL);
LRESULT		LV_GetAllItems(HWND hWnd, INDEX* pcItems = NULL, INDEX** prgItems = NULL, LPARAM** prgParams = NULL);


/////////////////////////////////////////////////////////////////////
// TreeView Helpers
//
/////////////////////////////////////////////////////////////////////
HTREEITEM	TV_InsertItem(HWND hWnd, HTREEITEM hParent, HTREEITEM hInsAfter, WCHAR* wszName, LPARAM lParam = 0, INT iImage = 0, INT iSelectedImage = 0, UINT iState = 0, UINT iStateMask = 0);

BOOL		TV_GetItemText(HWND hWnd, HTREEITEM hItem, WCHAR* pwszBuffer, LONG ulMaxSize);
LPARAM		TV_GetItemParam(HWND hWnd, HTREEITEM hItem);
BOOL		TV_SetItemState(HWND hWnd, HTREEITEM hItem, UINT iState, UINT iStateMask);

HTREEITEM	TV_FindItem(HWND hWnd, HTREEITEM hParent, WCHAR* wszName);



#endif //__CDIALOGLITE_H__
