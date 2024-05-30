Attribute VB_Name = "Module1"
'/***********************************************************************************\
'*************************************************************************************
'*  COM+ Hanson Brothers SDK Sample
'*  Module Module1 (HBTradeStation)
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
'Option Explicit

Public customerSSN As String
Public customerType As Integer
Public CustLoginSucceeded As Boolean
Public nakTrades As Variant
Public alerts As Variant

Global m_objCust As HBInstitution.ICustomer
Global m_objAcct As HBInstitution.IAccount
Global m_objQuote As HBExchange.IQuote
Global m_objOrder As HBInstitution.IOrder
Global m_XMLDOM As DOMDocument

Global m_bQueued As Boolean
Global m_bNewsOk As Boolean
Global m_bStopQuote As Boolean

Global m_qNames() As String

Global m_bStartAllObjects As Boolean
Global m_bUseXML As Boolean

Public Sub ReceiveNewsHeadlines(ByVal sNews As String)

    MsgBox ("News Received " & sNews)
    
End Sub

Public Function HandleError(ByVal str As String)

    Dim sLogErr As String
    Dim rc As Variant
    Dim LogErrorStr As String
    
    LogErrorStr = "HBTradeStation Error"
    
    If Not Err Is Nothing Then
        sLogErr = "HBTradeStation Exception." & str & ":  ErrNum: " & Err.Number & "  Desc: " & Err.Description
    End If
    
    App.LogEvent sLogErr, vbLogEventTypeError
    
    If MsgBox("" & sLogErr & " Do you want to Continue?", vbYesNo, "HBTradeStation Exception Window") = vbNo Then
        End
    End If
    
End Function

Public Sub LogInfo(ByVal sMsg As String)

    Dim sLogInfo As String
    
    sLogInfo = "HBExchange." & sMsg
    
    App.LogEvent sLogInfo, vbLogEventTypeInformation
    
End Sub


Sub DeactivateAllObjects()

    If Not m_objCust Is Nothing Then
        Set m_objCust = Nothing
    End If
    If Not m_objAcct Is Nothing Then
        Set m_objAcct = Nothing
    End If
    If Not m_objQuote Is Nothing Then
        Set m_objQuote = Nothing
    End If
    If Not m_objOrder Is Nothing Then
        Set m_objOrder = Nothing
    End If
    
End Sub
Sub ActivateAllObjects()

    If m_bStartAllObjects = True Then
    
        Call DeactivateAllObjects
        
        Set m_objCust = New HBInstitution.ICustomer
        Set m_objAcct = New HBInstitution.IAccount
        Set m_objQuote = New HBExchange.IQuote
        Set m_objOrder = New HBInstitution.IOrder
    End If

End Sub


Sub Main()
   
   On Error GoTo ErrorHandler
   
   ' Set Default Startup Values
   
   frmMainProfile.Enabled = False
   
   frmMainProfile.TransientCBut.Value = 1

   frmMainProfile.TestTEd.Visible = False
   frmMainProfile.TestLabel.Visible = False
   frmMainProfile.LoopText.Visible = False
   frmMainProfile.ReAuthenticateTBUT.Visible = False
   frmMainProfile.StopCBut.Visible = False
   frmMainProfile.TestCBut.Visible = False
   frmMainProfile.TestTEd.Visible = False
   frmMainProfile.TestLabel.Visible = False
   frmMainProfile.ODBCCBut.Visible = False
   frmMainProfile.PersistCBut.Visible = False
   frmMainProfile.LoopCBut.Visible = False
   frmMainProfile.LoopText.Visible = False
   frmMainProfile.chtReport.Visible = False
   
   frmMainProfile.CustomerCombo.Clear
   
   frmMainProfile.TestTEd.Text = 0
   frmMainProfile.TestCBut.Value = 0
   
   frmMainProfile.CCBut.Value = 1
   frmMainProfile.ViewTEd.Visible = False
   frmMainProfile.NTEd.Visible = False
   frmMainProfile.NLabel.Visible = False
   
   customerType = NO_CUSTOMER_TYPE
   
   m_bStartAllObjects = ACTIVATE_ALL_OBJECTS_ON_STARTUP
   
   m_bQueued = QUEUED_ON_STARTUP
   
   m_bUseXML = USE_XML_ON_STARTUP
   
   m_bStopQuote = False
   
   If m_bUseXML = True Then
        frmMainProfile.chkXML = 1
   Else
        frmMainProfile.chkXML = 0
   End If

   m_bNewsOk = True

    If m_bStartAllObjects = True Then
        frmMainProfile.ObjectCBut.Value = 1
        Call ActivateAllObjects
    Else
        frmMainProfile.ObjectCBut.Value = 0
    End If
    
    If m_bQueued = True Then
        frmMainProfile.QueueCBut.Value = 1
    Else
        frmMainProfile.QueueCBut.Value = 0
    End If
    
    EnableForm (False)
    
    frmMainProfile.TradeText.Text = ""
  
    frmMainProfile.Show
    frmLogin.Show 1
    
    If CustLoginSucceeded = True Then
        frmMainProfile.Enabled = True
        If Not customerSSN = "000000000" Then
            Call frmMainProfile.FillCustomer(customerSSN)
            Call FillForm
            RunTicker
        End If
    Else
        End
    End If
    
    Exit Sub

ErrorHandler:
    HandleError ("General HBTradeStation Exception")
    Resume Next
End Sub

Sub EnableForm(ByVal bEnable As Boolean)

    
    If bEnable = False Then
        frmMainProfile.QuoteTimer.Enabled = False
        frmMainProfile.HBut.Visible = False
        frmMainProfile.SSTab1.TabEnabled(0) = False
        frmMainProfile.SSTab1.TabEnabled(1) = False
        frmMainProfile.SSTab1.TabEnabled(2) = False
        frmMainProfile.SSTab1.TabEnabled(3) = False
        frmMainProfile.SSTab1.TabEnabled(4) = False
        frmMainProfile.SSTab1.TabEnabled(5) = True
        frmMainProfile.AccountFlexGrid.Visible = False
        frmMainProfile.AccountFlexGrid2.Visible = False
        frmMainProfile.HoldingFGrid.Visible = False
        frmMainProfile.PendingFlxGrid.Visible = False
        frmMainProfile.HistoryFGrid.Visible = False
        frmMainProfile.ConfirmFrame.Visible = False
        frmMainProfile.TradeFrame.Visible = False
        frmMainProfile.ConfirmTBUT.Enabled = False
        frmMainProfile.ReportTBUT.Visible = False
        frmMainProfile.SettleTBUT.Visible = False
        frmMainProfile.SettleTED.Visible = False
        frmMainProfile.Label1.Visible = False
    
    Else
        frmMainProfile.QuoteTimer.Enabled = True
        frmMainProfile.SSTab1.TabEnabled(3) = True
        frmMainProfile.AccountFlexGrid.Visible = True
        frmMainProfile.ReportTBUT.Visible = True

    End If
    
End Sub

Sub FillForm()
    
    If m_bStopQuote = True Then
        MsgBox ("You Must Enable Quotes from Settings before you can do this action.")
        Exit Sub
    End If
    
    Dim rc As Long
    Dim Customers As Variant
    Dim QuoteList As ADODB.Recordset
    Dim sMsg As String
    Dim i As Integer
    Dim cType As Integer
     
    frmMainProfile.BannerLabel.Caption = "Market Quotes Unavailable ...."
    
    frmMainProfile.CustomerCombo.Clear
    
    If customerType = REPRESENTATIVE Or customerType = TRADER Then
        If m_bStartAllObjects = False Then
            Dim objCust As New HBInstitution.ICustomer
            rc = objCust.GetCustomers(Customers, sMsg)
            Set objCust = Nothing
        Else
            rc = m_objCust.GetCustomers(Customers, sMsg)
        End If
    
        If rc = SUCCESS Then
            For i = 0 To UBound(Customers, 2)
                If customerType = REPRESENTATIVE Then
                    cType = CInt(Customers(4, i))
                    If cType <> TRADER Then
                        ' Don't show other Traders
                        frmMainProfile.CustomerCombo.AddItem (Customers(0, i))
                    End If
                Else
                    frmMainProfile.CustomerCombo.AddItem (Customers(0, i))
                End If
            Next
        End If
    Else ' CUSTOMER
        ' JUST Show This Customer
        frmMainProfile.CustomerCombo.AddItem (customerSSN)
    End If
    
    frmMainProfile.CustomerCombo.Text = customerSSN
    
    Set Customers = Nothing
    
    If m_bStartAllObjects = False Then
        Dim objQuote As New HBExchange.IQuote
        rc = objQuote.GetSymbolList(QuoteList, sMsg)
        Set objQuote = Nothing
    Else
        rc = m_objQuote.GetSymbolList(QuoteList, sMsg)
    End If
    
    frmMainProfile.QuoteCombo.Clear
    frmMainProfile.TQuoteCombo.Clear
    frmMainProfile.NewsCombo.Clear
    
    If QuoteList Is Nothing Then
        MsgBox ("Please go to Feed.exe and intialize Quote Data Before Continuing.")
    Else
        ReDim m_qNames(QuoteList.RecordCount + 1)
    End If
    
    i = 0
    If rc = SUCCESS Then
        While (Not QuoteList.EOF)
           Dim s As String
           s = QuoteList("symbol")
           frmMainProfile.QuoteCombo.AddItem (s)
           frmMainProfile.TQuoteCombo.AddItem (s)
           
           m_qNames(i) = QuoteList("fullName")
           i = i + 1
           QuoteList.MoveNext
        Wend
    End If
    
    Set QuoteList = Nothing
    
    Call SetSymbolChart
    
End Sub

Public Sub LogDebug(ByVal sMsg As String)

App.LogEvent "DEBUG: " & sMsg

End Sub

Public Sub RunTicker()
    
    Dim rc As Long
    Dim SymbolList As Variant
    Dim sTmp As String
    
    Dim sMsg As String
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
    Dim i As Integer
    
    Dim objQuote As HBExchange.IQuote
    
    On Error GoTo RunTickerErr
    
    If m_bStartAllObjects = False Then
        Set objQuote = New HBExchange.IQuote
        rc = objQuote.GetSymbolList(SymbolList, sMsg)
    Else
        rc = m_objQuote.GetSymbolList(SymbolList, sMsg)
    End If
    
    If rc <> SUCCESS Then
        sMsg = "Failed on GetSymbolList"
        GoTo Done
    End If
        
    If SymbolList.EOF Then
        sMsg = "No Symbols In Symbols DB Table"
        GoTo Done
    End If
        
    Dim symbols()
         
    symbols = SymbolList.GetRows
    
    sTmp = ""
    For i = 0 To UBound(symbols, 2)
        sSymbol = symbols(0, i)
        If i > 5 Then
            Exit For
        End If
         
        If m_bStartAllObjects = False Then
            rc = objQuote.RetrieveEx(sSymbol, QuoteTime, bidPrice, askPrice, LastTradeTime, LastTradePrice, NetChange, DailyHigh, DailyLow, askSize, bidSize, OpenPrice, ClosePrice, closeDate, sMsg)
        Else
            rc = m_objQuote.RetrieveEx(sSymbol, QuoteTime, bidPrice, askPrice, LastTradeTime, LastTradePrice, NetChange, DailyHigh, DailyLow, askSize, bidSize, OpenPrice, ClosePrice, closeDate, sMsg)
        End If
        
        If rc <> SUCCESS Then
            MsgBox "Unable  to Retrieve Ticker Quote for " & sSymbol
            GoTo Done
        End If
                
        sTmp = sTmp & "    " & Trim(sSymbol) & ": " & " ASK " & askPrice & " BID " & bidPrice & ","
    Next
        
    frmMainProfile.BannerLabel.Caption = Trim(sTmp)
  
Done:

    If m_bStartAllObjects = False Then
        Set objQuote = Nothing
    End If
    
    Set SymbolList = Nothing
    
    Exit Sub

RunTickerErr:
    ' Do nothing
    
    sTmp = "Error"
    
    GoTo Done

End Sub


Public Sub SetSymbolChart()

    Dim QuoteList As Variant
    Dim sMsg As String
    Dim rc As Long
    
    If m_bStartAllObjects = False Then
        Dim objQuote As New HBExchange.IQuote
        rc = objQuote.GetSymbolList(QuoteList, sMsg)
        Set objQuote = Nothing
    Else
        rc = m_objQuote.GetSymbolList(QuoteList, sMsg)
    End If
    
    frmMainProfile.ChartSymbolCombo.Clear
    If rc = SUCCESS Then
        While (Not QuoteList.EOF)
           Dim s As String
           s = QuoteList("symbol")
           frmMainProfile.ChartSymbolCombo.AddItem (s)
           QuoteList.MoveNext
        Wend
    End If
    
End Sub

Private Sub ChartSymbolCombo_Change()
    SetChartInfo (Trim(frmMainProfile.ChartSymbolCombo.Text))
End Sub


Public Sub SetChartInfo(ByVal sSymbol As String)

  Dim rst As Variant
  Dim dStartDate As Date
  Dim dEndDate As Date
  
  dEndDate = Now()
  
  dStartDate = DateAdd("d", -600, dEndDate)

  ' Bring Back a Large Amount of Data

  If m_bStartAllObjects = False Then
        Dim objQuote As New HBExchange.IQuote
        Set rst = objQuote.GetIntradayQuotes(sSymbol, dStartDate, dEndDate)
        Set objQuote = Nothing
  Else
        Set rst = m_objQuote.GetIntradayQuotes(sSymbol, dStartDate, dEndDate)
  End If
    
  frmMainProfile.StartCombo.Clear
  frmMainProfile.EndCombo.Clear
  
  If rst.EOF Then
    MsgBox ("Unable to get quotes for the last hour. You will need to Re-Initialize the database at Settings Tab.")
    Exit Sub
  End If
  
  While (Not rst.EOF)
    
    frmMainProfile.StartCombo.AddItem (rst("QuoteTime"))
    frmMainProfile.EndCombo.AddItem (rst("QuoteTime"))
    
    rst.MoveNext
  Wend
  
  
  Set rst = Nothing
    
End Sub


Public Function StringPad(strString As String, intPadSize As Integer, strPadCharacter As String) As String
    If Len(strString) >= intPadSize Then
        Exit Function
    End If

    If Len(CStr(strPadCharacter)) < 1 Then
        strPadCharacter = " "
    Else
        strPadCharacter = Left(strPadCharacter, 1)
    End If

    StringPad = String(intPadSize - Len(strString), strPadCharacter) & strString
End Function

Public Sub LogError(ByVal sSub As String, ByVal sMsg As String)

    Dim sLogStr As String

    sLogStr = "HBClient Error:" & sSub & " App Error:" & sMsg & " Sys Error.  Number: " & Err.Number & "  Desc: " & Err.Description & "  Source: " & Err.Source
    App.LogEvent sLogStr

End Sub


Public Sub LogWarning(ByVal sSub As String, ByVal sMsg As String)

    Dim sLogStr As String

    sLogStr = "HBClient Warning:" & sSub & " " & sMsg
    App.LogEvent sLogStr

End Sub

Public Sub ShowAlert(ByVal sMsg As String)

    frmMainProfile.List3.AddItem (sMsg)
       
End Sub

