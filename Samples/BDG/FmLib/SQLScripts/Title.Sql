If Exists (Select * From sysobjects Where name = N'title' And user_name(uid) = N'dbo')
	Drop Table dbo.title
Go

Create Table dbo.title
	(
	bib# int Not Null Identity (1, 1),
	title varchar(255) Not Null,
	call varchar(50) Null,
	coll varchar(24) Null,
	ISBN varchar(64) Null,
	publisher varchar(255) Null,
	pubdate datetime Null,
	description varchar(255) Null,
	notes text Null,
	n_items int Not Null Constraint DF_title_nitems Default (0),
	timestamp timestamp Not Null
	)
Go
Alter Table dbo.title Add Constraint
	PK_title Primary Key Nonclustered
	(
	bib#
	)
Go
