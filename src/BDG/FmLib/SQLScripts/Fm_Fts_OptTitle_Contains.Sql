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
                                                                                                                                                                                                                                                           
   exec("insert into " + @tblname +                                                                                                                                                                                                                           
   " Select distinct stuff('../images/icon.gif',15,0,coll) as Icon," +                                                                                                                                                                                    
   "stuff('javascript:Dolong()',19,0,ltrim(str(t.bib#))) as Link," +                                                                                                                                                                                     
   "t.title,t.coll,t.call,convert(char(4),t.pubdate,112) as Pubdate " +                                                                                                                                                                                  
   "from Title as t where t.n_items>0 AND CONTAINS(t.*,'" + @search + "') " + @where )

Go

