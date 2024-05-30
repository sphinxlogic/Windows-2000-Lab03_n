If Exists (Select * From sysobjects Where name = N'fm_admin_overdue_notices' And user_name(uid) = N'dbo')
	Drop Procedure dbo.fm_admin_overdue_notices
Go

CREATE procedure fm_admin_overdue_notices as

SET NOCOUNT ON

declare @borrowerNo integer
declare @bibNo integer
declare @today datetime
declare @timelimit integer

select @today = getdate()
select @timelimit = recallperiod from settings -- A week will pass between notices

DECLARE overdue CURSOR
   LOCAL FORWARD_ONLY
   FOR SELECT borrower#, bib# from item where due_date <= @today and @today-last_overdue_notice > @timelimit
   FOR UPDATE OF last_overdue_notice

OPEN overdue

FETCH FROM overdue INTO @borrowerNo, @bibNo

WHILE (@@FETCH_STATUS <> -1)
BEGIN
	IF (@@FETCH_STATUS <> -2)
	BEGIN	
		EXEC fm_admin_send_notice @borrowerNo, @bibNo
		UPDATE item SET last_overdue_notice=@today WHERE CURRENT OF overdue
	END
	FETCH NEXT FROM overdue INTO @borrowerNo, @bibNo
END

CLOSE overdue
DEALLOCATE overdue

Go

