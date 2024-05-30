If Exists (Select * From sysobjects Where name = N'fm_admin_update_title' And user_name(uid) = N'dbo')
	Drop Procedure dbo.fm_admin_update_title
Go

create procedure fm_admin_update_title (
   @bibNo integer,
   @title varchar(255),
   @call varchar(50),
   @coll varchar(24),
   @ISBN varchar(64),
   @publisher varchar(255),
   @pubdate char(10),
   @description varchar(255),
   @notes text
) as
   set nocount on

   if @bibNo > 0
      update title set title=@title, call=@call, coll=@coll, ISBN=@ISBN,
             publisher=@publisher, pubdate=@pubdate, description=@description,
             notes=@notes where bib#=@bibNo
   else

   begin
      insert into title values(@title, @call, @coll, @ISBN, @publisher, @pubdate,
             @description, @notes, 0, null)
      select @bibNo = @@IDENTITY
   end

   return @bibNo

Go

