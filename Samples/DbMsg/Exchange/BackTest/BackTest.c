// --backtest.c-----------------------------------------------------------------
//
//  Backup sample.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------
//kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib edbbcli.lib 
#include "edk.h"
#include <edbback.h>
#include <edbbcli.h>
#include <time.h>
#include "backtest.h"

#define MIN_READ_HINT_SIZE 8193

DWORD
g_cbReadHintSize= 65536;

BOOL
g_fRandomReads	= fFalse;

SZ
SzFromHr(
	HRESULT hr
	)
{
	SZ szReturn = NULL;
	HMODULE hmoduleEdb = NULL;

	hmoduleEdb = LoadLibrary(TEXT("edbbcli.dll"));

	if (hmoduleEdb == NULL)
	{
		return "";
	}

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_HMODULE,
						hmoduleEdb,
						hr,
						GetUserDefaultLangID(),
						(CHAR *)&szReturn,
						0,
						NULL) == 0)
	{
		if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
							NULL,
							hr,
							GetUserDefaultLangID(),
							(CHAR *)&szReturn,
							0,
							NULL) == 0)
			return "Unknown";
	}

	return szReturn;
}

unsigned long
msfrompc(
	LARGE_INTEGER lipcDuration
	)
{
	LARGE_INTEGER lipcFrequency = {0};		// Ticks/second.

	if (!QueryPerformanceFrequency(&lipcFrequency)) {
		return(0);
	}

	lipcFrequency.QuadPart /= 1000;	// Convert to ticks/millisecond

	return(unsigned long)(lipcDuration.QuadPart / lipcFrequency.QuadPart);
}

EC
EcBackupFile(
	HBC hbcBackupContext,
	SZ szFile,
	HANDLE hBackupFile
	)
{
	LARGE_INTEGER liFileSize = {0};
	LARGE_INTEGER liBytesRead = {0};
	LARGE_INTEGER lipcStart = {0};
	LARGE_INTEGER lipcEnd = {0};
	LARGE_INTEGER lipcDuration = {0};
	CB cbRead = 0;
	HRESULT hrStatus = NOERROR;
	BackupFile bf = {0};
	CB cbWritten = 0;
	BFT bft = 0;

	VOID *pvBuffer = malloc(g_cbReadHintSize);

	if (pvBuffer == NULL)
	{
		return(hrError);
	}

	printf("Back up %s\n", szFile);

	liBytesRead.QuadPart = 0;

	//
	//	Open the remote database.
	//

	if (!QueryPerformanceCounter(&lipcStart))
	{
		printf("Unable to query performance counter: %d\n", GetLastError());
	}

	//
	//	Open the remote database.
	//

	bft = *szFile++;

	hrStatus = HrBackupOpenFile(hbcBackupContext, szFile,
						g_cbReadHintSize, &liFileSize);

	if (hrStatus != ERROR_SUCCESS) {
		printf("Open failed:%s %d\n", szFile, hrStatus);
		free(pvBuffer);
		HrBackupClose(hbcBackupContext);
		return hrStatus;
	}

	bf.ulFileSignature = FILE_SIGNATURE;
	bf.liFileSize = liFileSize;
	bf.cbFileNameLength = strlen(szFile)+1;
	bf.bft = bft;

	if (hBackupFile)
	{
		if (!WriteFile(hBackupFile, &bf, sizeof(bf), &cbWritten, NULL))
		{
			hrStatus = GetLastError();
			free(pvBuffer);
			HrBackupClose(hbcBackupContext);
			return(hrStatus);
		}
	
		if (cbWritten != sizeof(bf))
		{
			hrStatus = ERROR_HANDLE_DISK_FULL;
			free(pvBuffer);
			HrBackupClose(hbcBackupContext);
			return(hrStatus);
		}
	
		if (!WriteFile(hBackupFile, szFile, bf.cbFileNameLength, &cbWritten, NULL))
		{
			hrStatus = GetLastError();
			free(pvBuffer);
			HrBackupClose(hbcBackupContext);
			return(hrStatus);
		}
	
		if (cbWritten != bf.cbFileNameLength)
		{
			hrStatus = ERROR_HANDLE_DISK_FULL;
			free(pvBuffer);
			HrBackupClose(hbcBackupContext);
			return(hrStatus);
		}	
	}

	if (!QueryPerformanceCounter(&lipcEnd))
	{
		printf("Unable to query performance counter: %d\n", GetLastError());
	}

	lipcDuration.QuadPart = lipcEnd.QuadPart - lipcStart.QuadPart;

	printf("EcBackupOpenFile took %d milliseconds\n", msfrompc(lipcDuration));

	if (!QueryPerformanceCounter(&lipcStart))
	{
		printf("Unable to query performance counter: %d\n", GetLastError());
	}

	while ((hrStatus == ERROR_SUCCESS) &&
		   (liBytesRead.QuadPart < liFileSize.QuadPart)) {
		CB cbToRead = g_cbReadHintSize;

		if (g_fRandomReads)
		{
			cbToRead = rand() % g_cbReadHintSize;
            if (cbToRead < MIN_READ_HINT_SIZE)
            {
                cbToRead = MIN_READ_HINT_SIZE;
            }
		}

		//
		//  Read the next chunk from the database.
		//
		hrStatus = HrBackupRead(hbcBackupContext,
									pvBuffer,
									cbToRead,
									&cbRead);

		if (hrStatus == ERROR_SUCCESS) {
			liBytesRead.QuadPart += cbRead;
        } 
		else 
		{
			printf("Read failed:%s %d\n", szFile, hrStatus);
			break;
		}

		if (hBackupFile)
		{
			if (!WriteFile(hBackupFile, pvBuffer, cbRead, &cbWritten, NULL))
			{
				hrStatus = GetLastError();
				free(pvBuffer);
				HrBackupClose(hbcBackupContext);
				return(hrStatus);
			}
	
			if (cbWritten != cbRead)
			{
				hrStatus = ERROR_HANDLE_DISK_FULL;
				free(pvBuffer);
				HrBackupClose(hbcBackupContext);
				return(hrStatus);
			}
		}
	}

	if (!QueryPerformanceCounter(&lipcEnd))
	{
		printf("Unable to query performance counter: %d\n", GetLastError());
	}
	
	lipcDuration.QuadPart = lipcEnd.QuadPart - lipcStart.QuadPart;
	if (hrStatus == ERROR_HANDLE_EOF) {
		hrStatus = ERROR_SUCCESS;
	}

	if (hrStatus == ERROR_SUCCESS) {
		printf("Read %I64d bytes from the file, %3.3fs %f kb/second.\n", liBytesRead.QuadPart, ((double)msfrompc(lipcDuration) / 1000.0), (msfrompc(lipcDuration) ? ((double)liBytesRead.QuadPart / (double)(msfrompc(lipcDuration))) : 0));
	}

	hrStatus = HrBackupClose(hbcBackupContext);

	if (hrStatus != hrNone)
	{
		printf("Close failed:%s %d\n", szFile, hrStatus);
	}

	free(pvBuffer);
	return(hrStatus);
}

EC
EcDoBackup(
	BOOL fIncremental,
	SZ szBackupServer,
	SZ szBackupAnnotation,
	SZ szBackupFile
	)
{
	HBC hbcBackupContext = NULL;
	SZ szAttachmentInformation = NULL;
	CB cbSize = 0;
	EC hrStatus =  0;
	SZ szAttachment = 0;
	SZ szBackupLogFile = NULL;
	SZ szBackupLogName = NULL;
	HANDLE hBackupFile = NULL;
	BackupHeader bh = {0};
	LogHeader lh = {0};
	C cAttachment = 0;
	C cLogs = 0;
	CB cbWritten = 0;

	//
	//	Contact the component on the server to be backed up - the
	//  szBackupAnnotation field indicates which component on the
	//  server is to be contacted.
	//
	
	if (fIncremental)
	{
		hrStatus = HrBackupPrepare(	szBackupServer, 
								szBackupAnnotation, 
								1,	
								BACKUP_TYPE_LOGS_ONLY, 
								&hbcBackupContext);	
	}
	else
	{
		hrStatus = HrBackupPrepare(	szBackupServer, 
								szBackupAnnotation, 
								0,
								BACKUP_TYPE_FULL, 
								&hbcBackupContext);	
	}
	
	if (hrStatus != ERROR_SUCCESS) 
	{
		return hrStatus;
    }

	if (szBackupFile)
	{
		//
		//	Open up the backup file for write access.
		//
		hBackupFile = CreateFile(szBackupFile,
								GENERIC_WRITE | GENERIC_READ,
								0,
								NULL,
								OPEN_ALWAYS,
								FILE_FLAG_SEQUENTIAL_SCAN,
								NULL
								);
		if (hBackupFile == INVALID_HANDLE_VALUE)
		{
			return(GetLastError());
		}
	}

	cAttachment = 0;
	if (!fIncremental)
	{
		//
		//	Get the list of attached databases to perform the backup
		//
		hrStatus = HrBackupGetDatabaseNames(hbcBackupContext,
												&szAttachmentInformation,
												&cbSize);
		if (hrStatus != ERROR_SUCCESS) {
			HrBackupEnd(hbcBackupContext);
			if (hBackupFile)
			{
				CloseHandle(hBackupFile);
			}
			return hrStatus;
		}
	
		szAttachment = szAttachmentInformation;
	
		while (*szAttachment != '\0')
		{
			cAttachment  += 1;
			szAttachment += strlen(szAttachment)+1;
		}
	}

	if (hBackupFile)
	{
		//
		//	Write the header for the backup into the file.
		//	
		bh.ulSignature = BACKUP_SIGNATURE;
		bh.ulVersion = BACKUP_VERSION;			
		bh.cbDatabaseNameLength = strlen(szBackupAnnotation)+1;
		bh.cBackupFiles = cAttachment;
	
		if (!WriteFile(hBackupFile, &bh, sizeof(bh), &cbWritten, NULL))
		{
			hrStatus = GetLastError();
			HrBackupEnd(hbcBackupContext);
			return(hrStatus);
		}
	
		if (cbWritten != sizeof(bh))
		{
			hrStatus = ERROR_HANDLE_DISK_FULL;
			HrBackupEnd(hbcBackupContext);
			return(hrStatus);
		}
	
		if (!WriteFile(hBackupFile, szBackupAnnotation, bh.cbDatabaseNameLength, &cbWritten, NULL))
		{
			hrStatus = GetLastError();
			HrBackupEnd(hbcBackupContext);
			return(hrStatus);
		}
	
		if (cbWritten != bh.cbDatabaseNameLength)
		{
			hrStatus = ERROR_HANDLE_DISK_FULL;
			HrBackupEnd(hbcBackupContext);
			return(hrStatus);
		}
	}

	if (!fIncremental)
	{
		szAttachment = szAttachmentInformation;
		while (*szAttachment != '\0') 
		{
			hrStatus = EcBackupFile(hbcBackupContext, szAttachment, hBackupFile);

			if (hrStatus != hrNone)
			{
				BackupFree(szAttachmentInformation);
				HrBackupEnd(hbcBackupContext);
				if (hBackupFile)
				{
					CloseHandle(hBackupFile);
				}
				return(hrStatus);
			}
			szAttachment += strlen(szAttachment)+1;
		}

		BackupFree(szAttachmentInformation);
	}
	

	//
	//	We've successfully backed up the system, now clear 
    //  out the logs by truncating them.
	//

	hrStatus = HrBackupGetBackupLogs(hbcBackupContext,
									&szBackupLogFile,
									&cbSize);

	if (hrStatus != ERROR_SUCCESS) {
		HrBackupEnd(hbcBackupContext);
		if (hBackupFile)
		{
			CloseHandle(hBackupFile);
		}
		return hrStatus;
	}

	cLogs = 0;

	szBackupLogName = szBackupLogFile;

	while (*szBackupLogName != '\0')
	{
		cLogs += 1;
		szBackupLogName += strlen(szBackupLogName)+1;
	}

	if (hBackupFile)
	{
		//
		//	Write the header for the log portion of the backup into the file.
		//	
	
		lh.ulLogSignature = LOG_SIGNATURE;
		lh.cLogFiles = cLogs;
	
		if (!WriteFile(hBackupFile, &lh, sizeof(lh), &cbWritten, NULL))
		{
			hrStatus = GetLastError();
			HrBackupEnd(hbcBackupContext);
			return(hrStatus);
		}
	
		if (cbWritten != sizeof(lh))
		{
			hrStatus = ERROR_HANDLE_DISK_FULL;
			HrBackupEnd(hbcBackupContext);
			return(hrStatus);
		}
	}

	szBackupLogName = szBackupLogFile;

	while (*szBackupLogName != '\0') {
		hrStatus = EcBackupFile(hbcBackupContext, szBackupLogName, hBackupFile);
		if (hrStatus != hrNone)
		{
			BackupFree(szBackupLogFile);
			HrBackupEnd(hbcBackupContext);
			if (hBackupFile)
			{
				CloseHandle(hBackupFile);
			}
			return(hrStatus);
		}
		szBackupLogName += strlen(szBackupLogName)+1;
	}

	BackupFree(szBackupLogFile);

	printf("All logs and files backed up.\n");

	if (!fIncremental)
	{
		hrStatus = HrBackupTruncateLogs(hbcBackupContext);
	
		if (hrStatus != hrNone)
		{
			printf("Unable to truncate log: %d (%x).\n", hrStatus, hrStatus);
			if (hBackupFile)
			{
				CloseHandle(hBackupFile);
			}
	
			return(hrStatus);
		}
	
	}

	hrStatus = HrBackupEnd(hbcBackupContext);

	if (hBackupFile)
	{
		CloseHandle(hBackupFile);
	}

	return(hrStatus);
}


void
usage(void)
{
    printf("\nUsage: BackTest\t -S:<Server>"
        "\n\t\t -B:<Backup File>"
        "\n\t\t -T:<MDB|DSA>"
        "\n\t\t[-R:<Read Buffer Size>]"
        "\n\t\t[-R:R]  (generate random buffer sizes on successive reads)"
		"\n\t\t[-I]    (incremental backup)\n" );
}

int
_cdecl
main (int cArg, char *rgszArgv[])
{
	EC ecResult = 0;
	I irgsz = 0;
	BOOL fDsa = fFalse;
	BOOL fMdb = fFalse;
	SZ szServerName = NULL;
	SZ szBackupType = NULL;
	SZ szBackupFile = NULL;
	char rgComputerName[ MAX_COMPUTERNAME_LENGTH ] = {0};
	ERR err = 0;
	BOOL fIncremental = fFalse;

    if (cArg <= 1)
    {
        usage();
        exit(1);
    }

	for (irgsz = 1; irgsz < cArg ; irgsz += 1)
	{
		if (rgszArgv[irgsz][0] == '-' || rgszArgv[irgsz][0]=='/' )
		{
			if (toupper(rgszArgv[irgsz][1]) == 'T')
			{
				szBackupType = (rgszArgv[irgsz][2] == ':' ? &rgszArgv[irgsz][3] : rgszArgv[++irgsz]);
			}
			else if (toupper(rgszArgv[irgsz][1]) == 'S')
			{
				szServerName = (rgszArgv[irgsz][2] == ':' ? &rgszArgv[irgsz][3] : rgszArgv[++irgsz]);
			}
			else if (toupper(rgszArgv[irgsz][1]) == 'B')
			{
				szBackupFile = (rgszArgv[irgsz][2] == ':' ? &rgszArgv[irgsz][3] : rgszArgv[++irgsz]);
			}
			else if (toupper(rgszArgv[irgsz][1]) == 'R')
			{
				SZ szReadHint = (rgszArgv[irgsz][2] == ':' ? &rgszArgv[irgsz][3] : rgszArgv[++irgsz]);
				if (isdigit(*szReadHint))
				{
					g_cbReadHintSize = atoi(szReadHint);
                    if (g_cbReadHintSize < MIN_READ_HINT_SIZE)
                    {
                        g_cbReadHintSize = MIN_READ_HINT_SIZE;
                    }
				}
				else
				{
					switch (toupper(*szReadHint))
					{
					case 'R':
					case 'r':
						g_fRandomReads = fTrue;
						srand(time(NULL));
						break;
					default:
						usage();
						exit(1);
					}
				}
			}
			else if (toupper(rgszArgv[irgsz][1]) == 'I')
			{
				fIncremental = fTrue;
			}
			else
			{
				usage();
				exit(1);
			}
		}
	}

	if (szServerName == NULL)
	{
		CB cbComputerName = sizeof(rgComputerName);
		if (!GetComputerName(rgComputerName, &cbComputerName)) {
			printf("Unable to query local computer name %d", GetLastError());
			return(GetLastError());
		}
		szServerName = rgComputerName;
	}

	if (szBackupType == NULL)
	{
		usage();
		printf("Must specify a backup type\n");
		return(hrError);
	}
	else if (_stricmp(szBackupType, "MDB") == 0)
	{
		fMdb = fTrue;
	}
	else if (_stricmp(szBackupType, "DSA") == 0)
	{
		fDsa = fTrue;
	}

	if (!fMdb && !fDsa)
	{
		usage();
		printf("Must specify either MDB or DSA as the backup type");
		return(hrError);
	}

	ecResult = EcDoBackup(fIncremental, szServerName, ( fMdb ? EDBBACK_MDB_SERVER : (fDsa ? EDBBACK_DS_SERVER : NULL)), szBackupFile);

	printf("ecResult: %s (%d/0x%x)\n", SzFromHr(ecResult), ecResult, ecResult);

	return(ecResult);
}


