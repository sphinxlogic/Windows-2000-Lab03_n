@ECHO OFF
SETLOCAL

Set SQL_SERVER=%1
Set SQL_DATABASE=%2
Set SQL_FTSPATH=%3
Set SQL_ACCOUNT=%4
Set SQL_PASSWORD=%5

If [%SQL_SERVER%]==[] Goto ErrUsage
If [%SQL_ACCOUNT%]==[] Set SQL_ACCOUNT=sa
If [%SQL_DATABASE%]==[] Set SQL_DATABASE=FmLib
If [%SQL_FTSPATH%]==[] Set SQL_FTSPATH=C:\MSSQL7\FTDATA

Set TABLES=Title Author TitleAuth Subject TitleSubj Borrower Item_Status Item Request Settings Critique
Set PROCS1=fm_queue_cancel fm_queue_length fm_queue_enqueue fm_queue_dequeue fm_queue_location
Set PROCS2=fm_admin_send_notice fm_admin_send_recall fm_admin_renew fm_user_update
Set PROCS3=fm_admin_checkout fm_admin_overdue_notices fm_admin_recall_notices
Set PROCS4=fm_fts_create_table fm_fts_setup fm_fts_drop_tables
Set PROCS5=fm_fts_optAuthor_contains fm_fts_optSubject_contains fm_fts_optTitle_contains
Set PROCS6=lc_admin_send_notice fm_admin_checkin 

For %%a In (%TABLES% %PROCS1% %PROCS2% %PROCS3% %PROCS4% %PROCS5% %PROC6%) do (
    ISQL -S %SQL_SERVER% -U %SQL_ACCOUNT% -P %SQL_PASSWORD% -d %SQL_DATABASE% -i %%a.sql
)

:SetupFTS
ISQL -S %SQL_SERVER% -U %SQL_ACCOUNT% -P %SQL_PASSWORD% -d %SQL_DATABASE% -Q "exec fm_fts_setup 'FmLib_Catalog','%SQL_FTSPATH%'"

Goto Regress

:ErrUsage
ECHO.
ECHO Usage: %0 SQLServerName [DataBaseName] [Full-Text_Catalog_Path] [SA_Account] [SA_Password]
ECHO.
ECHO    SQLServerName          -- Name of NT Server hosting SQL 7 database
ECHO    DataBaseName           -- Name of FmLib database (default: FmLib)
ECHO    Full-Text_Catalog_Path -- Physical directory of full-text data (default: 
ECHO                              C:\MSSQL7\FTDATA)
ECHO    SA_Account             -- System administrator account name (default: 
ECHO                              sa)
ECHO    SA_Password            -- Password of system administrator account
ECHO                              (default: )
ECHO.

:Regress
pause