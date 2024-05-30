If Exists (Select * From sysobjects Where name = N'fm_admin_send_notice' And user_name(uid) = N'dbo')
	Drop Procedure dbo.fm_admin_send_notice
Go


CREATE procedure fm_admin_send_notice
(
    @borrowerNo integer,
    @bibNo integer
)
as
    declare @fname varchar(64)
    declare @lname varchar(64)
    declare @fullname varchar(128)
    declare @alias varchar(50)
    declare @title varchar(255)
    declare @domain varchar(128)

    select @alias = alias, @fname = fname, @lname = lname from borrower where borrower# = @borrowerNo
    select @fullname = @lname + ', ' + @fname
    select @title = title from title where bib# = @bibNo

    create table ##TEMP (c1 varchar(80))
    insert into ##TEMP values(@fname + ',')
    insert into ##TEMP values('The following book is overdue:')
    insert into ##TEMP values(@title)
    insert into ##TEMP values('Please return the book to the library at your earliest convenience.')
    insert into ##TEMP values('Thanks,')
    insert into ##TEMP values('The Library')

    select @domain = defaultdomainname from settings
    select @alias = RTRIM(@alias + '@' + @domain)

    exec master.dbo.xp_sendmail @recipients = @alias, @query = 'SELECT RTRIM(c1) FROM ##TEMP', 
         @subject = 'Automatic Overdue Notice', @no_output = 'TRUE', @no_header='TRUE',
         @width = 80

    if @@ERROR = 0
	    print 'Notice sent to ''' + @fullname + ''' for title ''' + @title + ''''
    else
	    print 'Failed to send notice to ''' + @fullname + '''. (Error ' + @@ERROR + ')'

    drop table ##TEMP
    


Go

