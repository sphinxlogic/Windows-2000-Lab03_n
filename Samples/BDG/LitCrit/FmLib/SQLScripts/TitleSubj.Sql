If Not Exists (Select * From sysobjects Where name = N'titlesubj' And user_name(uid) = N'dbo')
Begin
   Create Table dbo.titlesubj
   	(
   	bib# int Not Null,
   	subj# int Not Null
   	)
   Alter Table dbo.titlesubj Add Constraint
   	PK_TitleSubj Primary Key Nonclustered
   	(
   	bib#,
   	subj#
   	)
   Alter Table dbo.titlesubj Add Constraint
   	FK_titlesubj_title Foreign Key
   	(
   	bib#
   	) References dbo.title
   	(
   	bib#
   	)
   Alter Table dbo.titlesubj Add Constraint
   	FK_titlesubj_subject Foreign Key
   	(
   	subj#
   	) References dbo.subject
   	(
   	subj#
   	)
End
Go
