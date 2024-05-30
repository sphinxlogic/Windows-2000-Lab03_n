If Exists (Select * From sysobjects Where name = N'fm_fts_optAuthor_contains' And user_name(uid) = N'dbo')
	Drop Procedure dbo.fm_fts_optAuthor_contains
Go

CREATE PROCEDURE fm_fts_optAuthor_contains
(
     @search varchar(255),
     @tblname char(64),
     @where varchar(255)
)
As
     set nocount on
     
     exec fm_fts_create_table @tblname

     exec("insert into " + @tblname + "Select distinct t.bib# " +
     "from Title as t, Author as a, TitleAuth as ta " +
     "where (t.bib# = ta.bib# and ta.auth# = a.auth#) and " + 
     "t.n_items>0 AND CONTAINS(a.*, '" + @search + "')" + @where)


Go

