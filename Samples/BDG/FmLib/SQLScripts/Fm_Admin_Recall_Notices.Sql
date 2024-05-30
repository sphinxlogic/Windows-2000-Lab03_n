If Exists (Select * From sysobjects Where name = N'fm_admin_recall_notices' And user_name(uid) = N'dbo')
	Drop Procedure dbo.fm_admin_recall_notices
Go

CREATE procedure fm_admin_recall_notices as 
 
 set nocount on

 declare @borrowerNo integer
 declare @bibNo integer
 declare @today datetime
 declare @duedate datetime
 declare @timelimit integer
 
 select @today = getdate()
 select @timelimit = recallperiod from settings 

 DECLARE recall CURSOR
     FOR SELECT i.borrower#, i.bib# from item i JOIN request r ON r.bib# = i.bib#  where due_date - @today > @timeLimit and @today-last_overdue_notice > @timelimit
     FOR UPDATE OF last_overdue_notice
     
 Open recall
 
 FETCH FROM recall INTO @borrowerNo, @bibNo

 WHILE(@@FETCH_STATUS <> -1)
 BEGIN 
    IF(@@FETCH_STATUS<> -2 ) 
    BEGIN
       EXEC fm_admin_send_recall @borrowerNo, @bibNo
       UPDATE item SET last_overdue_notice = @today WHERE CURRENT OF recall
    END
    FETCH NEXT FROM overdue INTO @borrowerNo, @bibNo
 END

 CLOSE recall
 DEALLOCATE recall
 

Go

