If Exists (Select * From sysobjects Where name = N'fm_queue_location' And user_name(uid) = N'dbo')
	Drop Procedure dbo.fm_queue_location
Go


CREATE Procedure fm_queue_location
	(
		@borrowerNo int,
		@bibNo int
	)
As
 Begin
	declare @Position int
	
   set nocount on
 
   -- In case request is not found in queue...
   select @position = 0
 
   select @Position = req_queue_ord  from request as r
     where r.borrower# = @borrowerNo and r.bib# = @bibNo
 
   return @position
 End

Go

