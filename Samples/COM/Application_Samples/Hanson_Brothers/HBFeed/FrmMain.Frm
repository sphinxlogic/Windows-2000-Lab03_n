VERSION 5.00
Begin VB.Form frmMain 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "HBFeed:  Hanson Brothers Market Simulation"
   ClientHeight    =   3420
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   6570
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   3420
   ScaleWidth      =   6570
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton DeleteOrdersTBut 
      Caption         =   "Delete All Orders"
      Height          =   255
      Left            =   4920
      TabIndex        =   18
      Top             =   50
      Width           =   1575
   End
   Begin VB.TextBox SymTEd 
      Alignment       =   1  'Right Justify
      Height          =   285
      Left            =   3360
      TabIndex        =   16
      Text            =   "5"
      Top             =   0
      Width           =   615
   End
   Begin VB.CheckBox SymCBut 
      Alignment       =   1  'Right Justify
      Caption         =   "Generate Test"
      Height          =   255
      Left            =   80
      TabIndex        =   15
      Top             =   0
      Width           =   1335
   End
   Begin VB.TextBox QNumTEd 
      Alignment       =   1  'Right Justify
      Height          =   285
      Left            =   1200
      TabIndex        =   14
      Text            =   "1200"
      Top             =   345
      Width           =   495
   End
   Begin VB.CheckBox NewsCBut 
      Alignment       =   1  'Right Justify
      Caption         =   "News"
      Height          =   255
      Left            =   3180
      TabIndex        =   13
      Top             =   360
      Width           =   735
   End
   Begin VB.TextBox DTEd 
      Alignment       =   1  'Right Justify
      Height          =   285
      Left            =   2520
      TabIndex        =   4
      Text            =   "1.0"
      Top             =   345
      Width           =   495
   End
   Begin VB.CheckBox QCBut 
      Alignment       =   1  'Right Justify
      Caption         =   "Queue"
      Height          =   255
      Left            =   3960
      TabIndex        =   5
      Top             =   360
      Width           =   825
   End
   Begin VB.TextBox TimerTEd 
      Alignment       =   1  'Right Justify
      Height          =   285
      Left            =   6000
      TabIndex        =   7
      Text            =   "500"
      Top             =   345
      Width           =   495
   End
   Begin VB.ListBox lstSymbols 
      BeginProperty Font 
         Name            =   "Courier"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1425
      Left            =   120
      TabIndex        =   8
      Top             =   1320
      Width           =   6375
   End
   Begin VB.CommandButton cmdClose 
      Caption         =   "Close Exchange"
      Height          =   495
      Left            =   4980
      TabIndex        =   9
      Tag             =   "True"
      Top             =   2820
      Width           =   1515
   End
   Begin VB.Timer timTimer 
      Enabled         =   0   'False
      Interval        =   500
      Left            =   3840
      Top             =   2880
   End
   Begin VB.CommandButton cmdEnd 
      Caption         =   "Suspend Exchange"
      Height          =   495
      Left            =   1860
      TabIndex        =   1
      Top             =   2820
      Width           =   1695
   End
   Begin VB.CommandButton cmdStart 
      Caption         =   "Start Exchange"
      Height          =   495
      Left            =   120
      TabIndex        =   0
      Top             =   2820
      Width           =   1695
   End
   Begin VB.Label Label5 
      Caption         =   "Stock Symbol Count:"
      Height          =   255
      Left            =   1800
      TabIndex        =   17
      Top             =   30
      Width           =   1575
   End
   Begin VB.Label Label4 
      BackColor       =   &H00C0C0C0&
      Caption         =   "  SYMBOL       LAST PRICE    NET CHANGE    TRADE DATE / TIME"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   195
      Left            =   120
      TabIndex        =   12
      Top             =   1080
      Width           =   6375
   End
   Begin VB.Label Label3 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Volatility:"
      Height          =   255
      Left            =   1800
      TabIndex        =   3
      Top             =   360
      Width           =   675
   End
   Begin VB.Label InitDataLabel 
      Alignment       =   2  'Center
      BackColor       =   &H8000000C&
      Caption         =   "Init Quotes"
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Top             =   360
      Width           =   1035
   End
   Begin VB.Label Label2 
      Caption         =   "Activity (msec):"
      Height          =   255
      Left            =   4920
      TabIndex        =   6
      Top             =   360
      Width           =   1095
   End
   Begin VB.Label Label1 
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Symbol    Price   Change         Time"
      BeginProperty Font 
         Name            =   "Courier"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   120
      TabIndex        =   11
      Top             =   1440
      Width           =   6135
   End
   Begin VB.Label lblStatus 
      Caption         =   "Status: Inactive"
      Height          =   255
      Left            =   120
      TabIndex        =   10
      Top             =   720
      Width           =   6375
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'/***********************************************************************************\
'*************************************************************************************
'*  COM+ Hanson Brothers SDK Sample
'*  frmMain.FRM (HBFeed)
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

Public m_cn As ADODB.Connection
Public m_rs As ADODB.Recordset
Public m_cmd As ADODB.Command
Public m_oQuoteUpdate As HBExchange.IQuoteUpdate
Public m_bQueued As Boolean
Public m_dStartDate As String
Public m_bIgnoreTestMsg As Boolean

Dim m_sSymbol As String
Dim m_cBidPrice As Currency
Dim m_cAskPrice As Currency
Dim m_dLastTradeTime As Date
Dim m_cLastTradePrice As Currency
Dim m_dNetChange As Double
Dim m_cDailyHigh As Currency
Dim m_cDailyLow As Currency
Dim m_lAskSize As Long
Dim m_lBidSize As Long
Dim m_cOpenPrice As Currency
Dim m_cClosePrice As Currency
Dim m_dCloseDate As Date
Dim m_lNewsId As Long

Const INIT_ALL = 1
Const INIT_CUSTOMER = 2
Const INIT_QUOTES = 3
Const INIT_ORDERS_ONLY = 4

Const STATIC_DNS = False

Const CONNECT_CONSTANT = "DRIVER={SQL Server}; SERVER=(local);DATABASE=market;user id=sa;password="

Const SUCCESS = 1
Const FAILED = 0

Public m_dic As Scripting.Dictionary
Public m_strConnectString As String

Public m_bLoaded As Boolean

Private Sub Init()
    m_bLoaded = False
    m_bIgnoreTestMsg = False
    lstSymbols.Clear
    
    If SymCBut.Value = 1 Then
        SymTEd.Visible = True
        Label5.Visible = True
        QNumTEd.Visible = False
        DTEd.Text = 0
    Else
        SymTEd.Visible = False
        Label5.Visible = False
        QNumTEd.Visible = True
        DTEd.Text = 1#
    End If
    
    Set m_dic = New Scripting.Dictionary
    m_strConnectString = ""
    Call GetDSN
End Sub


Private Sub DeleteOrdersTBut_Click()

    If MsgBox("Are you Sure you want to Delete all Orders and Holdings?", vbOKCancel) = vbOK Then
    
        Dim rc As Long
        Dim sMsg As String
        Dim objAcct As HBInstitution.IAccount
        
        Set objAcct = New HBInstitution.IAccount
                
        rc = objAcct.InitTestData(INIT_ORDERS_ONLY, 0, sMsg, 0, 0)
        sMsg = "Pending Orders and holdings deleted."
        lblStatus.Caption = sMsg
        MsgBox sMsg & " You MUST PURGE any Public Queues from HBNotify, HBExchange, or HBNews or Errors May occur trying to match unmatchable orders."
        
        Set objAcct = Nothing
        
    End If

End Sub

Private Sub Form_Load()
    
    On Error GoTo ErrorHandler
    
    m_bQueued = False
    
    NewsCBut.Value = 0
    
    QCBut.Value = 1
    QCBut.Enabled = False
    
    m_dStartDate = "01/01/99"
    
    lblStatus.Caption = "Minnesota Exchange Waiting to be Started"
    
    On Error GoTo ErrorHandler
    
    Call Init
    
    Exit Sub
    
ErrorHandler:

    Call cmdClose_Click
    
End Sub

Private Sub cmdStart_Click()
    Dim strSQL As String

    On Error GoTo ErrorHandler
    
    If m_bLoaded = True Then
        lblStatus.Caption = "Exchange Started"
        timTimer.Enabled = True
        Exit Sub
    End If
    
    If Not IsDate(m_dStartDate) Then
        MsgBox "'" & m_dStartDate & "'" & vbCrLf & "Is not as valid date"
        Call cmdClose_Click
    End If
    m_dStartDate = FormatDateTime(m_dStartDate, vbGeneralDate)
    
    lblStatus.Caption = "Minnesota Exchange Starting Components"
    
    Set m_oQuoteUpdate = New HBExchange.IQuoteUpdate
    
    lblStatus.Caption = "Minnesota Exchange Loading LongQuote Records"
    
      
    Set m_cn = New ADODB.Connection
    m_cn.Open m_strConnectString
    
    Set m_cmd = New ADODB.Command
    m_cmd.CommandText = "SELECT * From LongQuote WHERE QuoteTime >= '" & m_dStartDate & "' ORDER BY QuoteTime"
    m_cmd.CommandType = adCmdText
    Set m_cmd.ActiveConnection = m_cn
    
    Set m_rs = New ADODB.Recordset
    m_rs.CursorLocation = adUseClient
    m_rs.Open m_cmd, , adOpenStatic, adLockBatchOptimistic, adCmdText
    
    ' Disconnect the Record Set
    Set m_rs.ActiveConnection = Nothing
    
    Set m_cn = Nothing
    
    If Not (m_rs.BOF And m_rs.EOF) Then
        lblStatus.Caption = "Exchange Starting..."
        timTimer.Enabled = True
        m_bLoaded = True
    Else
        MsgBox "No Feed data found for date time provided"
        Call cmdClose_Click
    End If
    
    Exit Sub
    
ErrorHandler:
    If MsgBox("HB Feed Start ERROR: ErrMsg: " & Err.Description & ". DO YOU WISH TO EXIT? ", vbOKCancel) = vbOK Then
        Call cmdClose_Click
    End If
    
End Sub

Private Sub InitDataLabel_Click()
  Dim sym_len As Long
  sym_len = 0
  If SymCBut.Value = 1 Then
    sym_len = CLng(SymTEd.Text)
    m_bIgnoreTestMsg = False
    Call InitGenData(sym_len)
  Else
    Call InitDefData
  End If
End Sub

Private Sub InitDefData()
    
    On Error GoTo Load_Error
    
    Dim dDelta As Double
    Dim iQNum As Integer
    
    Dim sMsg As String
        
    dDelta = CDbl(DTEd.Text)
    
    iQNum = CInt(QNumTEd.Text)
    
    If iQNum < 3 Or iQNum > 9999 Then
        MsgBox ("Approximate Number of Quotes Generated Must be between 3 and 9,999")
        QNumTEd.Text = "1200"
        Exit Sub
    End If
        
    If dDelta > 10 Or dDelta <= 0.01 Then
        MsgBox ("Market Volatility must be between 0.01 and 10.0")
        Exit Sub
    End If
    
    If dDelta > 1 Then
        sMsg = "Your Delta will create about " & iQNum & " Quote records with INCREASED Market Volatily Data (More Frequent News). Are you Sure you want to re-initialize?"
    ElseIf dDelta < 1 Then
        sMsg = "Your Delta will create about " & iQNum & " Quote records with DECREASED Market Volatily Data (Less Frequent News). Are you Sure you want to re-initialize?"
    Else
        sMsg = "Your Delta will create about " & iQNum & " Quote records with (Default) Market Volatily Data. Are you Sure you want to re-initialize?"
    End If
    
    If MsgBox(sMsg, vbOKCancel) = vbOK Then
     
        Dim rc As Long
        
        sMsg = ""
        
        timTimer.Enabled = False
        cmdStart.Enabled = False
        cmdEnd.Enabled = False
        cmdClose.Enabled = False
        InitDataLabel.Enabled = False
        
        InitDataLabel.BackColor = &HFF&   ' Red
    
        InitDataLabel.Refresh
        
        lblStatus.Caption = "Exchange Suspended while New data is loaded. Please wait about 60 seconds ..."
    
        Call CleanUp
     
        Dim objAcct As HBInstitution.IAccount
        Dim sym_len As Integer
        
        Set objAcct = New HBInstitution.IAccount
            
        rc = objAcct.InitTestData(INIT_QUOTES, dDelta, sMsg, CInt(iQNum / 3), 0)
        Set objAcct = Nothing
        
        InitDataLabel.BackColor = &H404040
     
        MsgBox sMsg
        If rc <> SUCCESS Then
            Exit Sub
        End If
        
Done:
        Call Init
        cmdStart.Enabled = True
        cmdEnd.Enabled = True
        cmdClose.Enabled = True
        InitDataLabel.Enabled = True

    End If
    
    Exit Sub
    
Load_Error:
    If MsgBox("HB Feed Load Data ERROR: " & sMsg & " ErrMsg: " & Err.Description & ". DO YOU WISH TO EXIT? ", vbOKCancel) = vbOK Then
        Call cmdClose_Click
    End If
    GoTo Done
End Sub

Private Sub InitGenData(sym_len As Long)
    
    On Error GoTo Load_Error
    
    Dim dDelta As Double
    Dim lQNum As Long
    
    Dim sMsg As String
        
    dDelta = CDbl(DTEd.Text)
    
    lQNum = CLng(SymTEd.Text)
    
    If lQNum < 1 Or lQNum > 90000 Then
        MsgBox ("Approximate Number of Quotes Generated Must be between 1 and 90,000")
        SymTEd.Text = "5"
        Exit Sub
    End If
        
    If dDelta > 10 Or dDelta < 0 Then
        MsgBox ("Market Volatility must be between 0.0 and 10.0")
        Exit Sub
    End If
    
    If dDelta > 0 Then
        sMsg = "Your Delta will create about " & lQNum & " Test Quote records with INCREASING Prices. Are you Sure you want to re-initialize?"
    Else
        sMsg = "Your will create about " & lQNum & " Test Quote records with the same Prices. Are you Sure you want to re-initialize?"
    End If
    
    sMsg = sMsg + " NOTE: You Must Run the Exchange to Load all Test Quotes - a Msg Box will Appear when Completed."
    
    If MsgBox(sMsg, vbOKCancel) = vbOK Then
     
        Dim rc As Long
        
        sMsg = ""
        
        timTimer.Enabled = False
        cmdStart.Enabled = False
        cmdEnd.Enabled = False
        cmdClose.Enabled = False
        InitDataLabel.Enabled = False
        
        InitDataLabel.BackColor = &HFF&   ' Red
    
        InitDataLabel.Refresh
        
        lblStatus.Caption = "Exchange Suspended while New data is loaded. Please wait about 60 seconds ..."
    
        Call CleanUp
     
        Dim objAcct As HBInstitution.IAccount
        
        Set objAcct = New HBInstitution.IAccount
            
        rc = objAcct.InitTestData(INIT_QUOTES, dDelta, sMsg, CLng(lQNum / 3), lQNum)
        Set objAcct = Nothing
        
        InitDataLabel.BackColor = &H404040
     
        MsgBox sMsg + " You may now START the Exchange."
        If rc <> SUCCESS Then
            Exit Sub
        End If
        
Done:
        Call Init
        cmdStart.Enabled = True
        cmdEnd.Enabled = True
        cmdClose.Enabled = True
        InitDataLabel.Enabled = True

    End If
    
    Exit Sub
    
Load_Error:
    If MsgBox("HB Feed Load Data ERROR: " & sMsg & " ErrMsg: " & Err.Description & ". DO YOU WISH TO EXIT? ", vbOKCancel) = vbOK Then
        Call cmdClose_Click
    End If
    GoTo Done
End Sub

Private Sub NewsCBut_Click()
    If NewsCBut.Value = 1 Then
        QCBut.Enabled = True
    Else
        QCBut.Enabled = False
    End If
End Sub

Private Sub QCBut_Click()
    If QCBut.Value = 1 Then
        m_bQueued = True
    Else
        m_bQueued = False
    End If
End Sub



Private Sub SymCBut_Click()
    If SymCBut.Value = 1 Then
        SymTEd.Visible = True
        Label5.Visible = True
        QNumTEd.Visible = False
        DTEd.Text = 0
        MsgBox ("You should Really Start and Stop IMDB (to flush out old cached data) before you start a new test!")
    Else
        SymTEd.Visible = False
        Label5.Visible = False
        QNumTEd.Visible = True
        DTEd.Text = 1#
    End If
End Sub



Private Sub timTimer_Timer()
    Dim sMsg As String
    Dim retval As Long
    
    On Error GoTo ErrorHandler
    
    If m_bLoaded = False Then
        MsgBox ("Exchange Active Without Trades. Closing Exchange..")
        Call cmdClose_Click
    End If
        
    lblStatus.Caption = "Status: Dispatching Information for " & Trim(m_rs("Symbol")) & " time " & m_rs("QuoteTime")
    
    timTimer.Enabled = False
    
    m_sSymbol = Trim(m_rs("Symbol"))
    m_cBidPrice = m_rs("BidPrice")
    m_cAskPrice = m_rs("AskPrice")
    m_dLastTradeTime = m_rs("LastTradeTime")
    m_cLastTradePrice = FormatCurrency(m_rs("LastTradePrice"))
    m_dNetChange = m_rs("NetChange")
    m_cDailyHigh = m_rs("DailyHigh")
    m_cDailyLow = m_rs("DailyLow")
    m_lAskSize = m_rs("AskSize")
    m_lBidSize = m_rs("BidSize")
    m_cOpenPrice = m_rs("OpenPrice")
    m_cClosePrice = m_rs("ClosePrice")
    m_dCloseDate = m_rs("tCloseDate")
    m_lNewsId = m_rs("newsID")
    
    If NewsCBut.Value = 0 Then
        m_lNewsId = 0
    Else
        m_lNewsId = m_rs("newsID")
    End If
        
    retval = m_oQuoteUpdate.Update(m_sSymbol, m_cBidPrice, m_cAskPrice, m_dLastTradeTime, m_cLastTradePrice, m_dNetChange, m_cDailyHigh, m_cDailyLow, m_lAskSize, m_lBidSize, m_cOpenPrice, m_cClosePrice, m_dCloseDate, m_lNewsId, m_bQueued, sMsg)
    
    If Not m_dic.Exists(m_sSymbol) Then
        lstSymbols.AddItem m_sSymbol
        m_dic.Add m_sSymbol, lstSymbols.NewIndex
    End If
    
    If retval = 1 Then
        lstSymbols.List(CInt(m_dic.Item(m_sSymbol))) = StringPad(m_sSymbol, 5, " ") & StringPad(Trim(m_rs("LastTradePrice")), 12, " ") & StringPad(FormatPercent(m_dNetChange / 100), 10, " ") & "     " & m_rs("QuoteTime")
    ElseIf retval = 4 Then
        ' No Update
         lstSymbols.List(CInt(m_dic.Item(m_sSymbol))) = StringPad(m_sSymbol, 5, " ") & StringPad(Trim(m_rs("LastTradePrice")), 12, " ") & StringPad("N/C", 10, " ") & "     " & m_rs("QuoteTime")
    Else
        lstSymbols.List(CInt(m_dic.Item(m_sSymbol))) = StringPad(m_sSymbol, 5, " ") & "Error"
        If MsgBox("ERROR processing Symbol '" & m_rs("Symbol") & ": " & sMsg & "  DO YOU WISH TO EXIT? ", vbOKCancel) = vbOK Then
            Call cmdClose_Click
        End If
    End If
    
    sMsg = ""
    
    m_rs.MoveNext
    If m_rs.EOF Then
        If SymCBut.Value = 1 And m_bIgnoreTestMsg = False Then
            MsgBox "You May Now SUSPEND the Exchange for Testing. All Quotes Loaded! This msg will not be displayed again."
            m_bIgnoreTestMsg = True
        End If
        m_rs.MoveFirst
    End If
    
    timTimer.Enabled = True
    
    Exit Sub
    
ErrorHandler:
    If MsgBox("HB Feed Timer ERROR: " & sMsg & " ErrMsg: " & Err.Description & ". DO YOU WISH TO EXIT? ", vbOKCancel) = vbOK Then
        Call cmdClose_Click
    End If
End Sub

Private Sub CleanUp()
    
    timTimer.Enabled = False
    
    m_dic.RemoveAll
    
    If Not m_cn Is Nothing Then
        m_cn.Close
    End If
    
    If Not m_oQuoteUpdate Is Nothing Then
        Set m_oQuoteUpdate = Nothing
    End If
    
    If Not m_cmd Is Nothing Then
        Set m_cmd.ActiveConnection = Nothing
        Set m_cmd = Nothing
    End If
    
    If Not m_rs Is Nothing Then
        Set m_rs = Nothing
    End If
    
    If Not m_cn Is Nothing Then
        Set m_cn = Nothing
    End If
    
End Sub

Private Sub cmdClose_Click()
    
    ' Close the Exchange down for the day, Exit
    lblStatus.Caption = "Closing Exchange ..."
    m_bLoaded = False
    Call CleanUp
    
    End
End Sub

Private Sub cmdEnd_Click()

    ' Temporarily Suspend Trading
    
    timTimer.Enabled = False
    
    lblStatus.Caption = "Exchange Suspended"
    
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

Sub GetDSN()
    
    If STATIC_DNS = True Then
        m_strConnectString = "" & CONNECT_CONSTANT & ""
        Exit Sub
    End If
       
    Dim fso As New FileSystemObject
    Dim fil1 As File
    Dim ts As TextStream
    Dim s As String
    
    On Error GoTo ErrorHandler
    
    s = Environ("HBPATH") & "\DSN.txt"
       
    Set fil1 = fso.GetFile(s)
    
    ' Read the contents of the file.
    Set ts = fil1.OpenAsTextStream(ForReading)
    
    m_strConnectString = ts.ReadLine & ""
    
    ts.Close
   
Done:
    Set fso = Nothing
    
    Exit Sub

ErrorHandler:

    LogError ("Error Reading DSN.txt " & Err.Description)
    
    GoTo Done
    
End Sub

Public Sub LogError(ByVal sMsg As String)

Dim sLogStr As String

sLogStr = sMsg & " Error.  Number: " & Err.Number & "  Desc: " & Err.Description & "  Source: " & Err.Source
App.LogEvent sMsg

End Sub

Private Sub TimerTEd_Change()

    Dim lVal As Long
    
    lVal = CLng(Trim(TimerTEd.Text))
    If lVal <= 0 Then
        MsgBox ("Cannot use a non-positive number")
        Exit Sub
    ElseIf lVal > 100000 Then
        MsgBox ("Cannot use a number > 100,000")
        Exit Sub
    End If
    
    timTimer.Interval = lVal

End Sub
