If Exists (Select * From sysobjects Where name = N'titlesubj' And user_name(uid) = N'dbo')
	Drop Table dbo.titlesubj
Go

Create Table dbo.titlesubj
	(
	bib# int Not Null,
	subj# int Not Null
	)
Go
Alter Table dbo.titlesubj Add Constraint
	PK_TitleSubj Primary Key Nonclustered
	(
	bib#,
	subj#
	)
Go
Alter Table dbo.titlesubj Add Constraint
	FK_titlesubj_subject Foreign Key
	(
	subj#
	) References dbo.subject
	(
	subj#
	)
Go
Alter Table dbo.titlesubj Add Constraint
	FK_titlesubj_title Foreign Key
	(
	bib#
	) References dbo.title
	(
	bib#
	)
Go
