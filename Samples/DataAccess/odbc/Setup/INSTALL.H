/* ODBCSetupCons.h - ODBC Setup Console style header file */

BOOL ProcessErrorMessages( char * func );
BOOL Install();
BOOL IsMyDriverInstalled();
void BumpUpDriverUsageCount();
BOOL InstallMyDriver();
BOOL AddMyDSN();
void CreateAttributeString( char * pszAttributes );
BOOL GetFileVersion( char * pFilePath, char * pVersion, UINT uMaxVersionLen );
BOOL CheckIfFileExists( char * szFilePath, char * szFileName );
BOOL VersionCheckCopyFile( char * szOldPath, char * szNewPath, char * szFileName );
void CreateDriverKeywords( char * keywords );
void CopyODBCCore( char * pszPath );