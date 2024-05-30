VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 4  'RequiresNewTransaction
END
Attribute VB_Name = "IOrder"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Attribute VB_Ext_KEY = "RVB_UniqueId" ,"37367D240128"
'/***********************************************************************************\
'*************************************************************************************
'*  COM+ Hanson Brothers SDK Sample
'*  Class IOrder (HBInstitution)
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

Public Function Execute1(ByVal sSSN As String, ByVal sAcctNum As String, ByVal sSymbol As String, ByVal iQuantity As Integer, ByVal cLimitPrice As Double, ByVal cBidPrice As Double, ByVal cAskPrice As Double, ByVal iAction As Integer, ByVal iTradeType As Integer, ByRef lConfirmationNumber As Long, ByVal bQueued As Boolean, ByRef sMsg As Variant) As Long

    'App.LogEvent "Execute1: SSN=" & sSSN & ", Acct=" & sAcctNum & ", Symbol=" & sSymbol & ", Quantity=" & iQuantity & ", LimitPrice=" & cLimitPrice & ", BidPrice=" & cBidPrice & ", AskPrice=" & cAskPrice & ", Action=" & iAction & ", TradeType=" & iTradeType & ", ConfirmNum=" & lConfirmationNumber & ", Queued=" & bQueued & ", sMsg=" & sMsg & ""
 
    Execute1 = Execute(sSSN, sAcctNum, sSymbol, iQuantity, cLimitPrice, cBidPrice, cAskPrice, iAction, iTradeType, lConfirmationNumber, bQueued, sMsg)
    
End Function

 
' The Order Component should "Require New" transaction. In the case of
' the Execute method, the Order and Account component needs to update the holding table
' and the .IMarketFloor component needs to successfully queue up
' before the order transaction can be considered successful.
Public Function Execute(ByVal sSSN As String, ByVal sAcctNum As String, ByVal sSymbol As String, ByVal iQuantity As Integer, ByVal cLimitPrice As Currency, ByVal cBidPrice As Currency, ByVal cAskPrice As Currency, ByVal iAction As Integer, ByVal iTradeType As Integer, ByRef lConfirmationNumber As Variant, ByVal bQueued As Boolean, ByRef sMsg As Variant) As Long
    
   ' Execute will go through (again) the verification again (since there may be a long time
   ' between when the user Verifies and Executes. Yes - There was an opportunity to
   ' code reuse
                  
    Dim sSQL As String
    Dim lNumRecs As Long
    Dim ssn As String
    Dim dSettlementDate As Date
    Dim iOrderStatus As Integer
    Dim cValue As Currency
    Dim iShares As Integer
    Dim cCommissionTotal As Integer
    
    Dim sngCost As Currency
    Dim sngCommission As Currency
    Dim sFullName As String
    
    Dim oQuote As HBExchange.IQuote
    Dim oAcct As HBInstitution.IAccount
    Dim oMarketOrder As HBExchange.IExchangeOrder
    Dim oData As DataLayer
    Dim rs As ADODB.Recordset
    Dim rc As Long
    
    Dim cNetWorth As Currency
    Dim cCash As Currency
    Dim cCashDebit As Currency
    Dim cCashDebitTotal As Currency
    Dim lOrderId As Long
    Dim iInstitutionId As Integer
    
        
    sMsg = "Unknown Failure"
    
    On Error GoTo ErrorHandler
     
    If cBidPrice <= 0 Or cAskPrice <= 0 Then
        sMsg = "Market Quotes Are not Available. Please try again"
        GoTo ErrorHandler
    End If
    
    If iQuantity <= 0 Then
        sMsg = "Amount of Shares is Less than or Equal to Zero. Please Enter Share Value > 0"
        GoTo ErrorHandler
    End If
   
    Dim cn As ADODB.Connection
    
    If Not GetObjectContext Is Nothing Then
        Set oAcct = GetObjectContext.CreateInstance("HBInstitution.IAccount")
    Else
        Set oAcct = CreateObject("HBInstitution.IAccount")
    End If
    
    If iAction = BUY Then
        
        rc = oAcct.GetAccountNetWorth(sAcctNum, cNetWorth, cCash, cCashDebitTotal, sMsg)
    
        ' Calculate cash available for purchasing
        cCash = cCash - cCashDebitTotal 'cCashDebitTotal is a positive value
     
        If rc <> SUCCESS Then
            If rc = NO_RECORDS_FOUND Then
                sMsg = "Cannot Get Account Information Upon Execution of Order"
            End If
            GoTo ErrorHandler
        End If
        
        If iTradeType = LIMIT_ORDER Then
            sngCost = iQuantity * cLimitPrice
            sngCommission = sngCost * COMMISSION_PERCENTAGE
            cCashDebit = sngCommission + sngCost
            
            If cCash < cCashDebit Then
                sMsg = "You do not have enough Available Cash to make this trade." & vbCrLf & vbCrLf & "Please adjust your order." & vbCrLf & vbCrLf & "Cash Available = " & cCash & vbCrLf & "Order Cost = " & cCashDebit
                GoTo ErrorHandler
            End If
            
        ElseIf iTradeType = MARKET_ORDER Then
            sngCost = iQuantity * cAskPrice
            sngCommission = sngCost * COMMISSION_PERCENTAGE
            cCashDebit = sngCommission + sngCost
            
            If cCash < cCashDebit Then
                sMsg = "You do not have enough Available Cash to make this Market Order at the current Ask Price of $" & cAskPrice & vbCrLf & vbCrLf & "Please adjust order." & vbCrLf & vbCrLf & "Cash Available = $" & cCash & vbCrLf & "Order Cost = $" & cCashDebit
                GoTo ErrorHandler
            End If
        End If
        
    Else ' SELL ORDER
    
        ' NOTE: Cash is not credited until order reconciliation
              
        ' Check to make sure there are enough shares in this account to sell
        
        rc = oAcct.GetHoldingSummary(sAcctNum, sSymbol, iShares, cCommissionTotal, cValue, dSettlementDate, sSSN, sMsg)
           
        If rc <> SUCCESS Then
            If rc = NO_RECORDS_FOUND Then
                  sMsg = "You do Not Have Enough shares of " & sSymbol & " To Sell"
            Else
                  sMsg = "Execute Problem: Unable to get Holding Summary: " & sMsg
            End If
             If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
            Exit Function
        End If
             
        If iShares < iQuantity Then
                sMsg = "The Number of " & sSymbol & " shares to Sell Now exceeds the Number of shares (" & iShares & ") in your IAccount. "
                GoTo ErrorHandler
        End If
        
        cCashDebit = sngCost * COMMISSION_PERCENTAGE ' Only Commission debit on a Sell
    
    End If
    
    'Recalculate the account cashDebitTotal
    
    cCashDebitTotal = cCashDebitTotal + cCashDebit
        
    ' Update Cash regardless if order has been confirmed by Market
    rc = oAcct.UpdateAcctCashDebit(sAcctNum, cCashDebitTotal, sMsg)
    
    If rc <> SUCCESS Then
            GoTo ErrorHandler
    End If
    
    sSQL = "EXEC sp_InsertHolding"
    sSQL = sSQL & "  @acctNumber = '" & sAcctNum & "'"
    sSQL = sSQL & ", @tradeType = " & iTradeType
    sSQL = sSQL & ", @symbol = '" & sSymbol & "'"
    sSQL = sSQL & ", @quantity = " & iQuantity
    sSQL = sSQL & ", @confirmationDate = NULL"
    sSQL = sSQL & ", @commision = " & 0 ' No Commission until order is filled
    sSQL = sSQL & ", @check_number = NULL"
    sSQL = sSQL & ", @value = " & 0
    sSQL = sSQL & ", @confirmationNumber = " & 0
    sSQL = sSQL & ", @orderStatus = " & ICONFIRMED
    sSQL = sSQL & ", @acknowledged = " & NOT_ACKNOWLEDGED
    sSQL = sSQL & ", @settlementDate = NULL"
    sSQL = sSQL & ", @reconcileDate = NULL"
    sSQL = sSQL & ", @action = " & iAction
    sSQL = sSQL & ", @limitPrice = " & cLimitPrice
    sSQL = sSQL & ", @ssn = '" & sSSN & "'"
    sSQL = sSQL & ", @settledPrice = " & 0
    sSQL = sSQL & ", @submissionDate = '" & FormatDateTime(Now(), vbGeneralDate) & "'"
    
    Set oData = New HBInstitution.DataLayer


    Set rs = oData.ExecSql(sSQL, PROVIDER, GetDSN(), True, False)
    
    ' The Stored Procedure will always return back a order Id Number
    lOrderId = CLng(Trim(rs("orderId") & ""))
    
    If lOrderId <= 0 Then
        GoTo ErrorHandler
    End If

    ' Release the record set (locks) to avoid record contention when the order is later
    ' processed, filled, and updated (you will especially see this if you serialize the
    ' order (i.e., choose no-queuing option found in the HBTradeStation (Client) Settings Tab
    rs.Close
    
    ' The order has been logged in the holdings and has been sent to the market pending confirmation
    ' Last thing to do is send the order to the trading floor
    
    iInstitutionId = HB_INSTITUTION_ID
    
    'QC ISSUES: Supports the following MSMQ properties:
    '   AppSpecific: App-specific info attached to msg. Default = none
    '   AuthLevel:  Specifies whether MSMQ out-going msgs are authenticated by attaching digital certificates. Default = Derived from server app info installed on client.
    '   ComputerName:   Name of computer recipient queue resides. Default=same as above
    '   Delivery:   Whether MSMQ msgs are always committed to disk for reliability while in transit (recoverable)or kept in RAM for sped (express). Default = Recoverable
    '   EncryptAlgorithm:   Algorithm used if sending private msg. Default=MSMQ default
    '   FormatName: Format name of Queue. Default=MSMQ Default
    '   HashAlgorithm: Algorithm used for computing checksum to verify msg hasn't been altered. Default=MSMQ default
    '   Journal:    Journaling level of queue. Default=MSMQ default
    '   Label:  Human Readable string attached to msg. Default=MSMQ default
    '   MaxTimeToReachQueue:    Time after which msg is deleted if it hasn't already reached the queue on the recipient machine. Default=Infinite
    '   MaxTimeToReceive:   Time after which the msg is deleted if it hasn't been read from the queue on the receiving app. Default=Infinite
    '   PathName:   Full pathname to the recipient queue. Default=Derived from Server app info installed on client
    '   Priority:   Priority level of sent msgs, level 1-7. Default=NSNQ ignores priority for transacted queues
    '   PrivLevel:  Msgs level of privacy. Determines whether message is encrypted. Default=MSMQ default
    '   QueueName:  Name of destination queue on recipient machine. Default=MSMQ default
    '   Trace:  Specifies whether to generate response messages tracing a msgs path through the MSMQ enterprise network. Default=Off
    
    ' Hanson Brothers can encrypt the order by setting the PrivLevel Attribute to: MSMQ_PRIV_LEVEL_BODY
    ' Example: CreateObject("queue:PrivLevel=MSMQ_PRIV_LEVEL_BODY/new:HBExchange.IExchangeOrder")
        
    If bQueued = True Then
        Set oMarketOrder = CreateObject("queue:/new:HBExchange.IExchangeOrder")
    Else
        Set oMarketOrder = CreateObject("HBExchange.IExchangeOrder")
    End If
    
    ' And enter the order
    Call oMarketOrder.EnterOrder(sSSN, sAcctNum, sSymbol, iAction, iQuantity, cLimitPrice, iTradeType, lOrderId, iInstitutionId, bQueued)
     
    'If no errors than return the intitutional confirmation number
    
Done:
    lConfirmationNumber = lOrderId

    Execute = SUCCESS

    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
    
    Exit Function
    
ErrorHandler:

    If Not rs Is Nothing Then
        Set rs = Nothing
    End If
    
    If Not cn Is Nothing Then
        Set cn = Nothing
    End If
    
    If Not oAcct Is Nothing Then
        Set oAcct = Nothing
    End If
    
    If Not oMarketOrder Is Nothing Then
        Set oMarketOrder = Nothing
    End If
    
    If Not oData Is Nothing Then
        Set oData = Nothing
    End If
     
    lConfirmationNumber = 0
    
    Execute = FAILED

    ' if we have a Context then Abort
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    sMsg = LogErrorStr("IOrder.Execute " & sMsg & "SQL = " & sSQL)
    
End Function


Public Function Verify(ByVal sAcctNum As String, ByVal sSymbol As String, ByVal iQuantity As Double, ByVal cLimitPrice As Variant, ByVal cBidPrice As Variant, ByVal cAskPrice As Variant, ByVal iAction As Integer, ByVal iTradeType As Integer, ByRef sMsg As Variant) As Long

   ' Verify that the user has enough funds or owned shares to make the trade.
   ' Future Change: Common parts of Verify and Execute to be rolled in together
 
    Verify = FAILED
    sMsg = "Unknown Failure"
    
    On Error GoTo ErrorHandler
                    
    Dim sSQL As String
    Dim lNumRecs As Long
    Dim ssn As String
    Dim iCommision As Currency
    Dim iConfirmNumber As Integer
    Dim dSettlementDate As Date
    Dim iOrderStatus As Integer
    Dim cValue As Currency
    Dim iShares As Integer
    Dim cCommissionTotal As Integer
    
    Dim sngCost As Currency
    Dim sngCommission As Currency
    Dim sFullName As String
    
    Dim oQuote As HBExchange.IQuote
    Dim oAcct As HBInstitution.IAccount
    Dim oMarketOrder As HBExchange.IMarketFloor
    Dim rc As Long
    
    Dim cNetWorth As Currency
    Dim cCash As Currency
    Dim cCashDebit As Currency
    Dim cCashCredit As Currency
    Dim cCashDebitTotal As Currency
    
    Dim sSSN As String
    
    If cBidPrice <= 0 Or cAskPrice <= 0 Then
        sMsg = "Market Quotes Are not Available. Please try again"
         If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
        Exit Function
    End If
    
    If iQuantity <= 0 Then
        sMsg = "Amount of Shares is Less than or Equal to Zero. Please Enter Share Value > 0"
         If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
        Exit Function
    End If
   
    Dim cn As ADODB.Connection
    
    If Not GetObjectContext Is Nothing Then
        Set oAcct = GetObjectContext.CreateInstance("HBInstitution.IAccount")
    Else
        Set oAcct = CreateObject("HBInstitution.IAccount")
    End If
    
    If iAction = BUY Then
        
        rc = oAcct.GetAccountNetWorth(sAcctNum, cNetWorth, cCash, cCashDebitTotal, sMsg)
    
        ' Calculate cash available for purchasing
        cCash = cCash - cCashDebitTotal
     
        If rc <> SUCCESS Then
            If rc = NO_RECORDS_FOUND Then
                sMsg = "Cannot Get Account Information Upon Execution of Order"
            End If
            If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
            Exit Function
        End If
        
        ' Future Change: Commissions are to be computed in Reconcile using Settled priceas opposed to
        ' the AskPrice (For MARKET Orders)
        
        If iTradeType = LIMIT_ORDER Then
            sngCost = iQuantity * cLimitPrice
            sngCommission = sngCost * COMMISSION_PERCENTAGE
            cCashDebit = sngCommission + sngCost
            
            If cCash < cCashDebit Then
                sMsg = "You do not have enough Available Cash to make this trade." & vbCrLf & vbCrLf & "Please adjust your order." & vbCrLf & vbCrLf & "Cash Available = " & cCash & vbCrLf & "Order Cost = " & cCashDebit
                If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
                Exit Function
            Else
               sMsg = "Please Confirm Order." & vbCrLf & vbCrLf & "Buy " & iQuantity & " Shares of " & sSymbol & ": " & sFullName & vbCrLf & "At Limit Price = $" & cLimitPrice & vbCrLf & vbCrLf & "Cost = $" & sngCost & vbCrLf & "Estimated Commission = $" & sngCommission & vbCrLf & "Total Cost = $" & cCashDebit
            End If
            
        ElseIf iTradeType = MARKET_ORDER Then
            sngCost = iQuantity * cAskPrice
            sngCommission = sngCost * COMMISSION_PERCENTAGE
            cCashDebit = sngCommission + sngCost
            
            If cCash < cCashDebit Then
                sMsg = "You do not have enough Available Cash to make this Market Order at the current Ask Price of $" & cAskPrice & vbCrLf & vbCrLf & "Please adjust order." & vbCrLf & vbCrLf & "Cash Available = $" & cCash & vbCrLf & "Order Cost = $" & cCashDebit
                If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
                Exit Function
            Else
               sMsg = "Please Confirm Order." & vbCrLf & vbCrLf & "BUY " & iQuantity & " Shares of " & sSymbol & ": " & sFullName & vbCrLf & vbCrLf & "Estimated Cost = $" & sngCost & vbCrLf & "Estimated Commission = $" & sngCommission & vbCrLf & "Total Estimated Cost = $" & cCashDebit
            End If
        End If
        
    Else ' SELL ORDER
    
        ' NOTE: Cash is not credited until order reconciliation
              
        ' Check to make sure there are enough shares in this account to sell
        
        rc = oAcct.GetHoldingSummary(sAcctNum, sSymbol, iShares, cCommissionTotal, cValue, dSettlementDate, sSSN, sMsg)
           
        If rc <> SUCCESS Then
            If rc = NO_RECORDS_FOUND Then
                  sMsg = "You do Not Have Enough shares of " & sSymbol & " To Sell"
            Else
                  sMsg = "Execute Problem: Unable to get Holding Summary: " & sMsg
            End If
            If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
            Exit Function
        End If
             
        If iShares < iQuantity Then
                sMsg = "The Number of " & sSymbol & " shares to Sell Now exceeds the Number of shares (" & iShares & ") in your IAccount. "
                If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
                Exit Function
        End If
        
        If iTradeType = LIMIT_ORDER Then
            
            sngCost = iQuantity * cLimitPrice
            sngCommission = sngCost * COMMISSION_PERCENTAGE
            cCashCredit = sngCost - sngCommission

            sMsg = "Please Confirm Order." & vbCrLf & vbCrLf & "SELL " & iQuantity & " Shares of " & sSymbol & ": " & sFullName & vbCrLf & vbCrLf & "At Limit Price = $" & cLimitPrice & vbCrLf & vbCrLf & "Estimated Value = $" & sngCost & vbCrLf & "Commision = $" & sngCommission & vbCrLf & "Total Estimated Value = $" & cCashCredit

        ElseIf iTradeType = MARKET_ORDER Then

            sngCost = iQuantity * cBidPrice
            sngCommission = sngCost * COMMISSION_PERCENTAGE
            cCashCredit = sngCost - sngCommission

            sMsg = "Please Confirm Order." & vbCrLf & vbCrLf & "SELL " & iQuantity & " Shares of " & sSymbol & ": " & sFullName & vbCrLf & vbCrLf & "Market Bid Price = $" & cBidPrice & vbCrLf & vbCrLf & "Estimated Value = $" & sngCost & vbCrLf & "Commision = $" & sngCommission & vbCrLf & "Total Estimated Value = $" & cCashCredit
              
        End If
    
    End If
        
    Verify = SUCCESS
    
    ' If we have a Context the SetComplete
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
    
    Exit Function
    
ErrorHandler:

    If Not oAcct Is Nothing Then
        Set oAcct = Nothing
    End If
    
    If Not oMarketOrder Is Nothing Then
        Set oMarketOrder = Nothing
    End If
    
    If Not oQuote Is Nothing Then
        Set oQuote = Nothing
    End If
    
    Verify = FAILED
 
    ' if we have a Context then Abort
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    sMsg = LogErrorStr("IOrder.Verify " & sMsg)

End Function


Public Function Acknowledge(ByVal iConfirmNumber As Integer, ByRef sMsg As Variant) As Long

    Acknowledge = FAILED
    
    On Error GoTo ErrorHandler
                    
    ' Declare
    Dim oData As DataLayer
    Dim sSQL As String
    Dim lNumRecs As Long
        
    ' Create ADO Objects
    Set oData = New HBInstitution.DataLayer
    
    sSQL = "update holding set acknowledged = 1 where orderId = " & iConfirmNumber
    
    Call oData.ExecSql(sSQL, _
                       PROVIDER, _
                       GetDSN(), _
                       False)
    
    Acknowledge = SUCCESS
    
    sMsg = "Order Acknowledgement Set"
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
    
    Exit Function
    
ErrorHandler:
    
    If Not oData Is Nothing Then
        Set oData = Nothing
    End If
    
    Acknowledge = FAILED
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    sMsg = LogErrorStr("IOrder.Acknowledge " & sMsg)

End Function

