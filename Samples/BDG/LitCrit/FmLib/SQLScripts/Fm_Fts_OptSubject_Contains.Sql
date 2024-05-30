If Exists (Select * From sysobjects Where name = N'fm_fts_optSubject_contains' And user_name(uid) = N'dbo')
	Drop Procedure dbo.fm_fts_optSubject_contains
Go

CREATE PROCEDURE fm_fts_optSubject_contains
(
     @search varchar(255),
     @tblname char(64),
     @where varchar(255)
)
As
     set nocount on
     
     exec fm_fts_create_table @tblname

     exec("insert into " + @tblname + "Select distinct t.bib# " +
     "from Title as t, Subject as s, TitleSubj as ts " +
     "where (t.bib# = ts.bib# and ts.subj# = s.subj#) and " + 
     "t.n_items>0 AND CONTAINS(s.*, '" + @search + "')" + @where)


Go

