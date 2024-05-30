If Exists (Select * From sysobjects Where name = N'fm_fts_create_table' And user_name(uid) = N'dbo')
	Drop Procedure dbo.fm_fts_create_table
Go

CREATE Procedure fm_fts_create_table
(
	@tblname varchar(64)
)
AS
   DECLARE @rowcount integer
   SELECT @rowcount=MaxSearchResults FROM Settings
   SET ROWCOUNT @rowcount

   SET NOCOUNT ON

   IF EXISTS (Select * From sysobjects Where name=@tblname And user_name(uid)=N'dbo')
	     exec ("DROP TABLE dbo." + @tblname)
                                                                                                                                                                                                                                                             
   exec("CREATE TABLE " + @tblname +
        "(icon char(50) NULL,link char(50) NULL," +
        "title varchar(255) NULL,coll char(24) NULL," +
        "call char(50) NULL,pubdate char(4) NULL)")

Go

