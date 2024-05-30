VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 1  'NoTransaction
END
Attribute VB_Name = "INews"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
'/***********************************************************************************\
'*************************************************************************************
'*  COM+ Hanson Brothers SDK Sample
'*  Class INews (HBNews)
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

Public Sub PublishNews(ByVal iNewsID)
 
    ' PURPOSE: Retrieve the news given a newsID
    
    Dim sText As String
    Dim sHeadline As String
    Dim sNewsURL As String
    Dim sSymbol As String
    Dim dTime As Date
    Dim sSQL As String

    On Error GoTo ErrorHandler
        
    If iNewsID <= 0 Then
        GetObjectContext.SetAbort
        Exit Sub
    End If
     
    sSQL = "SELECT * FROM news WHERE newsId = " & iNewsID
    
    App.LogEvent ("PublishNews: SQL = " & sSQL)
     
    Dim cn As New ADODB.Connection
    Dim rs As ADODB.Recordset
    
    cn.Open GetDSN()
    
    Set rs = cn.Execute(sSQL)
                        
    If Not rs.EOF Then
        Dim sStr As String
        
        sSymbol = Trim(rs("symbol"))
        sHeadline = Trim(rs("headline"))
        dTime = rs("timeStamp")
        sNewsURL = Trim(rs("news_url"))
        
        'Format Headline
        sStr = "[" & sSymbol & "] Headline: " & sHeadline & " **** Time [" & dTime & "] **** For Story, see " & sNewsURL
        
        ' For now, just publish news headlines
        Call PublishNewsHeadLine(sStr)
        
    End If
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
    
    Exit Sub
    
ErrorHandler:
    
    If Not rs Is Nothing Then
        Set rs = Nothing
    End If
    
    If Not cn Is Nothing Then
        Set cn = Nothing
    End If
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    LogError "INews.PublishNews. Headline = [" & sHeadline & "]. sSQL = " & sSQL
     
End Sub

Private Function PublishNewsHeadLine(ByVal sHeadline As String)
    
    Dim HB As IHB
    
    Dim NewsService As INewsService

On Error GoTo PublishError
    
    ' EVENT ISSUES: COM+ Event system is synchronous, like an extremely
    ' well-managed connection point. Calls to subscribers will be serialized
    ' and will do so on the publishers (this) thread. Some of this
    ' sychronized nature can be mitigated by using composing them
    ' on a queued component. Having LCE events fire for quote updates
    ' may not be a good use for LCE given the fair amount of overhead. However,
    ' Eventing News is considered reasonable here sense that the latency of
    ' between the first person receiving the news is not much greater then
    ' the last person, in a limited subscribed group, receiving the
    ' same news. One architectural change may be
    ' to create this method in a queued component itself and to avoid
    ' blocking on this thread. We can go further by making the call below
    ' queued itself. If performance is an issue, then this service
    ' should leverage WinSock for publishing. Many RT servers are written using
    ' WinSock.
    
    ' Using COM+ LCE, Hanson Brothers supports parallel firing of events as well as synchronous so
    ' one bad subscriber doesn't hang the publisher.
       
    Set HB = CreateObject("HBEventClass.HBEventClass.1")
    Set NewsService = HB
    
    ' Also Available:
    'HB.NewEvent ("NewEvent")
    'News.HotNews ("HotNews")
    
    NewsService.NewsHeadline (sHeadline)
    
    LogInfo "INews.PublishNewsHeadLine. Headline = [" & sHeadline & "]"
      
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
     
    Exit Function

PublishError:

    If Not HB Is Nothing Then
        Set HB = Nothing
    End If
       
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    LogError "INews.PublishNewsHeadline: Headline = [" & sHeadline & "]."
    
End Function

