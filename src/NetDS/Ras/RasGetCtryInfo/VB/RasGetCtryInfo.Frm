VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "RasGetCountryInfo"
   ClientHeight    =   3720
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3720
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command1 
      Caption         =   "Quit"
      Height          =   375
      Left            =   1560
      TabIndex        =   2
      Top             =   3120
      Width           =   1095
   End
   Begin VB.ListBox List1 
      Height          =   1620
      Left            =   240
      TabIndex        =   0
      Top             =   840
      Width           =   4095
   End
   Begin VB.Label Label1 
      Caption         =   "Country Name ( Country Code )"
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   480
      TabIndex        =   1
      Top             =   240
      Width           =   3375
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
    Dim lpRasCtryInfo As RASCTRYINFO
    Dim lpdwSize As Long
    Dim nRet As Long
    Dim lptr As Long
    Dim tptr As Long
    Dim n As Integer
    Dim CountryName(256) As Byte
        
    lptr = GlobalAlloc(GPTR, 256)
    lpRasCtryInfo.dwCountryID = 1
    
    Do While (lpRasCtryInfo.dwCountryID <> 0)
        lpRasCtryInfo.dwSize = LenB(lpRasCtryInfo)
        lpdwSize = 256
        CopyMemory ByVal lptr, lpRasCtryInfo, LenB(lpRasCtryInfo)
    
        nRet = RasGetCountryInfo(ByVal lptr, lpdwSize)
        If (nRet <> 0) Then
            MsgBox ("RasGetCountryInfo failed: Error = " & nRet), , "Error"
            GoTo 10
        End If
        
        CopyMemory lpRasCtryInfo, ByVal lptr, LenB(lpRasCtryInfo)
        tptr = lptr + lpRasCtryInfo.dwCountryNameOffset
        n = lpdwSize - lpRasCtryInfo.dwCountryNameOffset
    
        CopyMemory CountryName(0), ByVal tptr, n
    
        List1.AddItem (ByteToString(CountryName)) + " (" + Str(lpRasCtryInfo.dwCountryCode) + " )"
        lpRasCtryInfo.dwCountryID = lpRasCtryInfo.dwNextCountryID
    Loop
10:
End Sub
