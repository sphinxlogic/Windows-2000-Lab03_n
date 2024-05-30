VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.2#0"; "comctl32.ocx"
Begin VB.Form frmHttpQuery 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "WinInet App"
   ClientHeight    =   6855
   ClientLeft      =   1290
   ClientTop       =   2580
   ClientWidth     =   8385
   Icon            =   "HTTP.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   6855
   ScaleWidth      =   8385
   Begin VB.OptionButton optSSL 
      Caption         =   "Select if https url"
      Height          =   255
      Left            =   4200
      TabIndex        =   60
      Top             =   120
      Width           =   1575
   End
   Begin VB.Frame Frame2 
      Caption         =   "Submit Request"
      Height          =   2055
      Left            =   6480
      TabIndex        =   56
      Top             =   240
      Width           =   1815
      Begin VB.OptionButton optPost 
         Caption         =   "      Post"
         Height          =   255
         Left            =   360
         TabIndex        =   59
         Top             =   840
         Width           =   1215
      End
      Begin VB.OptionButton optGet 
         Caption         =   "      Get"
         Height          =   255
         Left            =   360
         TabIndex        =   58
         Top             =   480
         Width           =   1215
      End
      Begin VB.CommandButton btSend 
         Caption         =   "Send Request"
         Height          =   495
         Left            =   240
         TabIndex        =   57
         Top             =   1320
         Width           =   1455
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Authentication"
      Height          =   2295
      Left            =   6480
      TabIndex        =   51
      Top             =   3840
      Width           =   1815
      Begin VB.TextBox txtPassword 
         Height          =   375
         IMEMode         =   3  'DISABLE
         Left            =   240
         PasswordChar    =   "*"
         TabIndex        =   53
         Tag             =   "1"
         Top             =   1680
         Width           =   1215
      End
      Begin VB.TextBox txtUsername 
         Height          =   375
         Left            =   240
         TabIndex        =   52
         Tag             =   "1"
         Top             =   720
         Width           =   1215
      End
      Begin VB.Label Label24 
         Caption         =   "Password:"
         Height          =   375
         Left            =   240
         TabIndex        =   55
         Top             =   1200
         Width           =   1095
      End
      Begin VB.Label Label22 
         Caption         =   "Username:"
         Height          =   255
         Left            =   240
         TabIndex        =   54
         Top             =   360
         Width           =   975
      End
   End
   Begin VB.PictureBox picMain 
      BorderStyle     =   0  'None
      Height          =   5175
      Index           =   0
      Left            =   240
      ScaleHeight     =   5175
      ScaleWidth      =   5835
      TabIndex        =   1
      Top             =   960
      Width           =   5835
      Begin VB.TextBox txtResponseHeaders 
         BackColor       =   &H00FFFFFF&
         Height          =   1095
         Left            =   1380
         MultiLine       =   -1  'True
         ScrollBars      =   2  'Vertical
         TabIndex        =   7
         Tag             =   "1"
         Top             =   3900
         Width           =   4275
      End
      Begin VB.Label lblServer 
         BackColor       =   &H00FFFFFF&
         BorderStyle     =   1  'Fixed Single
         Height          =   315
         Left            =   1380
         TabIndex        =   28
         Tag             =   "1"
         Top             =   3060
         Width           =   4215
      End
      Begin VB.Label Label20 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "Request Method: "
         Height          =   195
         Left            =   3345
         TabIndex        =   27
         Tag             =   "0"
         Top             =   180
         Width           =   1275
      End
      Begin VB.Label Label15 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "Server: "
         Height          =   195
         Left            =   720
         TabIndex        =   26
         Tag             =   "0"
         Top             =   3120
         Width           =   555
      End
      Begin VB.Label lblRequestMethod 
         BackColor       =   &H00FFFFFF&
         BorderStyle     =   1  'Fixed Single
         Height          =   315
         Left            =   4680
         TabIndex        =   25
         Tag             =   "1"
         Top             =   120
         Width           =   915
      End
      Begin VB.Label Label18 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "Raw Headers CR/LF: "
         Height          =   195
         Left            =   360
         TabIndex        =   24
         Tag             =   "0"
         Top             =   3540
         Width           =   1590
      End
      Begin VB.Label Label17 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "Raw Headers: "
         Height          =   195
         Left            =   255
         TabIndex        =   23
         Tag             =   "0"
         Top             =   2700
         Width           =   1065
      End
      Begin VB.Label lblRawHeaders 
         BackColor       =   &H00FFFFFF&
         BorderStyle     =   1  'Fixed Single
         Height          =   315
         Left            =   1380
         TabIndex        =   22
         Tag             =   "1"
         Top             =   2640
         Width           =   4215
      End
      Begin VB.Label lblStatusText 
         BackColor       =   &H00FFFFFF&
         BorderStyle     =   1  'Fixed Single
         Height          =   315
         Left            =   1380
         TabIndex        =   21
         Tag             =   "1"
         Top             =   2220
         Width           =   2835
      End
      Begin VB.Label Label14 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "Text: "
         Height          =   195
         Left            =   900
         TabIndex        =   20
         Tag             =   "0"
         Top             =   2280
         Width           =   405
      End
      Begin VB.Label Label13 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "Status Code: "
         Height          =   195
         Left            =   3615
         TabIndex        =   19
         Tag             =   "0"
         Top             =   540
         Width           =   960
      End
      Begin VB.Label Label12 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "Version: "
         Height          =   195
         Left            =   660
         TabIndex        =   18
         Tag             =   "0"
         Top             =   1800
         Width           =   615
      End
      Begin VB.Label Label11 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "Last Modified: "
         Height          =   195
         Left            =   285
         TabIndex        =   17
         Tag             =   "0"
         Top             =   1440
         Width           =   1035
      End
      Begin VB.Label Label10 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "Forwarded: "
         Height          =   195
         Left            =   465
         TabIndex        =   16
         Tag             =   "0"
         Top             =   1020
         Width           =   840
      End
      Begin VB.Label Label9 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "Content Length: "
         Height          =   195
         Left            =   120
         TabIndex        =   15
         Tag             =   "0"
         Top             =   600
         Width           =   1185
      End
      Begin VB.Label Label8 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "Content Type: "
         Height          =   195
         Left            =   240
         TabIndex        =   14
         Tag             =   "0"
         Top             =   180
         Width           =   1050
      End
      Begin VB.Label lblStatusCode 
         BackColor       =   &H00FFFFFF&
         BorderStyle     =   1  'Fixed Single
         Height          =   315
         Left            =   4680
         TabIndex        =   13
         Tag             =   "1"
         Top             =   480
         Width           =   915
      End
      Begin VB.Label lblVersion 
         BackColor       =   &H00FFFFFF&
         BorderStyle     =   1  'Fixed Single
         Height          =   315
         Left            =   1380
         TabIndex        =   12
         Tag             =   "1"
         Top             =   1800
         Width           =   2835
      End
      Begin VB.Label lblLastModified 
         BackColor       =   &H00FFFFFF&
         BorderStyle     =   1  'Fixed Single
         Height          =   315
         Left            =   1380
         TabIndex        =   11
         Tag             =   "1"
         Top             =   1380
         Width           =   2835
      End
      Begin VB.Label lblForwarded 
         BackColor       =   &H00FFFFFF&
         BorderStyle     =   1  'Fixed Single
         Height          =   315
         Left            =   1380
         TabIndex        =   10
         Tag             =   "1"
         Top             =   960
         Width           =   4215
      End
      Begin VB.Label lblContentLength 
         BackColor       =   &H00FFFFFF&
         BorderStyle     =   1  'Fixed Single
         Height          =   315
         Left            =   1380
         TabIndex        =   9
         Tag             =   "1"
         Top             =   540
         Width           =   1395
      End
      Begin VB.Label lblContentType 
         BackColor       =   &H00FFFFFF&
         BorderStyle     =   1  'Fixed Single
         Height          =   315
         Left            =   1380
         TabIndex        =   8
         Tag             =   "1"
         Top             =   120
         Width           =   1395
      End
   End
   Begin VB.CommandButton btClear 
      Caption         =   "&Clear"
      Height          =   435
      Left            =   6600
      TabIndex        =   4
      Top             =   2400
      Width           =   1695
   End
   Begin VB.CommandButton btExit 
      Caption         =   "&Exit"
      Height          =   435
      Left            =   6600
      TabIndex        =   3
      Top             =   3120
      Width           =   1695
   End
   Begin VB.TextBox txtURL 
      Height          =   315
      Left            =   720
      TabIndex        =   0
      Text            =   "www.microsoft.com"
      Top             =   120
      Width           =   3195
   End
   Begin ComctlLib.TabStrip tabMain 
      Height          =   5595
      Left            =   120
      TabIndex        =   6
      Top             =   600
      Width           =   6195
      _ExtentX        =   10927
      _ExtentY        =   9869
      _Version        =   327682
      BeginProperty Tabs {0713E432-850A-101B-AFC0-4210102A8DA7} 
         NumTabs         =   4
         BeginProperty Tab1 {0713F341-850A-101B-AFC0-4210102A8DA7} 
            Caption         =   "&Response Header"
            Key             =   ""
            Object.Tag             =   ""
            Object.ToolTipText     =   "Response headers that where sent to the HTTP server"
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab2 {0713F341-850A-101B-AFC0-4210102A8DA7} 
            Caption         =   "Re&quest Header"
            Key             =   ""
            Object.Tag             =   ""
            Object.ToolTipText     =   "Request headers that were sent to the HTTP server"
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab3 {0713F341-850A-101B-AFC0-4210102A8DA7} 
            Caption         =   "&HTML Retrieval"
            Key             =   ""
            Object.Tag             =   ""
            Object.ToolTipText     =   "Let's add a progress indicator"
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab4 {0713F341-850A-101B-AFC0-4210102A8DA7} 
            Caption         =   "&Compose Post"
            Key             =   ""
            Object.Tag             =   ""
            Object.ToolTipText     =   "Version number of the DLL"
            ImageVarType    =   2
         EndProperty
      EndProperty
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin ComctlLib.StatusBar sbrMain 
      Align           =   2  'Align Bottom
      Height          =   315
      Left            =   0
      TabIndex        =   5
      Top             =   6540
      Width           =   8385
      _ExtentX        =   14790
      _ExtentY        =   556
      SimpleText      =   ""
      _Version        =   327682
      BeginProperty Panels {0713E89E-850A-101B-AFC0-4210102A8DA7} 
         NumPanels       =   1
         BeginProperty Panel1 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            AutoSize        =   1
            Object.Width           =   14737
            TextSave        =   ""
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
      EndProperty
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin VB.PictureBox picMain 
      BorderStyle     =   0  'None
      Height          =   5175
      Index           =   2
      Left            =   240
      ScaleHeight     =   5175
      ScaleWidth      =   5835
      TabIndex        =   43
      Top             =   960
      Width           =   5835
      Begin VB.TextBox txtHTML 
         Height          =   3435
         Left            =   300
         MultiLine       =   -1  'True
         ScrollBars      =   3  'Both
         TabIndex        =   47
         Top             =   960
         Width           =   5535
      End
      Begin VB.CommandButton btGet 
         Caption         =   "&Get File"
         Enabled         =   0   'False
         Height          =   435
         Left            =   4080
         TabIndex        =   44
         Top             =   4620
         Width           =   1695
      End
      Begin ComctlLib.ProgressBar ProgressBar1 
         Height          =   435
         Left            =   1500
         TabIndex        =   45
         Top             =   4620
         Width           =   2235
         _ExtentX        =   3942
         _ExtentY        =   767
         _Version        =   327682
         Appearance      =   1
      End
      Begin VB.Label Label16 
         AutoSize        =   -1  'True
         Caption         =   "Raw HTML View:"
         Height          =   195
         Left            =   180
         TabIndex        =   48
         Tag             =   "0"
         Top             =   600
         Width           =   1260
      End
      Begin VB.Label Label21 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "Progress Meter: "
         Height          =   195
         Left            =   300
         TabIndex        =   46
         Tag             =   "0"
         Top             =   4740
         Width           =   1155
      End
   End
   Begin VB.PictureBox picMain 
      BorderStyle     =   0  'None
      Height          =   5175
      Index           =   3
      Left            =   240
      ScaleHeight     =   5175
      ScaleWidth      =   5835
      TabIndex        =   38
      Top             =   960
      Width           =   5835
      Begin VB.TextBox txtPost 
         Height          =   375
         Left            =   480
         TabIndex        =   61
         Text            =   "lname=Doe&fname=John"
         Top             =   2280
         Width           =   3255
      End
      Begin VB.Label Label25 
         Caption         =   "Data to be posted:"
         Height          =   255
         Left            =   480
         TabIndex        =   62
         Top             =   1920
         Width           =   1695
      End
      Begin VB.Label lblMinor 
         BackColor       =   &H00FFFFFF&
         BorderStyle     =   1  'Fixed Single
         Height          =   315
         Left            =   1680
         TabIndex        =   42
         Tag             =   "1"
         Top             =   1020
         Width           =   1395
      End
      Begin VB.Label lblMajor 
         BackColor       =   &H00FFFFFF&
         BorderStyle     =   1  'Fixed Single
         Height          =   315
         Left            =   1680
         TabIndex        =   41
         Tag             =   "1"
         Top             =   600
         Width           =   1395
      End
      Begin VB.Label Label7 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "Minor Version: "
         Height          =   195
         Left            =   480
         TabIndex        =   40
         Tag             =   "0"
         Top             =   1080
         Width           =   1050
      End
      Begin VB.Label Label6 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "Major Version: "
         Height          =   195
         Left            =   465
         TabIndex        =   39
         Tag             =   "0"
         Top             =   660
         Width           =   1050
      End
   End
   Begin VB.PictureBox picMain 
      BorderStyle     =   0  'None
      Height          =   5175
      Index           =   1
      Left            =   240
      ScaleHeight     =   5175
      ScaleWidth      =   5835
      TabIndex        =   29
      Top             =   960
      Width           =   5835
      Begin VB.TextBox txtRequestHeaders 
         BackColor       =   &H00FFFFFF&
         Height          =   1095
         Left            =   660
         MultiLine       =   -1  'True
         ScrollBars      =   2  'Vertical
         TabIndex        =   34
         Tag             =   "1"
         Top             =   2220
         Width           =   4275
      End
      Begin VB.Label lblRequestMethod2 
         BackColor       =   &H00FFFFFF&
         BorderStyle     =   1  'Fixed Single
         Height          =   315
         Left            =   1560
         TabIndex        =   37
         Tag             =   "1"
         Top             =   1380
         Width           =   1395
      End
      Begin VB.Label lblUserAgent 
         BackColor       =   &H00FFFFFF&
         BorderStyle     =   1  'Fixed Single
         Height          =   315
         Left            =   1560
         TabIndex        =   36
         Tag             =   "1"
         Top             =   900
         Width           =   1395
      End
      Begin VB.Label lblPragma 
         BackColor       =   &H00FFFFFF&
         BorderStyle     =   1  'Fixed Single
         Height          =   315
         Left            =   1560
         TabIndex        =   35
         Tag             =   "1"
         Top             =   480
         Width           =   1395
      End
      Begin VB.Label Label5 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "Raw Headers CR/LF: "
         Height          =   195
         Left            =   120
         TabIndex        =   33
         Tag             =   "0"
         Top             =   1860
         Width           =   1590
      End
      Begin VB.Label Label4 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "Request Method: "
         Height          =   195
         Left            =   270
         TabIndex        =   32
         Tag             =   "0"
         Top             =   1440
         Width           =   1275
      End
      Begin VB.Label Label2 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "User Agent: "
         Height          =   195
         Left            =   630
         TabIndex        =   31
         Tag             =   "0"
         Top             =   960
         Width           =   885
      End
      Begin VB.Label Label3 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "Query Pragma: "
         Height          =   195
         Left            =   435
         TabIndex        =   30
         Tag             =   "0"
         Top             =   540
         Width           =   1095
      End
   End
   Begin VB.Label Label23 
      Caption         =   "Label23"
      Height          =   15
      Left            =   6360
      TabIndex        =   50
      Top             =   1920
      Width           =   615
   End
   Begin VB.Label Label19 
      Caption         =   "UserName"
      Height          =   375
      Left            =   5280
      TabIndex        =   49
      Top             =   3240
      Width           =   1095
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "URL: "
      Height          =   195
      Left            =   240
      TabIndex        =   2
      Tag             =   "0"
      Top             =   180
      Width           =   420
   End
End
Attribute VB_Name = "frmHttpQuery"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private hInternetSession As Long
Private hInternetConnect As Long
Private hHttpOpenRequest As Long

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : btClear_Click
' Purpose    : Click event for button
' Parameters : NA
' Return val : NA
' Algorithm  : Clears labels on form
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub btClear_Click()
On Error Resume Next
Dim ctrLabel As Control
For Each ctrLabel In Me.Controls
   Select Case TypeName(ctrLabel)
        Case "Label":
            If CBool(ctrLabel.Tag) Then ctrLabel = vbNullString
        Case "TextBox":
            ctrLabel = vbNullString
   End Select
Next ctrLabel
If hHttpOpenRequest <> 0 Then InternetCloseHandle (hHttpOpenRequest)
If hInternetConnect <> 0 Then InternetCloseHandle (hInternetConnect)
hHttpOpenRequest = 0
hInternetConnect = 0
btSend.Enabled = True
SetStatus "Ready"
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : btExit_Click
' Purpose    : Click event for button
' Parameters : NA
' Return val : NA
' Algorithm  : Exist application
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub btExit_Click()
On Error Resume Next
InternetCloseHandle (hHttpOpenRequest)
InternetCloseHandle (hInternetConnect)
InternetCloseHandle (hInternetSession)
Unload Me
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : btGet_Click
' Purpose    : Click event for button
' Parameters : NA
' Return val : NA
' Algorithm  : Gets resource identified in URL
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub btGet_Click()
Dim bDoLoop             As Boolean
Dim sReadBuffer         As String * 2048
Dim lNumberOfBytesRead  As Long
Dim sBuffer             As String
On Error Resume Next
btGet.Enabled = False
Screen.MousePointer = vbHourglass
ProgressBar1.Min = 0
If CBool(Val(lblContentLength)) Then ProgressBar1.Max = Val(lblContentLength)
ProgressBar1.Value = ProgressBar1.Min
SetStatus "InternetReadFile"
bDoLoop = True
While bDoLoop
    sReadBuffer = vbNullString
    bDoLoop = InternetReadFile(hHttpOpenRequest, sReadBuffer, Len(sReadBuffer), lNumberOfBytesRead)
    sBuffer = sBuffer & Left$(sReadBuffer, lNumberOfBytesRead)
    If Not CBool(lNumberOfBytesRead) Then bDoLoop = False
    If CBool(Val(lblContentLength)) Then ProgressBar1.Value = ProgressBar1.Value + lNumberOfBytesRead
Wend
SetStatus "Ready"
Screen.MousePointer = vbDefault
txtHTML = sBuffer
ProgressBar1.Value = 0
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : btSend_Click
' Purpose    : Click event for button
' Parameters : NA
' Return val : NA
' Algorithm  : Sends request to server
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub btSend_Click()
Dim iRetVal     As Integer
Dim sBuffer     As String * 1024
Dim lBufferLen  As Long
Dim vDllVersion As tWinInetDLLVersion
Dim sStatus     As String
Dim sOptionBuffer   As String
Dim lOptionBufferLen As Long
Screen.MousePointer = vbHourglass
btSend.Enabled = True
lBufferLen = Len(sBuffer)
If CBool(hInternetSession) Then
    SetStatus "InternetQueryOption"
    InternetQueryOption hInternetSession, INTERNET_OPTION_VERSION, vDllVersion, Len(vDllVersion)
    lblMajor = vDllVersion.lMajorVersion
    lblMinor = vDllVersion.lMinorVersion
    SetStatus "InternetConnect"
    If optSSL.Value = False Then
        hInternetConnect = InternetConnect(hInternetSession, CheckUrl, INTERNET_DEFAULT_HTTP_PORT, _
                            txtUsername.Text, txtPassword.Text, INTERNET_SERVICE_HTTP, 0, 0)
    Else
        hInternetConnect = InternetConnect(hInternetSession, CheckUrl, INTERNET_DEFAULT_HTTPS_PORT, _
                            txtUsername.Text, txtPassword.Text, INTERNET_SERVICE_HTTP, 0, 0)
    End If
    If hInternetConnect > 0 Then
       
        SetStatus "HttpOpenRequest"
        If optGet.Value = True Then
            sOptionBuffer = vbNullString
            lOptionBufferLen = 0
            If optSSL.Value = False Then
                hHttpOpenRequest = HttpOpenRequest(hInternetConnect, "GET", GetUrlObject, "HTTP/1.0", vbNullString, 0, _
                INTERNET_FLAG_RELOAD Or INTERNET_FLAG_KEEP_CONNECTION, 0)
            Else
                hHttpOpenRequest = HttpOpenRequest(hInternetConnect, "GET", GetUrlObject, "HTTP/1.0", vbNullString, 0, _
                INTERNET_FLAG_RELOAD Or INTERNET_FLAG_KEEP_CONNECTION Or INTERNET_FLAG_SECURE Or INTERNET_FLAG_IGNORE_CERT_CN_INVALID Or INTERNET_FLAG_IGNORE_CERT_DATE_INVALID, 0)
            End If
        Else
            sOptionBuffer = txtPost.Text
            lOptionBufferLen = Len(sOptionBuffer)
            If optSSL.Value = False Then
                hHttpOpenRequest = HttpOpenRequest(hInternetConnect, "POST", GetUrlObject, "HTTP/1.0", vbNullString, 0, _
                INTERNET_FLAG_RELOAD Or INTERNET_FLAG_MULTIPART, 0)
            Else
                hHttpOpenRequest = HttpOpenRequest(hInternetConnect, "POST", GetUrlObject, "HTTP/1.0", vbNullString, 0, _
                INTERNET_FLAG_RELOAD Or INTERNET_FLAG_MULTIPART Or INTERNET_FLAG_SECURE Or INTERNET_FLAG_IGNORE_CERT_CN_INVALID Or INTERNET_FLAG_IGNORE_CERT_DATE_INVALID, 0)
           End If
        End If
       
        If CBool(hHttpOpenRequest) Then
            SetStatus "HttpSendRequest"
            Debug.Print sOptionBuffer
            Dim sHeader As String
            
            'sHeader = "Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/vnd." & vbCrLf
            'iRetVal = HttpAddRequestHeaders(hHttpOpenRequest, sHeader, Len(sHeader), HTTP_ADDREQ_FLAG_REPLACE Or HTTP_ADDREQ_FLAG_ADD)
            'Debug.Print iRetVal & " " & Len(sHeader)
            
            sHeader = "Accept-Language: en" & vbCrLf
            iRetVal = HttpAddRequestHeaders(hHttpOpenRequest, sHeader, Len(sHeader), HTTP_ADDREQ_FLAG_REPLACE Or HTTP_ADDREQ_FLAG_ADD)
            Debug.Print iRetVal & " " & Len(sHeader)
                        
            sHeader = "Connection: Keep-Alive" & vbCrLf
            iRetVal = HttpAddRequestHeaders(hHttpOpenRequest, sHeader, Len(sHeader), HTTP_ADDREQ_FLAG_REPLACE Or HTTP_ADDREQ_FLAG_ADD)
            Debug.Print iRetVal & " " & Len(sHeader);
 
            sHeader = "Content-Type: application/x-www-form-urlencoded" & vbCrLf
            iRetVal = HttpAddRequestHeaders(hHttpOpenRequest, sHeader, Len(sHeader), HTTP_ADDREQ_FLAG_REPLACE Or HTTP_ADDREQ_FLAG_ADD)
            Debug.Print iRetVal & " " & Len(sHeader);
           'sHeader = "Content-Type: text/html" & vbCrLf ' "Accept = image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/vnd." & vbCrLf
            'iRetVal = HttpAddRequestHeaders(hHttpOpenRequest, sHeader, Len(sHeader), HTTP_ADDREQ_FLAG_REPLACE Or HTTP_ADDREQ_FLAG_ADD)
            'Debug.Print iRetVal & " " & Len(sHeader)
            
'Actually only INTERNET_OPTION_RECEIVE_TIMEOUT works. More info see the following KB:
'BUG: InternetSetOption Does Not Set Timeout Values            [axsdk]
'ID: Q176420    CREATED: 06-NOV-1997   MODIFIED: 06-NOV-1997
           Dim dwTimeOut As Long
            dwTimeOut = 30000
            iRetVal = InternetSetOption(hHttpOpenRequest, INTERNET_OPTION_CONNECT_TIMEOUT, _
        dwTimeOut, 4)
            Debug.Print iRetVal & " " & Err.LastDllError & " " & "INTERNET_OPTION_CONNECT_TIMEOUT"
            iRetVal = InternetSetOption(hHttpOpenRequest, INTERNET_OPTION_RECEIVE_TIMEOUT, _
        dwTimeOut, 4)
            Debug.Print iRetVal & " " & "INTERNET_OPTION_RECEIVE_TIMEOUT"
            iRetVal = InternetSetOption(hHttpOpenRequest, INTERNET_OPTION_SEND_TIMEOUT, _
        dwTimeOut, 4)
            Debug.Print iRetVal & " " & "INTERNET_OPTION_SEND_TIMEOUT"
            
Resend:
            iRetVal = HttpSendRequest(hHttpOpenRequest, vbNullString, 0, sOptionBuffer, lOptionBufferLen)
            Dim dwStatus As Long, dwStatusSize As Long
            dwStatusSize = Len(dwStatus)
            HttpQueryInfo hHttpOpenRequest, HTTP_QUERY_FLAG_NUMBER Or HTTP_QUERY_STATUS_CODE, dwStatus, dwStatusSize, 0
            Select Case dwStatus
                Case HTTP_STATUS_PROXY_AUTH_REQ
                'make sure change it to your user name and password.
                'Note Poxy authentication only works for IE40 wininet. For IE3.0x, you need to
                'manually add Proxy-Authentication header.
                 iRetVal = InternetSetOptionStr(hHttpOpenRequest, INTERNET_OPTION_PROXY_USERNAME, _
        "IUSR_WEIHUA1", Len("IUSR_WEIHUA1") + 1)
                 iRetVal = InternetSetOptionStr(hHttpOpenRequest, INTERNET_OPTION_PROXY_PASSWORD, _
        "IUSR_WEIHUA1", Len("IUSR_WEIHUA1") + 1)
              Case HTTP_STATUS_DENIED
                iRetVal = InternetSetOptionStr(hHttpOpenRequest, INTERNET_OPTION_USERNAME, _
        "IUSR_WEIHUA1", Len("IUSR_WEIHUA1") + 1)
                iRetVal = InternetSetOptionStr(hHttpOpenRequest, INTERNET_OPTION_PASSWORD, _
        "IUSR_WEIHUA1", Len("IUSR_WEIHUA1") + 1)
            GoTo Resend
           End Select
            
            If iRetVal Then
                SetStatus "HttpQueryInfo"
                'response headers
                GetQueryInfo hHttpOpenRequest, lblContentType, HTTP_QUERY_CONTENT_TYPE
                GetQueryInfo hHttpOpenRequest, lblContentLength, HTTP_QUERY_CONTENT_LENGTH
                GetQueryInfo hHttpOpenRequest, lblLastModified, HTTP_QUERY_LAST_MODIFIED
                GetQueryInfo hHttpOpenRequest, lblVersion, HTTP_QUERY_VERSION
                GetQueryInfo hHttpOpenRequest, lblStatusCode, HTTP_QUERY_STATUS_CODE
                GetQueryInfo hHttpOpenRequest, lblStatusText, HTTP_QUERY_STATUS_TEXT
                GetQueryInfo hHttpOpenRequest, lblRawHeaders, HTTP_QUERY_RAW_HEADERS
                GetQueryInfo hHttpOpenRequest, txtResponseHeaders, HTTP_QUERY_RAW_HEADERS_CRLF
                GetQueryInfo hHttpOpenRequest, lblForwarded, HTTP_QUERY_FORWARDED
                GetQueryInfo hHttpOpenRequest, lblServer, HTTP_QUERY_SERVER
                GetQueryInfo hHttpOpenRequest, lblRequestMethod, HTTP_QUERY_REQUEST_METHOD
                GetQueryInfo hHttpOpenRequest, lblPragma, HTTP_QUERY_FLAG_REQUEST_HEADERS + HTTP_QUERY_PRAGMA
                GetQueryInfo hHttpOpenRequest, txtRequestHeaders, HTTP_QUERY_FLAG_REQUEST_HEADERS + HTTP_QUERY_RAW_HEADERS_CRLF
                GetQueryInfo hHttpOpenRequest, lblUserAgent, HTTP_QUERY_FLAG_REQUEST_HEADERS + HTTP_QUERY_USER_AGENT
                GetQueryInfo hHttpOpenRequest, lblRequestMethod2, HTTP_QUERY_FLAG_REQUEST_HEADERS + HTTP_QUERY_REQUEST_METHOD
                sStatus = "Ready"
                btSend.Enabled = False
                btGet.Enabled = True
            Else
                ' HttpSendRequest failed
                sStatus = "HttpSendRequest call failed; Error code: " & Err.LastDllError & "."
            End If
        Else
            ' HttpOpenRequest failed
            sStatus = "HttpOpenRequest call failed; Error code: " & Err.LastDllError & "."
        End If
    Else
        ' InternetConnect failed
        sStatus = "InternetConnect call failed; Error code: " & Err.LastDllError & "."
    End If
Else
    ' hInternetSession handle not allocated
    sStatus = "InternetOpen call failed: Error code: " & Err.LastDllError & "."
End If
SetStatus sStatus
Screen.MousePointer = vbDefault
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : Form_Load
' Purpose    : Allocates session handle and centers form
' Parameters : NA
' Return val : NA
' Algorithm  : Calls CenterForm and InternetOpen functions
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub Form_Load()
CenterForm Me
picMain(0).ZOrder 0
optGet.Value = 1
SetStatus "InternetOpen"
hInternetSession = 0
hHttpOpenRequest = 0
hInternetConnect = 0
hInternetSession = InternetOpen(scUserAgent, INTERNET_OPEN_TYPE_PRECONFIG, vbNullString, vbNullString, 0)
If CBool(hInternetSession) Then
    SetStatus "Ready"
Else
    SetStatus "InternetOpen failed."
End If
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : CenterForm
' Purpose    : Used for centering form on screen
' Parameters : the form you would like to center
' Return val : NA
' Algorithm  : moves the form to center of screen after calculating position
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Sub CenterForm(theForm As Form)
Dim iLeft   As Integer
Dim iTop    As Integer
iLeft = (Screen.Width - theForm.Width) / 2
iTop = (Screen.Height - theForm.Height) / 2
If (iLeft < 0) Then iLeft = 0
If (iTop < 0) Then iTop = 0
theForm.Move iLeft, iTop
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : GetQueryInfo
' Purpose    : Retrieves header information
' Parameters : HttpRequest handle, label to put information in, and infolevel flag
' Return val : Success/Failure
' Algorithm  : Calls the HttpQueryInfo function and copies result into label
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Function GetQueryInfo(ByVal hHttpRequest As Long, ByVal lblContentType As Object, ByVal iInfoLevel As Long) As Boolean
Dim sBuffer         As String * 1024
Dim lBufferLength   As Long
lBufferLength = Len(sBuffer)
GetQueryInfo = CBool(HttpQueryInfo(hHttpRequest, iInfoLevel, ByVal sBuffer, lBufferLength, 0))
lblContentType = sBuffer
End Function

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : CheckUrl
' Purpose    : Checks for an URL
' Parameters : NA
' Return val : URL
' Algorithm  : If a URL is not specified it returns a default URL
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Function CheckUrl() As String
If Len(txtURL) = 0 Then txtURL = "www.microsoft.com"
Dim posSlash As Long
posSlash = InStr(txtURL, "/")
If InStr(txtURL, "/") <> 0 Then
CheckUrl = Left(txtURL, InStr(txtURL, "/") - 1)
Else
CheckUrl = txtURL
End If
End Function

Private Function GetUrlObject() As String
If InStr(txtURL, "/") <> 0 Then
GetUrlObject = Right(txtURL, Len(txtURL) - InStr(txtURL, "/") + 1)
Else
GetUrlObject = ""
End If
End Function



Private Sub optGet_Click()
    Set tabMain.SelectedItem = tabMain.Tabs(1)
    picMain(0).ZOrder 0
End Sub

Private Sub optPost_Click()
    Set tabMain.SelectedItem = tabMain.Tabs(4)
    picMain(3).ZOrder 0
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : tabMain_Click
' Purpose    : Tabstrip control click event
' Parameters : NA
' Return val : NA
' Algorithm  : Sets Z-Order of picture control
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub tabMain_Click()
picMain(tabMain.SelectedItem.Index - 1).ZOrder 0
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : SetStatus
' Purpose    : Sets the status text in the status bar
' Parameters : New status message
' Return val : NA
' Algorithm  : Sets the text property
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Sub SetStatus(sStatus As String)
sbrMain.Panels(1).Text = sStatus
DoEvents
End Sub

