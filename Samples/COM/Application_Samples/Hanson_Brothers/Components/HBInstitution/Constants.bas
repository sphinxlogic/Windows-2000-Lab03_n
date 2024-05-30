Attribute VB_Name = "Constants"
Attribute VB_Ext_KEY = "RVB_UniqueId" ,"37367D1A0177"
'/***********************************************************************************\
'*************************************************************************************
'*  COM+ Hanson Brothers SDK Sample
'*  Module Constants (HBInstitution)
'*
'*  This file is provided as part of the COM+ Software Development Kit.
'*
'*  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
'*  EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES
'*  OF MERCHANTABILITY AND/OR FITNESS FOR A  PARTICULAR PURPOSE.
'*
'* Copyright (C) 1999 Microsoft Corporation, All rights reserved
'**************************************************************************************
'\***********************************************************************************/

Public Const STATIC_DNS = False

Dim customerId As String

Public Const HB_INSTITUTION_ID = 42

Public Const COMPLUS_MODE = True

Public Const TEST_STUB = False ' Set to True to Test Stubs

Public Const STUB_SYMBOL = "MSFT"

Public Const STUB_ACCOUNT = "12345678"

Public Const SUCCESS = 1

Public Const FAILED = 0

Public Const NO_RECORDS_FOUND = 2

Public Const RECORD_INSERTION_FAILED = 3

Public Const RECORD_UPDATE_FAILED = 4

Public Const RECORD_READ_FAILED = 5

Public Const NOT_ACKNOWLEDGED = 0

Public Const acknowledged = 1


Public Const PROVIDER = "SQLOLEDB"

Public Const SHAPE_PROVIDER = "provider=msdatashape;"

Public Const DSN = "market"

Public Const DSN_USER_ID = "sa"

Public Const DSN_PASSWORD = ""

Public Const COMMISSION_PERCENTAGE = 0.01

Public Const CUSTOMER = 3

Public Const BUY = 0

Public Const SELL = 1

Public Const HOLDING_SUMMARY = 99

Public Const UNCONFIRMED = 0

Public Const CONFIRMED = 1

Public Const SETTLED = 2

Public Const RECONCILED = 3

Public Const CONFIRMED_ERROR = 21

Public Const SETTLED_ERROR = 22

Public Const CANCELED = 4

Public Const ICONFIRMED = 5

Public Const MARKET_ORDER = 0

Public Const LIMIT_ORDER = 1

Public Const DEFAULT_HOLDING_TYPE = 1

Public Const SLOW_DELTA = 1.12
Public Const FAST_DELTA = 1.95
Public Const NO_DELTA = 0.2

Public Const INIT_ALL = 1
Public Const INIT_CUSTOMER = 2
Public Const INIT_QUOTES = 3
Public Const INIT_ORDERS_ONLY = 4

Public Const CONNECT_CONSTANT = "DRIVER={SQL Server}; SERVER=(local);DATABASE=market;user id=sa;password="


