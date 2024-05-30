If Not Exists (Select * From sysobjects Where name = N'subject' And user_name(uid) = N'dbo')
Begin
   Create Table dbo.subject
   	(
   	subj# int Not Null Identity (1, 1),
   	text varchar(255) Not Null,
   	timestamp timestamp Not Null
   	)
   Alter Table dbo.subject Add Constraint
   	PK_subject Primary Key Nonclustered
   	(
   	subj#
   	)
End
Go
