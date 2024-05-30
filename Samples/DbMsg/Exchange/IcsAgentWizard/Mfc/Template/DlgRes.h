//{{NO_DEPENDENCIES}}
// Microsoft Visual C++ generated include file.
// Used by $$ROOT$$.RC
//
$$IF(PROJTYPE_DLG)
#define IDR_MAINFRAME					128
$$IF(ABOUT)
#define IDM_ABOUTBOX					0x0010
#define IDD_ABOUTBOX					100
$$ENDIF //ABOUT
$$IF(AUTOMATION)
#define IDP_OLE_INIT_FAILED				100
$$ENDIF //AUTOMATION
$$IF(ABOUT)
#define IDS_ABOUTBOX					101
$$ENDIF //ABOUT	
#define IDD_$$SAFE_ROOT$$_DIALOG				102
$$ENDIF //PROJTYPE_DLG
$$IF(SOCKETS)
$$IF(PROJTYPE_DLG)
#define IDP_SOCKETS_INIT_FAILED			103
$$ELSE //!PROJTYPE_DLG (i.e., PROJTYPE_DLL)
#define IDP_SOCKETS_INIT_FAILED			101


$$ENDIF //PROJTYPE_DLG
$$ENDIF //SOCKETS

// Next default values for new objects
// 
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS

$$IF(PROJTYPE_DLL || PROJTYPE_OCX)
#define _APS_NEXT_RESOURCE_VALUE	$$START_RES$$
#define _APS_NEXT_CONTROL_VALUE		$$START_RES$$
#define _APS_NEXT_SYMED_VALUE		$$START_RES$$
$$ELSE
#define _APS_NEXT_RESOURCE_VALUE	129
#define _APS_NEXT_CONTROL_VALUE		1000
#define _APS_NEXT_SYMED_VALUE		101
$$ENDIF
#define _APS_NEXT_COMMAND_VALUE		32771
#endif
#endif


//
// Customized resources for ICS Dialog-based applications
//
$$IF(PROJTYPE_DLG)

#define IDD_$$SAFE_ROOT$$_DIALOG        102
#define IDS_PRODUCT_NAME                102
#define IDS_COPYRIGHT                   103
#define IDS_AUTHORS                     104
#define IDR_MAINFRAME                   128
#define IDI_MAIL                        129
#define IDI_MAIN_ICON                   130
#define IDI_MAIN_SMALL_ICON             131
#define IDC_HELP_TEXT_1                 1000
#define IDC_HELP_TEXT_2                 1001
#define IDC_HELP_TEXT_3                 1002
#define IDC_TEST_BUTTON                 1002
#define IDC_TRACE_LIST                  1003
#define IDC_START                       1004
#define IDC_STOP                        1005
#define IDC_SYNCH                       1006

$$ENDIF // PROJTYPE_DLG
