//$--proxygen.c-----------------------------------------------------------------
//
//  This file implements a proxy address generating dll for SMTP style 
//  address@domain addresses (although can be used for any address type that
//  matches these conventions).
//
//  Proxies are generated from some combination of mailbox name, display name,
//  given name and surname (with spaces and other illegal characters replaced
//  or deleted) using the template specified in the site level proxy generated
//  by your setup program or the Microsoft Exchange Administrator program.
//  See the function header for rcGenerateProxy for details.
//
//  All functions will attempt to write an event log entry in the case of any
//  failure other than RC_MEMORY.
// 
// Copyright Microsoft Corporation 1986-1996,  All Rights Reserved
// -----------------------------------------------------------------------------

//
// Include Files
// --------------

#include "proxygen.h"
#include "proxyinf.h"
#include "proxymsg.h"

//
// Defines
// -------

#define FREE(x) { if((x) != NULL) { free((void *)(x)); (x) = NULL; } }

#define MAX(a,b) a>b?a:b

typedef	DWORD		IES;

// RcInitProxies parses 3 data components out of the site proxy as follows:
//   ADDRESS-TYPE ":" FORMAT "@" DOMAIN
// For example, if the site proxy were "SMTP:%m@microsoft.com" then
//   ADDRESS TYPE is "SMTP"
//   FORMAT is "%m"
//   DOMAIN is "microsoft.com"
// Once these components are parsed out they are stored in the PROXYSESSION
// structure and accessed using the macros below.

typedef struct _proxysession
{
    LPWSTR      pszServer;
    LPWSTR      pszFormat;
    LPWSTR      pszType;
    ULONG       cchType;
    LPWSTR      pszDomain;
    ULONG       cchDomain;
} PROXYSESSION, *PPROXYSESSION;

#define GET_SITE_FORMAT(x)     ((PPROXYSESSION)(x))->pszFormat
#define GET_SITE_TYPE(x)       ((PPROXYSESSION)(x))->pszType
#define GET_SITE_TYPE_CCH(x)   ((PPROXYSESSION)(x))->cchType
#define GET_SITE_DOMAIN(x)     ((PPROXYSESSION)(x))->pszDomain
#define GET_SITE_DOMAIN_CCH(x) ((PPROXYSESSION)(x))->cchDomain
#define GET_SERVER(x)          ((PPROXYSESSION)(x))->pszServer

// The translation table from unicode to SMTP legal (subset of 7-bit ASCII)
// characters is indexed from 0 to MAX_TRANSLATE_TABLE.  Characters outside
// the range of the translation table are deleted.  Do not change this 
// constant without changing the translation table defined locally to 
// RcGenerateUserProxy().
#define MAX_TRANSLATE_TABLE     255

//
// Globals
// -------

const PWSTR pszEventSource         	= L"EDKProxy";
const WCHAR chAddressTypeDelimiter  = (WCHAR)':';
const WCHAR chDomainDelimiter       = (WCHAR)'@';
const PWSTR pszDefaultFormat        = L"%m";
const ULONG cchDefaultFormat        = 2;

//  Local Function Prototypes
//  -------------------------

RC rcScanAndAppend(IN char *        sAnsitoSMTPMap,         // char replacement table
                   IN LPWSTR        pszSource,              // source buffer
                   IN OUT LPWSTR    pszDest,                // dest buffer
                   IN OUT ULONG *   piDest,                 // current index in dest buffer
                   IN ULONG         iMaxDest);              // max dest buffer index

BOOL fIsWhiteSpaceW(WCHAR wc);

VOID TrimW(IN OUT PWSTR pwstrSrc);

VOID LogError(LPWSTR pszServer, IES ies, WORD wEventType, LPWSTR rgwsz[], WORD cwsz);

RC RcGenerateUserProxy(                 // RETURNS: RC_SUCCESS RC_MEMORY RC_ERROR
    IN LPWSTR pwstrUserFormat,          // Format string for user part of proxy
    IN LPWSTR pwstrServer,              // Server name
    IN PRECIPIENTINFO pRecipientInfo,   // Recipient specific details. 
    INT nRetries,                       // Number of times this function
                                        //   has previously been called with
                                        //   this value for pRecipientInfo.
    IN OUT LPWSTR pwstrUserProxy,       // user part of SMTP proxy address
    OUT ULONG * pcchUserProxy);         // count of num chars in pwstrUserProxy



//$--RcInitProxies--------------------------------------------------------------
//  Parses and makes the site specific information accessible to the 
//  RcGenerateProxy, RcUpdateProxy, RcValidateProxy, RcValidateSiteProxy and
//  CloseProxies functions. 
//
//  The pwstrSiteProxy parameter is required as it cannot be defaulted for this
//  type of address.
// -----------------------------------------------------------------------------
RC RcInitProxies(               // RETURNS:  RC_MEMORY RC_ERROR RC_SUCCESS
    IN LPWSTR pwstrSiteProxy,   // The site proxy for this address type. 
    IN LPWSTR pszServer,        // Exchange Server name
    OUT HANDLE *phProxySession) // Handle to the proxy session.
{
    RC     rc           = RC_ERROR;
    LPWSTR pszType      = NULL;
    ULONG  cchType      = 0;
    LPWSTR pszFormat    = NULL;
    ULONG  cchFormat    = 0;
    LPWSTR pszDomain    = NULL;
    ULONG  cchDomain    = 0;
    LPWSTR pszAt        = NULL;
    LPWSTR pszColon     = NULL;

    // Verify Input Parameters

    if (pszServer == NULL)
    {
        // invalid arguments - internal error
        // can't write event log since no server name
        rc = RC_ERROR;
        goto error;
    }
                
    // The domain proxy must be available so check this first

    if (pwstrSiteProxy == NULL)
    {
		LogError(
		    pszServer,
		    iesNoSiteProxy,
		    EVENTLOG_ERROR_TYPE,
		    NULL,
		    0);
        rc = RC_ERROR;
        goto error;
    }

    // Initialize output parameter

    *phProxySession = NULL;

    // Allocate a proxy session structure

    *phProxySession = (HANDLE) malloc(sizeof(PROXYSESSION));
    if (*phProxySession == NULL)
    {
        rc = RC_MEMORY;
        goto error;
    }

    // Initialize elements of *phProxySession

    GET_SERVER(*phProxySession) = NULL;
    GET_SITE_FORMAT(*phProxySession) = NULL;
    GET_SITE_DOMAIN(*phProxySession) = NULL;
    GET_SITE_DOMAIN_CCH(*phProxySession) = 0;
    GET_SITE_TYPE(*phProxySession) = NULL;
    GET_SITE_TYPE_CCH(*phProxySession) = 0;

    // Trim blanks from pwstrSiteProxy

    TrimW(pwstrSiteProxy);

    // Validate pwstrSiteProxy, must be "TYPE:x@y" where x is 0 or more chars
    // up to the first colon and y is at least 1 char

    cchDomain = lstrlenW(pwstrSiteProxy);
    pszAt = wcschr(pwstrSiteProxy, chDomainDelimiter);
    pszColon = wcschr(pwstrSiteProxy, chAddressTypeDelimiter);
    
    if ((cchDomain < 4) ||  // min size = T:@y
        (pszColon == NULL) ||       // no colon
        (*pszColon != chAddressTypeDelimiter) || 
        (pwstrSiteProxy[0] == chAddressTypeDelimiter)) // 1st char is :, no addr type
    {
        // pwstrSiteProxy is invalid

   		LPWSTR rgwsz[] = 
		{
			pwstrSiteProxy
		};

		LogError(
		    pszServer,
		    iesBadSiteProxy,
		    EVENTLOG_ERROR_TYPE,
		    rgwsz,
		    1);

        rc = RC_ERROR;
        goto error;
    }

    // Split site proxy into it's component parts
    // ------------------------------------------

    // replace : with 0 temporarily

    *pszColon = 0;

    // get address type

    cchType = lstrlenW(pwstrSiteProxy);

    pszType = malloc((cchType + 1) * sizeof(WCHAR));

    if (pszType == NULL)
    {
        rc = RC_MEMORY;
        goto error;
    }

    lstrcpyW(pszType, pwstrSiteProxy);

    // Restore ':'

    *pszColon = chAddressTypeDelimiter;

    // Check site proxy again for more validation

    if ((pwstrSiteProxy[cchType] != chAddressTypeDelimiter) ||
        (pszAt == NULL) ||
        (*pszAt != chDomainDelimiter))
    {
        // pwstrSiteProxy is invalid

   		LPWSTR rgwsz[] = 
		{
			pwstrSiteProxy
		};

		LogError(
		    pszServer,
		    iesBadSiteProxy,
		    EVENTLOG_ERROR_TYPE,
		    rgwsz,
		    1);

        rc = RC_ERROR;
        goto error;
    }

    // replace @ with 0 temporarily

    *pszAt = 0;

    // get format part
    
    cchFormat = lstrlenW(&(pwstrSiteProxy[cchType+1]));

    if (cchFormat == 0)
    {
        // use default format
        
        pszFormat = malloc((lstrlenW(pszDefaultFormat) + 1) * sizeof(WCHAR));
    
        if (pszFormat == NULL)
        {
            rc = RC_MEMORY;
            goto error;
        }
        
        lstrcpyW(pszFormat, pszDefaultFormat);
    }
    else
    {
        // pull format out of site proxy

        pszFormat = malloc((cchFormat+1)*sizeof(WCHAR));
    
        if (pszFormat == NULL)
        {
            rc = RC_MEMORY;
            goto error;
        }
    
        lstrcpyW(pszFormat, &(pwstrSiteProxy[cchType])+1);
    }

    // get domain part
    
    cchDomain = lstrlenW(pszAt+1);
    pszDomain = malloc((cchDomain+1)*sizeof(WCHAR));

    if (pszDomain == NULL)
    {
        rc = RC_MEMORY;
        goto error;
    }
    
    lstrcpyW(pszDomain, (pszAt+1));

    // Restore '@'

    *pszAt = chDomainDelimiter;

    // Set structure members

    GET_SERVER(*phProxySession) = pszServer;
    GET_SITE_FORMAT(*phProxySession) = pszFormat;
    GET_SITE_DOMAIN(*phProxySession) = pszDomain;
    GET_SITE_DOMAIN_CCH(*phProxySession) = cchDomain;
    GET_SITE_TYPE(*phProxySession) = pszType;
    GET_SITE_TYPE_CCH(*phProxySession) = cchType;

    rc = RC_SUCCESS;
    goto cleanup;

error:

    FREE(*phProxySession);
    FREE(pszType);
    FREE(pszFormat);
    FREE(pszDomain);

cleanup:

    return rc;
}


//$--RcGenerateUserProxy--------------------------------------------------------
//  Private helper function: Generates the user part of the proxy (before the 
//  '@') given the format portion of the site proxy and the recipient info.
// -----------------------------------------------------------------------------
RC RcGenerateUserProxy(                 // RETURNS: RC_SUCCESS RC_MEMORY RC_ERROR
    IN LPWSTR pwstrUserFormat,          // Format string for user part of proxy
    IN LPWSTR pwstrServer,              // Server name
    IN PRECIPIENTINFO pRecipientInfo,   // Recipient specific details. 
    INT nRetries,                       // Number of times this function
                                        //   has previously been called with
                                        //   this value for pRecipientInfo.
    IN OUT LPWSTR pwstrUserProxy,       // user part of SMTP proxy address
    OUT ULONG * pcchUserProxy)          // count of num chars in pwstrUserProxy
{
    RC      rc                          = RC_ERROR;
    LPWSTR  pszLocalFormat              = NULL;
    BOOL    fFreeLocalFormat            = FALSE;
    ULONG   iProxyBuffer                = 0,
            iFormat                     = 0,
            cchFormat                   = 0;
    BOOL    fEscape                     = FALSE;
    char sAnsitoSMTPMap[] = 
    {   // SMTP        ANSI        Byte
            0,      // null         00
            0,      // (control)    01
            0,      // (control)    02
            0,      // (control)    03
            0,      // (control)    04
            0,      // (control)    05
            0,      // (control)    06
            0,      // (control)    07
            0,      // (control)    08
            0,      // (control)    09
            0,      // (control)    10
            0,      // (control)    11
            0,      // (control)    12
            0,      // (control)    13
            0,      // (control)    14
            0,      // (control)    15
            0,      // (control)    16
            0,      // (control)    17
            0,      // (control)    18
            0,      // (control)    19
            0,      // (control)    20
            0,      // (control)    21
            0,      // (control)    22
            0,      // (control)    23
            0,      // (control)    24
            0,      // (control)    25
            0,      // (control)    26
            0,      // (control)    27
            0,      // (control)    28
            0,      // (control)    29
            0,      // (control)    30
            0,      // (control)    31
            0,      // space        32 
            '!',    // !            33
            0,      // "            34 ** special **
            '#',    // #            35
            '$',    // $            36
            '%',    // %            37
            '&',    // &            38
            39,     // '            39
            0,      // (            40 ** special **
            0,      // )            41 ** special **
            '*',    // *            42
            '+',    // +            43
            0,      // ,            44 ** special **
            '-',    // -            45
            '.',    // .            46 ** This is a special but is ok here **
            '/',    // /            47
            '0',    // 0            48
            '1',    // 1            49
            '2',    // 2            50
            '3',    // 3            51
            '4',    // 4            52
            '5',    // 5            53
            '6',    // 6            54
            '7',    // 7            55
            '8',    // 8            56
            '9',    // 9            57
            0,      // :            58 ** special **
            0,      // ;            59 ** special **
            0,      // <            60 ** special **
            '=',    // =            61 
            0,      // >            62 ** special **
            '?',    // ?            63
            0,      // @            64 ** special **
            'A',    // A            65
            'B',    // B            66
            'C',    // C            67
            'D',    // D            68
            'E',    // E            69
            'F',    // F            70
            'G',    // G            71
            'H',    // H            72
            'I',    // I            73
            'J',    // J            74
            'K',    // K            75
            'L',    // L            76
            'M',    // M            77
            'N',    // N            78
            'O',    // O            79
            'P',    // P            80
            'Q',    // Q            81
            'R',    // R            82
            'S',    // S            83
            'T',    // T            84
            'U',    // U            85
            'V',    // V            86
            'W',    // W            87
            'X',    // X            88
            'Y',    // Y            89
            'Z',    // Z            90
            0,      // [            91 ** special **
            '^',    // ^            92
            0,      // ]            93 ** special **
            0,      // ,            94 ?? - doesn't translate
            '_',    // _            95 
            '`',    // `            96
            'a',    // a            97
            'b',    // b            98
            'c',    // c            99
            'd',    // d            100
            'e',    // e            101
            'f',    // f            102
            'g',    // g            103
            'h',    // h            104
            'i',    // i            105
            'j',    // j            106
            'k',    // k            107
            'l',    // l            108
            'm',    // m            109
            'n',    // n            110
            'o',    // o            111
            'p',    // p            112
            'q',    // q            113
            'r',    // r            114
            's',    // s            115
            't',    // t            116
            'u',    // u            117
            'v',    // v            118
            'w',    // w            119
            'x',    // x            120
            'y',    // y            121
            'z',    // z            122
            '{',    // {            123
            '|',    // |            124
            '}',    // }            125
            '~',    // ~            126
            0,      // del          127
            0,      // (control)    128
            0,      // (control)    129
            0,      // (control)    130
            0,      // (control)    131
            0,      // (control)    132
            0,      // (control)    133
            0,      // (control)    134
            0,      // (control)    135
            0,      // (control)    136
            0,      // (control)    137
            0,      // (control)    138
            0,      // (control)    139
            0,      // (control)    140
            0,      // (control)    141
            0,      // (control)    142
            0,      // (control)    143
            0,      // (control)    144
            0,      // (control)    145
            0,      // (control)    146
            0,      // (control)    147
            0,      // (control)    148
            0,      // (control)    149
            0,      // (control)    150
            0,      // (control)    151
            0,      // (control)    152
            0,      // (control)    153
            0,      // (control)    154
            0,      // (control)    155
            0,      // (control)    156
            0,      // (control)    157
            0,      // (control)    158
            0,      // (control)    159
            0,      // space        160
            0,      // 1st exclamn  161
            'C',    // cents        162
            'L',    // pounds       163
            'P',    // phi          164
            'Y',    // yen          165
            'I',    // pipe         166
            'S',    // section      167
            0,      // "            168
            'C',    // copyright    169
            'A',    // a underscore 170
            0,      // <<           171
            0,      // not          172
            '-',    // -            173
            'R',    // registered   174
            0,      // bar          175
            0,      // degree       176
            0,      // plus/minus   177
            '2',    // supers 2     178
            '3',    // supers 3     179
            0,      // '            180
            'M',    // mu           181
            'P',    // paragraph    182
            0,      // "            183
            0,      // ,            184
            '1',    // supers 1     185
            'O',    // o underscore 186
            0,      // >>           187
            0,      // 1/4          188
            0,      // 1/2          189
            0,      // 3/4          190
            0,      // 1st question 191
            'A',    // A grave      192
            'A',    // A acute      193
            'A',    // A circumflex 194
            'A',    // A tilde      195
            'A',    // A umlaut     196
            'A',    // A dot        197
            'A',    // AE ligature  198
            'C',    // C cedilla    199
            'E',    // E grave      200
            'E',    // E acute      201
            'E',    // E circumflex 202
            'E',    // E umlaut     203
            'I',    // I grave      204
            'I',    // I acute      205
            'I',    // I circumflex 206
            'I',    // I umlaut     207
            'D',    // D dash       208
            'N',    // N tilde      209
            'O',    // O grave      210
            'O',    // O acute      211
            'O',    // O circumflex 212
            'O',    // O tilde      213
            'O',    // O umlaut     214
            'X',    // multiplicn   215
            '0',    // 0 slash      216
            'U',    // U grave      217
            'U',    // U acute      218
            'U',    // U circumflex 219 
            'U',    // U umlaut     220
            'Y',    // Y acute      221
            'T',    // iapta        222
            'B',    // beta         223
            'a',    // a grave      224
            'a',    // a acute      225
            'a',    // a circumflex 226
            'a',    // a tilde      227
            'a',    // a umlaut     228
            'a',    // a dot        229
            'a',    // ae ligature  230
            'c',    // c cedilla    231
            'e',    // e grave      232
            'e',    // e acute      233
            'e',    // e circumflex 234
            'e',    // e umlaut     235
            'i',    // i grave      236
            'i',    // i acute      237
            'i',    // i circumflex 238
            'i',    // i umlaut     239
            'd',    // d dash       240
            'n',    // n tilde      241
            'o',    // o grave      242
            'o',    // o acute      243
            'o',    // o circumflex 244
            'o',    // o tilde      245
            'o',    // o umlaut     246
            0,      // divide       247
            '0',    // o slash      248
            'u',    // u grave      249
            'u',    // u acute      250
            'u',    // u circumflex 251 
            'u',    // u umlaut     252
            'y',    // y acute      253
            't',    // iapta        254
            'y'     // y umlaut     255
    };
 
    // Verify Input Parameters

    if  (pwstrServer == NULL)
    {
        // invalid arguments - internal error
        // can't write event log since no server name
        rc = RC_ERROR;
        goto cleanup;
    }
                
    if ((pwstrUserFormat == NULL) ||
        (pwstrServer == NULL) ||
        (pRecipientInfo == NULL) ||
        (pwstrUserProxy == NULL))
    {
        // invalid arguments - internal error

		LogError(
		    pwstrServer,
		    iesProxyInternalFailure,
		    EVENTLOG_ERROR_TYPE,
		    NULL,
		    0);
        rc = RC_ERROR;
        goto cleanup;
    }
    
    // Initialize output parameters

    *pwstrUserProxy = 0;
    *pcchUserProxy = 0;

    // Figure out what format to use based on nRetries
    // -----------------------------------------------

    if (nRetries == 0)
    {
        pszLocalFormat = pwstrUserFormat;
    }
    else if (nRetries == 1)
    {
        pszLocalFormat = pszDefaultFormat;
    }
    else if (nRetries > 1)
    {

		// Reason for use of random numbers as suffix to alias name in proxy generation:
		//
		// The Caller of RcGenerateProxy() calls RcGenerateProxy() to generate the
		// proxy and RcGenerateProxy() calls RcGenerateUserProxy(). The user part of 
		// proxy is generated in this function and returned to RcGenerateProxy() which 
		// then using this user part, generates full proxy address and returns to its 
		// caller. The caller function then varifies the generated proxy and if it
		// finds out that generated proxy is not unique (ie. similar proxy 
		// address already exists), then it calls RcGenerateProxy with incremented
		// nRetries value. This keeps on going in the loop as long as
		// nRetries <= PROXY_MAX_RETRIES After those many attempts it gives up and 
		// logs error.
		//
		// To avoid this situation, instead of using nRetries as the suffix to alias
		// name, we use randomly generated number as the suffix, which reduces the 
		// probability of non-unique proxy address.


		INT   iSuffix;
		INT   i;
		WCHAR pszSuffix[20]; // temp buffer used to convert long to string
	
		srand((unsigned int)GetTickCount()); // Seed the random number generator.
	
		// The following makes sure that with subsequent calls, if the TickCount
		//   doesn't change, we still get something random in most cases.
		for (i=0;i < nRetries; i++)
			rand();
	
		iSuffix = rand();
	
		_itow(iSuffix, pszSuffix, 10); // 10 is base
		
		pszLocalFormat = malloc(
            (cchDefaultFormat + lstrlenW(pszSuffix) + 1) * sizeof(WCHAR));

        if (pszLocalFormat == NULL)
        {
            rc = RC_MEMORY;
            goto cleanup;
        }
        
        fFreeLocalFormat = TRUE;
        wsprintfW(pszLocalFormat, L"%s%s", pszDefaultFormat, pszSuffix);

    }
    else
    {
        // nRetries is negative - nonsensical or nRetries is so big its negative

   		LPWSTR rgwsz[] = 
		{
			pRecipientInfo->pszDisplayName
		};

		LogError(
		    pwstrServer,
		    iesUnableToCreateUniqueProxy,
		    EVENTLOG_ERROR_TYPE,
		    rgwsz,
		    1);

        rc = RC_ERROR;
        goto cleanup;
    }

    cchFormat = lstrlenW(pszLocalFormat);

    // Parse the format string 
    // -----------------------

    fEscape = FALSE;

    for (iFormat = 0; iFormat < cchFormat; iFormat++)
    {
        if (fEscape)
        {
            // next character indicates reason for escape

            switch (pszLocalFormat[iFormat])
            {
            
            case ('%'):
                if (iProxyBuffer+1 < cchMaxProxyValue)
                {
                    pwstrUserProxy[iProxyBuffer++] = '%';
                    pwstrUserProxy[iProxyBuffer] = 0;
                }
                else
                {
                    // Can't fit character in buffer

   		  			LPWSTR rgwsz[] = 
					{
						pRecipientInfo->pszDisplayName
					};
               
  	    		    LogError(
	    	    	    pwstrServer,
				        iesProxyToBig,
				        EVENTLOG_ERROR_TYPE,
				        rgwsz,
				        1);

                    rc = RC_ERROR;
                    goto cleanup;
                }
                break;
                
            case ('s'): // surname
                rc = rcScanAndAppend(
                    sAnsitoSMTPMap,                 // char replacement table
                    pRecipientInfo->pszLastName,    // source buffer
                    pwstrUserProxy,                 // dest buffer
                    &iProxyBuffer,                  // current index in dest buffer
                    cchMaxProxyValue-1);            // dest buffer max index

                if (RC_FAILED(rc))
                {
                    // Can't fit last name in buffer

   		  			LPWSTR rgwsz[] = 
					{
						pRecipientInfo->pszDisplayName
					};
               
  	    		    LogError(
	    	    	    pwstrServer,
				        iesProxyToBig,
				        EVENTLOG_ERROR_TYPE,
				        rgwsz,
				        1);

                    rc = RC_ERROR;
                    goto cleanup;
                }
                break;

            case ('g'): // given name
                rc = rcScanAndAppend(
                    sAnsitoSMTPMap,                 // char replacement table
                    pRecipientInfo->pszFirstName,   // source buffer
                    pwstrUserProxy,                 // dest buffer
                    &iProxyBuffer,                  // current index in dest buffer
                    cchMaxProxyValue-1);            // dest buffer size

                if (RC_FAILED(rc))
                {
                    // Can't fit given name in buffer

   		  			LPWSTR rgwsz[] = 
					{
						pRecipientInfo->pszDisplayName
					};
               
  	    		    LogError(
	    	    	    pwstrServer,
				        iesProxyToBig,
				        EVENTLOG_ERROR_TYPE,
				        rgwsz,
				        1);

                    rc = RC_ERROR;
                    goto cleanup;
                }
                break;

            case ('d'): // display name
                rc = rcScanAndAppend(
                    sAnsitoSMTPMap,                 // char replacement table
                    pRecipientInfo->pszDisplayName, // source buffer
                    pwstrUserProxy,                 // dest buffer
                    &iProxyBuffer,                  // current index in dest buffer
                    cchMaxProxyValue-1);            // dest buffer size

                if (RC_FAILED(rc))
                {
                    // Can't fit display name in buffer

   		  			LPWSTR rgwsz[] = 
					{
						pRecipientInfo->pszDisplayName
					};
               
  	    		    LogError(
	    	    	    pwstrServer,
				        iesProxyToBig,
				        EVENTLOG_ERROR_TYPE,
				        rgwsz,
				        1);

                    rc = RC_ERROR;
                    goto cleanup;
                }
                break;

            case ('m'): // mailbox name
                rc = rcScanAndAppend(
                    sAnsitoSMTPMap,                 // char replacement table
                    pRecipientInfo->pszCommonName,  // source buffer
                    pwstrUserProxy,                 // dest buffer
                    &iProxyBuffer,                  // current index in dest buffer
                    cchMaxProxyValue-1);            // dest buffer size

                if (RC_FAILED(rc))
                {
                    // Can't fit mailbox name in buffer

   		  			LPWSTR rgwsz[] = 
					{
						pRecipientInfo->pszDisplayName
					};
               
  	    		    LogError(
	    	    	    pwstrServer,
				        iesProxyToBig,
				        EVENTLOG_ERROR_TYPE,
				        rgwsz,
				        1);

                    rc = RC_ERROR;
                    goto cleanup;
                }
                break;

            case ('r'): // char replacement change
                if (iFormat+2 < cchFormat)
                {
                    char chSrc, chDest;

                    chSrc = (char)pszLocalFormat[iFormat+1];
                    chDest = (char)pszLocalFormat[iFormat+2];

                    if (chSrc == chDest)
                    {
                        sAnsitoSMTPMap[chSrc] = 0;
                    }
                    else
                    {
                        sAnsitoSMTPMap[chSrc] = chDest;
                    }

                    iFormat += 2;
                }
                else
                {
                    // format string is invalid

   		  			LPWSTR rgwsz[] = 
					{
						pszLocalFormat
					};
               
  	    		    LogError(
	    	    	    pwstrServer,
				        iesInvalidFormatString,
				        EVENTLOG_ERROR_TYPE,
				        rgwsz,
				        1);

                    rc = RC_ERROR;
                    goto cleanup;
                }
                break;
                 
             default:
                // format specifier is unrecognized
                {
	  			    LPWSTR rgwsz[] = 
    			    {
					    pszLocalFormat
				    };
               
  	    		    LogError(
	    	            pwstrServer,
				        iesInvalidFormatString,
				        EVENTLOG_ERROR_TYPE,
				        rgwsz,
				        1);
                }

                rc = RC_ERROR;
                goto cleanup;
            
            } // switch

            fEscape = FALSE;
            
        } // if fEscape
        else 
        {       
            if (pszLocalFormat[iFormat] == '%')
            {
                fEscape = TRUE;
            } // if escape char
            else
            {
                // literal character; just insert it as long as it is legal
                if ((pszLocalFormat[iFormat] <= MAX_TRANSLATE_TABLE) &&
                    (sAnsitoSMTPMap[pszLocalFormat[iFormat]] != 0) &&
                    (iProxyBuffer < cchMaxProxyValue-1))
                {
                    pwstrUserProxy[iProxyBuffer++] = pszLocalFormat[iFormat];
                    pwstrUserProxy[iProxyBuffer] = 0;
                }
                else
                {
                    // invalid literal character in format string

   		  			LPWSTR rgwsz[] = 
					{
						pszLocalFormat
					};
               
  	    		    LogError(
	    	    	    pwstrServer,
				        iesInvalidFormatString,
				        EVENTLOG_ERROR_TYPE,
				        rgwsz,
				        1);

                    rc = RC_ERROR;
                    goto cleanup;
                }
            } // else literal
        } // else !fEscape
            
    } // for iFormat        

    *pcchUserProxy = iProxyBuffer;
 
    rc = RC_SUCCESS;

cleanup:
    
    if (fFreeLocalFormat)
    {
        FREE(pszLocalFormat);
    }

    return rc;

}


//$--RcGenerateProxy------------------------------------------------------------
//  Returns a single proxy address as a unicode string. 
//
//  When nRetries == 0
//  ==================
//
//  The format of this proxy is based upon the site proxy string which has the 
//  following format:
//      address-type ":" [format] "@" domain 
//  
//  The address-type and domain are uninterpreted and are written exactly as is
//
//  Format is optional, if specified it must contain only valid address
//  characters plus the following special symbols:
//      "%s"        substitute the Surname of the user 
//      "%g"        substitute the Given name of the user
//      "%d"        substitute the Display name of the user
//      "%m"        substitute the mailbox name of the user
//      "%%"        substitute a single '%'
//  In all the substitutions above, spaces and illegal characters will be
//  removed from the field before the substitution is made. To specify a 
//  different substitution to be used, use %r:
//      "%r" char1 char2 
//  All instances of char1 will be replaced by char2 in the substitutions 
//  which occur after this in the format string. If char1 == char2 the 
//  character will be deleted.
//
//  If the format field is not present, this is equivalent to:
//      address-type ":" "%m" "@" domain 
//
//  Examples:
//
//  These examples are based on:
//      mailbox = "dougdo"
//      display name = "Doug M. Dosdall"
//      surname = "Dosdall"
//      given name = "Doug"
//
//  Site Proxy                          Generated User Proxy
//  ----------------------------------- ----------------------------------------
//  SMTP:%r _%d@wspu.microsoft.com      SMTP:Doug_M._Dosdall@wspu.microsoft.com
//  SAMPLE:%r..%d@wspu.microsoft.com    SAMPLE:DougMDosdall@wspu.microsoft.com
//  EDK:%g.%s@wspu.microsoft.com        EDK:Doug.Dosdall@wspu.microsoft.com
//  SMTP:@wspu.microsoft.com            SMTP:dougdo@wspu.microsoft.com
//
//
//  When nRetries == 1
//  ==================
//
//  The user proxy is generated as per above except the format portion is 
//  ignored, i.e. assumed to be %m only.
//
//
//  When nRetries > 1
//  =================
//
//  The user proxy is generated using the following format: 
//      address-type ":" "%m" nRetries "@" domain 
//
//  For example, when nRetries == 2, the generated user proxy for the example
//  above would be:
//  
//  SMTP:dougdo2@wspu.microsoft.com
//
// -----------------------------------------------------------------------------
RC RcGenerateProxy(                     // RETURNS: RC_SUCCESS RC_MEMORY RC_ERROR
    IN HANDLE hProxySession,            // Handle to proxy sesssion. 
    IN PRECIPIENTINFO pRecipientInfo,   // Recipient specific details. 
    INT nRetries,                       // Number of times this function
                                        //   has previously been called with
                                        //   this value for pRecipientInfo.
    OUT LPWSTR *ppwstrProxyAddr)        // generated proxy address. 
{
    RC      rc                          = RC_SUCCESS;
    WCHAR   pwstrProxyBuffer[cchMaxProxyValue] = {L'\0'};
    ULONG   cchProxyBuffer              = 0;
    ULONG   cb                          = 0;
    ULONG   i                           = 0;
 
    // Verify Input Parameters

	if ((hProxySession == NULL) || 
        (GET_SERVER(hProxySession) == NULL))
    {
        // invalid arguments - internal error
        // can't write event log since no server name
        rc = RC_ERROR;
        goto cleanup;
    }
                
    if ((GET_SITE_FORMAT(hProxySession) == NULL) ||
        (GET_SITE_DOMAIN(hProxySession) == NULL) ||
        (pRecipientInfo == NULL) ||
        (pRecipientInfo->pszCommonName == NULL))
    {
        // invalid arguments - internal error; RcGenerateProxy should never
        // be called unless RcInitProxies was succesfully called first and
        // RcInitProxies must always set the site format and site domain.

		LogError(
		    GET_SERVER(hProxySession),
		    iesProxyInternalFailure,
		    EVENTLOG_ERROR_TYPE,
		    NULL,
		    0);
        rc = RC_ERROR;
        goto cleanup;
    }
    
    // Initialize output parameter

    *ppwstrProxyAddr = NULL;

    // Get the expanded user part of the proxy 
    // ---------------------------------------

    rc = RcGenerateUserProxy(
        GET_SITE_FORMAT(hProxySession),
        GET_SERVER(hProxySession),
        pRecipientInfo,
        nRetries,
        pwstrProxyBuffer,
        &cchProxyBuffer);

    if (RC_FAILED(rc))
    {
        // RcGenerateUserProxy generates own log entry
        // just pass error through
        goto cleanup;
    }
        
    // Figure out the size of the final proxy and alloc buffer
    // -------------------------------------------------------

    cb = (GET_SITE_TYPE_CCH(hProxySession) +    // e.g. "SMTP"
          1 +                                   // ":"
          cchProxyBuffer +                      // user proxy
          1 +                                   // @
          GET_SITE_DOMAIN_CCH(hProxySession) +  // domain
          1) * sizeof(WCHAR);                   // terminating null

    *ppwstrProxyAddr = malloc(cb);

    if ((*ppwstrProxyAddr) == NULL)
    {
        rc = RC_MEMORY;
        goto cleanup;
    }

    // Put all the pieces together in *ppwstrProxyAddr
    // -----------------------------------------------

    lstrcpyW(*ppwstrProxyAddr, GET_SITE_TYPE(hProxySession));
    i = GET_SITE_TYPE_CCH(hProxySession);
    (*ppwstrProxyAddr)[i++] = chAddressTypeDelimiter;
    lstrcpyW(&((*ppwstrProxyAddr)[i]), pwstrProxyBuffer);
    i += cchProxyBuffer;
    (*ppwstrProxyAddr)[i++] = chDomainDelimiter;    
    lstrcpyW(&((*ppwstrProxyAddr)[i]), GET_SITE_DOMAIN(hProxySession));

cleanup:
    
    return rc;

}


//$--RcUpdateProxy--------------------------------------------------------------
//  Updates a given proxy based on given the new site proxy. 
//
//  Updates the user part and the domain part of the proxy
//
//  Previously this method used to allow for selective updating of proxies; 
//  it's main goal was to attempt
//  to only update proxies which had been previously automatically generated
//  and not to lose manual edits previously made by an administrator.
//
//  But with the new design, this method gets only new site proxy in both the
//  places - pwstrOldSiteProxy and pwstrNewSiteProxy and hence it can not do 
//  selective updating. It now updates both user and domain part, according to new
//  site proxy rule, irrespective of proxy was created mannually or was 
//  automatically genereated.
//
//  Example 1: Domain has changed.
//  Old Site Proxy: %g@acme.com
//  New Site Proxy: %g@acmetool.com
//  User Proxies: Alice@acme.com, Bob@acme.com
//  In this example, RcUpdateProxy would be called 2 times, once for each user.
//
//  the resulting pwstrProxy will be
//  Alice@acmetool.com and
//  Bob@acmetool.com
//
//  Example 2: Format string changed; acme is now too big to use only first names
//  Old Site Proxy: %g@acme.com
//  New Site Proxy: %g.%s@acme.com
//  User Proxies: alice@acme.com, bob@acme.com
//  So the resulting pwstrProxy will be
//  AliceN@acme.com and
//  BobB@acme.com
//
// -----------------------------------------------------------------------------
RC RcUpdateProxy(                   	// RETURNS: RC_SUCCESS RC_MEMORY RC_ERROR RC_NOTFOUND
    IN HANDLE hProxySession,            // Handle to proxy sesssion. 
    IN PRECIPIENTINFO pRecipientInfo,
    IN LPWSTR pwstrOldSiteProxy,        // Old site proxy 
										// with new design, this has value of pwstrNewSiteProxy
    IN LPWSTR pwstrNewSiteProxy,        // New site proxy
    IN OUT LPWSTR pwstrProxy,      		// Proxy to modify, buffer is of 
                                        //   cchMaxProxyValue size
	IN VOID * pUnused)					// Unused
{            
    RC      rc = RC_SUCCESS;
    WCHAR   pwstrBuf[cchMaxProxyValue] = {L'\0'};   // working buffer for final proxy
    ULONG   iBuf            = 0;
    WCHAR   pwstrUserBuf[cchMaxProxyValue];
    ULONG   cchUserBuf;
    LPWSTR  pwstrTypeP      = NULL; //   address type part of pwstrProxy
    LPWSTR  pwstrTypeNSP    = NULL; //                        pwstrNewSiteProxy
    LPWSTR  pwstrUserP      = NULL; //   user/format part of pwstrProxy 
    LPWSTR  pwstrUserNSP    = NULL; //                     pwstrNewSiteProxy
    LPWSTR  pwstrDomainP    = NULL; //   domain part of pwstrProxy
    LPWSTR  pwstrDomainNSP  = NULL; //                pwstrNewSiteProxy

    // separate out the parts we need of the input parameters
    // ------------------------------------------------------

    // separate pwstrNewSiteProxy into type, user format and domain by temp
    // replacing : and @ with \0

    pwstrTypeNSP = pwstrNewSiteProxy;

    pwstrUserNSP = wcschr(pwstrNewSiteProxy, chAddressTypeDelimiter);

    if (pwstrUserNSP == NULL)
    {
        // internal error - we are getting a site proxy string which does not start
        // ADDRTYPE: (this should never happen)
		LogError(
		    GET_SERVER(hProxySession),
		    iesProxyInternalFailure,
		    EVENTLOG_ERROR_TYPE,
		    NULL,
		    0);
        rc = RC_ERROR;
        goto cleanup;
    }

    *pwstrUserNSP = 0;
    pwstrUserNSP++;

    pwstrDomainNSP = wcschr(pwstrUserNSP, chDomainDelimiter);

    if (pwstrDomainNSP)
    {
        *pwstrDomainNSP = 0;
        pwstrDomainNSP++;
    }

    // separate pwstrProxy into type, user and domain by temporarily replacing
    // @ and : with \0

    pwstrTypeP = pwstrProxy;

    pwstrUserP = wcschr(pwstrProxy, chAddressTypeDelimiter);

    if (pwstrUserP == NULL)
    {
        // internal error - we are getting a site proxy string which does not start
        // ADDRTYPE: (this should never happen)
		LogError(
		    GET_SERVER(hProxySession),
		    iesProxyInternalFailure,
		    EVENTLOG_ERROR_TYPE,
		    NULL,
		    0);
        rc = RC_ERROR;
        goto cleanup;
    }
    
    *pwstrUserP = 0;
    pwstrUserP++;
    
    pwstrDomainP = wcschr(pwstrUserP, chDomainDelimiter);

    if (pwstrDomainP)
    {
        *pwstrDomainP = 0;
        pwstrDomainP++;
    }

    // Do the address types match?

	if (lstrcmpiW(pwstrTypeNSP, pwstrTypeP))
    {
        // internal error - the address types do not match; again, this should
        // never occur.
		LogError(
		    GET_SERVER(hProxySession),
		    iesProxyInternalFailure,
		    EVENTLOG_ERROR_TYPE,
		    NULL,
		    0);
        rc = RC_ERROR;
        goto cleanup;
    }

    // Start building the new proxy; however leave *pfNoDomainMatch == TRUE
    // until we know we have made a significate change
    // --------------------------------------------------------------------

    // Copy in the address type and ":"

    lstrcpyW(pwstrBuf, pwstrTypeP);
    iBuf = lstrlenW(pwstrTypeP);
    pwstrBuf[iBuf++] = chAddressTypeDelimiter;

    // go ahead and get the updated the user part

    if (pwstrUserNSP[0] == 0)
    {
        rc = RcGenerateUserProxy(
            pszDefaultFormat,
            GET_SERVER(hProxySession),
            pRecipientInfo,
            0,
            pwstrUserBuf,
            &cchUserBuf);
    }
    else
    {
        rc = RcGenerateUserProxy(
            pwstrUserNSP,
            GET_SERVER(hProxySession),
            pRecipientInfo,
            0,
            pwstrUserBuf,
            &cchUserBuf);
    }
            
    if (RC_FAILED(rc))
    {
        goto cleanup;
    }

    // copy the new user part onto the final result

    lstrcpyW(&(pwstrBuf[iBuf]), pwstrUserBuf);
    iBuf += cchUserBuf;

    // Always replace the domain part of the site proxy.  Add the domain
    // part of the site proxy to the proxy if there is anything to add
    // -----------------------------------------------------------------
    
    if (pwstrDomainNSP)
    {
        pwstrBuf[iBuf++] = chDomainDelimiter;
        lstrcpyW(&(pwstrBuf[iBuf]), pwstrDomainNSP);
    }

    // Always copy the final result to the output buffer
    // -------------------------------------------------

    lstrcpyW(pwstrProxy, pwstrBuf);

cleanup:

    // Restore the : and @ characters in the munged strings 

    if (pwstrUserNSP)
    {
        *(pwstrUserNSP-1) = chAddressTypeDelimiter;
    }
    if (pwstrDomainNSP)
    {
        *(pwstrDomainNSP-1) = chDomainDelimiter;
    }

    return rc;
}

//$--RcValidateProxy------------------------------------------------------------
//  Verifies that a manually entered proxy is at least minimally valid.  
// -----------------------------------------------------------------------------
RC RcValidateProxy(             // RETURNS: RC_SUCCESS  RC_MEMORY RC_ERROR
                                //          RC_IMPLEMENTATION
    IN HANDLE hProxySession,    // Handle to the proxy session previously 
                                // returned by rcProxuInit.
    IN LPWSTR pwstrProxyAddr,   // The foreign format proxy address to be 
                                // validated.
    OUT BOOL *pfValid)          // Recieves TRUE if valid, FALSE otherwise.
                                // Undefined if other than RC_SUCCESS returned
                                // by function.
{
    UINT    i, 
            cch = 0;

    // assume address is valid until proven otherwise

    *pfValid = TRUE;
    
    // The only proxy validation done here is to look for characters < 33 or
    // > 127. Obviously more should be done as more characters are illegal.

    // Could also do some sort of content checking to verify whether the content
    // (i.e. the domain part) is not only legal but makes sense (this is harder).

    cch = lstrlenW(pwstrProxyAddr);

    for (i = 0; i < cch; i++)
    {
        if ((pwstrProxyAddr[i] < 33) || (pwstrProxyAddr[i] > 127))
        {

            // Log error so user knows why proxy address was rejected

       		LPWSTR rgwsz[] = 
    		{
    			pwstrProxyAddr
    		};

    	    LogError(
        	    GET_SERVER(hProxySession),
    	        iesInvalidCharacter,
    	        EVENTLOG_ERROR_TYPE,
    	        rgwsz,
    	        1);

            *pfValid = FALSE;
            break;
        }
    }

    return RC_SUCCESS;
}


//$--RcValidateSiteProxy--------------------------------------------------------
// Given a Unicode string, it validates that this string is a valid site address.
// This is called to verify that manually generated site proxies are legal.
// For this implementation, it is assumed the site proxy is legal if:
// - We can split it into it's component parts
// - The format and domain parts contain only chars in the 33-127 range
// -----------------------------------------------------------------------------
RC RcValidateSiteProxy(         // RETURNS: RC_SUCCESS  RC_MEMORY RC_ERROR
                                //          RC_IMPLEMENTATION
    IN HANDLE hProxySession,    // Handle to the proxy session previously 
                                // returned by rcProxuInit.
    IN LPWSTR pwstrSiteProxy,   // The foreign format site proxy address to be 
                                // validated.
    OUT BOOL *pfValid)	        // Recieves TRUE if valid, FALSE otherwise.
                                // Undefined if other than RC_SUCCESS returned
                                // by function.
{
    RC      rc          = RC_SUCCESS;
	LPWSTR  pszServer   = GET_SERVER(hProxySession);
    LPWSTR pszType      = NULL;
    ULONG  cchType      = 0;
    LPWSTR pszFormat    = NULL;
    ULONG  cchFormat    = 0;
    LPWSTR pszDomain    = NULL;
    ULONG  cchDomain    = 0;
    LPWSTR pszAt        = NULL;
    LPWSTR pszColon     = NULL;
    BOOL   fEscape      = FALSE;
    ULONG  i;

    // Initialize output parameter

    *pfValid = TRUE;

    // The site proxy must be available so check this first

    if (pwstrSiteProxy == NULL)
    {
		LogError(
		    pszServer,
		    iesNoSiteProxy,
		    EVENTLOG_ERROR_TYPE,
		    NULL,
		    0);
        *pfValid = FALSE;
        goto exit;
    }

    // Trim blanks from pwstrSiteProxy

    TrimW(pwstrSiteProxy);

    // Validate pwstrSiteProxy, must be "TYPE:x@y" where x is 0 or more chars
    // up to the first colon and y is at least 1 char

    cchDomain = lstrlenW(pwstrSiteProxy);
    pszAt = wcschr(pwstrSiteProxy, chDomainDelimiter);
    pszColon = wcschr(pwstrSiteProxy, chAddressTypeDelimiter);
    
    if ((cchDomain < 4) ||  // min size = T:@y
        (pszColon == NULL) ||       // no colon
        (*pszColon != chAddressTypeDelimiter) || 
        (pwstrSiteProxy[0] == chAddressTypeDelimiter))
    {
        // pwstrSiteProxy is invalid

   		LPWSTR rgwsz[] = 
		{
			pwstrSiteProxy
		};

		LogError(
		    pszServer,
		    iesBadSiteProxy,
		    EVENTLOG_ERROR_TYPE,
		    rgwsz,
		    1);

        *pfValid = FALSE;
        goto exit;
    }

    // Split site proxy into it's component parts
    // ------------------------------------------

    // replace : with 0 temporarily

    *pszColon = 0;

    // get address type

    cchType = lstrlenW(pwstrSiteProxy);

    pszType = malloc((cchType + 1) * sizeof(WCHAR));

    if (pszType == NULL)
    {
        rc = RC_MEMORY;
        goto exit;
    }

    lstrcpyW(pszType, pwstrSiteProxy);

    // Restore ':'

    *pszColon = chAddressTypeDelimiter;

    // Check site proxy again for more validation

    if ((pwstrSiteProxy[cchType] != chAddressTypeDelimiter) ||
        (pszAt == NULL) ||
        (*pszAt != chDomainDelimiter))
    {
        // pwstrSiteProxy is invalid

   		LPWSTR rgwsz[] = 
		{
			pwstrSiteProxy
		};

		LogError(
		    pszServer,
		    iesBadSiteProxy,
		    EVENTLOG_ERROR_TYPE,
		    rgwsz,
		    1);

        *pfValid = FALSE;
        goto exit;
    }

    // replace @ with 0 temporarily

    *pszAt = 0;

    // get format part
    
    cchFormat = lstrlenW(&(pwstrSiteProxy[cchType+1]));

    if (cchFormat == 0)
    {
        // use default format
        
        pszFormat = malloc((lstrlenW(pszDefaultFormat) + 1) * sizeof(WCHAR));
    
        if (pszFormat == NULL)
        {
            rc = RC_MEMORY;
            goto exit;
        }
        
        lstrcpyW(pszFormat, pszDefaultFormat);
    }
    else
    {
        // pull format out of site proxy

        pszFormat = malloc((cchFormat+1)*sizeof(WCHAR));
    
        if (pszFormat == NULL)
        {
            rc = RC_MEMORY;
            goto exit;
        }
    
        lstrcpyW(pszFormat, &(pwstrSiteProxy[cchType])+1);
    }

    // get domain part
    
    cchDomain = lstrlenW(pszAt+1);
    pszDomain = malloc((cchDomain+1)*sizeof(WCHAR));

    if (pszDomain == NULL)
    {
        rc = RC_MEMORY;
        goto exit;
    }
    
    lstrcpyW(pszDomain, (pszAt+1));

    // Restore '@'

    *pszAt = chDomainDelimiter;

    // We've now split up the site proxy which is the minumum needed to be
    // able to call Generate, etc. Now validate the pieces

    // validate address type
    // nothing to do, this is not user editable so we won't bother to check it

    // validate format string 
    // Just check that char's after % are valid and that rest of chars
    // are in 33 to 127 range.  More could be done but GenerateProxy will
    // take care of that.

    for (i = 0; i < cchFormat; i++)
    {
        
        if (pszFormat[i] == '%')
        {
            i++;
            if ((i >= cchFormat) || (wcschr(L"sgdmr%", pszFormat[i]) == NULL))
            {
           		LPWSTR rgwsz[] = 
        		{
        			pszFormat
        		};

    		    LogError(
    	    	    pszServer,
			        iesInvalidFormatString,
			        EVENTLOG_ERROR_TYPE,
			        rgwsz,
			        1);

                *pfValid = FALSE;
                goto exit;
            }
        }
        else if ((pszFormat[i] < 33) || (pszFormat[i] > 127))
        {
       		LPWSTR rgwsz[] = 
    		{
    			pszFormat
    		};

    	    LogError(
        	    pszServer,
    	        iesInvalidFormatString,
    	        EVENTLOG_ERROR_TYPE,
    	        rgwsz,
    	        1);

            *pfValid = FALSE;
            goto exit;
        }

    } // for
    
    // validate domain part
    // just check for characters < 33 or > 127

    for (i = 0; i < cchDomain; i++)
    {
        
        if ((pszDomain[i] < 33) || (pszDomain[i] > 127))
        {
       		LPWSTR rgwsz[] = 
    		{
    			pwstrSiteProxy
    		};

    	    LogError(
        	    pszServer,
    	        iesBadSiteProxy,
    	        EVENTLOG_ERROR_TYPE,
    	        rgwsz,
    	        1);

            *pfValid = FALSE;
            goto exit;
        }

    } // for

exit:

    FREE(pszType);
    FREE(pszFormat);
    FREE(pszDomain);

    return rc;
}


//$--FreeProxy------------------------------------------------------------------
//  Frees the memory previously allocated by GenerateProxy for a proxy address
//  string.
//------------------------------------------------------------------------------
VOID FreeProxy(
    IN LPWSTR pszProxy)   // the proxy string to free  May be NULL.
{
    FREE(pszProxy);
}


//$--CloseProxies---------------------------------------------------------------
//  Closes a proxy generation session and frees any associated data.  The DLL
//  can now be unloaded. 
// -----------------------------------------------------------------------------
VOID CloseProxies(
    IN HANDLE hProxySession)    //  Handle to proxy session.
{
    if (hProxySession)
    {
        FREE(GET_SITE_FORMAT(hProxySession));
        FREE(GET_SITE_DOMAIN(hProxySession));
        GET_SITE_DOMAIN_CCH(hProxySession) = 0;
        FREE(hProxySession);
    }

    return;
}


//$--rcScanAndAppend------------------------------------------------------------
//  For each character in pszSource, it maps it to a (possibly) new character 
//  using sAnsiToSMTPMap (chars > MAX_TRANSLATE_TABLE or which map to 0 are 
//  deleted) then appends it to pszDest at position iDest.  pszDest and iDest
//  are updated. If the location to be written is >= iMaxDest, then RC_ERROR is
//  returned.
// -----------------------------------------------------------------------------
RC rcScanAndAppend(IN char *        sAnsitoSMTPMap, // char replacement table
                   IN LPWSTR        pszSource,      // source buffer
                   IN OUT LPWSTR    pszDest,        // dest buffer
                   IN OUT ULONG *   piDest,         // current index in dest buffer
                   IN ULONG         iMaxDest)       // max dest buffer index
{
    RC      rc          = RC_SUCCESS; // only error paths set
    ULONG   cchSource;
    ULONG   i;

    // How big is source string?
    
    cchSource = lstrlenW(pszSource);

    if ((cchSource <= 0) || (pszSource == NULL))
    {
        // nothing to append; just return success
        goto cleanup;
    }

    // Iterate through source string and add it

    for (i = 0; i < cchSource; i++)
    {
        if ((pszSource[i] >= 0) &&
            (pszSource[i] <= MAX_TRANSLATE_TABLE) && 
            (sAnsitoSMTPMap[pszSource[i]] != 0))
        {
            // add translated character
            
            if (*piDest < iMaxDest)
            {
                pszDest[(*piDest)++] = sAnsitoSMTPMap[pszSource[i]];
            }
            else
            {
                // won't fit; return error
                rc = RC_ERROR;
                goto cleanup;
            }
                
        }
        // else skip it

     } // for

     // append final null

     pszDest[*piDest] = 0;

cleanup:
    return rc;
}


//$--TrimW----------------------------------------------------------------------
// Trims leading blanks from the begining and end of the string.
// -----------------------------------------------------------------------------
static VOID TrimW(              // RETURNS nothing (can't fail)
    IN OUT PWSTR pwstrSrc)      // String to be trimmed
{
    PWSTR pwstrDest = NULL;
    INT i = 0;

    if (pwstrSrc == NULL)
        goto cleanup;

    // trim leading

    pwstrDest = pwstrSrc;
    while ((pwstrSrc!=L'\0') && fIsWhiteSpaceW(*pwstrSrc))
    {
        pwstrSrc++;
    }

    // copy rest

    while (*pwstrSrc!=L'\0')
    {
        *pwstrDest=*pwstrSrc;
        pwstrDest++;
        pwstrSrc++;
        i++;
    }
    *pwstrDest = L'\0';
    
    // trim trailing

    if (i>0)
    {
        pwstrDest--;
        i--;

        while ((i>0) && (fIsWhiteSpaceW(*pwstrDest)))
        {
            *pwstrDest=L'\0';    
            i--;
        }
    }

cleanup:
    return;
}


//$--fIsWhiteSpaceW-------------------------------------------------------------
// Determines if character is a white space (space or tab).
// -----------------------------------------------------------------------------
static BOOL fIsWhiteSpaceW(     // RETURNS:  TRUE if whitespace, FALSE o/w
    WCHAR wc)                   // character to test. 
{
    BOOL bRes = TRUE;

    if (wc == L' ')
        goto cleanup;
    
    if (wc == L'\t')
        goto cleanup;

    bRes = FALSE;
    
cleanup:
    return bRes;
}


//$--LogError-------------------------------------------------------------------
// Logs an error to the application log in case of a proxy generation failure
// -----------------------------------------------------------------------------
VOID LogError(LPWSTR pszServer, IES ies, WORD wEventType, LPWSTR rgwsz[], WORD cwsz)
{
	HANDLE h;

	h = RegisterEventSourceW(pszServer, pszEventSource);
	if (h != NULL)
	{
		ReportEventW(
				h,
				wEventType, 
				0,
				ies,
				NULL,
				cwsz,
				0,
				rgwsz,
				NULL);
	DeregisterEventSource(h);
	}
}

