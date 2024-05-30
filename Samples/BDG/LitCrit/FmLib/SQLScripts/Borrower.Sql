If Not Exists (Select * From sysobjects Where name = N'borrower' And user_name(uid) = N'dbo')
Begin
   Create Table dbo.borrower
   	(
   	borrower# int Not Null Identity (1, 1),
   	alias varchar(32) Not Null,
   	fname varchar(64) Not Null,
   	lname varchar(64) Not Null,
   	location varchar(64) Null,
   	phone varchar(32) Null,
   	title varchar(64) Null,
   	dept varchar(64) Null,
   	last_cko_date datetime Null,
   	n_ckos smallint Not Null Constraint DF_borrower_n_ckos Default (0),
   	is_staff tinyint Not Null Constraint DF_borrower_is_staff Default (0)
   	)
   Alter Table dbo.borrower Add Constraint
   	PK_borrower Primary Key Nonclustered
   	(
   	borrower#
   	)
End   	
Go
