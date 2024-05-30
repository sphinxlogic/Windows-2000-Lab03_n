If Exists (Select * From sysobjects Where name = N'fm_queue_enqueue' And user_name(uid) = N'dbo')
	Drop Procedure dbo.fm_queue_enqueue
Go

CREATE Procedure fm_queue_enqueue
	(
		@borrowerNo int,
		@bibNo int,
		@location varchar(64),
		@comment varchar(255)
	)
As
Begin
   declare @ordnum int
   
   set nocount on

   exec @ordnum = fm_queue_length @bibNo
   
   select @ordnum = @ordnum + 1
	   
   insert into request(bib#,borrower#,req_queue_ord,pickup_location,comment) 
          values(@bibNo,@borrowerNo,@ordnum,@location,@comment)
          
   return @ordnum
End
Go

