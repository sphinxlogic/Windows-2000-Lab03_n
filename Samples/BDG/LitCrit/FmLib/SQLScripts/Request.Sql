If Not Exists (Select * From sysobjects Where name = N'request' And user_name(uid) = N'dbo')
Begin
   Create Table dbo.request
   	(
   	request# int Not Null Identity (1, 1),
   	bib# int Not Null,
   	borrower# int Not Null,
   	req_queue_ord int Not Null,
   	pickup_location varchar(64) Not Null,
   	comment varchar(255) Null,
   	date_requested datetime Not Null Constraint DF_request_date_requested Default (getdate())
   	)
   Alter Table dbo.request Add Constraint
   	PK_request Primary Key Nonclustered
   	(
   	request#
   	)
   Alter Table dbo.request Add Constraint
   	FK_request_title Foreign Key
   	(
   	bib#
   	) References dbo.title
   	(
   	bib#
   	)
   Alter Table dbo.request Add Constraint
   	FK_request_borrower Foreign Key
   	(
   	borrower#
   	) References dbo.borrower
   	(
   	borrower#
   	)
End   	
Go
If Exists (Select * From sysobjects Where name = N'fm_tr_queue_dequeue' And user_name(uid) = N'dbo')
   DROP trigger fm_tr_queue_dequeue
Go
CREATE TRIGGER fm_tr_queue_dequeue 
	On dbo.request
	For Delete
AS
   declare @bibNo int
   declare @ordNum int

   select @bibNo = bib#, @ordNum = req_queue_ord from deleted

   Update request 
      set req_queue_ord = req_queue_ord - 1
      where bib# = @bibNo and req_queue_ord > @ordNum
Go
If Exists (Select * From sysobjects Where name = N'fm_tr_queue_enqueue' And user_name(uid) = N'dbo')
   DROP trigger fm_tr_queue_enqueue
Go
CREATE TRIGGER fm_tr_queue_enqueue 
	ON request 
	FOR Insert
AS
	declare @count integer

	-- Detect duplicate request entry
	select  @count = count(*)
		from Request as r join Inserted as i
		on r.bib# = i.bib# and r.borrower# = i.borrower#

	if      @count = 1
	   begin
		-- Ensure the request has been inserted as the last in the queue
		update Request set req_queue_ord = (select count(*)
		from Request as r join Inserted as i on r.bib#=i.bib#)
		where request# = (select request# from Inserted)
	   end
	else
	   begin
        	ROLLBACK TRANSACTION
		RaisError('Duplicate request detected',16,1)
	   end
Go
