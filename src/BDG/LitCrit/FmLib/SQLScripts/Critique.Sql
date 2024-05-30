If Not Exists (Select * From sysobjects Where name = N'Critique' And user_name(uid) = N'dbo')
Begin
   Create Table dbo.Critique
   	(
   	critique# int Not Null Identity (1, 1),
   	bib# int Not Null,
   	borrower# int Not Null,
   	objectId char(255) Null,
   	title varchar(255) Null,
   	rating int Not Null Constraint DF_Critique_rating Default (0),
   	dateOfCritique datetime Not Null,
   	isApproved tinyint Not Null Constraint DF_Critique_status Default (0)
   	)
   Alter Table dbo.Critique Add Constraint
   	PK_Critique Primary Key Nonclustered
   	(
   	critique#
   	)
   Alter Table dbo.Critique Add Constraint
   	UQ_Critique_bib_borrower Unique Nonclustered
   	(
   	bib#,
   	borrower#
   	)
   Alter Table dbo.Critique Add Constraint
   	FK_Critique_title Foreign Key
   	(
   	bib#
   	) References dbo.title
   	(
   	bib#
   	)
   Alter Table dbo.Critique Add Constraint
   	FK_Critique_borrower Foreign Key
   	(
   	borrower#
   	) References dbo.borrower
   	(
   	borrower#
   	)
End
Go
If Exists (Select * From sysobjects Where name = N'fm_tr_avg_rating' And user_name(uid) = N'dbo')
   DROP trigger fm_tr_avg_rating
Go
CREATE trigger fm_tr_avg_rating
	on dbo.critique
	for insert,update,delete
as
   set nocount on
      
   declare @avg_rating decimal(2,1)
   declare @avg_rounded decimal(2,1)
   declare @avg_truncated decimal(2,1)
   declare @bibno integer
      
   select @bibno = bib# from inserted
   if @bibno is null
      select @bibno = bib# from deleted
      
   if @bibno is not null
   begin
      select @avg_rating = avg(convert(decimal,rating)) from critique 
             where bib#=@bibno and isApproved=1
      select @avg_rounded = round(@avg_rating,0,0)
      select @avg_truncated = round(@avg_rating,0,1)
      update title set avg_rating=(@avg_rounded+@avg_truncated)/2 where bib#=@bibno
   end
   else
      update title set avg_rating=null where bib#=@bibno
Go