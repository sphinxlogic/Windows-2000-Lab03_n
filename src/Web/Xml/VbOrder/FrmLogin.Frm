VERSION 5.00
Begin VB.Form frmLogin 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Login - XML Order Application"
   ClientHeight    =   1545
   ClientLeft      =   2835
   ClientTop       =   3480
   ClientWidth     =   3750
   Icon            =   "frmLogin.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   912.837
   ScaleMode       =   0  'User
   ScaleWidth      =   3521.047
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.TextBox txtUserName 
      Height          =   345
      Left            =   1290
      TabIndex        =   1
      Text            =   "Guest"
      Top             =   135
      Width           =   2325
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   390
      Left            =   495
      TabIndex        =   4
      Top             =   1020
      Width           =   1140
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   390
      Left            =   2100
      TabIndex        =   5
      Top             =   1020
      Width           =   1140
   End
   Begin VB.TextBox txtPassword 
      Height          =   345
      IMEMode         =   3  'DISABLE
      Left            =   1290
      PasswordChar    =   "*"
      TabIndex        =   3
      Text            =   "password"
      Top             =   525
      Width           =   2325
   End
   Begin VB.Label lblLabels 
      Caption         =   "&User Name:"
      Height          =   270
      Index           =   0
      Left            =   105
      TabIndex        =   0
      Top             =   150
      Width           =   1080
   End
   Begin VB.Label lblLabels 
      Caption         =   "&Password:"
      Height          =   270
      Index           =   1
      Left            =   105
      TabIndex        =   2
      Top             =   540
      Width           =   1080
   End
End
Attribute VB_Name = "frmLogin"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'*--------------------------------------------------------------------------
' Copyright (c) 1999  Microsoft Corporation.  All Rights Reserved.
'
' THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
' ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
' THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
' PARTICULAR PURPOSE.
'file://frmLogin.frm--------------------------------------------------------------------------
 
 
Option Explicit

Public LoginSucceeded As Boolean ' Used to see if the user was verified

Private Sub cmdCancel_Click()
    '---------------------------
    'set the global var to false
    'to denote a failed login
    '---------------------------
    LoginSucceeded = False
    Me.Hide
    
    Unload frmLogin
    
End Sub

Private Sub cmdOK_Click()
    
    '------------------------------------------------------------------
    'check for correct password and add a log entry in the log.xml file
    '------------------------------------------------------------------
    
    Dim User_File As String
    Dim User_Query As IXMLDOMNode
    Dim Log As New DOMDocument
    Dim new_node As IXMLDOMNode
    Dim new_Tree As IXMLDOMNode
    Dim Log_Path As String
    
    '----------------------------------------------------------------------
    ' Use the following code only if you are using VB to save the XML file
    ' See the notes in the function Save_XML_File() for save info
    '----------------------------------------------------------------------
    'Log_Path = CurDir("c") & "\log.xml"
    'User_File = CurDir("c") & "\users.xml"
    
    Log_Path = "log.xml"
    User_File = "users.xml" ' set global path to xml file
    
    Log.Load (Log_Path)

    doc.Load (User_File) ' load users.xml file

    If Log.xml = "" Then ' Create log file if it does not exist
        Log.loadXML ("<root></root>")
    End If
    
    If doc.xml <> "" Then
        
        ' Query for current user
        
        Set User_Query = doc.documentElement
    
        Set User_Query = User_Query.selectSingleNode("users/user[name[value()='" & txtUserName.Text & "']]/password")
    
        If txtPassword = User_Query.Text Then
             
            ' Make new "log" node

            Set new_node = Log.createElement("log")

            Set new_Tree = Log.documentElement.appendChild(new_node)

            ' create "Date" and "User" attributes

            Set new_node = Log.createAttribute("Date")

            new_node.Text = Date

            Set new_Tree = Log.documentElement.lastChild.Attributes.setNamedItem(new_node)

            Set new_node = Log.createAttribute("User")

            new_node.Text = txtUserName.Text

            Set new_Tree = Log.documentElement.lastChild.Attributes.setNamedItem(new_node)

            ' Save log info to disk
            
            DoEvents
            
            Call Save_XML_File(Log_Path, Log)
            
            Call Load_XML_Files   ' Load and Init XML Files
            
            Load MDIFrmMain
             
            MDIFrmMain.StatusBar1.Panels.Item(1).Text = "User: " & txtUserName.Text
            
            MDIFrmMain.Show
                        
            Unload frmLogin
            
        Else
            MsgBox "Invalid Password, try again!", , "Login"
            txtPassword.SetFocus
            SendKeys "{Home}+{End}"
        End If
    Else
        MsgBox "No users in xml file."
        txtPassword.SetFocus
        SendKeys "{Home}+{End}"
    End If
    
    Set User_Query = Nothing
    Set doc = Nothing ' unload users.xml file
    Set Log = Nothing ' unload log.xml file
    
End Sub

Private Sub txtPassword_GotFocus()
    '-----------------------------------------------
    ' When entering the text box select all the text
    '-----------------------------------------------
    txtPassword.SelStart = 0
    txtPassword.SelLength = Len(txtPassword.Text)
End Sub

Private Sub txtUserName_gotfocus()
    '-----------------------------------------------
    ' When entering the text box select all the text
    '-----------------------------------------------
    txtUserName.SelStart = 0
    txtUserName.SelLength = Len(txtUserName.Text)
End Sub
