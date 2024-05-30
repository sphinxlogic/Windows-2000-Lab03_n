If Exists (Select * From sysobjects Where name = N'fm_queue_length' And user_name(uid) = N'dbo')
	Drop Procedure dbo.fm_queue_length
Go

CREATE Procedure fm_queue_length
	(
		@bibNo int
	)
As
Begin 
   declare @length int
   
   set nocount on
  
   select @length = isnull(max(req_queue_ord),0)
          from request where bib# = @bibNo
             
   return @length
End
   

Go

