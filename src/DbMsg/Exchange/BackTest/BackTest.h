// --backtest.c-----------------------------------------------------------------
//
//  Backup sample header file.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef	_BACKTEST_
#define	_BACKTEST_

#define	DEF_BACKUP_FILE		"EXCHANGE.BAK"

#define	BACKUP_SIGNATURE	(0xFF + ('B' << 8) + ('A' << 16) + ('K' << 24))
#define	LOG_SIGNATURE		(0xFF + ('L' << 8) + ('O' << 16) + ('G' << 24))
#define	FILE_SIGNATURE		(0xFF + ('F' << 8) + ('I' << 16) + ('L' << 24))

#define	BACKUP_VERSION		0x00000001

#define fFalse  FALSE
#define fTrue   TRUE

/* Count, index types */
typedef LONG	C;
typedef LONG	I;

/* Other Hungarian */
typedef char *	SZ;
typedef WCHAR *	WSZ;
typedef long	EC;
typedef void *	PV;
typedef C		CB;
typedef I		IB;
typedef BYTE *	PB;
typedef C		CCH;
typedef	char *	PCH;

typedef struct tagBackupHeader {
	ULONG			ulSignature;
	ULONG			ulVersion;
	C				cBackupFiles;
	CB				cbDatabaseNameLength;
//	char			rgDatabaseName[cbDatabaseNameLength]
} BackupHeader, *PBackupHeader;

typedef struct tagLogHeader {
	ULONG			ulLogSignature;
	C				cLogFiles;
} LogHeader, *PLogHeader;

typedef struct tagBackupFile {
	ULONG			ulFileSignature;
	LARGE_INTEGER	liFileSize;
	BFT				bft;
	CB				cbFileNameLength;	// Includes null.
//	char			rgFileName[cbFileNameLength];
//	char			rgFileData[liFileSize];
} BackupFile, *PBackupFile;


#endif	// _BACKTEST_
