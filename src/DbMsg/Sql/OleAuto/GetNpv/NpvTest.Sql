--truncate table NPVTestData

select * from NPVTestData
go

insert NPVTestdata (cost, retrate, pmt0, pmt1, pmt2, pmt3, pmt4) 
	values (100000,0.10,25000,30000,30000,35000,40000)
insert NPVTestdata (cost, retrate, pmt0, pmt1, pmt2, pmt3, pmt4) 
	values (100000,0.13,25000,30000,30000,35000,40000)

go
select project,cost,retrate,NPV  from NPVTestData
go

insert NPVTestdata (cost, retrate, pmt0, pmt1, pmt2, pmt3, pmt4)
	select cost + 10000, retrate, pmt0, pmt1, pmt2, pmt3, pmt4 from NPVTestdata
go
select project,cost,retrate,NPV  from NPVTestData
go
