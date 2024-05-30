// --poppst.cpp---------------------------------------------------------------
//
// Implementation of mail storage file populator program.
//  
// Copyright (C) Microsoft Corp. 1986-1996.  All rights reserved.
//
//-----------------------------------------------------------------------------

//
// Begin program documentation
//

/*

Poppst is a command line program that uses input from an ini file to create
messages in either a new PST or an existing PST.  If a new PST is desired, it
will be created in a temporary profile that is deleted when PST creation is
done.  If it is desired to create the messages in an existing PST, the profile
name is given for the PST.

Command line arguments:

One command line argument, the name of the ini file, is required.

Format of the ini file:

The following notation is used in describing the ini file grammar:

- Angle brackets (ie. <>) are used to indicate a token, or syntactic element.
- Braces (ie. {}) are used to indicate an optional syntactic element.
- Ellipsis (ie. ...) are used to indicate that the preceding syntactic element
  may be repeated.
- // indicates embedded comments (ie., not part of the file format).
- | indicates alternation (ie., a | b implies a or b is acceptable).

File format generalities:

The format used is basically consistent with the standard Microsoft ini file
format.  Thus, there are section header lines and section entry lines.  The
section header lines are distinguished from section entry lines by enclosing
the section keyword in square brackets.  Section entry lines have an entry
keyword that is immediately followed by an '='.  The '=' is then immediately
followed by a value for the section entry.  All characters following the '='
up to the newline are used for the value (ie., if there is whitespace, it will
be included in the value).  Leading whitespace is permitted in all lines, and
is not significant.  Whitespace everywhere else IS significant.  Comments may
be included by using ';' as the first nonwhitespace character on a line.
Blank lines may also be included in the ini file and are ignored.  Either a
newpst section or a profile section is required, and must be the first section
in the ini file.  Note that both a newpst section and a profile section
should NOT be used in one ini file.  One or more message sections should then
follow the newpst or profile section.  Unless otherwise noted, all section
entry lines are required, and must occur exactly once in a section.  The order
of section entries within a section is not important.The poppst program is
not case sensitive with regard to keywords.  The maximum line length permitted
is 512 chars (cbMaxIniLine) including the newline.

!!!!!IMPORTANT INFORMATION!!!!!

The [newpst] and [profile] sections are mutually exclusive.  

If you specify the [newpst] section, a temporary profile will be used.
This means that no name resolution will be possible.

If you specify the [profile] section, the message create
will be placed in the specified folder in the default message store.
If you want the message to be placed into your PST, then you must
FIRST set the PST "Personal Folders" store to be your default store
for the specified profile (Select Options | Delivery in the Exchange 
client).

!!!!!!!!END IMPORTANT INFORMATION!!!!!!!!!!!!!!!

Newpst section format (use to create a new pst and add msgs to it):\

[newpst]
	NAME=<pst display name string>
	ENCRYPTION=<encryption state>
	PASSWORD=<pst password string>
	PATH=<file path>

Profile section format (use to add msgs to existing pst in existing profile):

[profile]
	NAME=<profile name string>
	PASSWORD=<profile password string>

Message section format:

[message<whitespace><number>]
	FROM=<user name>{;<user name>}...
	TO=<user name>{;<user name>}...
	CC=<user name>{;<user name>}...		// Optional.
	BCC=<user name>{;<user name>}...	// Optional.
	FOLDER=<folder path>
	SUBJECT=<string>
	XTEXT=<file path>                   // Optional
	DATE=<date>
	TIME=<time>
	PRIORITY=<priority>
	XATTACH=<file path>{;<file path>}...// Optional.



// The <number> value in the message section header should be unique.  Poppst
// doesn't acutally use the number.  It is there only for Windows API compatibility.

BNF for syntactic elements used above:

//	This is an incomplete BNF, in that in some instances, we resolve an element
//	to <string> or <nonnull string>, and then add a comment indicating that
//	the string must be acceptable input for a given parameter of a given api
//	or a valid value for a given property.

<pst display name string> ::= <string>		// Must be valid PR_DISPLAY_NAME
											// value.
<pst password string> ::= <string>			// Must be valid PR_PST_PW_SZ_NEW
											// value.

<profile name string> ::= <nonnull string>	// Must be valid lpszProfileName
											// param of MAPILogonEx().

<profile password string> ::= <string>		// Must be valid lpszPassword
											// param of MAPILogonEx().

<whitespace> ::= <char>						// Where isspace(<char>) == TRUE.

<number> ::= <digit>...

<user name> ::= <user display name>{[<address type>:<email address>]}

<user display name> ::= <nonnull string>	// Must be valid PR_DISPLAY_NAME
											// value.

<address type> ::= <nonnull string>			// Must be valid PR_ADDRTYPE value.

<email address> ::= <nonnull string>		// Must be valid PR_EMAIL_ADDRESS
											// value.

<folder path> ::= {<folder namestring>{\<folder namestring>}...}	// See note
																	// below.
<string> ::= {<char>}...

<file path> ::= <nonnull string>			// Must be valid filename param of
											// fopen() api.

<date> ::= YYYY-MM-DD						// ie., year-month-day, as digits.

<time> ::= HH:MM{:SS}						// ie., hour:min{sec} as digits.

<encryption state> ::= ON | OFF

<priority> ::= HIGH | NORMAL | LOW

<nonnull string> ::= <char>...

<char> ::= Any char other than '\n'.

<digit> ::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9

<folder namestring> ::= <nonnull string>	// Must be valid PR_DISPLAY_NAME
											// value for a mailstore folder.

// Additional note on <folder path>:

A null folder path is used to specify the root folder of a mail store.  If you
want to add mail to the user inbox, the correct folder path is:
"Microsoft Personal Information Store\Inbox".

// Notes on message properties:

The properties that are created for each entry line in a message section are
documented below.  In general, we have used the properties that will result
in the information being displayed by the Exchange client frontend.

FROM:		PR_SENDER_NAME = <user name>
			PR_SENT_REPRESENTING_NAME = <user name>

// The following three lines are used to set up the recipient table in
// a message.  If the address book is available and <user name> can be
// resolved, then PR_DISPLAY_NAME will be used to derive PR_ADDRTYPE,
// PR_EMAIL_ADDRESS, and PR_ENTRYID.  If the address book is available,
// PR_ADDRTYPE and PR_EMAIL_ADDRESS may also be provided explicitly by using
// a <user name> of form <user display name>[<address type>:<email address>].
// All the <user display name>'s provided will also be used to set
// PR_DISPLAY_TO, PR_DISPLAY_CC, and PR_DISPLAY_BCC.

TO:			PR_RECIPIENT_TYPE = MAPI_TO;
			PR_DISPLAY_NAME = <user name> for each <user name>;

CC:			PR_RECIPIENT_TYPE = MAPI_CC;
			PR_DISPLAY_NAME = <user name> for each <user name>;

BCC:		PR_RECIPIENT_TYPE = MAPI_BCC;
			PR_DISPLAY_NAME = <user name> for each <user name>;

FOLDER:		Used to find folder message should be placed in.  If it does not
			exist, it will be created.

SUBJECT:	Used to set PR_SUBJECT.

XTEXT:		Contents of <file path> used to set PR_BODY & PR_RTF_COMPRESSED

DATE:		Used to set PR_MESSAGE_DELIVERY_TIME.

TIME:		Used to set PR_MESSAGE_DELIVERY_TIME.

PRIORITY:	Used to set PR_PRIORITY & PR_IMPORTANCE

XATTACH:	Contents of <file path> used to set PR_ATTACH_DATA_BIN.
			PR_ATTACH_METHOD = ATTACH_BY_VALUE.
			PR_ATTACH_FILENAME = <file path>.
			PR_ATTACH_LONG_FILENAME = <file path>.

*/

//
// End program documentation
//

#include "edk.h"
#include "mspst.h"
#include "popstrs.h"
#include "poppstmc.h"			// generated by the message compiler from poppstmc.mc
#include "poppst.chk"

//
// Manifest constants
//

const ULONG ulMapiLogonFlags    =   
		(MAPI_NEW_SESSION | MAPI_EXPLICIT_PROFILE | MAPI_NO_MAIL);

const UINT  cbMaxIniLine    =   512;

//
// Macros
//

// No macros defined.

//
// Enumeration, structure, and other type definitions
//

enum INIFILESECTIONTYPE		// ifst
{
    IFST_MESSAGE,
	IFST_NEWPST,
    IFST_PROFILE,
    IFST_UNKNOWN
};

enum LINEREADSTATUS			// lrs
{
    LRS_OKAY,           	// Line was read and is available.
    LRS_EOF,            	// We are at end of file; no more lines.
    LRS_IOERROR,        	// There was an I/O error in the last read.
    LRS_LINETOOLONG     	// Last line too long to return.
};

struct INIFILELINEVALUE		// iflv
{
	BOOL			fValid;
    CHAR            achValue[cbMaxIniLine];
};

struct INIFILEPARSEINFO		// ifpi
{
    CHAR *          	pszKeyword;
    HRESULT            	(*HrParseFunction)(IN	CHAR *	pch);
	INIFILELINEVALUE *	piflv;
};

//
// Forward function declarations
//

static
HRESULT
HrCreateMessageAttachment(
	IN		LPMESSAGE	lpMsg,
	IN		LPSTR		lpszAttachPath
	);

static
HRESULT
HrGetNextLine(OUT LINEREADSTATUS * lpReadStatus);

static
VOID
InitSectionData(
	IN		BOOL	fCommented);	// TRUE if section data is commented

static
HRESULT
HrIsSectionLine(
    IN      CHAR *  pch,
    OUT     BOOL * bIsSectionLine
    );

static
HRESULT
HrOpenFolder(OUT LPMAPIFOLDER * lppFolder);

static
HRESULT
HrParseDateValue(
    IN      CHAR *  pch
    );

static
HRESULT
HrParseEncryptionValue(
    IN      CHAR *  pch
    );

static
HRESULT
HrParseEntryLine(
    IN      CHAR *  pch
    );

static
HRESULT
HrParseLine();

static
HRESULT
HrParseNonNullStringValue(
    IN      CHAR *  pch
    );

static
HRESULT
HrParsePriorityValue(
    IN      CHAR *  pch
    );

static
HRESULT
HrParseSectionLine(
    IN      CHAR *  pch,		// pointer to section keyword
	IN		BOOL	fCommented	// TRUE is section is commented out
    );

static
HRESULT
HrParseStringValue(
    IN      CHAR *  pch
    );

static
HRESULT
HrParseTimeValue(
    IN      CHAR *  pch
    );

static
HRESULT
HrProcessMessageSection(VOID);

static
HRESULT
HrProcessNewPSTSection(VOID);

static
HRESULT
HrProcessProfileSection(VOID);

static
HRESULT
HrResolveRecipientNames(
	OUT		LPADRLIST *	lppAdrList
	);

static
HRESULT
HrResolveSenderName(
    IN      LPSTR pszName,
	OUT		LPADRLIST *	ppAdrList
	);

static
HRESULT
HrSetMessageProperties(
	IN		LPMESSAGE	lpMsg
	);

static
HRESULT
HrWriteMessageText(
	IN		LPMESSAGE	lpMsg,
	IN		LPSTR		lpszFilePath
	);

//
// Static storage
//

// Temporary profile name
static LPSTR			lpszProfileName =   NULL;

// Temporary profile password
static LPSTR			lpszProfilePassword =   NULL;

// Storage used to input and parse ini file lines and store values.

// Ini file pointer:

static FILE *           IniFile =			NULL;

// Current input line:

static CHAR             achIniLine[cbMaxIniLine]  =   {0};

// Parser state variables:

static BOOL					fTmpProf 			=	FALSE;
static INIFILESECTIONTYPE	ifstCurSection  	=   IFST_UNKNOWN;

// The following variable is TRUE if the current section has been 
// commented out (e.g. ;[newpst])
static BOOL					fCurSectionComment	=	FALSE;

// Parsed value storage (uses ~0.5KB per value):

static INIFILELINEVALUE	iflvBCC =   {0};			// For Message
static INIFILELINEVALUE	iflvCC  =   {0};				// For Message
static INIFILELINEVALUE	iflvDATE    =   {0};			// For Message
static INIFILELINEVALUE	iflvENCRYPTION  =   {0};		// For NewPST
static INIFILELINEVALUE	iflvFOLDER  =   {0};			// For Message
static INIFILELINEVALUE	iflvFROM    =   {0};			// For Message
static INIFILELINEVALUE	iflvPROFILENAME =   {0};	// For Profile
static INIFILELINEVALUE	iflvPSTNAME =   {0};		// For NewPST
static INIFILELINEVALUE	iflvPROFILEPASSWORD =   {0};// For Profile
static INIFILELINEVALUE	iflvPSTPASSWORD =   {0};	// For NewPST
static INIFILELINEVALUE	iflvPATH    =   {0};			// For NewPST
static INIFILELINEVALUE	iflvPRIORITY    =   {0};		// For Message
static INIFILELINEVALUE	iflvSUBJECT =   {0};		// For Message
static INIFILELINEVALUE	iflvTIME    =   {0};			// For Message
static INIFILELINEVALUE	iflvTO  =   {0};				// For Message
static INIFILELINEVALUE	iflvXATTACH =   {0};		// For Message
static INIFILELINEVALUE	iflvXTEXT   =   {0};			// For Message

// We translate some values and store them below during parsing:

static BOOL				bEncryptionNewPST   =   0;
static FILETIME			ftCurMsg            =   {0};
static LONG				lPriorityCurMsg     =   0;
static LONG             lImportanceCurMsg   =   0;
static SYSTEMTIME		stCurMsg =			{0, 0, 0, 0, 0, 0, 0, 0};

// Parser tables for entries:

static
INIFILEPARSEINFO    aifpiMessageEntry[] =   {
                                            "BCC", HrParseNonNullStringValue,
											&iflvBCC,
                                            "CC", HrParseNonNullStringValue,
											&iflvCC,
                                            "DATE", HrParseDateValue,
											&iflvDATE,
                                            "FOLDER", HrParseStringValue,
											&iflvFOLDER,
                                            "FROM", HrParseNonNullStringValue,
											&iflvFROM,
                                            "PRIORITY", HrParsePriorityValue,
											&iflvPRIORITY,
                                            "SUBJECT", HrParseStringValue,
											&iflvSUBJECT,
                                            "TIME", HrParseTimeValue,
											&iflvTIME,
                                            "TO", HrParseNonNullStringValue,
											&iflvTO,
                                            "XATTACH", HrParseNonNullStringValue,
											&iflvXATTACH,
                                            "XTEXT", HrParseNonNullStringValue,
											&iflvXTEXT
                                            };
static
INIFILEPARSEINFO  aifpiNewPSTEntry[] =     {
                                            "NAME", HrParseStringValue,
											&iflvPSTNAME,
                                            "PASSWORD", HrParseStringValue,
											&iflvPSTPASSWORD,
											"ENCRYPTION", HrParseEncryptionValue,
											&iflvENCRYPTION,
											"PATH", HrParseNonNullStringValue,
											&iflvPATH
                                            };
static
INIFILEPARSEINFO  aifpiProfileEntry[] =     {
                                            "NAME", HrParseNonNullStringValue,
											&iflvPROFILENAME,
                                            "PASSWORD", HrParseStringValue,
											&iflvPROFILEPASSWORD
                                            };
// Error handling variables:

static ULONG	cMsgs =		0;
static DWORD	iLine =		1;
static DWORD	iSection =	1;

// MAPI-related storage:

static LPADRBOOK			lpAdrBook =			NULL;
static LPMDB				lpMdb =				NULL;
static LPMAPIFOLDER			lpRootFolder =		NULL;
static LPMAPISESSION		lpSession =			NULL;

// character constants
const CHAR	cSemiColon		=	';';			// delimiter character or comment
const CHAR	cBeginSectLine	=	'[';			// begins section line
const CHAR 	cEndSectLine	=	']';			// ends section line
const CHAR	cEquals			=	'=';			// keyword equals value character
const CHAR	cNewLine		=	'\n';			// new line character
const CHAR 	cColon			=	':';			// colon character
const CHAR	cBackSlash		=	'\\';			// backslash character
const CHAR	cDate			=	'd';			// date template character

// string constants
LPCSTR		pszSeparator	=	";";			// delimiter character

// Application name
static CHAR	szAppName[]			=	"POPPST";

// Static inline "macros"
// Used instead of #define macros, since they can do type checking

// in-line static for determining if should process section
static inline BOOL fSectionReady(				// RETURNS: BOOL
	IN INIFILESECTIONTYPE ifstDesiredSection)	// section want to process
{
 	// If current section is desired section and current section
	// is not commented out, we should try to process it.
	return ( ( (ifstCurSection == ifstDesiredSection) && 
	  (fCurSectionComment == FALSE) ) ? TRUE : FALSE );

}
	
//
// Functions
//

//$--INTERNAL_ERROR----------------------------------------------------------
//  Helper functions for EventLogMsg
// --------------------------------------------------------------------------
static inline VOID INTERNAL_ERROR(
    IN LPCTSTR str,
    IN const HRESULT hr)
{
    TCHAR szErrorCode[16] = {0};

    EventLogMsg(
        POPPST_INTERNAL_ERROR,
        2, str, _itot( hr, szErrorCode, 16),
        0);
}

static inline LPCTSTR SZ_BASE10(
    IN const INT iNumber)
{
    static TCHAR szTemp[16] = {0};
    return( (LPCTSTR)_itot( iNumber, szTemp, 10));
}

static inline LPCTSTR SZ_BASE16(
    IN const ULONG ulNumber)
{
    static TCHAR szTemp[16] = {0};
    return( (LPCTSTR)_itot( ulNumber, szTemp, 16));
}


//$--DisplayUserMsg----------------------------------------------------------
//
// DESCRIPTION: Utility to display message to command line user.
//
// INPUT:       hInst   --  program instance handle
//              nResID  --  Resource string identifier
// 
// RETURNS:     VOID
//
// ----------------------------------------------------------------------------
VOID DisplayUserMsg(            // RETURNS: nothing
            IN UINT nResID,     // resource string identifier
            ...)                // additional arguments
{    
    INT     		nRetCode    = 	0;			// return value
    va_list 		vArgList    =   {0};        // variable argument list
	static HMODULE	hModule		=	NULL;		// application instance handle
	static BOOL		fInit		=	FALSE;		// TRUE if module handle has is initialized
	DWORD			nLastErr	=	0;			// last Win32 API error

    const INT		nMsgLength	=   256;        // maximum length of printed messages

	// LoadString message buffer
    CHAR  			szMessage[nMsgLength]  =   "";

    DEBUGPRIVATE("DisplayUserMsg()\n");

    // No CHK_DisplayUserMsg() call.
    // We check arguments as we go, as we may be in an error state.

    // Check the instance handle
    if ( fInit == FALSE )
    {
		// Retrieve this programs instance handle.
		hModule = GetModuleHandle(NULL);

		fInit = TRUE;	// have retrieved instance handle

		// Print out error if have failed.	
		if ( hModule == NULL )
		{	
			nLastErr = GetLastError();

			fprintf(stderr, "ERROR: Unable to display resource messages to console: "
				"error code 0x%lx,\n", nLastErr);

			HR_LOG(HRESULT_FROM_WIN32(nLastErr));
		}
    }

	// Check validity of module handle
	if ( hModule == NULL )
	{
		// can't do anything
		goto cleanup;
	}

	// retrieve resource string
    nRetCode = LoadString(
    	hModule, 
    	nResID, 
    	szMessage, 
    	nMsgLength);

    if ( nRetCode == 0 )
    {
        // Print out default error string.
		nLastErr = GetLastError();

		fprintf(stderr, "ERROR: Can't load resource string %ld: "
			"error code 0x%lx,\n", nResID, nLastErr);

        HR_LOG(HRESULT_FROM_WIN32(nLastErr));

        goto cleanup;
    }

    // Get an optional argument list pointer
    va_start(vArgList, nResID);

    // Print the message to standard out
    vprintf(szMessage,          // format string
            vArgList);          // variable argument list

    va_end(vArgList);

	// we are done.

cleanup:

    // Return
    return;

}   // end DisplayUserMsg()

//$--main--------------------------------------------------------------------
//
// DESCRIPTION: poppst.exe main() routine.
//
// INPUT:       argc    --  argument count
//              argv    --  command line arguments
//
// RETURNS:     INT --     0 on success;
//                         E_INVALIDARG if invalid parameter,
//                         E_OUTOFMEMORY if memory problems,
//                         E_FAIL if internal error.
//
//---------------------------------------------------------------------------

INT main(               // RETURNS: INT
    IN  INT     argc,       // # arguments on command line
    IN  CHAR *  argv[]      // command line arguments array
    )
{
    HRESULT 			hr  				=   NOERROR;
	INT		            iCounter	        =	0;		// argument index
	BOOL				bMAPIInitialized 	=	FALSE;
    LINEREADSTATUS      lrs 				=   LRS_OKAY;
    BOOL    			bIsSectionLine  	=   FALSE;  // TRUE if the line is a section line
	HANDLE				hEvent				=	NULL;	// event logging handle
	EDKEVENTCOUNT		sEventCount			=	{0};	// event log count structure
	BOOL				fEventLogOpened		=	FALSE;	// TRUE if event log is open

    DEBUGPUBLIC("main()\n");

    // Check input parameters.
	hr = CHK_main(argc, argv);
	if ( FAILED(hr) )
		goto cleanup;

	// parse comand line
    if (argc == 1)
    {
		// Display usage message
		DisplayUserMsg(
			IDS_USAGE);
		DisplayUserMsg(
			IDS_NEWLINE);
		DisplayUserMsg(
			IDS_USAGEFILE);
		DisplayUserMsg(
			IDS_USAGEHELP);

        hr = HR_LOG(E_INVALIDARG);

        goto cleanup;
    }

    // Check to see if user wants help (/? or /HELP flag)
    for ( iCounter = 0; iCounter < argc; iCounter++ )
    {
        ASSERT_STRING_PTR(argv[iCounter], "Bad argv[iCounter]");

        if ( argv[iCounter][0] == '/' || argv[iCounter][0] == '-')
        {
            if ( (argv[iCounter][1] == '?') || 
                 (argv[iCounter][1] == 'H') ||
                 (argv[iCounter][1] == 'h') )
            {
                // display help message
				DisplayUserMsg(
					IDS_HELP);
				DisplayUserMsg(
					IDS_NEWLINE);
				DisplayUserMsg(
					IDS_USAGE);
				DisplayUserMsg(
					IDS_NEWLINE);
				DisplayUserMsg(
					IDS_USAGEFILE);
				DisplayUserMsg(
					IDS_HELPDOC);

                hr = HR_LOG(E_INVALIDARG);

                goto cleanup;
            }
        }
    }   // end for

    // Check number of parameters.  (Should be 2, including the
    // program name).
    if ( argc != 2 )
    {
		DisplayUserMsg(
			IDS_PARAM_NUMBER);

        hr = HR_LOG(E_INVALIDARG);

        goto cleanup;
    }

    if ( FAILED(hr) )
        goto cleanup;

	// Open an event logging handle for this application.
 	hr = HrEventOpenLog(
		szAppName,					// application name
		NULL,						// executable name (computed)
    	NULL,						// event message file (computed)
		NULL,						// parameter message file
		NULL,						// category message file
		&hEvent);					// event logging handle

	if ( FAILED(hr) )
	{
		DisplayUserMsg(
			IDS_EVENT_LOG,
			hr);

		goto cleanup;
	}

	ASSERTERROR((hEvent != NULL), "Bad hEvent");

	fEventLogOpened = TRUE;

	// Let user know that we are doing something.
	DisplayUserMsg(
		IDS_PROCESSING, 
		argv[1]);

    // open the INI file.
    IniFile = fopen(argv[1], "r");

	if ( IniFile == NULL )
	{
		EventLogMsg(
			POPPST_OPEN_FILE_ERROR,
			1,			// # of string replacements
			argv[1],
			0);			// # of Win32 error codes

        hr = HR_LOG(E_INVALIDARG);
        goto cleanup;
	}

	hr = MAPIInitialize(0);

	if (FAILED(hr))
	{
		EventLogMsg(
			POPPST_MAPIINIT_ERROR,
			1, SZ_BASE16(hr),
			0);

        hr = HR_LOG(E_FAIL);

		goto cleanup;
	}

	bMAPIInitialized = TRUE;

	InitSectionData(FALSE);

    while (TRUE)
    {
		hr = HrGetNextLine(&lrs);

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

		if (lrs == LRS_OKAY)
		{
            hr = HrIsSectionLine(achIniLine, &bIsSectionLine);

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

			if ( bIsSectionLine )
			{
				if ( fSectionReady(IFST_MESSAGE) == TRUE )
				{
				    hr = HrProcessMessageSection();

                    if ( FAILED(hr) )
                    {
                        goto cleanup;
                    }
				}
				else if ( fSectionReady(IFST_NEWPST) == TRUE )
				{
                    hr = HrProcessNewPSTSection();

					if ( FAILED(hr) )
                    {
						goto cleanup;
                    }
				}
				else if ( fSectionReady(IFST_PROFILE) == TRUE )
				{
                    hr = HrProcessProfileSection();

					if ( FAILED(hr) )
                    {
						goto cleanup;
                    }
				}

				// If ifstCurSection == IFST_UNKNOWN, we don't have a valid
				// section at present, and do nothing.
			}

            hr = HrParseLine();

        	if ( FAILED(hr) )
        	{
				EventLogMsg(
					POPPST_SYNTAX_ERROR,
					1, SZ_BASE10(iLine),
					0);
            }
		}
		else if (lrs == LRS_LINETOOLONG)
		{
			EventLogMsg(
				POPPST_LENGTH_ERROR,
				1, SZ_BASE10(iLine),
				0);
		}
		else
		{
			break;
		}

        iLine++;
    }

    if (lrs == LRS_EOF) 
    {
		if ( fSectionReady(IFST_MESSAGE) == TRUE )
		{
			hr = HrProcessMessageSection();				

            if ( FAILED(hr) )
            {
                goto cleanup;
            }
		}
		else if ( fSectionReady(IFST_NEWPST) == TRUE )
		{
            hr = HrProcessNewPSTSection();

			if ( FAILED(hr) )
            {
				goto cleanup;
            }
		}
		else if ( fSectionReady(IFST_PROFILE) == TRUE )
		{
            hr = HrProcessProfileSection();

			if ( FAILED(hr) )
            {
				goto cleanup;
            }
		}

    }	// end if have reached end of file

	// Dertermine number of errors, warnings and informationsl
	// messages logged to the event log.
	hr = HrEventGetCounts(
		&sEventCount);		// structure to hold event logging statistics

	if ( FAILED(hr) )
	{
        INTERNAL_ERROR( TEXT("HrEventGetCounts()"), hr);

		sEventCount.cError = 1;	// have at least one error
	}

	// if no errors, check for proper program termination state
	if ( sEventCount.cError == 0 )
	{
		if ( (lrs == LRS_EOF) && (ifstCurSection == IFST_UNKNOWN) )
		{
			// Have an empty INI file.  
			// Print out error to the user.
			hr = HR_LOG(E_FAIL);
			
			EventLogMsg(
				POPPST_EMPTY_ERROR,
				1,
				argv[1],
				0);

			goto cleanup;			

		}	// end if have an empty file

    	else if (lrs == LRS_IOERROR)
    	{
			EventLogMsg(
				POPPST_IO_ERROR,
				1, SZ_BASE10(iLine),
				0);

			goto cleanup;
    	}

		// Otherwise, we are successful
   		else
    	{
			// Log this fact.
			EventLogMsg(
				POPPST_POPULATE_SUCCEEDED,
				0,
				0);
    	}

	}	// end if no error message printed out so far

	// We are done.

cleanup:

	// Print out a completion message to the user.
	// First, determine the number of errors, warnings and informationsl
	// messages logged to the event log.
	if ( fEventLogOpened == TRUE )
	{
		ZeroMemory(&sEventCount, sizeof(sEventCount));
		hr = HrEventGetCounts(
			&sEventCount);		// structure to hold event logging statistics

		if ( FAILED(hr) )
		{
            INTERNAL_ERROR( TEXT("HrEventGetCounts()"), hr);

			sEventCount.cError = 1;	// have at least one error
		}

		if ( sEventCount.cError == 0 )
		{
			// print success message 
			DisplayUserMsg(
				IDS_SUCCESS);
		}

		else if ( sEventCount.cError == 1 )
		{
			// print one error message
			DisplayUserMsg(
				IDS_1ERROR);
		}
	
		else 
		{
			// print multiple error message
			DisplayUserMsg(
				IDS_ERRORS);
		}

		if ( sEventCount.cWarning == 1 )
		{
			// print out one warning message
			DisplayUserMsg(
				IDS_1WARNING);
		}

		else if ( sEventCount.cWarning > 1 )
		{
			// print out mutliple warnings message
			DisplayUserMsg(
				IDS_WARNINGS);
		}

		// close event log
		(VOID)HrEventCloseLog();
		hEvent = NULL;
		fEventLogOpened = FALSE;

	}	// end if have event log handle

	// Release MAPI and OLE objects
	ULRELEASE(lpAdrBook);
	ULRELEASE(lpRootFolder);
	ULRELEASE(lpMdb);

	if (lpSession)
	{
	    lpSession->Logoff(0, 0, 0);
		ULRELEASE(lpSession);
	}

	if (fTmpProf)
	{
		HrCleanupPSTGlobals(lpszProfileName);

        MAPIFREEBUFFER(lpszProfileName);
        MAPIFREEBUFFER(lpszProfilePassword);
	}

	if (bMAPIInitialized)
    {
	    MAPIUninitialize();
    }

    if (IniFile)
    {
        fclose(IniFile);
    }

    // return the appropriate exit code, based on our HRESULT.
    return _nEcFromHr(hr);
}

//$--HrCreateMessageAttachment-----------------------------------------------
//
// DESCRIPTION: Create a message attachment and write the contents of the
//				specified file to it.  Also create various required properties
//				for the message attachment.
//
// INPUT:
//
//		[lpMsg]			-- Message for which attachment is to be created.
//		[lpszAttachPath]-- Path of file containing attachment text.
//
// RETURNS: HRESULT --  NOERROR if O.K., 
//                      E_INVALIDARG if invalid parameter,
//                      E_OUTOFMEMORY if memory problems,
//                      E_FAIL if call fails
//
//---------------------------------------------------------------------------


HRESULT HrCreateMessageAttachment(          // RETURNS: HRESULT
	IN		LPMESSAGE	lpMsg,              // MAPI message pointer
	IN		LPSTR		lpszAttachPath      // list of attachment file names
	)
{
    HRESULT         hr              =   NOERROR;    // return code
	ULONG			cb              =   0;
	LPATTACH		lpAttach        =	NULL;
	ULONG			ulAttachmentNum =   0;
    ULONG           nAttachments    =   0;      // # of attachments
    ULONG           iAttach         =   0;      // attachment index
    LPSTR           lpszCurrent     =   NULL;   // current attachment
	LPSTR *			lppszAttachTok	=	NULL;	// array of tokenized attachments

    // MAPI property creation flags.    
    const ULONG     ulFlags     =   MAPI_CREATE | MAPI_MODIFY | 
                                    MAPI_DEFERRED_ERRORS;   // reduces RPCs

    // Buffer read/write size
    const UINT      cbBufSize           =   4096;

    // read/write data buffer
	BYTE			ab[cbBufSize]       =   {0};

    // # of attachment properties
    const ULONG		cValues             =	3;

    // property value array
    SPropValue      aPropVals[cValues]  =   {0};

    DEBUGPRIVATE("HrCreateMessageAttachment()\n");

    // Check input parameters
    hr = CHK_HrCreateMessageAttachment(lpMsg, lpszAttachPath);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // Determine number of attachments by breaking into tokens
	hr = HrStrTokAll(
		lpszAttachPath,			// file name list
		(LPSTR) pszSeparator,	// separator character
		&nAttachments,			// # of file names
		&lppszAttachTok);		// array of strings pointer

	if ( FAILED(hr) )
	{
        INTERNAL_ERROR( TEXT("HrStrTokAll()"), hr);

		goto cleanup;
	}

    ASSERTERROR((nAttachments != 0), "Bad nAttachments");
	ASSERT_READ_PTR(lppszAttachTok, sizeof(LPSTR) * nAttachments, 
		"Bad lppszAttachTok");

    // Process each attachment.
    for ( iAttach = 0; iAttach < nAttachments; iAttach++ )
    {
        // Release MAPI objects
	    ULRELEASE(lpAttach);

		// Retrieve next attachment
		lpszCurrent = lppszAttachTok[iAttach];

		ASSERT_STRINGA_PTR(lpszCurrent, "Bad lpszCurrent");

	    // Create the attachment in the message.
	    hr = lpMsg->CreateAttach(NULL,
							 MAPI_DEFERRED_ERRORS,  // reduces RPCs
							 &ulAttachmentNum,
							 &lpAttach);

	    if ( FAILED(hr) )
	    {  
            INTERNAL_ERROR( TEXT("IMessage::CreateAttach()"), hr);

            hr = HR_LOG(E_FAIL);

		    goto cleanup;
	    }

        ASSERT_IUNKNOWN_PTR(lpAttach, "Bad lpAttach");
        	
	    // Create required additional properties.
		LPSPropProblemArray	lpProblems 		=	NULL;
		LPSTR				lpszFileName    =   NULL;

		aPropVals[0].ulPropTag =	PR_ATTACH_METHOD;
		aPropVals[0].Value.l =		ATTACH_BY_VALUE;

		lpszFileName = strrchr(lpszCurrent, cBackSlash);

		if (!lpszFileName)
			lpszFileName = lpszCurrent;
		else
			lpszFileName++;	// Advance past the backslash.

		// CAVEAT - We don't do anything here to check for invalid FAT 8.3
		//		    names.  This may be a good idea.
		aPropVals[1].ulPropTag =	PR_ATTACH_FILENAME;
		aPropVals[1].Value.lpszA =	lpszFileName;

		aPropVals[2].ulPropTag =	PR_ATTACH_LONG_FILENAME;
		aPropVals[2].Value.lpszA =	lpszFileName;

		hr = lpAttach->SetProps(cValues, aPropVals, &lpProblems);

		if (FAILED(hr))
		{
            INTERNAL_ERROR( TEXT("IMAPIProp::SetProps()"), hr);

            hr = HR_LOG(E_FAIL);
			goto cleanup;
		}

		if (lpProblems != NULL)
		{
			ULONG	i   =   0;
			for (i = 0; i < lpProblems->cProblem; i++)
			{
                INTERNAL_ERROR( TEXT("IMAPIProp::SetProps()"), lpProblems->aProblem[i].scode);
			}

			MAPIFREEBUFFER(lpProblems);

            hr = HR_LOG(E_FAIL);
			goto cleanup;
		}

        // Create the PR_ATTACH_DATA_BIN property from the attachment
        // file text.
        hr = HrMAPISetPropFromFile(
            lpAttach,               // pointer to attachment object
            PR_ATTACH_DATA_BIN,     // property tag
            lpszCurrent,            // fully-pathed file name from which to read data
            &cb);                   // # bytes read in

        if ( FAILED(hr) )
        {
            INTERNAL_ERROR( TEXT("HrMAPISetPropFromFile()"), hr);

            goto cleanup;
        }

	    // Commit the attachment changes.
	    hr = lpAttach->SaveChanges(0);

	    if (FAILED(hr))
	    {	
            INTERNAL_ERROR( TEXT("IMAPIProp::SaveChanges()"), hr);

            hr = HR_LOG(E_FAIL);
		    goto cleanup;
	    }
    }   // end for each attachment

    // we are done

cleanup:

    // Release MAPI and OLE objects
	ULRELEASE(lpAttach);

	// Free MAPI buffers
	MAPIFREEBUFFER(lppszAttachTok);

	RETURN(hr);

}

//$--HrGetNextLine-----------------------------------------------------------
//
// DESCRIPTION: Get the next input line from the ini file and deposit it in
//				the input buffer (achIniLine).
//
// OUTPUT:  LINEREADSTATUS *    --  pointer to line read status
//
//  LRS_OKAY if line was read and is available.
//  LRS_EOF if we are at end of file; no more lines.
//  LRS_IOERROR if there was an I/O error in the last read.
//  LRS_LINETOOLONG if last line was too long to fit in the buffer.
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_INVALIDARG if bad parameter,
//
//---------------------------------------------------------------------------

HRESULT HrGetNextLine(                  // RETURNS: HRESULT
    OUT LINEREADSTATUS * lpReadStatus)  // pointer to line read status
{
    HRESULT         hr  =   NOERROR;    // return code
    INT             ch  =   0;
    CHAR *          pch =       &achIniLine[0];
    CHAR *          pchInv =    &achIniLine[cbMaxIniLine];

    DEBUGPRIVATE("HrGetNextLine()\n");

    // Check input parameters.
    hr = CHK_HrGetNextLine(lpReadStatus);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    *lpReadStatus = LRS_OKAY;

    while (TRUE)
    {
        if (pch == pchInv)
        {
            // Line is too long
            *lpReadStatus =           LRS_LINETOOLONG;
            achIniLine[0] = 0;
            while ((ch = getc(IniFile)) != EOF && (ch != cNewLine));

            break;
        }

        ch = getc(IniFile);

        if (ch == cNewLine)
        {
            // Just read end of this line
            *lpReadStatus =   LRS_OKAY;
            *pch =  0;

            break;
        }

        if (ch == EOF)
        {
            // Just read last line in file
            // We want to process the last line, if any.
            *pch = 0;

            if ( pch == &achIniLine[0] )
            {
                // we have passed the last line in the file.
                *lpReadStatus = feof(IniFile) ? LRS_EOF : LRS_IOERROR;
            }

            else
            {
                // we just read last line.  We want to process
                // its data.
                *lpReadStatus = feof(IniFile) ? LRS_OKAY : LRS_IOERROR;
            }

            break;

        }   // end if end of file reached

        *pch = ch;
        pch++;
    }

    RETURN(hr);

}


//$--InitSectionData---------------------------------------------------------
//
// DESCRIPTION: Initialize static variables that will be used in parsing an
//				ini file section to default values.
//
// INPUT:       None.
//
// RETURNS:     Nothing.
//
//---------------------------------------------------------------------------

VOID InitSectionData(           // RETURNS: VOID
	IN BOOL fCommented)			// TRUE if section is commented out
{
    DEBUGPRIVATE("InitSectionData()\n");

	// Record whether or not section is commented out
	fCurSectionComment = fCommented;

	ifstCurSection =				IFST_UNKNOWN;

	iflvBCC.fValid =				FALSE;
	iflvCC.fValid =					FALSE;
	iflvDATE.fValid =				FALSE;
	iflvENCRYPTION.fValid =			FALSE;
	iflvFOLDER.fValid =				FALSE;
	iflvFROM.fValid =				FALSE;
	iflvPATH.fValid =				FALSE;
	iflvPRIORITY.fValid =			FALSE;
	iflvPROFILENAME.fValid =		FALSE;
	iflvPROFILEPASSWORD.fValid =	FALSE;
	iflvPSTNAME.fValid =			FALSE;
	iflvPSTPASSWORD.fValid =		FALSE;
	iflvSUBJECT.fValid =			FALSE;
	iflvTIME.fValid =				FALSE;
	iflvTO.fValid =					FALSE;
	iflvXATTACH.fValid =			FALSE;
	iflvXTEXT.fValid =				FALSE;
}


//$--HrIsSectionLine-----------------------------------------------------------
//
// DESCRIPTION: Determine if an input line is a section header (ie., first
//				non-whitespace char is '[').
//
// INPUT:       [pch]	-- Ptr to input line.
//
// OUTPUT:      lpbIsSectionLine    --  BOOLEAN pointer.  TRUE if is section line.
//
// RETURNS:     HRESULT --  NOERROR if successful
//                          E_INVALIDARG if bad parameter
//---------------------------------------------------------------------------

HRESULT HrIsSectionLine(                    // RETURNS: HRESULT
    IN      CHAR *  pch,                    // input line
    OUT     BOOL * lpbIsSectionLine     // boolean pointer
    )
{
    HRESULT hr  =   NOERROR;    // return code

    DEBUGPRIVATE("HrIsSectionLine()\n");

    // Check input parameters.
    hr = CHK_HrIsSectionLine(pch, lpbIsSectionLine);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

	// skip leading white space and comment characters
    while ( (isspace(*pch) > 0) || (*pch == cSemiColon) )
	{
        pch++;
	}

	*lpbIsSectionLine = (*pch == cBeginSectLine);		// All sections must start with an '['

    RETURN(hr);

}


//$--HrOpenFolder------------------------------------------------------------
//
// DESCRIPTION: Open the folder specified by the iflvFOLDER static variable.
//
// INPUT:       None.
//
// OUTPUT:      lppFolder   --  folder pointer pointer
//
// RETURNS:     HRESULT --  NOERROR if successful,
//              E_INVALIDARG if invalid parameters,
//              E_FAIL otherwise
//
//---------------------------------------------------------------------------

HRESULT HrOpenFolder(                   // RETURNS: HRESULT
    OUT LPMAPIFOLDER * lppFolder)   // output folder pointer pointer
{
    HRESULT         hr          =   NOERROR;  
    UINT            cchFolder   =   0;      // # characters in folder

    const CHAR      chSep    =   cBackSlash;      // separator character

    DEBUGPRIVATE("HrOpenFolder()\n");

    // Check input parameters
    hr = CHK_HrOpenFolder(lppFolder);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }
    
    *lppFolder = NULL;  // initialize

    // Strip the trailing '\', if any.
    cchFolder = lstrlen(iflvFOLDER.achValue);

    ASSERTERROR((cchFolder > 0), "Bad cchFolder");

    if ( iflvFOLDER.achValue[cchFolder - 1] == cBackSlash )
    {
        iflvFOLDER.achValue[cchFolder - 1] = 0;
    }

    // Determine if getting root folder
	if (iflvFOLDER.achValue[0] == 0)
    {
		*lppFolder = lpRootFolder;
        
        goto cleanup;
    }

    // Otherwise, opent the pathed folder.
    hr = HrMAPIOpenFolderEx(
        lpMdb,                      // message store pointer
        chSep,                      // folder path separator character
        iflvFOLDER.achValue,        // folder path
        lppFolder);                 // pointer to folder opened

    if ( FAILED(hr) )
    {
		EventLogMsg(
			POPPST_FOLDER_ERROR,
			2, iflvFOLDER.achValue, SZ_BASE16(hr),
            0);

        goto cleanup;
    }

cleanup:

	RETURN(hr);

}


//$--HrParseDateValue--------------------------------------------------------
//
// DESCRIPTION: Parse a DATE= entry for the value.
//
// INPUT:       [pch]	-- Ptr to input string.
//
// RETURNS:     HRESULT --  NOERROR if success,
//                          E_INVALIDARG if bad input,
//                          E_FAIL if call fails.
//
//---------------------------------------------------------------------------

HRESULT HrParseDateValue(           // RETURNS: HRESULT
    IN      CHAR *  pch             // date string
    )
{
    HRESULT hr  =   NOERROR;    // return value
    static CHAR    DateTemplate[] = "dddd-dd-dd";
    INT     i = 0;

    DEBUGPRIVATE("HrParseDateValue()\n");

    // Check input parameters
    hr = CHK_HrParseDateValue(pch);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    for (i = 0; i < sizeof(DateTemplate); i++)
    {
        if (DateTemplate[i] == cDate)
        {
            if (!isdigit(*(pch + i)))
            {
                hr = HR_LOG(E_FAIL);

                goto cleanup;
            }
        }
        else
        {
            if (DateTemplate[i] != *(pch + i))
            {
                hr = HR_LOG(E_FAIL);

                goto cleanup;
            }
        }
    }

	// Given that we can't REALLY do range checking without knowing about
	// leap years, we rely on SystemTimeToFileTime() to later do complete range
	// checking on the year/month/day values.  We can cast the values to words
	// without a problem, given we know there are a most 4 decimal digits.

	stCurMsg.wYear =	(WORD)atol(pch);
	stCurMsg.wMonth =	(WORD)atol(pch + 5);
	stCurMsg.wDay =		(WORD)atol(pch + 8);

cleanup:

    RETURN(hr);

}


//$--HrParseEncryptionValue----------------------------------------------------
//
// DESCRIPTION: Parse an ENCRYPTION= entry for the value.
//
// INPUT:       [pch]	-- Ptr to input string.
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input,
//                          E_FAIL if call fails
//
//---------------------------------------------------------------------------
HRESULT HrParseEncryptionValue(         // RETURNS: HRESULT
    IN      CHAR *  pch                 // input encryption string
    )
{
    HRESULT hr  =   NOERROR;    // return value

    DEBUGPRIVATE("HrParseEncryptionValue()\n");

    // check input parameters
    hr = CHK_HrParseEncryptionValue(pch);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

	if (!_stricmp(pch, "ON"))
		bEncryptionNewPST = TRUE;
	else if (!_stricmp(pch, "OFF"))
		bEncryptionNewPST = FALSE;
	else
    {
	    hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

cleanup:

    RETURN(hr);
	
}


//$--HrParseEntryLine--------------------------------------------------------
//
// DESCRIPTION: Parse an ini file section entry line to determine what kind of
//				entry it is, and store the value.  Section entry lines are the
//				lines that follow the section header.
//
// INPUT:       [pch]	-- Ptr to input string.
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input,
//                          E_FAIL if call fails.
//
//---------------------------------------------------------------------------

HRESULT HrParseEntryLine(       // RETURNS: HRESULT
    IN      CHAR *  pch         // input line
    )
{
    HRESULT             hr  =                   NOERROR;
    INIFILEPARSEINFO *  aifpiEntry  =           NULL;
    CHAR                chTmp   =               0;
    INT                 cKeywords   =           0;
    INT                 i   =                   0;
    CHAR *              pchKeyword  =           NULL;

    DEBUGPRIVATE("HrParseEntryLine()\n");

    // Check input parameters
    hr = CHK_HrParseEntryLine(pch);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    if (ifstCurSection == IFST_MESSAGE)
    {
        aifpiEntry = aifpiMessageEntry;
        cKeywords = sizeof(aifpiMessageEntry)/sizeof(aifpiMessageEntry[0]);
    }
    else if (ifstCurSection == IFST_NEWPST)
    {
        aifpiEntry = aifpiNewPSTEntry;
        cKeywords = sizeof(aifpiNewPSTEntry)/sizeof(aifpiNewPSTEntry[0]);
    }
    else if (ifstCurSection == IFST_PROFILE)
    {
        aifpiEntry = aifpiProfileEntry;
        cKeywords = sizeof(aifpiProfileEntry)/sizeof(aifpiProfileEntry[0]);
    }
    else
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Save ptr to keyword.

    pchKeyword = pch;

    // Scan for end of keyword and delimit keyword, saving replaced char.

    while (*pch != cEquals && *pch != 0)
        pch++;

    if (*pch == 0)
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    chTmp = *pch;
    *pch  = 0;

    // Compare putative keyword against valid section keywords.

    for (i = 0; i < cKeywords; i++)
        if (!_stricmp(pchKeyword, aifpiEntry[i].pszKeyword))
            break;

    *pch = chTmp;

    if (i == cKeywords)
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    hr = aifpiEntry[i].HrParseFunction(pch + 1);

    // Store result if success.

    if ( SUCCEEDED(hr) )
    {
		// Check for duplicate entries in a section:

		if (aifpiEntry[i].piflv->fValid)
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

		aifpiEntry[i].piflv->fValid = TRUE;
        strcpy(aifpiEntry[i].piflv->achValue, pch + 1);
    }

cleanup:

    RETURN(hr);

}


//$--HrParseLine---------------------------------------------------------------
//
// DESCRIPTION: Parse an ini file line, and store the value if it is a section
//				entry line.
//
// INPUT:       None.
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_FAIL otherwise.
//
//---------------------------------------------------------------------------

HRESULT HrParseLine(VOID)       // RETURNS: HRESULT
{
    HRESULT     hr  				=       NOERROR;
    CHAR *      pch 				=       &achIniLine[0];
	BOOL		fCommentedSection	=		FALSE;	// TRUE if see commented section

    DEBUGPRIVATE("HrParseLine()\n");

    while ( isspace(*pch) > 0 )		// Skip leading line whitespace.
        pch++;

    if (*pch == 0)               // It is a blank line.
    {
        goto cleanup;
    }

    if (*pch == cSemiColon)           // It is a comment.
    {
		// Skip intervening white spaces and comments
		while ( (isspace(*pch) > 0) || (*pch == cSemiColon) )
		{
			pch++;
		}

		// Check to see if the commented out line is a section header.
		// If if is, then the effect is that the entire section is
		// commented out.
		if ( *pch == cBeginSectLine )
		{
			// have a commented-out section			
			fCommentedSection = TRUE;

			// continue on to next if statement
		}

		else
		{
			// commented out line, ignore it.
        	goto cleanup;
		}
    }

    if ( *pch == cBeginSectLine )  // It is a section, or is invalid
    {
		iSection = iLine;
        hr = HrParseSectionLine(
        	pch + 1, 			// pointer to section keyword
        	fCommentedSection);	// TRUE if have a commented-out section

        if ( FAILED(hr) )
        {
            goto cleanup;
        }
    }
    else                            // It is a section entry, or is invalid.
    {
        hr = HrParseEntryLine(pch);

        if ( FAILED(hr) )
        {
            goto cleanup;
        }
    }

cleanup:

    RETURN(hr);

}


//$--HrParseNonNullStringValue-----------------------------------------------
//
// DESCRIPTION: Parse a non-null string value for an entry line (ie., the
//				null string is not a permissible value).
//
// INPUT:       [pch]	-- Ptr to input string.
//
// HRESULT:     HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if invalid parameter,
//                          E_FAIL if call fails
//---------------------------------------------------------------------------

HRESULT HrParseNonNullStringValue(          // RETURNS: HRESULT
    IN      CHAR *  pch                     // input line
    )
{
    HRESULT hr  =   NOERROR;

    DEBUGPRIVATE("HrParseNonNullStringValue()\n");

    // Check input parameters.
    hr = CHK_HrParseNonNullStringValue(pch);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    if ( *pch == 0 )
    {
        hr = HR_LOG(E_FAIL);
    }

    RETURN(hr);

}


//$--HrParsePriorityValue----------------------------------------------------
//
// DESCRIPTION: Parse a PRIORITY= section entry line.
//
// INPUT:       [pch]	-- Ptr to input string.
//
// HRESULT:     HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input,
//                          E_FAIL if call fails
//
//---------------------------------------------------------------------------

HRESULT HrParsePriorityValue(           // RETURNS: HRESULT
    IN      CHAR *  pch                 // input line
    )
{
    HRESULT hr  =   NOERROR;    // return value

    DEBUGPRIVATE("HrParsePriorityValue()\n");

    // Check input parameters.
    hr = CHK_HrParsePriorityValue(pch);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

	if (!_stricmp(pch, "NORMAL"))
    {
		lPriorityCurMsg = PRIO_NORMAL;
        lImportanceCurMsg = IMPORTANCE_NORMAL;
    }
	else if (!_stricmp(pch, "HIGH"))
    {
		lPriorityCurMsg = PRIO_URGENT;
        lImportanceCurMsg = IMPORTANCE_HIGH;
    }
	else if (!_stricmp(pch, "LOW"))
    {
		lPriorityCurMsg = PRIO_NONURGENT;
        lImportanceCurMsg = IMPORTANCE_LOW;
    }
	else
    {
        hr = HR_LOG(E_FAIL);
    }

	RETURN(hr);

}


//$--HrParseSectionLine------------------------------------------------------
//
// DESCRIPTION: Parse an ini file section header line. 
//
// INPUT:       [pch]	-- Ptr to section keyword
//				fComment	--	TRUE if section is commented-out
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if invalid input,
//                          E_FAIL if call fails.
//
//---------------------------------------------------------------------------

HRESULT HrParseSectionLine(
    IN      CHAR *  pch,            // input line
	IN		BOOL fComment			// TRUE if section is commented
    )
{
    HRESULT     hr  =   NOERROR;
    CHAR        chTmp   =   0;
    CHAR *      pchKeyword  =   NULL;

    DEBUGPRIVATE("HrParseSectionLine()\n");

    // Check input parameters
    hr = CHK_HrParseSectionLine(pch, fComment);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

	InitSectionData(
		fComment);		// TRUE if section is commented

    // Save ptr to keyword.

    pchKeyword = pch;

    // Scan for end of keyword and delimit keyword, saving replaced char.

    while (!isspace(*pch) && *pch != cEndSectLine && *pch != 0)
        pch++;

    if (*pch == 0)
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    chTmp = *pch;
    *pch  = 0;

    // Compare putative keyword against valid section keywords.

    if (!_stricmp(pchKeyword, "message"))
    {
		// Numeric value may follow "message" keyword.  We don't use it,
		// but we do a rough check that what we are seeing is consistent
		// with what we expect.

        *pch = chTmp;

        while ( isspace(*pch) > 0 )
            pch++;

        if (!isdigit(*pch))
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

		pch++;

        while (isdigit(*pch))
            pch++;

        // Check for proper section entry termination.

        if (*pch == cEndSectLine && *(pch + 1) == 0)
        {
            ifstCurSection =	IFST_MESSAGE;
        }
    }
    else if (!_stricmp(pchKeyword, "newpst"))
    {
        // Check for proper section entry termination.
        // NewPST sections don't have a value.

        *pch = chTmp;

        if (*pch == cEndSectLine && *(pch + 1) == 0)
        {
            ifstCurSection =	IFST_NEWPST;
        }
    }
    else if (!_stricmp(pchKeyword, "profile"))
    {
        // Check for proper section entry termination.
        // Profile sections don't have a value.

        *pch = chTmp;

        if (*pch == cEndSectLine && *(pch + 1) == 0)
        {
            ifstCurSection =	IFST_PROFILE;
        }
    }
    else
    {
        hr = HR_LOG(E_FAIL);
        *pch = chTmp;   // Invalid section keyword.

        goto cleanup;

    }

cleanup:

    RETURN(hr);

}


//$--HrParseStringValue--------------------------------------------------------
//
// DESCRIPTION: Parse a string value for an entry line.
//
// INPUT:       [pch]	-- Ptr to input string.
//
// HRESULT:     HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input.
//
//---------------------------------------------------------------------------

HRESULT HrParseStringValue(     // RETURNS: HRESULT
    IN      CHAR *  pch         // input line
    )
{
    HRESULT hr  =   NOERROR;

    DEBUGPRIVATE("HrParseStringValue()\n");

    // Check input parameters.
    hr = CHK_HrParseStringValue(pch);
    
    // Anything is a valid string!

    RETURN(hr);

}


//$--HrParseTimeValue--------------------------------------------------------
//
// DESCRIPTION: Parse a TIME= section entry line.
//
// INPUT:       [pch]	-- Ptr to input string.
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input,
//                          E_FAIL if call fails.
//
//---------------------------------------------------------------------------

HRESULT HrParseTimeValue(           // RETURNS: HRESULT
    IN      CHAR *  pch             // input line
    )
{
    HRESULT hr  =   NOERROR;
    long    Hour    =   0;
    long    Minute  =   0;
    long    Second = 0;

    DEBUGPRIVATE("HrParseTimeValue()\n");

    // Check input parameters.
    hr = CHK_HrParseTimeValue(pch);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    if (!isdigit(*pch)          ||
        !isdigit(*(pch + 1))    ||
        *(pch + 2) != cColon)
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    Hour = atol(pch);

    if (Hour > 23)
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

	stCurMsg.wHour = (WORD)Hour;

    pch += 3;

    if (!isdigit(*pch)                              ||
        !isdigit(*(pch + 1))                        ||
        (*(pch + 2) != cColon && *(pch + 2) != 0))
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    Minute = atol(pch);

    if (Minute > 59)
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

	stCurMsg.wMinute = (WORD)Minute;

    if (*(pch + 2) == cColon)
    {
        pch += 3;

        if (!isdigit(*pch)                              ||
            !isdigit(*(pch + 1))                        ||
            *(pch + 2) != 0)
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        Second = atol(pch);

        if (Second > 59)
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }
    }

	stCurMsg.wSecond = (WORD)Second;

    if (Hour * 60L * 60L + Minute * 60L + Second >= 24L * 60L * 60L)
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

cleanup:

    RETURN(hr);

}

//$--HrProcessMessageSection---------------------------------------------------
//
// DESCRIPTION: Process the information parsed in a message section, creating
//				a message in a pst.
//
// INPUT:       None.
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_FAIL otherwise.
//
//---------------------------------------------------------------------------

HRESULT HrProcessMessageSection(VOID)        // RETURNS: HRESULT
{
	HRESULT			hr  =   NOERROR;
	LPADRLIST		lpRecips =	NULL;
	LPMAPIFOLDER	lpFolder =	NULL;
	LPMESSAGE		lpMsg =		NULL;

    DEBUGPRIVATE("HrProcessMessageSection()\n");

	// Confirm that a NewPST or Profile section has been parsed and a MAPI
	// session has been established.
	if (!lpSession)
	{
        hr = HR_LOG(E_FAIL);

		EventLogMsg(
			POPPST_ORDER_ERROR,
			1, SZ_BASE10(iSection),
			0);

		goto cleanup;
	}

	// Confirm that the Message section has the required section entries.

	if (!iflvDATE.fValid		||
		!iflvFOLDER.fValid		||
		!iflvFROM.fValid		||
		!iflvPRIORITY.fValid	||
		!iflvSUBJECT.fValid		||
		!iflvTIME.fValid		||
		!iflvTO.fValid)
	{
        hr = HR_LOG(E_FAIL);

		EventLogMsg(
			POPPST_MISSING_ERROR,
			2, TEXT("Message"), SZ_BASE10(iSection),
			0);

		goto cleanup;
	}

	// Convert message date/time to FILETIME.

	if (!SystemTimeToFileTime(&stCurMsg, &ftCurMsg))
	{
        INTERNAL_ERROR( TEXT("SystemTimeToFileTime()"), GetLastError());

        hr = HR_LOG(E_FAIL);
		goto cleanup;
	}

	// Open the specified folder, or if it does not exist, create it.
	// If the root folder was specified, the value of pRootFolder will
	// be returned.
    hr = HrOpenFolder(&lpFolder);

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

	// Create the message.
	hr = lpFolder->CreateMessage(NULL, MAPI_DEFERRED_ERRORS, &lpMsg);

	if (FAILED(hr))
	{
        INTERNAL_ERROR( TEXT("IMAPIFolder::CreateMessage()"), hr);

        hr = HR_LOG(E_FAIL);
		goto cleanup;
	}

	// Set the sender, subject, date/time, and priority properties.
    hr = HrSetMessageProperties(lpMsg);

    if ( FAILED(hr) )
    {
		goto cleanup;
    }

	// Write the message text, if any
	hr = HrWriteMessageText(lpMsg, iflvXTEXT.achValue);

    if ( FAILED(hr) )
    {
		goto cleanup;
    }

	// Resolve recipient name information.
	hr = HrResolveRecipientNames(&lpRecips);

    if ( FAILED(hr) )
    {
		goto cleanup;
    }

	// Set recipient info.
	hr = lpMsg->ModifyRecipients(MODRECIP_ADD, lpRecips);

	if (FAILED(hr))
	{
        INTERNAL_ERROR( TEXT("IMessage::ModifyRecipients()"), hr);

        hr = HR_LOG(E_FAIL);
		goto cleanup;
	}

	// If there is an attachment, create it.
	if (iflvXATTACH.fValid)
	{
		hr = HrCreateMessageAttachment(lpMsg, iflvXATTACH.achValue);

        if ( FAILED(hr) )
        {
			goto cleanup;
        }
	}

    // save the message!
	hr = lpMsg->SaveChanges(0);

	if (FAILED(hr))
	{
        INTERNAL_ERROR( TEXT("IMAPIProp::SaveChanges()"), hr);

        hr = HR_LOG(E_FAIL);
    	goto cleanup;
    }

	// Done!
	cMsgs++;

cleanup:

	if (lpRecips)
	{
		// Have to release the SPropVal allocations first.
		ULONG			i;

		for (i = 0; i < lpRecips->cEntries; i++)
			MAPIFREEBUFFER(lpRecips->aEntries[i].rgPropVals);

		MAPIFREEBUFFER(lpRecips);
	}
	
	ULRELEASE(lpMsg);

	if (lpFolder && lpFolder != lpRootFolder)
		ULRELEASE(lpFolder);

    RETURN(hr);

}


//$--HrProcessNewPSTSection----------------------------------------------------
//
// DESCRIPTION: Process the information parsed in a newpst section, creating
//				a temporary profile and new pst and logging onto a MAPI session
//				for the temporary profile.  Also open the new pst and its
//				root folder.
//
// INPUT:       None.
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_FAIL otherwise.
//
// Notes:		If this function fails, the error should be treated as a
//				fatal error.
//---------------------------------------------------------------------------

HRESULT HrProcessNewPSTSection(VOID)        // RETURNS: HRESULT
{
	HRESULT			hr  =   NOERROR;

    DEBUGPRIVATE("HrProcessNewPSTSection()\n");

	// Confirm that this is the first NewPST section we have encountered,
	// and there was not a Profile section.
	if (lpSession)
	{
        hr = HR_LOG(E_FAIL);

		EventLogMsg(
			POPPST_MUTUAL_EXCLUSIVENESS_ERROR,
			1, SZ_BASE10(iSection),
			0);

		goto cleanup;
	}

	// Confirm that it has the required section entries.

	if (!iflvENCRYPTION.fValid	||
		!iflvPATH.fValid		||
		!iflvPSTNAME.fValid	||
		!iflvPSTPASSWORD.fValid)
	{
        hr = HR_LOG(E_FAIL);

		EventLogMsg(
			POPPST_MISSING_ERROR,
			2, TEXT("NewPST"), SZ_BASE10(iSection),
            0);

		goto cleanup;
	}

	fTmpProf = TRUE; // Flag used to indicate we are using a temporary profile.

	// Create the requested PST.  This also creates a new profile, and we must
	// get a session on the new profile in order to further manipulate the PST.
	hr = HrCreatePersonalStore(iflvPATH.achValue,
					  bEncryptionNewPST ?
					  PSTF_COMPRESSABLE_ENCRYPTION :
					  PSTF_NO_ENCRYPTION,
					  iflvPSTNAME.achValue,
					  iflvPSTPASSWORD.achValue,
					  &lpszProfileName,
					  &lpszProfilePassword);

	if (FAILED(hr))
	{
		EventLogMsg(
			POPPST_NEWPST_ERROR,
			2, iflvPSTNAME.achValue, SZ_BASE16(hr),
			0);

		goto cleanup;
	}

	// Save profile values (they will be used later by HrProcessProfileSection()).

	iflvPROFILENAME.fValid = TRUE;

	strcpy(iflvPROFILENAME.achValue, lpszProfileName);

	iflvPROFILEPASSWORD.fValid = TRUE;

	strcpy(iflvPROFILEPASSWORD.achValue, lpszProfilePassword);

	// Log onto a session.

	hr = HrProcessProfileSection();

    if ( FAILED(hr) )
    {
		goto cleanup;
    }

    // warn the user that a temporary profile is being used
	EventLogMsg(
		POPPST_TEMPORARY_PROFILE_WARNING,
		0,
		0);

cleanup:

	RETURN(hr);

}


//$--HrProcessProfileSection-------------------------------------------------
//
// DESCRIPTION: Process the information parsed in a profile section, logging
//				onto a MAPI profile session and opening the message store, its
//				root folder, and the pab if one is available.
//
// INPUT:       None.
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_FAIL otherwise.
//
// Notes:		If this function fails, the error should be treated as a
//				fatal error.  On successful completion, lpSession, lpMdb, and
//				lpRootFolder are valid.  These are all opened here and left
//				open because they need to be open during message processing.
//
//---------------------------------------------------------------------------

HRESULT HrProcessProfileSection(VOID)       // RETURNS: HRESULT
{
	HRESULT			hr          =   NOERROR;
	LPSRowSet		lpRows      =	NULL;
    ULONG           cbEid       =   0;      // # bytes in entry identifier
    LPENTRYID       lpEid       =   NULL;   // entry identifier
    ULONG		    ulObjType   =   0;      // MAPI object type

    DEBUGPRIVATE("HrProcessProfileSection()\n");

	// Confirm that this is the first Profile section we have encountered,
	// and there was not a NewPST section.
	if (lpSession)
	{
        hr = HR_LOG(E_FAIL);

		EventLogMsg(
			POPPST_MUTUAL_EXCLUSIVENESS_ERROR,
			1, SZ_BASE10(iSection),
			0);

		goto cleanup;
	}

	// Confirm that it has the required section entries.

	if (!iflvPROFILEPASSWORD.fValid	||
		!iflvPROFILENAME.fValid)
	{
        hr = HR_LOG(E_FAIL);

		EventLogMsg(
			POPPST_MISSING_ERROR,
			2, TEXT("Profile"), SZ_BASE10(iSection),
            0);

		goto cleanup;
	}

	// Log on to the specified profile.

	hr = MAPILogonEx(0,
				   iflvPROFILENAME.achValue,
				   iflvPROFILEPASSWORD.achValue,
				   ulMapiLogonFlags,
				   &lpSession);

	if (FAILED(hr))
	{
		EventLogMsg(
			POPPST_LOGON_ERROR,
			2, iflvPROFILENAME.achValue, SZ_BASE16(hr),
            0);

        hr = HR_LOG(E_FAIL);
		goto cleanup;
	}

    ASSERTERROR(!FBadUnknown(lpSession), "Bad lpSession");

	// Find the default message store in the message stores table.
    hr = HrMAPIFindDefaultMsgStore(
                lpSession,      // MAPI session pointer
                &cbEid,         // entry identifier byte count
                &lpEid);        // entry identifier

    if ( FAILED(hr) )
    {
        INTERNAL_ERROR( TEXT("HrMAPIFindDefaultMsgStore"), hr);

        goto cleanup;
    }

	// Open the default message store.
	hr = lpSession->OpenMsgStore(
                0,
			    cbEid,  // entry id byte count
				lpEid,  // entry id
				NULL,
				MDB_WRITE | MAPI_DEFERRED_ERRORS | MDB_NO_DIALOG,  // want write access
				&lpMdb);    // MDB pointer

	if (FAILED(hr))
	{
		EventLogMsg(
			POPPST_OPEN_STORE_ERROR,
			2, iflvPROFILENAME.achValue, SZ_BASE16(hr),
            0);

        hr = HR_LOG(E_FAIL);
	    goto cleanup;
	}

    ASSERT_IUNKNOWN_PTR(lpMdb, "Bad lpMdb");

	// Open the root folder in the default message store.  OpenEntry() opens
	// the root folder if lpEntryID is NULL.
	hr = lpMdb->OpenEntry(0,
						  NULL,
						  NULL,
						  MAPI_MODIFY|MAPI_DEFERRED_ERRORS,
						  &ulObjType,
						  (LPUNKNOWN *)&lpRootFolder);

	if (FAILED(hr))
	{
        INTERNAL_ERROR( TEXT("IMsgStore::OpenEntry()"), hr);

        hr = HR_LOG(E_FAIL);
		goto cleanup;
	}

	if (ulObjType != MAPI_FOLDER)
	{
        INTERNAL_ERROR( TEXT("IMsgStore::OpenEntry()"), MAPI_E_UNEXPECTED_TYPE);

        hr = HR_LOG(E_FAIL);
		goto cleanup;
	}

    ASSERTERROR(!FBadUnknown(lpRootFolder), "Bad lpRootFolder");

    // open address book if not using a temporary profile
    if ( fTmpProf == FALSE )
    {
        // open the address book
	    hr = lpSession->OpenAddressBook(
	            0,              // window handle
	            NULL,           // interface pointer
	            AB_NO_DIALOG,   // don't want dialogue box
	            &lpAdrBook);    // address book pointer

	    if (FAILED(hr))
	    {
			EventLogMsg(
				POPPST_AB_ERROR,
				2, iflvPROFILENAME.achValue, SZ_BASE16(hr),
				0);

            hr = HR_LOG(E_FAIL);
            goto cleanup;
	    }

        ASSERTERROR(!FBadUnknown(lpAdrBook), "Bad lpAdrBook");

    }   // end if not using temporary profile

cleanup:

    // free MAPI buffers and release MAPI objects
    MAPIFREEBUFFER(lpEid);

	FREEPROWS(lpRows);

	RETURN(hr);

}

//$--HrResolveSenderName------------------------------------------------------
//
// DESCRIPTION: Resolve the sender's name, if possible.  
//              Also checks number of sender names.
//
// INPUT:       pszName --  sender's display name
//
// OUTPUT:      ppAdrList   --  pointer to address list pointer
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input,
//                          E_FAIL otherwise
//
// ---------------------------------------------------------------------------
HRESULT HrResolveSenderName(
        IN LPSTR pszName,   // sender's display name
        OUT LPADRLIST * ppAdrList)  // pointer to address list pointer
{
    HRESULT hr      	=   NOERROR;
    ULONG   cNames  	=   0;          // # of sender names
	LPSTR *	lppszTemp	=	NULL;		// array of string pointers

    const ULONG cProps  =   2;      // # of property values
	const LPSTR	pszSep	=	";";	// separator character

    // property value array
    SPropValue  rgPropVals[cProps]  =   {0};
    
    DEBUGPRIVATE("HrResolveSenderName()\n");

    hr = CHK_HrResolveSenderName(pszName, ppAdrList);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // Check number of sender names.  There should only be one.
	hr = HrStrTokAll(
		pszName,				// sender names
		(LPSTR) pszSeparator,	// separator character
		&cNames,				// number of sender names
		&lppszTemp);			// array of string pointers

    if ( FAILED(hr) )
    {
        INTERNAL_ERROR( TEXT("HrStrTokAll()"), hr);

        goto cleanup;
    }

    if ( cNames != 1 )
    {
		EventLogMsg(
			POPPST_FROM_ERROR,
			1, SZ_BASE10(iSection),
			0);

        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

	ASSERT_READ_PTR(lppszTemp, sizeof(LPSTR) * cNames, "Bad lppszTemp");

    // Only resolve sender name if we are not using a temporary
    // profile!
    if ( fTmpProf == FALSE )
    {
        // Set up property value with know values.
        rgPropVals[0].ulPropTag = PR_DISPLAY_NAME;
        rgPropVals[0].Value.lpszA = pszName;

        rgPropVals[1].ulPropTag = PR_RECIPIENT_TYPE;
        rgPropVals[1].Value.l = MAPI_TO;

        // Create an address list for our sender name.
        hr = HrMAPICreateAddressList(
                cProps,         // # of property values
                rgPropVals,     // property value array
                ppAdrList);     // address list pointer

        if ( FAILED(hr) )
        {
            INTERNAL_ERROR( TEXT("HrMAPICreateAddressList()"), hr);

            goto cleanup;
        }

        // Resolve the name
	    hr = lpAdrBook->ResolveName(
	            0,              // window handle
	            0, 
	            NULL, 
	            *ppAdrList);    // address list pointer

        // Handle case where sender name can't be resolved.
        if ( FAILED(hr) )
        {
            // some fatal error
			EventLogMsg(
				POPPST_SENDER_ERROR,
				3, pszName, SZ_BASE10(iSection), SZ_BASE16(hr),
				0);

            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        ASSERTERROR(!IsBadReadPtr(ppAdrList, sizeof(LPADRLIST)),
                    "Bad ppAdrList");
        ASSERTERROR(!IsBadReadPtr(*ppAdrList, sizeof(ADRLIST)),
                    "Bad *ppAdrList");

    }   // end if have a "real" address book

cleanup:

	// Free MAPI buffers
	MAPIFREEBUFFER(lppszTemp);

    RETURN(hr);

}

//$--HrResolveRecipientNames-------------------------------------------------
//
// DESCRIPTION: Get the properties needed for the recipients using the input
//				information and resolves the recipient names, if possible.
//
// OUTPUT       [lppAdrList]	-- Ptr to output address list with resolved
//								   names.
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input parameter,
//                          E_OUTOFMEMORY if memory problems
//                          E_FAIL if call fails.
//
//---------------------------------------------------------------------------

HRESULT HrResolveRecipientNames(            // RETURNS: HRESULT
	OUT		LPADRLIST *	lppAdrList      // address list pointer
	)
{
#define	CRECIPLST			3	// # of recipient lists

    HRESULT         hr  			=   NOERROR;
	ULONG			cRecips 		=   0;		// total # of recipients
	ULONG			cToRecips		=	0;		// # of TO recipients
	ULONG			cCCRecips		=	0;		// # of CC recipients
	ULONG			cBCCRecips		=	0;		// # of BCC recipients
	LPADRLIST		lpAdrList 		=	NULL;
	LPSTR *			ppch 			=   0;
	LPSTR *			lppszToRecips	=	NULL;	// array of tokenized TO recipients
	LPSTR *			lppszCCRecips	=	NULL;	// array of tokenized CC recipients
	LPSTR *			lppszBCCRecips	=	NULL;	// array of tokenized BCC recipients

	// Array of recipient INI file lines
	INIFILELINEVALUE *	apiflv[CRECIPLST]	=
	{
		&iflvTO,
		&iflvCC,
		&iflvBCC
	};

	// Array of recipient types
	LONG			aRecipTypes[CRECIPLST]	=	
	{
		MAPI_TO,
		MAPI_CC,
		MAPI_BCC
	};

	// Array of tokenized recipient names
	LPSTR **		rgRecipTokens[CRECIPLST]	=	
	{
		&lppszToRecips,
		&lppszCCRecips,
		&lppszBCCRecips
	};

	// Array of recipient counts
	ULONG *			rgcRecips[CRECIPLST]	=
	{
		&cToRecips,
		&cCCRecips,
		&cBCCRecips
	};

    DEBUGPRIVATE("HrResolveRecipientNames()\n");

    // Check input parameters.
    hr = CHK_HrResolveRecipientNames(lppAdrList);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    *lppAdrList = NULL; // initialize

	if ( iflvTO.fValid )
	{
		// Count the number of recipients to be resolved by scanning the strings
		// for semicolons.
		hr = HrStrTokAll(
			iflvTO.achValue,		// MAPI TO recipients
			(LPSTR) pszSeparator,	// separator character
			&cToRecips,				// # of TO recipients
			&lppszToRecips);		// array of tokenized recipients
		    
    	if ( FAILED(hr) )
    	{
            INTERNAL_ERROR( TEXT("HrStrTokAll()"), hr);

        	goto cleanup;
    	}

		// increment total # of recipients
		cRecips += cToRecips;

		ASSERT_READ_PTR(lppszToRecips, sizeof(LPSTR) * cToRecips, 
			"Bad lppszToRecips");
	}

	if (iflvCC.fValid)
    {
		hr = HrStrTokAll(
			iflvCC.achValue,		// MAPI CC recipients
			(LPSTR) pszSeparator,	// separator character
			&cCCRecips,				// # of CC recipients
			&lppszCCRecips);		// array of tokenized recipients

        if ( FAILED(hr) )
        {
            INTERNAL_ERROR( TEXT("HrStrTokAll()"), hr);

            goto cleanup;
        }

        cRecips += cCCRecips;

		ASSERT_READ_PTR(lppszCCRecips, sizeof(LPSTR) * cCCRecips, 
			"Bad lppszCCRecips");
    }

	if (iflvBCC.fValid)
    {
		hr = HrStrTokAll(
			iflvBCC.achValue,		// MAPI BCC recipients
			(LPSTR) pszSeparator,	// separator character
			&cBCCRecips,			// # of BCC recipients
			&lppszBCCRecips);		// array of tokenized recipients

        if ( FAILED(hr) )
        {
            INTERNAL_ERROR( TEXT("HrStrTokAll()"), hr);

            goto cleanup;
        }

        cRecips += cBCCRecips;

		ASSERT_READ_PTR(lppszBCCRecips, sizeof(LPSTR) * cBCCRecips, 
			"Bad lppszBCCRecips");
    }

	// Check that there is at least one recipient.
	if ( cRecips <= 0 )
	{
		EventLogMsg(
			POPPST_NEED_RECIPIENT_ERROR,
			1, SZ_BASE10(iSection),
			0);

		hr = HR_LOG(E_FAIL);
		goto cleanup;
	}

	// Set up an ADRLIST to be returned to caller.  THREE levels of allocation
	// are required!
	hr = MAPIAllocateBuffer(CbNewADRLIST(cRecips), (LPVOID *)&lpAdrList);

	if ( FAILED(hr) )
	{
        INTERNAL_ERROR( TEXT("MAPIAllocateBuffer()"), hr);

        hr = HR_LOG(E_OUTOFMEMORY);
		goto cleanup;
	}

	*lppAdrList = lpAdrList;

	{
		LPSPropValue	aPropVals   =   NULL;
        ULONG           cPropVals   =   2;
		ULONG			i           =   0;
		ULONG			j           =   0;
		LPADRENTRY		lpAdrEntry  =   NULL;
		LPSTR			lpszName    =   NULL;

		lpAdrList->cEntries = cRecips;

		// Initialize the ADRENTRY's prior to actually allocating the
		// SPropValue arrays.  This makes cleanup possible if there is an error.

		for (i = 0; i < cRecips; i++)
		{
			lpAdrList->aEntries[i].ulReserved1 =	0;
			lpAdrList->aEntries[i].cValues =		cPropVals;
			lpAdrList->aEntries[i].rgPropVals =		NULL;
		}

		// Now allocate and initialize the SPropValue arrays.
		for (i = 0; i < cRecips; i++)
		{
			hr = MAPIAllocateBuffer(cPropVals * sizeof(SPropValue),
								  (LPVOID *)&(aPropVals));
			if ( FAILED(hr) )
			{
                INTERNAL_ERROR( TEXT("MAPIAllocateBuffer()"), hr);

                hr = HR_LOG(E_OUTOFMEMORY);
				goto cleanup;
			}

			lpAdrList->aEntries[i].rgPropVals = aPropVals;

			aPropVals[0].ulPropTag =		PR_RECIPIENT_TYPE;
			aPropVals[0].Value.l =			0;

			aPropVals[1].ulPropTag =		PR_DISPLAY_NAME;
			aPropVals[1].Value.lpszA =		NULL;
		}

		// Now fill in the property values.  Note that we can count on the
		// recipient lists to be non-null strings, because we checked for
		// this during parsing.

		{
			lpAdrEntry = lpAdrList->aEntries;

			for (i = 0; i < CRECIPLST; i++)
			{
				if (!apiflv[i]->fValid)
					continue;

				// Retrieve current recipient list of type X.
				ppch =	*(rgRecipTokens[i]);

				ASSERTERROR(ppch != NULL, "Bad ppch");

				for ( j = 0; j < *(rgcRecips[i]); j++ )
				{
					// Retrieve current recipient
					lpszName = ppch[j];

					ASSERT_STRINGA_PTR(lpszName, "Bad lpszName");

					lpAdrEntry->rgPropVals[0].Value.l = aRecipTypes[i];

					hr = MAPIAllocateMore(
						cbStrLenA(lpszName),
						lpAdrEntry->rgPropVals,
						(LPVOID *) &lpAdrEntry->
							rgPropVals[1].Value.lpszA);

					if ( FAILED(hr) )
					{
                        INTERNAL_ERROR( TEXT("MAPIAllocateMore()"), hr);

                        hr = HR_LOG(E_OUTOFMEMORY);
						goto cleanup;
					}

					lstrcpyA(lpAdrEntry->rgPropVals[1].Value.lpszA, lpszName);

					lpAdrEntry++;

				}
			}
		}

        // if not using a temporary profile, try to resolve the
        // recipient names
        if ( fTmpProf == FALSE )
        {
		    // If we have an address book available, use it to resolve any names
		    // that you can.  If we don't, then whatever got entered as the user
		    // name remains as the display name.

		    // CAVEAT - It seems that MAPI has some sort of bug whereby the first
		    //			attempt to resolve a given name fails.  A subsequent
		    //			identical request will succeed, so the first of two
		    //			messages referencing a recipient won't be resolved, but
		    //			the second will.
	        hr = lpAdrBook->ResolveName(0, 0, NULL, lpAdrList);

            if ( (hr == MAPI_E_NOT_FOUND) || 
                 (hr == MAPI_E_AMBIGUOUS_RECIP) )
            {
                // non-fatal errors.  Just can't resolve
                // this recipient name.
				EventLogMsg(
					POPPST_RESOLVE_WARNING,
					2, SZ_BASE10(iSection), SZ_BASE16(hr),
                    0);

                hr = HR_LOG(NOERROR);

                // continue on.
            }

		    if ( FAILED(hr) )
		    {
                // Some un-recoverable error.
				EventLogMsg(
					POPPST_RESOLVE_ERROR,
					2, SZ_BASE10(iSection), SZ_BASE16(hr),
					0);

                hr = HR_LOG(E_FAIL);

	    		goto cleanup;
		    }

		    // Now look for problems reported in the returned ADRLIST.
		    for (i = 0; i < lpAdrList->cEntries; i++)
		    {
                HRESULT         hrT =   NOERROR;
                
			    lpAdrEntry = &lpAdrList->aEntries[i];

			    for (j = 0; j < lpAdrEntry->cValues; j++)
			    {
				    LPSPropValue	pPropVal;
    
	    			pPropVal = &lpAdrEntry->rgPropVals[j];

				    if (PROP_TYPE(pPropVal->ulPropTag == PT_ERROR))
					{
					    hrT = pPropVal->Value.err;

						break;
					}
                }   // end for this recipient

                if ( (hrT == MAPI_E_NOT_FOUND) ||
                     (hrT == MAPI_E_AMBIGUOUS_RECIP) )
                {
                    // not a fatal error.  Just can't
                    // resolve a particular recipient.	
					EventLogMsg(
						POPPST_RESOLVE_WARNING,
						2, SZ_BASE10(iSection), SZ_BASE16(hrT),
                        0);

                    hrT = HR_LOG(NOERROR);

                    // continue on.
                }

                // Print out error for this recipient, if any
		    	if ( FAILED(hrT) )
			    {
                    // Some non-recoverable error.
					EventLogMsg(
						POPPST_RESOLVE_ERROR,
						2, SZ_BASE10(iSection), SZ_BASE16(hrT),
                        0);

                    hr = HR_LOG(hrT);
                    goto cleanup;
			    }

                // continue with next recipient

		    }   // end for
        }   // end if not using temporary PST
	}

cleanup:

	// Free MAPI buffers
	MAPIFREEBUFFER(lppszToRecips);
	MAPIFREEBUFFER(lppszCCRecips);
	MAPIFREEBUFFER(lppszBCCRecips);

	// Actual cleanup of *lppAdrList and its substructures must be done by
	// caller!

    RETURN(hr);

}


//$--HrSetMessageProperties--------------------------------------------------
//
// DESCRIPTION: Set the sender, subject, date/time, and priority properties
//				for the input message.
//
// INPUT/OUTPUT:lpMsg 	-- Message for which properties are to be set.
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input,
//                          E_OUTOFMEMORY if memory problems.
//                          E_FAIL if call fails
//
//---------------------------------------------------------------------------

HRESULT HrSetMessageProperties(     // RETURNS: HRESULT
	IN OUT LPMESSAGE	lpMsg       // message pointer
	)
{
	HRESULT				hr  =           NOERROR;
	LPSPropProblemArray	lpProblems =	NULL;
    LPADRLIST           lpAdrList =     NULL;   // used to resolve sender's address
    ULONG               iProp   =       0;      // property value index
    LPSPropValue        lpEntry =       NULL;   // address list entry pointer
    ULONG               nValues =       NULL;   // # of property values

    // String buffers for resolved sender name values.
    CHAR                szFromAddr[cbMaxIniLine]  =   "";
    CHAR                szFromAdrTyp[cbMaxIniLine]=   "";    

    // property value indices
    const UINT          iMsgClass   =   0;
    const UINT          iPriority   =   1;
    const UINT          iImportance =   2;
    const UINT          iftDeliver  =   3;
    const UINT          iftSubmit   =   4;
    const UINT          iSubject    =   5;
    const UINT          iFromName   =   6;
    const UINT          iRepFromName=   7;
    const UINT          iDelete     =   8;

    const ULONG         cMinValues  =   9;
        
    // properties which are only set if using a real profile
    const UINT          iFromAddr   =   9;
    const UINT          iFromAdrTyp =   10;
    const UINT          iFromEID    =   11;
    const UINT          iFromKey    =   12;
    const UINT          iRepFromAddr=   13;
    const UINT          iRepFromAdrTyp= 14;
    const UINT          iRepFromEID =   15;
    const UINT          iRepFromKey =   16;

    // maximum number of property values
	const ULONG		    cMaxValues =	17;

    // array of property values
    SPropValue          aPropVals[cMaxValues]  =   {0};

    const UINT          cbEidMax            =   256;    // max EID size

    // entry identifier buffer
    SizedENTRYID(cbEidMax, eidFrom)         =   {0};

    DEBUGPRIVATE("HrSetMessageProperties()\n");

    // Check input parameters
    hr = CHK_HrSetMessageProperties(lpMsg);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // initiliaze # of property values
    nValues = cMinValues;

	aPropVals[iFromName].ulPropTag = PR_SENDER_NAME;
	aPropVals[iFromName].Value.lpszA = iflvFROM.achValue;

	aPropVals[iRepFromName].ulPropTag =	PR_SENT_REPRESENTING_NAME;
	aPropVals[iRepFromName].Value.lpszA =	iflvFROM.achValue;

	aPropVals[iSubject].ulPropTag =	PR_SUBJECT;
	aPropVals[iSubject].Value.lpszA = iflvSUBJECT.achValue;

    // PR_DELIVER_TIME is not transmittable.
    aPropVals[iftDeliver].ulPropTag = PR_DELIVER_TIME;
    aPropVals[iftDeliver].Value.ft = ftCurMsg;

    // PR_CLIENT_SUBMIT_TIME is transmittable
	aPropVals[iftSubmit].ulPropTag = PR_CLIENT_SUBMIT_TIME;
	aPropVals[iftSubmit].Value.ft =	ftCurMsg;

    aPropVals[iMsgClass].ulPropTag = PR_MESSAGE_CLASS;
    aPropVals[iMsgClass].Value.lpszA = "IPM.Note";

    aPropVals[iPriority].ulPropTag = PR_PRIORITY;
    aPropVals[iPriority].Value.l = lPriorityCurMsg;

    aPropVals[iImportance].ulPropTag = PR_IMPORTANCE;    
    aPropVals[iImportance].Value.l = lImportanceCurMsg;

    aPropVals[iDelete].ulPropTag = PR_DELETE_AFTER_SUBMIT;
    aPropVals[iDelete].Value.b = TRUE;

    // Resolve the sender's address if we are using a real
    // profile
    if ( fTmpProf == FALSE )
    {
        hr = HrResolveSenderName(
                iflvFROM.achValue,  // sender's display name
                &lpAdrList);        // address list pointer

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // Set the EMAIL_ADDRESS, ADDR_TYPE and ENTRYID properties
        // based on what HrResolveSenderName returned.
        lpEntry = lpAdrList->aEntries[0].rgPropVals;   // intialize entry pointer
        for ( iProp = 0; iProp < lpAdrList->aEntries[0].cValues; iProp++ )
        {
            switch ( lpEntry[iProp].ulPropTag )
            {
                case PR_DISPLAY_NAME:           
                    // update sender's name with resolved name
                    lstrcpyn(iflvFROM.achValue,
                    lpEntry[iProp].Value.lpszA, cbMaxIniLine);

                    break;

                case PR_ADDRTYPE:            
                    // fill in address type
                    lstrcpyn(
                        szFromAdrTyp, 
                        lpEntry[iProp].Value.lpszA,
                        cbMaxIniLine);

                    aPropVals[iFromAdrTyp].ulPropTag = PR_SENDER_ADDRTYPE;
                    aPropVals[iFromAdrTyp].Value.lpszA =
                        szFromAdrTyp;

                    aPropVals[iRepFromAdrTyp].ulPropTag = PR_SENT_REPRESENTING_ADDRTYPE;
                    aPropVals[iRepFromAdrTyp].Value.lpszA =
                        szFromAdrTyp;

                    break;

                case PR_EMAIL_ADDRESS:
                    // Fill in email address
                    lstrcpyn(
                        szFromAddr,
                        lpEntry[iProp].Value.lpszA,
                        cbMaxIniLine);

                    aPropVals[iFromAddr].ulPropTag = PR_SENDER_EMAIL_ADDRESS;
                    aPropVals[iFromAddr].Value.lpszA =
                        szFromAddr;

                    aPropVals[iRepFromAddr].ulPropTag = 
                        PR_SENT_REPRESENTING_EMAIL_ADDRESS;
                    aPropVals[iRepFromAddr].Value.lpszA =
                        szFromAddr;

                    break;

                case PR_ENTRYID:
                    // fill in entry identifier               
                    CopyMemory(
                        &eidFrom.ab,
                        lpEntry[iProp].Value.bin.lpb,
                        lpEntry[iProp].Value.bin.cb);

                    aPropVals[iFromEID].ulPropTag = PR_SENDER_ENTRYID;                                                        
                    aPropVals[iFromEID].Value.bin.cb =
                        lpEntry[iProp].Value.bin.cb;
                    aPropVals[iFromEID].Value.bin.lpb =
                        (BYTE *) &eidFrom.ab;                    

                    aPropVals[iRepFromEID].ulPropTag = PR_SENT_REPRESENTING_ENTRYID;
                    aPropVals[iRepFromEID].Value.bin.cb =
                        lpEntry[iProp].Value.bin.cb;
                    aPropVals[iRepFromEID].Value.bin.lpb =
                        (BYTE *) &eidFrom.ab;                    

                    break;
        
                case PR_SEARCH_KEY:
                    // fill in sender's seach key
                    aPropVals[iFromKey].ulPropTag = PR_SENDER_SEARCH_KEY;
                    aPropVals[iFromKey].Value.bin.cb =
                        lpEntry[iProp].Value.bin.cb;
                    aPropVals[iFromKey].Value.bin.lpb =
                        lpEntry[iProp].Value.bin.lpb;

                    aPropVals[iRepFromKey].ulPropTag = 
                        PR_SENT_REPRESENTING_SEARCH_KEY;
                    aPropVals[iRepFromKey].Value.bin.cb =
                        lpEntry[iProp].Value.bin.cb;
                    aPropVals[iRepFromKey].Value.bin.lpb =
                        lpEntry[iProp].Value.bin.lpb;

                    break;

                default:
                    // not concerned with this property
                    break;

            }   // end switch
        }   // end for

        // Re-set number of property values
        nValues = cMaxValues;

    }   // end if has real profile

    ASSERTERROR((nValues != 0), "Bad nValues");

	hr = lpMsg->SetProps(nValues, aPropVals, &lpProblems);

	if (FAILED(hr))
	{
        INTERNAL_ERROR( TEXT("IMAPIProp::SetProps()"), hr);

        hr = HR_LOG(E_FAIL);
		goto cleanup;
	}

	if (lpProblems != NULL)
	{
		ULONG	i;

		for (i = 0; i < lpProblems->cProblem; i++)
            INTERNAL_ERROR( TEXT("IMAPIProp::SetProps()"), lpProblems->aProblem[1].scode);								
		MAPIFREEBUFFER(lpProblems);

        hr = HR_LOG(E_FAIL);
		goto cleanup;
	}

cleanup:

    // Free MAPI buffers
    FREEPADRLIST(lpAdrList);

	RETURN(hr);

}


//$--HrWriteMessageText------------------------------------------------------
//
// DESCRIPTION:    Write the message text (PR_BODY & PR_RTF_COMPRESSED) 
//                 to the message, if any
//
// INPUT:
//
//		[lpMsg]			-- Message for which message text is to be written.
//		[lpszFilePath]	-- Path of file containing message text (may be null)
//
// RETURNS:     NOERROR if successful,
//              E_INVALIDARGS if bad input,
//              E_FAIL if call fails.
//
// Notes:		We use stream methods to do this, since the SetProps() has a
//				4KB limit for the size of a property you can set.
//
//---------------------------------------------------------------------------

HRESULT HrWriteMessageText(             // RETURNS: HRESULT
	IN		LPMESSAGE	lpMsg,          // message pointer
	IN		LPSTR		lpszFilePath    // message text path, may be null
	)
{
    HRESULT         hr          =   NOERROR;
	LPSTREAM	    lpStrm      =	NULL;
    ULONG           cbText      =   0;      // # bytes in message text
    ULONG           cbBody      =   0;      // # bytes in PR_BODY
    STATSTG         sStatStg    =   {0};    // stream status structure

    DEBUGPRIVATE("HrWriteMessageText()\n");

    // Check input parameters
    hr = CHK_HrWriteMessageText(lpMsg, lpszFilePath);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // If no message text, then we are done.
    if ( *lpszFilePath == 0 )
    {
        goto cleanup;
    }

    // Create the PR_BODY property (needed by the PST, which is not an
    // rich-text aware store) from the message body file data.
    hr = HrMAPISetPropFromFile(
        lpMsg,              // pointer to message object
        PR_BODY,            // property tag
        lpszFilePath,       // pointer to source file name
        &cbBody);           // # bytes in message body

    if ( FAILED(hr) )
    {	
        INTERNAL_ERROR( TEXT("HrMAPISetPropFromFile()"), hr);

        goto cleanup;
    }

    // Build the RTF compressed data for the message (needed
    // for RTF-aware stores, such as the Exchange MDB).
    // First, open a virtual (bufferred) stream on the input text file.
    hr = HrOpenVirtualStreamOnFile(
        MAPIAllocateBuffer,     // allocation routine
        MAPIFreeBuffer,         // deallocation routine
        STGM_READ | STGM_SHARE_EXCLUSIVE,	// interface flags
        lpszFilePath,           // file name
        NULL,                   // file prefix
        &lpStrm);               // stream pointer

    if ( FAILED(hr) )
    {
        INTERNAL_ERROR( TEXT("HrOpenVirtualStreamOnFile()"), hr);

        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    ASSERT_IUNKNOWN_PTR(lpStrm, "Bad lpStrm");

    // Determine size of stream (not necessarily size of PR_BODY!)
    hr = lpStrm->Stat(
        &sStatStg,          // status structure pointer
        0);                 // flags

    if ( FAILED(hr) )
    {
        INTERNAL_ERROR( TEXT("VSOF::Stat()"), hr);

        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    cbText = sStatStg.cbSize.LowPart;

    // See if body if too big for us to handle
    if ( sStatStg.cbSize.HighPart > 0 )
    {
		EventLogMsg(
			POPPST_BODY_ERROR,
			1, SZ_BASE10(iSection),
            0);

        hr = HR_LOG(E_NOTIMPL);
        goto cleanup;
    }

    // Create RTF compressed property from the ASCII text
    hr = HrTextToRTFCompressed(
            cbText, // # of bytes of text
            lpStrm, // text stream pointer
			0,		// # of attachment w/ rendering positions
			NULL,	// array of attachment rendering positions
            lpMsg,  // message pointer
			0);		// use current code page

    if ( FAILED(hr) )
    {
        INTERNAL_ERROR( TEXT("HrTextToRTFCompressed()"), hr);

        goto cleanup;
    }

    // we are done.

cleanup:

	ULRELEASE(lpStrm);

	RETURN(hr);
}
