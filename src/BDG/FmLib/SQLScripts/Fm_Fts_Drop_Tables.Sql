If Exists (Select * From sysobjects Where name = N'fm_fts_drop_tables' And user_name(uid) = N'dbo')
	Drop Procedure dbo.fm_fts_drop_tables
Go

CREATE PROCEDURE fm_fts_drop_tables AS

SET NOCOUNT ON

DECLARE @tablename SYSNAME

DECLARE tnames_cursor CURSOR
   FORWARD_ONLY READ_ONLY
   FOR SELECT name FROM sysobjects WHERE name LIKE 'srch%' AND type='U'

OPEN tnames_cursor

FETCH NEXT FROM tnames_cursor INTO @tablename

WHILE (@@FETCH_STATUS <> -1)
BEGIN
	IF (@@FETCH_STATUS <> -2) 
		EXEC('DROP TABLE ' + @tablename)

	FETCH NEXT FROM tnames_cursor INTO @tablename
END

CLOSE tnames_cursor
DEALLOCATE tnames_cursor

Go

