-- TSQL script exercising xp_srv_paraminfo_sample
sp_addextendedproc 'xp_srv_paraminfo_sample', 'xp_param.dll'
go

-- Call xp_srv_paraminfo_sample with literal parameters
exec xp_srv_paraminfo_sample 7, 'Produce', 'Dried fruit and bean curd'
go

-- EXPECTED RESULTS
-- Parameter 1: Input Parameter 2: Input Parameter 3: Input
-- ------------------ ------------------ -------------------------
-- 7                  Produce            Dried fruit and bean curd

-- (1 row(s) affected)

-- Call xp_srv_paraminfo_sample with variable parameters
declare @CategoryID int
declare @CategoryName varchar(15)
declare @Description nvarchar(50)
declare @OrderDate datetime
declare @Discount real

select @CategoryID = 7
select @CategoryName = 'Produce'
select @Description = 'Dried fruit and bean curd'
select @OrderDate = 'April 22, 1995'
select @Discount = .025

exec xp_srv_paraminfo_sample @CategoryID OUTPUT, @CategoryName,
    @Description OUTPUT, @OrderDate, @Discount OUTPUT
go

-- EXPECTED RESULTS
-- Parameter 1: Output Parameter 2: Input Parameter 3: Output       Parameter 4: Input          Parameter 5: Output               
-- ------------------- ------------------ ------------------------- --------------------------- -------------------
-- 7                   Produce            Dried fruit and bean curd 1995-04-22 00:00:00.000     0.025

-- (1 row(s) affected)

