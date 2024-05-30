/*++

Copyright (c) 1995 Intel Corp

Module Name:

    dialog.c

Abstract:

    Contains dialog-box procedures for the WinSock2 Chat sample
    application.  See ws2chat.rc for the actual resource script.

--*/

#include "nowarn.h"  /* turn off benign warnings */
#ifndef _WINSOCKAPI_
#define _WINSOCKAPI_   /* Prevent inclusion of winsock.h in windows.h */
#endif

#include <windows.h>
#include "nowarn.h"  /* some warnings may have been turned back on */
#include <ws2atm.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "ws2chat.h"
#include "chatsock.h"
#include "chatdlg.h"
#include "resource.h"





LRESULT APIENTRY
ChooseFamilyDlgProc(
    IN HWND DialogWindow,
    IN UINT Message,
    IN WPARAM WParam,
    IN LPARAM LParam)
/*++

Routine Description:

    Callback function that processes messages sent to the 'Choose
    Family' dialog box.

Implementation

    This dialog box is used to query the user as to which supported
    protocol he wishes to use for the chat connection he wishes to
    make.  The available protocols are listed in the IDC_FAM_LB
    listbox via the FillInFamilies function in socket.c.

    It is expected that this dialog box gets the WM_INITDIALOG
    message with a LParam that is a pointer to the CONNDATA structure
    for the impending connection.  The result of this function is that
    the ProtocolInfo field of the ConnData struct is filled with a
    pointer to the protocol information structure the user chose in
    the listbox.

Arguments:

    DialogWindow - Supplies handle of the dialog box.

    Message - Supplies the message identifier

    WParam - Supplies the first message parameter

    LParam - Supplies the second message parameter

Return Value:

    TRUE -- This function handled the message.

    FALSE -- This function did not handle the message.

--*/
{
    int              LBIndex;         // index of the item chosen
    static PCONNDATA ConnData = NULL; // connection-specific data

    switch (Message) {

    case WM_INITDIALOG:

        // Get the parameter and fill in the listbox with the
        // available protocols.
        ConnData = (PCONNDATA)LParam;
        assert(ConnData != NULL);
        if (!FillInFamilies(DialogWindow, IDC_FAM_LB)) {
            MessageBox(DialogWindow, "FillInFamilies failed.", "Error.",
                        MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
            EndDialog(DialogWindow, FALSE);
        }

        return(TRUE);

    case WM_COMMAND:

        switch (WParam) {

        case IDOK:

            // Get the index of the listbox item the user has chosen.
            LBIndex = (int)SendMessage(GetDlgItem(DialogWindow, IDC_FAM_LB),
                                  LB_GETCURSEL, 0, 0);
            if (LBIndex == LB_ERR) {

                // Nothing was selected.
                MessageBox(DialogWindow, "Choose an item, or hit cancel.",
                           "No Selection?",
                           MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
                return(TRUE);
            }

            // Get the protocol associated with the listbox item the
            // user selected.
            ConnData->ProtocolInfo = GetProtoFromIndex(LBIndex);
            assert(ConnData->ProtocolInfo != NULL);
            EndDialog(DialogWindow, TRUE);
            return(TRUE);

        case IDCANCEL:

            // Kill the dialog box.
            EndDialog(DialogWindow, FALSE);
            return(TRUE);

        default:

            return(FALSE);
        } // switch (WParam)

    default:

        return(FALSE);
    } // switch (Message)

} // ChooseFamilyDlgProc()




LRESULT APIENTRY
InetConnDlgProc(
    IN HWND DialogWindow,
    IN UINT Message,
    IN WPARAM WParam,
    IN LPARAM LParam)

/*++

Routine Description:

    Callback function that processes messages sent to the internet
    connection info dialog box.

Implementation

    This dialog box gets two strings from the user: the internet
    address and port to which she wants to make a chat connection.
    When the user clicks on the OK button, these two strings are
    converted into a sockaddr_in structure and a pointer to this
    structure is saved in the connection window's CONNDATA structure.

    NOTE: No name resolution takes place here!  The address edit
    control expects up to 15 characters, and this string is expected
    to be in.dotted.decimal.notation.  When RNR is available, this is
    where it would be called upon to provide the appropriate
    sockaddr_in structure.  Actually, this dialog box would be
    replaced with a protocol independent name dialog box; RNR would do
    all the rest...

Arguments:

    DialogWindow - Supplies handle of the dialog box.

    Message - Supplies the message identifier

    WParam - Supplies the first message parameter

    LParam - Supplies the second message parameter

Return Value:

    TRUE -- This function handled the message.

    FALSE -- This function did not handle the message; or the message
    was WM_INITDIALOG and we set the focus.

--*/

{
    char               PortText[INET_PORT_LEN + 1];   // holds port string
    char               AddressText[INET_ADDR_LEN + 1];// holds addr string
    static PCONNDATA   ConnData = NULL;               // conn-specific data
    struct sockaddr_in *SockAddrInet;                 // Inet socket address
    u_long             InetAddr;                      // Inet-style address
    u_short            InetPort;                      // Inet-style port
    int                Port;                          // intermediate var.
    BOOL               PortStringTranslated;          // for GetDlgItemInt
    struct hostent *host;

    switch (Message) {

    case WM_INITDIALOG:

        // Get the connection data pointer, initialize the dialog box.
        ConnData = (PCONNDATA)LParam;
        assert(ConnData != NULL);
        SendMessage(GetDlgItem(DialogWindow, IDC_INET_ADDRESS),
                    EM_LIMITTEXT, (WPARAM)INET_ADDR_LEN, 0);
        SendMessage(GetDlgItem(DialogWindow, IDC_INET_PORT),
                    EM_LIMITTEXT, (WPARAM)INET_PORT_LEN, 0);
        wsprintf(PortText,"%d", INET_DEFAULT_PORT);
        SendMessage(GetDlgItem(DialogWindow, IDC_INET_PORT),
                    WM_SETTEXT, 0, (LPARAM)PortText);
        SetFocus(GetDlgItem(DialogWindow, IDC_INET_ADDRESS));
        return(FALSE);

    case WM_COMMAND:

        switch (WParam) {

        case IDOK:

            // The user has pressed the 'OK' button.  Extract the
            // internet address into a buffer and check the value the
            // user typed for the port.
            GetDlgItemText(DialogWindow,
                           IDC_INET_ADDRESS,
                           AddressText,
                           INET_ADDR_LEN);
            strcpy(ConnData->PeerAddress, AddressText);
            Port = (int)GetDlgItemInt(DialogWindow,
                                      IDC_INET_PORT,
                                      &PortStringTranslated,
                                      TRUE);
            if ((Port < 0) || (Port > 65535) || !PortStringTranslated) {
              MessageBox(DialogWindow,
                         "Please choose a port between 0 and 65535.",
                         "Bad Port.",
                         MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
                return(TRUE);
            }

            // Convert the address string to an unsigned long, and
            // convert the port integer to an unsigned short.  If all
            // goes well, fill in the fields and end the dialog box.
            // If not, inform the user and *don't* kill the dialog box.
            InetAddr = inet_addr(AddressText);
            if (InetAddr == INADDR_NONE) {
                host = gethostbyname(AddressText);
                if (host) {
                    InetAddr = *((u_long *)host->h_addr_list[0]);
                }
            }
            InetPort = (u_short)Port;
            if ((InetAddr != INADDR_NONE) && (InetAddr != 0)) {

                // Allocate memory for an internet-style socket address;
                // point ConnData->SockAddr at this memory, and
                // use a local pointer to a struct sockaddr_in to
                // reference the fields.
                ConnData->RemoteSockAddr.len = sizeof(struct sockaddr_in);
                ConnData->RemoteSockAddr.buf =
                  malloc(ConnData->RemoteSockAddr.len);
                if (ConnData->RemoteSockAddr.buf == NULL) {
                    ChatSysError("malloc()",
                                 "InetConnDlgProc()",
                                 TRUE);
                }

                SockAddrInet =
                  (struct sockaddr_in *)ConnData->RemoteSockAddr.buf;
                SockAddrInet->sin_family = AF_INET;
                SockAddrInet->sin_port = htons(InetPort);
                SockAddrInet->sin_addr.S_un.S_addr = InetAddr;
                EndDialog(DialogWindow, TRUE);
                return(TRUE);

            }

            MessageBox(DialogWindow,
                       "Invalid Internet address. Try again or cancel.",
                       "Error", MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
            return(TRUE);

        case IDCANCEL:

            // The user has pressed cancel.  Kill the dialog box.
            EndDialog(DialogWindow, FALSE);
            return(TRUE);

        default:

            break;
        } // switch (WParam)

        break;
    } // switch (Message)

    return(FALSE);
} // InetConnDlgProc()


VOID ShowMessage(
    HWND hWnd,
    PSTR pMsg)
    /*
    Routine Description:
            Just pop up an error message box.
    */
{
    MessageBox(NULL, pMsg, "WS2Test", MB_OK);
} // ShowMessage


BOOL ScanAtmAddress(
    HWND        hWndDlg,
    ATM_ADDRESS *pAtmAddr)
    /*
        Routine Description:
            Scanner of ATM Address af a field of ATM socket address.
    */
{
    UCHAR textBuf[MAX_ADDRESS_TEXT];
    UINT value[ATM_ADDR_LENGTH];     // for sscanf
    DWORD length;
    int scanResult;
    UINT i;
    HWND hWndControl;
    UINT selection;

    hWndControl = GetDlgItem(hWndDlg, IDC_ADDR_TYPE);
    selection = ListBox_GetCurSel(hWndControl);
    pAtmAddr->AddressType = AtmAddrTypeValue[selection];

    length = GetDlgItemText(hWndDlg, IDC_ATM_ADDR, textBuf, sizeof(textBuf));
    if (pAtmAddr->AddressType == ATM_E164)
    {
        memcpy(pAtmAddr->Addr, textBuf, length);
        pAtmAddr->NumofDigits = length;
    }
    else if (pAtmAddr->AddressType != SAP_FIELD_ANY)
    {
        scanResult = sscanf(
            textBuf,
            "%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x",
            &value[0], &value[1], &value[2], &value[3], &value[4],
            &value[5], &value[6], &value[7], &value[8], &value[9],
            &value[10], &value[11], &value[12], &value[13], &value[14],
            &value[15], &value[16], &value[17], &value[18], &value[19]);
        if (scanResult != ATM_ADDR_LENGTH)
        {
            ShowMessage(hWndDlg, "Invalid value for ATM address.");
            return FALSE;
        } // if
        for (i = 0; i < ATM_ADDR_LENGTH; i++)
        {
            pAtmAddr->Addr[i] = (UCHAR)value[i];
        }
        pAtmAddr->NumofDigits = ATM_ADDR_LENGTH;
    }

    return TRUE;

} // ScanAtmAddress



BOOL ScanAtmBlli(
    HWND hWndDlg,
    ATM_BLLI *pBLLI)
    /*
        Routine Description:
            Scanner of BLLI af a field of ATM socket address.
    */
{
    UCHAR textBuf[MAX_PARSE_TEXT];
    UINT value[ATM_SNAP_ID_LENGTH];
    HWND hWndControl;
    UINT selection;
    UINT length;
    int scanResult;
    UINT i;

    hWndControl = GetDlgItem(hWndDlg, IDC_L2PROTO);
    selection = ListBox_GetCurSel(hWndControl);
    pBLLI->Layer2Protocol = AtmBlliL2ProtoValue[selection];

    length = GetDlgItemText(hWndDlg, IDC_L2USER_PROTO, textBuf, sizeof(textBuf));
    if (length != 0)
    {
        if (sscanf(textBuf, "%u", &value[0]) != 1)
        {
            ShowMessage(hWndDlg, "Invalid value for user specified layer 2 protocol info.");
            return FALSE;
        } // if
        else
        {
            pBLLI->Layer2UserSpecifiedProtocol = value[0];
        }
    }
    else
    {
        pBLLI->Layer2UserSpecifiedProtocol = SAP_FIELD_ABSENT;
    }

    hWndControl = GetDlgItem(hWndDlg, IDC_L3PROTO);
    selection = ListBox_GetCurSel(hWndControl);
    pBLLI->Layer3Protocol = AtmBlliL3ProtoValue[selection];

    length = GetDlgItemText(hWndDlg, IDC_L3USER_PROTO, textBuf, sizeof(textBuf));
    if (length != 0)
    {
        if (sscanf(textBuf, "%u", &value[0]) != 1)
        {
            ShowMessage(hWndDlg, "Invalid value for user specified layer 3 protocol info.");
            return FALSE;
        } // if
        else
        {
            pBLLI->Layer3UserSpecifiedProtocol = value[0];
        }
    }
    else
    {
        pBLLI->Layer3UserSpecifiedProtocol = SAP_FIELD_ABSENT;
    }

    hWndControl = GetDlgItem(hWndDlg, IDC_L3IPI);
    selection = ListBox_GetCurSel(hWndControl);
    pBLLI->Layer3IPI = AtmBlliL3IpiValue[selection];

    length = GetDlgItemText(hWndDlg, IDC_SNAP_ID, textBuf, sizeof(textBuf));
    if (length > 0)
    {
        scanResult = sscanf(
            textBuf,
            "%x.%x.%x.%x.%x",
            &value[0], &value[1], &value[2], &value[3], &value[4]);
        if (scanResult != ATM_SNAP_ID_LENGTH)
        {
            ShowMessage(hWndDlg, "Invalid value for SNAP ID.");
            return FALSE;
        } // if
        for (i = 0; i < ATM_SNAP_ID_LENGTH; i++)
        {
            pBLLI->SnapID[i] = (UCHAR)value[i];
        }
    }
    else
    {
        memset(pBLLI->SnapID, 0, ATM_SNAP_ID_LENGTH);
    }

    return TRUE;

} // ScanBlli



BOOL ScanAtmBhli(
    HWND hWndDlg,
    ATM_BHLI *pBHLI)
    /*
        Routine Description:
            Scanner of BHLI af a field of ATM socket address.
    */
{
    UCHAR textBuf[MAX_PARSE_TEXT];
    UCHAR value[ATM_HL_INFO_LENGTH];
    HWND hWndControl;
    UINT selection;
    UINT length;
    UINT i;
    int scanResult;

    hWndControl = GetDlgItem(hWndDlg, IDC_BHLI_TYPE);
    selection = ListBox_GetCurSel(hWndControl);
    pBHLI->HighLayerInfoType = AtmBhliTypeValue[selection];
    if (pBHLI->HighLayerInfoType != BHLI_UserSpecific) {
        ShowMessage(hWndDlg, "Please choose user specific for BHLI type.");
        return FALSE;
    }

    length = GetDlgItemText(hWndDlg, IDC_BHLI, textBuf, sizeof(textBuf));
    if (length != 0)
    {
        scanResult = sscanf(
            textBuf,
            "%c%c%c%c%c%c%c%c",
            &value[0], &value[1], &value[2], &value[3],
            &value[4], &value[5], &value[6], &value[7]);

        if ((scanResult != ATM_HL_INFO_LENGTH))
        {
            ShowMessage(hWndDlg, "High Layer Information is a string of 8 chars.");
            return FALSE;
        } // if
        pBHLI->HighLayerInfoLength = (DWORD)scanResult;
        for (i = 0; i < pBHLI->HighLayerInfoLength; i++)
        {
            pBHLI->HighLayerInfo[i] = value[i];
        }
    }
    else
    {
        pBHLI->HighLayerInfoLength = 0;
        memset(pBHLI->HighLayerInfo, 0, ATM_HL_INFO_LENGTH);
    }

    return TRUE;
} // ScanAtmBhli


int InitSelection(
    DWORD   InitValue,
    int     NumOfValues,
    DWORD * ValueList)
{
    int i;
    for (i=0; i<NumOfValues; i++) {
        if (InitValue == ValueList[i]) {
            return i;
        }
    }
    return -1;

}


LRESULT APIENTRY
ATMSockAddrProc(
    IN HWND DialogWindow,
    IN UINT Message,
    IN WPARAM WParam,
    IN LPARAM LParam)

/*++

Routine Description:

    Callback function that processes messages sent to the native ATM
    connection info dialog box.

Implementation

    This dialog box gets the ATM socket address for connection party.

Arguments:

    DialogWindow - Supplies handle of the dialog box.

    Message - Supplies the message identifier

    WParam - Supplies the first message parameter

    LParam - Supplies the second message parameter

Return Value:

    TRUE -- This function handled the message.

    FALSE -- This function did not handle the message; or the message
    was WM_INITDIALOG and we set the focus.

--*/

{

    static PCONNDATA   ConnData = NULL;               // conn-specific data
    HWND hListBox;
    int i;
    UCHAR textBuf[MAX_ERROR_TEXT];
    static struct sockaddr_atm * pATMSockAddr;
    UINT selection;

    switch (Message) {

        case WM_INITDIALOG:

            // Get the connection data pointer, initialize the dialog box.
            pATMSockAddr = (struct sockaddr_atm *)LParam;
            assert(pATMSockAddr != NULL);

            //Initialize ATM address type list box
            hListBox = GetDlgItem(DialogWindow, IDC_ADDR_TYPE);
            for (i = 0; i < NUM_ATM_ADDR_TYPES; i++)
            {
                ListBox_AddString(hListBox, AtmAddrTypeName[i]);
            }
            i = InitSelection(pATMSockAddr->satm_number.AddressType,
                                 NUM_ATM_ADDR_TYPES,
                                 AtmAddrTypeValue);
            if (i>=0) {
                ListBox_SetCurSel(hListBox, i);
            }

            if(AtmAddrTypeValue[i] == SAP_FIELD_ANY) {
                EnableWindow(GetDlgItem(DialogWindow, IDC_ATM_ADDR), FALSE);
            }
            else {
                //Initialize ATM address edit box
                sprintf(textBuf,
                    "%02x.%02x.%02x.%02x.%02x.%02x.%02x.%02x.%02x.%02x.%02x.%02x.%02x.%02x.%02x.%02x.%02x.%02x.%02x.%02x",
                    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
                SetDlgItemText(DialogWindow, IDC_ATM_ADDR, textBuf);
            }

            //Initialize Layer 2 protocol list box
            hListBox = GetDlgItem(DialogWindow, IDC_L2PROTO);
            for (i = 0; i < NUM_BLLI_L2PROTO; i++)
            {
                ListBox_AddString(hListBox, AtmBlliL2ProtoName[i]);
            }
            i = InitSelection(pATMSockAddr->satm_blli.Layer2Protocol,
                              NUM_BLLI_L2PROTO,
                              AtmBlliL2ProtoValue);
            if (i>=0) {
                ListBox_SetCurSel(hListBox, i);
            }
            if (AtmBlliL2ProtoValue[i] != BLLI_L2_USER_SPECIFIED) {
                EnableWindow(GetDlgItem(DialogWindow, IDC_L2USER_PROTO), FALSE);
            }

            //Initialize Layer 3 protocol list box
            hListBox = GetDlgItem(DialogWindow, IDC_L3PROTO);
            for (i = 0; i < NUM_BLLI_L3PROTO; i++)
            {
                ListBox_AddString(hListBox, AtmBlliL3ProtoName[i]);
            }
            i = InitSelection(pATMSockAddr->satm_blli.Layer3Protocol,
                              NUM_BLLI_L3PROTO,
                              AtmBlliL3ProtoValue);
            if (i>=0) {
                ListBox_SetCurSel(hListBox, i);
            }

            if (AtmBlliL3ProtoValue[i] != BLLI_L3_USER_SPECIFIED) {
                EnableWindow(GetDlgItem(DialogWindow, IDC_L3USER_PROTO), FALSE);
            }

            //Initialize Layer 3 IPI list box
            hListBox = GetDlgItem(DialogWindow, IDC_L3IPI);
            for (i = 0; i < NUM_BLLI_L3IPI; i++)
            {
                ListBox_AddString(hListBox, AtmBlliL3IpiName[i]);
            }
            i = InitSelection(pATMSockAddr->satm_blli.Layer3IPI,
                              NUM_BLLI_L3IPI,
                              AtmBlliL3IpiValue);
            if (i>=0) {
                ListBox_SetCurSel(hListBox, i);
            }

            if (AtmBlliL3IpiValue[i] != BLLI_L3_IPI_SNAP) {
                EnableWindow(GetDlgItem(DialogWindow, IDC_SNAP_ID), FALSE);
            }
            else {
                //Initialize SnapID edit control
                sprintf(textBuf, "%02x.%02x.%02x.%02x.%02x", 0,0,0,0,0);
                SetDlgItemText(DialogWindow, IDC_SNAP_ID, textBuf);
            }

            if (AtmBlliL3ProtoValue[i] != BLLI_L3_ISO_TR9577) {
                EnableWindow(GetDlgItem(DialogWindow, IDC_L3IPI), FALSE);
                EnableWindow(GetDlgItem(DialogWindow, IDC_SNAP_ID), FALSE);
            }

            //Initialize high layer info type list box
            hListBox = GetDlgItem(DialogWindow, IDC_BHLI_TYPE);
            for (i = 0; i < NUM_BHLI_TYPES; i++)
            {
                ListBox_AddString(hListBox, AtmBhliTypeName[i]);
            }
            i = InitSelection(pATMSockAddr->satm_bhli.HighLayerInfoType,
                              NUM_BHLI_TYPES,
                              AtmBhliTypeValue);
            if (i>=0) {
                ListBox_SetCurSel(hListBox, i);
            }

            if (AtmBhliTypeValue[i] == SAP_FIELD_ABSENT ||
                AtmBhliTypeValue[i] == SAP_FIELD_ANY) {
                EnableWindow(GetDlgItem(DialogWindow, IDC_BHLI), FALSE);
            }
            else {
                //Initialize high layer info edit control
                if (pATMSockAddr->satm_bhli.HighLayerInfoType == BHLI_UserSpecific) {
                    SetDlgItemText(DialogWindow, IDC_BHLI, ATM_DEFAULT_BHLI_INFO);
                }
            }

            return(FALSE);

        case WM_COMMAND:

            switch ((USHORT)WParam) {

                case IDC_ADDR_TYPE:
                    hListBox = GetDlgItem(DialogWindow, IDC_ADDR_TYPE);
                    selection = ListBox_GetCurSel(hListBox);
                    if (AtmAddrTypeValue[selection] != SAP_FIELD_ANY) {
                        EnableWindow(GetDlgItem(DialogWindow, IDC_ATM_ADDR), TRUE);
                    }
                    else {
                        EnableWindow(GetDlgItem(DialogWindow, IDC_ATM_ADDR), FALSE);
                    }
                    break;

                case IDC_L2PROTO:
                    hListBox = GetDlgItem(DialogWindow, IDC_L2PROTO);
                    selection = ListBox_GetCurSel(hListBox);
                    if (AtmBlliL2ProtoValue[selection] == BLLI_L2_USER_SPECIFIED) {
                        EnableWindow(GetDlgItem(DialogWindow, IDC_L2USER_PROTO), TRUE);
                    }
                    else {
                        EnableWindow(GetDlgItem(DialogWindow, IDC_L2USER_PROTO), FALSE);
                    }
                    break;

                case IDC_L3PROTO:
                    hListBox = GetDlgItem(DialogWindow, IDC_L3PROTO);
                    selection = ListBox_GetCurSel(hListBox);
                    if (AtmBlliL3ProtoValue[selection] == BLLI_L3_USER_SPECIFIED) {
                        EnableWindow(GetDlgItem(DialogWindow, IDC_L3USER_PROTO), TRUE);
                    }
                    else {
                        EnableWindow(GetDlgItem(DialogWindow, IDC_L3USER_PROTO), FALSE);
                    }
                    if (AtmBlliL3ProtoValue[selection] == BLLI_L3_ISO_TR9577) {
                        EnableWindow(GetDlgItem(DialogWindow, IDC_L3IPI), TRUE);
                        hListBox = GetDlgItem(DialogWindow, IDC_L3IPI);
                        selection = ListBox_GetCurSel(hListBox);
                        if (AtmBlliL3IpiValue[selection] == BLLI_L3_IPI_SNAP) {
                            EnableWindow(GetDlgItem(DialogWindow, IDC_SNAP_ID), TRUE);
                        }
                        else {
                            EnableWindow(GetDlgItem(DialogWindow, IDC_SNAP_ID), FALSE);
                        }
                    }
                    else {
                        EnableWindow(GetDlgItem(DialogWindow, IDC_L3IPI), FALSE);
                        EnableWindow(GetDlgItem(DialogWindow, IDC_SNAP_ID), FALSE);
                    }
                    break;

                case IDC_L3IPI:
                    hListBox = GetDlgItem(DialogWindow, IDC_L3IPI);
                    selection = ListBox_GetCurSel(hListBox);
                    if (AtmBlliL3IpiValue[selection] == BLLI_L3_IPI_SNAP) {
                        EnableWindow(GetDlgItem(DialogWindow, IDC_SNAP_ID), TRUE);
                    }
                    else {
                        EnableWindow(GetDlgItem(DialogWindow, IDC_SNAP_ID), FALSE);
                    }
                    break;

                case IDC_BHLI_TYPE:
                    hListBox = GetDlgItem(DialogWindow, IDC_BHLI_TYPE);
                    selection = ListBox_GetCurSel(hListBox);
                    if (AtmBhliTypeValue[selection] == SAP_FIELD_ABSENT ||
                        AtmBhliTypeValue[selection] == SAP_FIELD_ANY) {
                        EnableWindow(GetDlgItem(DialogWindow, IDC_BHLI), FALSE);
                    }
                    else {
                        EnableWindow(GetDlgItem(DialogWindow, IDC_BHLI), TRUE);
                    }
                    break;

                case IDOK:
                    if ((ScanAtmAddress(DialogWindow, &pATMSockAddr->satm_number)) &&
                        (ScanAtmBlli(DialogWindow, &pATMSockAddr->satm_blli)) &&
                        (ScanAtmBhli(DialogWindow, &pATMSockAddr->satm_bhli)))
                    {
                        pATMSockAddr->satm_family = AF_ATM;
                        EndDialog(DialogWindow, TRUE);
                        return TRUE;
                    }

                    return FALSE;

                case IDCANCEL:

                    // The user has pressed cancel.  Kill the dialog box.
                    EndDialog(DialogWindow, FALSE);
                    return(TRUE);

            default:

                break;
            } // switch (WParam)

            break;
    } // switch (Message)

    return(FALSE);
} // ATMSockAddrProc()




LRESULT APIENTRY
DefaultConnDlgProc(
    IN HWND DialogWindow,
    IN UINT Message,
    IN WPARAM WParam,
    IN LPARAM LParam)
/*++

Routine Description:

    Callback function that processes messages sent to the default
    connection info dialog box.

Implementation

    This dialog box is the default when chat doesn't recognize a
    particular address family.  The user enters actual hex digits and
    the hex value is stored in the SocketAddress associated with the
    connection. Obviously, this requires the user to know how to
    interpret the structure of the socket address for this address
    family.

Arguments:

    DialogWindow - Supplies handle of the dialog box.

    Message - Supplies the message identifier

    WParam - Supplies the first message parameter

    LParam - Supplies the second message parameter

Return Value:

    TRUE -- This function handled the message.

    FALSE -- This function did not handle the message.

--*/
{

    static PCONNDATA ConnData = NULL;                // connection data
    static int       AddrLen;                        // length of addresses
    char             AddrText[MAX_SOCKADDR_LEN * 2]; // address string

    switch (Message) {

    case WM_INITDIALOG:

        // Get the parameter and figure out how long addresses for
        // this protocol may be.
        ConnData = (PCONNDATA)LParam;
        assert(ConnData != NULL);

        AddrLen = ConnData->ProtocolInfo->iMaxSockAddr;

        if (AddrLen > MAX_SOCKADDR_LEN) {
            MessageBox(DialogWindow,
                       "Sorry, socket addresses are too big. Aborting.",
                       "Error.", MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
            EndDialog(DialogWindow, FALSE);
        }

        // Limit the amount of text in the edit control to twice
        // AddrLen, i.e. 2 hex characters per byte.
        SendMessage(GetDlgItem(DialogWindow, IDC_ADDRESS), EM_LIMITTEXT,
                    (WPARAM)(AddrLen * 2), 0);
        return(TRUE);

    case WM_COMMAND:

        switch (WParam) {

        case IDOK:

            // The user clicked 'OK'.  Get the text from the edit
            // control, and convert the hex string into bytes and put
            // the bytes into the socket address for this connection.
            GetDlgItemText(DialogWindow, IDC_ADDRESS, AddrText,
                           MAX_SOCKADDR_LEN * 2);
            ConnData->RemoteSockAddr.len = AddrLen;
            ConnData->RemoteSockAddr.buf =
              malloc(ConnData->RemoteSockAddr.len);
            if (ConnData->RemoteSockAddr.buf == NULL) {
                ChatSysError("malloc()",
                             "DefaultConnDlgProc()",
                             TRUE);
            }

            if (TranslateHex(ConnData->RemoteSockAddr.buf,
                             ConnData->RemoteSockAddr.len,
                             AddrText,
                             DialogWindow)) {
                EndDialog(DialogWindow, TRUE);
            }
            return(TRUE);

        case IDCANCEL:

            // Kill the dialog box.
            EndDialog(DialogWindow, FALSE);
            return(TRUE);

        default:

            return(FALSE);
        } // switch (WParam)

    default:

        return(FALSE);
    } // switch (Message)

} // DefaultConnDlgProc()





LRESULT APIENTRY
NameAndSubjectDlgProc(
    IN HWND DialogWindow,
    IN UINT Message,
    IN WPARAM WParam,
    IN LPARAM LParam)
/*++

Routine Description:

    Callback function that processes messages sent to the name and
    subject dialog box.

Implementation

    This dialog box is brought up in MakeConnection (see socket.c)
    only if the protocol for the connection to be made supports
    connection-time data transfer.  The user fills in the two fields
    and this data is packed the WSABUF which is referenced through a
    pointer passed in during WM_INITDIALOG processing.

Arguments:

    DialogWindow - Supplies handle of the dialog box.

    Message - Supplies the message identifier

    WParam - Supplies the first message parameter

    LParam - Supplies the second message parameter

Return Value:

    TRUE -- This function handled the message.

    FALSE -- This function did not handle the message; or the message
    was WM_INITDIALOG and we set the focus.

--*/
{

    static LPWSABUF CallerBuffer;            // caller user data
    char            NameText[NAME_LEN + 1];  // name string
    char            SubjectText[SUB_LEN + 1];// subject string

    switch (Message) {

    case WM_INITDIALOG:

        // Get the parameter and initialize the dialog box.
        CallerBuffer = (LPWSABUF)LParam;
        assert(CallerBuffer != NULL);

        SendMessage(GetDlgItem(DialogWindow, IDC_CALLERNAME),
                    EM_LIMITTEXT, (WPARAM)NAME_LEN, 0);
        SendMessage(GetDlgItem(DialogWindow, IDC_SUBJECT),
                    EM_LIMITTEXT, (WPARAM)SUB_LEN, 0);
        SetFocus(GetDlgItem(DialogWindow, IDC_CALLERNAME));
        return(FALSE);

    case WM_COMMAND:

        switch (WParam) {

        case IDOK:

            // Get the strings the user has typed.
            GetDlgItemText(DialogWindow,
                           IDC_CALLERNAME,
                           NameText,
                           NAME_LEN);
            GetDlgItemText(DialogWindow,
                           IDC_SUBJECT,
                           SubjectText,
                           SUB_LEN);

            CallerBuffer->len = strlen(NameText) + strlen(SubjectText) + 2;
            CallerBuffer->buf = (char *)malloc(CallerBuffer->len);
            if (CallerBuffer->buf == NULL) {
                ChatSysError("malloc()",
                             "NameAndSubjectDlgProc()",
                             TRUE);
            }

            if (!PackTwoStrings(CallerBuffer->buf,
                                CallerBuffer->len,
                                NameText,
                                SubjectText)) {
                MessageBox(DialogWindow, "PackTwoStrings failed. Aborting.",
                           "Error.", MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
                EndDialog(DialogWindow, FALSE);
            }

            EndDialog(DialogWindow, TRUE);
            return(TRUE);

        case IDCANCEL:

            // Kill the dialog box.
            EndDialog(DialogWindow, FALSE);
            return(TRUE);

        default:

            return(FALSE);
        } // switch (WParam)

    default:

        return(FALSE);
    } // switch (Message)

} // NameAndSubjectDlgProc()





LRESULT APIENTRY
AcceptConnectionDlgProc(
    IN HWND DialogWindow,
    IN UINT Message,
    IN WPARAM WParam,
    IN LPARAM LParam)

/*++

Routine Description:

    Callback function that processes messages sent to the
    AcceptConnection dialog box.  Get's the callee's name and copies
    it into the CalleeBuffer, which is passed in as a parameter to the
    WM_INITDIALOG message.

Arguments:

    DialogWindow - Supplies handle of the AcceptConnection dialog box

    Message - Supplies the message identifier

    WParam - Supplies the first message parameter

    LParam - Supplies the second message parameter

Return Value:

    TRUE -- This function handled the message.

    FALSE -- This function did not handle the message; or the message
    was WM_INITDIALOG and we set the focus.

--*/

{
    static LPWSABUF CalleeData; // callee user data

    switch (Message) {

    case WM_INITDIALOG:

        CalleeData = (LPWSABUF)LParam;
        assert(CalleeData != NULL);

        // Determine how much room there is in the user data buffer.
        // Limit the text to NAME_LEN characters, or less if we
        // don't have room for that many.
        if (CalleeData->len < (NAME_LEN + 1)) {
            SendMessage(GetDlgItem(DialogWindow, IDC_CALLERNAME),
                        EM_LIMITTEXT, (WPARAM)(CalleeData->len - 1),
                        0);
        } else {
            SendMessage(GetDlgItem(DialogWindow, IDC_CALLERNAME),
                        EM_LIMITTEXT, (WPARAM)NAME_LEN, 0);
        }
        SetFocus(GetDlgItem(DialogWindow, IDC_CALLEENAME));
        return(FALSE);

    case WM_COMMAND:

        switch (WParam) {

        case IDOK:

            // Get the name from the control and but it in CalleeData.
            GetDlgItemText(DialogWindow,
                           IDC_CALLEENAME,
                           CalleeData->buf,
                           NAME_LEN);
            CalleeData->len = strlen(CalleeData->buf + 1);
            EndDialog(DialogWindow, TRUE);
            return(TRUE);

        case IDCANCEL:

            // Kill the dialog box
            EndDialog(DialogWindow, FALSE);
            return(TRUE);

        default:

            break;

        }

        break;
    } // switch (Message)

    return(FALSE);
} // AcceptConnectionDlgProc()





LRESULT APIENTRY
InetListenPortDlgProc(
    IN HWND DialogWindow,
    IN UINT Message,
    IN WPARAM WParam,
    IN LPARAM LParam)
/*++

Routine Description:

    Callback function that processes messages sent to the
    listening port dialog box.

Arguments:

    DialogWindow - Supplies handle of the AcceptConnection dialog box

    Message - Supplies the message identifier

    WParam - Supplies the first message parameter

    LParam - Supplies the second message parameter

Return Value:

    TRUE -- This function handled the message.

    FALSE -- This function did not handle the message; or the message
    was WM_INITDIALOG and we set the focus.

--*/
{

    static struct sockaddr_in *SockAddrInet;             // Inet sockaddress
    int                       Port;                      // Inet port
    BOOL                      PortStringTranslated;      // for GetDlgItemInt
    char                      PortText[INET_PORT_LEN+1]; // Inet port string

    switch (Message) {

    case WM_INITDIALOG:

        // Get the parameter and initialize the dialog box.
        SockAddrInet = (struct sockaddr_in *)LParam;
        assert(SockAddrInet != NULL);
        SendMessage(GetDlgItem(DialogWindow, IDC_LISTEN_PORT),
                    EM_LIMITTEXT, (WPARAM)INET_PORT_LEN, 0);
        wsprintf(PortText,"%d", INET_DEFAULT_PORT);
        SendMessage(GetDlgItem(DialogWindow, IDC_LISTEN_PORT),
                    WM_SETTEXT, 0, (LPARAM)PortText);
        SetFocus(GetDlgItem(DialogWindow, IDC_LISTEN_PORT));
        return(FALSE);

    case WM_COMMAND:

        switch (WParam) {

        case IDOK:

            // Get the port.
            Port = (int)GetDlgItemInt(DialogWindow,
                                      IDC_LISTEN_PORT,
                                      &PortStringTranslated,
                                      TRUE);
            if ((Port < 0) || (Port > 65535) || !PortStringTranslated) {
                MessageBox(DialogWindow,
                           "Please choose a port between 0 and 65535.",
                           "Bad Port.",
                           MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
                return(TRUE);
            }

            SockAddrInet->sin_port = htons((u_short)Port);
            EndDialog(DialogWindow, TRUE);
            return(TRUE);

        case IDCANCEL:

            // Kill the dialog box.
            EndDialog(DialogWindow, FALSE);
            return(TRUE);

        default:
            break;
        }
        break;

    } // switch (Message)

    return(FALSE);
} // InetListenPortDlgProc()
