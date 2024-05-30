If Not Exists (Select * From sysobjects Where name = N'item_status' And user_name(uid) = N'dbo')
Begin
   Create Table dbo.item_status
   	(
   	item_status varchar(7) Not Null,
   	descr varchar(255) Null,
   	available_for_request bit Not Null Constraint DF_item_status_available_f Default (0),
   	n_items int Not Null Constraint DF_item_status_n_items Default (0)
   	)
   Alter Table dbo.item_status Add Constraint
   	PK_item_status Primary Key Nonclustered
   	(
   	item_status
   	)
End
Go
