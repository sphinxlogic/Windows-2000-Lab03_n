VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 1  'NoTransaction
END
Attribute VB_Name = "IExchangeOrder"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Attribute VB_Ext_KEY = "RVB_UniqueId" ,"373680E90186"
'/***********************************************************************************\
'*************************************************************************************
'*  COM+ Hanson Brothers SDK Sample
'*  Class IExchange (HBExchange)
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


' The MarketFloor component "Uses" transactions. The transaction originator is
' the Order component (in particular, the Order.Execute method).

Option Explicit

Public Sub EnterOrder(ByVal sSSN As String, ByVal sAcctNum As String, ByVal sSymbol As String, ByVal iAction As Integer, ByVal iQuantity As Integer, ByVal cLimitPrice As Currency, ByVal iTradeType As Integer, ByVal lOrderId As Long, ByVal iInstitutionId As Integer, ByVal bQueued As Boolean)

    ' PURPOSE: Enter a new order into the pendingOrder table. In addition, call the
    ' IMarketFloor.GetMatchingTrades to determine if an existing quote satisfies
    ' this order (as opposed to waiting for IQuoteUpdate.Update to call when a quote changes)
    
    Dim oData As DataLayer
    Dim rs As ADODB.Recordset
    Dim sSQL As String
    Dim lConfirmNumber As Long
    Dim iNotQueued As Integer
    Dim oMarketFloor As HBExchange.IMarketFloor
    Dim oQuote As HBExchange.IQuote
    Dim oNotify As Object
   
    Dim dNetChange As Double
    Dim cOpenPrice As Currency
    Dim cClosePrice As Currency
    Dim cDailyHigh As Currency
    Dim cDailyLow As Currency
    Dim cAskPrice As Currency
    Dim cBidPrice As Currency
    Dim cLastTradePrice As Currency
    Dim lBidSize As Long
    Dim lAskSize As Long
    Dim dQuoteTime As Date
    Dim dLastTradeTime As Date
    Dim dCloseDate As Date
    Dim sMsg As String
    Dim strSymbol As String
    Dim rc As Long
    
    strSymbol = Trim(sSymbol)
    
    On Error GoTo ErrorHandler
    
    If bQueued Then
        iNotQueued = 0
    Else
        iNotQueued = 1
    End If
    
    Set oData = New HBExchange.DataLayer
    
    sSQL = "EXEC sp_InsertPendingTrades "
    sSQL = sSQL & "@ssn = '" & Trim(sSSN) & "'"
    sSQL = sSQL & ", @acctNum = '" & sAcctNum & "'"
    sSQL = sSQL & ", @symbol = '" & strSymbol & "'"
    sSQL = sSQL & ", @action = " & iAction
    sSQL = sSQL & ", @quantity = " & iQuantity
    sSQL = sSQL & ", @limitPrice = " & cLimitPrice
    sSQL = sSQL & ", @tradeType = " & iTradeType
    sSQL = sSQL & ", @status = " & CONFIRMED
    sSQL = sSQL & ", @priority = " & iTradeType
    sSQL = sSQL & ", @orderId = " & lOrderId
    sSQL = sSQL & ", @institutionId = " & iInstitutionId
    sSQL = sSQL & ", @notQueued = " & iNotQueued
      
    ' This will put the order into the PendingOrder Table, Release resources
    Set rs = oData.ExecSql(sSQL, PROVIDER, GetDSN(), True, False)
    
    ' The Stored Procedure should always return back a confirmation Number
    lConfirmNumber = CLng(Trim(rs("confirmationNumber") & ""))
    
    ' Release resources early
    rs.Close
    
    Set rs = Nothing
     
    ' Send the Confirmation Number back to the market.
    ' NOTE: At some point (perhaps by Win2000 release) it may be possible to send a
    ' notification ref back to the calling Institution. For now,
    ' an Institution Id is used to direct the notification to
    ' the correct Institution (only one institution in this case).
    
    ' The order of messages read in the message queue are not predictable since
    ' different threads may work at different rates in this queued scenario.
    ' It is therefore possible for the IMarketFloor (activated by HBFeed) to find this (MARKET) order in the database
    ' (just added it above) and respnd by sending a FILLED notice to HBNotify "BEFORE"
    ' a "CONFIRMATION" for this same order has been sent.
    ' This is resolved by "assuming" that a FILLED order received by HBInstitution is "proof"
    ' of a prior received market CONFIRMED order. (See HBInstitution.IAccount.UpdateHoldingStatus)
    
    If bQueued = True Then
        Set oNotify = CreateObject("queue:/new:HBNotify.INotify")
    Else
        ' No transactional context is required to flow, use CreateObject
        Set oNotify = CreateObject("HBNotify.INotify")
    End If
    
    ' And notify the institute (fire and forget)
    Call oNotify.ProcessConfirmation(lOrderId, iInstitutionId, lConfirmNumber)
    
    ' Call IMarketFloor to determine if order can be FILLED at the
    ' current price. The is needed for a MARKET order as well as a LIMIT order with a 'current'
    ' limit price.
     
    Set oQuote = New HBExchange.IQuote

    ' Make a quick read from IMDB
    rc = oQuote.RetrieveEx(strSymbol, dQuoteTime, cBidPrice, cAskPrice, dLastTradeTime, cLastTradePrice, dNetChange, cDailyHigh, cDailyLow, lAskSize, lBidSize, cOpenPrice, cClosePrice, dCloseDate, sMsg)
    
    If rc = SUCCESS Then
        ' Does not need to participate in transaction. If this fails (assuming no exception) then transaction is still valid
        ' Transaction only requires that HBExchange has entered the order in its PendingOrders table
        Set oMarketFloor = New HBExchange.IMarketFloor
        
        ' See if there is a match at the current price
        rc = oMarketFloor.GetMatchingTrades(strSymbol, cBidPrice, cAskPrice, cLastTradePrice, iQuantity, lBidSize, sMsg)
        ' Ignore return value
    End If
    
    ' The order has been entered successfully, we are happy
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
    
    Exit Sub
    
ErrorHandler:

    If Not oMarketFloor Is Nothing Then
        Set oMarketFloor = Nothing
    End If
    
    If Not oQuote Is Nothing Then
        Set oQuote = Nothing
    End If
    
    If Not rs Is Nothing Then
        Set rs = Nothing
    End If
    
    If Not oData Is Nothing Then
        Set oData = Nothing
    End If
    
    ' if we have a Context then Abort
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    ' Do not raise an Error to the Calling Argument
    LogError "IExchangeOrder.EnterOrder. SQL = " & sSQL, False
    
End Sub
