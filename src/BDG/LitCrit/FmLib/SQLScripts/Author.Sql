If Not Exists (Select * From sysobjects Where name = N'author' And user_name(uid) = N'dbo')
Begin
   Create Table dbo.author
   	(
   	auth# int Not Null Identity (1, 1),
   	fname varchar(128) Not Null,
   	lname varchar(128) Not Null,
   	timestamp timestamp Not Null
   	)
   Alter Table dbo.author Add Constraint
   	PK_author Primary Key Nonclustered
   	(
   	auth#
   	)
End
Go

