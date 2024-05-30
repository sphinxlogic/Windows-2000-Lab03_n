VERSION 5.00
Object = "{EAB22AC0-30C1-11CF-A7EB-0000C05BAE0B}#1.1#0"; "SHDOCVW.DLL"
Begin VB.Form MyWebBrowser 
   Caption         =   "My VB Web browser"
   ClientHeight    =   4455
   ClientLeft      =   165
   ClientTop       =   735
   ClientWidth     =   6780
   LinkTopic       =   "Form1"
   ScaleHeight     =   4455
   ScaleWidth      =   6780
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox enter_url 
      Height          =   285
      Left            =   720
      TabIndex        =   1
      Text            =   "Text1"
      Top             =   0
      Width           =   3975
   End
   Begin SHDocVwCtl.WebBrowser WebBrowser1 
      Height          =   3375
      Left            =   720
      TabIndex        =   0
      Top             =   600
      Width           =   5295
      ExtentX         =   9340
      ExtentY         =   5953
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
   Begin VB.Label Label1 
      Caption         =   "Address:"
      Height          =   255
      Left            =   0
      TabIndex        =   2
      Top             =   0
      Width           =   615
   End
   Begin VB.Menu menuFile 
      Caption         =   "&File"
      Begin VB.Menu menuFileNew 
         Caption         =   "&New"
         Shortcut        =   ^N
      End
      Begin VB.Menu menuFileOpen 
         Caption         =   "&Open..."
         Shortcut        =   ^O
      End
      Begin VB.Menu menuFileSave 
         Caption         =   "&Save"
         Shortcut        =   ^S
      End
      Begin VB.Menu menuFileSaveAs 
         Caption         =   "Save &As..."
      End
      Begin VB.Menu menuFileSeparator1 
         Caption         =   "-"
      End
      Begin VB.Menu menuFilePageSetup 
         Caption         =   "Page Set&up..."
      End
      Begin VB.Menu menuFilePrint 
         Caption         =   "&Print..."
         Shortcut        =   ^P
      End
      Begin VB.Menu menuFileSeparator2 
         Caption         =   "-"
      End
      Begin VB.Menu menuFileWorkOffline 
         Caption         =   "&Work Offline"
      End
      Begin VB.Menu menuFileClose 
         Caption         =   "&Close"
      End
   End
   Begin VB.Menu menuEdit 
      Caption         =   "&Edit"
      Begin VB.Menu menuEditCut 
         Caption         =   "Cu&t"
         Shortcut        =   ^X
      End
      Begin VB.Menu menuEditCopy 
         Caption         =   "&Copy"
         Shortcut        =   ^C
      End
      Begin VB.Menu menuEditPaste 
         Caption         =   "&Paste"
         Shortcut        =   ^V
      End
      Begin VB.Menu menuEditSeparator1 
         Caption         =   "-"
      End
      Begin VB.Menu menuEditSelectAll 
         Caption         =   "Select &All"
         Shortcut        =   ^A
      End
      Begin VB.Menu menuEditSeparator2 
         Caption         =   "-"
      End
      Begin VB.Menu menuEditFind 
         Caption         =   "&Find"
         Shortcut        =   ^F
      End
   End
   Begin VB.Menu menuView 
      Caption         =   "&View"
      Index           =   1
      Begin VB.Menu menuViewFonts 
         Caption         =   "Fo&nts"
         Begin VB.Menu menuViewFontsLargest 
            Caption         =   "Lar&gest"
         End
         Begin VB.Menu menuViewFontsLarger 
            Caption         =   "&Larger"
         End
         Begin VB.Menu menuViewFontsMedium 
            Caption         =   "&Medium"
         End
         Begin VB.Menu menuViewFontsSmaller 
            Caption         =   "&Smaller"
         End
         Begin VB.Menu menuViewFontsSmallest 
            Caption         =   "Sm&allest"
         End
      End
      Begin VB.Menu menuViewSeparator1 
         Caption         =   "-"
      End
      Begin VB.Menu menuViewStop 
         Caption         =   "Sto&p"
      End
      Begin VB.Menu menuViewRefresh 
         Caption         =   "&Refresh"
      End
      Begin VB.Menu menuViewSeparator2 
         Caption         =   "-"
      End
      Begin VB.Menu menuViewSource 
         Caption         =   "Sour&ce"
      End
      Begin VB.Menu menuViewSeparator3 
         Caption         =   "-"
      End
      Begin VB.Menu menuViewInternetOptions 
         Caption         =   "Internet &Options..."
      End
   End
   Begin VB.Menu menuGo 
      Caption         =   "&Go"
      Begin VB.Menu menuGoBack 
         Caption         =   "&Back"
      End
      Begin VB.Menu menuGoForward 
         Caption         =   "&Forward"
      End
      Begin VB.Menu menuGoUpOneLevel 
         Caption         =   "&Up One Level"
      End
      Begin VB.Menu menuGoSeparator1 
         Caption         =   "-"
      End
      Begin VB.Menu menuGoHomePage 
         Caption         =   "&Home Page"
      End
      Begin VB.Menu menuGoSearchTheWeb 
         Caption         =   "&Search the Web"
      End
      Begin VB.Menu menuGoSeparator2 
         Caption         =   "-"
      End
      Begin VB.Menu menuGoMail 
         Caption         =   "&Mail"
      End
      Begin VB.Menu menuGoNews 
         Caption         =   "&News"
      End
      Begin VB.Menu menuGoMyComputer 
         Caption         =   "My &Computer"
      End
      Begin VB.Menu menuGoAddressBook 
         Caption         =   "&Address  Book"
      End
   End
   Begin VB.Menu menuFavorites 
      Caption         =   "&Favorites"
      Begin VB.Menu menuFavoritesAddToFavorites 
         Caption         =   "&Add to Favorites..."
      End
      Begin VB.Menu menuFavoritesOrganizeFavorites 
         Caption         =   "&Organize Favorites..."
      End
      Begin VB.Menu menuFavoritesSeparator1 
         Caption         =   "-"
      End
      Begin VB.Menu menuFavoritesManageSubscriptions 
         Caption         =   "&Manage Subscriptions..."
      End
      Begin VB.Menu ShowFavorites 
         Caption         =   "Show Favorites"
      End
   End
End
Attribute VB_Name = "MyWebBrowser"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' Implements most of the functionality found in a typical browser application
' by using various WebBrowser technologies
' uses WBAddrBook helper DLL to get at Address Book and other functionality

Dim WBAddrBook As WBWAB
Private Declare Function GetWindowsDirectory Lib "kernel32" _
Alias "GetWindowsDirectoryA" _
(ByVal lpDirName As String, ByVal usize As Long) As Long
Private Sub enter_url_KeyPress(KeyAscii As Integer)
    If KeyAscii = vbKeyReturn Then
        On Error GoTo NavigateErr
        WebBrowser1.Navigate Me.enter_url.Text
    End If
    Exit Sub
NavigateErr:
    WebBrowser1.Navigate "about:NavigationFailure"
End Sub
Private Sub Form_Load()
    Set WBAddrBook = New WBWAB
    Set WBAddrBook.WebBrowser = WebBrowser1
    WebBrowser1.Navigate "msdn.microsoft.com"
End Sub

Private Sub Form_Resize()
    WebBrowser1.Move 0, Me.enter_url.Height, Me.ScaleWidth, Me.ScaleHeight - Me.enter_url.Height
End Sub

Private Sub menuEditFind_Click()
    On Error Resume Next
    WBAddrBook.ShowFind
End Sub

Private Sub menuFavoritesAddToFavorites_Click()
    Dim Favorites As ShellUIHelper
    Set Favorites = New ShellUIHelper
    Favorites.AddFavorite WebBrowser1.LocationURL, WebBrowser1.LocationName
End Sub

Private Sub menuFavoritesOrganizeFavorites_Click()
    WBAddrBook.ShowOrganizeFavorites (Me.hWnd)
End Sub

Private Sub menuFavoritesManageSubscriptions_Click()
    ' create a pathname for the subscriptions folder
    Dim Length As Long
    Dim WindowsDir As String
    WindowsDir = String(255, vbNullChar)
    Length = GetWindowsDirectory(WindowsDir, Len(WindowsDir))
    WindowsDir = Left(WindowsDir, Length) + "\Subscriptions"
    
    ' open a shell window for the subscriptions folder
    Dim Subscriptions As shell
    Set Subscriptions = New shell
    Subscriptions.Open (WindowsDir)
End Sub

Private Sub menuFile_Click()
    Dim status As Boolean
    status = (WebBrowser1.QueryStatusWB(OLECMDID_NEW) And OLECMDF_ENABLED)
    Me.menuFileNew.Enabled = status
    status = (WebBrowser1.QueryStatusWB(OLECMDID_OPEN) And OLECMDF_ENABLED)
    Me.menuFileOpen.Enabled = status
    status = (WebBrowser1.QueryStatusWB(OLECMDID_SAVE) And OLECMDF_ENABLED)
    Me.menuFileSave.Enabled = status
    status = (WebBrowser1.QueryStatusWB(OLECMDID_SAVEAS) And OLECMDF_ENABLED)
    Me.menuFileSaveAs.Enabled = status
    status = (WebBrowser1.QueryStatusWB(OLECMDID_PAGESETUP) And OLECMDF_ENABLED)
    Me.menuFilePageSetup.Enabled = status
    status = (WebBrowser1.QueryStatusWB(OLECMDID_PRINT) And OLECMDF_ENABLED)
    Me.menuFilePrint.Enabled = status
    Me.menuFileWorkOffline.Checked = WBAddrBook.Offline
End Sub

Private Sub menuFileNew_Click()
    On Error Resume Next
    WebBrowser1.ExecWB OLECMDID_NEW, OLECMDEXECOPT_PROMPTUSER
End Sub

Private Sub menuFileOpen_Click()
    Dim GetURL As New GetURL
    GetURL.Show 1, Me
    If GetURL.exitStatus = True Then
        WebBrowser1.Navigate GetURL.theURL.Text
    End If
    Unload GetURL
End Sub
Private Sub menuFilePageSetup_Click()
    On Error Resume Next
    WebBrowser1.ExecWB OLECMDID_PAGESETUP, OLECMDEXECOPT_PROMPTUSER
End Sub

Private Sub menuFilePrint_Click()
    On Error Resume Next
    WebBrowser1.ExecWB OLECMDID_PRINT, OLECMDEXECOPT_PROMPTUSER
End Sub
Private Sub menuFileSave_Click()
    On Error Resume Next
    WebBrowser1.ExecWB OLECMDID_SAVE, OLECMDEXECOPT_DODEFAULT
End Sub
Private Sub menuFileSaveAs_Click()
    On Error Resume Next
    WebBrowser1.ExecWB OLECMDID_SAVEAS, OLECMDEXECOPT_PROMPTUSER
End Sub
Private Sub menuFileWorkOffline_Click()
    ' see notes in WBAddrBook regarding why we are not using the WebBrowser property here
    Me.menuFileWorkOffline.Checked = Not Me.menuFileWorkOffline.Checked
    WBAddrBook.Offline = Me.menuFileWorkOffline.Checked
End Sub
Private Sub menuFileClose_Click()
    Unload MyWebBrowser
End Sub
Private Sub menuEdit_Click()
    Dim status As Boolean
    status = (WebBrowser1.QueryStatusWB(OLECMDID_CUT) And OLECMDF_ENABLED)
    Me.menuEditCut.Enabled = status
    status = (WebBrowser1.QueryStatusWB(OLECMDID_COPY) And OLECMDF_ENABLED)
    Me.menuEditCopy.Enabled = status
    status = (WebBrowser1.QueryStatusWB(OLECMDID_PASTE) And OLECMDF_ENABLED)
    Me.menuEditPaste.Enabled = status
    status = (WebBrowser1.QueryStatusWB(OLECMDID_SELECTALL) And OLECMDF_ENABLED)
    Me.menuEditSelectAll.Enabled = status
End Sub
Private Sub menuEditCut_Click()
    WebBrowser1.ExecWB OLECMDID_CUT, OLECMDEXECOPT_DODEFAULT
End Sub
Private Sub menuEditCopy_Click()
    WebBrowser1.ExecWB OLECMDID_COPY, OLECMDEXECOPT_DODEFAULT
End Sub
Private Sub menuEditPaste_Click()
    WebBrowser1.ExecWB OLECMDID_PASTE, OLECMDEXECOPT_DODEFAULT
End Sub

Private Sub menuEditSelectAll_Click()
    WebBrowser1.ExecWB OLECMDID_SELECTALL, OLECMDEXECOPT_DODEFAULT
End Sub

Private Sub menuGoBack_Click()
    WebBrowser1.GoBack
End Sub

Private Sub menuGoForward_Click()
    WebBrowser1.GoForward
End Sub

Private Sub menuGoHomePage_Click()
    WebBrowser1.GoHome
End Sub

Private Sub menuGoMyComputer_Click()
    WBAddrBook.ShowMyComputer (Me.hWnd)
End Sub

Private Sub menuGoSearchTheWeb_Click()
    WebBrowser1.GoSearch
End Sub
Private Sub menuGoNews_Click()
    WBAddrBook.ShowNews (Me.hWnd)
End Sub
Private Sub menuGoMail_Click()
    WBAddrBook.ShowMail (Me.hWnd)
End Sub

Private Sub menuGoAddressBook_Click()
    WBAddrBook.ShowAddressBook (Me.hWnd)
End Sub

Private Sub menuViewFonts_Click()
    ' let weboc remember our font size state
    Me.menuViewFontsLargest.Checked = False
    Me.menuViewFontsLarger.Checked = False
    Me.menuViewFontsMedium.Checked = False
    Me.menuViewFontsSmaller.Checked = False
    Me.menuViewFontsSmallest.Checked = False
    
    ' we know the range goes from 0 to 4
    Dim range As Variant
    MyWebBrowser.WebBrowser1.ExecWB OLECMDID_ZOOM, OLECMDEXECOPT_DONTPROMPTUSER, Null, range
    Select Case range
    Case 0
        Me.menuViewFontsSmallest.Checked = True
    Case 1
        Me.menuViewFontsSmaller.Checked = True
    Case 2
        Me.menuViewFontsMedium.Checked = True
    Case 3
        Me.menuViewFontsLarger.Checked = True
    Case 4
        Me.menuViewFontsLargest.Checked = True
    End Select
End Sub
Private Sub setFontSize(size As Integer)
    Dim range As Variant
    range = CLng(size)
    WebBrowser1.ExecWB OLECMDID_ZOOM, OLECMDEXECOPT_DONTPROMPTUSER, range, Null
End Sub
Private Sub menuViewFontsLargest_Click()
    setFontSize (4)
End Sub
Private Sub menuViewFontsLarger_Click()
    setFontSize (3)
End Sub
Private Sub menuViewFontsMedium_Click()
    setFontSize (2)
End Sub
Private Sub menuViewFontsSmaller_Click()
    setFontSize (1)
End Sub
Private Sub menuViewFontsSmallest_Click()
    setFontSize (0)
End Sub

Private Sub menuViewRefresh_Click()
    WebBrowser1.Refresh
End Sub

Private Sub menuViewStop_Click()
    WebBrowser1.Stop
End Sub
Private Sub menuViewSource_Click()
    On Error Resume Next
    WBAddrBook.ShowViewSource
End Sub
Private Sub menuViewInternetOptions_Click()
    On Error Resume Next
    WBAddrBook.ShowProperties
End Sub

Private Sub ShowFavorites_Click()
    Dim MyShell As New shell
    If Not (MyShell Is Nothing) Then
        MyShell.Open (ssfFAVORITES)
    End If
End Sub

Private Sub WebBrowser1_CommandStateChange(ByVal Command As Long, ByVal Enable As Boolean)
    Select Case Command
        Case CSC_NAVIGATEBACK
            Me.menuGoBack.Enabled = Enable
        Case CSC_NAVIGATEFORWARD
            Me.menuGoForward.Enabled = Enable
    End Select
End Sub

Private Sub WebBrowser1_DownloadComplete()
    'this will popup a dialog upon receiving the IE4 DownloadComplete event
    'webBrowser1.Document.parentWindow.execScript "document.body.onclick = new Function(""alert('hi mom')"")", "javascript"
End Sub

Private Sub WebBrowser1_NavigateComplete2(ByVal pDisp As Object, URL As Variant)
    Me.enter_url.Text = URL
End Sub

Private Sub WebBrowser1_NewWindow2(ppDisp As Object, Cancel As Boolean)
    ' start a new instance of MyWebBrowser (instead of IE)
    Dim frmWB As MyWebBrowser
    Set frmWB = New MyWebBrowser
    Set ppDisp = frmWB.WebBrowser1.Object
    frmWB.Visible = True
    Set frmWB = Nothing
End Sub

Private Sub WebBrowser1_TitleChange(ByVal Text As String)
    Me.Caption = Text + " - VB5 Browser"
End Sub
