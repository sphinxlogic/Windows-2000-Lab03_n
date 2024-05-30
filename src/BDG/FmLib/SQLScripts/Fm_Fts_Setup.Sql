If Exists (Select * From sysobjects Where name = N'fm_fts_setup' And user_name(uid) = N'dbo')
	Drop Procedure dbo.fm_fts_setup
Go

CREATE procedure fm_fts_setup
(
   @catname sysname = 'FmLib_Catalog',
   @catpath nvarchar(100) = 'C:\MSSQL7\FTDATA'
) as
set nocount on

exec sp_fulltext_database 'enable'

if exists (select ftcatid from sysfulltextcatalogs where name=@catname)
begin
   exec sp_fulltext_catalog @catname, 'stop'
   exec sp_fulltext_table 'subject', 'drop'
   exec sp_fulltext_table 'author', 'drop'
   exec sp_fulltext_table 'title', 'drop'
   exec sp_fulltext_catalog @catname, 'drop'
end

exec sp_fulltext_catalog  @catname, 'create', @catpath

exec sp_fulltext_table    'title', 'create', @catname, 'PK_Title'
exec sp_fulltext_column   'title', 'title', 'add'
exec sp_fulltext_column   'title', 'ISBN', 'add'
exec sp_fulltext_column   'title', 'notes', 'add'
exec sp_fulltext_table    'title', 'activate'

exec sp_fulltext_table    'author', 'create', @catname, 'PK_Author'
exec sp_fulltext_column   'author', 'fname', 'add'
exec sp_fulltext_column   'author', 'lname', 'add'
exec sp_fulltext_table    'author', 'activate'

exec sp_fulltext_table    'subject', 'create', @catname, 'PK_Subject'
exec sp_fulltext_column   'subject', 'text', 'add'
exec sp_fulltext_table    'subject', 'activate'

exec sp_fulltext_catalog  'FmLib_Catalog', 'start_full'


Go

