// --resttest.cpp---------------------------------------------------------------
//
//  Backup restore sample.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"
#include <edbback.h>
#include <edbbcli.h>
#include <time.h>
#include "..\\backtest.h"

DWORD
cbReadSize = 0x10000;

CHAR
rgchComputerName[ MAX_COMPUTERNAME_LENGTH ];

ERR
ErrRestoreFile(
	HANDLE hBackup,
	EDB_RSTMAP *rgrstmap,
	I *irgRestMap,
	SZ szDatabaseLocationList,
	SZ *pszBackupLogDirectory = NULL,
    PBOOL pfSetGen = NULL,
	PDWORD gen = NULL
	);


ERR
ErrReadStructure(
	HANDLE hFile,
	VOID *pvStruct,
	CB cbStruct
	)
{
	CB cbRead = 0;

	if (!ReadFile(hFile, pvStruct, cbStruct, (PDWORD)&cbRead, NULL))
	{
		printf("Unable to read log headers from backup file %d\n", GetLastError());
		return(GetLastError());
	}

	if (cbRead != cbStruct)
	{
		printf("Unable to read all of log header from backup file\n");
		return(1);
	}
	return(ERROR_SUCCESS);
}

ERR
ErrReadHeader(
	HANDLE hFile,
	PBackupHeader bh
	)
{
	ERR err = 0;
	if (err = ErrReadStructure(hFile, bh, sizeof(BackupHeader)))
	{
		printf("Unable to read log headers from backup file: %d\n", err);
		return(err);
	}

	if (bh->ulSignature != BACKUP_SIGNATURE)
	{
		printf("Log signature does not match, backup is probably corrupt\n");
		return(1);
	}
	return(ERROR_SUCCESS);
}

ERR
ErrReadHeader(
	HANDLE hFile,
	PBackupFile bf
	)
{
	ERR err = 0;
	if (err = ErrReadStructure(hFile, bf, sizeof(BackupFile)))
	{
		printf("Unable to read log headers from backup file: %d\n", err);
		return(err);
	}

	if (bf->ulFileSignature != FILE_SIGNATURE)
	{
		printf("Log signature does not match, backup is probably corrupt\n");
		return(1);
	}
	return(ERROR_SUCCESS);
}

ERR
ErrReadHeader(
	HANDLE hFile,
	PLogHeader lh
	)
{
	ERR err = 0;
	if (err = ErrReadStructure(hFile, lh, sizeof(LogHeader)))
	{
		printf("Unable to read log headers from backup file: %d\n", err);
		return(err);
	}

	if (lh->ulLogSignature != LOG_SIGNATURE)
	{
		printf("Log signature does not match, backup is probably corrupt\n");
		return(1);
	}
	return(ERROR_SUCCESS);
}

SZ
SzFindBFT(
	SZ szDatabaseLocationList,
	BFT bft
	)
{
	SZ	szDatabaseLocation = szDatabaseLocationList;
	
	while (*szDatabaseLocation)
	{
		BFT bftLocation = *szDatabaseLocation++;

		if (bftLocation == bft)
		{
			return szDatabaseLocation;
			break;
		}

		szDatabaseLocation += strlen(szDatabaseLocation)+1;
	}

	return NULL;
}

ERR
ErrRestoreFile(
	HANDLE hBackup,
	EDB_RSTMAP *prstmap,
	I *pirgrstmap,
	SZ szDatabaseLocationList,
	SZ *pszBackupLogDirectory,
    PBOOL pfSetGen,
	PDWORD gen
	)
{
	ERR err = 0;
	BackupFile bf = {0};
	SZ szNewFileName = NULL;
	HANDLE hRestoreFile = NULL;
	CB cbRead = 0;
	BFT bftFile = 0;
	SZ szFileName = NULL;
	PVOID pvBuffer = NULL;
	char rgchDrive[_MAX_DRIVE] = {0};
	char rgchDir[_MAX_DIR] = {0};
	char rgchFileName[_MAX_FNAME] = {0};
	char rgchExtension[_MAX_EXT] = {0};
	LARGE_INTEGER liBytesRemaining = {0};
	DWORD cbToRead = 0;

	//
	//	Read the backup header for the file.
	//

    if (pfSetGen)
        *pfSetGen = fFalse;

	err = ErrReadHeader(hBackup, &bf);

	szFileName = new char[bf.cbFileNameLength];

	if (szFileName == NULL)
	{
		printf("Error allocating space for database name\n");
		err = ERROR_NOT_ENOUGH_MEMORY;
        goto cleanup;
	}

	if (!ReadFile(hBackup, szFileName, bf.cbFileNameLength, (PDWORD)&cbRead, NULL))
	{
		printf("Unable to read file name from backup file: %d\n", GetLastError());
		err = GetLastError();
        goto cleanup;
	}

	//
	//	Save away the backup file type of this file.
	//

	bftFile = bf.bft;

	//
	//	Crack the incoming database name to determine the file name.
	//

	_splitpath(szFileName, rgchDrive, rgchDir, rgchFileName, rgchExtension);

	if (gen != NULL)
	{
		//
		//	We want to find out the generation of this file if it's a log file.
		//

		if (strnicmp(rgchFileName, "EDB", 3) == 0)
		{
			if (stricmp(rgchExtension, ".LOG") == 0)
			{
				//
				//	log file generations are hex digits.
				//

				*gen = strtoul(&rgchFileName[3], NULL, 16);
                if (pfSetGen)
                    *pfSetGen = fTrue;

				//
				//	If we want to find out the log directory, return it.
				//
			
				if (pszBackupLogDirectory != NULL)
				{
					if (rgchDir[strlen(rgchDir)-1] == '\\')
					{
						rgchDir[strlen(rgchDir)-1] = '\0';
					}
			
					//
					//	Save away the backup log directory if needed.
					//

					*pszBackupLogDirectory = strdup(rgchDir);
				}
			
			}
		}
	}

	//
	//	Ok, now find out where we are going	to put this file.
	//


	//
	//	First scan for an exact match on BFT.
	//

	szNewFileName = SzFindBFT(szDatabaseLocationList, bftFile);

	if (szNewFileName == NULL)
	{
		//
		//	Ok, we didn't find it exactly, let's try to find it's directory.
		//

		if (bftFile & BFT_LOG_DIRECTORY)
		{
			SZ szLogDir = NULL;

			//
			//	This guy goes into the log directory.  Find out where that is.
			//

			szLogDir = SzFindBFT(szDatabaseLocationList, BFT_LOG_DIR);

			if (szLogDir == NULL)
			{
				printf("Could not find log directory");
				err = ERROR_FILE_NOT_FOUND;
                goto cleanup;
			}

			szNewFileName = new char[strlen(szLogDir)+1+strlen(rgchFileName)+strlen(rgchExtension)+2];
			strcpy(szNewFileName, szLogDir);
			strcat(szNewFileName, "\\");
			strcat(szNewFileName, rgchFileName);
			strcat(szNewFileName, rgchExtension);
		}
		else if (bftFile & BFT_DATABASE_DIRECTORY)
		{
			printf("Don't support inexact match in datbase directory yet");
			err = ERROR_FILE_NOT_FOUND;
		}
	}

	//
	//	If this goes into the database directory, it needs to go into the RSTMAP.
	//

	if (bftFile & BFT_DATABASE_DIRECTORY)
	{
		prstmap[*pirgrstmap].szDatabaseName = szFileName;
		prstmap[*pirgrstmap].szNewDatabaseName = strdup(szNewFileName);
		*pirgrstmap+=1;
	}

	//
	//	If the munged name in the database is on our current machine, then unmunge the name for efficency.
	//

	if (szNewFileName[0] == '\\' && szNewFileName[1] == '\\')
	{
		//
		//	Ok, this is a munged file name.
		//
		SZ szBackslash = strchr(&szNewFileName[2], '\\');

		if (szBackslash != NULL)
		{
			if (_strnicmp(&szNewFileName[2], rgchComputerName, szBackslash-&szNewFileName[2]) == 0)
			{
				//
				//	Ok, the current computer name matches the munged name, we want to munge the
				//  destination file specified to match the local name.
				//

				szNewFileName = _strdup(szBackslash+1);
					
				if (szNewFileName[1] == '$')
				{
					szNewFileName[1] = ':';
				}
			}
		}
	}

	hRestoreFile = CreateFile(szNewFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
								FILE_FLAG_SEQUENTIAL_SCAN, NULL);

	if (hRestoreFile == INVALID_HANDLE_VALUE)
	{
		err = GetLastError();

		if (ERROR_SHARING_VIOLATION==err)
		{
			printf("Unable to open %s. Make sure the Store service has been "
				"stopped before restoring.\n", szNewFileName, GetLastError());
		}
		else
		{
			printf("Unable to open file %s for restore: %d\n", szNewFileName, err);
		}
		goto cleanup;
	}

	liBytesRemaining = bf.liFileSize;

	pvBuffer = (void *)new char[cbReadSize];

	if (pvBuffer == NULL)
	{
		printf("Unable to allocate buffer for file restore.\n");
		err = 1;
        goto cleanup;
	}

	cbToRead = cbReadSize;

	while (liBytesRemaining.QuadPart != 0)
	{
		DWORD cbRead = 0;
		DWORD cbWritten = 0;

		if (liBytesRemaining.QuadPart < cbReadSize)
		{
			cbToRead = liBytesRemaining.LowPart;
		}

		if (!ReadFile(hBackup, pvBuffer, cbToRead, &cbRead, NULL))
		{
			printf("Unable to read from restore file: %d\n", GetLastError());
			err = GetLastError();
            goto cleanup;
		}

		if (cbRead != cbToRead)
		{
			printf("Unable to read from restore file: %d\n", GetLastError());
			err = GetLastError();
            goto cleanup;
		}

		if (!WriteFile(hRestoreFile, pvBuffer, cbRead, &cbWritten, NULL))
		{
			printf("Unable to write to restored file: %d\n", GetLastError());
			err = GetLastError();
            goto cleanup;
		}

		if (cbRead != cbWritten)
		{
			printf("Unable to write to restored file: %d\n", GetLastError());
			err = GetLastError();
            goto cleanup;
		}

		liBytesRemaining.QuadPart -= cbRead;
	}

	CloseHandle(hRestoreFile);

	err = ERROR_SUCCESS;

cleanup:
    if (pvBuffer)
    {
	    delete pvBuffer;
    }

    return(err);
}

int
_cdecl
main (int cArg, char *rgszArgv[])
{
	I irgsz = 0;
	BOOL fDsa = fFalse;
	BOOL fMdb = fFalse;

	SZ szBackupFile = DEF_BACKUP_FILE;
	SZ szBackupServer = NULL;
	HANDLE hBackupFile = NULL;
	DWORD cbComputerName = sizeof(rgchComputerName);
	SZ szDatabaseLocationList = NULL;
	DWORD cbLocationList = 0;

    BOOL fInvalidArg = fFalse;

	if (!GetComputerName(rgchComputerName, &cbComputerName))
	{
		printf("Unable to query computer name: %d\n", GetLastError());
		return(GetLastError());
	}

	for (irgsz = 1; irgsz < cArg ; irgsz += 1)
	{
		if (rgszArgv[irgsz][0] == '-' || rgszArgv[irgsz][0]=='/' )
		{
			if (toupper(rgszArgv[irgsz][1]) == 'B')
			{
				szBackupFile = (rgszArgv[irgsz][2] == ':' ? &rgszArgv[irgsz][3] : rgszArgv[++irgsz]);
			}
			else if (toupper(rgszArgv[irgsz][1]) == 'S')
			{
				szBackupServer = (rgszArgv[irgsz][2] == ':' ? &rgszArgv[irgsz][3] : rgszArgv[++irgsz]);
			}
			else
			{
                fInvalidArg = fTrue;
                break;
			}
		}
	}

    if (fInvalidArg || cArg <= 1)
	{
		printf("\nUsage: RestTest\t -S:<Server>\n\t\t -B:<Backup File>\n");
        return(0);
	}

	if (szBackupServer == NULL)
	{
		szBackupServer = rgchComputerName;
	}

	//
	//	Open up the backup file for write access.
	//

	hBackupFile = CreateFile(szBackupFile,
							GENERIC_READ,
							0,
							NULL,
							OPEN_EXISTING,
							FILE_FLAG_SEQUENTIAL_SCAN,
							NULL
							);
	if (hBackupFile == INVALID_HANDLE_VALUE)
	{
		printf("Unable to open backup file %s: %d\n", szBackupFile, GetLastError());
		return(GetLastError());
	}

	BackupHeader bh = {0};
	CB cbRead = 0;

	ERR err = 0;

	err = ErrReadHeader(hBackupFile, &bh);

	if (err != ERROR_SUCCESS)
	{
		return(err);
	}

	SZ szRestoreAnnotation = NULL;
	szRestoreAnnotation = new char[bh.cbDatabaseNameLength];

	if (szRestoreAnnotation == NULL)
	{
		printf("Out of memory error\n");
		return(1);
	}
	if (!ReadFile(hBackupFile, szRestoreAnnotation, bh.cbDatabaseNameLength, (PDWORD)&cbRead, NULL))
	{
		printf("Unable to read from backup file %s: %d\n", szBackupFile, GetLastError());
		return(GetLastError());
	}

	if (cbRead != bh.cbDatabaseNameLength)
	{
		printf("Unable to read all of database name from backup file %s\n", szBackupFile);
		return(GetLastError());
	}

	if (strlen(szRestoreAnnotation) != (ULONG)bh.cbDatabaseNameLength-1)
	{
		printf("Database name %s corrupted in backup file %s\n", szRestoreAnnotation, szBackupFile);
		return(GetLastError());
	}

	printf("Now performing component specific restoration\n");

	HBC hbc = NULL;

    err = HrRestorePrepare(szBackupServer, szRestoreAnnotation, &hbc);

	if (err != ERROR_SUCCESS)
	{
		printf("Unable to connect to restore provider on server %s\n", szBackupServer);
		return(err);
	}

	err = HrRestoreGetDatabaseLocations(
						hbc,
						&szDatabaseLocationList,
						&cbLocationList);

	if (err != ERROR_SUCCESS)
	{
		printf("Unable to query database locations on %s\n", szBackupServer);
		return(err);
	}


	C cRemainingBackupFiles = bh.cBackupFiles;

	//
	//	Skip past the files to the log headers.
	//

	while (cRemainingBackupFiles--)
	{
		BackupFile bf = {0};

		err = ErrReadHeader(hBackupFile, &bf);

		if (err != ERROR_SUCCESS)
		{
			return(err);
		}
		LARGE_INTEGER liMoveDelta = {0};

		liMoveDelta = bf.liFileSize;

		liMoveDelta.QuadPart += bf.cbFileNameLength;

		if (!SetFilePointer(hBackupFile, liMoveDelta.LowPart, &liMoveDelta.HighPart, FILE_CURRENT)) {
			printf("Unable to set file pointer past file.\n");
			return(1);
		}
	}

	LogHeader lh = {0};

	err = ErrReadHeader(hBackupFile, &lh);

	if (err != ERROR_SUCCESS)
	{
		return(err);
	}
	//
	//	We now know the total number of logs to back up.
	//

	C cBackupFiles = lh.cLogFiles + bh.cBackupFiles;


	printf("Restoring %s database\n", szRestoreAnnotation);

	if (!SetFilePointer(hBackupFile, sizeof(BackupHeader)+bh.cbDatabaseNameLength, NULL, FILE_BEGIN)) {
		printf("Unable to reset database pointer to start of database.\n");
		return(1);
	}

	I irgRestMap = 0;
	EDB_RSTMAP *rgRestMap=NULL;


	//
	//	If cRemainingBackupFiles == 0 then we are doing an 
	//	- incremental restore
	//
	cRemainingBackupFiles = bh.cBackupFiles;
	if (cRemainingBackupFiles)
	{
		rgRestMap = new EDB_RSTMAP[cBackupFiles];
		if (rgRestMap == NULL)
		{
			printf("Error allocating memory for restore map\n");
			return(1);
		}	
	}

	//
	//	Now copy the restore database.
	//

	while (cRemainingBackupFiles--)
	{
		ERR err = ErrRestoreFile(hBackupFile, rgRestMap, &irgRestMap, szDatabaseLocationList);
		if (err != ERROR_SUCCESS)
		{
			printf("Unable to restore file.\n");
			return(err);
		}
	}

	//
	//	Now read the log header again.
	//
	err = ErrReadHeader(hBackupFile, &lh);

	cRemainingBackupFiles = lh.cLogFiles;

	DWORD genLow = 0xffffffffL;
	DWORD genHigh = 0;

	SZ szBackupLogPath = NULL;

	while (cRemainingBackupFiles--)
	{
		DWORD gen = 0;
        BOOL fSetGen = fFalse;

		ERR err = ErrRestoreFile(
            hBackupFile, 
            rgRestMap, 
            &irgRestMap, 
            szDatabaseLocationList, 
            &szBackupLogPath, 
            &fSetGen, 
            &gen);
		if (err != ERROR_SUCCESS)
		{
			printf("Unable to restore file.\n");
			return(err);
		}
        if (fSetGen)
        {
		    if (gen < genLow)
		    {
			    genLow = gen;
		    }

		    if (gen > genHigh)
		    {
			    genHigh = gen;
		    }
        }
	}
	
	printf("Databases successfully restored\n");

	SZ szLogPath = NULL;

	SZ szCheckpointDir = NULL;

	//
	//	Now find out where the database locations go.
	//

	SZ szDatabaseLocation = szDatabaseLocationList;

	while (*szDatabaseLocation)
	{
		BFT bftLocation = *szDatabaseLocation++;
		if (bftLocation == BFT_LOG_DIR)
		{
			szLogPath = szDatabaseLocation;
		}
		else if (bftLocation == BFT_CHECKPOINT_DIR)
		{
			szCheckpointDir = szDatabaseLocation;
		}
		else

		szDatabaseLocation += strlen(szDatabaseLocation)+1;
	}

	err = HrRestoreRegister(hbc, szCheckpointDir, szLogPath, rgRestMap, irgRestMap, szBackupLogPath, genLow, genHigh);

	if (err != ERROR_SUCCESS)
	{
	    (void) HrRestoreRegisterComplete(hbc, err);
	    (void) HrRestoreEnd(hbc);
		printf("Unable to perform restore %d\n", err);
		return(err);
	}

	(void) HrRestoreRegisterComplete(hbc, hrNone);

	err = HrRestoreEnd(hbc);

	if (err != ERROR_SUCCESS)
	{
		printf("Unable to complete restore: %d\n", err);
		return(err);
	}

	return(0);

}
