If Not Exists (Select * From sysobjects Where name = N'titleauth' And user_name(uid) = N'dbo')
Begin
   Create Table dbo.titleauth
   	(
   	bib# int Not Null,
   	auth# int Not Null
   	)
   Alter Table dbo.titleauth Add Constraint
   	FK_titleauth_title Foreign Key
   	(
   	bib#
   	) References dbo.title
   	(
   	bib#
   	)
   Alter Table dbo.titleauth Add Constraint
   	FK_titleauth_author Foreign Key
   	(
   	auth#
   	) References dbo.author
   	(
   	auth#
   	)
End
Go
