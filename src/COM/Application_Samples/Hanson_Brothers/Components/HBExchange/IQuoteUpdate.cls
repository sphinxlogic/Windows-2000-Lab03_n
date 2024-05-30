VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 1  'NoTransaction
END
Attribute VB_Name = "IQuoteUpdate"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Attribute VB_Ext_KEY = "RVB_UniqueId" ,"373680E403D8"
'/***********************************************************************************\
'*************************************************************************************
'*  COM+ Hanson Brothers SDK Sample
'*  Class IQuoteUpdate (HBExchange)
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


Public Function Update(ByVal strSymbol As String, ByVal cBidPrice As Currency, ByVal cAskPrice As Currency, ByVal LastTradeTime As String, ByVal cLastTradePrice As Currency, ByVal dNetChange As Double, ByVal cDailyHigh As Currency, ByVal cDailyLow As Currency, ByVal lAskSize As Long, ByVal lBidSize As Long, ByVal cOpenPrice As Currency, ByVal cClosePrice As Currency, ByVal closeDate As Date, ByVal lNewsId As Long, ByVal bQueued As Boolean, ByRef sMsg As Variant) As Long

    Update = FAILED
    On Error GoTo ErrorHandler

    Dim cn As ADODB.Connection
    Dim rs As ADODB.Recordset
    Dim blnSendMessage As Boolean
    Dim oMarketFloor As HBExchange.IMarketFloor
    Dim retval As Long
    Dim a(15) As Variant
    Dim b(15) As Variant
    Dim Localquotetime As Variant
    Dim LocalVolume As Variant
    
    Dim oNews As HBNews.INews
  
    Localquotetime = "10:34:00 AM"
    LocalVolume = 10
    
    retval = SUCCESS
    
    Set cn = New ADODB.Connection
    Set rs = New ADODB.Recordset

    cn.PROVIDER = PROVIDER
    cn.ConnectionString = GetDSN()
    cn.ConnectionTimeout = 0
    cn.Open
    rs.CursorType = adOpenDynamic
    rs.LockType = adLockOptimistic ' New
    rs.CursorLocation = adUseServer
    rs.ActiveConnection = cn
    
    rs.Source = "SELECT * FROM Quote WHERE symbol = '" & Trim(CStr(strSymbol)) & "'"
    
    rs.Open
        
    If rs.BOF And rs.EOF Then
  
        ' Add a new record by passing parameters to rs.AddNew
        a(0) = "Symbol"
        a(1) = "QuoteTime"
        a(2) = "bidPrice"
        a(3) = "askPrice"
        a(4) = "LastTradeTime"
        a(5) = "LastTradePrice"
        a(6) = "DailyHigh"
        a(7) = "DailyLow"
        a(8) = "askSize"
        a(9) = "bidSize"
        a(10) = "OpenPrice"
        a(11) = "ClosePrice"
        a(12) = "tCloseDate"
        a(13) = "NetChange"
        a(14) = "Volume"
        a(15) = "newsID"
        
        b(0) = strSymbol
        b(1) = Localquotetime
        b(2) = cBidPrice
        b(3) = cAskPrice
        b(4) = LastTradeTime
        b(5) = cLastTradePrice
        b(6) = cDailyHigh
        b(7) = cDailyLow
        b(8) = lAskSize
        b(9) = lBidSize
        b(10) = cOpenPrice
        b(11) = cClosePrice
        b(12) = closeDate
        b(13) = dNetChange
        b(14) = LocalVolume
        b(15) = lNewsId
     
        rs.AddNew a, b
    
        rs.Update
        
        blnSendMessage = True
    Else
        ' Check if there is News
        
        If lNewsId > 0 Then
        
            ' Here is another "Fire & Forget" case where a Queued Component call
            ' is useful in avoiding bogging down the Exchange. specially if
            ' the news service is blocking on a bad subscriber.
            ' NOTE: The number of News messages are a small percentage of the
            ' overall work done by this component.

            If bQueued = True Then
                Set oNews = CreateObject("queue:/new:HBNews.INews")
            Else
                ' No Transaction Context needs to flow, so just use CreateObject
                Set oNews = CreateObject("HBNews.INews")
            End If
            
            Call oNews.PublishNews(lNewsId)
  
        End If
            
        If rs("bidPrice") <> cBidPrice Or _
            rs("askPrice") <> cAskPrice Or _
            rs("askSize") <> lAskSize Or _
            rs("bidSize") <> lBidSize Or _
            rs("ClosePrice") <> cClosePrice Then
            
            rs("bidPrice") = cBidPrice
            rs("askPrice") = cAskPrice
            rs("LastTradeTime") = LastTradeTime
            rs("LastTradePrice") = cLastTradePrice
            rs("NetChange") = dNetChange
            rs("DailyHigh") = cDailyHigh
            rs("DailyLow") = cDailyLow
            rs("askSize") = lAskSize
            rs("bidSize") = lBidSize
            rs("OpenPrice") = cOpenPrice
            rs("ClosePrice") = cClosePrice
            rs("tCloseDate") = closeDate
    
            rs.Update
            
            blnSendMessage = True
        Else
            Update = RECORD_UPDATE_FAILED
            sMsg = "No Change. Record Not Updated"
            GoTo Complete
        End If
    End If
    
    If blnSendMessage Then
        
        ' Lastly, this object was not Queued since the
        ' MarketFloor can only go as fast as
        ' this method sends it quote updates. However, if this quote feed went to more
        ' then one MarketFloor, then you may want to queue.
        
        ' No transaction Context needs to flow, so just use CreateObject
        Set oMarketFloor = GetObjectContext.CreateInstance("HBExchange.IMarketFloor") 'CreateObject("HBExchange.IMarketFloor")
        'Set oMarketFloor = CreateObject("HBExchange.IMarketFloor")
        
        retval = oMarketFloor.GetMatchingTrades(strSymbol, cBidPrice, cAskPrice, cLastTradePrice, lAskSize, lBidSize, sMsg)
        
        If retval <> SUCCESS Then
              
            ' Don't fail (abort) since the market may only be temporarily down
                    
            Update = retval
            
            GoTo Complete
              
        End If
        
    End If
   
    Update = SUCCESS
  
Complete:

    cn.Close
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
    
    Exit Function

ErrorHandler:

    If Not oMarketFloor Is Nothing Then
        Set oMarketFloor = Nothing
    End If
    
    If Not cn Is Nothing Then
        Set cn = Nothing
    End If
    
    If Not rs Is Nothing Then
        Set rs = Nothing
    End If
    
    If Not oNews Is Nothing Then
        Set oNews = Nothing
    End If
 
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    sMsg = LogErrorStr("IQuoteUpdate.Update")

End Function




