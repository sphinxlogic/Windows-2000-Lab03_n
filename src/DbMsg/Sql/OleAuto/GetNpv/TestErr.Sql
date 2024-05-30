/* Stored Procedure:	sp_testerr
** Description:		This sp connects back to SQL Server via an OA
**			object outside SS.  The OA server retrieves a
**			result set from a SS table and returns it back
**			to this sp.
*/


if exists (select * from sysobjects where id = object_id('dbo.sp_testerr') and sysstat & 0xf = 4)
	drop proc sp_testerr
go

create proc sp_testerr as
	declare @pObj int, @hr int
	declare @source varchar(30), @desc varchar(200)
	declare @property varchar(30), @result int

	Print 'Test: testerr'
	Print '--------------'

	/* Create a new OLE automation object */
	exec @hr=sp_OACreate "GetNPV.CGetNPV", @pObj OUT
	if @hr <> 0 goto Err

	Print ' '
	exec @hr=sp_OAGetProperty @pObj, "MyProperty", @property OUT
	if @hr <> 0 goto Err
	select "MyProperty value"=@property

	Print ' '
	Print 'Calling TestError method'
	exec @hr=sp_OAMethod @pObj, "TestError", @result OUT
	if @hr <> 0 goto Err

	select "Result"=@result
	goto Done

Err:
	Print ' '
	Print '## ERROR ##'
	exec sp_OAGetErrorInfo null, @source OUT, @desc OUT
	select hr=convert(binary(4),@hr), source=@source, description=@desc
	goto Done

Done:
	exec sp_OADestroy @pObj
	return @hr
go