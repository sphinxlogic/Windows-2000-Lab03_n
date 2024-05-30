If Exists (Select * From sysobjects Where name = N'fm_admin_renew' And user_name(uid) = N'dbo')
	Drop Procedure dbo.fm_admin_renew
Go


CREATE Procedure fm_admin_renew
	(
		@barcode varchar(15),
		@dueDate char(10)
	)
As
	set nocount on
	
	declare @itemNo int
	declare @bibNo int
	declare @n_renewals int
	declare @lngthRequest int
	declare @lngthItem int
	
	select @bibNo=bib#, @itemNo=item#, @n_renewals=n_renewals from item where barcode=@barcode
	
	-- First check with request table to see if there are present requests for this title
   exec @lngthRequest = fm_queue_length @bibNo
   
	-- If requests exist, this renewal can be satisfied only if enough items are available
   if @lngthRequest > 0
      select @lngthItem = count(*) from item where bib#=@bibNo and item_status in 
                         (select item_status from item_status where available_for_request=1)
   else
      select @lngthItem = 1  -- dummy value for logic below
      
   if @lngthItem - @lngthRequest > 0
      begin         
	      -- NOTE: Should probably limit the number of times an item can be renewed...
         select @n_renewals = @n_renewals + 1
   	   update item set due_date=@dueDate, n_renewals=@n_renewals where item#=@itemNo
         return @n_renewals
   	end
   else   	
		return 0               -- Indicate that no renewal was made  




Go

