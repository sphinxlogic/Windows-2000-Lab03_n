If Exists (Select * From sysobjects Where name = N'fm_admin_update_item' And user_name(uid) = N'dbo')
	Drop Procedure dbo.fm_admin_update_item
Go

create procedure fm_admin_update_item (
   @itemNo integer,
   @barcode varchar(16),
   @bibNo integer,
   @location varchar(64),
   @source varchar(64),
   @price money,
   @notes varchar(255),
   @staff_only tinyint,
   @item_status varchar(7)
) as
   set nocount on

   if @itemNo > 0
      update item set barcode=@barcode, bib#=@bibNo, location=@location, source=@source,
             price=@price, notes=@notes, staff_only=@staff_only, item_status=@item_status
             where item#=@itemNo
   else
   begin
      insert into item(barcode, bib#, location, source, price, notes, staff_only, item_status)
             values(@barcode, @bibNo, @location, @source, @price, @notes, @staff_only, @item_status)
      select @itemNo = @@IDENTITY
   end

   return @itemNo


Go

