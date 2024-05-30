/*																			 */
/*	ISVReg.h - include file for C routine that creates Registry entries      */
/*	for ISV Application Launching in SMS 1.2							     */
/*																			 */
/*	Created: 8 April 1996													 */
/*																			 */

#ifndef ISVREG
#define ISVREG

/* we use the generic text-mapping macros to handle multiple platforms		 */
#include <tchar.h>

#define SmsRegMaxLength		2048	/* the maximum size of any value: bytes  */

/* useful defines */
#define SmsRegRootKey		_T("Software\\Microsoft\\SMS\\Applications")
#define SmsLocalMachine     _T("HKEY_LOCAL_MACHINE")
#define SmsCurrentUser      _T("HKEY_CURRENT_USER")
#define SmsRegNameValue		_T("ApplicationName")
#define SmsRegOrder			_T("Order")
#define SmsRegIconFile		_T("IconFile")
#define SmsRegIconIndex		_T("IconFile")
#define SmsRegCommand		_T("Command")
#define SmsRegDescription	_T("Description")
#define SmsRegWorkingDir	_T("WorkingDir")
#define SmsRegRunWindow		_T("RunWindow")
#define SmsRegEnableRule	_T("EnableRule")
#define SmsRegPresentRule	_T("PresentRule")
#define SmsRegArguments		_T("Arguments")
#define SmsRegPrompt		_T("Prompt")
    
#define SmsTotalNumContexts     13    /* Total number of defined contexts      */
#define SmsGeneralContext       _T("General")
#define SmsAlertsContext        _T("SMSAlerts")
#define SmsArchWndContext       _T("SMSArchWnd")
#define SmsJobsContext          _T("SMSJobs")
#define SmsMachineContext       _T("SMSMachine")
#define SmsMachineGroupsContext _T("SMSMachineGroups")
#define SmsPackagesContext      _T("SMSPackages")
#define SmsPackageGroupsContext _T("SMSPackageGroups")
#define SmsQueriesContext       _T("SMSQueries")
#define SmsQueryResultsContext  _T("SMSQueryResults")
#define SmsSiteGroupsContext    _T("SMSSiteGroups")
#define SmsSitesContext         _T("SMSSites")
#define SmsTrapWndContext       _T("SMSTrapWnd")

/* ISVContext holds the information stored in the a Context subkey			 */

typedef struct
{
	LPTSTR	m_pContextKey;		/* the context the app launches from		 */
	/* 
		m_pEnableRule, m_pPresentRule, and m_pArguments should point to
		null-terminated strings with the character \r\n (CR\LF) in
		them representing line breaks. RegisterSMSTool will
		convert those strings into REG_MULTI_SZ data by replacing the \r\n
		characters with nulls and adding an additional null at the end	
	*/
	LPTSTR	m_pEnableRule;		
	LPTSTR	m_pPresentRule;
	LPTSTR	m_pArguments;
}
ISVContext,
*LPISVContext;

/* ISVAppReg holds the information stored in the Vendor Key and subkeys		*/
/* including an array of ISVContext structs that hold the Context subkeys   */
/* to be registered.														*/

typedef struct 
{
	LPTSTR			m_pVendor;          /* name of vendor */
	LPTSTR			m_pAppNameKey;      /* name of application key */
	LPTSTR			m_pAppName;         /* value-name that appears in menu */
	LPTSTR			m_pCommand;         /* The command to execute */
	LPTSTR			m_pWorkingDir;      /* working directory */
	LPTSTR			m_pDescription;     /* status bar description*/
	LPTSTR			m_pRunWindow;       /* Normal, Minimized, or Maximized */

	DWORD			m_dwOrder;
	BOOL			m_bHkeyLocal;       /* TRUE if using HKEY_LOCAL_MACHINE */
	int				m_nNumContexts;		/* number of ISVContexts in m_pContexts */
	LPISVContext	m_pContexts;		/* an array of ISVContexts */
}
ISVAppReg, 
*LPISVAppReg;

#if defined(__cplusplus)
extern "C"
{
#endif
/*
	RegisterSMSTool(BOOL bRemove, LPISVAppReg lpisv)

	This routine makes multiple calls to Registry APIs to create or update	
	information about a single application that wants to be visible in the
	SMS Tools menu and therefore launchable from the SMS Admin UI.
	
	bRemove == TRUE means take out the information
	bRemove == FALSE means add or update the information
	
	The input struct contains all the strings and values to be registered.
	See the ISV Application Launching spec for details about what these
	strings should be. In general the name of the key or value is the
	about the same as the member variable. Because an application can support 
	multiple contexts, the input structure has a pointer to multiple ISVContext
	structs in an array, plus a count.

	Return ERROR_SUCCESS if successful, otherwise the error code from the
	Registry function that failed.
*/

LONG WINAPI RegisterSMSTool(BOOL bRemove, LPISVAppReg lpisv);
#if defined(__cplusplus)
}
#endif

#endif  /* ISVREG */