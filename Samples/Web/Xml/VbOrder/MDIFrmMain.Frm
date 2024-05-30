VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.MDIForm MDIFrmMain 
   BackColor       =   &H8000000C&
   Caption         =   "Main Menu - XML Order Application"
   ClientHeight    =   6210
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   8835
   Icon            =   "MDIFrmMain.frx":0000
   LinkTopic       =   "MDIForm1"
   StartUpPosition =   3  'Windows Default
   WindowState     =   2  'Maximized
   Begin MSComctlLib.StatusBar StatusBar1 
      Align           =   2  'Align Bottom
      Height          =   300
      Left            =   0
      TabIndex        =   1
      Top             =   5910
      Width           =   8835
      _ExtentX        =   15584
      _ExtentY        =   529
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   1
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            AutoSize        =   1
            Object.Width           =   15081
            Text            =   "User:"
            TextSave        =   "User:"
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.ImageList ImageList1 
      Left            =   480
      Top             =   1200
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   32
      ImageHeight     =   32
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   4
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "MDIFrmMain.frx":0442
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "MDIFrmMain.frx":0F0E
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "MDIFrmMain.frx":122A
            Key             =   ""
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "MDIFrmMain.frx":167E
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.Toolbar Toolbar1 
      Align           =   1  'Align Top
      Height          =   870
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   8835
      _ExtentX        =   15584
      _ExtentY        =   1535
      ButtonWidth     =   1482
      ButtonHeight    =   1376
      Appearance      =   1
      ImageList       =   "ImageList1"
      _Version        =   393216
      BeginProperty Buttons {66833FE8-8583-11D1-B16A-00C0F0283628} 
         NumButtons      =   3
         BeginProperty Button1 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "Orders"
            Description     =   "Create/Edit/View Orders"
            ImageIndex      =   1
         EndProperty
         BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "Customers"
            Description     =   "View/Edit/Add Customers"
            ImageIndex      =   2
         EndProperty
         BeginProperty Button3 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Caption         =   "Exit"
            Description     =   "Exit"
            ImageIndex      =   4
         EndProperty
      EndProperty
   End
End
Attribute VB_Name = "MDIFrmMain"
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
'file://MDIFrmMain.frm--------------------------------------------------------------------------
 
 
Private Sub MDIForm_Load()
    ' Init the variables that store the hWnd of each form
    Order_Form_hWnd = 0
    Customer_Form_hWnd = 0
End Sub

Private Sub Toolbar1_ButtonClick(ByVal Button As MSComctlLib.Button)

MousePointer = 11 ' change mousepointer to a hour glass

If Button = "Orders" Then ' load order form
    Load frmOrder
    frmOrder.ZOrder (0) ' Place form on top
    frmOrder.WindowState = 0 ' restore window incase it was min.
    frmOrder.Height = 6870
    frmOrder.Width = 9510
    frmOrder.Show
ElseIf Button = "Customers" Then ' load customer form
    Load frmCustomers
    frmCustomers.ZOrder (0) ' Place form on top
    frmCustomers.WindowState = 0 ' restore window incase it was min.
    frmCustomers.Height = 5445
    frmCustomers.Width = 8220
    frmCustomers.Show
ElseIf Button = "Exit" Then ' Exit app
    Unload frmOrder
    Unload frmCustomers
    Unload MDIFrmMain
    Exit Sub
End If

MousePointer = 0 ' restore mousepointer

End Sub

