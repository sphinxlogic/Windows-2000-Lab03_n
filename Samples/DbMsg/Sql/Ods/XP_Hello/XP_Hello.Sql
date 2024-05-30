-- TSQL script exercising xp_hello sample
sp_addextendedproc 'xp_hello', 'xp_hello.dll'
go

-- Call xp_hello with literal parameters
declare @txt varchar(33)
exec xp_hello @txt OUTPUT
select @txt AS OUTPUT_Parameter
go

-- EXPECTED RESULTS
-- Column 1:
-- ---------
-- Hello World!

-- (1 row(s) affected)

-- OUTPUT_PARAMETER
-- ----------------
-- Hello World!

-- (1 row(s) affected)

