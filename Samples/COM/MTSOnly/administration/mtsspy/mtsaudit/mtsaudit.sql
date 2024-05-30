/* Microsoft SQL Server - Scripting			*/
/* Server: JOELONG					*/
/* Database: MtsAudit					*/
/* Creation Date 8/19/97 11:03:32 AM 			*/

set quoted_identifier on
GO

/****** Object:  Table dbo.Authenticate    Script Date: 8/19/97 11:03:34 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.Authenticate') and sysstat & 0xf = 3)
	drop table "dbo"."Authenticate"
GO

/****** Object:  Table dbo.MethodEvents    Script Date: 8/19/97 11:03:34 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.MethodEvents') and sysstat & 0xf = 3)
	drop table "dbo"."MethodEvents"
GO

/****** Object:  Table dbo.ObjectEvents    Script Date: 8/19/97 11:03:34 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.ObjectEvents') and sysstat & 0xf = 3)
	drop table "dbo"."ObjectEvents"
GO

/****** Object:  Table dbo.PackageEvents    Script Date: 8/19/97 11:03:34 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.PackageEvents') and sysstat & 0xf = 3)
	drop table "dbo"."PackageEvents"
GO

/****** Object:  Table dbo.ResourceEvents    Script Date: 8/19/97 11:03:34 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.ResourceEvents') and sysstat & 0xf = 3)
	drop table "dbo"."ResourceEvents"
GO

/****** Object:  Table dbo.ThreadEvents    Script Date: 8/19/97 11:03:34 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.ThreadEvents') and sysstat & 0xf = 3)
	drop table "dbo"."ThreadEvents"
GO

/****** Object:  Table dbo.TransactionEvents    Script Date: 8/19/97 11:03:34 AM ******/
if exists (select * from sysobjects where id = object_id('dbo.TransactionEvents') and sysstat & 0xf = 3)
	drop table "dbo"."TransactionEvents"
GO

/****** Object:  Table dbo.Authenticate    Script Date: 8/19/97 11:03:34 AM ******/
CREATE TABLE "dbo"."Authenticate" (
	"ctr" "int" IDENTITY (1, 1) NOT NULL ,
	"tick" "int" NOT NULL ,
	"guidActivity" varchar (40) NOT NULL ,
	"OriginalUser" varchar (255) NULL ,
	"DirectUser" varchar (255) NULL ,
	"fImpersonation" "int" NOT NULL 
)
GO

/****** Object:  Table dbo.MethodEvents    Script Date: 8/19/97 11:03:34 AM ******/
CREATE TABLE "dbo"."MethodEvents" (
	"ctr" "int" IDENTITY (1, 1) NOT NULL ,
	"tick" "int" NOT NULL ,
	"oid" "int" NOT NULL ,
	"cid" varchar (40) NOT NULL ,
	"rid" varchar (40) NOT NULL ,
	"Method" varchar(255) NULL,
	"hresult" "int" NULL ,
	"Event" varchar (32) NOT NULL ,
	CONSTRAINT "PK___4__10" PRIMARY KEY  CLUSTERED 
	(
		"ctr"
	)
)
GO

/****** Object:  Table dbo.ObjectEvents    Script Date: 8/19/97 11:03:35 AM ******/
CREATE TABLE "dbo"."ObjectEvents" (
	"ctr" "int" IDENTITY (1, 1) NOT NULL ,
	"tick" "int" NOT NULL ,
	"activity" varchar (40) NULL ,
	"clsid" varchar (40) NULL ,
	"tsid" varchar (40) NULL ,
	"ObjectId" "int" NOT NULL ,
	"Event" varchar (32) NOT NULL ,
	CONSTRAINT "PK___2__10" PRIMARY KEY  CLUSTERED 
	(
		"ctr"
	)
)
GO

/****** Object:  Table dbo.PackageEvents    Script Date: 8/19/97 11:03:35 AM ******/
CREATE TABLE "dbo"."PackageEvents" (
	"ctr" "int" IDENTITY (1, 1) NOT NULL ,
	"tick" "int" NOT NULL ,
	"guid" varchar (40) NOT NULL ,
	"name" varchar (255) NOT NULL ,
	CONSTRAINT "PK___1__10" PRIMARY KEY  CLUSTERED 
	(
		"ctr"
	)
)
GO

/****** Object:  Table dbo.ResourceEvents    Script Date: 8/19/97 11:03:35 AM ******/
CREATE TABLE "dbo"."ResourceEvents" (
	"ctr" "int" IDENTITY (1, 1) NOT NULL ,
	"ActivityGuid" varchar(40) NULL, 
	"tick" "int" NOT NULL ,
	"ObjectId" "int" NOT NULL ,
	"type" varchar (255) NOT NULL ,
	"resId" "int" NOT NULL ,
	"Event" varchar (32) NOT NULL ,
	CONSTRAINT "PK___5__10" PRIMARY KEY  CLUSTERED 
	(
		"ctr"
	)
)
GO

/****** Object:  Table dbo.ThreadEvents    Script Date: 8/19/97 11:03:35 AM ******/
CREATE TABLE "dbo"."ThreadEvents" (
	"ctr" "int" IDENTITY (1, 1) NOT NULL ,
	"tick" "int" NOT NULL ,
	"ThreadId" "int" NOT NULL ,
	"guidActivity" varchar (40) NULL ,
	"Event" varchar (32) NOT NULL ,
	CONSTRAINT "PK_ThreadEvents_1__10" PRIMARY KEY  CLUSTERED 
	(
		"ctr"
	)
)
GO

/****** Object:  Table dbo.TransactionEvents    Script Date: 8/19/97 11:03:35 AM ******/
CREATE TABLE "dbo"."TransactionEvents" (
	"ctr" "int" IDENTITY (1, 1) NOT NULL ,
	"tick" "int" NOT NULL ,
	"guidTx" varchar (40) NOT NULL ,
	"tsid" varchar (40) NULL ,
	"root" "int" NULL ,
	"voteYes" "int" NULL ,
	"event" varchar (32) NOT NULL ,
	CONSTRAINT "PK___3__10" PRIMARY KEY  CLUSTERED 
	(
		"ctr"
	)
)
GO

