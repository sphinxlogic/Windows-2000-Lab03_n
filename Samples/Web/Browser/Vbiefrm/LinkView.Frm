VERSION 5.00
Object = "{EAB22AC0-30C1-11CF-A7EB-0000C05BAE0B}#1.1#0"; "SHDOCVW.DLL"
Begin VB.Form LinkView 
   Caption         =   "Form1"
   ClientHeight    =   6480
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7590
   LinkTopic       =   "Form1"
   ScaleHeight     =   6480
   ScaleWidth      =   7590
   StartUpPosition =   3  'Windows Default
   Begin SHDocVwCtl.WebBrowser WebBrowser1 
      Height          =   3495
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   7215
      ExtentX         =   6165
      ExtentY         =   12726
      ViewMode        =   1
      Offline         =   0
      Silent          =   0
      RegisterAsBrowser=   0
      RegisterAsDropTarget=   1
      AutoArrange     =   -1  'True
      NoClientEdge    =   0   'False
      AlignLeft       =   0   'False
      ViewID          =   "{0057D0E0-3573-11CF-AE69-08002B2E1262}"
      Location        =   ""
   End
   Begin VB.TextBox editNavURL 
      Height          =   375
      Left            =   1800
      TabIndex        =   1
      Top             =   5940
      Width           =   5655
   End
   Begin VB.CommandButton btnNavigate 
      Caption         =   "Navigate"
      Default         =   -1  'True
      Height          =   375
      Left            =   120
      TabIndex        =   2
      Top             =   5940
      Width           =   1455
   End
   Begin VB.TextBox editID 
      Height          =   375
      Left            =   3480
      TabIndex        =   10
      TabStop         =   0   'False
      Top             =   5400
      Width           =   3975
   End
   Begin VB.TextBox editElement 
      Height          =   375
      Left            =   1920
      TabIndex        =   8
      TabStop         =   0   'False
      Top             =   5400
      Width           =   855
   End
   Begin VB.ListBox listLinks 
      Height          =   1425
      Left            =   1800
      TabIndex        =   6
      TabStop         =   0   'False
      Top             =   3840
      Width           =   5655
   End
   Begin VB.CommandButton btnGoBack 
      Caption         =   "Go Back"
      Enabled         =   0   'False
      Height          =   375
      Left            =   120
      TabIndex        =   4
      Top             =   4320
      Width           =   1455
   End
   Begin VB.CommandButton btnGoForward 
      Caption         =   "Go Forward"
      Enabled         =   0   'False
      Height          =   375
      Left            =   120
      TabIndex        =   5
      Top             =   3840
      Width           =   1455
   End
   Begin VB.CommandButton btnGetLinks 
      Caption         =   "Get Links"
      Height          =   375
      Left            =   120
      TabIndex        =   3
      Top             =   4950
      Width           =   1455
   End
   Begin VB.Label Label2 
      Caption         =   "href:"
      Height          =   285
      Left            =   3000
      TabIndex        =   9
      Top             =   5490
      Width           =   375
   End
   Begin VB.Label Label1 
      Caption         =   "onMouseOver Element:"
      Height          =   285
      Left            =   120
      TabIndex        =   7
      Top             =   5490
      Width           =   1815
   End
End
Attribute VB_Name = "LinkView"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim WithEvents DocEvents As HTMLDocument
Attribute DocEvents.VB_VarHelpID = -1

Private Sub Form_Load()
    WebBrowser1.navigate ("http://www.microsoft.com")
End Sub

Private Sub WebBrowser1_BeforeNavigate2(ByVal pDisp As Object, URL As Variant, Flags As Variant, TargetFrameName As Variant, PostData As Variant, Headers As Variant, Cancel As Boolean)
    Set DocEvents = Nothing
    listLinks.Clear
    editElement = ""
    editID = ""
End Sub

Private Sub btnNavigate_Click()
    '  Check to make sure a URL has been added
    If editNavURL.Text <> "" Then
       WebBrowser1.navigate (editNavURL)
    End If
End Sub
   
Private Sub btnGoForward_Click()
    WebBrowser1.GoForward
End Sub

Private Sub btnGoBack_Click()
    WebBrowser1.GoBack
End Sub

Private Sub WebBrowser1_CommandStateChange(ByVal Command As Long, ByVal Enable As Boolean)
    Select Case Command
        Case CSC_NAVIGATEBACK
            btnGoBack.Enabled = Enable
        Case CSC_NAVIGATEFORWARD
            btnGoForward.Enabled = Enable
    End Select
End Sub

Private Sub DocEvents_onmouseover()
    ' the element may not have an href
    On Error Resume Next
    
    Dim curWnd As HTMLWindow2
    Dim curElement As IHTMLElement
    
    Set curWnd = WebBrowser1.document.parentWindow
    Set curElement = curWnd.event.srcElement
    
    editElement = ""
    editID = ""
    
    editElement = curElement.tagName
    editID = curElement.href
End Sub

Private Sub DocEvents_onmouseout()
    editElement = ""
    editID = ""
End Sub

Private Sub btnGetLinks_Click()
    On Error Resume Next
   
    Dim theControl As WebBrowser
    Set theControl = WebBrowser1
    
    Dim HTMLDoc As HTMLDocument
    Set HTMLDoc = WebBrowser1.document
     
    listLinks.Clear
    Call RecurseFrames(HTMLDoc)
End Sub

Private Sub RecurseFrames(HTMLDoc As HTMLDocument)
    On Error GoTo handleError
    
    If HTMLDoc Is Nothing Then
        ' Not an HTML document
        Exit Sub
    End If
    
    Dim BODYElement As IHTMLElement
    Set BODYElement = HTMLDoc.body
    
    If BODYElement.tagName = "BODY" Then
        Dim ELEMENTCo As IHTMLElementCollection
        Set ELEMENTCo = HTMLDoc.links
        
        Dim Element As HTMLAnchorElement
        
        For Each Element In ELEMENTCo
            listLinks.AddItem (Element.href)
        Next
    End If
    
    Dim HTMLFrames As IHTMLFramesCollection2
    Set HTMLFrames = HTMLDoc.frames
    
    Dim HTMLWnd As HTMLWindow2
    
    For countFrames = 0 To HTMLFrames.length - 1
        Set HTMLWnd = HTMLFrames(countFrames)
        Call RecurseFrames(HTMLWnd.document)
    Next
    
    Exit Sub
handleError:
        MsgBox (Err.Description)
End Sub

Private Sub WebBrowser1_DocumentComplete(ByVal pDisp As Object, URL As Variant)
    'may be word or some other server
    On Error Resume Next
    
    If pDisp Is WebBrowser1.Object Then
        Set DocEvents = WebBrowser1.document
    End If
End Sub

