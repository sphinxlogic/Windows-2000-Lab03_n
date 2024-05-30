//  Copyright (C) 1995-1999 Microsoft Corporation.  All rights reserved.

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// found this necessary to get things to work with Oracle's xa.h
#define __STDC__ 1
#include "xa.h"


extern "C"
{
	#include <oratypes.h> /* LDA and CDA struct declarations */
	#include <ocidfn.h>
	#include <ocidem.h>	/* demo constants and structs */
	#include <ociapr.h>
}


//---------------------------------------------------------
//				TYPEDEFS
//---------------------------------------------------------
typedef void __cdecl TYPE_sqlld2 (struct cda_def *lda, text *cname, sb4 *cnlen);
typedef short __cdecl TYPE_oopen  (struct cda_def*, struct cda_def*, text*, sword, sword, text*, sword);
typedef sword __cdecl  TYPE_oclose   (struct cda_def *cursor);
typedef sword __cdecl  TYPE_opinit	 (ub4 mode);

#define MAX_STR_BUFFER 300

//---------------------------------------------------------
//				PROTOTYPES
//---------------------------------------------------------
BOOL ValidateCommandLineArgs(int,char**);
BOOL GetLibsAndFuncs();
BOOL DoWork(void);
void DetermineDLLNames (void);


//---------------------------------------------------------
//				GLOBALS
//---------------------------------------------------------
static HINSTANCE					g_hinstXALIB;		// Saved handle to XA73.dll
static HINSTANCE					g_hinstSQLLIB;		// Saved handle to SQLLIB18.dll
static HINSTANCE                    g_hinstOCILIB;      // Saved handle to OCIW32.dll
xa_switch_t	*						g_pXaSwitch;
TYPE_sqlld2	*						g_pfnSqlLD2;
TYPE_oopen *                        g_pfnOopen;
TYPE_oclose *						g_pfnOclose;
TYPE_opinit *						g_pfnOpinit;
XID									g_xid;

char                                g_szUser[MAX_STR_BUFFER];
char                                g_szPassword[MAX_STR_BUFFER];
char                                g_szServer[MAX_STR_BUFFER];

Lda_Def								lda;
ub4									hda[HDA_SIZE/sizeof(ub4)];
Cda_Def								cda1;


const char g_szMTxOCIRegKey[] = "SOFTWARE\\Microsoft\\MSDTC\\MTxOCI";

char szOCILib[256]  = "ociw32.dll";
char szXaLib[256]   = "xa73.dll";
char szSqlLib[256]  = "SQLLib18.dll";

char szUsage[] =	"This Oracle test program determines whether you can connect to your \n"
					"Oracle7.3 or Oracle8 database using Oracle's XA facility.\n"
					"This program uses standard Oracle interfaces and XA transaction facilities.\n"
					"It makes no use of Microsoft Distributed Transaction Coordinator.\n"
					"Failure of the test program indicates that your Oracle system is \n"
					"improperly installed or configured.\n"
					"If this program fails, reinstall and reconfigure Oracle, or contact the \n"
					"Oracle Support Organization for assistance.\n"
					"\n"
					"Usage:  MSDtcOra.exe [-U<username>] [-P<password>] -S<Service_Name as contained in the TNS file>\n"
					"Defaults for <username> and <password> are scott and tiger.\n"
					"\n"
					"Example:  MSDtcOra.exe -UMyUserName -PMySpecialPassword -SMyOracleServer\n\n";

 
/* -----------------------------------------------------------------------------
@func main

----------------------------------------------------------------------------- */
int __cdecl main (int cArgs, char** ppszArgs)
{
	memset ((void *) &lda, 0x0, sizeof (lda));

	//create the xid
	g_xid.formatID			= 0101;			
	g_xid.gtrid_length		= 5;		
	g_xid.bqual_length		= 1;		
	

	printf("\n\n****** MS DTC Oracle XA Configuration Test Utility ******\n\n");
	printf("%s", szUsage);

	if (!ValidateCommandLineArgs(cArgs, ppszArgs))
		goto done;

	if (!GetLibsAndFuncs())
		goto done;

	if (!DoWork())
		goto done;

	printf("\n\nTest completed successfully.\n");
	
done:
	return 0;
}


/* -----------------------------------------------------------------------------
@func DoWork

----------------------------------------------------------------------------- */

BOOL DoWork (void)
{
	char				szOpenString[MAX_STR_BUFFER]; 
	int					rc;
	struct cda_def 		LDA;
	long				lVal				= -1;
	char                szDBName[MAX_STR_BUFFER];

	//-------------------------------------------------------------------------
	//connect to the oracle database

	strcpy(szDBName, "TEST");
	sprintf (szOpenString, 
			 "Oracle_XA+Acc=P/%s/%s+SesTm=440+DB=%s+SqlNet=%s+Threads=TRUE",
			 g_szUser,
			 g_szPassword,
			 szDBName,
			 g_szServer);

	printf("Calling Oracle 'xa_open' function with the open string '%s'.\n", szOpenString);
	rc = g_pXaSwitch->xa_open_entry
						 (
							szOpenString,
							1,
							TMNOFLAGS
						 );
	if (rc != XA_OK)
	{
		printf ("'xa_open' call failed with the return code = %d.\n", rc);
		return FALSE;
	}
	printf("'xa_open' call succeeded.\n\n");

	//-------------------------------------------------------------------------
	//Enlist this Xa connection on a new transaction
	printf("Calling Oracle 'xa_start' function.\n");
	rc = g_pXaSwitch->xa_start_entry
						(
							&g_xid,
							1,
							TMNOFLAGS
						);

	if (rc != XA_OK)
	{
		printf ("'xa_start' call failed with the return code = %d.\n", rc);
		return FALSE;
	}
	printf("'xa_start' call succeeded.\n\n");

	//-------------------------------------------------------------------------
	//Open a cursor
	printf("Calling Oracle 'opinit' function.\n");
    if (rc = g_pfnOpinit(OCI_EV_TSF))
    {
		printf ("'opinit' call failed with the return code = %d.\n", rc);
		return FALSE;
    }
	printf("'opinit' call succeeded.\n\n");

	//-------------------------------------------------------------------------
	//get the lda for the connection by calling sqlld2
	printf("Calling Oracle 'sqlld2' function.\n");
	g_pfnSqlLD2	(
					&LDA,
					(unsigned char *)szDBName,
					&lVal
				);
	if (LDA.rc)
	{
		printf ("'sqlld2' call failed with the return code = %d.\n", LDA.rc);
		return FALSE;
	}
	printf("'sqlld2' call succeeded.\n\n");

	//-------------------------------------------------------------------------
	//Open a cursor
	printf("Calling Oracle 'oopen' function.\n");
    if ((rc = g_pfnOopen(&cda1, &LDA, (text *) 0, -1, -1, (text *) 0, -1)))
    {
		printf ("'oopen' call failed with the return code = %d.\n", rc);
		return FALSE;
    }
	printf("'oopen' call succeeded.\n\n");

	// close the cursor
	printf("Calling Oracle 'oclose' function.\n");
    if ((rc = g_pfnOclose(&cda1)))
    {
		printf ("'oclose' call failed with the return code = %d.\n", rc);
		return FALSE;
    }
	printf("'oclose' call succeeded.\n\n");


	printf("Calling Oracle 'xa_end' function \n");

	// call xa_end
	rc = g_pXaSwitch->xa_end_entry
							(
								&g_xid,
								1,				//rmid
								TMFAIL
							);
	if (rc != XA_OK)
	{
		printf ("'xa_end' call failed with the return code = %d.\n", rc);
		return FALSE;
	}
	printf("'xa_end' call succeeded.\n\n");


	printf("Calling Oracle 'xa_rollback' function \n");

	// call xa_rollback
	rc = g_pXaSwitch->xa_rollback_entry
							(
								&g_xid,
								1,				//rmid
								TMNOFLAGS		
							);
	if (rc != XA_OK)
	{
		printf ("'xa_rollback' call failed with the return code = %d.\n", rc);
		return FALSE;
	}
	printf("'xa_rollback' call succeeded.\n\n");


	printf("Calling Oracle 'xa_recover' function \n");
	rc = g_pXaSwitch->xa_recover_entry
						 (
							&g_xid,
							1,   // no of xids to recover
							1,
							TMSTARTRSCAN
						 );

	if (rc < 0)
	{
		printf ("'xa_recover' call failed with the return code = %d.\n", rc);
		return FALSE;
	}
	
	printf("'xa_recover' call succeeded with return code = %d. \n\n", rc);

	
	printf("Calling Oracle 'xa_close' function \n");

	rc = g_pXaSwitch->xa_close_entry("",1,TMNOFLAGS);

	if (rc != XA_OK)
	{
		printf ("'xa_close' call failed with the return code = %d.\n", rc);
		return FALSE;
	}
		
	printf(" 'xa_close' call succeeded. \n");
		
		
	return TRUE;
} //end DoWork

/* -----------------------------------------------------------------------------
@func GetLibsAndFuncs

----------------------------------------------------------------------------- */
BOOL GetLibsAndFuncs()
{
	DetermineDLLNames ();


	//-------------------------------------------------------------------------
	//load xa dll
	printf("Calling LoadLibrary on %s. \n", szXaLib);
	if ((g_hinstXALIB = LoadLibrary(szXaLib)) == NULL)
	{
		printf("LoadLibrary on %s failed.\n", szXaLib);
		return FALSE;
	}
	printf("LoadLibrary on %s succeeded.\n\n", szXaLib);


	//-------------------------------------------------------------------------
	//load sqllib dll
	printf("Calling LoadLibrary on %s. \n", szSqlLib);
	if ((g_hinstSQLLIB = LoadLibrary(szSqlLib)) == NULL)
	{
		printf("LoadLibrary on %s failed.\n", szSqlLib);
		return FALSE;
	}
	printf("LoadLibrary on %s succeeded.\n\n", szSqlLib);

	//-------------------------------------------------------------------------
	//load ociw32 dll
	printf("Calling LoadLibrary on %s. \n", szOCILib);
	if ((g_hinstOCILIB = LoadLibrary(szOCILib)) == NULL)
	{
		printf("LoadLibrary on %s failed.\n", szOCILib);
		return FALSE;
	}
	printf("LoadLibrary on %s succeeded.\n\n", szOCILib);

	//-------------------------------------------------------------------------
	//get the xa_switch
	printf("Calling GetProcAddress on the Oracle xa_switch function 'xaosw' in %s.\n", szXaLib);
	g_pXaSwitch = (xa_switch_t *) GetProcAddress ( g_hinstXALIB, "xaosw" );
	if (g_pXaSwitch == NULL)
	{
		printf("GetProcAddress on 'xaosw' in %s failed.\n", szXaLib);
		return FALSE;
	} 	
	printf("GetProcAddress on 'xaosw' in %s succeeded.\n\n", szXaLib);

	//-------------------------------------------------------------------------
	//get the sqlld2 function
	printf("Calling GetProcAddress on the Oracle 'sqlld2' function in %s.\n", szSqlLib);
	g_pfnSqlLD2 = (TYPE_sqlld2 *) GetProcAddress ( g_hinstSQLLIB, "sqlld2" );
	if (g_pfnSqlLD2 == NULL)
	{
		printf("GetProcAddress on 'sqlld2' in %s failed.\n", szSqlLib);
		return FALSE;
	}
	printf("GetProcAddress on 'sqlld2' in %s succeeded.\n\n", szSqlLib);


	//-------------------------------------------------------------------------
	//get the opinit function
	printf("Calling GetProcAddress on the Oracle 'opinit' function in %s.\n", szOCILib);
	g_pfnOpinit = (TYPE_opinit*) GetProcAddress( g_hinstOCILIB, "opinit" );
	if (g_pfnOpinit == NULL)
	{
		printf("GetProcAddress on 'opinit' in %s failed.\n", szOCILib);
		return FALSE;
	}
	printf("GetProcAddress on 'opinit' in %s succeeded.\n\n", szOCILib);


	//-------------------------------------------------------------------------
	//get the oopen function
	printf("Calling GetProcAddress on the Oracle 'oopen' function in %s.\n", szOCILib);
	g_pfnOopen = (TYPE_oopen*) GetProcAddress( g_hinstOCILIB, "oopen" );
	if (g_pfnOopen == NULL)
	{
		printf("GetProcAddress on 'oopen' in %s failed.\n", szOCILib);
		return FALSE;
	}
	printf("GetProcAddress on 'oopen' in %s succeeded.\n\n", szOCILib);
	

	//get the oclose function
	printf("Calling GetProcAddress on the Oracle 'oclose' function in %s.\n", szOCILib);
	g_pfnOclose = (TYPE_oclose*) GetProcAddress( g_hinstOCILIB, "oclose" );
	if (g_pfnOclose == NULL)
	{
		printf("GetProcAddress on 'oclose' in %s failed.\n", szOCILib);
		return FALSE;
	}
	printf("GetProcAddress on 'oclose' in %s succeeded.\n\n", szOCILib);
	
	return TRUE;
}

/* -----------------------------------------------------------------------------
@func ValidateCommandLineArgs

----------------------------------------------------------------------------- */
ValidateCommandLineArgs(int cArgs, char** ppszArgs)
{
	long i;
	BOOL bServerSet = FALSE;

	
	// Initialize defaults
	strcpy(g_szUser, "scott");
	strcpy(g_szPassword, "tiger");
	strcpy(g_szServer, "");

	for (i=1; i < cArgs; i++)
	{
		if (*ppszArgs[i] == '-' || *ppszArgs[i] == '/')
		{
			switch (ppszArgs[i][1])
			{
				// 'u' -- set user name
				case 'u':
				case 'U': 
					strcpy(g_szUser, &(ppszArgs[i][2]));
					break;
				
				// 'p' -- set password
				case 'p':
				case 'P':
					strcpy(g_szPassword, &(ppszArgs[i][2]));
					break;

				// 's' -- set server name
				case 's':
				case 'S':
					strcpy(g_szServer, &(ppszArgs[i][2]));
					bServerSet = TRUE;
					break;

				// '?' -- display usage
				case '?':
					printf("%s", szUsage);
					return FALSE;
					break;

				default:
					goto badarg;
			}
		}
		else
		  goto badarg;
	}
	if (!bServerSet)
		goto badarg;
	
	return TRUE;

badarg:
	printf("%s", szUsage);	
	return FALSE;
}




void DetermineDLLNames (void)
{
	HKEY			hKey		= 0x0;
	DWORD			dwcbBuffer;
	DWORD			dwlptype;
	long			lRetVal;


	//-------------------------------------------------------------------------
	//Attempt to open the registry key in which the Oracle DLL names may be specified.
	//If the registry key cannot be found then use the Oracle 7.3 DLLs by default.

	lRetVal = RegOpenKeyEx
				(
					HKEY_LOCAL_MACHINE,
					g_szMTxOCIRegKey,
					0x0,
					KEY_ALL_ACCESS,
					&hKey
				);

	if (lRetVal != ERROR_SUCCESS)
	{
		printf ("Unable to locate the registry key '%s'.\n", g_szMTxOCIRegKey);
		printf ("Using the Oracle 7.3 DLLs 'xa73.dll', 'SQLLib18.dll' and 'OciW32.dll' by default.\n\n");
		return;
	}


	//-------------------------------------------------------------------------
	//Attempt to retreive the name of the Oracle xa lib DLL
	//If the registry key cannot be found then use the Oracle 7.3 xa lib DLL by default.

	dwcbBuffer = 256;

	lRetVal = RegQueryValueEx
				(
					hKey,
					"OracleXaLib",
					0x0,
					&dwlptype,
					(unsigned char *)szXaLib,
					&dwcbBuffer
				);

	if (lRetVal != ERROR_SUCCESS)
	{
		//assume 7.3.3

		printf ("Unable to locate the Oracle XA Dll name in the registry.\n");
		printf ("Using the Oracle 7.3 'xa73.dll' by default.\n\n");
	}

	//-------------------------------------------------------------------------
	//Attempt to retreive the name of the Oracle SQL lib DLL
	//If the registry key cannot be found then use the Oracle 7.3 SQL lib DLL by default.


	dwcbBuffer = 256;

	lRetVal = RegQueryValueEx
				(
					hKey,
					"OracleSqlLib",
					0x0,
					&dwlptype,
					(unsigned char *)szSqlLib,
					&dwcbBuffer
				);

	if (lRetVal != ERROR_SUCCESS)
	{
		//assume 7.3.3
		printf ("Unable to locate the Oracle SQLLib Dll name in the registry.\n");
		printf ("Using the Oracle 7.3 'SQLLib18.dll' by default.\n\n");
	}

	//-------------------------------------------------------------------------
	//Attempt to retreive the name of the Oracle OCI DLL
	//If the registry key cannot be found then use the Oracle 7.3 OCIW32 DLL by default.


	dwcbBuffer = 256;

	lRetVal = RegQueryValueEx
				(
					hKey,
					"OracleOciLib",
					0x0,
					&dwlptype,
					(unsigned char *)szOCILib,
					&dwcbBuffer
				);

	if (lRetVal != ERROR_SUCCESS)
	{
		//assume 7.3.3
		printf ("Unable to locate the Oracle OciLib name in the registry.\n");
		printf ("Using the Oracle 7.3 'OciW32.dll' by default.\n\n");
	}

	return;
} //end DetermineDLLNames