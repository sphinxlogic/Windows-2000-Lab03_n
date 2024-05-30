If Exists (Select * From sysobjects Where name = N'item' And user_name(uid) = N'dbo')
	Drop Table dbo.item
Go

Create Table dbo.item
	(
	item# int Not Null Identity (1, 1),
	barcode varchar(16) Not Null,
	bib# int Not Null,
	location varchar(64) Not Null,
	source varchar(64) Null,
	price money Not Null Constraint DF_item_price Default (0),
	notes varchar(255) Null,
	staff_only tinyint Not Null Constraint DF_item_staff_only Default (0),
	item_status varchar(7) Not Null,
	last_cko_date datetime Null,
	n_ckos smallint Not Null Constraint DF_item_n_ckos Default (0),
	borrower# int Null,
	due_date datetime Null,
	last_overdue_notice datetime Null,
	n_renewals smallint Not Null Constraint DF_item_n_renewals Default (0)
	)
Go
Alter Table dbo.item Add Constraint
	PK_item Primary Key Nonclustered
	(
	item#
	)
Go
Alter Table dbo.item Add Constraint
	UQ_Item_Barcode Unique Nonclustered
	(
	barcode
	)
Go
Alter Table dbo.item Add Constraint
	FK_item_title Foreign Key
	(
	bib#
	) References dbo.title
	(
	bib#
	)
Go
Alter Table dbo.item Add Constraint
	FK_item_item_status Foreign Key
	(
	item_status
	) References dbo.item_status
	(
	item_status
	)
Go
Alter Table dbo.item Add Constraint
	FK_item_borrower Foreign Key
	(
	borrower#
	) References dbo.borrower
	(
	borrower#
	)
Go
Grant Select On dbo.item To public As dbo
Go
Grant Insert On dbo.item To public As dbo
Go
Grant Delete On dbo.item To public As dbo
Go
Grant Update On dbo.item To public As dbo
Go
CREATE trigger fm_tr_items_add
	on dbo.item
	for insert
as
   UPDATE title SET n_items = n_items+1 WHERE bib# = (select bib# from inserted)
   UPDATE item_status SET n_items = n_items+1 WHERE item_status = (SELECT item_status FROM inserted)

Go
CREATE trigger fm_tr_items_del
	on dbo.item
	for delete
as 
   UPDATE title SET n_items = n_items-1 WHERE bib# = (select bib# from deleted)
   UPDATE item_status SET n_items = n_items-1 WHERE item_status = (SELECT item_status FROM deleted)

Go
CREATE TRIGGER fm_tr_items_upd
   ON dbo.item
   FOR UPDATE
AS
   UPDATE item_status SET n_items = n_items - 1 WHERE item_status = (SELECT item_status FROM deleted)
   UPDATE item_status SET n_items = n_items + 1 WHERE item_status = (SELECT item_status FROM inserted)

Go
