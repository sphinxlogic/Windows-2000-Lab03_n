VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 1  'NoTransaction
END
Attribute VB_Name = "IMarketFloor"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Attribute VB_Ext_KEY = "RVB_UniqueId" ,"373680CF0177"
'/***********************************************************************************\
'*************************************************************************************
'*  COM+ Hanson Brothers SDK Sample
'*  Class IMarket (HBExchange)
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

Public Function GetMatchingTrades(ByVal sSymbol As String, ByVal cBidPrice As Currency, ByVal cAskPrice As Currency, ByVal cLastPrice As Currency, ByVal lAskSize As Long, ByVal lBidSize As Long, ByRef sMsg As Variant) As Long
  
    ' PURPOSE: Match orders pending in the PendingTrades dB table with
    ' quotes. Anytime a quote (symbol) changes, IIQuoteUpdate.Update calls this method.
    ' The marketFloor responds by checking the pendingTrades table to see if
    ' any orders (market or limit) meet price or (eventually) quantity
    ' criterias.
    
    ' NOTE: This is probably one of the most critical areas of Hanson Brothers and requireds the
    ' most error detection, i.e., what to do if the order is processed as sent to HBInstitution
    ' via HBNotify as being filled but is unable to change the status of the pending record.
    ' Or, what to do if the status IS changed in Pending but is not reflected in the HBInstitution
    ' holding record. The first problem is not known to occur within HB, the later can.
    ' For it's possible for HBExchange to mark the order as SETTLED and HBInstitution not being
    ' able to update it's holding record. This will result in (say) a PENDING Market order from the
    ' client during HIGH contention scenarios (Placing multiple orders for the same Account and same symbol)
    ' One way to deal with this is to have HBInstitution do conflict resolution at the end of the (during
    ' Reconciliation.
    
    ' Future: A more direct coding solution below (left for the reader) is to write a SPROC
    ' to read and update the record in TSQL, returning the rs and queuing the results to
    ' HBNotify.
    
    Dim rs As ADODB.Recordset
    Dim oData As HBExchange.DataLayer
    Dim sSQL As String
    Dim retval As Long
    Dim oINotify As Object
    
    Dim iInstitutionId As Integer
    Dim sAcctNum As String
    Dim iAction As Integer
    Dim iQuantity As Integer
    Dim iTradeType As Integer
    Dim iConfirmNumber As Integer
    Dim cValue As Currency
    Dim iNotQueued As Integer
    Dim iOrderId As Integer
    Dim num As Integer
    
    GetMatchingTrades = FAILED
    
    On Error GoTo ErrorHandler
    
    Set oData = New HBExchange.DataLayer
 
    sSQL = "SELECT * FROM PendingTrades WHERE symbol = '" & sSymbol & "'" & " AND status = " & CONFIRMED & " AND "
    sSQL = sSQL & " ( tradeType = " & LIMIT_ORDER & " AND (( action = " & BUY & " AND limitPrice >= " & cAskPrice
    sSQL = sSQL & " ) OR ( action = " & SELL & " AND limitPrice <= " & cBidPrice & ")"
    sSQL = sSQL & " ) OR ( " & " tradeType = " & MARKET_ORDER & " )) "
    
    Set rs = oData.ExecSql(sSQL, PROVIDER, GetDSN(), True, True)
    
    num = 0
    
    If Not (rs.BOF And rs.EOF) Then
       
        iNotQueued = rs("notQueued")
        
        If iNotQueued = 1 Then
            Set oINotify = CreateObject("HBNotify.INotify")
        Else
            Set oINotify = GetObject("queue:/new:HBNotify.INotify")
        End If
    
        ' May Have Multiple Order Hits
        While Not rs.EOF
        
            iInstitutionId = rs("institutionId")
            sAcctNum = rs("acctNum")
            iAction = rs("action")
            iQuantity = rs("quantity")
            iTradeType = rs("tradeType")
            iConfirmNumber = rs("ConfirmationNumber")
            iOrderId = rs("orderId")
            
            If num = 0 Then
                ' Build SQL string instead of ADO BatchUpdate
                sSQL = "Update pendingTrades Set status = " & SETTLED & " WHERE symbol = '" & sSymbol & "' AND status = " & CONFIRMED & " AND ( orderId = " & iOrderId
            Else
                sSQL = sSQL & " OR orderId = " & iOrderId
            End If
            
            If iAction = BUY Then  ' Buy at the ask price
             
                cValue = iQuantity * cAskPrice
                
                Call oINotify.ProcessSettlement(iInstitutionId, sAcctNum, iOrderId, iAction, iQuantity, cAskPrice, iTradeType, iConfirmNumber, cValue)
                
            ElseIf iAction = SELL Then ' Sell At the bidPrice

                cValue = iQuantity * cBidPrice
                
                Call oINotify.ProcessSettlement(iInstitutionId, sAcctNum, iOrderId, iAction, iQuantity, cBidPrice, iTradeType, iConfirmNumber, cValue)
                
            End If
            
            num = num + 1
            
            rs.MoveNext
        Wend
        
        rs.Close
    
        Set rs = Nothing
        
        ' If no Failures, then update batch
        If num > 0 Then
            Set rs = oData.ExecSql(sSQL & " )", PROVIDER, GetDSN(), True, False)
        End If
        
    End If
       
    GetMatchingTrades = SUCCESS
    
    ' All orders that are able to be processed have been processed. If any fail (exception thrown)
    ' call, Then all (these) Processed orders are aborted.
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
      
    Exit Function
    
ErrorHandler:
    
    If Not oINotify Is Nothing Then
        Set oINotify = Nothing
    End If
    
    If Not rs Is Nothing Then
        Set rs = Nothing
    End If
    
    If Not oData Is Nothing Then
        Set oData = Nothing
    End If
    
    GetMatchingTrades = FAILED
  
    ' if we have a Context then Abort
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    sMsg = LogErrorStr("IMarketFloor.GetMatchingTrades. SQL = " & sSQL)
    
End Function

