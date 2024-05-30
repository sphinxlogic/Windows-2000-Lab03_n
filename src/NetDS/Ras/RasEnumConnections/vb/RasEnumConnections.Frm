VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "RasEnumconnections"
   ClientHeight    =   1995
   ClientLeft      =   3450
   ClientTop       =   3420
   ClientWidth     =   5025
   LinkTopic       =   "Form1"
   ScaleHeight     =   1995
   ScaleWidth      =   5025
   Begin VB.ListBox List1 
      Height          =   450
      Left            =   240
      TabIndex        =   2
      Top             =   600
      Width           =   4455
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Quit"
      Height          =   375
      Left            =   1800
      TabIndex        =   0
      Top             =   1440
      Width           =   1215
   End
   Begin VB.Label Label1 
      Caption         =   "Active RAS connections"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   1440
      TabIndex        =   1
      Top             =   120
      Width           =   2175
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Command1_Click()
    End
End Sub

Private Sub Form_Load()
    Dim lprasconn As RASCONN
    Dim lpcb As Long
    Dim lpcConnections As Long
    Dim lptr As Long
    Dim tptr As Long
    Dim i As Long
    Dim nRet As Long
    
    lpcb = 0
    lprasconn.dwSize = 412
    nRet = RasEnumConnections(lprasconn, lpcb, lpcConnections)
    If (ERROR_BUFFER_TOO_SMALL = nRet And lpcb <> 0) Then
        lptr = GlobalAlloc(GPTR, lpcb)
    ElseIf (nRet = 0 And lpcb = 0) Then
        MsgBox ("No active connections"), , "Attention"
        Exit Sub
    Else
        MsgBox "RasEnumConnections returns " & nRet
    End If
    CopyMemory ByVal lptr, lprasconn, LenB(lprasconn)
    nRet = RasEnumConnections(ByVal lptr, lpcb, lpcConnections)
    If (nRet <> 0) Then
        MsgBox ("RasEnumConnections failed: Error = " & nRet), , "Error"
        GlobalFree (lptr)
        Exit Sub
    Else
        tptr = lptr
        For i = 1 To lpcConnections
            CopyMemory lprasconn, ByVal tptr, LenB(lprasconn)
            List1.AddItem (ByteToString(lprasconn.szEntryName) & _
                           " is connected via " & _
                           ByteToString(lprasconn.szDeviceName))
            tptr = tptr + lprasconn.dwSize
        Next i
    End If

    GlobalFree (lptr)

    
End Sub
