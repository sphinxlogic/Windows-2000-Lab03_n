VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 1  'NoTransaction
END
Attribute VB_Name = "ICustomer"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Attribute VB_Ext_KEY = "RVB_UniqueId" ,"37367D050128"
'/***********************************************************************************\
'*************************************************************************************
'*  COM+ Hanson Brothers SDK Sample
'*  Class ICustomer (HBInstitution)
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

Option Explicit

Public Function IsCustomer(ByVal sSSN As String) As Long

    Dim sSQL As String
    Dim oData As DataLayer
    Dim rs As ADODB.Recordset
    
    IsCustomer = FAILED
    
    On Error GoTo ErrorHandler
    
    If sSSN = "" Then
        If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
        Exit Function
    End If
    
    Set oData = New HBInstitution.DataLayer
     
    sSQL = "SELECT * FROM customer WHERE ssn = '" & sSSN & "'"

    Set rs = oData.ExecSql(sSQL, PROVIDER, GetDSN(), True, True)

    If rs.EOF <> True Then
            IsCustomer = SUCCESS
    End If

    ' If the Recordset is Open then Close It
    If rs.State = adStateOpen Then
        rs.Close
    End If
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
           
    Exit Function
    
ErrorHandler:
    
    If Not rs Is Nothing Then
        Set rs = Nothing
    End If
    
    If Not oData Is Nothing Then
        Set oData = Nothing
    End If
    
    ' if we have a Context then Abort
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    LogError "ICustomer.IsCustomer"

End Function

Public Function ValidateUser(ByVal cUserName As String, ByVal cPassword As String) As Long

    Dim sSQL As String
    Dim oData As DataLayer
    Dim rs As ADODB.Recordset
    Dim sPIN As String
    
    ValidateUser = FAILED
    
    On Error GoTo ErrorHandler
    
    If cUserName = "" Then
        If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
        Exit Function
    End If
    
    Set oData = New HBInstitution.DataLayer
     
    sSQL = "SELECT * FROM customer WHERE ssn = '" & cUserName & "'"

    Set rs = oData.ExecSql(sSQL, PROVIDER, GetDSN(), True, True)
    
    If rs.EOF <> True Then
        sPIN = rs("pin")
        If cPassword = Trim(sPIN & "") Then
            ValidateUser = CLng(rs("type"))
        End If
    End If
    
    ' If the Recordset is Open then Close It
    If rs.State = adStateOpen Then
        rs.Close
    End If
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
           
    Exit Function
    
ErrorHandler:
    
    If Not rs Is Nothing Then
        Set rs = Nothing
    End If
    
    If Not oData Is Nothing Then
        Set oData = Nothing
    End If
    
    ' if we have a Context then Abort
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    LogError "ICustomer.ValidateUser"

End Function

Public Function GetCustomerInfo(ByVal sSSN As String, ByRef cusType As Variant, ByRef name As Variant, ByRef address As Variant, ByRef phone As Variant, ByRef Email As Variant, ByRef sMsg As Variant) As Long
    
    Dim oData As DataLayer
    Dim rs As Variant
    Dim sSQL As String
    Dim lNumRecs As Long
    
    GetCustomerInfo = FAILED
    
    If sSSN = "" Then
        If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
        Exit Function
    End If
    
    On Error GoTo ErrorHandler
    
    Set oData = New HBInstitution.DataLayer
    
    sSQL = "Select * from Customer where ssn = '" & sSSN & "'"
    
    Set rs = oData.ExecSql(sSQL, PROVIDER, GetDSN(), True)
        
    If Not rs.EOF Then
        With rs
            cusType = !Type
            name = Trim(!firstName) & " " & Trim(!middleName) & " " & Trim(!lastName)
            address = Trim(!streetAddress) & " " & Trim(!City) & " " & Trim(!State) & " " & Trim(!Zip)
            phone = Trim(!homePhone)
            Email = Trim(!Email)
        End With
        GetCustomerInfo = SUCCESS
     Else
        GetCustomerInfo = NO_RECORDS_FOUND
    End If

    ' If the Recordset is Open then Close It
    If rs.State = adStateOpen Then
        rs.Close
    End If

    ' If we have a Context the SetComplete
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
           
    Exit Function
    
ErrorHandler:

    If Not rs Is Nothing Then
        Set rs = Nothing
    End If
    
    If Not oData Is Nothing Then
        Set oData = Nothing
    End If
    
    ' if we have a Context then Abort
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    sMsg = LogErrorStr("ICustomer.GetCustomerInfo")

End Function

Public Function AddCustomer(ByVal ssn As String, ByVal PIN As String, _
ByVal firstName As String, ByVal lastName As String, ByVal middleName As String, _
ByVal homePhone As String, ByVal workPhone As String, ByVal Email As String, _
ByVal streetAddress As String, ByVal City As String, ByVal State As String, ByVal Zip As String, _
ByVal acctTypeP As Boolean, ByVal acctTypeG As Boolean, ByVal acctTypeS As Boolean, _
ByVal DepositP As Currency, ByVal DepositG As Currency, ByVal DepositS As Currency, _
ByRef sMsg As Variant) As Long

    ' acctType = "P", or "G", or "S"
    Dim acctType As String
    Dim cn As ADODB.Connection
    Dim rs As ADODB.Recordset
    Dim sSQL As String
    Dim ret As Long
    Dim Level As Integer
    Dim deposit As Currency
    
    AddCustomer = FAILED
    
    On Error GoTo ErrorHandler
    
    Set cn = New ADODB.Connection
    
    cn.Open GetDSN()
    
    sSQL = "SELECT ssn FROM customer WHERE ssn = '" & ssn & "'"
    Set rs = cn.Execute(sSQL)
    
    If Not rs.EOF Then
        sMsg = "Customer SSN " & ssn & " Already Present. Cannot Create new Customer or Account."
        GoTo Done
    End If

    sSQL = "INSERT INTO customer"
    sSQL = sSQL & " VALUES ( '" & ssn & "'"
    sSQL = sSQL & ", " & CUSTOMER
    sSQL = sSQL & ", '" & firstName & "'"
    sSQL = sSQL & ", '" & lastName & "'"
    sSQL = sSQL & ", '" & middleName & "'"
    sSQL = sSQL & ", '" & homePhone & "'"
    sSQL = sSQL & ", '" & workPhone & "'"
    sSQL = sSQL & ", '" & Email & "'"
    sSQL = sSQL & ", '" & streetAddress & "'"
    sSQL = sSQL & ", '" & City & "'"
    sSQL = sSQL & ", '" & State & "'"
    sSQL = sSQL & ", '" & Zip & "'"
    sSQL = sSQL & ", " & 1
    sSQL = sSQL & ", '" & PIN & "'"
    sSQL = sSQL & ", " & 0
    sSQL = sSQL & " )"
            
    Set rs = cn.Execute(sSQL)
    
    sMsg = "Customer Added Successfully"
   
      
    If (acctTypeP) Then
        Level = 4
        deposit = DepositP
        sSQL = "INSERT INTO account"
        sSQL = sSQL & " VALUES ( '" & ssn & "'"
        sSQL = sSQL & ", '" & acctType & ssn & "'"
        sSQL = sSQL & ", " & Level
        sSQL = sSQL & ", " & 0
        sSQL = sSQL & ", " & 1
        sSQL = sSQL & ", " & 2
        sSQL = sSQL & ", " & 1
        sSQL = sSQL & ", '" & "US" & "'"
        sSQL = sSQL & ", " & 0
        sSQL = sSQL & ", " & 0
        sSQL = sSQL & ", " & deposit
        sSQL = sSQL & " )"
        Set rs = cn.Execute(sSQL)
     End If
     If (acctTypeG) Then
        Level = 3
        deposit = DepositG
        sSQL = "INSERT INTO account"
        sSQL = sSQL & " VALUES ( '" & ssn & "'"
        sSQL = sSQL & ", '" & acctType & ssn & "'"
        sSQL = sSQL & ", " & Level
        sSQL = sSQL & ", " & 0
        sSQL = sSQL & ", " & 1
        sSQL = sSQL & ", " & 2
        sSQL = sSQL & ", " & 1
        sSQL = sSQL & ", '" & "US" & "'"
        sSQL = sSQL & ", " & 0
        sSQL = sSQL & ", " & 0
        sSQL = sSQL & ", " & deposit
        sSQL = sSQL & " )"
        Set rs = cn.Execute(sSQL)
     End If
     If (acctTypeS) Then
        Level = 2
        deposit = DepositS
        sSQL = "INSERT INTO account"
        sSQL = sSQL & " VALUES ( '" & ssn & "'"
        sSQL = sSQL & ", '" & acctType & ssn & "'"
        sSQL = sSQL & ", " & Level
        sSQL = sSQL & ", " & 0
        sSQL = sSQL & ", " & 1
        sSQL = sSQL & ", " & 2
        sSQL = sSQL & ", " & 1
        sSQL = sSQL & ", '" & "US" & "'"
        sSQL = sSQL & ", " & 0
        sSQL = sSQL & ", " & 0
        sSQL = sSQL & ", " & deposit
        sSQL = sSQL & " )"
        Set rs = cn.Execute(sSQL)
     End If
    
    sMsg = "Customer " & ssn & " Added Successfully"
    
    AddCustomer = SUCCESS
    
Done:
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
    
    Exit Function

ErrorHandler:

    If Not cn Is Nothing Then
        Set cn = Nothing
    End If
    
    If Not rs Is Nothing Then
        Set rs = Nothing
    End If
    
    AddCustomer = FAILED
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
     
    sMsg = LogErrorStr("ICustomer.AddCustomer. " & sMsg & " SQL = " & sSQL)
    
    
End Function

Public Function GetPortfolioHierarchy(ByVal cUserName As String, ByVal cPassword As String, ByRef rs As Variant, ByRef sMsg As Variant) As Long

    GetPortfolioHierarchy = FAILED
  
    On Error GoTo ErrorHandler
  
    Dim cn As ADODB.Connection
    Dim cmd As ADODB.Command
    Dim rst As ADODB.Recordset
    
    If cUserName = "" Then
        Exit Function
    End If
    
    Set cn = New ADODB.Connection
    Set cmd = New ADODB.Command
    Set rst = New ADODB.Recordset
    
    cn.Open SHAPE_PROVIDER & GetDSN()
     
    rst.CursorLocation = adUseClient
    
    cmd.CommandText = "shape( shape { select ad.ssn, ad.acctNumber, ad.acctType, ad.cash, ad.cashDebit, ad.netWorth from account ad where ad.ssn = ? order by acctNumber} Append calc(cash - cashDebit) As AvailCash ) as rsAccountDetail sum(rsAccountDetail.netWorth) as TotalNetWorth, sum(rsAccountDetail.AvailCash) as TotalCashAvail, Any(rsAccountDetail.acctNumber) as AcctNumber, rsAccountDetail by acctNumber) as rsAccounts"
      
    cmd.CommandType = adCmdText
    Set cmd.ActiveConnection = cn
    
    cmd.Parameters.Append cmd.CreateParameter("SSN", adChar, adParamInput, 20)
    
    cmd.Parameters(0).value = cUserName
    
    rst.Open cmd, , adOpenStatic, adLockBatchOptimistic, adCmdText
    
    Set rs = rst
    
    GetPortfolioHierarchy = SUCCESS
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
    
    Exit Function
    
ErrorHandler:

    If Not rst Is Nothing Then
        Set rst = Nothing
    End If
    
    If Not cn Is Nothing Then
        Set cn = Nothing
    End If
    
    If Not cmd Is Nothing Then
        Set cmd = Nothing
    End If
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    sMsg = LogErrorStr("ICustomer.GetPortfolioHierarchy")

End Function

Public Function GetAccountsDetails(ByVal sSSN As String, ByRef Accounts As Variant, ByRef sMsg As Variant) As Long
    
    GetAccountsDetails = FAILED
    
    On Error GoTo ErrorHandler
    
    Dim cn As ADODB.Connection
    Dim cmd As ADODB.Command
    Dim rst As ADODB.Recordset
    
    Set cn = New ADODB.Connection
    Set cmd = New ADODB.Command
    Set rst = New ADODB.Recordset
    
    If sSSN = "" Then
        If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
        Exit Function
    End If
      
    cn.Open SHAPE_PROVIDER & GetDSN()
     
    rst.CursorLocation = adUseClient
    
    'This just gets accounts
    cmd.CommandText = "shape ( shape {select ad.acctNumber, ad.acctType, ad.cash, ad.cashDebit, ad.netWorth from account ad where ad.ssn = ? order by acctNumber } Append calc(cash - cashDebit) As AvailCash ) as rsAccountDetail"
    
    cmd.CommandType = adCmdText
    Set cmd.ActiveConnection = cn
    cmd.Parameters.Append cmd.CreateParameter("ssn", adChar, adParamInput, 20)
  
    cmd.Parameters(0).value = sSSN
    
    rst.Open cmd, , adOpenStatic, adLockBatchOptimistic, adCmdText
    
    GetAccountsDetails = SUCCESS
     
    Set Accounts = rst
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
    
    Exit Function
    
ErrorHandler:

    If Not rst Is Nothing Then
        Set rst = Nothing
    End If
    
    If Not cn Is Nothing Then
        Set cn = Nothing
    End If
    
    If Not cmd Is Nothing Then
        Set cmd = Nothing
    End If
     
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    sMsg = LogErrorStr("ICustomer.GetAccountHierarchy2")
    
End Function

Public Function GetAccounts(ByVal sSSN As String, ByRef Accounts As Variant, ByRef sMsg As Variant) As Long
                    
    GetAccounts = FAILED
   
    On Error GoTo ErrorHandler
    
    Dim cn As ADODB.Connection
    Dim rs As ADODB.Recordset
    Dim sSQL As String
    
    Set cn = New ADODB.Connection
    
    sSQL = "Select * from Account where ssn = '" & sSSN & "'"
    
    cn.Open GetDSN()
    
    Set rs = cn.Execute(sSQL)
    
    If Not rs.EOF Then
        Set Accounts = rs
        GetAccounts = SUCCESS
    Else
        GetAccounts = NO_RECORDS_FOUND
    End If
                   
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
    
    Exit Function
    
ErrorHandler:

    If Not rs Is Nothing Then
        Set rs = Nothing
    End If
    
    If Not cn Is Nothing Then
        Set cn = Nothing
    End If
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    sMsg = LogErrorStr("ICustomer.GetAccounts")
    
End Function

Public Function GetAlerts(ByVal sSSN As String, ByRef alerts As Variant, ByRef sMsg As Variant) As Long
         
    Dim oData As DataLayer
    Dim rs As Variant
    Dim sSQL As String
    Dim lNumRecs As Long
    
    GetAlerts = FAILED
     
    On Error GoTo ErrorHandler
    
    If sSSN = "" Then
        If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
        Exit Function
    End If
    
    Set oData = New HBInstitution.DataLayer
    
    sSQL = "Select * from Alert where ssn = '" & sSSN & "'"
    
    Set rs = oData.ExecSql(sSQL, PROVIDER, GetDSN(), True, True)

    If Not rs.EOF Then
        alerts = rs.GetRows
        GetAlerts = SUCCESS
    Else
        GetAlerts = NO_RECORDS_FOUND
    End If
    
    If rs.State = adStateOpen Then rs.Close
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
   
    Exit Function
    
ErrorHandler:

    If Not rs Is Nothing Then
        Set rs = Nothing
    End If
    
    If Not oData Is Nothing Then
        Set oData = Nothing
    End If
        
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    sMsg = LogErrorStr("ICustomer.GetAlerts")

End Function

Public Function GetNonAcknowledgedTrades(ByVal ssSSN As String, ByRef nakTrades As Variant, ByRef sMsg As Variant) As Long
              
    Dim oData As DataLayer
    Dim rs As Variant
    Dim sSQL As String
    
    GetNonAcknowledgedTrades = FAILED
     
    On Error GoTo ErrorHandler
    
    If ssSSN = "" Then
        Exit Function
    End If
    
    Set oData = New HBInstitution.DataLayer
    
    sSQL = "SELECT * FROM holding where ssn = '"
    sSQL = sSQL & ssSSN
    sSQL = sSQL & "' and acknowledged = " & NOT_ACKNOWLEDGED & " and ( action = " & BUY & " or action = " & SELL & " ) and orderStatus = " & SETTLED
    
    Set rs = oData.ExecSql(sSQL, PROVIDER, GetDSN(), True, True)

    If Not rs.EOF Then
        nakTrades = rs.GetRows
        GetNonAcknowledgedTrades = SUCCESS
        sMsg = "Found ICustomer.GetNonAcknowledgedTrades"
    Else
        GetNonAcknowledgedTrades = NO_RECORDS_FOUND
        sMsg = "Did Not Find ICustomer.GetNonAcknowledgedTrades"
    End If
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete

    Exit Function
    
ErrorHandler:

    If Not rs Is Nothing Then
        Set rs = Nothing
    End If
    
    If Not oData Is Nothing Then
        Set oData = Nothing
    End If

    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    sMsg = LogErrorStr("ICustomer.GetNonAcknowledgedTrades. " & sMsg & " SQL = " & sSQL)

End Function

Public Function GetHistoryHierarchy(ByVal sSSN As String, ByRef Accounts As Variant, ByRef sMsg As Variant) As Long
    
    GetHistoryHierarchy = FAILED
       
    On Error GoTo ErrorHandler
    
    Dim cn As ADODB.Connection
    Dim cmd As ADODB.Command
    Dim rst As ADODB.Recordset
    
    If sSSN = "" Then
        If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
        Exit Function
    End If
    
    Set cn = New ADODB.Connection
    Set cmd = New ADODB.Command
    Set rst = New ADODB.Recordset
    
    cn.Open SHAPE_PROVIDER & GetDSN()
    
    rst.StayInSync = False

    rst.CursorLocation = adUseClient
    
    cmd.CommandText = "shape {select ad.acctNumber, ad.acctType, ad.cash, ad.cashDebit, ad.netWorth from account ad where ad.ssn = ?} APPEND ({select * from holding where action <> " & HOLDING_SUMMARY & " } AS Holdings RELATE acctNumber TO acctNumber)"
    
    cmd.CommandType = adCmdText
    Set cmd.ActiveConnection = cn
    cmd.Parameters.Append cmd.CreateParameter("ssn", adChar, adParamInput, 20)
  
    cmd.Parameters(0).value = sSSN
    
    rst.Open cmd, , adOpenStatic, adLockBatchOptimistic, adCmdText
    
    GetHistoryHierarchy = SUCCESS
    
    Set Accounts = rst
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
    
    Exit Function
    
ErrorHandler:

    If Not rst Is Nothing Then
        Set rst = Nothing
    End If
    
    If Not cn Is Nothing Then
        Set cn = Nothing
    End If
    
    If Not cmd Is Nothing Then
        Set cmd = Nothing
    End If
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    sMsg = LogErrorStr("ICustomer.GetHistoryHierarchy")
    
End Function

Public Function CalcHolding(ByVal sAcctNum As String, ByRef Holdings As Variant, ByRef sMsg As Variant) As Long
    
    ' PURPOSE: When viewing current holdings, each holdings NetValue appears. This
    ' is calculated at the end of the previous day. In addition, current holding value
    ' is calculated as determined by the current holdings market value.
    
    CalcHolding = FAILED
        
    On Error GoTo ErrorHandler
      
    Dim rst As Variant
    Dim oAcct As HBInstitution.IAccount
    Dim oQuote As HBExchange.IQuote
    Dim rc As Long
    
    If Not GetObjectContext Is Nothing Then
        Set oAcct = GetObjectContext.CreateInstance("HBInstitution.IAccount")
        Set oQuote = GetObjectContext.CreateInstance("HBExchange.IQuote")
    Else
        Set oAcct = CreateObject("HBInstitution.IAccount")
        Set oQuote = CreateObject("HBExchange.IQuote")
    End If
    
    Dim I, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12
    
    Dim sSymbol As String
    Dim lastPrice As Double
        
    If sAcctNum = "" Then
        If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
        Exit Function
    End If
    
    ' Get Current quotes
    
    sMsg = "Calling GetHoldings"
    rc = oAcct.GetHoldings(sAcctNum, rst, sMsg)
    If rc = SUCCESS Then
        For I = 0 To UBound(rst, 2)
            sSymbol = rst(1, I)
        
            sMsg = sMsg & "Calling RetrieveEx with " & sSymbol
            rc = oQuote.RetrieveEx(sSymbol, a1, a2, a3, a4, lastPrice, a5, a6, a7, a8, a9, a10, a11, a12, sMsg)
            If rc = SUCCESS Then
                sMsg = sMsg & "Calling UpdateSummaryQuote"
                rc = oAcct.UpdateSummaryQuote(sAcctNum, sSymbol, lastPrice, sMsg)
            Else
                sMsg = sMsg & "Failed RetrieveEx "
                If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
                Exit Function
            End If
        Next
        CalcHolding = SUCCESS
    ElseIf rc = NO_RECORDS_FOUND Then
        CalcHolding = NO_RECORDS_FOUND
    Else
        sMsg = sMsg & "Failed getHoldings"
    End If
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
    
    Exit Function
    
ErrorHandler:

    If Not oAcct Is Nothing Then
        Set oAcct = Nothing
    End If
    
    If Not oQuote Is Nothing Then
        Set oQuote = Nothing
    End If
    
    If Not rst Is Nothing Then
        Set rst = Nothing
    End If
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    sMsg = LogErrorStr("ICustomer.CalcHolding " & sMsg)
 
End Function

Public Function GetHoldingHierarchy(ByVal sAcctNum As String, ByRef Holdings As Variant, ByRef sMsg As Variant) As Long
    
    GetHoldingHierarchy = FAILED
     
    On Error GoTo ErrorHandler
    
    Dim cn As ADODB.Connection
    Dim cmd As ADODB.Command
    Dim rst As ADODB.Recordset
        
    If sAcctNum = "" Then
        If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
        Exit Function
    End If
    
    Set cn = New ADODB.Connection
    Set cmd = New ADODB.Command
    Set rst = New ADODB.Recordset
   
    cn.Open SHAPE_PROVIDER & GetDSN()
    
    rst.CursorLocation = adUseClient
    
    cmd.CommandText = "shape ( shape {select hd.symbol, hd.quantity,  hd.value, hd.reconcileDate, hd.settledPrice from holding hd where hd.acctNumber = ? and action = " & HOLDING_SUMMARY & " and quantity > 0 order by symbol } Append calc(quantity * settledPrice) As CurrentValue ) as rsHoldingDetail"
    cmd.CommandType = adCmdText
    Set cmd.ActiveConnection = cn
    
    cmd.Parameters.Append cmd.CreateParameter("AccountNum", adChar, adParamInput, 20)
  
    cmd.Parameters(0).value = sAcctNum
    
    rst.Open cmd, , adOpenStatic, adLockBatchOptimistic, adCmdText
    
    If rst.RecordCount > 0 Then
        GetHoldingHierarchy = SUCCESS
    Else
       GetHoldingHierarchy = NO_RECORDS_FOUND
    End If
    
    Set Holdings = rst
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
    
    Exit Function
    
ErrorHandler:

    If Not rst Is Nothing Then
        Set rst = Nothing
    End If
    
    If Not cn Is Nothing Then
        Set cn = Nothing
    End If
    
    If Not cmd Is Nothing Then
        Set cmd = Nothing
    End If
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    sMsg = LogErrorStr("ICustomer.GetHoldingHierarchy")
    
End Function

Public Function GetCustomers(ByRef Customers As Variant, ByRef sMsg As Variant) As Long
    
    Dim oData As DataLayer
    Dim rs As Recordset
    Dim sSQL As String
    
    GetCustomers = FAILED
   
    On Error GoTo ErrorHandler
    
    Set oData = New HBInstitution.DataLayer
    
    sSQL = "SELECT ssn, firstName, middleName, lastName, type "
    sSQL = sSQL & "FROM customer"
    
    Set rs = oData.ExecSql(sSQL, PROVIDER, GetDSN(), True, True)
    
    Customers = rs.GetRows
    
    GetCustomers = SUCCESS
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
    
    Exit Function
    
ErrorHandler:

    If Not rs Is Nothing Then
        Set rs = Nothing
    End If
    
    If Not oData Is Nothing Then
        Set oData = Nothing
    End If
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    sMsg = LogErrorStr("ICustomer.GetCustomers. SQL = " & sSQL)

End Function

Public Function GetTotalNetWorth(ByVal sSSN As String, ByRef TotalValue As Variant, ByRef TotalCash As Variant, ByRef sMsg As Variant) As Long
    
    Dim cn As ADODB.Connection
    Dim cmd As ADODB.Command
    Dim rs As ADODB.Recordset
    Dim Accounts As Variant
    Dim dTotalValue As Currency
    Dim dTotalCash As Currency
    Dim oData As DataLayer
    Dim sSQL As String
    Dim I As Integer
    
    GetTotalNetWorth = FAILED
        
On Error GoTo ErrorHandler

    Set cn = New ADODB.Connection
    Set cmd = New ADODB.Command
   
    Set oData = New HBInstitution.DataLayer
    
    sSQL = "Select netWorth, cash, cashDebit from account where ssn = '" & sSSN & "'"
    
    Set rs = oData.ExecSql(sSQL, PROVIDER, GetDSN(), True)

    dTotalValue = 0
    dTotalCash = 0
    If Not rs.EOF Then
        Accounts = rs.GetRows
        For I = 0 To UBound(Accounts, 2)
            dTotalValue = Accounts(0, I) + dTotalValue
            dTotalCash = Accounts(1, I) + dTotalCash
        Next
        TotalValue = dTotalValue
        TotalCash = dTotalCash
        GetTotalNetWorth = SUCCESS
    Else
        GetTotalNetWorth = NO_RECORDS_FOUND
    End If
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
        
    Exit Function
    
ErrorHandler:
    
    If Not rs Is Nothing Then
        Set rs = Nothing
    End If
    
    If Not oData Is Nothing Then
        Set oData = Nothing
    End If
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    sMsg = LogErrorStr("ICustomer.GetTotalNetWorth. SQL = " & sSQL)

End Function

Public Function GetCustomerSum(ByRef Customers As Variant, ByRef sMsg As Variant) As Long
    
    GetCustomerSum = FAILED
      
    On Error GoTo ErrorHandler
    
    Dim cn As ADODB.Connection
    Dim rs As ADODB.Recordset
    Dim sSQL As String
    
    Set cn = New ADODB.Connection

    sSQL = "SELECT ssn, netWorth  "
    sSQL = sSQL & "FROM customer"
    
    cn.Open GetDSN()
    
    Set rs = cn.Execute(sSQL)
    
    If Not rs.EOF Then
        Set Customers = rs
        GetCustomerSum = SUCCESS
    Else
        GetCustomerSum = NO_RECORDS_FOUND
    End If
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete

    Exit Function
    
ErrorHandler:

    If Not rs Is Nothing Then
        Set rs = Nothing
    End If
    
    If Not cn Is Nothing Then
        Set cn = Nothing
    End If
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    sMsg = LogErrorStr("ICustomer.GetCustomerSum. SQL = " & sSQL)

End Function

Public Function GetCustomerInfoEx(ByVal sSSN As String, ByRef cusType As Variant, ByRef firstName As Variant, ByRef middleName As Variant, ByRef lastName As Variant, ByRef homePhone As Variant, ByRef workPhone As Variant, ByRef Email As Variant, ByRef streetAddress As Variant, ByRef City As Variant, ByRef State As Variant, ByRef Zip As Variant, ByRef permissions As Variant, ByRef sMsg As Variant) As Long
            
    ' Could Use IMDB Here. ToDo
                
    GetCustomerInfoEx = FAILED
    
    On Error GoTo ErrorHandler
  
    Dim cn As ADODB.Connection
    Dim rs As ADODB.Recordset
    
    Dim retval As Long
    
    Set cn = New ADODB.Connection
    Set rs = New ADODB.Recordset

    cn.PROVIDER = "MSIMDB"
    cn.ConnectionString = "data source=ERIKGUN"
    cn.Open
    
    rs.Source = "customer"
    rs.CursorLocation = adUseNone
    rs.ActiveConnection = cn
    rs.Open
    
    rs.Filter = "ssn = '" & CStr(sSSN) & "'"
        
    ' If we have data then return it
     If Not rs.EOF Then
        With rs
         
            cusType = !Type
            firstName = !firstName
            middleName = !middleName
            lastName = !lastName
            homePhone = !homePhone
            workPhone = !workPhone
            Email = !Email
            streetAddress = !streetAddress
            City = !City
            State = !State
            Zip = !Zip
            permissions = !permissions
    
        End With
        GetCustomerInfoEx = SUCCESS
    Else
        GetCustomerInfoEx = NO_RECORDS_FOUND
    End If
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
        
    Exit Function
    
ErrorHandler:

    If Not rs Is Nothing Then
        Set rs = Nothing
    End If
    
    If Not cn Is Nothing Then
        Set cn = Nothing
    End If
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    sMsg = LogErrorStr("ICustomer.GetCustomerInfoEx")
    
End Function

