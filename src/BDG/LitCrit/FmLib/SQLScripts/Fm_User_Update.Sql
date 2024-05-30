If Exists (Select * From sysobjects Where name = N'fm_user_update' And user_name(uid) = N'dbo')
	Drop Procedure dbo.fm_user_update
Go


CREATE Procedure fm_user_update
(
	@alias varchar(32),
	@fname varchar(64),
	@lname varchar(64),
	@location varchar(64),
	@title varchar(64),
	@phone varchar(32),
	@dept varchar(64)
)
As
	set nocount on
	
	declare @borrowerno int
	
	-- In case this record doesn't exist
	select @borrowerno = 0

	select @borrowerno = borrower# from borrower where alias=@alias
	
	if @borrowerno = 0 
	begin
	   insert into borrower(alias,fname,lname,location,title,phone,dept)
	          values(@alias,@fname,@lname,@location,@title,@phone,@dept)
	   select @borrowerno = @@IDENTITY
	end
	else
	   update borrower 
	   set fname=@fname, lname=@lname, location=@location, title=@title, 
	       phone=@phone, dept=@dept
	   where borrower# = @borrowerno
	
	return @borrowerno



Go

