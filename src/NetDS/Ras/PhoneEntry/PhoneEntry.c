/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples.
*       Copyright 1993 - 1998 Microsoft Corporation.
*       All rights reserved.
*       This source code is only intended as a supplement to
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the
*       Microsoft samples programs.
\******************************************************************************/

#define STRICT
#include <windows.h>
#include <windowsx.h>
#include <ras.h>
#include <raserror.h>
#include <commctrl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "resource.h"

#define BUFFSIZE 4096

UINT unMsg;
HINSTANCE hInstance;
char szEntryName[256];
LPRASENTRY lpRasEntry;
RASDEVINFO *RasDevInfo;
BOOL flag;
BOOL valid_entry;
DWORD tEntries;
int GlobalTemp;



// Property sheet
HWND hSheet = NULL;


// Property sheet function prototypes
BOOL CALLBACK PropSheet(HWND hWnd);
INT_PTR CALLBACK Page0Proc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK Page1Proc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK Page2Proc(HWND, UINT, WPARAM, LPARAM);

// Dialog box function prototype
INT_PTR CALLBACK Dlg_Proc1(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK Dlg_Proc2(HWND, UINT, WPARAM, LPARAM);




//
//  FUNCTION: Dlg_Proc1(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Dialog Procedure for manipulating the TCP/IP settings for a
//			  phonebook entry.
//
//  PARAMETERS:
//    hwnd     - window handle
//    uMessage - message number
//    wparam   - additional information (dependant on message number)
//    lparam   - additional information (dependant on message number)
//
//  RETURN VALUE:
//			Returns 0.
//
//  COMMENTS:
//		This function handles the dialog box for the TCP/IP settings.
//		The dialog box allows the user to assign an IP address or use a server
//		assigned one. It also allows the user to specify the various name server
//		addresses. Finally, the user can also specify to use IP header compression
//		and to use a default gateway on a remote network.
//
//		The following fields of the RASENTRY structure are modified
//
//		lpRasEntry->ipaddr
//		lpRasEntry->ipaddrDns
//		lpRasEntry->ipaddrDnsAlt
//		lpRasEntry->ipaddrWins
//		lpRasEntry->ipaddrWinsAlt
//
//		The following flags in the lpRasEntry->dwfOptions are modified
//
//		RASEO_SpecificIpAddr
//		RASEO_SpecificNameServers
//		RASEO_IpHeaderCompression
//		RASEO_RemoteDefaultGateway
//

INT_PTR CALLBACK Dlg_Proc1(HWND hWnd, UINT uMsgID, WPARAM wParam, LPARAM lParam)
{
    static HWND hRadio1;
    static HWND hRadio2;
    static HWND hRadio3;
    static HWND hRadio4;
    static HWND hEdit1;
    static HWND hEdit2;
    static HWND hEdit3;
    static HWND hEdit4;
    static HWND hEdit5;
    char buff[256];
    BYTE a, b, c, d;

// Initialize handles for various controls
    hRadio1 = GetDlgItem(hWnd, IDC_RADIO1);
    hRadio2 = GetDlgItem(hWnd, IDC_RADIO2);
    hRadio3 = GetDlgItem(hWnd, IDC_RADIO3);
    hRadio4 = GetDlgItem(hWnd, IDC_RADIO4);
    hEdit1 = GetDlgItem(hWnd, IDC_EDIT8);
    hEdit2 = GetDlgItem(hWnd, IDC_EDIT2);
    hEdit3 = GetDlgItem(hWnd, IDC_EDIT3);
    hEdit4 = GetDlgItem(hWnd, IDC_EDIT6);
    hEdit5 = GetDlgItem(hWnd, IDC_EDIT7);

    switch (uMsgID)
    {
        case WM_INITDIALOG:
            if (flag)           // Check if any phonebook entry exists
            {                   // Display parametres of the existing entry
                if (lpRasEntry->dwfOptions & RASEO_SpecificIpAddr)
                {
                    CheckRadioButton(hWnd, IDC_RADIO1, IDC_RADIO2, IDC_RADIO2);
                    EnableWindow(hEdit1, TRUE);
                    sprintf(buff, "%d.%d.%d.%d", lpRasEntry->ipaddr.a, lpRasEntry->ipaddr.b,
                        lpRasEntry->ipaddr.c, lpRasEntry->ipaddr.d);
                    SendMessage(hEdit1, WM_SETTEXT, 0, (LPARAM) (LPCTSTR) buff);
                }
                else
                {
                    CheckRadioButton(hWnd, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
                    EnableWindow(hEdit1, FALSE);
                }
                if (lpRasEntry->dwfOptions & RASEO_SpecificNameServers)
                {
                    CheckRadioButton(hWnd, IDC_RADIO3, IDC_RADIO4, IDC_RADIO4);
                    EnableWindow(hEdit2, TRUE);
                    EnableWindow(hEdit3, TRUE);
                    EnableWindow(hEdit4, TRUE);
                    EnableWindow(hEdit5, TRUE);
                    sprintf(buff, "%d.%d.%d.%d", lpRasEntry->ipaddrDns.a, lpRasEntry->ipaddrDns.b,
                        lpRasEntry->ipaddrDns.c, lpRasEntry->ipaddrDns.d);
                    SendMessage(hEdit2, WM_SETTEXT, 0, (LPARAM) (LPCTSTR) buff);
                    sprintf(buff, "%d.%d.%d.%d", lpRasEntry->ipaddrDnsAlt.a, lpRasEntry->ipaddrDnsAlt.b,
                        lpRasEntry->ipaddrDnsAlt.c, lpRasEntry->ipaddrDnsAlt.d);
                    SendMessage(hEdit3, WM_SETTEXT, 0, (LPARAM) (LPCTSTR) buff);
                    sprintf(buff, "%d.%d.%d.%d", lpRasEntry->ipaddrWins.a, lpRasEntry->ipaddrWins.b,
                        lpRasEntry->ipaddrWins.c, lpRasEntry->ipaddrWins.d);
                    SendMessage(hEdit4, WM_SETTEXT, 0, (LPARAM) (LPCTSTR) buff);
                    sprintf(buff, "%d.%d.%d.%d", lpRasEntry->ipaddrWinsAlt.a, lpRasEntry->ipaddrWinsAlt.b,
                        lpRasEntry->ipaddrWinsAlt.c, lpRasEntry->ipaddrWinsAlt.d);
                    SendMessage(hEdit5, WM_SETTEXT, 0, (LPARAM) (LPCTSTR) buff);
                }
                else
                {
                    CheckRadioButton(hWnd, IDC_RADIO3, IDC_RADIO4, IDC_RADIO3);
                    EnableWindow(hEdit2, FALSE);
                    EnableWindow(hEdit3, FALSE);
                    EnableWindow(hEdit4, FALSE);
                    EnableWindow(hEdit5, FALSE);
                }
                if (lpRasEntry->dwfOptions & RASEO_IpHeaderCompression)
                    CheckDlgButton(hWnd, IDC_CHECK7, BST_CHECKED);
                if (lpRasEntry->dwfOptions & RASEO_RemoteDefaultGateway)
                    CheckDlgButton(hWnd, IDC_CHECK8, BST_CHECKED);
            }
            else
            {                   // No entry exists, display default paramters
                CheckRadioButton(hWnd, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
                CheckRadioButton(hWnd, IDC_RADIO3, IDC_RADIO4, IDC_RADIO3);
                EnableWindow(hEdit1, FALSE);
                EnableWindow(hEdit2, FALSE);
                EnableWindow(hEdit3, FALSE);
                EnableWindow(hEdit4, FALSE);
                EnableWindow(hEdit5, FALSE);
                CheckDlgButton(hWnd, IDC_CHECK7, BST_CHECKED);
                CheckDlgButton(hWnd, IDC_CHECK8, BST_CHECKED);
            }
            break;
        case WM_CLOSE:
            EndDialog(hWnd, 0);
            break;
        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                case IDOK:
                    if (IsDlgButtonChecked(hWnd, IDC_RADIO2) == BST_CHECKED)
                    {           // Enable the SpecificIpAddr flag and store the
                                // IP address in RASENTRY
                        lpRasEntry->dwfOptions |= RASEO_SpecificIpAddr;
                        GetWindowText(GetDlgItem(hWnd, IDC_EDIT8), buff, 256);
                        sscanf(buff, "%d.%d.%d.%d", &a, &b, &c, &d);
                        lpRasEntry->ipaddr.a = a;
                        lpRasEntry->ipaddr.b = b;
                        lpRasEntry->ipaddr.c = c;
                        lpRasEntry->ipaddr.d = d;
                    }
                    else        // Disable the SpecificIpAddr flag
                        lpRasEntry->dwfOptions &= ~RASEO_SpecificIpAddr;
                    if (IsDlgButtonChecked(hWnd, IDC_RADIO4) == BST_CHECKED)
                    {           // Enable the SpecificNameServers flag and store
                        // the DNS, DNS Alt., WINS and WINS Alt. addresses in RASENTRY
                        lpRasEntry->dwfOptions |= RASEO_SpecificNameServers;
                        GetWindowText(GetDlgItem(hWnd, IDC_EDIT2), buff, 256);
                        sscanf(buff, "%d.%d.%d.%d", &a, &b, &c, &d);
                        lpRasEntry->ipaddrDns.a = a;
                        lpRasEntry->ipaddrDns.b = b;
                        lpRasEntry->ipaddrDns.c = c;
                        lpRasEntry->ipaddrDns.d = d;
                        GetWindowText(GetDlgItem(hWnd, IDC_EDIT3), buff, 256);
                        sscanf(buff, "%d.%d.%d.%d", &a, &b, &c, &d);
                        lpRasEntry->ipaddrDnsAlt.a = a;
                        lpRasEntry->ipaddrDnsAlt.b = b;
                        lpRasEntry->ipaddrDnsAlt.c = c;
                        lpRasEntry->ipaddrDnsAlt.d = d;
                        GetWindowText(GetDlgItem(hWnd, IDC_EDIT6), buff, 256);
                        sscanf(buff, "%d.%d.%d.%d", &a, &b, &c, &d);
                        lpRasEntry->ipaddrWins.a = a;
                        lpRasEntry->ipaddrWins.b = b;
                        lpRasEntry->ipaddrWins.c = c;
                        lpRasEntry->ipaddrWins.d = d;
                        GetWindowText(GetDlgItem(hWnd, IDC_EDIT7), buff, 256);
                        sscanf(buff, "%d.%d.%d.%d", &a, &b, &c, &d);
                        lpRasEntry->ipaddrWinsAlt.a = a;
                        lpRasEntry->ipaddrWinsAlt.b = b;
                        lpRasEntry->ipaddrWinsAlt.c = c;
                        lpRasEntry->ipaddrWinsAlt.d = d;
                    }
                    else        // Disable the SpecificNameServers
                        lpRasEntry->dwfOptions &= ~RASEO_SpecificNameServers;
                    if (IsDlgButtonChecked(hWnd, IDC_CHECK7) == BST_CHECKED)
                        // Enable the IpHeaderCompression flag
                        lpRasEntry->dwfOptions |= RASEO_IpHeaderCompression;
                    else        // Disable the IpHeaderCompression flag
                        lpRasEntry->dwfOptions &= ~RASEO_IpHeaderCompression;
                    if (IsDlgButtonChecked(hWnd, IDC_CHECK8) == BST_CHECKED)
                        // Enable the RemoteDefaultGateway flag
                        lpRasEntry->dwfOptions |= RASEO_RemoteDefaultGateway;
                    else        // Disable the RemoteDefaultGateway flag
                        lpRasEntry->dwfOptions &= ~RASEO_RemoteDefaultGateway;

                    EndDialog(hWnd, TRUE);
                    break;
                case IDCANCEL:
                    EndDialog(hWnd, 0);
                    break;
                case IDC_RADIO2:
                    EnableWindow(hEdit1, TRUE);
                    break;
                case IDC_RADIO4:
                    EnableWindow(hEdit2, TRUE);
                    EnableWindow(hEdit3, TRUE);
                    EnableWindow(hEdit4, TRUE);
                    EnableWindow(hEdit5, TRUE);
                    break;
                case IDC_RADIO1:
                    EnableWindow(hEdit1, FALSE);
                    break;
                case IDC_RADIO3:
                    EnableWindow(hEdit2, FALSE);
                    EnableWindow(hEdit3, FALSE);
                    EnableWindow(hEdit4, FALSE);
                    EnableWindow(hEdit5, FALSE);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    return 0;
}


//
//  FUNCTION: Page0_Proc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Intialized Page 0 of the property sheet.
//
//  PARAMETERS:
//    hwnd     - window handle
//    uMessage - message number
//    wparam   - additional information (dependant on message number)
//    lparam   - additional information (dependant on message number)
//
//  RETURN VALUE:
//			Returns 0.
//
//  COMMENTS:
//		This function handles the dialog box on the zeroth page (Basic) of the
//		property sheet.
//		The dialog box allows the user to enter the name of the phone book
//		entry. It further allows the user to enter the telephone number
//		and the device that is to be associated with that phone book entry
//
//		It uses the following RAS APIs
//		RasEnumDevices(): To enumerate the various RAS capable devices
//		RasGetCountryInfo(): To obtain the country code and country ID
//		RasValidateEntryName(): To verify the entry name is of the correct form
//		RasSetEntryProperties(): To set the modified values of an existing
//		phone book entry or to set the values of a new entry

//		The following fields of the RASENTRY structure are modified
//
//		lpRasEntry->dwCountryID
//		lpRasEntry->dwCountryCode
//		lpRasEntry->szAreaCode
//		lpRasEntry->szLocalPhoneNumber
//		lpRasEntry->szDeviceType
//		lpRasEntry->szDeviceName
//
//		The following flag in the lpRasEntry->dwfOptions is modified
//
//		RASEO_UseCountryAndAreaCodes
//

INT_PTR CALLBACK Page0Proc(HWND hWnd, UINT uMsgID, WPARAM wParam, LPARAM lParam)
{
    int i, j, k = 0, iItem;
    char szCCode[256], szCName[256];
    char szTemp[256], temp[256];
    DWORD nRet;
    DWORD cb = 0;
    DWORD cDevices;
    LPRASCTRYINFO lpRasCtryInfo = (LPRASCTRYINFO) temp;
    DWORD Size;
	WPARAM wp;

    static HWND hComboBox;
    static HWND hComboBox2;
    static HWND hEditBox1;
    static HWND hEditBox2;
    static HWND hEditBox3;
    static HWND hEditBox4;


// Initialize the various controls
    hComboBox = GetDlgItem(hWnd, IDC_COMBO3);
    hComboBox2 = GetDlgItem(hWnd, IDC_COMBO1);
    hEditBox1 = GetDlgItem(hWnd, IDC_ENTRYNAME);
    hEditBox3 = GetDlgItem(hWnd, IDC_ACODE);
    hEditBox4 = GetDlgItem(hWnd, IDC_PHONE);

//	ZeroMemory(lpRasCtryInfo, 256);

    lpRasCtryInfo->dwCountryID = 1;
    switch (uMsgID)
    {
        case WM_INITDIALOG:


            // Allocate memory in RASDEVINFO for RasEnumDevices
            RasEnumDevices(NULL, &cb, &cDevices);

            RasDevInfo = (RASDEVINFO *) LocalAlloc(LPTR, cb);

            RasDevInfo->dwSize = sizeof(RASDEVINFO);
            // Check for RAS capable devices using RasEnumDevices
            if (nRet = RasEnumDevices(RasDevInfo, &cb, &cDevices))
            {
                wsprintf(szTemp, "RasEnumDevices failed: %d ", nRet);
                MessageBox(hWnd, szTemp, NULL, MB_OK | MB_ICONERROR);
                return 0;
            }
            else
            {
                GlobalTemp = cDevices;
                if (!cDevices)
                {
                    wsprintf(szTemp, "No RAS capable devices found.");
                    MessageBox(hWnd, szTemp, NULL, MB_OK | MB_ICONERROR);
                    return 0;
                }
                else
                {               // Display the devices in the combo box
                    for (i = 0; i < (int) cDevices; i++)
                        SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR) RasDevInfo[i].szDeviceName);
                    if (flag)
                    {
                        wp = SendMessage(hComboBox, CB_FINDSTRINGEXACT, 0, (LPARAM) (LPCTSTR) lpRasEntry->szDeviceName);
                        SendMessage(hComboBox, CB_SETCURSEL, wp, 0);
                    }
                    else
                        SendMessage(hComboBox, CB_SETCURSEL, 0, 0);
                }
            }

            while (lpRasCtryInfo->dwCountryID)
            {
                // Initialize RASCTRYINFO structure to be used in RasGetCountryInfo().
                lpRasCtryInfo->dwSize = sizeof(RASCTRYINFO);
                Size = 256;     // Minimum size of 256 required.
                if (nRet = RasGetCountryInfo(lpRasCtryInfo, &Size))
                {
                    wsprintf(szTemp, "RasGetCountryInfo failed: %d", nRet);
                    MessageBox(hWnd, szTemp, NULL, MB_OK | MB_ICONERROR);
                    return -1;
                }
                sprintf(szCCode, "%s (%d)", (LPSTR) lpRasCtryInfo + lpRasCtryInfo->dwCountryNameOffset, lpRasCtryInfo->dwCountryCode);
                // Display the country information in the combo box
                SendMessage(hComboBox2, CB_ADDSTRING, 0, (LPARAM) (LPCTSTR) szCCode);
                // Store the current phonebook entry's country name and code
                if (lpRasEntry->dwCountryID == lpRasCtryInfo->dwCountryID)
                {
                    lstrcpy(szTemp, szCCode);
                }
                lpRasCtryInfo->dwCountryID = lpRasCtryInfo->dwNextCountryID;
            }

            if (flag == TRUE)   // Flag to indicate phonebook entry exists
                // Display the properties retrieved for the first page
            {
                SendMessage(hEditBox1, WM_SETTEXT, 0, (LPARAM) (LPCTSTR) szEntryName);
                if (lpRasEntry->dwfOptions & RASEO_UseCountryAndAreaCodes)
                {
                    CheckDlgButton(hWnd, IDC_CHECK6, BST_CHECKED);
                    wp = SendMessage(hComboBox2, CB_FINDSTRINGEXACT, 0, (LPARAM) (LPCTSTR) szTemp);
                    SendMessage(hComboBox2, CB_SETCURSEL, wp, 0);
                    SendMessage(hEditBox3, WM_SETTEXT, 0, (LPARAM) (LPCTSTR) lpRasEntry->szAreaCode);
                    EnableWindow(hEditBox3, TRUE);
                    EnableWindow(hComboBox2, TRUE);

                }
                else
                {
                    EnableWindow(hEditBox3, FALSE);
                    EnableWindow(hComboBox2, FALSE);
                }
                SendMessage(hEditBox4, WM_SETTEXT, 0, (LPARAM) (LPCTSTR) lpRasEntry->szLocalPhoneNumber);

            }
            else
                // Set Default Values
            {
                EnableWindow(hComboBox2, FALSE);
                EnableWindow(hEditBox3, FALSE);
                lpRasEntry->dwfNetProtocols |= RASNP_Ip;
                lpRasEntry->dwFramingProtocol = RASFP_Ppp;
            }

            break;
        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                    // If user selects to use the Country Code and Area Code
                case IDC_ECAC:
                    if (IsDlgButtonChecked(hWnd, IDC_ECAC) == BST_CHECKED)
                    {
                        EnableWindow(hEditBox3, TRUE);
                        EnableWindow(hComboBox2, TRUE);
                        SendMessage(hComboBox2, CB_SETCURSEL, 0, 0);
                    }
                    else
                    {
                        EnableWindow(hEditBox3, FALSE);
                        EnableWindow(hComboBox2, FALSE);
                    }
                default:
                    break;

            }
            break;
        case WM_NOTIFY:
            switch (((LPNMHDR) lParam)->code)
            {
                case PSN_APPLY: // OK button has been clicked
                    // Get the values in the edit fields of the first page
                    GetWindowText(GetDlgItem(hWnd, IDC_ENTRYNAME), szEntryName, 256);
                    GetWindowText(GetDlgItem(hWnd, IDC_ACODE), lpRasEntry->szAreaCode, 256);
                    GetWindowText(GetDlgItem(hWnd, IDC_PHONE), lpRasEntry->szLocalPhoneNumber, 256);

                    // Validate the phonebook entry name using RasValidateEntryName
                    if (nRet = RasValidateEntryName(NULL, (LPSTR) szEntryName))
                    {
                        switch (nRet)
                        {
                            case ERROR_ALREADY_EXISTS:
                                // If entry already exists, warn user that original values
                                // will be overwritten
                                valid_entry = TRUE;
                                wsprintf(szTemp, "Entry name %s already exists, will overwrite!", szEntryName);
                                iItem = MessageBox(hWnd, szTemp, "Warning!!!", MB_YESNO | MB_ICONWARNING);
                                if (iItem == IDNO)
                                    return 0;
                                break;
                            case ERROR_INVALID_NAME:
                                valid_entry = FALSE;
                                wsprintf(szTemp, "Entry name %s is invalid", szEntryName);
                                MessageBox(hWnd, szTemp, NULL, MB_OK | MB_ICONERROR);
                                return 0;
                                break;
                        }
                    }
                    else
                        valid_entry = TRUE;
                    if (IsDlgButtonChecked(hWnd, IDC_ECAC) == BST_CHECKED)
                        // Enable the UseCountryAndAreaCodes flag
                    {
                        lpRasEntry->dwfOptions |= RASEO_UseCountryAndAreaCodes;
                        // Get the country name and code
						wp = SendMessage(hComboBox2, CB_GETCURSEL, 0, 0);
                        SendMessage(hComboBox2, CB_GETLBTEXT, wp, (LPARAM) (LPCSTR) szTemp);
                        lstrcpy(szCCode, szTemp);
                        k = 0;
                        // Store the country name in a buffer
                        while (szCCode[k] != '(')
                            k++;
                        szCCode[k - 1] = '\0';
                        k++;
                        i = 0;
                        // Store the country code in another buffer
                        while (szTemp[k] != ')')
                        {
                            szCName[i] = szTemp[k];
                            i++;
                            k++;
                        }
                        szCName[i] = '\0';
                        // Convert the country code string to an integer
                        j = atoi(szCName);
                        lpRasCtryInfo->dwSize = sizeof(RASCTRYINFO);
                        lpRasCtryInfo->dwCountryID = 1;
                        // Obtain the country ID by using RasGetCountryInfo
                        while (lpRasCtryInfo->dwCountryID)
                        {
                            lpRasCtryInfo->dwSize = sizeof(RASCTRYINFO);
                            Size = 256;
                            if (nRet = RasGetCountryInfo(lpRasCtryInfo, &Size))
                            {
                                wsprintf(szTemp, "RasGetCountryInfo failed: %d", nRet);
                                MessageBox(hWnd, szTemp, NULL, MB_OK | MB_ICONERROR);
                                return -1;
                            }
                            if ((lstrcmp(szCCode, (LPSTR) lpRasCtryInfo + lpRasCtryInfo->dwCountryNameOffset)) == 0)
                            {
                                lpRasEntry->dwCountryCode = lpRasCtryInfo->dwCountryCode;
                                lpRasEntry->dwCountryID = lpRasCtryInfo->dwCountryID;
                                break;
                            }
                            lpRasCtryInfo->dwCountryID = lpRasCtryInfo->dwNextCountryID;

                        }
                    }
                    else
                        lpRasEntry->dwfOptions &= ~RASEO_UseCountryAndAreaCodes;

                    // Get the device chosen from the combo box
					wp = SendMessage(hComboBox, CB_GETCURSEL, 0, 0);
                    SendMessage(hComboBox, CB_GETLBTEXT, wp, (LPARAM) (LPCSTR) lpRasEntry->szDeviceName);
                    for (i = 0; i < GlobalTemp; i++)
                    {
                        if (!(lstrcmp(RasDevInfo[i].szDeviceName, lpRasEntry->szDeviceName)))
                            lstrcpy(lpRasEntry->szDeviceType, RasDevInfo[i].szDeviceType);

                    }
                    // Set the properties of the phonebook entry using
                    // RasSetEntryProperties

                    if (nRet = RasSetEntryProperties(NULL, (LPSTR) szEntryName, lpRasEntry, lpRasEntry->dwSize, NULL, 0))
                    {
                        wsprintf(szTemp, "RasSetEntryProperties  failed: %d", nRet);
                        MessageBox(hWnd, szTemp, NULL, MB_OK | MB_ICONERROR);
                    }

                    return TRUE;

                default:
                    break;
            }
            break;

        default:
            break;
            // PropertySheet_Changed(hSheet,hWnd);
    }

    return 0;
}

//
//  FUNCTION: Page1_Proc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Intialized Page 1 of the property sheet.
//
//  PARAMETERS:
//    hwnd     - window handle
//    uMessage - message number
//    wparam   - additional information (dependant on message number)
//    lparam   - additional information (dependant on message number)
//
//  RETURN VALUE:
//			Returns 0.
//
//  COMMENTS:
//		This function handles the dialog box on the first page (Server) of the
//		property sheet.
//		The dialog box allows the user to enter the dial up server type.
//		There are three options to choose from. It further allows the user to
//		choose the Network Protocols, namely, TCP/IP, NetBEUI or IPX/SPX.
//		Finally it allows the user to enable Software Compression and PPP LCP
//		extensions.
//
//		The following fields of the RASENTRY structure are modified
//
//		lpRasEntry->dwfNetProtocols
//		lpRasEntry->dwFramingProtocol
//
//		The following flags in the lpRasEntry->dwfOptions are modified
//
//		RASEO_SwCompression
//		RASEO_DisableLcpExtensions
//

INT_PTR CALLBACK Page1Proc(HWND hWnd, UINT uMsgID, WPARAM wParam, LPARAM lParam)
{
    static HWND hComboBox;
    static HWND hCheckBox1;
    static HWND hCheckBox2;
    static HWND hCheckBox3;
    static HWND hCheckBox4;
    static HWND hCheckBox5;
    static HWND hButton;
    int i;

// Initialize the various controls
    hComboBox = GetDlgItem(hWnd, IDC_COMBO2);
    hCheckBox1 = GetDlgItem(hWnd, IDC_CHECK1);
    hCheckBox2 = GetDlgItem(hWnd, IDC_CHECK2);
    hCheckBox3 = GetDlgItem(hWnd, IDC_CHECK3);
    hCheckBox4 = GetDlgItem(hWnd, IDC_CHECK4);
    hCheckBox5 = GetDlgItem(hWnd, IDC_CHECK5);
    hButton = GetDlgItem(hWnd, IDC_BUTTON1);

    switch (uMsgID)
    {
        case WM_INITDIALOG:
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM) "PPP: Windows NT, Windows 95 Plus, Internet");
            SendMessage(hComboBox, CB_ADDSTRING, 1, (LPARAM) "SLIP: Internet");
            SendMessage(hComboBox, CB_ADDSTRING, 2, (LPARAM) "Windows NT 3.1, Windows for Workgroups 3.11");
            if (flag)           // Phonebook entry exists
            {                   // Display the entry's parameters
                if (lpRasEntry->dwfOptions & RASEO_SwCompression)
                    CheckDlgButton(hWnd, IDC_CHECK4, BST_CHECKED);
                if (lpRasEntry->dwfOptions & RASEO_DisableLcpExtensions)
                    CheckDlgButton(hWnd, IDC_CHECK5, BST_CHECKED);
                switch (lpRasEntry->dwFramingProtocol)
                {
                    case RASFP_Ppp:
                        SendMessage(hComboBox, CB_SETCURSEL, 0, 0);
                        break;
                    case RASFP_Slip:
                        SendMessage(hComboBox, CB_SETCURSEL, 1, 0);
                        break;
                    case RASFP_Ras:
                        SendMessage(hComboBox, CB_SETCURSEL, 2, 0);
                        break;
                    default:
                        break;
                }
                if (lpRasEntry->dwfNetProtocols & RASNP_Ip)
                    CheckDlgButton(hWnd, IDC_CHECK1, BST_CHECKED);
                if (lpRasEntry->dwfNetProtocols & RASNP_Ipx)
                    CheckDlgButton(hWnd, IDC_CHECK3, BST_CHECKED);
                if (lpRasEntry->dwfNetProtocols & RASNP_NetBEUI)
                    CheckDlgButton(hWnd, IDC_CHECK2, BST_CHECKED);
            }
            else
            {                   // Display default parameters
                SendMessage(hComboBox, CB_SETCURSEL, 0, 0);
                CheckDlgButton(hWnd, IDC_CHECK5, BST_CHECKED);
                CheckDlgButton(hWnd, IDC_CHECK1, BST_CHECKED);
            }
            break;
        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                case IDC_BUTTON1:   // TCP/IP Settings Button pressed
                    DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG7), hWnd, Dlg_Proc1);
                    break;
                case IDC_COMBO2:// Framing Protocol settings
                    i = (int)SendMessage(hComboBox, CB_GETCURSEL, 0, 0);
                    switch (i)
                    {
                        case 0: // PPP

                            CheckDlgButton(hWnd, IDC_CHECK1, BST_CHECKED);
                            CheckDlgButton(hWnd, IDC_CHECK5, BST_CHECKED);
                            EnableWindow(hCheckBox1, TRUE);
                            EnableWindow(hCheckBox2, TRUE);
                            EnableWindow(hCheckBox3, TRUE);
                            EnableWindow(hCheckBox4, TRUE);
                            EnableWindow(hCheckBox5, TRUE);
                            EnableWindow(hButton, TRUE);
                            break;
                        case 1: // Slip
                            EnableWindow(hCheckBox1, TRUE);
                            CheckDlgButton(hWnd, IDC_CHECK1, BST_CHECKED);
                            if (IsDlgButtonChecked(hWnd, IDC_CHECK2))
                                CheckDlgButton(hWnd, IDC_CHECK2, BST_UNCHECKED);
                            if (IsDlgButtonChecked(hWnd, IDC_CHECK3))
                                CheckDlgButton(hWnd, IDC_CHECK3, BST_UNCHECKED);
                            if (IsDlgButtonChecked(hWnd, IDC_CHECK4))
                                CheckDlgButton(hWnd, IDC_CHECK4, BST_UNCHECKED);
                            if (IsDlgButtonChecked(hWnd, IDC_CHECK5))
                                CheckDlgButton(hWnd, IDC_CHECK5, BST_UNCHECKED);
                            EnableWindow(hCheckBox2, FALSE);
                            EnableWindow(hCheckBox3, FALSE);
                            EnableWindow(hCheckBox4, FALSE);
                            EnableWindow(hCheckBox5, FALSE);
                            EnableWindow(hButton, TRUE);
                            break;
                        case 2: // Microsoft proprietary protocol
                            if (IsDlgButtonChecked(hWnd, IDC_CHECK1))
                                CheckDlgButton(hWnd, IDC_CHECK1, BST_UNCHECKED);
                            if (IsDlgButtonChecked(hWnd, IDC_CHECK3))
                                CheckDlgButton(hWnd, IDC_CHECK3, BST_UNCHECKED);
                            if (IsDlgButtonChecked(hWnd, IDC_CHECK5))
                                CheckDlgButton(hWnd, IDC_CHECK5, BST_UNCHECKED);
                            EnableWindow(hCheckBox1, FALSE);
                            EnableWindow(hCheckBox2, TRUE);
                            EnableWindow(hCheckBox3, FALSE);
                            EnableWindow(hCheckBox4, TRUE);
                            EnableWindow(hCheckBox5, FALSE);
                            EnableWindow(hButton, FALSE);
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
            break;
        case WM_NOTIFY:
            switch (((LPNMHDR) lParam)->code)
            {
                case PSN_KILLACTIVE:
                    i = (int)SendMessage(hComboBox, CB_GETCURSEL, 0, 0);
                    switch (i)  // Set framing protocol based on the
                    {           // value returned from the combo box
                        case 0:
                            lpRasEntry->dwFramingProtocol = RASFP_Ppp;
                            break;
                        case 1:
                            lpRasEntry->dwFramingProtocol = RASFP_Slip;
                            break;
                        case 2:
                            lpRasEntry->dwFramingProtocol = RASFP_Ras;
                            break;
                        default:
                            lpRasEntry->dwFramingProtocol = RASFP_Ppp;
                            break;
                    }
                    if (IsDlgButtonChecked(hWnd, IDC_CHECK4) == BST_CHECKED)
                        // Enable the SwCompression flag
                        lpRasEntry->dwfOptions |= RASEO_SwCompression;
                    else        // Disable the SwCompression flag
                        lpRasEntry->dwfOptions &= ~RASEO_SwCompression;
                    if (IsDlgButtonChecked(hWnd, IDC_CHECK1) == BST_CHECKED)
                        // Enable Ip Net Protocol
                        lpRasEntry->dwfNetProtocols |= RASNP_Ip;
                    else        // Disable Ip Net Protocol
                        lpRasEntry->dwfNetProtocols &= ~RASNP_Ip;
                    if (IsDlgButtonChecked(hWnd, IDC_CHECK2) == BST_CHECKED)
                        // Enable NetBEUI Net Protocol
                        lpRasEntry->dwfNetProtocols |= RASNP_NetBEUI;
                    else        // Disable NetBEUI Net Protocol
                        lpRasEntry->dwfNetProtocols &= ~RASNP_NetBEUI;
                    if (IsDlgButtonChecked(hWnd, IDC_CHECK3) == BST_CHECKED)
                        // Enable Ipx Net Protocol
                        lpRasEntry->dwfNetProtocols |= RASNP_Ipx;
                    else        // Disable Ipx Net Protocol
                        lpRasEntry->dwfNetProtocols &= ~RASNP_Ipx;
                    if (IsDlgButtonChecked(hWnd, IDC_CHECK5) == BST_UNCHECKED)
                        // Enable the DisableLcpExtensions flag
                        lpRasEntry->dwfNetProtocols |= RASEO_DisableLcpExtensions;
                    else        // Disable the DisableLcpExtensions flag
                        lpRasEntry->dwfNetProtocols &= ~RASEO_DisableLcpExtensions;
                    return TRUE;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    return 0;
}

//
//  FUNCTION: Page2_Proc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Intialized Page 2 of the property sheet.
//
//  PARAMETERS:
//    hwnd     - window handle
//    uMessage - message number
//    wparam   - additional information (dependant on message number)
//    lparam   - additional information (dependant on message number)
//
//  RETURN VALUE:
//			Returns 0.
//
//  COMMENTS:
//		This function handles the dialog box on the second page (Script) of the
//		property sheet.
//		The dialog box allows the user to enter the name of script that they
//		want to run after dialing. The user can also enable a Terminal Window
//		to show up after dialing.
//
//		The following field of the RASENTRY structure is modified
//
//		lpRasEntry->szScript
//
//		The following flag in the lpRasEntry->dwfOptions is modified
//
//		RASEO_TerminalAfterDial
//

INT_PTR CALLBACK Page2Proc(HWND hWnd, UINT uMsgID, WPARAM wParam, LPARAM lParam)
{
    static HWND hEdit1;

// Initialize the various controls
    hEdit1 = GetDlgItem(hWnd, IDC_EDIT1);

    switch (uMsgID)
    {
        case WM_INITDIALOG:
            if (flag)           // Phonebook entry exists
            {                   // Display the parameters of the entry
                if (lpRasEntry->dwfOptions & RASEO_TerminalAfterDial)
                {
                    CheckRadioButton(hWnd, IDC_RADIO1, IDC_RADIO3, IDC_RADIO3);
                    EnableWindow(hEdit1, FALSE);
                }
                else
                {
                    if ((strcmp(lpRasEntry->szScript, "")) != 0)
                    {
                        CheckRadioButton(hWnd, IDC_RADIO1, IDC_RADIO3, IDC_RADIO2);
                        EnableWindow(hEdit1, TRUE);
                        SendMessage(hEdit1, WM_SETTEXT, 0, (LPARAM) (LPCTSTR) lpRasEntry->szScript);
                    }
                    else
                    {
                        CheckRadioButton(hWnd, IDC_RADIO1, IDC_RADIO3, IDC_RADIO1);
                        EnableWindow(hEdit1, FALSE);
                    }
                }
            }
            else
            {                   // Display default parametrs
                CheckRadioButton(hWnd, IDC_RADIO1, IDC_RADIO3, IDC_RADIO1);
                EnableWindow(hEdit1, FALSE);
            }
            break;
        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                case IDC_RADIO1:// Disable the edit box for holding the script name
                case IDC_RADIO3:
                    EnableWindow(hEdit1, FALSE);
                    break;
                case IDC_RADIO2:// Enable the edit box for holding the script name
                    EnableWindow(hEdit1, TRUE);
                    break;
                default:
                    break;
            }
            break;
        case WM_NOTIFY:
            switch (((LPNMHDR) lParam)->code)
            {
                case PSN_KILLACTIVE:
                    if (IsDlgButtonChecked(hWnd, IDC_RADIO3))
                        // Enable the TerminalAfterDial flag
                        lpRasEntry->dwfOptions |= RASEO_TerminalAfterDial;
                    else        // Disable the TerminalAfterDial flag
                        lpRasEntry->dwfOptions &= ~RASEO_TerminalAfterDial;
                    if (IsDlgButtonChecked(hWnd, IDC_RADIO2))
                    {           // Get the script name from the edit box
                        GetWindowText(GetDlgItem(hWnd, IDC_EDIT1), lpRasEntry->szScript, 256);
                    }
                    else        // Corresponds to "None"
                        strcpy(lpRasEntry->szScript, "");

                    return TRUE;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    return 0;
}


//
//  FUNCTION: PropSheet()
//
//  PURPOSE:  Intialized Property Sheet.
//
//  PARAMETERS:
//		none
//
//  RETURN VALUE:
//		Returns 0.
//
//  COMMENTS:
//		This function defines and initializes the property sheet.
//

BOOL CALLBACK PropSheet(HWND hWnd)
{
    // Build property sheet
    PROPSHEETHEADER pshSheet;
    PROPSHEETPAGE pspPage[3];


    ZeroMemory(&pshSheet, sizeof(PROPSHEETHEADER));

    // Sheet
    pshSheet.dwSize = sizeof(PROPSHEETHEADER);
    pshSheet.dwFlags = PSH_PROPSHEETPAGE | PSH_NOAPPLYNOW;
    pshSheet.hwndParent = hWnd;
    pshSheet.hInstance = hInstance;
    pshSheet.pszCaption = "EditPhonebookEntries";
    pshSheet.nPages = 3;
    pshSheet.ppsp = pspPage;

    ZeroMemory(&pspPage, sizeof(PROPSHEETPAGE) * 3);

    // Page 0
    pspPage[0].dwSize = sizeof(PROPSHEETPAGE);
    pspPage[0].hInstance = hInstance;
    pspPage[0].pszTemplate = MAKEINTRESOURCE(IDD_DIALOG2);
    pspPage[0].pfnDlgProc = Page0Proc;

    // Page 1
    pspPage[1].dwSize = sizeof(PROPSHEETPAGE);
    pspPage[1].hInstance = hInstance;
    pspPage[1].pszTemplate = MAKEINTRESOURCE(IDD_DIALOG3);
    pspPage[1].pfnDlgProc = Page1Proc;

    // Page 2
    pspPage[2].dwSize = sizeof(PROPSHEETPAGE);
    pspPage[2].hInstance = hInstance;
    pspPage[2].pszTemplate = MAKEINTRESOURCE(IDD_DIALOG4);
    pspPage[2].pfnDlgProc = Page2Proc;





    hSheet = (HWND) PropertySheet(&pshSheet);

    return 0;
}


//
//  FUNCTION: WinMain(HWND, UINT, WPARAM, LPARAM)
//
//
//  PARAMETERS:
//    hwnd     - window handle
//    uMessage - message number
//    wparam   - additional information (dependant on message number)
//    lparam   - additional information (dependant on message number)
//
//  RETURN VALUE:
//		Returns the main dialog box which lists all the available phone
//		book entries.
//

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    return
    (int)DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, Dlg_Proc2);

}

//
//  FUNCTION: Dlg_Proc2(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Display a list of available phone book entries and
//			  allow user to modify it or enter a new entry to the phone book
//
//  PARAMETERS:
//    hwnd     - window handle
//    uMessage - message number
//    wparam   - additional information (dependant on message number)
//    lparam   - additional information (dependant on message number)
//
//  RETURN VALUE:
//			Returns 0.
//
//  COMMENTS:
//		This function displays the dialog box that contains a list of existing
//		phonebook entries. The user can either modify these entries or enter
//		values for a new entry.
//
//		RAS API's used
//
//		RasEnumEntries(): To enumerate the list of the phone book entries
//		RasGetEntryProperties(): To get the properties of an existing entry
//

INT_PTR CALLBACK Dlg_Proc2(HWND hWnd, UINT uMsgID, WPARAM wParam, LPARAM lParam)
{
    int i;
    char szTemp[256];
    DWORD nRet;
    LPRASENTRYNAME lpRasEntryName;
    DWORD cbEntry = sizeof(RASENTRYNAME);
    DWORD cEntries = 0;
    static HWND hComboBox;
    DWORD RasEntryInfoSize = 0;
	WPARAM wp;

    hComboBox = GetDlgItem(hWnd, IDC_COMBO1);




    switch (uMsgID)
    {
        case WM_INITDIALOG:
            // Enumerate all the phonebook entries using RasEnumEntries

            lpRasEntryName = (LPRASENTRYNAME) GlobalAlloc(GPTR, sizeof(RASENTRYNAME));
            lpRasEntryName->dwSize = sizeof(RASENTRYNAME);
            if ((nRet = RasEnumEntries(NULL, NULL, lpRasEntryName,
                        &cbEntry, &cEntries)) == ERROR_BUFFER_TOO_SMALL)
            {
                lpRasEntryName = (LPRASENTRYNAME) GlobalAlloc(GPTR, cbEntry);
                lpRasEntryName->dwSize = sizeof(RASENTRYNAME);
                if (nRet = RasEnumEntries(NULL, NULL, lpRasEntryName,
                        &cbEntry, &cEntries))
                {
                    wsprintf(szTemp, "RasEnumEntries  failed: %d", nRet);
                    MessageBox(hWnd, szTemp, NULL, MB_OK | MB_ICONERROR);
                    return 0;
                }
            }


            if (cEntries)
            {
                tEntries = cEntries;
                for (i = 0; i < (int) cEntries; i++)
                {
                    SendMessage(hComboBox, CB_ADDSTRING, i,
                        (LPARAM) (LPCTSTR) lpRasEntryName->szEntryName);
                    lpRasEntryName++;
                }
                SendMessage(hComboBox, CB_SETCURSEL, 0, 0);
                SendMessage(hComboBox, CB_GETLBTEXT, 0, (LPARAM) (LPCSTR) szEntryName);
            }
            else
                SendMessage(hComboBox, CB_SETCURSEL, 0, 0);
            break;
        case WM_CLOSE:
            EndDialog(hWnd, 0);
            break;
        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                case IDOK:
                    EndDialog(hWnd, 0);
                    break;
                case IDNEW:
                    flag = FALSE;
                    lpRasEntry = GlobalAlloc(GPTR, sizeof(RASENTRY));
                    lpRasEntry->dwSize = sizeof(RASENTRY);
                    PropSheet(hWnd);
                    if (valid_entry)
                    {
                        SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM) (LPCSTR) szEntryName);
						wp = SendMessage(hComboBox, CB_FINDSTRINGEXACT, 0, (LPARAM) (LPCTSTR) szEntryName);
                        SendMessage(hComboBox, CB_SETCURSEL, wp, 0);
                        tEntries++;
                    }
                    GlobalFree(lpRasEntry);
                    break;
                case IDCHANGE:
                    if (tEntries)
                    {
                        wp = SendMessage(hComboBox, CB_GETCURSEL, 0, 0);
                        SendMessage(hComboBox, CB_GETLBTEXT, wp, (LPARAM) (LPCSTR) szEntryName);
                        // Initialize the RasEntryInfoSize parameter
                        if ((nRet = RasGetEntryProperties(NULL,
                                    szEntryName,
                                    NULL,
                                    &RasEntryInfoSize,
                                    NULL,
                                    0)) != ERROR_BUFFER_TOO_SMALL)
                        {
                            wsprintf(szTemp, "RasGetEntryProperty failed: %d", nRet);
                            MessageBox(hWnd, szTemp, NULL, MB_OK | MB_ICONERROR);
                        }

                        if (RasEntryInfoSize > 0)
                        {
                            lpRasEntry = (LPRASENTRY) GlobalAlloc(GPTR, RasEntryInfoSize);
                            lpRasEntry->dwSize = RasEntryInfoSize;
                        }
                        else
                            lpRasEntry = NULL;
                        // Retrieve the properties of the phonebook entry using
                        // RasGetEntryProperties
                        if (nRet = RasGetEntryProperties(NULL,
                                szEntryName,
                                lpRasEntry,
                                &RasEntryInfoSize,
                                NULL,
                                0))
                        {
                            wsprintf(szTemp, "RasGetEntryProperty failed: %d", nRet);
                            MessageBox(hWnd, szTemp, NULL, MB_OK | MB_ICONERROR);
                        }
                        else
                        {
                            flag = TRUE;    // Flag to indicate phonebook entry exists
                            PropSheet(hWnd);
                        }
                        GlobalFree(lpRasEntry);
                    }
                    break;
                case IDC_COMBO1:
					wp = SendMessage(hComboBox, CB_GETCURSEL, 0, 0);
                    SendMessage(hComboBox, CB_GETLBTEXT, wp, (LPARAM) (LPCSTR) szEntryName);
                    break;
            }
            break;
    }
    return 0;
}