If Exists (Select * From sysobjects Where name = N'Settings' And user_name(uid) = N'dbo')
	Drop Table dbo.Settings
Go

Create Table dbo.Settings
	(
	ExchangeServer char(128) Not Null,
	ExchangeOrg char(128) Not Null,
	ExchangeSite char(128) Not Null,
	ExchangeAdmin char(128) Null,
	ExchangePass char(128) Null,
	DefaultLocation char(64) Not Null Constraint DF_Settings_DefaultLocation Default ('library'),
	DefaultDomainName char(64) Not Null Constraint DF_Settings_DefaultAlias Default ('Microsoft.com'),
	DefaultItemStatus char(64) Not Null Constraint DF_Settings_DefaultItemStatus Default ('in'),
	Debug tinyint Not Null Constraint DF_Settings_Debug Default (1),
	CheckoutPeriod int Not Null Constraint DF_Settings_OTime Default (21),
	RecallPeriod int Not Null Constraint DF_Settings_RTime Default (7),
	MaxSearchResults int Not Null Constraint DF_Settings_MaxSearchResults Default (600)
	)
Go
Alter Table dbo.Settings Add Constraint
	PK_Settings Primary Key Nonclustered
	(
	ExchangeServer
	)
Go
