If Exists (Select * From sysobjects Where name = N'fm_fts_optTitle_contains' And user_name(uid) = N'dbo')
	Drop Procedure dbo.fm_fts_optTitle_contains
Go

CREATE PROCEDURE fm_fts_optTitle_contains
(
    @search varchar(255),
    @tblname char(64),
    @where varchar(255)
)
As
   set nocount on

   exec fm_fts_create_table @tblname

   exec("insert into " + @tblname + "Select distinct bib# " +
   "from Title as t where t.n_items>0 AND CONTAINS(t.*,'" + @search + "') " + @where )

Go

