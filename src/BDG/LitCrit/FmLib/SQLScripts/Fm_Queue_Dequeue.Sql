If Exists (Select * From sysobjects Where name = N'fm_queue_dequeue' And user_name(uid) = N'dbo')
	Drop Procedure dbo.fm_queue_dequeue
Go


CREATE Procedure fm_queue_dequeue
(
	 @bibNo integer,
  	 @borrowerNo integer output,
  	 @location varchar(64) output,
  	 @comment varchar(255) output
)
As
   set nocount on

   Declare @reqno int
   
   Select @reqno = request#, @borrowerNo = borrower#, 
          @location = pickup_location, @comment = comment
       from request where bib# = @bibNo and req_queue_ord = 1
   
   Delete from request where request# = @reqno


Go

