/* Stored Procedure:	sp_loopbackDAO
** Description:	This sp connects back to SQL Server via an OLE Automation
**		object outside SQL Server.  The OLE Automation server retrieves a
**		result set from a SQL Server table and returns it back
**		to this stored procedure.
**
** This sample script should be run in the context of the 'pubs' database,
**  after creating the OLE DLL file using the SqlDao Visual Basic project
*/

if exists (select * from sysobjects where id = object_id('dbo.sp_loopbackDAO') and sysstat & 0xf = 4)
	drop proc sp_loopbackDAO
go


create proc sp_loopbackDAO
	@table_name varchar(30),
	@field_name varchar(30)
as
	declare @pObj int, @hr int
	declare @token varchar(255), @result varchar(255)

	Print 'Sample LoopbackDAO'
	Print '------------------'

	/* Create a new OLE automation object */
	exec @hr=sp_OACreate 'SQLDAO.CSqlDao', @pObj OUT

	/* Get the current client session token */
	exec sp_getbindtoken @token OUT, 1

	BEGIN TRANSACTION
		Print ' '
		/* This transaction proves that the two connections to the server
		** belonging to the same client do not deadlock each other, since
		** they are 'bound' to each other; hence the redundant update statement
		*/

		exec ("update " + @table_name + " set " + @field_name + " = " + @field_name)

		Print ' '

		/* Invoke the DaoGetAuthors method in the CSQLDao obj */
		exec @hr=sp_OAMethod @pObj, "DaoGetData", @result OUT, @table_name, @token
		if @hr <> 0
		BEGIN
			ROLLBACK TRANSACTION
		END

	COMMIT TRANSACTION

	/* Destroy the OLE Automation object */
	exec sp_OADestroy @pObj
go



/* Call the stored procedure created above */

sp_loopbackDAO authors, au_lname
go
