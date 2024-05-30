VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 1  'NoTransaction
END
Attribute VB_Name = "IXMLAccout"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
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

Public Function GetXMLAccounts(ByVal sSSN As String, ByRef sMsg As String) As XMLDSOControl
    
    ' Build the XML Document
    On Error GoTo ErrorHandler
    
    ' Data Base declarations
    Dim cn As New ADODB.Connection
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
    rsAcc.MoveFirst
    
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
            Set xmlChild = XMLCtrl.XMLDocument.createNode("element", rsAcc.Fields(nAccCount).Name, "")
            
            ' Check for NULL fields
            xmlChild.Text = ValidateFieldIndex(rsAcc, nAccCount)
            If rsAcc.Fields(nAccCount).Name = "acctNumber" Then
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
        If Not rsHold.BOF Then
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
    
    Set GetXMLAccounts = XMLCtrl
    
    GetObjectContext.SetComplete
    
    Exit Function
    
ErrorHandler:
Resume Next
    If Not XMLCtrl Is Nothing Then
        Set XMLCtrl = Nothing
    End If
    
    If Not cn Is Nothing Then
        Set cn = Nothing
    End If
    
    GetObjectContext.SetAbort
    
    sMsg = LogErrorStr("ICustomer.GetXMLAccounts")
    
End Function

Private Function ValidateField(ByRef oRecordSet As Recordset, strFieldVal As String) As String
    If oRecordSet(strFieldVal) <> "" Then
        ValidateField = oRecordSet(strFieldVal)
    Else
        ValidateField = ""
    End If
End Function

Private Function ValidateFieldIndex(ByRef oRecordSet As Recordset, ByVal strFieldIndex As Long) As String
    If oRecordSet.Fields(strFieldIndex) <> "" Then
        ValidateFieldIndex = oRecordSet.Fields(strFieldIndex)
    Else
        ValidateFieldIndex = ""
    End If
End Function

Public Function GetXMLStrAccounts(ByVal sSSN As String, ByRef sMsg As String) As String
    
    ' Build the XML Document
    On Error GoTo ErrorHandler
    
    Dim strXMLStream As String
    
    ' XML declarations
    Dim XMLCtrl As XMLDSOControl
    
    
    Set XMLCtrl = GetXMLAccounts(sSSN, sMsg)
                           
    strXMLStream = XMLCtrl.XMLDocument.xml
    
    GetXMLStrAccounts = strXMLStream
    
    GetObjectContext.SetComplete
    
    Set XMLCtrl = Nothing
    
    Exit Function
    
ErrorHandler:

    If Not XMLCtrl Is Nothing Then
        Set XMLCtrl = Nothing
    End If
    
    GetObjectContext.SetAbort
    
    sMsg = LogErrorStr("ICustomer.GetXMLAccounts")
    
End Function

