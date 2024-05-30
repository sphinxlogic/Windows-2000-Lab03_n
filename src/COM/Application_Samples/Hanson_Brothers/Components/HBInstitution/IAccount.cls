VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 1  'NoTransaction
END
Attribute VB_Name = "IAccount"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Attribute VB_Ext_KEY = "RVB_UniqueId" ,"37367CF00399"
'/***********************************************************************************\
'*************************************************************************************
'*  COM+ Hanson Brothers SDK Sample
'*  Class IAccount (HBInstitution)
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



Public Function GetAccountNetWorth(ByVal sAcctNumber As String, ByRef cNetWorth As Variant, ByRef cCash As Variant, ByRef cCashDebit As Variant, ByRef sMsg As Variant) As Long
    
    GetAccountNetWorth = FAILED
    
    On Error GoTo ErrorHandler
    
    Dim oData As HBInstitution.DataLayer
    Dim sSQL As String
    Dim rs As ADODB.Recordset
  
    Set oData = New HBInstitution.DataLayer
        
    cNetWorth = 0
    cCash = 0
    cCashDebit = 0
    
    sSQL = "Select netWorth, cash, cashDebit from account where acctNumber = '" & sAcctNumber & "'"
    
    Set rs = oData.ExecSql(sSQL, PROVIDER, GetDSN(), True, False)
    
    If Not rs.EOF Then
        cNetWorth = rs("netWorth")
        cCash = rs("cash")
        cCashDebit = rs("cashDebit")
        GetAccountNetWorth = SUCCESS
    Else
         GetAccountNetWorth = NO_RECORDS_FOUND
    End If

    ' If we have a Context the SetComplete
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
        
    Exit Function
    
ErrorHandler:
    
    GetAccountNetWorth = FAILED
    
    If Not rs Is Nothing Then
        Set rs = Nothing
    End If
    
    If Not oData Is Nothing Then
        Set oData = Nothing
    End If
    
    ' if we have a Context then Abort
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
   
    sMsg = LogErrorStr("IAccount.GetAccountNetWorth. SQL = " & sSQL)
    
End Function

Public Function GetHoldings(ByVal sAcctNum As String, ByRef Holdings As Variant, ByRef sMsg As Variant) As Long
     
    GetHoldings = FAILED
    
    On Error GoTo ErrorHandler
                    
    ' Declare
    Dim oData As DataLayer
    Dim rs As Variant
    Dim sSQL As String
    
    ' Create ADO Objects
    Set oData = New HBInstitution.DataLayer
    
    sSQL = "Select acctNumber, symbol, quantity, value from holding where acctNumber = '" & sAcctNum & "' AND action = " & HOLDING_SUMMARY & " AND quantity > 0 "
 
    Set rs = oData.ExecSql(sSQL, _
                           PROVIDER, _
                           GetDSN(), _
                           True)
                                                              
                                                       
    If Not rs.EOF Then
        Holdings = rs.GetRows
        GetHoldings = SUCCESS
    Else
        GetHoldings = NO_RECORDS_FOUND
    End If
    
     ' If the Recordset is Open then Close It
    If rs.State = adStateOpen Then _
        rs.Close
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete

    Exit Function
    
ErrorHandler:
    
    If Not rs Is Nothing Then
        Set rs = Nothing
    End If
    
    If Not oData Is Nothing Then
        Set oData = Nothing
    End If
    
    GetHoldings = RECORD_READ_FAILED
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort

    sMsg = LogErrorStr("IAccount.GetHoldings. SQL = " & sSQL)
    
End Function


Public Function GetPendingHierarchy(ByVal sAcctNum As String, ByRef Holdings As Variant, ByRef sMsg As Variant) As Long
    
    ' On Client: Parse XML stream and extract any Holding records which have orderStatus = CONFIRMED, order by Confirmation Date
    
    GetPendingHierarchy = FAILED
    
    On Error GoTo ErrorHandler
    
    Dim cn As ADODB.Connection
    Dim cmd As ADODB.Command
    Dim rst As ADODB.Recordset
    
    Set cn = New ADODB.Connection
    Set cmd = New ADODB.Command
    Set rst = New ADODB.Recordset

    cn.Open SHAPE_PROVIDER & GetDSN()
    
    rst.CursorLocation = adUseClient
    
    cmd.CommandText = "shape ( shape {select hd.orderId, hd.symbol, hd.quantity, hd.confirmationDate, hd.limitPrice, hd.acctNumber from holding hd where hd.acctNumber = ? AND orderStatus = " & CONFIRMED & " order by hd.confirmationDate } ) as rsPendingDetail"
     
    cmd.CommandType = adCmdText
    Set cmd.ActiveConnection = cn
    
    cmd.Parameters.Append cmd.CreateParameter("AccountNum", adChar, adParamInput, 20)
  
    cmd.Parameters(0).value = sAcctNum
     
    rst.Open cmd, , adOpenStatic, adLockBatchOptimistic, adCmdText
    
    If rst.RecordCount > 0 Then
        GetPendingHierarchy = SUCCESS
    Else
       GetPendingHierarchy = NO_RECORDS_FOUND
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
    
    sMsg = LogErrorStr("IAccount.GetPendingHierarchy" & sMsg)
    
End Function


Public Function UpdateAcctCashDebit(ByVal sAcctNum As String, ByVal cCashDebit As Currency, ByRef sMsg As Variant) As Long

    UpdateAcctCashDebit = FAILED
    
    On Error GoTo ErrorHandler
                    
    ' Declare
    
    Dim oData As HBInstitution.DataLayer
    Dim sSQL As String
    Dim rs As ADODB.Recordset
    
    If cCashDebit = 0 Then
         UpdateAcctCashDebit = SUCCESS
         Exit Function
    End If
    
    Set oData = New HBInstitution.DataLayer
        
    sSQL = "UPDATE account "
    
    sSQL = sSQL & " SET "
    sSQL = sSQL & " cashDebit = " & cCashDebit
    sSQL = sSQL & " WHERE acctNumber = '" & sAcctNum & "'"
        
    Set rs = oData.ExecSql(sSQL, PROVIDER, GetDSN(), True, False)
        
    UpdateAcctCashDebit = SUCCESS
        
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
    
    sMsg = LogErrorStr("IAccount.UpdateAcctCashDebit. SQL = " & sSQL)
    
End Function

Public Function UpdateOrderStatus(ByVal sAcctNum As String, ByVal iOrderId As Integer, ByVal iConfirmNumber As Integer, ByVal iOrderStatus As Integer, ByVal cSettledPrice As Currency, ByVal cValue As Currency, ByRef sMsg As Variant) As Long

    UpdateOrderStatus = FAILED
    
    On Error GoTo ErrorHandler
    
    Dim oData As HBInstitution.DataLayer
    Dim sSQL As String
    Dim rs As ADODB.Recordset
    
    'LogInfo ("UpdateOrderStatus: sAcctNum=" & sAcctNum & ", OrderId=" & iOrderId & ", ConfirmNum=" & iConfirmNumber & ", OrderStatus=" & iOrderStatus)
    
    Set oData = New HBInstitution.DataLayer
    
    ' When an order is entered, HBInstitution creates a holding record indexed by
    ' lOrderId. Afterwards, HBInstitution sends the order to HBExchange. HBExchange receives
    ' the order and stores it in the pending table. HBExchange then
    ' reports back the Exchange confirmation number by placing a queued call to HBNotify.
    ' If the order is a market order, the order (may at the same time) also be filled (Settled) by HBExchange.
    ' Upon settlement, HBExchange notifies HBInstitution of the filled order and it's values - also by way of HBNotify.
    
    ' Given this scenario, It is quite possible that the filled order will beat the confirmed order. For settlement,
    ' this is considered reasonable. In this case, the market confirmed number and the
    ' market confirmed date and time will not be entered. It will be assumed that the
    ' lack of a market confirmation time is proof that the order confirmed and settled at the same time.
    
    sSQL = "UPDATE holding SET "
    
    If iOrderStatus = SETTLED Or iOrderStatus = SETTLED_ERROR Then
        ' Set to current Time
        sSQL = sSQL & " settlementDate = '" & FormatDateTime(Now(), vbShortDate) & "'"
        
        ' Set the price at which the order was settled
         sSQL = sSQL & ",  settledPrice = " & cSettledPrice
         
        ' Set the Value, which is calculated (shares * settledPrice)
        sSQL = sSQL & ", value = " & cValue
        
        ' Set the Market Confirmation Number if not set already by a preceeding ConfirmOrder
        sSQL = sSQL & ", confirmationNumber = " & iConfirmNumber
        
        ' Set Order Status
        sSQL = sSQL & ", orderStatus = " & iOrderStatus
        
        ' Calculate and update Commission
        sSQL = sSQL & ", commision = " & cValue * COMMISSION_PERCENTAGE
    
        sSQL = sSQL & " WHERE  orderId = " & iOrderId
        
    ElseIf iOrderStatus = RECONCILED Then
        sSQL = sSQL & " reconcileDate = '" & FormatDateTime(Now(), vbShortDate) & "'"
        sSQL = sSQL & ", orderStatus = " & RECONCILED
        
        sSQL = sSQL & " WHERE  confirmationNumber = " & iConfirmNumber
    Else
        sMsg = "Wrong Status for Updating Holding Record"
        Exit Function
    End If
    
    sSQL = sSQL & " AND acctNumber = '" & sAcctNum & "'"
    
    Set rs = oData.ExecSql(sSQL, PROVIDER, GetDSN(), True, False)
    
    ' FUTURE ToDO: Database Error checking should be addressed here by Win2000 RTM for
    ' non-committed FILLED notifications during high contention rates
    
    UpdateOrderStatus = SUCCESS
    
    sMsg = "IAccount.UpdateOrderStatus Confirmed"
    
Done:
     ' If the Recordset is Open then Close It
    If rs.State = adStateOpen Then _
        rs.Close
    
    ' The order has been entered successfully, we are happy
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
   
    Exit Function
    
ErrorHandler:

    If Not rs Is Nothing Then
        Set rs = Nothing
    End If
    
    If Not oData Is Nothing Then
        Set oData = Nothing
    End If
     
    UpdateOrderStatus = FAILED
    
    ' if we have a Context then Abort
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    sMsg = LogErrorStr("IAccount.UpdateOrderStatus. " & sMsg & " SQL = " & sSQL)

End Function

Public Function GetHistory(ByVal sAcctNum As String, ByRef History As Variant, ByRef sMsg As Variant) As Long

    GetHistory = FAILED
    
    On Error GoTo ErrorHandler
                    
    ' Declare
    Dim rs As ADODB.Recordset
    Dim sSQL As String
    Dim oData As DataLayer
    
    sSQL = "Select * from holding where acctNumber = '" & sAcctNum & "' AND action <> " & HOLDING_SUMMARY & " ORDER BY confirmationNumber DESC"
   
    On Error GoTo ErrorHandler
    
    Set oData = New HBInstitution.DataLayer
    
    Set rs = oData.ExecSql(sSQL, _
                           PROVIDER, _
                           GetDSN(), _
                           True)
    
    If Not rs.EOF Then
        Set History = rs
        GetHistory = SUCCESS
    Else
        GetHistory = NO_RECORDS_FOUND
    End If
    
     If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
    
    Exit Function
    
ErrorHandler:

    GetHistory = FAILED
    
    If Not rs Is Nothing Then
        Set rs = Nothing
    End If
    
    If Not oData Is Nothing Then
        Set oData = Nothing
    End If
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    sMsg = LogErrorStr("IAccount.GetHistory. SQL = " & sSQL)
    
End Function

Public Function ForceSettlement(ByVal confirmNumber, ByRef sMsg As Variant) As Long


    ' Force Settlement will use the current Quote Price for the symbol
     
    ForceSettlement = FAILED
    
    On Error GoTo ErrorHandler
                    
    ' Declare
    Dim oData As DataLayer
    Dim oQuote As HBExchange.IQuote
    Dim oAcct As HBInstitution.IAccount
    
    Dim rs As Variant
    Dim sSQL As String
    
    Dim QuoteTime As Date
    Dim LastTradeTime As Date
    Dim LastTradePrice As Currency
    Dim closeDate As Date
    
    Dim NetChange As Double
    Dim OpenPrice As Currency
    Dim ClosePrice As Currency
    Dim DailyHigh As Currency
    Dim DailyLow As Currency
    Dim askPrice As Currency
    Dim bidPrice As Currency
    Dim bidSize As Long
    Dim askSize As Long
    Dim rc As Long
    
    ' Create ADO Objects
    Set oData = New HBInstitution.DataLayer
    
    sSQL = "Select * from pendingTrades where orderId  = " & confirmNumber 'A.K.A. orderId
 
    Set rs = oData.ExecSql(sSQL, _
                           PROVIDER, _
                           GetDSN(), _
                           True)
                                                                                                                                                                        
    If Not rs.EOF Then
    
        Set oQuote = New HBExchange.IQuote
       
        rc = oQuote.RetrieveEx(rs("symbol"), QuoteTime, bidPrice, askPrice, LastTradeTime, LastTradePrice, NetChange, DailyHigh, DailyLow, askSize, bidSize, OpenPrice, ClosePrice, closeDate, sMsg)
    
        If rc <> SUCCESS Then
           ForceSettlement = FAILED
            If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
           Exit Function
        End If
    
        If Not GetObjectContext Is Nothing Then
            Set oAcct = GetObjectContext.CreateInstance("HBInstitution.IAccount")
        Else
             Set oAcct = CreateObject("HBInstitution.IAccount")
        End If
        
        If rs("action") = BUY Then
             
             rc = oAcct.UpdateOrderStatus(rs("acctNum"), rs("orderId"), rs("ConfirmationNumber"), SETTLED, askPrice, rs("quantity") * askPrice, sMsg)
        
        ElseIf rs("action") = SELL Then
              
             rc = oAcct.UpdateOrderStatus(rs("acctNum"), rs("orderId"), rs("ConfirmationNumber"), SETTLED, bidPrice, rs("quantity") * bidPrice, sMsg)
        
        Else
           sMsg = "Action " & rs("action") & " Not supported in Force Settlement"
           ForceSettlement = FAILED
           If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
           Exit Function
        End If
        
        If rc <> SUCCESS Then
            ForceSettlement = FAILED
            
            If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
            Exit Function
        End If
        ForceSettlement = SUCCESS
    Else
        ForceSettlement = NO_RECORDS_FOUND
    End If
    
    ' If the Recordset is Open then Close It
    If rs.State = adStateOpen Then _
        rs.Close
        
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
    
    Exit Function
    
ErrorHandler:

    If Not rs Is Nothing Then
        Set rs = Nothing
    End If
    
    If Not oData Is Nothing Then
        Set oData = Nothing
    End If
    
    If Not oAcct Is Nothing Then
        Set oAcct = Nothing
    End If
    
    If Not oQuote Is Nothing Then
        Set oQuote = Nothing
    End If
      
    ForceSettlement = RECORD_READ_FAILED
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    sMsg = LogErrorStr("IAccount.ForceSettlement." & sMsg)

End Function

Public Function UpdateAccountWorth(ByVal sAcctNum As String, ByVal cAcctCash As Currency, ByVal cNetWorth As Currency, ByRef sMsg As Variant) As Long

    Dim oData As DataLayer
    Dim rs As ADODB.Recordset
    Dim sSQL As String
   
    UpdateAccountWorth = FAILED

    On Error GoTo ErrorHandler
    
    Set oData = New HBInstitution.DataLayer
    
    sSQL = "UPDATE account SET "
    
    sSQL = sSQL & "  netWorth = " & cNetWorth
    sSQL = sSQL & ", cash = " & cAcctCash
    sSQL = sSQL & ", cashDebit = 0" ' Always set to zero after each reconciliation
    sSQL = sSQL & " WHERE acctNumber = '" & sAcctNum & "'"
    
    Set rs = oData.ExecSql(sSQL, PROVIDER, GetDSN(), True, False)
        
    UpdateAccountWorth = SUCCESS
    
    sMsg = "SettleOrder.UpdateAccountWorth Confirmed"
    
     ' If the Recordset is Open then Close It
    If rs.State = adStateOpen Then _
        rs.Close
        
    ' The order has been entered successfully, we are happy
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
            
    Exit Function
    
ErrorHandler:

    If Not rs Is Nothing Then
        Set rs = Nothing
    End If
    
    If Not oData Is Nothing Then
        Set oData = Nothing
    End If
    
    UpdateAccountWorth = FAILED
    
    ' if we have a Context then Abort
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    sMsg = LogErrorStr("IAccount.UpdateAccountWorth. SQL = " & sSQL)

End Function

Public Function UpdateSymbolSummary(ByVal sAcctNum As String, ByVal iConfirmNumber As Integer, ByVal sSymbol As String, ByVal cNewValue As Currency, ByVal iSummaryShares As Integer, ByRef sMsg As Variant) As Long

    Dim oData As DataLayer
    Dim rs As ADODB.Recordset
    Dim sSQL As String
     
    UpdateSymbolSummary = FAILED
    
    On Error GoTo ErrorHandler
    
    Set oData = New HBInstitution.DataLayer
    
    sSQL = "UPDATE holding"
    
    sSQL = sSQL & " SET "
    sSQL = sSQL & " reconcileDate = '" & FormatDateTime(Now(), vbShortDate) & "'"
    sSQL = sSQL & ", value = " & cNewValue
    sSQL = sSQL & ", quantity = " & iSummaryShares
    sSQL = sSQL & " "
    sSQL = sSQL & " WHERE  action = " & HOLDING_SUMMARY
    sSQL = sSQL & " AND symbol = '" & sSymbol & "'"
    sSQL = sSQL & " AND acctNumber = '" & sAcctNum & "'"
    
    Set rs = oData.ExecSql(sSQL, PROVIDER, GetDSN(), True, False)
      
    UpdateSymbolSummary = SUCCESS
    
    sMsg = "SettleOrder.UpdateSymbolSummary Confirmed"
    
    ' If the Recordset is Open then Close It
    If rs.State = adStateOpen Then _
        rs.Close
    
    ' The order has been entered successfully, we are happy
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
           
    Exit Function
    
ErrorHandler:

    If Not rs Is Nothing Then
        Set rs = Nothing
    End If
    
    If Not oData Is Nothing Then
        Set oData = Nothing
    End If
    
    UpdateSymbolSummary = FAILED
    
    ' if we have a Context then Abort
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    sMsg = LogErrorStr("IAccount.UpdateSymbolSummary. SQL = " & sSQL)
    
End Function

Public Function UpdateSummaryQuote(ByVal sAcctNum As String, ByVal sSymbol As String, ByVal dPrice As Double, ByRef sMsg As Variant) As Long

    Dim oData As DataLayer
    Dim rs As ADODB.Recordset
    Dim sSQL As String
     
    UpdateSummaryQuote = FAILED
    
    On Error GoTo ErrorHandler
    
    Set oData = New HBInstitution.DataLayer
    
    sSQL = "UPDATE holding"
    
    sSQL = sSQL & " SET "
    sSQL = sSQL & " settledPrice = " & dPrice
    sSQL = sSQL & " "
    sSQL = sSQL & " WHERE  action = " & HOLDING_SUMMARY
    sSQL = sSQL & " AND symbol = '" & sSymbol & "'"
    sSQL = sSQL & " AND acctNumber = '" & sAcctNum & "'"
    
    Set rs = oData.ExecSql(sSQL, PROVIDER, GetDSN(), True, False)
        
    UpdateSummaryQuote = SUCCESS
    
    sMsg = "SettleOrder.UpdateSummaryQuote Confirmed"
    
    ' If the Recordset is Open then Close It
    If rs.State = adStateOpen Then _
        rs.Close
        
    ' The order has been entered successfully, we are happy
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
    
    Exit Function
    
ErrorHandler:
    
    If Not rs Is Nothing Then
        Set rs = Nothing
    End If
    
    If Not oData Is Nothing Then
        Set oData = Nothing
    End If
    
    UpdateSummaryQuote = FAILED
    
    ' if we have a Context then Abort
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    sMsg = LogErrorStr("IAccount.UpdateSummaryQuote. SQL = " & sSQL)
  
End Function

Public Function GetSettledHoldings(ByVal sAcctNum As String, ByRef Holdings As Variant, ByRef sMsg As Variant) As Long
            
    Dim cn As ADODB.Connection
    Dim rs As ADODB.Recordset
    Dim sSQL As String
    
    GetSettledHoldings = FAILED
    
    On Error GoTo ErrorHandler
    
    Set cn = New ADODB.Connection
    
    cn.Open GetDSN()
    
    sSQL = "Select * from holding where acctNumber = '" & sAcctNum & "' AND orderStatus = " & SETTLED & " AND ( action = " & BUY & " OR action = " & SELL & ")"
    
    Set rs = cn.Execute(sSQL)
    
    If Not rs.EOF Then
       Set Holdings = rs
       GetSettledHoldings = SUCCESS
    Else
        GetSettledHoldings = NO_RECORDS_FOUND
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
    
    sMsg = LogErrorStr("IAccount.GetSettledHoldings. SQL = " & sSQL)

End Function

Public Function GetSymbolSummary(ByVal sAcctNum As String, ByVal sSymbol As String, ByRef Holdings As Variant, ByRef sMsg As Variant) As Long
            
    GetSymbolSummary = FAILED
    
    On Error GoTo ErrorHandler
    
    Dim cn As ADODB.Connection
    Dim rs As ADODB.Recordset
    Dim sSQL As String
    
    Set cn = New ADODB.Connection
    
    cn.Open GetDSN()
    
    If sSymbol = "ALL" Then
        sSQL = "Select * from holding where acctNumber = '" & sAcctNum & "' AND action = " & HOLDING_SUMMARY
    Else
        sSQL = "Select * from holding where acctNumber = '" & sAcctNum & "' AND symbol = '" & sSymbol & "' AND action = " & HOLDING_SUMMARY
    End If
    
    Set rs = cn.Execute(sSQL)
    
    If Not rs.EOF Then
       Set Holdings = rs
        GetSymbolSummary = SUCCESS
    Else
        GetSymbolSummary = NO_RECORDS_FOUND
    End If
    
     If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
    
Done:
    Exit Function
    
ErrorHandler:

    If Not rs Is Nothing Then
        Set rs = Nothing
    End If
    
    If Not cn Is Nothing Then
        Set cn = Nothing
    End If
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    sMsg = LogErrorStr("IAccount.GetSymbolSummary. SQL = " & sSQL)
     
End Function

Public Function Reconcile(ByRef sMsg As Variant) As Long

    ' Future Change: The Commision costs are to be calculated in Reconciliation
    
    ' NOTE: Time was not spent on this function to make it more efficient considering it
    ' is (EOD) batch oriented in this scenario
    
    Dim rc As Long
    
    Dim oCust As HBInstitution.ICustomer
    Dim oAcct As HBInstitution.IAccount
    Dim oQuote As HBExchange.IQuote
    
    Dim SettledOrders As ADODB.Recordset
    Dim Summary As ADODB.Recordset
    Dim sSymbol2 As String
    Dim sSSN As String
    Dim Accounts As Variant
    Dim Customers As Variant
    Dim cAcctCash As Currency
    Dim sSymbol As String
    
    Dim QuoteTime As Variant
    Dim bidPrice As Variant
    Dim askPrice As Variant
    Dim LastTradeTime As Variant
    Dim LastTradePrice As Variant
    Dim NetChange As Variant
    Dim DailyHigh As Variant
    Dim DailyLow As Variant
    Dim askSize As Variant
    Dim bidSize As Variant
    Dim OpenPrice As Variant
    Dim ClosePrice As Variant
    Dim closeDate As Variant
    
    Dim cTotalNetWorth As Currency
    Dim cCommission As Currency
    
    Dim cCustTotalNet As Currency
    Dim sAcctNum As String
    
    Reconcile = FAILED
    
    On Error GoTo ErrorHandler
        
    'Get All Settled orders for this account
    
    If Not GetObjectContext Is Nothing Then
        Set oCust = GetObjectContext.CreateInstance("HBInstitution.ICustomer")
        Set oAcct = GetObjectContext.CreateInstance("HBInstitution.IAccount")
    Else
        Set oCust = CreateObject("HBInstitution.ICustomer")
        Set oAcct = CreateObject("HBInstitution.IAccount")
    End If
    
    Set oQuote = New HBExchange.IQuote
    
    rc = oCust.GetCustomerSum(Customers, sMsg)

    If rc = SUCCESS Then
        While (Not Customers.EOF)
            
             sSSN = Customers("ssn")
             cCustTotalNet = Customers("netWorth") + 0
             
             rc = oCust.GetAccounts(sSSN, Accounts, sMsg)
            
             cCustTotalNet = 0
             If rc = SUCCESS Then
                 While (Not Accounts.EOF)
                
                     sAcctNum = Accounts("acctNumber") + ""
                     
                     ' Get the existing cash in the account
                     cAcctCash = Accounts("cash") + 0
                     
                     ' Get the existing netWorth in the account
                     cTotalNetWorth = Accounts("netWorth") + 0
                     
                     rc = oAcct.GetSettledHoldings(sAcctNum, SettledOrders, sMsg)
                     If rc <> SUCCESS Then
                         If rc = NO_RECORDS_FOUND Then
                                   sMsg = "No Settled Orders to Process for " & sAcctNum
                         Else
                                   sMsg = "ERROR: " & sMsg
                                   If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
                                   Exit Function
                         End If
                      
                     Else
                         
                     While (Not SettledOrders.EOF)
                         ' Determine if a Reconciled ("Summary") record exists for this
                         ' Symbol in this account
                         sSymbol2 = SettledOrders("symbol")
GET_SYMBOL:
                         rc = oAcct.GetSymbolSummary(sAcctNum, sSymbol2, Summary, sMsg)
                         If rc <> SUCCESS Then
                             If rc = NO_RECORDS_FOUND Then
                                 ' Create Summary Record
                                 rc = oAcct.CreateSymbolSummary(sSSN, sAcctNum, sSymbol2, sMsg)
                                 If rc <> SUCCESS Then
                                    sMsg = "ERROR: Unable to Create Summary for " & Trim(sSymbol2) & ", Acct = " & Trim(sAcctNum) & " in holding table"
                                    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
                                    Exit Function
                                 End If
                                 GoTo GET_SYMBOL
                             Else
                                 sMsg = "ERROR: " & sMsg
                                 If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
                                 Exit Function
                             End If
                         Else
                             ' Should Have One Summary Record
                             
                             Dim cSummaryValue As Currency
                             Dim cOrderValue As Currency
                             Dim iSummaryShares As Long
                             Dim iQuantity As Long
                             Dim iAction As Long
                             Dim cCash As Currency
                             Dim iConfirmNumber As Long
                             
                    
                             ' Add up All the Share Values (value = shares * settled Price)
                             cOrderValue = SettledOrders("value") + 0
                             
                             ' Get the debit/credit price of the trade
                             cCash = SettledOrders("settledPrice") + 0
                         
                             
                             iSummaryShares = Summary("quantity") + 0
                             
                             'iQuantity = total number of shares for a symbol owned
                             iQuantity = SettledOrders("quantity") + 0
                             
                             ' Buy or Sell
                             iAction = SettledOrders("action")
                             
                             ' Confirmation Number to update the order in holding table
                            iConfirmNumber = SettledOrders("confirmationNumber") + 0
                            
                            ' cCommission = Commissions per share * shares
                            cCommission = SettledOrders("commision")
                             
                             ' Get The current Quote (The quote should be fixed since
                             ' reconciliation would happen after market hours
                             
                             rc = oQuote.RetrieveEx(sSymbol2, QuoteTime, bidPrice, askPrice, LastTradeTime, LastTradePrice, NetChange, DailyHigh, DailyLow, askSize, bidSize, OpenPrice, ClosePrice, closeDate, sMsg)
    
                             If rc <> SUCCESS Then
                                 If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
                                Exit Function
                             End If
                             
                             If iAction = BUY Then
                             
                                ' Calculate the cost of this purchase
                                 cOrderValue = cOrderValue + cCommission
                                 
                                 ' decrement the cash in the account
                                 cAcctCash = cAcctCash - cOrderValue
                                 
                                 ' Add to the holding (summary) the # shares purchased
                                 iSummaryShares = iSummaryShares + iQuantity
                                 
                             ElseIf iAction = SELL Then
                                
                                 ' Calculate the value of this Sell
                                 cOrderValue = cOrderValue - cCommission
                             
                                 ' Add to cash in the account
                                 cAcctCash = cAcctCash + cOrderValue
                                 
                                 ' Subtract from holding (summary) the # shares sold
                                 iSummaryShares = iSummaryShares - iQuantity
                                 
                             Else
                                 sMsg = "Got wrong kind of order here. Symbol = " & sSymbol2
                                 If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
                                 Exit Function
                             End If
                             
                             ' Re-Calculate the holding networth
                             cSummaryValue = iSummaryShares * cCash
                                 
                             ' These should two calls should be transacted together
                             ' Both should work or fail
                             
                             rc = oAcct.UpdateOrderStatus(sAcctNum, 0, iConfirmNumber, RECONCILED, cCash, cOrderValue, sMsg)
                             rc = oAcct.UpdateSymbolSummary(sAcctNum, iConfirmNumber, sSymbol2, cSummaryValue, iSummaryShares, sMsg)
                             
                             If rc <> SUCCESS Then
                                 sMsg = "ERROR: " & sMsg
                                  If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
                                 Exit Function
                             End If
                 
                         End If
                         SettledOrders.MoveNext
                     Wend
                     ' Update Account Worth
                      
                    ' All Settled Orders Have been rolled up for each symbol
                    ' Now Add up all summaries for each Account
                    
                    rc = oAcct.GetSymbolSummary(sAcctNum, "ALL", Summary, sMsg)
                    If rc = SUCCESS Then
                    
                        cTotalNetWorth = 0
                        While (Not Summary.EOF)
                            ' cSummaryValue = total value of the same symbol owned (e.g., 100 DELL + 200 DELL = 300 total)
                            cSummaryValue = Summary("value") + 0
                            cTotalNetWorth = cTotalNetWorth + cSummaryValue
                            Summary.MoveNext
                        Wend
                             
                         rc = oAcct.UpdateAccountWorth(sAcctNum, cAcctCash, cTotalNetWorth, sMsg)
                         If rc <> SUCCESS Then
                            sMsg = "ERROR: " & sMsg
                             If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
                            Exit Function
                         End If
                         
                         ' Set The cashDebit back to zero
                         rc = oAcct.UpdateAcctCashDebit(sAcctNum, 0, sMsg)
                         If rc <> SUCCESS Then
                            sMsg = "ERROR: " & sMsg
                             If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
                            Exit Function
                         End If
                    End If
                End If
                Accounts.MoveNext
                Wend
                'Next  Account
         Else
             sMsg = "No Accounts For " & sSSN
         End If
             
         Customers.MoveNext
         Wend
        'Next Customer
    Else
        sMsg = "Error: No Customer"
         If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
        Exit Function
    End If
    
    Reconcile = SUCCESS
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
    
    Exit Function
    
ErrorHandler:

    If Not oCust Is Nothing Then
        Set oCust = Nothing
    End If
    
    If Not oQuote Is Nothing Then
        Set oQuote = Nothing
    End If
    
    If Not oAcct Is Nothing Then
        Set oAcct = Nothing
    End If
     
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    sMsg = LogErrorStr("IAccount.Reconcile. " & sMsg)

End Function

Public Function CreateSymbolSummary(ByVal sSSN As String, ByVal sAcctNum As String, ByVal sSymbol As String, ByRef sMsg As Variant) As Long

    Dim oData As DataLayer
    Dim rs As ADODB.Recordset
    Dim sSQL As String
    
   CreateSymbolSummary = FAILED
    
    On Error GoTo ErrorHandler
    
    Set oData = New HBInstitution.DataLayer
    
    sSQL = "INSERT INTO holding ("
    sSQL = sSQL & "acctNumber, tradeType, symbol,quantity, confirmationDate,commision"
    sSQL = sSQL & ",check_number,value,confirmationNumber,orderStatus,acknowledged"
    sSQL = sSQL & ",settlementDate,reconcileDate,action,limitPrice,ssn,settledPrice,submissionDate"
    sSQL = sSQL & ") "
    sSQL = sSQL & " VALUES ( '" & sAcctNum & "'"
    sSQL = sSQL & ", " & 0
    sSQL = sSQL & ", '" & sSymbol & "'"
    sSQL = sSQL & ", " & 0
    sSQL = sSQL & ", 0"  ' NULL
    sSQL = sSQL & ", " & 0
    sSQL = sSQL & ", " & 0
    sSQL = sSQL & ", " & 0
    sSQL = sSQL & ", " & 0
    sSQL = sSQL & ", " & UNCONFIRMED
    sSQL = sSQL & ", " & NOT_ACKNOWLEDGED
    sSQL = sSQL & ", 0" ' NULL
    sSQL = sSQL & ", '" & FormatDateTime(Now(), vbShortDate) & "'"
    sSQL = sSQL & ", " & HOLDING_SUMMARY  ' action
    sSQL = sSQL & ", " & 0
    sSQL = sSQL & ", '" & sSSN & "'"
    sSQL = sSQL & ", 0 "
    sSQL = sSQL & ", 0 "  ' NULL submission Date
    sSQL = sSQL & ")"
    
    Set rs = oData.ExecSql(sSQL, PROVIDER, GetDSN(), True, False)
    
    If Not rs Is Nothing Then
            CreateSymbolSummary = SUCCESS
    End If
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
    
    Exit Function
    
ErrorHandler:
    
    If Not oData Is Nothing Then
        Set oData = Nothing
    End If
    
    If Not rs Is Nothing Then
        Set rs = Nothing
    End If
      
    CreateSymbolSummary = FAILED
     
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    sMsg = LogErrorStr("IAccount.CreateSymbolSummary. SQL = " & sSQL)

End Function

Public Function GetHoldingSummary(ByVal sAcctNum As String, ByVal sSymbol As String, ByRef quantity As Variant, ByRef commision As Variant, ByRef value As Variant, ByRef settlementDate As Variant, ByRef ssn As Variant, ByRef sMsg As Variant) As Long
    
    GetHoldingSummary = FAILED
    On Error GoTo ErrorHandler
                    
    ' Declare
    Dim oData As DataLayer
    Dim rs As ADODB.Recordset
    Dim sSQL As String
    
    ' Create ADO Objects
    Set oData = New HBInstitution.DataLayer
    
    ' For Holdings, just get Buy orders that have been reconciled
    sSQL = "Select * from holding where acctNumber = '" & sAcctNum & "' AND symbol = '" & sSymbol & "' AND action = " & HOLDING_SUMMARY
    
    Set rs = oData.ExecSql(sSQL, _
                           PROVIDER, _
                           GetDSN(), _
                           True, False)
                                                              
    If Not rs.EOF Then
        'With rs
            quantity = rs("quantity")
            commision = rs("commision")
            value = rs("value")
            ssn = rs("ssn")
        'End With
       GetHoldingSummary = SUCCESS
                            
    Else
       GetHoldingSummary = NO_RECORDS_FOUND
    End If
    
    ' If the Recordset is Open then Close It
    If rs.State = adStateOpen Then _
        rs.Close
        
    ' If we have a Context the SetComplete
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
        
    Exit Function
    
ErrorHandler:

    If Not oData Is Nothing Then
        Set oData = Nothing
    End If
    
    If Not rs Is Nothing Then
        Set rs = Nothing
    End If
    
    GetHoldingSummary = RECORD_READ_FAILED
    
    ' if we have a Context then Abort
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    sMsg = LogErrorStr("IAccount.GetHoldingSummary. SQL = " & sSQL)

End Function

Public Function ConfirmOrder(ByVal lOrderId As Long, ByVal lConfirmNumber As Long, ByRef sMsg As Variant) As Long

    ConfirmOrder = FAILED
    
    Dim oData As HBInstitution.DataLayer
    Dim sSQLU As String
    Dim rs As ADODB.Recordset
    
    'LogInfo ("ConfirmOrder: OrderId=" & lOrderId & ", ConfirmNum=" & lConfirmNumber)
    
    Set oData = New HBInstitution.DataLayer
    
    ' Setup the Update SQL statement
    sSQLU = "UPDATE holding SET "
    sSQLU = sSQLU & " confirmationDate = '" & FormatDateTime(Now(), vbGeneralDate) & "'"
    sSQLU = sSQLU & ",  confirmationNumber = " & lConfirmNumber
    sSQLU = sSQLU & ", orderStatus = " & CONFIRMED
    sSQLU = sSQLU & " WHERE  orderId = " & lOrderId
    sSQLU = sSQLU & " AND orderStatus = " & ICONFIRMED
    
    ' NOTE: When an order is entered, HBInstitution creates a new holding record indexed by
    ' lOrderId. HBInstitution then sends the order to HBExchange. HBExchange receives
    ' the order and stores it in the pending table
    ' and reports back the Exchange confirmation number by placing a queued call to HBNotify
    ' which calls (synchronously) this function. Meanwhile, if the order is a market order,
    ' the order may be also be filled (Settled) by HBExchange. Upon settlement, HBExchange notifies
    ' HBInstitution of the filled order and it's values - also by way of HBNotify. It
    ' is quite possible that the filled order will beat the confirmed order.
    
    ' Locking is pessimistic and Dynamic. There is a tradeoff between performance and
    ' expected 'dirty writes' (i.e., the record is updated to SETTLED - by UpdateOrderStatus -
    ' before this UPDATE SQL is commited, but after this UPDATE SQL WHERE clause has been determined)
    
    ' If Serialized (i.e., queued disabled in the settings of HBTradeStation)
    ' you will receive a timeout on the next line. This is due to
    ' HBInstitution.IOrder.Execute transacting in the same record being locked (even though the record set is tried to be closed),
    
    ' This is left as a serialization problem and was left as an example
    
    Set rs = oData.ExecSql(sSQLU, PROVIDER, GetDSN(), True, False)
    
    ' Future Work: check status of rs
    
    ConfirmOrder = SUCCESS
    
    sMsg = "IAccount.ConfirmOrder Successful"

Done:

    ' If the Recordset is Open then Close It
    If rs.State = adStateOpen Then _
        rs.Close
    
    ' The order has been updated successfully, we are happy
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
           
    Exit Function
    
ErrorHandler:

    If Not oData Is Nothing Then
        Set oData = Nothing
    End If
    
    If Not rs Is Nothing Then
        Set rs = Nothing
    End If
     
    ConfirmOrder = FAILED
    
    ' if we have a Context then Abort
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    sMsg = LogErrorStr("IAccount.ConfirmOrder. SQLU = " & sSQLU)

End Function

Public Function InitTestData(ByVal flag As Integer, ByVal dDelta As Double, ByRef sMsg As Variant, Optional iLoops As Integer = 400, Optional sym_len As Long = 0) As Long

    ' Generate some fictitious data.
    
    Dim cn As ADODB.Connection
    Dim rs As ADODB.Recordset
    Dim sSQL As String
    Dim ret As Long
    
    InitTestData = FAILED
    
   
On Error GoTo ErrorHandler
    
    Set cn = New ADODB.Connection
    
    cn.Open GetDSN()
    
    If dDelta < 0 Then
        dDelta = 1
    End If
    If dDelta > 10 Then
        dDelta = 10
    End If
    
    ' Delete any Pending Orders
    sSQL = "DELETE pendingTrades"
    Set rs = cn.Execute(sSQL)
    sMsg = "DELETE of Pending Trades Records OK"
    
    ' Delete any holding records assoc with ssn
    sSQL = "DELETE holding"
    Set rs = cn.Execute(sSQL)
    sMsg = "DELETE of holding Records OK"
    
    ' Delete all tracking records
    sSQL = "DELETE tracking"
    Set rs = cn.Execute(sSQL)
    sMsg = "DELETE of All tracking Records OK"
    
    If flag = INIT_ORDERS_ONLY Then
        InitTestData = SUCCESS
        GoTo Done
    End If
        
    If flag = INIT_ALL Or flag = INIT_CUSTOMER Then
        
        If sym_len < 0 Or sym_len >= 32000 Then
            sMsg = "You can only have 1 to 32,000 Accounts!"
            InitTestData = FAILED
            GoTo Done
        End If
            
        ' Delete the Customer Info if Any
        sSQL = "DELETE customer"
        Set rs = cn.Execute(sSQL)
        sMsg = "DELETE of Customer Records OK"
            
        ' Delete the Account Info if Any
        sSQL = "DELETE account"
        Set rs = cn.Execute(sSQL)
        sMsg = "DELETE of Account Records OK"
    
        ' Declarations for news table
        Dim n_timeStamp As Date
        Dim n_headline As String
        Dim n_symbol As String
        Dim n_news_url As String
        Dim n_news_test As String
        Dim n_newsID As Long
        
        Dim I As Long
        
        n_timeStamp = vbNull
        n_headline = "NEWS HEADLINE"
        n_symbol = "AAA"
        n_news_url = "NEWS_URL"
        n_news_test = "THIS IS THE NEWS BODY"
        n_newsID = 1
        
        If flag = INIT_CUSTOMER And sym_len = 0 Then
        
            Const CUSTOMER_NUM = 5
            Const ACCOUNT_NUM = 5  ' MAX number of accounts possible
            
          'Declarations for the account Table
            Dim a_acctNumber(CUSTOMER_NUM, ACCOUNT_NUM) As String
            Dim a_acctType(CUSTOMER_NUM, ACCOUNT_NUM) As Long
            Dim a_portFolioId(CUSTOMER_NUM, ACCOUNT_NUM) As Long
            Dim a_taxReportingMethod(CUSTOMER_NUM, ACCOUNT_NUM) As Long
            Dim a_tradingLevel(CUSTOMER_NUM, ACCOUNT_NUM) As Long
            Dim a_serviceLevel(CUSTOMER_NUM, ACCOUNT_NUM) As Long
            Dim a_stateCode(CUSTOMER_NUM, ACCOUNT_NUM) As String
            Dim a_netWorth(CUSTOMER_NUM, ACCOUNT_NUM) As Double
            Dim a_cashDebit(CUSTOMER_NUM, ACCOUNT_NUM) As Double
            Dim a_cash(CUSTOMER_NUM, ACCOUNT_NUM) As Double
            
            Dim a_accts(CUSTOMER_NUM) As Integer
            
            ' ERIK Account Info
            a_accts(0) = 2 ' Number of accounts
            
            a_acctNumber(0, 0) = "PLATINUM_1" ' MUST BE 10 0r UNDER CHARACTERS
            a_acctType(0, 0) = 1
            a_portFolioId(0, 0) = 0
            a_taxReportingMethod(0, 0) = 0
            a_tradingLevel(0, 0) = 1
            a_serviceLevel(0, 0) = 1
            a_stateCode(0, 0) = "WA"
            a_netWorth(0, 0) = 0
            a_cashDebit(0, 0) = 0
            a_cash(0, 0) = 198500
          
            a_acctNumber(0, 1) = "GOLD_1"
            a_acctType(0, 1) = 2
            a_portFolioId(0, 1) = 0
            a_taxReportingMethod(0, 1) = 0
            a_tradingLevel(0, 1) = 1
            a_serviceLevel(0, 1) = 1
            a_stateCode(0, 1) = "WA"
            a_netWorth(0, 1) = 0
            a_cashDebit(0, 1) = 0
            a_cash(0, 1) = 134000
            
            ' ROSS Account Info
            a_accts(1) = 3 ' Number of accounts
            
            a_acctNumber(1, 0) = "GOLD_2"
            a_acctType(1, 0) = 2
            a_portFolioId(1, 0) = 0
            a_taxReportingMethod(1, 0) = 1
            a_tradingLevel(1, 0) = 2
            a_serviceLevel(1, 0) = 1
            a_stateCode(1, 0) = "WI"
            a_netWorth(1, 0) = 0
            a_cashDebit(1, 0) = 0
            a_cash(1, 0) = 15000
            
            a_acctNumber(1, 1) = "SILVER_2"
            a_acctType(1, 1) = 3
            a_portFolioId(1, 1) = 0
            a_taxReportingMethod(1, 1) = 1
            a_tradingLevel(1, 1) = 2
            a_serviceLevel(1, 1) = 1
            a_stateCode(1, 1) = "WI"
            a_netWorth(1, 1) = 0
            a_cashDebit(1, 1) = 0
            a_cash(1, 1) = 10000
            
            a_acctNumber(1, 2) = "RETIRE_2"
            a_acctType(1, 2) = 6
            a_portFolioId(1, 2) = 0
            a_taxReportingMethod(1, 2) = 5
            a_tradingLevel(1, 2) = 1
            a_serviceLevel(1, 2) = 1
            a_stateCode(1, 2) = "WI"
            a_netWorth(1, 2) = 0
            a_cashDebit(1, 2) = 0
            a_cash(1, 2) = 12000
            
            ' John Doe's 'TEST' Account Info
            
            a_accts(2) = 2 ' Number of accounts
            
            a_acctNumber(2, 0) = "TIN_3"
            a_acctType(2, 0) = 4
            a_portFolioId(2, 0) = 0
            a_taxReportingMethod(2, 0) = 1
            a_tradingLevel(2, 0) = 2
            a_serviceLevel(2, 0) = 1
            a_stateCode(2, 0) = "UK"
            a_netWorth(2, 0) = 0
            a_cashDebit(2, 0) = 0
            a_cash(2, 0) = 10000000#
            
            a_acctNumber(2, 1) = "ROCK_3"
            a_acctType(2, 1) = 5
            a_portFolioId(2, 1) = 0
            a_taxReportingMethod(1, 1) = 2
            a_tradingLevel(2, 1) = 0
            a_serviceLevel(2, 1) = 1
            a_stateCode(2, 1) = "UK"
            a_netWorth(2, 1) = 0
            a_cashDebit(2, 1) = 0
            a_cash(2, 1) = 10000000#
            
            ' John's Account Info
            a_accts(3) = 1 ' Number of accounts
            
            a_acctNumber(3, 0) = "GOLD_4"
            a_acctType(3, 0) = 1
            a_portFolioId(3, 0) = 0
            a_taxReportingMethod(3, 0) = 0
            a_tradingLevel(3, 0) = 2
            a_serviceLevel(3, 0) = 1
            a_stateCode(3, 0) = "NC"
            a_netWorth(3, 0) = 0
            a_cashDebit(3, 0) = 0
            a_cash(3, 0) = 1185.5
            
            ' Kev's Account Info
            a_accts(4) = 2 ' Number of accounts
            
            a_acctNumber(4, 0) = "PLATINUM_2"
            a_acctType(4, 0) = 4
            a_portFolioId(4, 0) = 0
            a_taxReportingMethod(4, 0) = 1
            a_tradingLevel(4, 0) = 2
            a_serviceLevel(4, 0) = 1
            a_stateCode(4, 0) = "UK"
            a_netWorth(4, 0) = 0
            a_cashDebit(4, 0) = 0
            a_cash(4, 0) = 35000#
            
            a_acctNumber(4, 1) = "GOLD_5"
            a_acctType(4, 1) = 5
            a_portFolioId(4, 1) = 0
            a_taxReportingMethod(1, 1) = 2
            a_tradingLevel(4, 1) = 0
            a_serviceLevel(4, 1) = 1
            a_stateCode(4, 1) = "UK"
            a_netWorth(4, 1) = 0
            a_cashDebit(4, 1) = 150.15
            a_cash(4, 1) = 29000#
            
            'Declarations for the customer Table
            Dim c_ssn(CUSTOMER_NUM) As String
            Dim c_type(CUSTOMER_NUM) As Long
            Dim c_firstName(CUSTOMER_NUM) As String
            Dim c_lastName(CUSTOMER_NUM) As String
            Dim c_middleName(CUSTOMER_NUM) As String
            Dim c_homePhone(CUSTOMER_NUM) As String
            Dim c_workPhone(CUSTOMER_NUM) As String
            Dim c_email(CUSTOMER_NUM) As String
            Dim c_streetAddress(CUSTOMER_NUM) As String
            Dim c_city(CUSTOMER_NUM) As String
            Dim c_state(CUSTOMER_NUM) As String
            Dim c_zip(CUSTOMER_NUM) As String
            Dim c_permissions(CUSTOMER_NUM) As Long
            Dim c_pin(CUSTOMER_NUM) As String
            Dim c_netWorth(CUSTOMER_NUM) As Double
            
            ' Erik Customer Info
            c_ssn(0) = "123456789"
            c_type(0) = 1
            c_firstName(0) = "Erik"
            c_lastName(0) = "Gunvaldson"
            c_middleName(0) = "P"
            c_homePhone(0) = "555-1212"
            c_workPhone(0) = "(425)703-7657"
            c_email(0) = "MS_erikgun@hotmail.com"
            c_streetAddress(0) = "1 Microsoft Way"
            c_city(0) = "Redmond"
            c_state(0) = "WA"
            c_zip(0) = "98007"
            c_permissions(0) = 1
            c_pin(0) = "111111"
            c_netWorth(0) = 0
        
            ' Ross Customer Info
            c_ssn(1) = "234567890"
            c_type(1) = 2
            c_firstName(1) = "Ross"
            c_lastName(1) = "Heise"
            c_middleName(1) = "K"
            c_homePhone(1) = "555-1212"
            c_workPhone(1) = "(425)704-3336"
            c_email(1) = "MS_rosshe@hotmail.com"
            c_streetAddress(1) = "1 Microsoft Way"
            c_city(1) = "Redmond"
            c_state(1) = "WA"
            c_zip(1) = "98007"
            c_permissions(1) = 1
            c_pin(1) = "111111"
            c_netWorth(1) = 0
            
            ' John Doe Customer Info
            c_ssn(2) = "345678901"
            c_type(2) = 3
            c_firstName(2) = "John"
            c_lastName(2) = "Doe"
            c_middleName(2) = ""
            c_homePhone(2) = "555-1212"
            c_workPhone(2) = "(425)936-2841"
            c_email(2) = "MS_JDoe@hotmail.com"
            c_streetAddress(2) = "1 Microsoft Way"
            c_city(2) = "Redmond"
            c_state(2) = "WA"
            c_zip(2) = "98007"
            c_permissions(2) = 1
            c_pin(2) = "111111"
            c_netWorth(2) = 0
            
             ' John's Customer Info
            c_ssn(3) = "456789012"
            c_type(3) = 2
            c_firstName(3) = "John"
            c_lastName(3) = "Shipway"
            c_middleName(3) = ""
            c_homePhone(3) = "555-1212"
            c_workPhone(3) = "(425)555-1212"
            c_email(3) = "MS_johnship@hotmail.com"
            c_streetAddress(3) = "1 Microsoft Way"
            c_city(3) = "Redmond"
            c_state(3) = "WA"
            c_zip(3) = "98007"
            c_permissions(3) = 1
            c_pin(3) = "111111"
            c_netWorth(3) = 0
            
            ' Kev's Customer Info
            c_ssn(4) = "983457489"
            c_type(4) = 1
            c_firstName(4) = "Kevin"
            c_lastName(4) = "Smith"
            c_middleName(4) = "B"
            c_homePhone(4) = "555-1212"
            c_workPhone(4) = "(118)909-4152"
            c_email(4) = "MS_kevinsmi@hotmail.com"
            c_streetAddress(4) = "Thames Valley Park"
            c_city(4) = "Reading"
            c_state(4) = "BE"
            c_zip(4) = "98007"
            c_permissions(4) = 1
            c_pin(4) = "111111"
            c_netWorth(4) = 0
            
            Dim K As Integer
            
            For I = 0 To CUSTOMER_NUM - 1
            
             ' Add the Customer Info
             sSQL = "INSERT INTO customer"
             sSQL = sSQL & " VALUES ( '" & c_ssn(I) & "'"
             sSQL = sSQL & ", " & c_type(I)
             sSQL = sSQL & ", '" & c_firstName(I) & "'"
             sSQL = sSQL & ", '" & c_lastName(I) & "'"
             sSQL = sSQL & ", '" & c_middleName(I) & "'"
             sSQL = sSQL & ", '" & c_homePhone(I) & "'"
             sSQL = sSQL & ", '" & c_workPhone(I) & "'"
             sSQL = sSQL & ", '" & c_email(I) & "'"
             sSQL = sSQL & ", '" & c_streetAddress(I) & "'"
             sSQL = sSQL & ", '" & c_city(I) & "'"
             sSQL = sSQL & ", '" & c_state(I) & "'"
             sSQL = sSQL & ", '" & c_zip(I) & "'"
             sSQL = sSQL & ", " & c_permissions(I)
             sSQL = sSQL & ", '" & c_pin(I) & "'"
             sSQL = sSQL & ", " & c_netWorth(I)
             sSQL = sSQL & " )"
            
             Set rs = cn.Execute(sSQL)
             
             sMsg = "INSERT of Customer Record OK. SSN = " & c_ssn(I)
             
             For K = 0 To (a_accts(I) - 1) And K < ACCOUNT_NUM
           
                sSQL = "INSERT INTO account"
                sSQL = sSQL & " VALUES ( '" & c_ssn(I) & "'"
                sSQL = sSQL & ", '" & a_acctNumber(I, K) & "'"
                sSQL = sSQL & ", " & a_acctType(I, K)
                sSQL = sSQL & ", " & a_portFolioId(I, K)
                sSQL = sSQL & ", " & a_taxReportingMethod(I, K)
                sSQL = sSQL & ", " & a_tradingLevel(I, K)
                sSQL = sSQL & ", " & a_serviceLevel(I, K)
                sSQL = sSQL & ", '" & a_stateCode(I, K) & "'"
                sSQL = sSQL & ", " & a_netWorth(I, K)
                sSQL = sSQL & ", " & a_cashDebit(I, K)
                sSQL = sSQL & ", " & a_cash(I, K)
                sSQL = sSQL & " )"
                
                Set rs = cn.Execute(sSQL)
                 
                sMsg = "INSERT of Account Record " & K & " OK. ACCT = " & a_acctNumber(I, K)
                
            Next ' K
             
        Next ' I
    Else
            
        Dim CUSTOMER_NUM2 As Integer
        Dim ACCOUNT_NUM2 As Integer
        
        CUSTOMER_NUM2 = sym_len
        ACCOUNT_NUM2 = 1
            
          'Declarations for the account Table
            Dim acctNumber As String
            Dim acctType As Long
            Dim portFolioId As Long
            Dim taxReportingMethod As Long
            Dim tradingLevel As Long
            Dim serviceLevel As Long
            Dim stateCode As String
            Dim netWorth As Double
            Dim cashDebit As Double
            Dim cash As Double
            
            Dim accts As Integer
            
            ' ERIK Account Info
            accts = ACCOUNT_NUM2 ' Number of accounts
            
            acctNumber = "AC" ' MUST BE 10 0r UNDER CHARACTERS
            acctType = 1
            portFolioId = 0
            taxReportingMethod = 0
            tradingLevel = 1
            serviceLevel = 1
            stateCode = "WA"
            netWorth = 0
            cashDebit = 0
            cash = 1000000
          
            
            'Declarations for the customer Table
            Dim ssn As String
            Dim ctype As Long
            Dim firstName As String
            Dim lastName As String
            Dim middleName As String
            Dim homePhone As String
            Dim workPhone As String
            Dim email As String
            Dim streetAddress As String
            Dim city As String
            Dim State As String
            Dim zip As String
            Dim permissions As Long
            Dim pin As String
            Dim cNetWorth As Double
            
            ' Erik Customer Info
            ssn = "SS"
            ctype = 1
            firstName = "Erik"
            lastName = "Gunvaldson"
            middleName = "P"
            homePhone = "555-1212"
            workPhone = "(425)703-7657"
            email = "erikgun@hotmail.com"
            streetAddress = "1 Microsoft Way"
            city = "Redmond"
            State = "WA"
            zip = "98007"
            permissions = 1
            pin = "111111"
            cNetWorth = 0
            
            For I = 0 To CUSTOMER_NUM2 - 1
            
             ' Add the Customer Info
             sSQL = "INSERT INTO customer"
             sSQL = sSQL & " VALUES ( '" & ssn & I & "'"
             sSQL = sSQL & ", " & ctype
             sSQL = sSQL & ", '" & firstName & "'"
             sSQL = sSQL & ", '" & lastName & "'"
             sSQL = sSQL & ", '" & middleName & "'"
             sSQL = sSQL & ", '" & homePhone & "'"
             sSQL = sSQL & ", '" & workPhone & "'"
             sSQL = sSQL & ", '" & email & "'"
             sSQL = sSQL & ", '" & streetAddress & "'"
             sSQL = sSQL & ", '" & city & "'"
             sSQL = sSQL & ", '" & State & "'"
             sSQL = sSQL & ", '" & zip & "'"
             sSQL = sSQL & ", " & permissions
             sSQL = sSQL & ", '" & pin & "'"
             sSQL = sSQL & ", " & cNetWorth
             sSQL = sSQL & " )"
            
             Set rs = cn.Execute(sSQL)
             
            sSQL = "INSERT INTO account"
            sSQL = sSQL & " VALUES ( '" & ssn & I & "'"
            sSQL = sSQL & ", '" & acctNumber & I & "'"
            sSQL = sSQL & ", " & acctType
            sSQL = sSQL & ", " & portFolioId
            sSQL = sSQL & ", " & taxReportingMethod
            sSQL = sSQL & ", " & tradingLevel
            sSQL = sSQL & ", " & serviceLevel
            sSQL = sSQL & ", '" & stateCode & "'"
            sSQL = sSQL & ", " & netWorth
            sSQL = sSQL & ", " & cashDebit
            sSQL = sSQL & ", " & cash
            sSQL = sSQL & " )"
                
            Set rs = cn.Execute(sSQL)
                   
        Next ' I
    
    End If

    InitTestData = SUCCESS
       
    ElseIf flag = INIT_ALL Or flag = INIT_QUOTES Then
        
        If sym_len = 0 Then
            ret = InitDefQuoteData(dDelta, sMsg, iLoops)
        Else
            ret = InitGenQuoteData(dDelta, sMsg, iLoops, sym_len)
        End If
        
        If ret <> SUCCESS Then
            InitTestData = FAILED
        Else
            InitTestData = SUCCESS
        End If
        
    End If

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
    
    InitTestData = FAILED
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
     
    sMsg = LogErrorStr("IAccount.InitTestData. " & sMsg & " SQL = " & sSQL)
    
End Function

Public Function InitDefQuoteData(ByVal dDelta As Double, ByRef sMsg As Variant, Optional iLoops As Integer = 400) As Long

        Dim myDate As Date
        Dim rcnt As Long
        Dim I As Long
        Dim K As Long
        Dim cnt As Long
        Dim sSQL As String
        Dim cn As ADODB.Connection
        Dim rs As ADODB.Recordset
        
        On Error GoTo ErrorHandler
        
        rcnt = 0
        myDate = Now()
        
        InitDefQuoteData = FAILED
        
        Set cn = New ADODB.Connection
        
        cn.Open GetDSN()
    
        'Declarations for the LongQuote Table
        Dim q_Symbol(5) As String
        Dim q_QuoteTime As Date
        Dim q_BidPrice(5) As Double
        Dim q_AskPrice(5) As Double
        Dim q_LastTradeTime(5) As String
        Dim q_LastTradePrice(5) As Double
        Dim q_NetChange(5) As Double
        Dim q_DailyHigh(5) As Double
        Dim q_DailyLow(5) As Double
        Dim q_AskSize(5) As Integer
        Dim q_BidSize(5) As Integer
        Dim q_OpenPrice(5) As Double
        Dim q_ClosePrice(5) As Double
        Dim q_tCloseDate(5) As Date
        Dim q_newsID(5) As Long
        Dim q_Delta(5) As Double
        
        Dim np As Integer
        
        Dim negpos(5) As Integer
        
        Dim q_News As String
        
        Dim oQuote As HBExchange.IQuote
        
        Dim nFlag(5) As Boolean
        
        nFlag(0) = True
        nFlag(1) = True
        nFlag(2) = True
        nFlag(3) = True
        nFlag(4) = True
            
        q_BidPrice(0) = 90.21
        q_AskPrice(0) = 91.55
        q_LastTradePrice(0) = 90.67
        q_OpenPrice(0) = 91.23
        q_ClosePrice(0) = 91.45
        q_tCloseDate(0) = myDate
        q_newsID(0) = 0
      
        q_BidPrice(1) = 60.21
        q_AskPrice(1) = 61.55
        q_LastTradePrice(1) = 60.37
        q_OpenPrice(1) = 60.9
        q_ClosePrice(1) = 59.38
        q_tCloseDate(1) = myDate
        q_newsID(1) = 0
         
        q_BidPrice(2) = 170.44
        q_AskPrice(2) = 181.67
        q_LastTradePrice(2) = 175.55
        q_OpenPrice(2) = 177.01
        q_ClosePrice(2) = 169.23
        q_tCloseDate(2) = myDate
        q_newsID(2) = 0
        
        q_BidPrice(3) = 34.61
        q_AskPrice(3) = 36.67
        q_LastTradePrice(3) = 35.55
        q_OpenPrice(3) = 70.61
        q_ClosePrice(3) = 72.45
        q_tCloseDate(3) = myDate
        q_newsID(3) = 0
        
        q_BidPrice(4) = 72.61
        q_AskPrice(4) = 72.88
        q_LastTradePrice(4) = 72.68
        q_OpenPrice(4) = 70.61
        q_ClosePrice(4) = 72.45
        q_tCloseDate(4) = myDate
        q_newsID(4) = 0
         
        q_DailyHigh(0) = 0
        q_DailyHigh(1) = 0
        q_DailyHigh(2) = 0
        q_DailyHigh(3) = 0
        q_DailyHigh(4) = 0
        
        negpos(0) = 1
        negpos(1) = -1
        negpos(2) = 1
        negpos(3) = -1
        negpos(4) = 1
        negpos(5) = -1
        q_DailyLow(0) = 1000
        q_DailyLow(1) = 1000
        q_DailyLow(2) = 1000
        q_DailyLow(3) = 1000
        q_DailyLow(4) = 1000
        
        q_Delta(0) = dDelta
        q_Delta(1) = dDelta + 0.2
        q_Delta(2) = dDelta + 0.4
        q_Delta(3) = dDelta - 0.2
        q_Delta(4) = dDelta - 0.4
    
        q_NetChange(0) = 0
        q_NetChange(1) = 0
        q_NetChange(2) = 0
        q_NetChange(3) = 0
        q_NetChange(4) = 0
        
        q_tCloseDate(0) = DateAdd("d", -1, myDate)
        q_tCloseDate(1) = q_tCloseDate(0)
        q_tCloseDate(2) = q_tCloseDate(0)
        q_tCloseDate(3) = q_tCloseDate(0)
        q_tCloseDate(4) = q_tCloseDate(0)
        
        q_QuoteTime = myDate
        
    ' Delete all LongQuote records
    sSQL = "DELETE LongQuote"
    Set rs = cn.Execute(sSQL)
    sMsg = "DELETE of All LongQuote Records OK"
    
    ' Delete all Quote records
    sSQL = "DELETE Quote"
    Set rs = cn.Execute(sSQL)
    sMsg = "DELETE of All Quote Records OK"
        
    ' Delete all symbol records
    sSQL = "DELETE symbol"
    Set rs = cn.Execute(sSQL)
    sMsg = "DELETE of All symbol Records OK"
        
    ' Delete all News records
    sSQL = "DELETE news"
    Set rs = cn.Execute(sSQL)
    sMsg = "DELETE of All News Records OK"
        
    Dim scnt As Long
    Dim J As Integer
    Dim SymbolList As Variant
    Dim rc As Long
    
    ' Create Symbol List Information
    sSQL = "INSERT INTO symbol VALUES ( 'WEYE', 1, 101, 'Walleye Pond Brewery' )"
    Set rs = cn.Execute(sSQL)
            
    sSQL = "INSERT INTO symbol VALUES ( 'MSQT', 2, 102, 'Mosquito Packing Company' )"
    Set rs = cn.Execute(sSQL)
            
    sSQL = "INSERT INTO symbol VALUES ( 'ICEI', 3, 103, 'Ice Cubes International' )"
    Set rs = cn.Execute(sSQL)
            
    sSQL = "INSERT INTO symbol VALUES ( 'MCFR', 4, 104, 'Milk Cartoon Floats Inc' )"
    Set rs = cn.Execute(sSQL)
            
    sSQL = "INSERT INTO symbol VALUES ( 'HCKY', 5, 105, 'Hockey Puck Foods' )"
    Set rs = cn.Execute(sSQL)
              
    sMsg = "INSERT of Symbol Records OK"
        
    cnt = 1
    
    If Not GetObjectContext Is Nothing Then
            Set oQuote = GetObjectContext.CreateInstance("HBExchange.IQuote")
    Else
            Set oQuote = CreateObject("HBExchange.IQuote")
    End If
        
    rc = oQuote.GetSymbolList(SymbolList, sMsg)
    If rc <> SUCCESS Then
            sMsg = "Failed on GetSymbolList"
            Exit Function
    End If
        
        
    If SymbolList.EOF Then
            sMsg = "No Symbols In Symbols DB Table"
            Exit Function
    End If
        
    Dim symbols()
        
    symbols = SymbolList.GetRows

        
    For I = 0 To iLoops
      
            For K = 0 To UBound(symbols, 2) And K < 5
            
                q_Symbol(K) = symbols(0, K)
               
                ' The higher the delta, the faster the price goes up or down.
                
                q_AskPrice(K) = q_AskPrice(K) + (q_Delta(K) * negpos(K))
                
                nFlag(K) = False
                If q_AskPrice(K) > (q_ClosePrice(K) + 50) Then
                    q_News = "Reached All-time High of " & q_AskPrice(K) & "!"
                    nFlag(K) = True
                    negpos(K) = -1
                ElseIf q_AskPrice(K) < 0.5 Then
                    nFlag(K) = True
                    q_AskPrice(K) = 0.5
                    negpos(K) = 1
                    q_News = "Bottomed at the Unbelievable Low of " & q_AskPrice(K) & "!"
                End If
                
                q_BidPrice(K) = q_AskPrice(K) - 0.35
                
                If q_BidPrice(K) <= 0 Then
                    q_BidPrice(K) = 0.1
                End If
                
                q_LastTradePrice(K) = q_AskPrice(K) - 0.15
                    
                If q_LastTradePrice(K) <= 0 Then
                    q_LastTradePrice(K) = 0.25
                End If
                
                If q_DailyHigh(K) < q_LastTradePrice(K) Then
                    q_DailyHigh(K) = q_LastTradePrice(K)
                End If
                    
                If q_DailyLow(K) > q_LastTradePrice(K) Then
                    q_DailyLow(K) = q_LastTradePrice(K)
                End If
                
                q_BidSize(K) = 10 + (K * 10)
                q_AskSize(K) = 10 + (K * 5)
                
                ' Set the News
                q_newsID(K) = 0
                If nFlag(K) = True Then
                    nFlag(K) = False
                    q_newsID(K) = rcnt
                    sSQL = "INSERT INTO news VALUES ( '" & myDate & "', '" & q_News & "', '" & q_Symbol(K) & "', 'microsoft.com', " & q_newsID(K) & " )"
                    Set rs = cn.Execute(sSQL)
                End If
                
                If q_LastTradePrice(K) < 1 Then
                    q_NetChange(K) = -100
                ElseIf q_LastTradePrice(K) = q_ClosePrice(K) Then
                    q_NetChange(K) = 0
                Else
                    q_NetChange(K) = ((q_LastTradePrice(K) - q_ClosePrice(K)) / q_ClosePrice(K)) * 100
                End If
                
                ' Create LongQuote Record
                
                sSQL = "INSERT INTO LongQuote"
                
                sSQL = sSQL & " VALUES ( '" & q_Symbol(K) & "'"
                sSQL = sSQL & ", '" & q_QuoteTime & "'"
                sSQL = sSQL & ", " & q_BidPrice(K)
                sSQL = sSQL & ", " & q_AskPrice(K)
                sSQL = sSQL & ", '" & FormatDateTime(q_QuoteTime) & "'"
                sSQL = sSQL & ", " & q_LastTradePrice(K)
                sSQL = sSQL & ", " & q_NetChange(K)
                sSQL = sSQL & ", " & q_DailyHigh(K)
                sSQL = sSQL & ", " & q_DailyLow(K)
                sSQL = sSQL & ", " & q_AskSize(K)
                sSQL = sSQL & ", " & q_BidSize(K)
                sSQL = sSQL & ", " & q_OpenPrice(K)
                sSQL = sSQL & ", " & q_ClosePrice(K)
                sSQL = sSQL & ", '" & q_tCloseDate(K) & "'"
                sSQL = sSQL & ", " & q_newsID(K)
                sSQL = sSQL & " )"
                
                Set rs = cn.Execute(sSQL)
                
                rcnt = rcnt + 1
                
                myDate = DateAdd("s", 1, myDate)
                
                q_QuoteTime = myDate
                
             Next
    Next
        
    sMsg = "" & rcnt & " Records Of LongQuote Have been Successfully re-generated with End Time of " & q_QuoteTime
        
    
    InitDefQuoteData = SUCCESS
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
    
    Exit Function

ErrorHandler:

    If Not cn Is Nothing Then
        Set cn = Nothing
    End If
    
    If Not rs Is Nothing Then
        Set rs = Nothing
    End If
    
    If Not oQuote Is Nothing Then
        Set oQuote = Nothing
    End If
    
    InitDefQuoteData = FAILED
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
     
    sMsg = LogErrorStr("IAccount.InitDefQuoteData. " & sMsg & " SQL = " & sSQL)
    
End Function

Public Function InitGenQuoteData(ByVal dDelta As Double, ByRef sMsg As Variant, Optional iLoops As Integer = 400, Optional sym_len As Long = 0) As Long

        Dim myDate As Date
        Dim rcnt As Long
        Dim sSQL As String
        Dim I As Long
        Dim K As Long
        Dim cnt As Long
        Dim cn As ADODB.Connection
        Dim rs As ADODB.Recordset
        
        On Error GoTo ErrorHandler
        
        rcnt = 0
        myDate = Now()
        
        InitGenQuoteData = FAILED
        
        Set cn = New ADODB.Connection
         
        cn.Open GetDSN()
    
        'Declarations for the LongQuote Table
        Dim q_Symbol As String
        Dim q_QuoteTime As Date
        Dim q_BidPrice As Double
        Dim q_AskPrice As Double
        Dim q_LastTradeTime As String
        Dim q_LastTradePrice As Double
        Dim q_NetChange As Double
        Dim q_DailyHigh As Double
        Dim q_DailyLow As Double
        Dim q_AskSize As Integer
        Dim q_BidSize As Integer
        Dim q_OpenPrice As Double
        Dim q_ClosePrice As Double
        Dim q_tCloseDate As Date
        Dim q_newsID As Long
        Dim q_Delta As Double
        Dim np As Integer
        Dim negpos As Integer
        Dim q_News As String
        Dim oQuote As HBExchange.IQuote
        Dim nFlag As Boolean
        
        nFlag = True
        q_BidPrice = 0.98
        q_AskPrice = 1.02
        q_LastTradePrice = 1#
        q_OpenPrice = 0.99
        q_ClosePrice = 0.98
        q_tCloseDate = myDate
        q_newsID = 0
        q_DailyHigh = 0
        negpos = 1
        q_DailyLow = 1000
        q_Delta = dDelta
    
        q_NetChange = 0
        
        q_tCloseDate = DateAdd("d", -1, myDate)
        
        q_QuoteTime = myDate
        
        ' Delete all LongQuote records
        sSQL = "DELETE LongQuote"
        Set rs = cn.Execute(sSQL)
        sMsg = "DELETE of All LongQuote Records OK"
        
         ' Delete all Quote records
        sSQL = "DELETE Quote"
        Set rs = cn.Execute(sSQL)
        sMsg = "DELETE of All Quote Records OK"
        
        ' Delete all symbol records
        sSQL = "DELETE symbol"
        Set rs = cn.Execute(sSQL)
        sMsg = "DELETE of All symbol Records OK"
        
        ' Delete all News records
        sSQL = "DELETE news"
        Set rs = cn.Execute(sSQL)
        sMsg = "DELETE of All News Records OK"
        
        Dim symbol_str As String
        Dim SymbolList As Variant
        Dim rc As Long
        
        For I = 1 To sym_len
                ' Create Symbol List Information
                symbol_str = "S" & I
                sSQL = "INSERT INTO symbol VALUES ( '" & symbol_str & "', " & I & ", " & I & ", '" & symbol_str & "' )"
                Set rs = cn.Execute(sSQL)
        Next
        sMsg = "INSERT of " & sym_len & " Symbol Records OK"
        
        cnt = 1
    
        If Not GetObjectContext Is Nothing Then
            Set oQuote = GetObjectContext.CreateInstance("HBExchange.IQuote")
        Else
            Set oQuote = CreateObject("HBExchange.IQuote")
        End If
        
        rc = oQuote.GetSymbolList(SymbolList, sMsg)
        If rc <> SUCCESS Then
            sMsg = "Failed on GetSymbolList"
            Exit Function
        End If
        
        
        If SymbolList.EOF Then
            sMsg = "No Symbols In Symbols DB Table"
            Exit Function
        End If
        
        Dim symbols()
        
        symbols = SymbolList.GetRows
      
        For K = 0 To UBound(symbols, 2) And K < sym_len
            
                q_Symbol = symbols(0, K)
               
                ' The higher the delta, the faster the price goes up or down.
                
                q_AskPrice = q_AskPrice + (dDelta * negpos)
                
                nFlag = False
                If q_AskPrice > (q_ClosePrice + 50) Then
                    q_News = "Reached All-time High of " & q_AskPrice & "!"
                    nFlag = True
                    negpos = -1
                ElseIf q_AskPrice < 0.5 Then
                    nFlag = True
                    q_AskPrice = 0.5
                    negpos = 1
                    q_News = "Bottomed at the Unbelievable Low of " & q_AskPrice & "!"
                End If
                
                q_BidPrice = q_AskPrice - (dDelta * 0.35)
                
                If q_BidPrice <= 0 Then
                    q_BidPrice = 0.1
                End If
                
                q_LastTradePrice = q_AskPrice - (dDelta * 0.15)
                    
                If q_LastTradePrice <= 0 Then
                    q_LastTradePrice = 0.25
                End If
                
                If q_DailyHigh < q_LastTradePrice Then
                    q_DailyHigh = q_LastTradePrice
                End If
                    
                If q_DailyLow > q_LastTradePrice Then
                    q_DailyLow = q_LastTradePrice
                End If
                
                q_BidSize = 10 * 10
                q_AskSize = 10 + 5
                
                ' Set the News
                q_newsID = 0
                If nFlag = True Then
                    nFlag = False
                    q_newsID = rcnt
                    sSQL = "INSERT INTO news VALUES ( '" & myDate & "', '" & q_News & "', '" & q_Symbol & "', 'microsoft.com', " & q_newsID & " )"
                    Set rs = cn.Execute(sSQL)
                End If
                
                If q_LastTradePrice < 1 Then
                    q_NetChange = -100
                ElseIf q_LastTradePrice = q_ClosePrice Then
                    q_NetChange = 0
                Else
                    q_NetChange = ((q_LastTradePrice - q_ClosePrice) / q_ClosePrice) * 100
                End If
                
                ' Create LongQuote Record
                
                sSQL = "INSERT INTO LongQuote"
                
                sSQL = sSQL & " VALUES ( '" & q_Symbol & "'"
                sSQL = sSQL & ", '" & q_QuoteTime & "'"
                sSQL = sSQL & ", " & q_BidPrice
                sSQL = sSQL & ", " & q_AskPrice
                sSQL = sSQL & ", '" & FormatDateTime(q_QuoteTime) & "'"
                sSQL = sSQL & ", " & q_LastTradePrice
                sSQL = sSQL & ", " & q_NetChange
                sSQL = sSQL & ", " & q_DailyHigh
                sSQL = sSQL & ", " & q_DailyLow
                sSQL = sSQL & ", " & q_AskSize
                sSQL = sSQL & ", " & q_BidSize
                sSQL = sSQL & ", " & q_OpenPrice
                sSQL = sSQL & ", " & q_ClosePrice
                sSQL = sSQL & ", '" & q_tCloseDate & "'"
                sSQL = sSQL & ", " & q_newsID
                sSQL = sSQL & " )"
                
                Set rs = cn.Execute(sSQL)
                
                rcnt = rcnt + 1
                
                myDate = DateAdd("s", 1, myDate)
                
                q_QuoteTime = myDate
                
    Next
        
    sMsg = "" & rcnt & " Records Of LongQuote Have been Successfully re-generated with End Time of " & q_QuoteTime
        
    
    InitGenQuoteData = SUCCESS
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
    
    Exit Function

ErrorHandler:

    If Not cn Is Nothing Then
        Set cn = Nothing
    End If
    
    If Not rs Is Nothing Then
        Set rs = Nothing
    End If
    
    If Not oQuote Is Nothing Then
        Set oQuote = Nothing
    End If
    
    InitGenQuoteData = FAILED
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
     
    sMsg = LogErrorStr("IAccount.InitGenQuoteData. " & sMsg & " SQL = " & sSQL)
    
End Function

Public Function GetXMLAccounts(ByVal sSSN As String, ByRef sXMLStream As Variant, ByRef sMsg As Variant) As Long
    
    GetXMLAccounts = FAILED

    ' Build the XML Document
    On Error GoTo ErrorHandler
    
    ' Data Base declarations
    Dim cn As ADODB.Connection
    Dim rsAcc As ADODB.Recordset
    Dim rsHold As ADODB.Recordset
    Dim cmdAcc As ADODB.Command
    Dim cmdHold As ADODB.Command
    Dim sSQL As String
    
    ' XML declarations
    Dim XMLCtrl As XMLDSOControl
    Dim xmlRoot As IXMLDOMNode
    Dim xmlNode As IXMLDOMNode
    Dim xmlChild As IXMLDOMNode
    Dim xmlChild2 As IXMLDOMNode
    Dim xmlAccounts As IXMLDOMNode
    Dim xmlHoldings As IXMLDOMNode
    Dim xmlHolding As IXMLDOMNode
    Dim xmlHistories As IXMLDOMNode
    Dim xmlHistory As IXMLDOMNode
    Dim xmlPendingOrders As IXMLDOMNode
    Dim xmlPending As IXMLDOMNode
    Dim xmlNetWorth As IXMLDOMNode
    
    ' General declarations
    Dim nAccCount As Integer
    Dim nHoldCount As Integer
    Dim strAccountNum As String
    Dim nAction As Long
    Dim nQuantity As Long
    Dim strSymbol As String
    Dim strSymbolOld As String
    Dim bSymbolChanged As Boolean
    Dim dSettledPrice As Double
    Dim dCommision  As Double
    Dim nAccountType As Long
    Dim dNetWorth, dCash, dCashDebit As Double
    Dim nTradeType As Integer
    Dim nOrderStatus As Integer

    Set cn = New ADODB.Connection
    
    ' Instanciate the XML control
    Set XMLCtrl = New XMLDSOControl
    
    ' Create a CustomerSSN child
    Set xmlRoot = XMLCtrl.XMLDocument.createNode("element", "CustomerSSN", "")
    Call XMLCtrl.XMLDocument.appendChild(xmlRoot)
    
    ' Add customer SSN for completeness
    Set xmlNode = XMLCtrl.XMLDocument.createNode("element", "SSN", "")
    xmlNode.Text = sSSN
    Call xmlRoot.appendChild(xmlNode)
        
    ' Query DB for those customers with a SSN equal to sSSN
    ' Use client side cursor
    cn.Open GetDSN()
    
    Set cmdAcc = New ADODB.Command
    sSQL = "Select *  FROM account Where account.ssn = '" & sSSN & "'"
    cmdAcc.CommandText = sSQL
    cmdAcc.CommandType = adCmdText
    Set cmdAcc.ActiveConnection = cn
    
    Set rsAcc = New ADODB.Recordset
    rsAcc.CursorLocation = adUseClient
    rsAcc.Open cmdAcc, , adOpenStatic, adLockBatchOptimistic, adCmdText
    
    ' Create the Accounts Branch
    Set xmlAccounts = XMLCtrl.XMLDocument.createNode("element", "Accounts", "")
    Call xmlRoot.appendChild(xmlAccounts)
    
    ' Calculate the total net worth for the customer
    While Not rsAcc.EOF
        dNetWorth = dNetWorth + rsAcc("networth")
        dCash = dCash + rsAcc("cash")
        dCashDebit = dCashDebit + rsAcc("cashDebit")
        rsAcc.MoveNext
    Wend
    
    Set xmlNode = XMLCtrl.XMLDocument.createNode("element", "total_networth", "")
    xmlNode.Text = dNetWorth
    Call xmlAccounts.appendChild(xmlNode)
    
    Set xmlNode = XMLCtrl.XMLDocument.createNode("element", "total_cash", "")
    xmlNode.Text = dCash
    Call xmlAccounts.appendChild(xmlNode)
    
    Set xmlNode = XMLCtrl.XMLDocument.createNode("element", "total_cashdebit", "")
    xmlNode.Text = dCashDebit
    Call xmlAccounts.appendChild(xmlNode)
    
    ' Create the Pending Order Branch
    Set xmlPendingOrders = XMLCtrl.XMLDocument.createNode("element", "Pending_Orders", "")
    Call xmlAccounts.appendChild(xmlPendingOrders)
        
    ' Move back to the first recordset
    If Not (rsAcc.BOF And rsAcc.EOF) Then
    rsAcc.MoveFirst
    End If
    
    ' Iterate thru all those records in the account DB table
    While Not rsAcc.EOF
        ' Create an account child for each account
        Set xmlNode = XMLCtrl.XMLDocument.createNode("element", "account", "")
        xmlNode.Text = rsAcc("acctNumber")
        Call xmlAccounts.appendChild(xmlNode)
        
        ' Needed for History
        nAccountType = rsAcc("acctType")
        
        ' Populate Account information
        For nAccCount = 0 To rsAcc.Fields.Count - 1
            Set xmlChild = XMLCtrl.XMLDocument.createNode("element", rsAcc.Fields(nAccCount).name, "")
            
            ' Check for NULL fields
            xmlChild.Text = ValidateFieldIndex(rsAcc, nAccCount)
            If rsAcc.Fields(nAccCount).name = "acctNumber" Then
                strAccountNum = rsAcc.Fields(nAccCount)
            End If
            Call xmlNode.appendChild(xmlChild)
        Next
        
        ' For each account we need to populate the Holdings within that account.
        ' Select the holdings for the specified SSN which exist in this account, order
        ' by symbol
        Set cmdHold = New ADODB.Command
        sSQL = "Select *  FROM holding Where holding.ssn = '" & sSSN & "' order by symbol"
        cmdHold.CommandText = sSQL
        cmdHold.CommandType = adCmdText
        Set cmdHold.ActiveConnection = cn
        
        Set rsHold = New ADODB.Recordset
        rsHold.CursorLocation = adUseClient
        rsHold.Open cmdHold, , adOpenStatic, adLockBatchOptimistic, adCmdText
        
        ' Create the Holding Branch
        Set xmlHoldings = XMLCtrl.XMLDocument.createNode("element", "Holdings", "")
        Call xmlNode.appendChild(xmlHoldings)
               
        ' Create the History Branch
        Set xmlHistories = XMLCtrl.XMLDocument.createNode("element", "Histories", "")
        Call xmlNode.appendChild(xmlHistories)

        ' Iterate thru all holdings
        While Not rsHold.EOF
        
            strSymbol = rsHold("symbol")
            nAction = rsHold("action")
            nQuantity = rsHold("quantity")
            dSettledPrice = rsHold("settledPrice")
            dCommision = rsHold("commision")
            
            ' If condition is true then we have a holding, otherwise, we have a history
            If nAction = HOLDING_SUMMARY And nQuantity > 0 Then
                ' Create a new holding entry
                Set xmlHolding = XMLCtrl.XMLDocument.createNode("element", "Holding", "")
                xmlHolding.Text = strSymbol
                Call xmlHoldings.appendChild(xmlHolding)
                            
                ' Add Holding Items ...
                ' Symbol
                Set xmlChild = XMLCtrl.XMLDocument.createNode("element", "symbol", "")
                xmlChild.Text = strSymbol
                Call xmlHolding.appendChild(xmlChild)
                
                ' Quantity
                Set xmlChild = XMLCtrl.XMLDocument.createNode("element", "quantity", "")
                xmlChild.Text = nQuantity
                Call xmlHolding.appendChild(xmlChild)
                
                ' Net Worth
                Set xmlChild = XMLCtrl.XMLDocument.createNode("element", "net_worth", "")
                xmlChild.Text = rsHold("value")
                Call xmlHolding.appendChild(xmlChild)
            
                ' Reconciled
                Set xmlChild = XMLCtrl.XMLDocument.createNode("element", "reconciled", "")
                xmlChild.Text = rsHold("reconcileDate")
                Call xmlHolding.appendChild(xmlChild)
            
                ' Current Price (settledPrice)
                Set xmlChild = XMLCtrl.XMLDocument.createNode("element", "current_price", "")
                xmlChild.Text = dSettledPrice
                Call xmlHolding.appendChild(xmlChild)
            
                ' Current Value
                Set xmlChild = XMLCtrl.XMLDocument.createNode("element", "current_value", "")
                xmlChild.Text = (dSettledPrice * nQuantity)
                Call xmlHolding.appendChild(xmlChild)
            
            Else
                ' Create a new history entry
                Set xmlHistory = XMLCtrl.XMLDocument.createNode("element", "History", "")
                xmlHistory.Text = strSymbol
                Call xmlHistories.appendChild(xmlHistory)
                
                ' Add History Items ...
                ' Confirmation Number
                Set xmlChild = XMLCtrl.XMLDocument.createNode("element", "confirmationNum", "")
                xmlChild.Text = ValidateField(rsHold, "orderID")
                Call xmlHistory.appendChild(xmlChild)
                
                ' Action
                Set xmlChild = XMLCtrl.XMLDocument.createNode("element", "action", "")
                If rsHold("action") = BUY Then
                    xmlChild.Text = "BUY"
                Else
                    xmlChild.Text = "SELL"
                End If
                Call xmlHistory.appendChild(xmlChild)
            
                ' Shares
                Set xmlChild = XMLCtrl.XMLDocument.createNode("element", "shares", "")
                xmlChild.Text = rsHold("quantity")
                Call xmlHistory.appendChild(xmlChild)
                
                ' Symbol
                Set xmlChild = XMLCtrl.XMLDocument.createNode("element", "symbol", "")
                xmlChild.Text = strSymbol
                Call xmlHistory.appendChild(xmlChild)
            
                ' Total Price
                Set xmlChild = XMLCtrl.XMLDocument.createNode("element", "total_price", "")
                xmlChild.Text = rsHold("value")
                Call xmlHistory.appendChild(xmlChild)
            
                ' Type
                Set xmlChild = XMLCtrl.XMLDocument.createNode("element", "type", "")
                nTradeType = rsHold("tradeType")
                If nTradeType = MARKET_ORDER Then
                    xmlChild.Text = "MARKET"
                ElseIf nTradeType = LIMIT_ORDER Then
                    xmlChild.Text = "LIMIT"
                Else
                    xmlChild.Text = "UNKNOWN"
                End If
                Call xmlHistory.appendChild(xmlChild)
            
                ' Status
                Set xmlChild = XMLCtrl.XMLDocument.createNode("element", "status", "")
                nOrderStatus = rsHold("orderStatus")
                If nOrderStatus = CONFIRMED Then
                    xmlChild.Text = "M-CONF"
                ElseIf nOrderStatus = SETTLED Then
                    xmlChild.Text = "FILLED"
                ElseIf nOrderStatus = RECONCILED Then
                    xmlChild.Text = "RECON"
                ElseIf nOrderStatus = CANCELED Then
                    xmlChild.Text = "CAN"
                ElseIf nOrderStatus = ICONFIRMED Then
                    xmlChild.Text = "I-CONF"
                Else
                    xmlChild.Text = "UNKNOWN"
                End If
                Call xmlHistory.appendChild(xmlChild)
            
                ' Limit Price
                Set xmlChild = XMLCtrl.XMLDocument.createNode("element", "limit_price", "")
                xmlChild.Text = ValidateField(rsHold, "limitPrice")
                Call xmlHistory.appendChild(xmlChild)
            
                ' Price
                Set xmlChild = XMLCtrl.XMLDocument.createNode("element", "price", "")
                xmlChild.Text = ValidateField(rsHold, "settledPrice")
                Call xmlHistory.appendChild(xmlChild)
            
                ' Confirmed
                Set xmlChild = XMLCtrl.XMLDocument.createNode("element", "confirmed", "")
                xmlChild.Text = ValidateField(rsHold, "confirmationDate")
                Call xmlHistory.appendChild(xmlChild)
            
                ' Settled
                Set xmlChild = XMLCtrl.XMLDocument.createNode("element", "settled", "")
                xmlChild.Text = ValidateField(rsHold, "settlementDate")
                Call xmlHistory.appendChild(xmlChild)
            
                ' Reconciled
                Set xmlChild = XMLCtrl.XMLDocument.createNode("element", "reconciled", "")
                xmlChild.Text = ValidateField(rsHold, "reconcileDate")
                Call xmlHistory.appendChild(xmlChild)
            
                ' Comm - Commision
                Set xmlChild = XMLCtrl.XMLDocument.createNode("element", "comm", "")
                xmlChild.Text = ValidateField(rsHold, "commision")
                Call xmlHistory.appendChild(xmlChild)
            
                ' Check_number
                Set xmlChild = XMLCtrl.XMLDocument.createNode("element", "check_number", "")
                xmlChild.Text = ValidateField(rsHold, "check_number")
                Call xmlHistory.appendChild(xmlChild)
            
                ' Acknowledged
                Set xmlChild = XMLCtrl.XMLDocument.createNode("element", "acknowledged", "")
                If rsHold("acknowledged") = NOT_ACKNOWLEDGED Then
                    xmlChild.Text = "NO"
                Else
                    xmlChild.Text = "YES"
                End If
                Call xmlHistory.appendChild(xmlChild)
                
                
            End If
                        
            rsHold.MoveNext
        Wend
        
        rsAcc.MoveNext
    Wend
                   
    ' Now pull out all the Pending Orders ...
    ' Check to see if we have a recordset (if there are no accounts an rs will not have
    ' been created
    If Not rsHold Is Nothing Then
        If Not (rsHold.EOF And rsHold.BOF) Then
            rsHold.MoveFirst
        End If
        
        While Not rsHold.EOF
            ' Check to see if we have any pending orders
            nOrderStatus = rsHold("orderStatus")
            If nOrderStatus = CONFIRMED Then
                ' Create a new holding entry
                Set xmlPending = XMLCtrl.XMLDocument.createNode("element", "Pending", "")
                xmlPending.Text = rsHold("symbol")
                Call xmlPendingOrders.appendChild(xmlPending)
                            
                ' Add Pending Items ...
                ' Confirmation Number
                Set xmlChild = XMLCtrl.XMLDocument.createNode("element", "confirmationNum", "")
                xmlChild.Text = ValidateField(rsHold, "orderID")
                Call xmlPending.appendChild(xmlChild)
                
                ' Symbol
                Set xmlChild = XMLCtrl.XMLDocument.createNode("element", "symbol", "")
                xmlChild.Text = rsHold("symbol")
                Call xmlPending.appendChild(xmlChild)
            
                ' Quantity
                Set xmlChild = XMLCtrl.XMLDocument.createNode("element", "quantity", "")
                xmlChild.Text = rsHold("quantity")
                Call xmlPending.appendChild(xmlChild)
                
                ' Confirmation Date
                Set xmlChild = XMLCtrl.XMLDocument.createNode("element", "confirmed", "")
                xmlChild.Text = ValidateField(rsHold, "confirmationDate")
                Call xmlPending.appendChild(xmlChild)
                
                ' Limit Price
                Set xmlChild = XMLCtrl.XMLDocument.createNode("element", "limit_price", "")
                xmlChild.Text = ValidateField(rsHold, "limitPrice")
                Call xmlPending.appendChild(xmlChild)
                
                ' Account Number
                Set xmlChild = XMLCtrl.XMLDocument.createNode("element", "acc_number", "")
                xmlChild.Text = rsHold("acctNumber")
                Call xmlPending.appendChild(xmlChild)
                
            End If
            
            rsHold.MoveNext
        Wend
    End If
    
    sXMLStream = XMLCtrl.XMLDocument.xml
        
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
    
    GetXMLAccounts = SUCCESS
    
    Exit Function
    
ErrorHandler:
    GetXMLAccounts = FAILED

    If Not XMLCtrl Is Nothing Then
        Set XMLCtrl = Nothing
    End If
    
    If Not cn Is Nothing Then
        Set cn = Nothing
    End If
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    sMsg = LogErrorStr("ICustomer.GetXMLAccounts")
Resume Next
End Function

