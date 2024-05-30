VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 1  'NoTransaction
END
Attribute VB_Name = "INotify"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Attribute VB_Ext_KEY = "RVB_UniqueId" ,"373681380261"
'/***********************************************************************************\
'*************************************************************************************
'*  COM+ Hanson Brothers SDK Sample
'*  Class INotify (HBNotify)
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

' To make this method call queuable, go to the HBInstitution application in the
' COM+ Explorer. Shutdown the application (if up). Go to the OrderSettlement
' component, drill down to the interface, bring up the _OrderSettlement
' property. Choose the Queuing Tab. Select Queued. Go back to the HBInstitution
'application icon,
' select properties, go to the Queuing Tab,
' Select both the Queued and Listen
' check boxes. This will automatically set up the necessary queues for
'HBInstitution.
' Start the HBInstitution application

Option Explicit

#Const HBTESTED = 1

Public Sub ProcessSettlement(ByVal iInstituteId As Integer, ByVal sAcctNum As String, ByVal iOrderId As Integer, ByVal iAction As Integer, ByVal iQuantity As Integer, ByVal cSettledPrice As Currency, ByVal iTradeType As Integer, ByVal iConfirmNumber As Integer, ByVal cValue As Currency)
    
    ' PURPOSE: The TradingFloor Queues "settled" orders (i.e., they have been matched and traded) to the
    ' Institution.
    
    Dim rc As Long
    Dim sMsg As String
    Dim oAcct As HBInstitution.IAccount
         
    rc = FAILED
    
    On Error GoTo ErrorHandler
    
    If iInstituteId = HB_INSTITUTION_ID Then
    
        ' No transactional Context needs to flow
        Set oAcct = CreateObject("HBInstitution.IAccount")
        rc = oAcct.UpdateOrderStatus(sAcctNum, iOrderId, iConfirmNumber, SETTLED, cSettledPrice, cValue, sMsg)
         
        'LogInfo "INotify.ProcessSettlement: iInstituteId = " & iInstituteId & ", Action = " & iAction & ", Acct = " & sAcctNum & ", Quantity = " & iQuantity & ", SettledPrice = " & cSettledPrice & ", TradeType = " & iTradeType & ", ConfirmNumber = " & iConfirmNumber & ", Value = " & cValue & ") rc = " & rc
    
    End If

    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
    
    Exit Sub
   
ErrorHandler:
      
 #If HBTESTED Then
    On Error Resume Next
    ' There is an error - notify HBInstitution of error
    Set oAcct = CreateObject("HBInstitution.IAccount")
    rc = oAcct.UpdateOrderStatus(sAcctNum, iOrderId, iConfirmNumber, SETTLED_ERROR, cSettledPrice, cValue, sMsg)
    If rc = FAILED Then
       If Not oAcct Is Nothing Then
            Set oAcct = Nothing
       End If
       If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    Else
       If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete
    End If
 #Else
    If Not oAcct Is Nothing Then
        Set oAcct = Nothing
    End If
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    LogError "INotify.ProcessSettlement: iInstituteId = " & iInstituteId & ", Action = " & iAction & ", Acct = " & sAcctNum & ", Quantity = " & iQuantity & ", SettledPrice = " & cSettledPrice & ", TradeType = " & iTradeType & ", ConfirmNumber = " & iConfirmNumber & ", Value = " & cValue & ")"
 #End If
 
End Sub
  
Public Sub ProcessConfirmation(ByVal lInstituteOrderId As Long, ByVal iInstituteId As Integer, ByVal lConfirmationNumber As Long)
    
    ' PURPOSE: The TradingFloor Queues "Confirmed" orders (i.e., they have been received and stored)
    ' to the Institution.
    
    Dim rc As Long
    Dim sMsg As String
    Dim oAcct As HBInstitution.IAccount
    
    rc = FAILED
    
    On Error GoTo ErrorHandler
    
    ' Check for Institution this should be directed towards
    If iInstituteId = HB_INSTITUTION_ID Then

        ' No transactional Context needs to flow
        Set oAcct = CreateObject("HBInstitution.IAccount")
        
        rc = oAcct.ConfirmOrder(lInstituteOrderId, lConfirmationNumber, sMsg)
        
        'LogInfo "INotify.ProcessConfirmation: InstituteOrderId = " & lInstituteOrderId & ", ConfirmationNumber = " & lConfirmationNumber & ") rc = " & rc
    
    End If
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetComplete

    Exit Sub
   
ErrorHandler:
    
    If Not oAcct Is Nothing Then
        Set oAcct = Nothing
    End If
    
    If Not GetObjectContext Is Nothing Then GetObjectContext.SetAbort
    
    'LogInfo "INotify.ProcessConfirmation: InstituteOrderId = " & lInstituteOrderId & ", ConfirmationNumber = " & lConfirmationNumber & ")"
 
End Sub
  

