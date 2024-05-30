VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form frmEventRegister 
   Caption         =   "CDO Transport Event Registration Tool"
   ClientHeight    =   5385
   ClientLeft      =   165
   ClientTop       =   735
   ClientWidth     =   9450
   Icon            =   "frmEventRegister.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   5385
   ScaleWidth      =   9450
   StartUpPosition =   3  'Windows Default
   Begin MSComctlLib.TreeView treeRegistrations 
      Height          =   4815
      Left            =   120
      TabIndex        =   0
      Top             =   480
      Width           =   3735
      _ExtentX        =   6588
      _ExtentY        =   8493
      _Version        =   393217
      HideSelection   =   0   'False
      Indentation     =   0
      LabelEdit       =   1
      LineStyle       =   1
      Style           =   7
      ImageList       =   "ilistEnabled"
      Appearance      =   1
      MousePointer    =   1
   End
   Begin VB.Frame frameDetails 
      Caption         =   "Properties"
      Height          =   2295
      Index           =   1
      Left            =   4080
      TabIndex        =   7
      Top             =   2880
      Visible         =   0   'False
      Width           =   4695
      Begin VB.CommandButton cmdSource 
         Caption         =   "Source "
         Enabled         =   0   'False
         Height          =   375
         Left            =   1680
         TabIndex        =   35
         ToolTipText     =   "Displays source properties."
         Top             =   1800
         Width           =   1215
      End
      Begin VB.PictureBox Picture1 
         BorderStyle     =   0  'None
         Height          =   495
         Left            =   120
         Picture         =   "frmEventRegister.frx":0442
         ScaleHeight     =   495
         ScaleWidth      =   495
         TabIndex        =   8
         TabStop         =   0   'False
         Top             =   360
         Width           =   495
      End
      Begin VB.CommandButton cmdBinding 
         Caption         =   "Event Binding"
         Enabled         =   0   'False
         Height          =   375
         Left            =   120
         TabIndex        =   33
         ToolTipText     =   "Displays event binding properties."
         Top             =   1800
         Width           =   1215
      End
      Begin VB.CommandButton cmdSink 
         Caption         =   "Sink"
         Enabled         =   0   'False
         Height          =   375
         Left            =   3240
         TabIndex        =   37
         ToolTipText     =   "Displays sink properties."
         Top             =   1800
         Width           =   1215
      End
      Begin VB.Label Label10 
         Caption         =   $"frmEventRegister.frx":0884
         Height          =   975
         Left            =   840
         TabIndex        =   9
         Top             =   360
         Width           =   3735
      End
   End
   Begin VB.Frame frameModify 
      Caption         =   "Modify this event registration"
      Height          =   1215
      Index           =   0
      Left            =   4080
      TabIndex        =   36
      Top             =   3360
      Visible         =   0   'False
      Width           =   4695
      Begin VB.CommandButton cmdModify 
         Caption         =   "Modify"
         Enabled         =   0   'False
         Height          =   375
         Left            =   3240
         TabIndex        =   40
         Top             =   720
         Width           =   1335
      End
      Begin VB.PictureBox Picture5 
         BorderStyle     =   0  'None
         Height          =   495
         Left            =   120
         Picture         =   "frmEventRegister.frx":0925
         ScaleHeight     =   495
         ScaleWidth      =   615
         TabIndex        =   39
         TabStop         =   0   'False
         Top             =   360
         Width           =   615
      End
      Begin VB.Label Label16 
         Caption         =   "You can use the wizard to modify this event registration. "
         Height          =   495
         Left            =   840
         TabIndex        =   38
         Top             =   360
         Width           =   3735
      End
   End
   Begin MSComctlLib.ImageList ilistEnabled 
      Left            =   8760
      Top             =   0
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   22
      ImageHeight     =   16
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   6
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmEventRegister.frx":0D67
            Key             =   "event"
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmEventRegister.frx":11F9
            Key             =   "disabled"
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmEventRegister.frx":168B
            Key             =   "nntp"
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmEventRegister.frx":1B1D
            Key             =   "enabled"
         EndProperty
         BeginProperty ListImage5 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmEventRegister.frx":1FAF
            Key             =   "server"
         EndProperty
         BeginProperty ListImage6 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmEventRegister.frx":2441
            Key             =   "smtp"
         EndProperty
      EndProperty
   End
   Begin VB.Frame frameOverview 
      Caption         =   "Event Registration Properties"
      Height          =   1815
      Index           =   0
      Left            =   4080
      TabIndex        =   41
      Top             =   600
      Width           =   4695
      Begin VB.PictureBox Picture2 
         BorderStyle     =   0  'None
         Height          =   375
         Left            =   120
         Picture         =   "frmEventRegister.frx":28D3
         ScaleHeight     =   375
         ScaleWidth      =   615
         TabIndex        =   42
         TabStop         =   0   'False
         Top             =   240
         Width           =   615
      End
      Begin VB.Label Label17 
         Caption         =   "Priority:"
         Height          =   255
         Left            =   2520
         TabIndex        =   53
         ToolTipText     =   "Priority indicates the order in which a sink is fired.  A lower number indicates a higher priority."
         Top             =   1200
         Width           =   615
      End
      Begin VB.Label lblPrio 
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
         Left            =   3120
         TabIndex        =   52
         ToolTipText     =   "Priority indicates the order in which a sink is fired.  A lower number indicates a higher priority."
         Top             =   1200
         Width           =   1455
      End
      Begin VB.Label lblRegName 
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
         Left            =   600
         TabIndex        =   51
         Top             =   960
         Width           =   3975
      End
      Begin VB.Label Label1 
         Caption         =   "Name:"
         Height          =   255
         Left            =   120
         TabIndex        =   50
         ToolTipText     =   "This is a friendly name for this event registration."
         Top             =   960
         Width           =   495
      End
      Begin VB.Label Label14 
         Caption         =   $"frmEventRegister.frx":2D15
         Height          =   615
         Left            =   720
         TabIndex        =   49
         Top             =   240
         Width           =   3855
      End
      Begin VB.Label lblEventName 
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
         Left            =   600
         TabIndex        =   48
         ToolTipText     =   "This is the name of the event associated with this registration."
         Top             =   1440
         Width           =   1935
      End
      Begin VB.Label Label13 
         Caption         =   "Event:"
         Height          =   255
         Left            =   120
         TabIndex        =   47
         ToolTipText     =   "This is the name of the event associated with this registration."
         Top             =   1440
         Width           =   1095
      End
      Begin VB.Label lblServerNum 
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
         Left            =   3840
         TabIndex        =   46
         ToolTipText     =   "This is the number of the virtual server this event registration applies to."
         Top             =   1440
         Width           =   735
      End
      Begin VB.Label Label12 
         Caption         =   "Virtual Server #:"
         Height          =   255
         Left            =   2520
         TabIndex        =   45
         ToolTipText     =   "This is the number of the virtual server this event registration applies to."
         Top             =   1440
         Width           =   1215
      End
      Begin VB.Label lblService 
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
         Left            =   720
         TabIndex        =   44
         ToolTipText     =   "This is the service (SMTP or NNTP) that this registration applies to."
         Top             =   1200
         Width           =   1095
      End
      Begin VB.Label Label11 
         Caption         =   "Service:"
         Height          =   255
         Left            =   120
         TabIndex        =   43
         ToolTipText     =   "This is the service (SMTP or NNTP) that this registration applies to."
         Top             =   1200
         Width           =   615
      End
   End
   Begin VB.Frame frameModify 
      Caption         =   "Delete"
      Height          =   1215
      Index           =   2
      Left            =   4080
      TabIndex        =   22
      Top             =   600
      Visible         =   0   'False
      Width           =   4695
      Begin VB.CommandButton cmdDelete 
         Caption         =   "Delete"
         Enabled         =   0   'False
         Height          =   375
         Left            =   3240
         TabIndex        =   25
         ToolTipText     =   "Unregister this sink for this event."
         Top             =   720
         Width           =   1335
      End
      Begin VB.PictureBox Picture4 
         BorderStyle     =   0  'None
         Height          =   495
         Left            =   120
         Picture         =   "frmEventRegister.frx":2DAB
         ScaleHeight     =   495
         ScaleWidth      =   615
         TabIndex        =   24
         TabStop         =   0   'False
         Top             =   240
         Width           =   615
      End
      Begin VB.Label Label3 
         Caption         =   "This will delete this event registration information from the event binding database."
         Height          =   495
         Left            =   720
         TabIndex        =   23
         Top             =   240
         Width           =   3855
      End
   End
   Begin VB.Frame frameModify 
      Caption         =   "Enable or Disable this event registration"
      Height          =   1335
      Index           =   1
      Left            =   4080
      TabIndex        =   26
      Top             =   1920
      Visible         =   0   'False
      Width           =   4695
      Begin VB.PictureBox pictGo 
         BorderStyle     =   0  'None
         Height          =   615
         Left            =   120
         Picture         =   "frmEventRegister.frx":31ED
         ScaleHeight     =   615
         ScaleWidth      =   615
         TabIndex        =   30
         ToolTipText     =   "This event registration is enabled."
         Top             =   240
         Visible         =   0   'False
         Width           =   615
      End
      Begin VB.CommandButton cmdDisable 
         Caption         =   "Disable"
         Enabled         =   0   'False
         Height          =   375
         Left            =   1800
         TabIndex        =   29
         ToolTipText     =   "Disable this event registration."
         Top             =   840
         Width           =   1335
      End
      Begin VB.CommandButton cmdEnable 
         Caption         =   "Enable"
         Enabled         =   0   'False
         Height          =   375
         Left            =   3240
         TabIndex        =   31
         ToolTipText     =   "Enable this event registration."
         Top             =   840
         Width           =   1335
      End
      Begin VB.PictureBox pictStopped 
         BorderStyle     =   0  'None
         Height          =   615
         Left            =   120
         Picture         =   "frmEventRegister.frx":362F
         ScaleHeight     =   615
         ScaleWidth      =   615
         TabIndex        =   27
         ToolTipText     =   "This event registration is disabled."
         Top             =   240
         Visible         =   0   'False
         Width           =   615
      End
      Begin VB.Label Label6 
         Caption         =   "If you disable the registration, then this event sink will not be run when its corresponding event is fired."
         Height          =   495
         Left            =   840
         TabIndex        =   28
         Top             =   360
         Width           =   3735
      End
   End
   Begin VB.Frame frameOverview 
      Caption         =   "Event Sink Properties"
      Height          =   1695
      Index           =   1
      Left            =   4080
      TabIndex        =   10
      Top             =   2520
      Width           =   4695
      Begin VB.PictureBox Picture3 
         BorderStyle     =   0  'None
         Height          =   495
         Left            =   120
         Picture         =   "frmEventRegister.frx":3A71
         ScaleHeight     =   495
         ScaleWidth      =   615
         TabIndex        =   18
         TabStop         =   0   'False
         Top             =   240
         Width           =   615
      End
      Begin VB.Label Label2 
         Caption         =   "The class of the registered sink, the rule used to trigger that sink, and the current status are listed here."
         Height          =   615
         Left            =   720
         TabIndex        =   17
         Top             =   240
         Width           =   3855
      End
      Begin VB.Label lblStatus 
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
         Left            =   720
         TabIndex        =   16
         ToolTipText     =   "Indicates if this registration is currently enabled."
         Top             =   1320
         Width           =   2175
      End
      Begin VB.Label Label8 
         Caption         =   "Status:"
         Height          =   255
         Left            =   120
         TabIndex        =   15
         ToolTipText     =   "Indicates if this registration is currently enabled."
         Top             =   1320
         Width           =   495
      End
      Begin VB.Label lblRule 
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
         Left            =   600
         TabIndex        =   14
         ToolTipText     =   "This is a rule that dictates when the sink is called if this event is raised."
         Top             =   1080
         Width           =   3975
      End
      Begin VB.Label Label5 
         Caption         =   "Rule:"
         Height          =   255
         Left            =   120
         TabIndex        =   13
         ToolTipText     =   "This is a rule that dictates when the sink is called if this event is raised."
         Top             =   1080
         Width           =   495
      End
      Begin VB.Label lblSinkClass 
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
         Left            =   960
         TabIndex        =   12
         ToolTipText     =   "This is the ProgID for the sink (handler) for this event registration."
         Top             =   840
         Width           =   3615
      End
      Begin VB.Label Label4 
         Caption         =   "Sink Class:"
         Height          =   255
         Left            =   120
         TabIndex        =   11
         ToolTipText     =   "This is the ProgID for the sink (handler) for this event registration."
         Top             =   840
         Width           =   855
      End
   End
   Begin VB.Frame frameOverview 
      Caption         =   "Script Location"
      Height          =   855
      Index           =   2
      Left            =   4080
      TabIndex        =   19
      Top             =   4320
      Width           =   4695
      Begin VB.Label lblScriptName 
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   495
         Left            =   600
         TabIndex        =   21
         ToolTipText     =   "This is the script that is run if this is a script-based event sink."
         Top             =   240
         Width           =   3975
         WordWrap        =   -1  'True
      End
      Begin VB.Label label7 
         Caption         =   "Script:"
         Height          =   255
         Left            =   120
         TabIndex        =   20
         ToolTipText     =   "This is the script that is run if this is a script-based event sink."
         Top             =   240
         Width           =   495
      End
   End
   Begin VB.Frame frameDetails 
      Caption         =   "Details"
      Height          =   2175
      Index           =   0
      Left            =   4080
      TabIndex        =   2
      Top             =   600
      Visible         =   0   'False
      Width           =   4695
      Begin VB.Label lblEventGUID 
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
         Left            =   480
         TabIndex        =   34
         ToolTipText     =   "This is the GUID for the event."
         Top             =   1080
         Width           =   4095
         WordWrap        =   -1  'True
      End
      Begin VB.Label Label15 
         Caption         =   "Event ID:"
         Height          =   255
         Left            =   120
         TabIndex        =   32
         ToolTipText     =   "This is the GUID for the event."
         Top             =   840
         Width           =   735
      End
      Begin VB.Label Label21 
         Caption         =   "Source ID:"
         Height          =   255
         Left            =   120
         TabIndex        =   6
         ToolTipText     =   "This GUID identifies the event source."
         Top             =   360
         Width           =   1335
      End
      Begin VB.Label lblSourceGUID 
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
         Left            =   480
         TabIndex        =   5
         ToolTipText     =   "This GUID identifies the event source."
         Top             =   600
         Width           =   4095
         WordWrap        =   -1  'True
      End
      Begin VB.Label Label19 
         Caption         =   "Binding ID:"
         Height          =   255
         Left            =   120
         TabIndex        =   4
         ToolTipText     =   "This is the GUID for this event binding."
         Top             =   1320
         Width           =   1215
      End
      Begin VB.Label lblEventBindingGUID 
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
         Left            =   480
         TabIndex        =   3
         ToolTipText     =   "This is the GUID for this event binding."
         Top             =   1560
         Width           =   4095
         WordWrap        =   -1  'True
      End
   End
   Begin MSComctlLib.TabStrip TabStrip1 
      Height          =   4815
      Left            =   3960
      TabIndex        =   1
      Top             =   480
      Width           =   5295
      _ExtentX        =   9340
      _ExtentY        =   8493
      MultiRow        =   -1  'True
      Placement       =   3
      _Version        =   393216
      BeginProperty Tabs {1EFB6598-857C-11D1-B16A-00C0F0283628} 
         NumTabs         =   3
         BeginProperty Tab1 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "Overview"
            Key             =   "keyOverview"
            Object.ToolTipText     =   "Overview of the registration information"
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab2 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "Details"
            Key             =   "keyDetails"
            Object.ToolTipText     =   "Details, including GUIDs, of the event registration information"
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab3 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "Modify"
            Key             =   "keyModify"
            Object.ToolTipText     =   "Modify this registration."
            ImageVarType    =   2
         EndProperty
      EndProperty
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&File"
      Begin VB.Menu mnuExit 
         Caption         =   "E&xit"
         Shortcut        =   ^Q
      End
   End
   Begin VB.Menu mnuEventSink 
      Caption         =   "&Selected Sink"
      Visible         =   0   'False
      Begin VB.Menu mnuModify 
         Caption         =   "&Modify Sink Registration..."
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuDelete 
         Caption         =   "&Delete Sink Registration..."
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuDisable 
         Caption         =   "Di&sable Event Sink"
      End
      Begin VB.Menu mnuEnable 
         Caption         =   "&Enable Event Sink"
      End
      Begin VB.Menu mnuDuplicate 
         Caption         =   "Du&plicate Sink Registration"
         Enabled         =   0   'False
      End
   End
   Begin VB.Menu mnuRegistrations 
      Caption         =   "&Registrations"
      Begin VB.Menu mnuAddReg 
         Caption         =   "&Add Event Sink Registration Wizard..."
         Shortcut        =   ^A
      End
      Begin VB.Menu mnuSeperator2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuDisableAll 
         Caption         =   "&Disable All Event Sinks"
      End
      Begin VB.Menu mnuEnableAll 
         Caption         =   "&Enable All Event Sinks"
      End
      Begin VB.Menu mnuDeleteAll 
         Caption         =   "De&lete All Event Registrations..."
      End
      Begin VB.Menu mnuSeperator1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuRefresh 
         Caption         =   "&Refresh"
         Shortcut        =   ^R
      End
   End
   Begin VB.Menu mnuSelectedEvent 
      Caption         =   "Selected Event"
      Visible         =   0   'False
      Begin VB.Menu mnuEventDisable 
         Caption         =   "&Disable All Sinks for this Event"
      End
      Begin VB.Menu mnuEventEnable 
         Caption         =   "&Enable All Sinks for this Event"
      End
      Begin VB.Menu mnuEventDelete 
         Caption         =   "De&lete All Sinks for this Event"
      End
   End
   Begin VB.Menu mnuServer 
      Caption         =   "Selected Server"
      Visible         =   0   'False
      Begin VB.Menu mnuServerDisable 
         Caption         =   "&Disable All Sinks for this Server"
      End
      Begin VB.Menu mnuServerEnable 
         Caption         =   "&Enable All Sinks for this Server"
      End
      Begin VB.Menu mnuServerDelete 
         Caption         =   "De&lete All Sinks for this Server"
      End
   End
   Begin VB.Menu mnuService 
      Caption         =   "Selected Service"
      Visible         =   0   'False
      Begin VB.Menu mnuServiceDisable 
         Caption         =   "&Disable All Sinks for this Service"
      End
      Begin VB.Menu mnuServiceEnable 
         Caption         =   "&Enable All Sinks for this Service"
      End
      Begin VB.Menu mnuServiceDelete 
         Caption         =   "De&lete All Sinks for this Service"
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "&Help"
      Begin VB.Menu mnuAbout 
         Caption         =   "&About"
      End
   End
End
Attribute VB_Name = "frmEventRegister"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit


' Const GUIDCat = "{871736c0-fd85-11d0-869a-00c04fd65616}"
' Const GUIDSources = "{DBC71A31-1F4B-11d0-869D-80C04FD65616}"


Dim Registrations As New Collection
Dim currentReg As EventRegistrationInfo

Dim ShowPopupMenu As Boolean

Private Sub LoadSinkInfo()
    Dim I As Integer
    
    ' Have to clear these before refresh in case the server
    ' has been restarted or stopped.
    Set currentReg = Nothing
    While Registrations.Count > 0
        Registrations.Remove 1
    Wend
    
        
    If Not LoadSinkSuccess Then
        MsgBox "The server does not exist or is unavailable.  Please exit and then reload this program.  If that fails, shut down or restart your inetinfo.exe process.  (""net stop iisadmin"")", vbExclamation, "Server unavailable."
    End If
    
End Sub
Private Function LoadSinkSuccess() As Boolean
    On Error GoTo ErrorHandler

    Dim SourceType As IEventSourceType
    Dim Source As IEventSource
    Dim newEvent As EventRegistrationInfo
    Dim eInfo As EventRegistrationInfo
    Dim Binding As IEventBinding
    Dim I As EventTypes
    Dim ErrCount As Integer
    Dim EventManager As CEventManager
    
    Set EventManager = New CEventManager
    
    For I = OnArrival To OnPostFinal
        Set SourceType = EventManager.SourceTypes(GetEvtSourceTypeGUID(I))
        For Each Source In SourceType.Sources
            For Each Binding In Source.GetBindingManager.Bindings(GetEvtGUID(I))
                Set newEvent = New EventRegistrationInfo
                Set newEvent.Source = Source
                Set newEvent.Binding = Binding
                newEvent.Service = GetEvtService(I)
                newEvent.VirtualServerNumber = Val(Trim(Right(Source.DisplayName, Len(Source.DisplayName) - Len(GetEvtService(I)))))
                newEvent.EventNum = I
                If Binding.SinkClass = GetEvtSSClass(I) Then
                    newEvent.SinkType = ScriptSink
                Else
                    newEvent.SinkType = DLLSink
                End If
                Registrations.Add newEvent, newEvent.Binding.ID
            Next
        Next
    Next

    LoadSinkSuccess = True
    Exit Function

ErrorHandler:
    If Err.Number = 462 Then
       LoadSinkSuccess = False
        Err.Clear
    Else
        MsgBox "An unexpected error occured when loading event binding information.  " & vbCrLf & "Error: " & Err.Description & vbCrLf & "Err #: " & Hex(Err.Number), vbCritical, "Error!"
        LoadSinkSuccess = False
        Err.Clear
    End If
  
End Function

Private Sub LoadTree()
    On Error Resume Next

    Dim eInfo As EventRegistrationInfo
    Dim serviceNode As Node
    Dim serverNode As Node
    Dim eventNode As Node
    Dim bindNode As Node
    Dim strName As String

        
    While treeRegistrations.Nodes.Count > 0
        treeRegistrations.Nodes.Remove 1
    Wend
    
    For Each eInfo In Registrations
        
        ' Check to see if a node exists for this service (NNTP or SMTP)
        Set serviceNode = treeRegistrations.Nodes(eInfo.Service)
        If Err.Number = 35601 Then
            Err.Clear
            If eInfo.Service = szSMTPService Then strName = "SMTP Servers"
            If eInfo.Service = szNNTPService Then strName = "NNTP Servers"
            Set serviceNode = treeRegistrations.Nodes.Add(, , eInfo.Service, strName)
            If eInfo.Service = szSMTPService Then serviceNode.Image = "smtp"
            If eInfo.Service = szNNTPService Then serviceNode.Image = "nntp"
            serviceNode.Expanded = True
        End If
        
        Set serverNode = treeRegistrations.Nodes(serviceNode.Key & ":" & eInfo.VirtualServerNumber)
        If Err.Number = 35601 Then
            Err.Clear
            Set serverNode = treeRegistrations.Nodes.Add(serviceNode.Key, tvwChild, serviceNode.Key & ":" & eInfo.VirtualServerNumber, "Virtual Server #" & eInfo.VirtualServerNumber)
            serverNode.Image = "server"
            serverNode.Expanded = True
        End If
        
        Set eventNode = treeRegistrations.Nodes(serverNode.Key & ":" & eInfo.EventNum)
        If Err.Number = 35601 Then
            Err.Clear
            Set eventNode = treeRegistrations.Nodes.Add(serverNode.Key, tvwChild, serverNode.Key & ":" & eInfo.EventNum, GetEvtName(eInfo.EventNum))
            eventNode.Tag = eInfo.EventNum
            eventNode.Image = "event"
            eventNode.Expanded = True
        End If
        
        Set bindNode = treeRegistrations.Nodes(eventNode.Key & ":" & eInfo.Binding.ID)
        If Err.Number = 35601 Then
            Err.Clear
            Set bindNode = treeRegistrations.Nodes.Add(eventNode.Key, tvwChild, eventNode.Key & ":" & eInfo.Binding.ID, eInfo.Binding.DisplayName)
            If eInfo.Binding.Enabled Then
                bindNode.Image = "enabled"
            Else
                bindNode.Image = "disabled"
            End If
        End If
    Next

End Sub

Private Sub cmdDelete_Click()
    Dim Result As VbMsgBoxResult
    Dim currentNode As Node
    
    If Not currentReg Is Nothing Then
        Result = MsgBox("Are you sure you want to delete the registration for " & currentReg.Binding.DisplayName & "?", vbYesNo, "Delete?")
        If Result = vbYes Then
            RemoveRegistration currentReg
            RefreshBindings
        End If
    End If
End Sub

Private Sub cmdDisable_Click()
    Dim currentNode As Node
        
    If Not (currentReg Is Nothing) Then
        currentReg.Binding.Enabled = False
        currentReg.Binding.Save
        
        
        Set currentNode = treeRegistrations.Nodes(currentReg.Key)
        If Err.Number = 0 Then
            currentNode.Image = "disabled"
        Else
            Err.Clear
        End If
        
        LoadDetails currentReg.Binding.ID
    End If
    
End Sub

Private Sub cmdEnable_Click()
    Dim currentNode As Node

    If Not (currentReg Is Nothing) Then
        currentReg.Binding.Enabled = True
        currentReg.Binding.Save
        
        Set currentNode = treeRegistrations.Nodes(currentReg.Key)
        If Err.Number = 0 Then
            currentNode.Image = "enabled"
        Else
            Err.Clear
        End If
        
        LoadDetails currentReg.Binding.ID
    End If
End Sub

Private Sub cmdModify_Click()
    Dim frm As New frmWizard
    frm.ModifyReg currentReg
    frm.Show vbModal, Me
    RefreshBindings
End Sub

Private Sub cmdSink_Click()
    Dim frm As New frmProps
    
    frm.Top = Me.Top + 300
    frm.Left = Me.Left + 300
    frm.Caption = "Sink properties for this event registration."
    Set frm.Props = currentReg.Binding.SinkProperties
    frm.Show vbModal, Me
End Sub

Private Sub cmdSource_Click()
    Dim frm As New frmProps
    
    frm.Top = Me.Top + 300
    frm.Left = Me.Left + 300
    Set frm.Props = currentReg.Binding.SourceProperties
    frm.Caption = "Source properties for this event registration."
    frm.Show vbModal, Me
    
End Sub

Private Sub cmdBinding_Click()
    Dim frm As New frmProps
        
    frm.Top = Me.Top + 300
    frm.Left = Me.Left + 300
    Set frm.Props = currentReg.Binding.EventBindingProperties
    frm.Caption = "Binding properties for this event registration."
    frm.Show vbModal, Me
End Sub


Private Sub Form_Load()
    On Error GoTo ErrorHandler
    Dim Result As VbMsgBoxResult
   
    RefreshBindings

    Exit Sub
ErrorHandler:
    If Err.Number = 429 Then
        MsgBox "It is likely that you do not have the SMTP or NNTP service installed on this machine." & vbCrLf & "Error: " & Err.Description & vbCrLf & "Err #: " & Hex(Err.Number), vbCritical, "Error!"
    Else
        Result = MsgBox("There has been an unexpected error." & vbCrLf & "Error: " & Err.Description & vbCrLf & "Err #: " & Hex(Err.Number), vbAbortRetryIgnore, "Error!")
        Select Case Result
            Case vbAbort:
                Unload Me
            Case vbRetry:
                Form_Load
        End Select
    End If
End Sub



Private Sub LoadDetails(Key As String)
    On Error GoTo CannotLoad
    
    Dim PrevFailed As Boolean
    Set currentReg = Nothing
    
    PrevFailed = False
    If Key <> "" Then
        
        
        ' First load all of the fields for the property pages
        Set currentReg = Registrations(Key)
        lblService.Caption = currentReg.Service
        lblServerNum.Caption = currentReg.VirtualServerNumber
        lblSinkClass.Caption = currentReg.Binding.SinkClass
        lblRule.Caption = currentReg.Binding.SourceProperties("Rule")
        lblEventName.Caption = GetEvtName(currentReg.EventNum)
        lblSourceGUID.Caption = currentReg.Source.ID
        lblEventBindingGUID.Caption = currentReg.Binding.ID
        lblRegName.Caption = currentReg.Binding.DisplayName
        lblRegName.ToolTipText = currentReg.Binding.DisplayName
        lblEventGUID.Caption = GetEvtGUID(currentReg.EventNum)
        lblPrio.Caption = currentReg.Binding.SourceProperties("Priority")
           
   
        If currentReg.Binding.Enabled Then
            lblStatus.Caption = "Enabled"
        Else
            lblStatus.Caption = "Disabled"
        End If
        
        If currentReg.SinkType = ScriptSink Then
            lblScriptName.Caption = currentReg.Binding.SinkProperties("ScriptName")
        Else
            lblScriptName.Caption = ""
        End If
        
        
        ' Enable the appropriate buttons
        If currentReg.Binding.Enabled Then
            cmdEnable.Enabled = False
            cmdDisable.Enabled = True
            pictGo.Visible = True
            pictStopped.Visible = False
        Else
            cmdEnable.Enabled = True
            cmdDisable.Enabled = False
            pictGo.Visible = False
            pictStopped.Visible = True
        End If
        
        mnuModify.Enabled = True
        mnuDelete.Enabled = True
        mnuDuplicate.Enabled = True
        mnuDuplicate.Enabled = True
        cmdBinding.Enabled = True
        cmdSink.Enabled = True
        cmdSource.Enabled = True
        cmdModify.Enabled = True
        cmdDelete.Enabled = True
        
        
    Else
        ' Clear the informational fields
        lblRegName.ToolTipText = ""
        lblEventGUID.Caption = ""
        lblService.Caption = ""
        lblServerNum.Caption = ""
        lblSinkClass.Caption = ""
        lblRule.Caption = ""
        lblEventName.Caption = ""
        lblScriptName.Caption = ""
        lblSourceGUID.Caption = ""
        lblEventBindingGUID.Caption = ""
        lblStatus.Caption = ""
        lblRegName.Caption = ""
        lblPrio.Caption = ""
        Set currentReg = Nothing
        
        ' Disable the appropriate buttons
        cmdDisable.Enabled = False
        cmdEnable.Enabled = False
        cmdDelete.Enabled = False
        cmdModify.Enabled = False
        mnuModify.Enabled = False
        mnuDelete.Enabled = False
        mnuDuplicate.Enabled = False
        cmdBinding.Enabled = False
        cmdSink.Enabled = False
        cmdSource.Enabled = False
        
        ' Hide the status indicating traffic lights
        pictGo.Visible = False
        pictStopped.Visible = True
        
    End If
    
    Exit Sub
CannotLoad:
    If Not PrevFailed Then
        RefreshBindings
        PrevFailed = True
        Err.Clear
        Resume
    Else
        MsgBox "Could not load registration information for the specified event sink (" & Key & ").  Try refreshing your event binding information under the ""Registrations"" menu.", vbCritical
        Err.Clear
    End If
End Sub


Private Sub Form_Resize()
    Dim frme As Frame

    If Me.WindowState <> 1 Then
    If Me.Width <= 9570 Then
        TabStrip1.Left = 3960
        For Each frme In frameOverview
            frme.Left = 4080
        Next
        For Each frme In frameDetails
            frme.Left = 4080
        Next
        For Each frme In frameModify
            frme.Left = 4080
        Next
        treeRegistrations.Width = 3735
    Else
        TabStrip1.Left = 3960 + Me.Width - 9570
        For Each frme In frameOverview
            frme.Left = 4080 + Me.Width - 9570
        Next
        For Each frme In frameDetails
            frme.Left = 4080 + Me.Width - 9570
        Next
        For Each frme In frameModify
            frme.Left = 4080 + Me.Width - 9570
        Next
        treeRegistrations.Width = 3735 + Me.Width - 9570
    End If
    
    If (4815 + Me.Height - 6075) > 0 Then
        treeRegistrations.Height = 4815 + Me.Height - 6075
    End If
    End If

End Sub



Private Sub mnuAbout_Click()
    frmAbout.Show vbModal, Me
End Sub

Private Sub mnuAddReg_Click()
    frmWizard.Show vbModal, Me
    RefreshBindings
End Sub

Private Sub mnuDelete_Click()
    If Not (currentReg Is Nothing) Then
        cmdDelete_Click
    End If
End Sub

Private Sub mnuDeleteAll_Click()
    Dim eInfo As EventRegistrationInfo
    
    If MsgBox("This will delete the registration information for all of your event sinks.  Are you sure you want to do this?", vbYesNo, "Delete all registrations?") = vbYes Then
        For Each eInfo In Registrations
            RemoveRegistration eInfo
        Next
    
        RefreshBindings
    End If
End Sub

Private Sub mnuDisable_Click()
    cmdDisable_Click
End Sub

Private Sub mnuDuplicate_Click()
    Dim NewBndg As IEventBinding
    Dim I As Integer
    
    Set NewBndg = currentReg.Source.GetBindingManager.Bindings(GetEvtGUID(currentReg.EventNum)).Add("")
    With NewBndg
        
        For I = 1 To currentReg.Binding.EventBindingProperties.Count
            .EventBindingProperties.Add currentReg.Binding.EventBindingProperties.Name(I), currentReg.Binding.EventBindingProperties.Item(I)
        Next
                
        .Save
    End With
    
    RefreshBindings
End Sub

Private Sub mnuEnable_Click()
    cmdEnable_Click
End Sub

Private Sub mnuEnableAll_Click()
On Error Resume Next

    Dim bndg As IEventBinding
    Dim eInfo As EventRegistrationInfo
    Dim currentNode As Node

    For Each eInfo In Registrations
        Set bndg = eInfo.Binding
        bndg.Enabled = True
        bndg.Save
        
        Set currentNode = treeRegistrations.Nodes(eInfo.Key)
        If Err.Number = 0 Then
            currentNode.Image = "enabled"
        Else
            Err.Clear
        End If
        
    Next
    
    If Not (currentReg Is Nothing) Then
        LoadDetails currentReg.Binding.ID
    End If
End Sub

Private Sub mnuDisableAll_Click()
    On Error Resume Next

    Dim bndg As IEventBinding
    Dim eInfo As EventRegistrationInfo
    Dim currentNode As Node

    For Each eInfo In Registrations
        Set bndg = eInfo.Binding
        bndg.Enabled = False
        bndg.Save
        
        Set currentNode = treeRegistrations.Nodes(eInfo.Key)
        If Err.Number = 0 Then
            currentNode.Image = "disabled"
        Else
            Err.Clear
        End If
        
    Next
    
    If Not (currentReg Is Nothing) Then
        LoadDetails currentReg.Binding.ID
    End If
End Sub

Private Sub mnuEventDelete_Click()
    Dim eInfo As EventRegistrationInfo
        
    If MsgBox("Are you sure you want to delete all registrations for this event?", vbYesNo, "Delete registrations?") = vbYes Then
        For Each eInfo In Registrations
            If (eInfo.Service & ":" & eInfo.VirtualServerNumber & ":" & eInfo.EventNum) = treeRegistrations.SelectedItem.Key Then
                RemoveRegistration eInfo
            End If
        Next
        
        RefreshBindings
    End If
End Sub

Private Sub mnuEventDisable_Click()
    On Error Resume Next

    Dim eInfo As EventRegistrationInfo
    Dim bndg As IEventBinding
    Dim currentNode As Node
  
        For Each eInfo In Registrations
            If (eInfo.Service & ":" & eInfo.VirtualServerNumber & ":" & eInfo.EventNum) = treeRegistrations.SelectedItem.Key Then
                Set bndg = eInfo.Binding
                bndg.Enabled = False
                bndg.Save
                
                Set currentNode = treeRegistrations.Nodes(eInfo.Key)
                If Err.Number = 0 Then
                    currentNode.Image = "disabled"
                Else
                    Err.Clear
                End If
            End If
        Next
End Sub

Private Sub mnuEventEnable_Click()
      On Error Resume Next

    Dim eInfo As EventRegistrationInfo
    Dim bndg As IEventBinding
    Dim currentNode As Node
  
        For Each eInfo In Registrations
            If (eInfo.Service & ":" & eInfo.VirtualServerNumber & ":" & eInfo.EventNum) = treeRegistrations.SelectedItem.Key Then
                Set bndg = eInfo.Binding
                bndg.Enabled = True
                bndg.Save
                
                Set currentNode = treeRegistrations.Nodes(eInfo.Key)
                If Err.Number = 0 Then
                    currentNode.Image = "enabled"
                Else
                    Err.Clear
                End If
            End If
        Next
End Sub

Private Sub mnuServerDelete_Click()
    Dim eInfo As EventRegistrationInfo
    
    If MsgBox("Are you sure you want to delete all registrations for this virtual server?", vbYesNo, "Delete registrations?") = vbYes Then
        For Each eInfo In Registrations
                If eInfo.Service & ":" & eInfo.VirtualServerNumber = _
                    treeRegistrations.SelectedItem.Key Then
                RemoveRegistration eInfo
            End If
        Next
    
        RefreshBindings
    End If
End Sub

Private Sub mnuServerDisable_Click()
    On Error Resume Next

    Dim eInfo As EventRegistrationInfo
    Dim bndg As IEventBinding
    Dim currentNode As Node
  
        For Each eInfo In Registrations
            If eInfo.Service & ":" & eInfo.VirtualServerNumber = _
                    treeRegistrations.SelectedItem.Key Then
                Set bndg = eInfo.Binding
                bndg.Enabled = False
                bndg.Save
                
                Set currentNode = treeRegistrations.Nodes(eInfo.Key)
                If Err.Number = 0 Then
                    currentNode.Image = "disabled"
                Else
                    Err.Clear
                End If
            End If
        Next
End Sub

Private Sub mnuServerEnable_Click()
On Error Resume Next

    Dim eInfo As EventRegistrationInfo
    Dim bndg As IEventBinding
    Dim currentNode As Node
  
        For Each eInfo In Registrations
            If eInfo.Service & ":" & eInfo.VirtualServerNumber = _
                    treeRegistrations.SelectedItem.Key Then
                Set bndg = eInfo.Binding
                bndg.Enabled = True
                bndg.Save
                
                Set currentNode = treeRegistrations.Nodes(eInfo.Key)
                If Err.Number = 0 Then
                    currentNode.Image = "enabled"
                Else
                    Err.Clear
                End If
            End If
        Next
End Sub

Private Sub mnuServiceDelete_Click()
    Dim eInfo As EventRegistrationInfo
    
    If MsgBox("Are you sure you want to delete all registrations for this service?", vbYesNo, "Delete registrations?") = vbYes Then
        For Each eInfo In Registrations
                If eInfo.Service = treeRegistrations.SelectedItem.Key Then
                RemoveRegistration eInfo
            End If
        Next
    
        RefreshBindings
    End If
End Sub

Private Sub mnuServiceDisable_Click()
    On Error Resume Next

    Dim eInfo As EventRegistrationInfo
    Dim bndg As IEventBinding
    Dim currentNode As Node
  
        For Each eInfo In Registrations
            If eInfo.Service = treeRegistrations.SelectedItem.Key Then
                Set bndg = eInfo.Binding
                bndg.Enabled = False
                bndg.Save
                
                Set currentNode = treeRegistrations.Nodes(eInfo.Key)
                If Err.Number = 0 Then
                    currentNode.Image = "disabled"
                Else
                    Err.Clear
                End If
            End If
        Next
End Sub

Private Sub mnuServiceEnable_Click()
    On Error Resume Next

    Dim eInfo As EventRegistrationInfo
    Dim bndg As IEventBinding
    Dim currentNode As Node
  
        For Each eInfo In Registrations
            If eInfo.Service = treeRegistrations.SelectedItem.Key Then
                Set bndg = eInfo.Binding
                bndg.Enabled = True
                bndg.Save
                
                Set currentNode = treeRegistrations.Nodes(eInfo.Key)
                If Err.Number = 0 Then
                    currentNode.Image = "enabled"
                Else
                    Err.Clear
                End If
            End If
        Next
End Sub

Private Sub mnuExit_Click()
    Unload Me
End Sub


Sub RefreshBindings()
    On Error Resume Next

    Dim selNode As Node
    Dim selectedKey As String

    Set selNode = treeRegistrations.SelectedItem
    If Not (selNode Is Nothing) Then
        selectedKey = selNode.Key
    Else
        selectedKey = ""
    End If
    
    LoadSinkInfo
    LoadTree
    
    If selectedKey <> "" Then
        Set selNode = treeRegistrations.Nodes(selectedKey)
        If Err.Number = 35601 Then
            Err.Clear
            LoadDetails ""
        Else
            selNode.Selected = True
            treeRegistrations_NodeClick selNode
        End If
    End If
End Sub


Private Sub mnuModify_Click()
    cmdModify_Click
End Sub

Private Sub mnuRefresh_Click()
   RefreshBindings
End Sub

' When a tab is clicked, hide and show the appropriate frames
Private Sub TabStrip1_Click()
    Dim frme As Frame

    For Each frme In frameOverview
        If TabStrip1.SelectedItem = "Overview" Then
            frme.Visible = True
        Else
            frme.Visible = False
        End If
    Next
    For Each frme In frameDetails
        If TabStrip1.SelectedItem = "Details" Then
            frme.Visible = True
        Else
            frme.Visible = False
        End If
    Next
    For Each frme In frameModify
        If TabStrip1.SelectedItem = "Modify" Then
            frme.Visible = True
        Else
            frme.Visible = False
        End If
    Next
    
    treeRegistrations.SetFocus
End Sub

' If the user right clicks on the tree control, a popup menu should show up
' if they are clicking on a node
Private Sub treeRegistrations_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
    ShowPopupMenu = (Button = 2)
End Sub



Private Sub treeRegistrations_NodeClick(ByVal Node As MSComctlLib.Node)
    Dim ColonCount As Integer
    Dim GUIDPosition As Integer
    Dim I As Integer
    Dim eInfo As EventRegistrationInfo

    
    If Len(Node.Key) >= 20 Then
        ColonCount = 0
        GUIDPosition = 0
        For I = 1 To Len(Node.Key)
            If Mid(Node.Key, I, 1) = ":" Then
                ColonCount = ColonCount + 1
                If ColonCount = 3 Then
                    GUIDPosition = I + 1
                    Exit For
                End If
            End If
        Next
    
        If GUIDPosition > 0 Then
            LoadDetails Mid(Node.Key, GUIDPosition)
        Else
            LoadDetails ""
        End If
    Else
        LoadDetails ""
        ColonCount = 0
        For I = 1 To Len(Node.Key)
            If Mid(Node.Key, I, 1) = ":" Then
                ColonCount = ColonCount + 1
            End If
        Next
    End If
    
    
    ' If the user has right-clicked to select this node, show a popup menu
    ' depending on the type of node that they clicked on.
    If ShowPopupMenu Then
        Select Case ColonCount
            ' The user has selected either NNTP or SMTP in the tree
            Case 0: mnuServiceDisable.Enabled = False
                    mnuServiceEnable.Enabled = False
                    For Each eInfo In Registrations
                        If eInfo.Service = Node.Key Then
                            If eInfo.Binding.Enabled Then
                                mnuServiceDisable.Enabled = True
                                If mnuServiceEnable.Enabled Then Exit For
                            Else
                                mnuServiceEnable.Enabled = True
                                If mnuServiceDisable.Enabled Then Exit For
                            End If
                        End If
                    Next
                    
                    Me.PopupMenu mnuService
        
            ' The user has selected a virtual server
            Case 1: mnuServerDisable.Enabled = False
                    mnuServerEnable.Enabled = False
                    For Each eInfo In Registrations
                        If eInfo.Service & ":" & eInfo.VirtualServerNumber = _
                            Node.Key Then
                            If eInfo.Binding.Enabled Then
                                mnuServerDisable.Enabled = True
                                If mnuServerEnable.Enabled Then Exit For
                            Else
                                mnuServerEnable.Enabled = True
                                If mnuServerDisable.Enabled Then Exit For
                            End If
                        End If
                    Next
                    
                    Me.PopupMenu mnuServer
        
            ' The user has selected the name of an event (such as OnArrival)
            Case 2: mnuEventDisable.Enabled = False
                    mnuEventEnable.Enabled = False
                    For Each eInfo In Registrations
                        If (eInfo.Service & ":" & eInfo.VirtualServerNumber & ":" & eInfo.EventNum) = Node.Key Then
                            If eInfo.Binding.Enabled Then
                                mnuEventDisable.Enabled = True
                                If mnuEventEnable.Enabled Then Exit For
                            Else
                                mnuEventEnable.Enabled = True
                                If mnuEventDisable.Enabled Then Exit For
                            End If
                        End If
                    Next
                    
                    Me.PopupMenu mnuSelectedEvent
                    
            ' An actual registration is selected
            Case 3: mnuDisable.Enabled = currentReg.Binding.Enabled
                    mnuEnable.Enabled = Not mnuDisable.Enabled
                    Me.PopupMenu mnuEventSink
       End Select
    End If
    ShowPopupMenu = False
End Sub

