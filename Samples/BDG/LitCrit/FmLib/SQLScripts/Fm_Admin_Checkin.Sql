If Exists (Select * From sysobjects Where name = N'fm_admin_checkin' And user_name(uid) = N'dbo')
	Drop Procedure dbo.fm_admin_checkin
Go


CREATE Procedure fm_admin_checkin
	(
		@barcode varchar(15),
		@location varchar(64)
	)
As
	set nocount on
	
	declare @bibNo integer
	declare @borrowerNo integer
	declare @critiqueenabled integer
   declare @status varchar(7)
	
	select @bibNo = bib#,@borrowerNo = borrower#,@status = item_status from item
	       where barCode = @barCode
	       
	if @status<>'in'
	begin
	
		--Sends request for submitting critique for checked in title
		select @critiqueenabled = critiqueenabled from settings
		if @critiqueenabled = 1
		begin
	         exec lc_admin_send_notice @borrowerNo,@bibNo
	   end 

	   update item set location=@location, item_status='in', borrower#=null,
	          due_date=null, last_overdue_notice=null
	          where barcode=@barcode
      return @bibNo
   end
   
   return 0
	


Go

