If Exists (Select * From sysobjects Where name = N'subject' And user_name(uid) = N'dbo')
	Drop Table dbo.subject
Go

Create Table dbo.subject
	(
	subj# int Not Null Identity (1, 1),
	text varchar(255) Not Null,
	timestamp timestamp Not Null
	)
Go
Alter Table dbo.subject Add Constraint
	PK_subject Primary Key Nonclustered
	(
	subj#
	)
Go
