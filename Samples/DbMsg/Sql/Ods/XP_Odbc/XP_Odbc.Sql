/** This script updates a table and calls an extended           **/
/** procedure which retrieves rows from the same table.         **/
/** Its purpose is to show how two connections can work with    **/
/** the same rows, without blocking each other. This is         **/
/** possible because the connection opened by the extended      **/
/** stored procedure xp_gettable_odbc is bound to the           **/
/** connection that the procedure is called from.               **/
  
sp_addextendedproc 'xp_gettable_odbc', 'xp_odbc.dll'
go

begin transaction
update pubs..authors
	set phone =phone
exec xp_gettable_odbc 'pubs..authors'
commit transaction
go

sp_dropextendedproc 'xp_gettable_odbc'
go

dbcc xp_odbc(free)
go