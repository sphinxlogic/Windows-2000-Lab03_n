If Exists (Select * From sysobjects Where name = N'fm_queue_cancel' And user_name(uid) = N'dbo')
	Drop Procedure dbo.fm_queue_cancel
Go

CREATE Procedure fm_queue_cancel
	(
		@borrowerNo int,
		@bibNo int
	)
As
   --set nocount on
  Begin
      Declare @tmpOrder int
      
      select @tmpOrder = req_queue_ord 
      from request
      where borrower# = @borrowerNo
      and bib# = @bibNo
      
      Delete  request 
      where borrower# = @borrowerNo
      and bib# = @bibNo
      
      --This line has to be moved into as a trigger
      Update request set req_queue_ord =req_queue_ord - 1
      where bib#=@bibNo and req_queue_ord > @tmpOrder
  
  
  End
Go

