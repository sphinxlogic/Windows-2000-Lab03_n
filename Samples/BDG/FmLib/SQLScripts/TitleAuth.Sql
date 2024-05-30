If Exists (Select * From sysobjects Where name = N'titleauth' And user_name(uid) = N'dbo')
	Drop Table dbo.titleauth
Go

Create Table dbo.titleauth
	(
	bib# int Not Null,
	auth# int Not Null
	)
Go
Alter Table dbo.titleauth Add Constraint
	FK_titleauth_title Foreign Key
	(
	bib#
	) References dbo.title
	(
	bib#
	)
Go
Alter Table dbo.titleauth Add Constraint
	FK_titleauth_author Foreign Key
	(
	auth#
	) References dbo.author
	(
	auth#
	)
Go
