if exists (select * from sysobjects where id = object_id('dbo.NPVtestdata'))
	drop table NPVTestdata
go
create table NPVTestdata
	(project smallint identity primary key,
	 cost decimal (12,2),
	 retrate decimal (5,4),
	 pmt0 decimal (12,2),
	 pmt1 decimal (12,2),
	 pmt2 decimal (12,2),
	 pmt3 decimal (12,2),
	 pmt4 decimal (12,2),
	 NPV  decimal (12,2) NULL)
go

create trigger GetNPV_trigger on NPVTestdata for INSERT as
	declare @pObj int, @hr int
	declare @source varchar(30)
	declare @desc varchar(200)
	declare @project smallint
	declare @cost decimal (12,2)
	declare @retrate decimal (5,4)
	declare @pmt0 decimal (12,2)
	declare @pmt1 decimal (12,2)
	declare @pmt2 decimal (12,2)
	declare @pmt3 decimal (12,2)
	declare @pmt4 decimal (12,2)
	declare @NPV decimal (12,2)


	/* if only one record inserted by the command, don't open a cursor */
	if @@rowcount = 1
	begin
		exec @hr=sp_OACreate "GetNPV.CGetNPV", @pObj OUT
		if @hr <> 0 goto Err

		select @project=project, @cost=cost, @retrate=retrate, 
			@pmt0=pmt0, @pmt1=pmt1, @pmt2=pmt2, @pmt3=pmt3, @pmt4=pmt4 
			from inserted
		exec @hr=sp_OAMethod @pObj, "GetNPV", @NPV OUT, 
			@cost, @retrate, @pmt0, @pmt1, @pmt2, @pmt3, @pmt4
		if @hr <> 0 goto Err
	
		update NPVtestdata set NPV=@NPV where project=@project
	end
	else
	/* if multiple rows inserted by command (INSERT...SELECT) use a cursor */
	begin
		exec @hr=sp_OACreate "GetNPV.CGetNPV", @pObj OUT
		if @hr <> 0 goto Err

		declare c1 cursor for select project, cost, retrate, 
			pmt0, pmt1, pmt2, pmt3, pmt4 from inserted
		open c1

		while (1=1)
		begin
			fetch c1 into @project, @cost, @retrate, 
				@pmt0, @pmt1, @pmt2, @pmt3, @pmt4
			if @@fetch_status <> 0 break

			exec @hr=sp_OAMethod @pObj, "GetNPV", @NPV OUT, 
				@cost, @retrate, @pmt0, @pmt1, @pmt2, @pmt3, @pmt4
			if @hr <> 0 goto Err
	
			update NPVtestdata set NPV=@NPV where project=@project

		end
		deallocate c1
	end

	goto Done

Err:
	raiserror ('Error in calculating Net Present Value. ', 16,1)
	exec sp_OAGetErrorInfo null, @source OUT, @desc OUT
	select hr=convert(binary(4),@hr), source=@source, description=@desc
	rollback transaction

Done:
	exec sp_OADestroy @pObj
go