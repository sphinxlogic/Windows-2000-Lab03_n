If Exists (Select * From sysobjects Where name = N'fm_admin_checkout' And user_name(uid) = N'dbo')
	Drop Procedure dbo.fm_admin_checkout
Go


CREATE Procedure fm_admin_checkout
	(
		@barcode varchar(15),
		@dueDate char(10)
	)
As
	set nocount on
	
   declare @bibNo integer
	declare @itemNo integer
	declare @borrowerNo integer
	declare @location varchar(64)
	declare @comment varchar(255)
	
	select @bibNo=bib#, @itemNo=item# from item where barcode=@barcode and
	       item_status in (select item_status from item_status where
	       available_for_request=1)

   if @bibNo > 0
   begin	
	   exec fm_queue_dequeue @bibNo, @borrowerNo output,
	                         @location output, @comment output
	   if @borrowerNo > 0
	   begin
	      update item set location=@location, item_status='out', last_cko_date=GETDATE(),
	                  n_ckos=n_ckos+1, borrower#=@borrowerNo, due_date=@dueDate
	                  where item# = @itemNo
	      return @borrowerNo
	   end
	   else RaisError('No requests found for this item. (%d)',16,1,@borrowerNo)
   end
   else RaisError('Item not available for request (%d)',16,1,@bibNo)
   
   return 0

Go

