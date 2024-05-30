VERSION 5.00
Begin VB.Form frmConnectDlg 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Connect"
   ClientHeight    =   1830
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   7440
   Icon            =   "Connect.frx":0000
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1830
   ScaleWidth      =   7440
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'CenterOwner
   WhatsThisHelp   =   -1  'True
   Begin VB.TextBox txtProvider 
      Height          =   315
      Left            =   1995
      TabIndex        =   3
      Top             =   1245
      Width           =   3315
   End
   Begin VB.TextBox txtUserID 
      Height          =   315
      Left            =   1995
      TabIndex        =   5
      Top             =   2505
      Width           =   3315
   End
   Begin VB.TextBox txtDataSource 
      Height          =   315
      Left            =   1995
      TabIndex        =   1
      Top             =   705
      Width           =   3315
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Enabled         =   0   'False
      Height          =   345
      Left            =   5910
      TabIndex        =   6
      Top             =   285
      Width           =   1125
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   345
      Left            =   5925
      TabIndex        =   7
      Top             =   720
      Width           =   1125
   End
   Begin VB.Label lblProvider 
      Alignment       =   1  'Right Justify
      BackStyle       =   0  'Transparent
      Caption         =   "Pro&vider:"
      Height          =   300
      Left            =   330
      TabIndex        =   2
      Top             =   1290
      Width           =   1575
   End
   Begin VB.Label lblUserID 
      Alignment       =   1  'Right Justify
      BackStyle       =   0  'Transparent
      Caption         =   "&Login ID:"
      Height          =   300
      Left            =   330
      TabIndex        =   4
      Top             =   2550
      Width           =   1575
   End
   Begin VB.Label lblDataSource 
      Alignment       =   1  'Right Justify
      BackStyle       =   0  'Transparent
      Caption         =   "&Database Name:"
      Height          =   300
      Left            =   330
      TabIndex        =   0
      Top             =   750
      Width           =   1575
   End
   Begin VB.Label lblDataSourceInstructions 
      Caption         =   "What multi-dimensional database do you want to use?"
      Height          =   450
      Left            =   345
      TabIndex        =   9
      Top             =   300
      Width           =   4965
   End
   Begin VB.Label lblLoginInstructions 
      Caption         =   "Enter your login ID for the server."
      Height          =   450
      Left            =   345
      TabIndex        =   8
      Top             =   2070
      Width           =   6525
   End
   Begin VB.Line lnSeparator 
      BorderColor     =   &H80000014&
      Index           =   2
      X1              =   7950
      X2              =   7950
      Y1              =   5085
      Y2              =   5115
   End
End
Attribute VB_Name = "frmConnectDlg"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'*******************************************************************************
'* FORM:  frmConnectDlg
'*    Dialog allowing the user to open an ADOMD connection and specify a cube
'*
'* VERSIONS:
'*    1.00  9/9/97   Matthew Carroll
'*
'* Copyright © 1997 Microsoft Corp.  All rights reserved.
'*******************************************************************************
Option Explicit
Option Compare Text



'********************
'*** DECLARATIONS ***
'********************

Private Const m_iBufferSize = 255
Private m_cnNew As Connection
Private m_fCanceled As Boolean
Private m_fConnectInfoChanged As Boolean
Private m_sDataSource As String

Private Declare Function GetUserName Lib "advapi32.dll" Alias "GetUserNameA" _
      (ByVal lpBuffer As String, nSize As Long) As Long
Private Declare Function GetComputerName Lib "kernel32" Alias _
      "GetComputerNameA" (ByVal lpBuffer As String, nSize As Long) As Long


'***************
'*** METHODS ***
'***************

'*******************************************************************************
'* METHOD:  GetConnection
'*    Walks the user through creating and ADOMD connection and then selecting
'*    a cube from that connection.
'*
'* PARAMETERS:
'*    NewConnection  ADOMD Connection created by the user (In/Out)
'*    DataSource     Name of data source of new connection; blank if not
'*                   connected (Out)
'*
'* RETURNS:
'*    True if a connection has been established, False if the user canceled
'*******************************************************************************
Public Function GetConnection(NewConnection As Connection, _
                              DataSource As String) As Boolean
   InitForm NewConnection
   Me.Show vbModal
   GetConnection = m_fCanceled
   DataSource = vbNullString
   If Not m_fCanceled Then
      Set NewConnection = m_cnNew
      DataSource = m_sDataSource
   End If
End Function

'* Initializes form values
Public Function InitForm(cnOldConnection As Connection)
   Dim sConnectStr As String
      
   Set m_cnNew = cnOldConnection
   m_fCanceled = True   '* Assume the user will cancel until they press finish
   If m_cnNew Is Nothing Then
'     txtDataSource = sGetComputerName
      txtDataSource = "*.cub"
      txtProvider = g_sCnStrProviderDefault
      txtUserID = sGetUserName()
   Else
      sConnectStr = m_cnNew.ConnectionString
      txtDataSource = sGetConnectStrValue(sConnectStr, g_sCnStrDataSource)
      txtProvider = sGetConnectStrValue(sConnectStr, g_sCnStrProvider)
      If txtProvider = vbNullString Then
         txtProvider = m_cnNew.Provider
      End If
      txtUserID = sGetConnectStrValue(sConnectStr, g_sCnStrUserID)
   End If
   CheckConnectInfo
   m_fConnectInfoChanged = False
End Function

'* Gets the computer name of the current system
Private Function sGetComputerName() As String
   Dim sBuffer As String
   sBuffer = String(m_iBufferSize, vbNull)
   GetComputerName sBuffer, m_iBufferSize
   sGetComputerName = sTrimNullChars(sBuffer)
End Function

'* Gets the name of the current user
Private Function sGetUserName() As String
   Dim sBuffer As String
   sBuffer = String(m_iBufferSize, vbNull)
   GetUserName sBuffer, m_iBufferSize
   sGetUserName = sTrimNullChars(sBuffer)
End Function

'* Trims all characters at and after the first null character from a string
Private Function sTrimNullChars(sValue As String) As String
   Dim iPos As Long
   iPos = InStr(sValue, vbNullChar)
   If iPos = 0 Then
      sTrimNullChars = sValue
   Else
      sTrimNullChars = Left(sValue, iPos - 1)
   End If
End Function

'* Enables the Ok button if sufficient connection information has been supplied
Private Sub CheckConnectInfo()
   If Len(txtDataSource) > 0 And Len(txtProvider) > 0 Then
      cmdOK.Enabled = True
   Else
      cmdOK.Enabled = False
   End If
End Sub

'* Attempts to open a connection; returns true if successful, otherwise displays
'* a message to the user describing the problem and returns false
Private Function fOpenConnection() As Boolean

   On Error GoTo fOpenConnectionErr
   Me.MousePointer = vbHourglass
   
   '*** ADOMD Example ***
   
   '* If connection is nothing, closed, or changed then open new connection
   If m_cnNew Is Nothing Then
      Set m_cnNew = New Connection
      m_cnNew.Open sGetConnectionStr
   ElseIf Not m_cnNew.State = adStateOpen Then
      Set m_cnNew = New Connection
      m_cnNew.Open sGetConnectionStr
   ElseIf m_fConnectInfoChanged Then
      Set m_cnNew = New Connection
      m_cnNew.Open sGetConnectionStr
      m_fConnectInfoChanged = False
   End If
               
   '*** End Example ***
   
   fOpenConnection = True
   
   Exit Function
fOpenConnectionErr:
   Me.MousePointer = vbDefault
   DisplayError "Unable to open connection."
   fOpenConnection = False
End Function

'* Builds and returns a connect string from the user supplied information
Private Function sGetConnectionStr() As String
   Dim sResults As String
   sResults = g_sCnStrDataSource & g_sCnStrValuePrefix & _
              txtDataSource & g_sCnStrValueSuffix
   sResults = sResults & g_sCnStrProvider & g_sCnStrValuePrefix & _
              txtProvider & g_sCnStrValueSuffix
   sResults = sResults & g_sCnStrUserID & g_sCnStrValuePrefix & _
              txtUserID & g_sCnStrValueSuffix
   sGetConnectionStr = sResults
End Function



'**********************
'*** EVENT HANDLERS ***
'**********************

Private Sub cmdCancel_Click()
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
         
   Unload Me
End Sub

Private Sub cmdOK_Click()
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
         
   If fOpenConnection Then
      m_fCanceled = False
      m_sDataSource = txtDataSource  '* Save value to return before unloading
      Unload Me
   End If
End Sub

Private Sub txtDataSource_Change()
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
         
   CheckConnectInfo
   m_fConnectInfoChanged = True
End Sub

Private Sub txtProvider_Change()
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
         
   CheckConnectInfo
   m_fConnectInfoChanged = True
End Sub

