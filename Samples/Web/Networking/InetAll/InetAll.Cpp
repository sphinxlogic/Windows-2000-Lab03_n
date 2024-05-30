//--------------------------------------------------------------------------
// (C) Copyright 1999 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS-IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// --- THIS CODE IS NOT SUPPORTED BY MICROSOFT ---
///////////////////////////////////////////////////////
/*
 *  inetcpp.cpp
 *
 *  Written by Microsoft Developer Support
 *
 *  Functions implemented in inetall.cpp
 *
 *  MyAllocMem()         - memory allocation helper function
 *  MyFreeMem()          - free memory allocated by MyAllocMem
 *  CMyItemArray::CMyItemArray()
 *                       - CMyItemArray constructor
 *  CMyItemArray::~CMyItemArray()
 *                       - CMyItemArray destructor
 *  CMyItemArray::Add()  - Add an item to the array
 *  CMyItemArray::RemoveAll()
 *                       - Remove all items in the array
 *  CMyItemArray::GetAt()- Get an item given an index
 *  CMyItemArray::GetSize()
 *                       - Get the size of the array
 *  WinMain	()           - WinMain, display our main dialog box
 *  Dlg_Proc()           - Message Proc for the main dialog box
 *  Dlg_OnInitDialog()   - WM_INITDIALOG handler for the main dialog box
 *  Dlg_OnCommand()      - WM_COMMAND handler for the main dialog box
 *  Dlg_OnDestroy()      - WM_DESTROY handler for the main dialog box
 *  BOOL UpdateUI()      - Exchange data between UI and member variables
 *  FillFtpOrFileObjArray()
 *                       - Enumerate a FTP or FILE URL, and populate a CMyItemArray
 *  FillTreeControl()    - Draw tree structure of a FTP or FILE URL in Treeview Ctrl
 *
 */
//////////////////////////////////////////////////////
#include <windows.h>

#include <windowsx.h> 
//we use message crackers to make code easier to read

#include <commctrl.h>
#include <tchar.h>
#include <string.h>
#include <wininet.h>
#include "inetall.h" 

LPVOID
MyAllocMem(
    DWORD cb)
{
    return HeapAlloc(GetProcessHeap(), 
    	HEAP_GENERATE_EXCEPTIONS | HEAP_ZERO_MEMORY, cb);
} 

BOOL
MyFreeMem(
    LPVOID pMem)
{
    return HeapFree(GetProcessHeap(), 0, pMem);
}

//////////////////////////////////////////////////////
//CMyItemArray Implementation functions
CMyItemArray::CMyItemArray()
{
	m_nCount = 0;
	m_pItemlist = NULL;
}

CMyItemArray::~CMyItemArray()
{
	if (m_pItemlist) MyFreeMem(m_pItemlist);
}

int CMyItemArray::Add(ItemAttrib& item)
{
	if (m_nCount%10 == 0)
	{
		//Allocating 10 ItemAttrib at a time
		LPVOID pTemp = MyAllocMem((m_nCount+10) * sizeof (ItemAttrib));
		if (!pTemp) return -1; 
		//The called function should check return value
		CopyMemory (pTemp, m_pItemlist, m_nCount*sizeof(ItemAttrib));
		MyFreeMem(m_pItemlist);
		m_pItemlist = (PItemAttrib)pTemp;
	}
	lstrcpy(m_pItemlist[m_nCount].szObjectPath, item.szObjectPath);
	m_pItemlist[m_nCount].nObjectType = item.nObjectType;
	return m_nCount++; //return index of the newly added item. Increment count.
}

void CMyItemArray::RemoveAll()
{
	if (m_pItemlist) MyFreeMem(m_pItemlist);
	m_pItemlist = NULL;
	m_nCount = 0;
}

ItemAttrib CMyItemArray::GetAt(int nIndex)
{
	if (nIndex>=0 && nIndex < m_nCount)
		return m_pItemlist[nIndex];
	else
	{
		ItemAttrib nullItem;
		(nullItem.szObjectPath)[0]='\0';
		nullItem.nObjectType = -1;
		return nullItem;
	}
}

int CMyItemArray::GetSize()
{
	return m_nCount;
}
//End of CMyItemArray Implementation
//////////////////////////////////////////////////////

//////////////////////////////////////////////////////
//Declare Dialog callback function.
BOOL CALLBACK Dlg_Proc (HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

//WinMain just displays a dialogbox
int APIENTRY WinMain (HINSTANCE hInstance, 
   HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow) {

	g_hInst = hInstance;
	InitCommonControls();
	if (DialogBox(hInstance, MAKEINTRESOURCE(IDD_INETALL_DIALOG), 
		NULL, (DLGPROC)Dlg_Proc) == -1) 
		MessageBox(NULL, "Failure in creating main dialog window", "Error", MB_OK);
	return(0);
}

BOOL Dlg_OnInitDialog (HWND hwnd, HWND hwndFocus, 
   LPARAM lParam) 
{
	BOOL bRet =  FALSE;

	g_Inet.m_dwSizeHtml = 1024;
	g_Inet.m_phtml = (LPTSTR)MyAllocMem(g_Inet.m_dwSizeHtml);
	if (!g_Inet.m_phtml)
	{
		MessageBox(hwnd, "Memory Allocation Failure", "Error", MB_OK);
		return bRet;
	}
	
	bRet = (g_hDlg = hwnd)
	&& (g_Inet.hCheckBoxCern = GetDlgItem(g_hDlg, IDC_CERN))
	&& (g_Inet.hwndUrl = GetDlgItem(g_hDlg, IDC_URL))
	&& (g_Inet.hwndPassword = GetDlgItem(g_hDlg, IDC_PASSWORD))
	&& (g_Inet.hwndUsername = GetDlgItem(g_hDlg, IDC_USERNAME))
	&& (g_Inet.hTreeViewCtrl = GetDlgItem(g_hDlg, IDC_TREE1))
	&& (g_Inet.hwndHTML = GetDlgItem(hwnd, IDC_HTML));

	if (!bRet) return bRet;

	//Set inital service to HTTP, and select the option button.
	g_Inet.m_dwServiceType = SERVICE_TYPE_HTTP;
	ShowWindow(g_Inet.hCheckBoxCern, SW_HIDE); //CERN check box only shown when doing ftp
	g_Inet.m_phtml[0]=g_Inet.m_url[0] = g_Inet.m_password[0] = g_Inet.m_username[0] = '\0';
	
	g_Inet.m_cern = TRUE;
	
	//Send g_Inet to update UI
	UpdateUI(FALSE);

	g_Inet.m_curItem = NULL; //No current selected item in tree control

	//Set up image list and tree control
	g_Inet.hImgList = ImageList_Create(16, 15, 0, 3, 2);
	HBITMAP hBmTemp;
	for (int iCnt=IDB_BMERR; iCnt<=IDB_BMFILE; iCnt++)
	{
		hBmTemp = LoadBitmap(g_hInst, MAKEINTRESOURCE(iCnt));
		ImageList_Add(g_Inet.hImgList, hBmTemp, NULL);
	}
	TreeView_SetImageList(g_Inet.hTreeViewCtrl, g_Inet.hImgList, TVSIL_NORMAL);
	TV_INSERTSTRUCT tvstruct;
	tvstruct.hParent = NULL;
	tvstruct.hInsertAfter = TVI_FIRST;
	tvstruct.item.iImage = 0;
	tvstruct.item.iSelectedImage = 0;
	tvstruct.item.pszText = _T("Root");
	tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
	g_Inet.m_curItem= (HTREEITEM)SendMessage(g_Inet.hTreeViewCtrl, TVM_INSERTITEM,0, (LPARAM)(LPTV_INSERTSTRUCT)&tvstruct);
	g_Inet.m_bRedrawTree = TRUE;
	return(TRUE);
}


void Dlg_OnDestroy (HWND hwnd) {
	if (g_Inet.hImgList) ImageList_Destroy(g_Inet.hImgList);
	if (g_Inet.m_phtml) MyFreeMem(g_Inet.m_phtml);
}

void Dlg_OnCommand (HWND hwnd, int id, 
   HWND hwndCtl, UINT codeNotify) 
{
   	switch (id) {
      case IDCANCEL:
         EndDialog(hwnd, id);
         break;

	  case IDC_HTTP: //http option button is clicked.
	  case IDC_FTP:  //ftp option button is clicked.
	  case IDC_FILE:  //file option button is clicked.
		g_Inet.m_url[0] = g_Inet.m_password[0] = g_Inet.m_username[0] 
			= g_Inet.m_phtml[0]= '\0';
		g_Inet.m_dwServiceType = (id == IDC_HTTP)? SERVICE_TYPE_HTTP:
		(id ==  IDC_FTP)?SERVICE_TYPE_FTP : SERVICE_TYPE_FILE;
		//Show CERN check box for FTP URL only
		if (id == IDC_FTP) 	ShowWindow(g_Inet.hCheckBoxCern, SW_SHOW);
		else ShowWindow(g_Inet.hCheckBoxCern, SW_HIDE);
		UpdateUI(FALSE); //Send g_Inet to update UI
		g_Inet.m_itemArray.RemoveAll(); 
		FillTreeControl();
		break;
	 
	  case IDC_CERN:  //CERN checked box is clicked.
		g_Inet.m_cern = IsDlgButtonChecked(g_hDlg, IDC_CERN)==BST_CHECKED;
		break;

	  case IDC_GETDATA: //GetData button is clicked
		HCURSOR		hCursor;
		hCursor = SetCursor(LoadCursor (NULL, IDC_WAIT));
		ShowCursor(TRUE);
		
		//Get the UI setting to g_Inet
		UpdateUI(TRUE);
		g_Inet.m_phtml[0]= '\0';
		UpdateUI(FALSE); //cleaning up the html window
		
		//strip out white space in url
		int i=0, j=0;
		while (g_Inet.m_url[i])
		{
			while (g_Inet.m_url[i] == ' ') i++;
			g_Inet.m_url[j++] = g_Inet.m_url[i++];
		}	
		g_Inet.m_url[j]='\0';
		if (!lstrlen(g_Inet.m_url))
		{
			MessageBox(g_hDlg, "You haven't enter a URL yet.", "Error", MB_OK);
			break;
		}

		CharLower(g_Inet.m_url); //change to all lower case
		if (_tcsstr(g_Inet.m_url, _T("http://")) ||
			_tcsstr(g_Inet.m_url, _T("ftp://")) ||
			_tcsstr(g_Inet.m_url, _T("file://")))
		{
			MessageBox(hwnd, "Don't type method name in the url text box!", g_Inet.m_url, MB_OK);
			goto CursorBackandBailOut;
		}

		if (g_Inet.m_dwServiceType == SERVICE_TYPE_FILE)
		{ //For file url, change all / to \ in the url
			i=0;
			while (g_Inet.m_url[i]) 
			{
				if (g_Inet.m_url[i] == '/') g_Inet.m_url[i] = '\\';
				i++;
			}
			lstrcpy(szFullUrl, "file://");
			lstrcat(szFullUrl, g_Inet.m_url);
		}
		else
		{ //For ftp or http, change all \ to / in the url
			i=0;
			while (g_Inet.m_url[i]) 
			{
				if (g_Inet.m_url[i] == '\\') g_Inet.m_url[i] = '/';
				i++;
			}		
//If the server requires username and password, we will construct a url like this:
//http://username:password@server:port/path.
//Since we only use InternetOpenUrl, there is no other way to pass in username and
//password.	Doesn't apply to FILE url.
			lstrcpy(szFullUrl, g_Inet.m_dwServiceType == SERVICE_TYPE_FTP?
				"ftp://":"http://");
			if (lstrlen(g_Inet.m_username) && lstrlen(g_Inet.m_password))
			{
				lstrcat(szFullUrl,g_Inet.m_username); 
				lstrcat(szFullUrl, ":");
				lstrcat(szFullUrl,(LPCTSTR)g_Inet.m_password); 
				lstrcat(szFullUrl, "@");
			}
			lstrcat(szFullUrl,(LPCTSTR)g_Inet.m_url); 
		}


		//if m_bRedrawTree is FALSE, which means user has clicked a treecontrol item,
		//we won't redraw the whole tree. We will simply add sub-item to the currnet 
		//selected item. Also if the service HTTP, we don't change tree control at all.
		if ((g_Inet.m_bRedrawTree && g_Inet.m_dwServiceType != SERVICE_TYPE_HTTP)
			|| g_Inet.m_dwServiceType == SERVICE_TYPE_HTTP)
		{
			TreeView_DeleteAllItems( g_Inet.hTreeViewCtrl);
			TV_INSERTSTRUCT tvstruct;
			tvstruct.hParent = NULL;
			tvstruct.hInsertAfter = TVI_FIRST;
			tvstruct.item.iImage = 0;
			tvstruct.item.iSelectedImage = 0;
			tvstruct.item.pszText = g_Inet.m_url;
			tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
			g_Inet.m_curItem = (HTREEITEM)SendMessage(g_Inet.hTreeViewCtrl, TVM_INSERTITEM,0, (LPARAM)(LPTV_INSERTSTRUCT)&tvstruct);
		}
		g_Inet.m_bRedrawTree = TRUE;


		HINTERNET hInternetSession;
		hInternetSession = InternetOpen(_T("InetAll"), INTERNET_OPEN_TYPE_PRECONFIG,
			NULL, NULL, 0);
		if (!hInternetSession)
		{
			MessageBox(hwnd, "InternetOpen Fails", "Error", MB_OK);
			goto CursorBackandBailOut;
		}
		switch (g_Inet.m_dwServiceType)
		{
			case SERVICE_TYPE_HTTP:
				HINTERNET hInternetFile;
				//We just download html and text. Modify if needs to download binary file.
				hInternetFile = InternetOpenUrl(hInternetSession, szFullUrl,
					NULL, 0, INTERNET_FLAG_TRANSFER_ASCII | INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE, 0);
				if (!hInternetFile)
				{
					MessageBox(hwnd, "InternetOpenUrl failed! Check URL or connection", szFullUrl, MB_OK);
					goto CursorBackandBailOut;
				}
				DWORD dwRead;
				TCHAR szTemp[1024];
				int nTimes;
				nTimes=1;
				while (InternetReadFile(hInternetFile, (LPVOID)szTemp, 1023, &dwRead))
				{
					if (!dwRead) break;
					szTemp[dwRead]='\0';
					//Enlarge buffer only on a need base
					if (++nTimes * 1024>(int)g_Inet.m_dwSizeHtml)
					{
						LPVOID pTemp = MyAllocMem(g_Inet.m_dwSizeHtml + 1024);
						if (!pTemp) {
							MessageBox(hwnd, "Mem alloc fails", "Error", MB_OK);
							InternetCloseHandle(hInternetFile);
							g_Inet.m_phtml[0] = '\0';
							goto CursorBackandBailOut;
						}
						CopyMemory (pTemp, g_Inet.m_phtml, g_Inet.m_dwSizeHtml);
						g_Inet.m_dwSizeHtml += 1024;

						MyFreeMem(g_Inet.m_phtml);
						g_Inet.m_phtml = (LPTSTR)pTemp;
					}
					lstrcat(g_Inet.m_phtml, szTemp);
				}
				SetWindowText(g_Inet.hwndHTML, g_Inet.m_phtml);
				InternetCloseHandle(hInternetFile);
				break;
				
			case SERVICE_TYPE_FILE:
			case SERVICE_TYPE_FTP:
				//FillFtpOrFileObjArray enumerates and FTP or FILE url, and populates
				//g_Inet.m_itemArray.
				if (!FillFtpOrFileObjArray(hInternetSession, szFullUrl)) break;
				//FillTreeControl draws the treeview control using g_Inet.m_itemArray 
				FillTreeControl();
				break;
		}

CursorBackandBailOut:
		InternetCloseHandle(hInternetSession);
		UpdateUI(FALSE);
		ShowCursor(FALSE);
		SetCursor(hCursor);
		break; //break for switch id
	}		  	
}


BOOL CALLBACK Dlg_Proc (HWND hDlg, UINT uMsg, 
   WPARAM wParam, LPARAM lParam) {
   
   BOOL fProcessed = TRUE;
   switch (uMsg) {
      HANDLE_MSG(hDlg, WM_INITDIALOG, Dlg_OnInitDialog);
      HANDLE_MSG(hDlg, WM_DESTROY, Dlg_OnDestroy);
      HANDLE_MSG(hDlg, WM_COMMAND, Dlg_OnCommand);

	  //No message crackers defined in windowsx.h for WM_NOTIFY, so we just handled	
	  //it directly.
	  //We only process WM_NOTIFY when TreeView items are double clicked.
	  case WM_NOTIFY:
		int idCtrl;
		idCtrl  = (int) wParam;
		LPNMHDR pnmh;
		pnmh =  (LPNMHDR) lParam; 
 
		if (idCtrl == IDC_TREE1 && pnmh->code == NM_DBLCLK)
		{
			g_Inet.m_curItem = TreeView_GetSelection(g_Inet.hTreeViewCtrl);

			//if it's already root, we don't need to enumerate again.
			if (! TreeView_GetParent(g_Inet.hTreeViewCtrl, g_Inet.m_curItem)) return fProcessed;
			TV_ITEM tvItem;
			tvItem.mask =TVIF_TEXT; 
			tvItem.hItem = g_Inet.m_curItem;
			tvItem.pszText = g_Inet.m_url;
			TreeView_GetItem(g_Inet.hTreeViewCtrl, &tvItem);

			//change UI to have new m_url
			UpdateUI(FALSE);

	//if the URL ends with a / or \, it's a directory, we call Dlg_OnCommand directly to
	//construct new m_itemArray. FillFtpOrFileObjArray
	//and FillTreeControl will be called by Dlg_OnCommand.
			TCHAR cRight;
			cRight = g_Inet.m_url[lstrlen(g_Inet.m_url)-1];
			if (cRight =='/' ||cRight =='\\')
			{
				g_Inet.m_bRedrawTree = FALSE;
				Dlg_OnCommand (g_hDlg, IDC_GETDATA, GetDlgItem(g_hDlg, IDC_GETDATA),0);
			}
			else
			{
				//if it's a file, we are downloading it.
				if (g_Inet.m_dwServiceType == SERVICE_TYPE_FTP)
				{
					HINTERNET hInternetFile, hInternetSession;
					hInternetSession = InternetOpen(_T("InetAll"), INTERNET_OPEN_TYPE_PRECONFIG,
						NULL, NULL, 0);
					if (!hInternetSession)
					{
						MessageBox(g_hDlg, "InternetOpen Fails", "Error", MB_OK);
						return fProcessed;
					}			
		
					UpdateUI(TRUE);
					lstrcpy(szFullUrl, g_Inet.m_dwServiceType == SERVICE_TYPE_FTP?
						"ftp://":"http://");
					if (lstrlen(g_Inet.m_username) && lstrlen(g_Inet.m_password))
					{
						lstrcat(szFullUrl,g_Inet.m_username); 
						lstrcat(szFullUrl, ":");
						lstrcat(szFullUrl,(LPCTSTR)g_Inet.m_password); 
						lstrcat(szFullUrl, "@");
					}
					lstrcat(szFullUrl,(LPCTSTR)g_Inet.m_url); 
					DeleteFile("c:\\deleteme");
					HANDLE f;
					DWORD dwRead;	
					//download the file to c:\deleteme
					f= CreateFile("c:\\deleteme", GENERIC_WRITE,  0, NULL, 
						CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL, NULL); 

					if (f==  INVALID_HANDLE_VALUE) 
					{
						MessageBox (hDlg, "Can't open c:\\deleteme to write! Enough free space on C:???",
						szFullUrl, MB_OK);
						return fProcessed;
					}
 					hInternetFile = InternetOpenUrl(hInternetSession,(LPCTSTR)szFullUrl, NULL, 0, 
						INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE, 0);
					if (!hInternetFile)
					{
						CloseHandle(f);
						return fProcessed;
					}
					TCHAR szTemp[1024];
					while (InternetReadFile(hInternetFile, (LPVOID)szTemp, 1024, &dwRead))
					{
						if (!dwRead) break;
						DWORD dwWritten;
						WriteFile(f, (LPVOID)szTemp, dwRead, &dwWritten, NULL);
					}
					CloseHandle(f);
					InternetCloseHandle(hInternetFile);
					InternetCloseHandle(hInternetSession);
					MessageBox(g_hDlg, "The url is downloaded in c:\\deleteme!", szFullUrl, MB_OK);

				}////////////
			else
			{ ///file type url
				DeleteFile("c:\\deleteme");
				if (CopyFile(
					g_Inet.m_url,	// pointer to name of an existing file 
					"c:\\deleteme",	// pointer to filename to copy to 
					FALSE 	// flag for operation if file exists 
					)) 
					MessageBox(g_hDlg, "The url is downloaded in c:\\deleteme!", g_Inet.m_url, MB_OK);
				else 
				{
					MessageBox(g_hDlg, "CopyFile failed!", g_Inet.m_url, MB_OK);
				}
			}
		}
		//Double click will actually collapse a tree. To expand it in double click event
		//we will simply post a TVM_EXPAND message to the treeview control.
		PostMessage(g_Inet.hTreeViewCtrl, TVM_EXPAND, (WPARAM) (UINT) TVE_EXPAND, (LPARAM) g_Inet.m_curItem); 
		}
		break;

      default:
         fProcessed = FALSE;
         break;
   }

   return(fProcessed);
}


//Update UI or Collect input from UI
//bDirection FALSE g_Inet to UI
//bDirection TRUE UI to g_Inet

BOOL UpdateUI(BOOL bDirection)
{
	BOOL bRet = FALSE;
	if (bDirection) //Get UI Input to g_Inet
	{
		if (BST_CHECKED == IsDlgButtonChecked(g_hDlg, IDC_CERN)) g_Inet.m_cern = TRUE;
		else g_Inet.m_cern =  FALSE;

		if (BST_CHECKED == IsDlgButtonChecked(g_hDlg, IDC_HTTP)) 
			g_Inet.m_dwServiceType = SERVICE_TYPE_HTTP;
		if (BST_CHECKED == IsDlgButtonChecked(g_hDlg, IDC_FTP)) 
			g_Inet.m_dwServiceType = SERVICE_TYPE_FTP;
		if (BST_CHECKED == IsDlgButtonChecked(g_hDlg, IDC_FILE)) 
			g_Inet.m_dwServiceType = SERVICE_TYPE_FILE;

		bRet = GetDlgItemText(g_hDlg, IDC_URL, g_Inet.m_url, MAX_STRING_SIZE)
		  && GetDlgItemText(g_hDlg, IDC_USERNAME, g_Inet.m_username, MAX_STRING_SIZE)
		  && GetDlgItemText(g_hDlg, IDC_PASSWORD, g_Inet.m_password, MAX_STRING_SIZE);
	}
	else //Update UI from g_Inet
	{ 
		int nService;

		if (g_Inet.m_dwServiceType == SERVICE_TYPE_HTTP) nService = IDC_HTTP;
		else if (g_Inet.m_dwServiceType == SERVICE_TYPE_FTP) nService = IDC_FTP;
		else nService = IDC_FILE;
		bRet = CheckRadioButton(g_hDlg, IDC_HTTP, IDC_FILE, nService)
			&& SetWindowText(g_Inet.hwndUrl, g_Inet.m_url)
		    && SetWindowText(g_Inet.hwndPassword, g_Inet.m_password)
			&& SetWindowText(g_Inet.hwndUsername, g_Inet.m_username);;
		bRet  = bRet && SetWindowText(g_Inet.hwndHTML, g_Inet.m_phtml);
	
		SendMessage(g_Inet.hCheckBoxCern, BM_SETCHECK, g_Inet.m_cern, 0);
	}
	return bRet;
}

//Enumerate strURL, and populate g_Inet.m_itemArray
BOOL FillFtpOrFileObjArray(HINTERNET hInternetSession, LPTSTR strURL)
{
	BOOL bRet = FALSE;
	if (!hInternetSession) return bRet;

	if (g_Inet.m_dwServiceType == SERVICE_TYPE_HTTP)
	{
		MessageBox(g_hDlg, "only ftp and file url needs enumeration!", "Error", MB_OK);
		return bRet;
	}

	ItemAttrib tempObj;
	g_Inet.m_itemArray.RemoveAll();

	if (g_Inet.m_dwServiceType == SERVICE_TYPE_FTP) //////// start_if_ftp
	{
		//CERN or NO CERN we will download HTML anyway.
		HINTERNET hInternetFile;
		hInternetFile = InternetOpenUrl(hInternetSession, szFullUrl,
					NULL, 0, INTERNET_FLAG_TRANSFER_ASCII | INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE, 0);
		DWORD dwRead;
		TCHAR szTemp[1024];
		int nTimes;
		nTimes=1;
		while (InternetReadFile(hInternetFile, (LPVOID)szTemp, 1023, &dwRead))
		{
			if (!dwRead) break;
			szTemp[dwRead]='\0';
			if (++nTimes * 1024>(int)g_Inet.m_dwSizeHtml)
			{
				LPVOID pTemp = MyAllocMem(g_Inet.m_dwSizeHtml + 1024);
				if (!pTemp) {
					MessageBox(g_hDlg, "Mem alloc fails", "Error", MB_OK);
					InternetCloseHandle(hInternetFile);
					g_Inet.m_phtml[0] = '\0';
					break;
				}
				CopyMemory (pTemp, g_Inet.m_phtml, g_Inet.m_dwSizeHtml);
				g_Inet.m_dwSizeHtml += 1024;

				MyFreeMem(g_Inet.m_phtml);
				g_Inet.m_phtml = (LPTSTR)pTemp;
			}
			lstrcat(g_Inet.m_phtml, szTemp);
		}
		SetWindowText(g_Inet.hwndHTML, g_Inet.m_phtml);
		InternetCloseHandle(hInternetFile);			

		//If direct access to FTP server, we will use 
		//InternetOpenUrl(INTERNET_FLAG_RAW_DATA) and InternetFindNextFile
		//to enumerate the sub directories and files
		if (!g_Inet.m_cern)  //start_if_no_cern
		{
			WIN32_FIND_DATA wfd;
				
			HINTERNET hInternetFind = InternetOpenUrl(hInternetSession,(LPCTSTR)strURL, NULL, 0, 
							INTERNET_FLAG_RAW_DATA| INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE, 0);
			if (!InternetFindNextFile (hInternetFind, &wfd)) 
			{
				bRet = FALSE; //Actually this may or may not be a failure.
				MessageBox(g_hDlg, "No files or sub-directories under this url directory", strURL, MB_OK);
				return bRet;
			}
			do {
				LPCTSTR strFileName;
				if(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
					strFileName = (LPCTSTR) &wfd.cFileName;
					if (strFileName[0] == '.') continue;
					lstrcpy(tempObj.szObjectPath, g_Inet.m_url);
					if (strURL[lstrlen(strURL)-1] != '/') lstrcat(tempObj.szObjectPath, "/");
					lstrcat (tempObj.szObjectPath, strFileName);
					if (tempObj.szObjectPath[lstrlen(tempObj.szObjectPath)-1] != '/' )
						lstrcat(tempObj.szObjectPath, "/");
					tempObj.nObjectType = 1;
					g_Inet.m_itemArray.Add(tempObj);
				}
				else
				{
					strFileName = (LPCTSTR) &wfd.cFileName;
					lstrcpy(tempObj.szObjectPath , g_Inet.m_url);
					if (strURL[lstrlen(strURL)-1] != '/') lstrcat(tempObj.szObjectPath, "/");
					lstrcat(tempObj.szObjectPath, strFileName);
					tempObj.nObjectType = 0;
					g_Inet.m_itemArray.Add(tempObj);
				}
			} while (InternetFindNextFile (hInternetFind, &wfd));
			InternetCloseHandle (hInternetFind);
		}  //end_if_no_cern
		else
		{ //start_if_cern 
			LPTSTR strTemp;
			TCHAR strTempUrl[MAX_STRING_SIZE];
			strTemp = g_Inet.m_phtml;
			//we have the html file listings in the strTemp, we just need to parse it 
			//a sample html is provided at the bottom of this file. Note that the parsing
			//code may not work with proxies other than MS Proxy server.
			while (TRUE)
			{
				int nPos;
				TCHAR strLeft[] = "<A HREF=";
				TCHAR strRight[] = ">";

				nPos = _tcsstr(strTemp, strLeft) - strTemp;
				if (nPos < 0) break;
				strTemp = strTemp + nPos +lstrlen(strLeft)+1;
				nPos = _tcsstr(strTemp, strRight) - strTemp;
				for (int i=0; i<nPos-1; i++)
					strTempUrl[i]=strTemp[i];
				strTempUrl[nPos-1] = '\0';
				strTemp =  strTemp +i +lstrlen(strRight);
				if (strTempUrl[0] == '.') continue;
				
				if (g_Inet.m_url[lstrlen(g_Inet.m_url)-1] != '/')
				{
					g_Inet.m_url[lstrlen(g_Inet.m_url)] ='/';
					g_Inet.m_url[lstrlen(g_Inet.m_url)+1] ='\0';
				}

				TCHAR strServerName[256];
				i=0;
				while (TRUE)
				{	
					strServerName[i]= g_Inet.m_url[i];
					if (g_Inet.m_url[i] == '/')
					{
						strServerName[i] = '\0';
						break;
					}
					i++;
				}
				lstrcpy(tempObj.szObjectPath, strServerName);
				lstrcat(tempObj.szObjectPath, strTempUrl);
				if (strTempUrl[lstrlen(strTempUrl)-1] == '/' ) tempObj.nObjectType = 1;
					else tempObj.nObjectType = 0;
					g_Inet.m_itemArray.Add(tempObj);
				}
			if (!g_Inet.m_itemArray.GetSize()){
					MessageBox(g_hDlg, "No files or sub-directories under the url", g_Inet.m_url, MB_OK);
					return bRet;
				}
			}//end_if_cern
		}////end_if_ftp
		else 
		{  //start_if_file
			TCHAR strFileSpec[MAX_STRING_SIZE];

			
			lstrcpy(strFileSpec, g_Inet.m_url);
			
			//trying to determine if it's a single machine name to enumerate, or
			//it's already a unc name.
			LPTSTR szTempRight;

			//in case user type in \\machine name in url text box,
			szTempRight = strFileSpec+2;
			int i=0;
			BOOL bServerNameOnly;
			bServerNameOnly= TRUE;
			for (i=0; i<lstrlen(szTempRight)-1; i++)
			{
				if (szTempRight[i] == '\\')
				{
					bServerNameOnly = FALSE;
					break;
				}
			}
			
			if (bServerNameOnly)
			{ 
				//user enters a single machine name, we will enumerate the shares.
				lstrcpy(g_Inet.m_url, "\\\\");
				int i=0;
				while (strFileSpec[i] == '\\') i++;
				lstrcat(g_Inet.m_url, (LPTSTR)(strFileSpec + i));
				if (g_Inet.m_url[lstrlen(g_Inet.m_url)-1] == '\\')
					g_Inet.m_url[lstrlen(g_Inet.m_url)-1] = '\0';
				//now the g_Inet.m_url is "\\server name
				NETRESOURCE nr;
				nr.dwScope = RESOURCE_GLOBALNET;
				nr.dwType = RESOURCETYPE_ANY;
				nr.dwDisplayType = RESOURCEDISPLAYTYPE_SERVER;
				nr.dwUsage = RESOURCEUSAGE_CONTAINER;
				nr.lpLocalName = NULL;
				nr.lpRemoteName = g_Inet.m_url;
				nr.lpComment = NULL;
				nr.lpProvider = NULL;
				LPVOID pMem =  HeapAlloc(GetProcessHeap(), 
    				HEAP_GENERATE_EXCEPTIONS | HEAP_ZERO_MEMORY, 16384);
				if (!pMem)
				{
					MessageBox(g_hDlg, "Not enough memory to allocate for WNetEnumResource",g_Inet.m_url, MB_OK );
					return bRet;
				}
				HANDLE hWNetEnum=NULL;
				DWORD dwStatus = WNetOpenEnum(RESOURCE_GLOBALNET, RESOURCETYPE_ANY, 
					RESOURCEUSAGE_CONNECTABLE, &nr, &hWNetEnum);
				if (dwStatus != NO_ERROR)
				{
					DWORD dwErr = GetLastError();
					MessageBox(g_hDlg, "WNetOpenEnum failed", g_Inet.m_url, MB_OK );
					HeapFree(GetProcessHeap(), 0, pMem);
					return bRet;
				}
				do
				{
					DWORD dwEntries;
					DWORD dwBuffSize;
					dwEntries =1;
					dwBuffSize= 16384;
					dwStatus = WNetEnumResource(hWNetEnum, &dwEntries, pMem, &dwBuffSize);
					if (dwStatus == NO_ERROR)
					{
						lstrcpy(tempObj.szObjectPath, ((LPNETRESOURCE)pMem)->lpRemoteName);
						lstrcat(tempObj.szObjectPath, "\\");
						tempObj.nObjectType = 1;
						g_Inet.m_itemArray.Add(tempObj);
					}
				} while (dwStatus == NO_ERROR);
				if (dwStatus != ERROR_NO_MORE_ITEMS)
				{
					MessageBox(g_hDlg, "WNetEnumResource failed",g_Inet.m_url, MB_OK);
					MyFreeMem(pMem);
					WNetCloseEnum(hWNetEnum);
					return bRet;
				}
				MyFreeMem(pMem);
				WNetCloseEnum(hWNetEnum);
				//we are done with enumerating shares on a file server.
				return bRet = TRUE;
			}
			
			lstrcpy(strFileSpec, "\\\\");
			i=0;
			while (g_Inet.m_url[i]=='\\') //skip starting \ in m_url
			{
				i++;
			}
			lstrcat(strFileSpec, g_Inet.m_url+i);
			//Now strFileSpec is a UNC such as \\server\share\filedirectory\...

			WIN32_FIND_DATA fd; 
			HANDLE hFind = NULL;		
			if ((hFind = FindFirstFile ((LPCTSTR) strFileSpec, &fd)) ==
				INVALID_HANDLE_VALUE) {
				if (strFileSpec[lstrlen(strFileSpec)-1] != '\\') lstrcat(strFileSpec, "\\");
				lstrcpy(g_Inet.m_url, strFileSpec);
				lstrcat(strFileSpec, "*.*");
				if ((hFind = FindFirstFile ((LPCTSTR) strFileSpec, &fd)) ==
					INVALID_HANDLE_VALUE) 
				{
					MessageBox(g_hDlg, "No files or sub-directories under the url", g_Inet.m_url, MB_OK);
					return bRet;
				}				
			}
			do {
				if(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
					 (LPCTSTR) &fd.cFileName;
					if ( ((LPCTSTR) &fd.cFileName)[0] == '.') continue;
					lstrcpy(tempObj.szObjectPath, g_Inet.m_url);
					lstrcat(tempObj.szObjectPath, (LPCTSTR) &fd.cFileName);
					lstrcat(tempObj.szObjectPath, "\\");
					tempObj.nObjectType = 1;
					g_Inet.m_itemArray.Add(tempObj);
				}
				else
				{
					lstrcpy(tempObj.szObjectPath, g_Inet.m_url);
					lstrcat(tempObj.szObjectPath, (LPCTSTR) &fd.cFileName);
					tempObj.nObjectType = 0;
					g_Inet.m_itemArray.Add(tempObj);
	
				}
			} while (FindNextFile (hFind, &fd));
			FindClose (hFind);	
		} //end_if_file
		bRet = TRUE; //happy here.

	return bRet;
}

//Draw tree structure of a FTP or FILE URL in 
//treeview Ctrl using g_Inet.m_itemArray
void FillTreeControl()
{
	TV_INSERTSTRUCT tvstruct;
	int nItem;
	nItem = g_Inet.m_itemArray.GetSize();
	HTREEITEM hChildItem=NULL, hNextChildItem=NULL;
	if (!nItem){
		TreeView_DeleteAllItems( g_Inet.hTreeViewCtrl);
		tvstruct.hParent = NULL;
		tvstruct.hInsertAfter = TVI_FIRST;
		tvstruct.item.iImage = 0;
		tvstruct.item.iSelectedImage = 0;
		tvstruct.item.pszText = _T("Root");
		tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
		SendMessage(g_Inet.hTreeViewCtrl, TVM_INSERTITEM,0, (LPARAM)(LPTV_INSERTSTRUCT)&tvstruct);
		return;
	}
	
	int nBMID;

	//Remove all old items under the selected item
	hChildItem = TreeView_GetChild(g_Inet.hTreeViewCtrl, g_Inet.m_curItem); 

	while (hChildItem)
	{
		hNextChildItem = TreeView_GetNextSibling(g_Inet.hTreeViewCtrl, hChildItem);
		 TreeView_DeleteItem(g_Inet.hTreeViewCtrl, hChildItem);
		hChildItem = hNextChildItem;
	}
	//add new items
	for (int i=0; i<nItem; i++)
	{
		nBMID = ((g_Inet.m_itemArray.GetAt(i)).nObjectType==0)?2:1;
		tvstruct.hParent = g_Inet.m_curItem;
		tvstruct.hInsertAfter = TVI_LAST;
		tvstruct.item.iImage = nBMID;
		tvstruct.item.iSelectedImage = nBMID;
		tvstruct.item.pszText = (g_Inet.m_itemArray.GetAt(i)).szObjectPath;
		tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
		SendMessage(g_Inet.hTreeViewCtrl, TVM_INSERTITEM,0, (LPARAM)(LPTV_INSERTSTRUCT)&tvstruct);
	}
	//Make sure the tree under the selected item is expanded.
	if (g_Inet.m_curItem) 
	{
		TreeView_EnsureVisible(g_Inet.hTreeViewCtrl, g_Inet.m_curItem);
		TreeView_Expand(g_Inet.hTreeViewCtrl, g_Inet.m_curItem, TVE_EXPAND);
	}
}

//A typical HTML wrapper for file listing a in ftp url from MS Proxy Server
//which is CERN-compatible proxy.
/*
<HTML>
<HEAD>
<TITLE>FTP root at ftp.microsoft.com</TITLE>
</HEAD>
<BODY>
<H1>FTP root at ftp.microsoft.com</H1>
<HR>
<H4><PRE>
This is FTP.MICROSOFT.COM.  Please see the
 dirmap.txt file for more information.
</PRE></H4>
<HR>
<PRE>
08/24/94 12:00AM          &lt;DIR&gt; <A HREF="/deskapps/access/">access</A>
08/24/94 12:00AM          &lt;DIR&gt; <A HREF="/deskapps/dosword/">dosword</A>
08/24/94 12:00AM          &lt;DIR&gt; <A HREF="/deskapps/excel/">excel</A>
08/24/94 12:00AM          &lt;DIR&gt; <A HREF="/deskapps/games/">games</A>
10/08/94 12:00AM          &lt;DIR&gt; <A HREF="/deskapps/GEN_INFO/">GEN_INFO</A>
08/24/94 12:00AM          &lt;DIR&gt; <A HREF="/deskapps/homeapps/">homeapps</A>
03/12/97 10:23PM          &lt;DIR&gt; <A HREF="/deskapps/kids/">kids</A>
08/24/94 12:00AM          &lt;DIR&gt; <A HREF="/deskapps/miscapps/">miscapps</A>
08/24/94 12:00AM          &lt;DIR&gt; <A HREF="/deskapps/mmapps/">mmapps</A>
08/28/96 12:00AM          &lt;DIR&gt; <A HREF="/deskapps/MONEY/">MONEY</A>
08/24/94 12:00AM          &lt;DIR&gt; <A HREF="/deskapps/office/">office</A>
08/24/94 12:00AM          &lt;DIR&gt; <A HREF="/deskapps/powerpt/">powerpt</A>
08/24/94 12:00AM          &lt;DIR&gt; <A HREF="/deskapps/project/">project</A>
08/24/94 12:00AM          &lt;DIR&gt; <A HREF="/deskapps/publishr/">publishr</A>
08/30/94 12:00AM          1,791 <A HREF="/deskapps/readme.txt">readme.txt</A>
08/24/94 12:00AM          &lt;DIR&gt; <A HREF="/deskapps/word/">word</A>
08/28/96 12:00AM          &lt;DIR&gt; <A HREF="/deskapps/WORKS/">WORKS</A>
</PRE>
<HR>
</BODY>
</HTML>
*/

/////////////////////// End Of File ////////////////////////