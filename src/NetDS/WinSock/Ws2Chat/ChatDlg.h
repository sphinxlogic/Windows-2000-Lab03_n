/*++

Copyright (c) 1995 Intel Corp

Module Name:

    chatdlg.h

Abstract:

    Header file containing function protoypes of functions in dialog.c.

--*/
#include <windows.h>
#include <ws2atm.h>
#include <Windowsx.h>

#define NUM_ATM_ADDR_TYPES      5
#define NUM_BLLI_L2PROTO        15
#define NUM_BLLI_L3PROTO        9
#define NUM_BLLI_L3IPI          3
#define NUM_BHLI_TYPES          6

#define MAX_ADDRESS_TEXT        100
#define ATM_ADDR_LENGTH         20
#define MAX_PARSE_TEXT          80
#define ATM_SNAP_ID_LENGTH      5
#define ATM_HL_INFO_LENGTH      8


static PUCHAR AtmAddrTypeName[] =
{
    "NSAP",
    "E164",
    "Any",
    "Any (Sel)",
    "ANY (Rest)"
};
static DWORD AtmAddrTypeValue[] =
{
    ATM_NSAP,
    ATM_E164,
    SAP_FIELD_ANY,
    SAP_FIELD_ANY_AESA_SEL,
    SAP_FIELD_ANY_AESA_REST
};


static PUCHAR AtmBlliL2ProtoName[] =
{
    "ISO 1745",
    "Q921",
    "X25L",
    "X25M",
    "ELAPB",
    "HDLC NRM",
    "HDLC ABM",
    "HDLC ARM",
    "LLC",
    "X75",
    "Q922",
    "ISO 7776",
    "User Specified",
    "Absent",
    "Any"
};
static DWORD AtmBlliL2ProtoValue[] =
{
    BLLI_L2_ISO_1745,
    BLLI_L2_Q921,
    BLLI_L2_X25L,
    BLLI_L2_X25M,
    BLLI_L2_ELAPB,
    BLLI_L2_HDLC_NRM,
    BLLI_L2_HDLC_ABM,
    BLLI_L2_HDLC_ARM,
    BLLI_L2_LLC,
    BLLI_L2_X75,
    BLLI_L2_Q922,
    BLLI_L2_ISO_7776,
    BLLI_L2_USER_SPECIFIED,
    SAP_FIELD_ABSENT,
    SAP_FIELD_ANY
};


static PUCHAR AtmBlliL3ProtoName[] =
{
    "X25",
    "ISO 8208",
    "X223",
    "ISO 8473",
    "T70",
    "ISO TR9577",
    "User Specified",
    "Absent",
    "Any"
};
static DWORD AtmBlliL3ProtoValue[] =
{
    BLLI_L3_X25,
    BLLI_L3_ISO_8208,
    BLLI_L3_X223,
    BLLI_L3_SIO_8473,
    BLLI_L3_T70,
    BLLI_L3_ISO_TR9577,
    BLLI_L3_USER_SPECIFIED,
    SAP_FIELD_ABSENT,
    SAP_FIELD_ANY
};


static PUCHAR AtmBlliL3IpiName[] =
{
    "SNAP",
    "IP",
    "Absent"
};
static DWORD AtmBlliL3IpiValue[] =
{
    BLLI_L3_IPI_SNAP,
    BLLI_L3_IPI_IP,
    SAP_FIELD_ABSENT
};


static PUCHAR AtmBhliTypeName[] =
{
    "ISO",
    "User Specific",
    "High Layer Profile",
    "Vendor Specific App",
    "Absent",
    "Any"
};
static DWORD AtmBhliTypeValue[] =
{
    BHLI_ISO,
    BHLI_UserSpecific,
    BHLI_HighLayerProfile,
    BHLI_VendorSpecificAppId,
    SAP_FIELD_ABSENT,
    SAP_FIELD_ANY
};


LRESULT APIENTRY
InetConnDlgProc(
    IN HWND DialogHandle,
    IN UINT Message,
    IN WPARAM WordParam,
    IN LPARAM LongParam);

LRESULT APIENTRY
ATMSockAddrProc(
    IN HWND DialogHandle,
    IN UINT Message,
    IN WPARAM WordParam,
    IN LPARAM LongParam);


LRESULT APIENTRY
DefaultConnDlgProc(
    IN HWND DialogWindow,
    IN UINT Message,
    IN WPARAM WordParam,
    IN LPARAM LongParam);

LRESULT APIENTRY
ChooseFamilyDlgProc(
    IN HWND DialogHandle,
    IN UINT Message,
    IN WPARAM WordParam,
    IN LPARAM LongParam);

LRESULT APIENTRY
NameAndSubjectDlgProc(
    IN HWND DialogWindow,
    IN UINT Message,
    IN WPARAM WordParam,
    IN LPARAM LongParam);

LRESULT APIENTRY
AcceptConnectionDlgProc(
    IN HWND DialogHandle,
    IN UINT Message,
    IN WPARAM WordParam,
    IN LPARAM LongParam);

LRESULT APIENTRY
InetListenPortDlgProc(
    IN HWND DialogHandle,
    IN UINT Message,
    IN WPARAM WordParam,
    IN LPARAM LongParam);

BOOL ScanAtmAddress(
    HWND        hWndDlg,
    ATM_ADDRESS *pAtmAddr);

BOOL ScanAtmBlli(
    HWND hWndDlg,
    ATM_BLLI *pBLLI);

BOOL ScanAtmBhli(
    HWND hWndDlg,
    ATM_BHLI *pBHLI);

