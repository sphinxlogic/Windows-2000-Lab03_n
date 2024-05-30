VERSION 5.00
Object = "{EAB22AC0-30C1-11CF-A7EB-0000C05BAE0B}#1.1#0"; "shdocvw.dll"
Begin VB.Form XMLClient 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "XMLClient"
   ClientHeight    =   8115
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   10320
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   8115
   ScaleWidth      =   10320
   StartUpPosition =   3  'Windows Default
   Begin VB.CheckBox chkPassAsString 
      Caption         =   "Pass String"
      Height          =   195
      Left            =   0
      TabIndex        =   4
      Top             =   7860
      Width           =   1155
   End
   Begin VB.ComboBox comboSSN 
      Height          =   315
      Left            =   0
      TabIndex        =   3
      Text            =   "Combo1"
      Top             =   7500
      Width           =   1275
   End
   Begin VB.CommandButton cmdGetAccountInfo 
      Caption         =   "Get Account Info"
      Height          =   555
      Left            =   1320
      TabIndex        =   2
      Top             =   7560
      Width           =   7635
   End
   Begin VB.CommandButton cmdClose 
      Caption         =   "Close"
      Height          =   555
      Left            =   9060
      TabIndex        =   1
      Top             =   7560
      Width           =   1215
   End
   Begin SHDocVwCtl.WebBrowser WebBrowser 
      Height          =   7395
      Left            =   60
      TabIndex        =   0
      Top             =   60
      Width           =   10215
      ExtentX         =   18018
      ExtentY         =   13044
      ViewMode        =   0
      Offline         =   0
      Silent          =   0
      RegisterAsBrowser=   0
      RegisterAsDropTarget=   1
      AutoArrange     =   0   'False
      NoClientEdge    =   0   'False
      AlignLeft       =   0   'False
      ViewID          =   "{0057D0E0-3573-11CF-AE69-08002B2E1262}"
      Location        =   ""
   End
End
Attribute VB_Name = "XMLClient"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
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

Private Sub cmdClose_Click()
    Unload Me
End Sub

Private Sub cmdGetAccountInfo_Click()
    Dim XMLCtrl As XMLDSOControl
    Dim XMLSrv As HBXMLServer.IXMLAccout
    Dim sMsg As String
    Dim sXML As String
    Dim xObj As Object
    
    Set XMLSrv = New HBXMLServer.IXMLAccout
    
    If chkPassAsString = False Then
                
        Set XMLCtrl = XMLSrv.GetXMLAccounts(comboSSN.List(comboSSN.ListIndex), sMsg)
        
        ' Save the XML stream
        XMLCtrl.XMLDocument.save ("C:\xmlStream.xml")
        WebBrowser.Navigate ("C:\xmlStream.xml")
    Else
        sXML = XMLSrv.GetXMLStrAccounts(comboSSN.List(comboSSN.ListIndex), sMsg)
        
        Set xObj = CreateObject("Microsoft.XMLDOM")
        xObj.loadXML (sXML)
        xObj.save ("C:\xmlStream.xml")
        WebBrowser.Navigate ("C:\xmlStream.xml")
    End If
    
    If Not XMLSrv Is Nothing Then
        Set XMLSrv = Nothing
    End If
    
    If Not xObj Is Nothing Then
        Set xObj = Nothing
    End If
    
End Sub

Private Sub comboSSN_Click()
    cmdGetAccountInfo.Enabled = True
End Sub

Private Sub Form_Load()
    comboSSN.AddItem ("123456789")
    comboSSN.AddItem ("234567890")
    comboSSN.AddItem ("345678901")
    comboSSN.AddItem ("456789012")
    comboSSN.AddItem ("983457489")
    comboSSN.Text = "Select SSN"
    
    ' Passing the XML by string is considerably faster
    chkPassAsString.Value = 1
    
    cmdGetAccountInfo.Enabled = False
End Sub
