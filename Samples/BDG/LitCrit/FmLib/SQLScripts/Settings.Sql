If Not Exists (Select * From sysobjects Where name = N'Settings' And user_name(uid) = N'dbo')
   Create Table dbo.Settings
   	(
   	ExchangeServer char(128) Not Null,
   	ExchangeOrg char(128) Not Null,
   	ExchangeSite char(128) Not Null,
   	ExchangeAdmin char(128) Null,
   	ExchangePass char(128) Null,
   	DefaultLocation char(64) Not Null Constraint DF_Settings_DefaultLocation Default ('library'),
   	DefaultDomainName char(64) Not Null Constraint DF_Settings_DefaultAlias Default ('microsoft.com'),
   	DefaultItemStatus char(64) Not Null Constraint DF_Settings_DefaultItemStatus Default ('in'),
   	Debug tinyint Not Null Constraint DF_Settings_Debug Default (1),
   	CheckoutPeriod int Not Null Constraint DF_Settings_OTime Default (21),
   	RecallPeriod int Not Null Constraint DF_Settings_RTime Default (7),
   	MaxSearchResults int Not Null Constraint DF_Settings_MaxSearchResults Default (600),
   	DefaultContactEmail char(10) Not Null Constraint DF_Settings_AdminAlias Default ('bdgfeed'),
   	CritiqueEnabled tinyint Not Null Constraint DF_Settings_CritiqueEnabled Default (1),
   	ApprovalRequired tinyint Not Null Constraint DF_Settings_ApprovalRequired Default (0),
   	ApproverEmail char(64) Null,
   	MaxFindResults int Not Null Constraint DF_Settings_MaxFindResults Default (600),
	   PublicFolderName char(255) Null,
	   PublicFolderObjectID char(255) Null
   	)
Else
   Alter Table dbo.Settings ADD
      DefaultContactEmail char(10) Not Null Constraint DF_Settings_AdminAlias Default ('bdgfeed'),
   	CritiqueEnabled tinyint Not Null Constraint DF_Settings_CritiqueEnabled Default (1),
   	ApprovalRequired tinyint Not Null Constraint DF_Settings_ApprovalRequired Default (0),
   	ApproverEmail char(64) Null,
   	MaxFindResults int Not Null Constraint DF_Settings_MaxFindResults Default (600),
	   PublicFolderName char(255) Null,
	   PublicFolderObjectID char(255) Null
Go

