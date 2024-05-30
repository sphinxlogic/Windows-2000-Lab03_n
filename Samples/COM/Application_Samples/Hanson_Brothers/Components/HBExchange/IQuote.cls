VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 1  'NoTransaction
END
Attribute VB_Name = "IQuote"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Attribute VB_Ext_KEY = "RVB_UniqueId" ,"373680D200CB"
'/***********************************************************************************\
'*************************************************************************************
'*  COM+ Hanson Brothers SDK Sample
'*  Class IQuote (HBExchange)
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

Public Function RetrieveEx(ByVal symbol As String, ByRef QuoteTime As Variant, ByRef bidPrice As Variant, ByRef askPrice As Variant, ByRef LastTradeTime As Variant, ByRef LastTradePrice As Variant, ByRef NetChange As Variant, ByRef DailyHigh As Variant, ByRef DailyLow As Variant, ByRef askSize As Variant, ByRef bidSize As Variant, ByRef OpenPrice As Variant, ByRef ClosePrice As Variant, ByRef closeDate As Variant, ByRef sMsg As Variant) As Long
    
    RetrieveEx = FAILED
    
    On Error GoTo ErrorHandler
  
    Dim cn As ADODB.Connection
    Dim rs As ADODB.Recordset
    
    Dim retval As Long
    
    ' This (commonly used) connection may wish to be held open
    Set cn = New ADODB.Connection
    Set rs = New ADODB.Recordset
 
    cn.PROVIDER = PROVIDER
    cn.ConnectionString = GetDSN()
    cn.ConnectionTimeout = 0
    cn.Open
    rs.CursorType = adOpenForwardOnly
    rs.LockType = adLockReadOnly
    rs.CursorLocation = adUseClient
    rs.ActiveConnection = cn
    
    rs.Source = "SELECT * FROM Quote WHERE symbol = '" & Trim(CStr(symbol)) & "'"
    
    rs.Open
        
    ' If we have data then return it
     If Not rs.EOF Then
        With rs
            QuoteTime = !QuoteTime
            bidPrice = !bidPrice
            askPrice = !askPrice
            LastTradeTime = !LastTradeTime
            LastTradePrice = !LastTradePrice
            NetChange = !NetChange
            DailyHigh = !DailyHigh
            DailyLow = !DailyLow
            askSize = !askSize
            bidSize = !bidSize
            OpenPrice = !OpenPrice
            ClosePrice = !ClosePrice
            closeDate = !tCloseDate
        End With
        RetrieveEx = SUCCESS
    Else
        RetrieveEx = NO_RECORDS_FOUND
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
    
    sMsg = LogErrorStr("IQuote.RetrieveEx. Symbol = " & symbol)
    
End Function

Public Function RetrieveODBCEx(ByVal symbol As String, ByRef QuoteTime As Variant, ByRef bidPrice As Variant, ByRef askPrice As Variant, ByRef LastTradeTime As Variant, ByRef LastTradePrice As Variant, ByRef NetChange As Variant, ByRef DailyHigh As Variant, ByRef DailyLow As Variant, ByRef askSize As Variant, ByRef bidSize As Variant, ByRef OpenPrice As Variant, ByRef ClosePrice As Variant, ByRef closeDate As Variant, ByRef sMsg As Variant) As Long

'#If DUMMY = 1 Then

    RetrieveODBCEx = FAILED
    
    Dim iDSN As Long
    Dim henv As Long
    Dim hdbc As Long
    Dim hstmt As Long
    Dim rc As Long
    Dim ret As Long
    Dim bInTxn As Boolean
    Dim strSQL As String
      
    On Error GoTo onError
    
    ' get ODBC handles
    ret = GetSQLHandles(iDSN, henv, hdbc, hstmt)
    If ret = FAILED Then
        GoTo onError
    End If
    
    If (GetObjectContext.IsInTransaction) Then
        bInTxn = True
    Else
        rc = SQLSetConnectAttr(hdbc, SQL_ATTR_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF, 0)
        If Not (rc = SQL_SUCCESS Or rc = SQL_SUCCESS_WITH_INFO) Then
            GoTo onError
        End If
        bInTxn = False
    End If
    
    ' Get quote for symbol
    strSQL = "select "
    strSQL = strSQL & "QuoteTime, " '1
    strSQL = strSQL & "BidPrice, "  '2
    strSQL = strSQL & "AskPrice, "  '3
    strSQL = strSQL & "LastTradeTime, " '4
    strSQL = strSQL & "LastTradePrice, "    '5
    strSQL = strSQL & "DailyHigh, " '6
    strSQL = strSQL & "DailyLow, "  '7
    strSQL = strSQL & "AskSize, "   '8
    strSQL = strSQL & "BidSize, "   '9
    strSQL = strSQL & "OpenPrice, " '10
    strSQL = strSQL & "ClosePrice, "    '11
    strSQL = strSQL & "tCloseDate, "    '12
    strSQL = strSQL & "netChange, " '13
    
    strSQL = strSQL & " from Quote where symbol = '" & Trim(CStr(symbol)) & "'"
    
    rc = SQLExecDirect(hstmt, strSQL, Len(strSQL))
    If Not (rc = SQL_SUCCESS Or rc = SQL_SUCCESS_WITH_INFO) Then
        GoTo onError
    End If
    
    Dim aQuoteTime As Date
    Dim aBidPrice As Currency
    Dim aAskPrice As Currency
    Dim aLastTradeTime As Date
    Dim aLastTradePrice As Currency
    Dim aDailyHigh As Currency
    Dim aDailyLow As Currency
    Dim aAskSize As Long
    Dim aBidSize As Long
    Dim aOpenPrice As Currency
    Dim aClosePrice As Currency
    Dim aCloseDate As Date
    Dim aNetChange As Double

    rc = SQLBindCol(hstmt, 1, SQL_DATE, aQuoteTime, 0, ByVal aQuoteTime)
    rc = SQLBindCol(hstmt, 2, SQL_CONCURRENCY, aBidPrice, 0, ByVal aBidPrice)
    rc = SQLBindCol(hstmt, 3, SQL_CONCURRENCY, aAskPrice, 0, ByVal aAskPrice)
    rc = SQLBindCol(hstmt, 4, SQL_DATE, aLastTradeTime, 0, ByVal aLastTradeTime)
    rc = SQLBindCol(hstmt, 5, SQL_CONCURRENCY, aLastTradePrice, 0, ByVal aLastTradePrice)
    rc = SQLBindCol(hstmt, 6, SQL_CONCURRENCY, aDailyHigh, 0, ByVal aDailyHigh)
    rc = SQLBindCol(hstmt, 7, SQL_CONCURRENCY, aDailyLow, 0, ByVal aDailyLow)
    rc = SQLBindCol(hstmt, 8, SQL_C_SLONG, aAskSize, 0, ByVal aAskSize)
    rc = SQLBindCol(hstmt, 9, SQL_C_SLONG, aBidSize, 0, ByVal aBidSize)
    rc = SQLBindCol(hstmt, 10, SQL_CONCURRENCY, aOpenPrice, 0, ByVal aOpenPrice)
    rc = SQLBindCol(hstmt, 11, SQL_CONCURRENCY, aClosePrice, 0, ByVal aClosePrice)
    rc = SQLBindCol(hstmt, 12, SQL_DATE, aCloseDate, 0, ByVal aCloseDate)
    rc = SQLBindCol(hstmt, 13, SQL_DOUBLE, aNetChange, 0, ByVal aNetChange)
        
    rc = SQLFetch(hstmt)
    If Not (rc = SQL_SUCCESS Or rc = SQL_SUCCESS_WITH_INFO) Then
        GoTo onError
    End If
    
    QuoteTime = aQuoteTime
    bidPrice = aBidPrice
    askPrice = aAskPrice
    LastTradeTime = aLastTradeTime
    LastTradePrice = aLastTradePrice
    DailyHigh = aDailyHigh
    DailyLow = aDailyLow
    askSize = aAskSize
    bidSize = aBidSize
    OpenPrice = aOpenPrice
    ClosePrice = aClosePrice
    closeDate = aCloseDate
    NetChange = aNetChange
     
    ' make sure to close the result set so we don't use another SQL connection
    rc = SQLFreeStmt(hstmt, SQL_CLOSE)
    If Not (rc = SQL_SUCCESS Or rc = SQL_SUCCESS_WITH_INFO) Then
        GoTo onError
    End If
    
     ' commit the transaction if no MTS txn required
    If Not (bInTxn) Then
        rc = SQLEndTran(SQL_HANDLE_DBC, hdbc, SQL_COMMIT)
        If Not (rc = SQL_SUCCESS Or rc = SQL_SUCCESS_WITH_INFO) Then
            GoTo onError
        End If
    End If
    
    ' all went well, we are now done
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
  
    ReleaseSQLHandles henv, hdbc, hstmt
    
    sMsg = ""
    
    RetrieveODBCEx = SUCCESS
    
    Exit Function
    
onError:
    If Not (bInTxn) Then
        rc = SQLEndTran(SQL_HANDLE_DBC, hdbc, SQL_ROLLBACK)
        If Not (rc = SQL_SUCCESS Or rc = SQL_SUCCESS_WITH_INFO) Then
            GoTo onError
        End If
    End If
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.Abort
    
    ' get SQL error here
    ReleaseSQLHandles henv, hdbc, hstmt
    
    sMsg = LogErrorStr("IQuote.RetrieveODBCEx. Symbol = " & symbol)

'#End If

End Function


Public Function GetSymbolInfo(ByVal sSymbol As String, ByRef sFullName As Variant, ByRef sMsg As Variant) As Long

    GetSymbolInfo = FAILED
    
    On Error GoTo ErrorHandler
                    
    Dim oData As DataLayer
    Dim rs As Variant
    Dim sSQL As String
    Dim lNumRecs As Long
    
    Set oData = New HBExchange.DataLayer
    
    sSQL = "Select * from symbol where symbol = '" & sSymbol & "'"
    
    Set rs = oData.ExecSql(sSQL, _
                           PROVIDER, _
                           GetDSN(), _
                           True, True)
                                                              
    If Not rs.EOF Then
        With rs
            sFullName = rs("fullName")
        End With
        GetSymbolInfo = SUCCESS
                            
    Else
       GetSymbolInfo = NO_RECORDS_FOUND
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
    
    sMsg = LogErrorStr("IQuote.GetSymbolInfo. Symbol = " & sSymbol)
    
End Function


Public Function GetSymbolList(ByRef QuoteList As Variant, ByRef sMsg As Variant) As Long
            
    Dim cn As New ADODB.Connection
    Dim rs As ADODB.Recordset
    Dim sSQL As String
    Dim oData As DataLayer
    
    GetSymbolList = FAILED
    
    On Error GoTo ErrorHandler
    
    Set oData = New HBExchange.DataLayer
    
    cn.Open GetDSN()

    sSQL = "SELECT * FROM Symbol ORDER BY symbol"
    
    Set rs = oData.ExecSql(sSQL, _
                           PROVIDER, _
                           GetDSN(), _
                           True, True)
                           
    'Set rs = cn.Execute(sSQL) ' EPG
    
    If Not rs.EOF Then
        Set QuoteList = rs
        GetSymbolList = SUCCESS
    Else
        GetSymbolList = NO_RECORDS_FOUND
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
    
    If Not oData Is Nothing Then
        Set oData = Nothing
    End If
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    sMsg = LogErrorStr("IQuote.GetSymbolList. SQL = " & sSQL)

End Function


Public Function GetIntradayQuotes(ByVal cTickerSymbol As String, ByVal dStartDate As Date, ByVal dEndDate As Date) As ADODB.Recordset

    Dim cn As New ADODB.Connection
    Dim cmd As New ADODB.Command
    Dim rst As New ADODB.Recordset
    
    On Error GoTo ErrorHandler
    
    cn.Open GetDSN()
    rst.CursorLocation = adUseClient
    
    Set cmd.ActiveConnection = cn
    cmd.CommandText = "sp_IntraDayQuotes"
    cmd.Parameters.Append cmd.CreateParameter("symbol", adChar, adParamInput, 10)
    cmd.Parameters.Append cmd.CreateParameter("startdatetime", adDBTimeStamp, adParamInput)
    cmd.Parameters.Append cmd.CreateParameter("enddatetime", adDBTimeStamp, adParamInput)
    cmd.Parameters("symbol").Value = cTickerSymbol
    cmd.Parameters("startdatetime").Value = dStartDate
    cmd.Parameters("enddatetime").Value = dEndDate
        
    rst.Open cmd, , adOpenStatic, adLockBatchOptimistic, adCmdStoredProc
    Set rst.ActiveConnection = Nothing
    cn.Close
       
     'Code to return tracking code
    Set GetIntradayQuotes = rst
    
    ' We are happy
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete

    Exit Function

ErrorHandler:

    If Not cn Is Nothing Then
        Set cn = Nothing
    End If
    
    If Not cmd Is Nothing Then
        Set cmd = Nothing
    End If
    
    If Not rst Is Nothing Then
        Set rst = Nothing
    End If
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    LogError "IQuote.GetIntradayQuotes. Symbol = " & cTickerSymbol
    
End Function
