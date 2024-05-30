VERSION 5.00
Begin VB.Form frmWizard 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Asset Information Wizard"
   ClientHeight    =   5385
   ClientLeft      =   420
   ClientTop       =   705
   ClientWidth     =   8445
   ControlBox      =   0   'False
   Icon            =   "frmWizard.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5385
   ScaleWidth      =   8445
   StartUpPosition =   2  'CenterScreen
   Begin VB.Frame fraWizardPages 
      BorderStyle     =   0  'None
      Height          =   4335
      Index           =   0
      Left            =   2640
      TabIndex        =   0
      Top             =   180
      Width           =   5655
      Begin VB.Line Lines 
         BorderColor     =   &H80000014&
         Index           =   3
         X1              =   0
         X2              =   5640
         Y1              =   495
         Y2              =   495
      End
      Begin VB.Line Lines 
         BorderColor     =   &H80000010&
         Index           =   2
         X1              =   0
         X2              =   5640
         Y1              =   480
         Y2              =   480
      End
      Begin VB.Label lblWelcome 
         Caption         =   "Click Cancel at any time to quit."
         Height          =   315
         Index           =   2
         Left            =   0
         TabIndex        =   3
         Top             =   2820
         Width           =   5595
      End
      Begin VB.Label lblWelcome 
         Caption         =   "To continue, click Next."
         Height          =   315
         Index           =   3
         Left            =   0
         TabIndex        =   4
         Top             =   3240
         Width           =   5475
      End
      Begin VB.Label lblWelcome 
         Caption         =   $"frmWizard.frx":0442
         Height          =   1455
         Index           =   1
         Left            =   0
         TabIndex        =   2
         Top             =   780
         Width           =   5475
      End
      Begin VB.Label lblWelcome 
         BackStyle       =   0  'Transparent
         Caption         =   "Welcome!"
         BeginProperty Font 
            Name            =   "Times New Roman"
            Size            =   20.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   -1  'True
            Strikethrough   =   0   'False
         EndProperty
         Height          =   525
         Index           =   0
         Left            =   0
         TabIndex        =   1
         Top             =   0
         Width           =   5505
      End
      Begin VB.Label lblWelcome 
         BackStyle       =   0  'Transparent
         Caption         =   "Welcome!"
         BeginProperty Font 
            Name            =   "Times New Roman"
            Size            =   20.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   -1  'True
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H80000010&
         Height          =   525
         Index           =   4
         Left            =   30
         TabIndex        =   49
         Top             =   30
         Width           =   5505
      End
   End
   Begin VB.Frame fraWizardPages 
      BorderStyle     =   0  'None
      Height          =   4335
      Index           =   4
      Left            =   2640
      TabIndex        =   40
      Top             =   180
      Width           =   5655
      Begin VB.TextBox txtFinishSummary 
         BackColor       =   &H8000000F&
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   2655
         Left            =   0
         Locked          =   -1  'True
         MultiLine       =   -1  'True
         ScrollBars      =   2  'Vertical
         TabIndex        =   43
         Top             =   1320
         Width           =   5475
      End
      Begin VB.Label lblFinish 
         Caption         =   "To transmit this information to the central database, please click Finish."
         Height          =   315
         Index           =   2
         Left            =   0
         TabIndex        =   44
         Top             =   4140
         Width           =   5595
      End
      Begin VB.Label lblFinish 
         Caption         =   $"frmWizard.frx":05DB
         Height          =   495
         Index           =   1
         Left            =   0
         TabIndex        =   42
         Top             =   780
         Width           =   5595
      End
      Begin VB.Line Lines 
         BorderColor     =   &H80000010&
         Index           =   11
         X1              =   0
         X2              =   5640
         Y1              =   480
         Y2              =   480
      End
      Begin VB.Line Lines 
         BorderColor     =   &H80000014&
         Index           =   10
         X1              =   0
         X2              =   5640
         Y1              =   495
         Y2              =   495
      End
      Begin VB.Label lblFinish 
         Caption         =   "Thank You!"
         BeginProperty Font 
            Name            =   "Times New Roman"
            Size            =   20.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   -1  'True
            Strikethrough   =   0   'False
         EndProperty
         Height          =   555
         Index           =   0
         Left            =   0
         TabIndex        =   41
         Top             =   0
         Width           =   5595
      End
   End
   Begin VB.Frame fraWizardPages 
      BorderStyle     =   0  'None
      Height          =   4335
      Index           =   3
      Left            =   2640
      TabIndex        =   27
      Top             =   180
      Width           =   5655
      Begin VB.CheckBox chkSysUnit 
         Caption         =   "This is a laptop computer"
         Height          =   195
         Left            =   300
         TabIndex        =   36
         Top             =   4020
         Width           =   4875
      End
      Begin VB.TextBox txtSysUnit 
         Height          =   285
         Index           =   0
         Left            =   300
         TabIndex        =   31
         Top             =   1980
         Width           =   4875
      End
      Begin VB.TextBox txtSysUnit 
         Height          =   285
         Index           =   1
         Left            =   300
         TabIndex        =   33
         Top             =   2700
         Width           =   4875
      End
      Begin VB.TextBox txtSysUnit 
         Height          =   285
         Index           =   2
         Left            =   300
         TabIndex        =   35
         Top             =   3420
         Width           =   4875
      End
      Begin VB.Line Lines 
         BorderColor     =   &H80000014&
         Index           =   9
         X1              =   0
         X2              =   5640
         Y1              =   495
         Y2              =   495
      End
      Begin VB.Label lblSysUnit 
         Alignment       =   1  'Right Justify
         Caption         =   "required"
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H80000011&
         Height          =   195
         Index           =   7
         Left            =   3120
         TabIndex        =   39
         Top             =   3180
         Width           =   2055
      End
      Begin VB.Label lblSysUnit 
         Alignment       =   1  'Right Justify
         Caption         =   "required"
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H80000011&
         Height          =   195
         Index           =   6
         Left            =   3120
         TabIndex        =   38
         Top             =   2460
         Width           =   2055
      End
      Begin VB.Label lblSysUnit 
         Alignment       =   1  'Right Justify
         Caption         =   "required"
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H80000011&
         Height          =   195
         Index           =   5
         Left            =   3120
         TabIndex        =   37
         Top             =   1740
         Width           =   2055
      End
      Begin VB.Line Lines 
         BorderColor     =   &H80000010&
         Index           =   8
         X1              =   0
         X2              =   5640
         Y1              =   480
         Y2              =   480
      End
      Begin VB.Label lblSysUnit 
         Caption         =   "System Details"
         BeginProperty Font 
            Name            =   "Times New Roman"
            Size            =   20.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   -1  'True
            Strikethrough   =   0   'False
         EndProperty
         Height          =   495
         Index           =   0
         Left            =   0
         TabIndex        =   28
         Top             =   0
         Width           =   5595
      End
      Begin VB.Label lblSysUnit 
         Caption         =   $"frmWizard.frx":0673
         Height          =   975
         Index           =   1
         Left            =   0
         TabIndex        =   29
         Top             =   720
         Width           =   5595
      End
      Begin VB.Label lblSysUnit 
         Caption         =   "Base unit manufacturer:"
         Height          =   195
         Index           =   2
         Left            =   0
         TabIndex        =   30
         Top             =   1740
         Width           =   2775
      End
      Begin VB.Label lblSysUnit 
         Caption         =   "Base unit model:"
         Height          =   195
         Index           =   3
         Left            =   0
         TabIndex        =   32
         Top             =   2460
         Width           =   2775
      End
      Begin VB.Label lblSysUnit 
         Caption         =   "Base unit asset number:"
         Height          =   195
         Index           =   4
         Left            =   0
         TabIndex        =   34
         Top             =   3180
         Width           =   2775
      End
   End
   Begin VB.Frame fraWizardPages 
      BorderStyle     =   0  'None
      Height          =   4335
      Index           =   2
      Left            =   2640
      TabIndex        =   18
      Top             =   180
      Width           =   5655
      Begin VB.TextBox txtSysLocation 
         Height          =   285
         Index           =   2
         Left            =   300
         TabIndex        =   26
         Top             =   3600
         Width           =   4875
      End
      Begin VB.TextBox txtSysLocation 
         Height          =   285
         Index           =   1
         Left            =   300
         TabIndex        =   24
         Top             =   2820
         Width           =   4875
      End
      Begin VB.TextBox txtSysLocation 
         Height          =   285
         Index           =   0
         Left            =   300
         TabIndex        =   22
         Top             =   2040
         Width           =   4875
      End
      Begin VB.Label lblSysLocation 
         Caption         =   "Located in building:"
         Height          =   195
         Index           =   3
         Left            =   0
         TabIndex        =   23
         Top             =   2580
         Width           =   2775
      End
      Begin VB.Label lblSysLocation 
         Caption         =   "Located in room number:"
         Height          =   195
         Index           =   4
         Left            =   0
         TabIndex        =   25
         Top             =   3360
         Width           =   2775
      End
      Begin VB.Label lblSysLocation 
         Caption         =   "Located on site:"
         Height          =   195
         Index           =   2
         Left            =   0
         TabIndex        =   21
         Top             =   1800
         Width           =   2775
      End
      Begin VB.Line Lines 
         BorderColor     =   &H80000010&
         Index           =   7
         X1              =   0
         X2              =   5640
         Y1              =   480
         Y2              =   480
      End
      Begin VB.Line Lines 
         BorderColor     =   &H80000014&
         Index           =   6
         X1              =   0
         X2              =   5640
         Y1              =   495
         Y2              =   495
      End
      Begin VB.Label lblSysLocation 
         Caption         =   $"frmWizard.frx":07A4
         Height          =   615
         Index           =   1
         Left            =   0
         TabIndex        =   20
         Top             =   720
         Width           =   5595
      End
      Begin VB.Label lblSysLocation 
         Caption         =   "System Location"
         BeginProperty Font 
            Name            =   "Times New Roman"
            Size            =   20.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   -1  'True
            Strikethrough   =   0   'False
         EndProperty
         Height          =   495
         Index           =   0
         Left            =   0
         TabIndex        =   19
         Top             =   0
         Width           =   5595
      End
   End
   Begin VB.Frame fraWizardPages 
      BorderStyle     =   0  'None
      Height          =   4335
      Index           =   1
      Left            =   2640
      TabIndex        =   5
      Top             =   180
      Width           =   5655
      Begin VB.TextBox txtContact 
         Height          =   285
         Index           =   3
         Left            =   300
         TabIndex        =   15
         Top             =   4020
         Width           =   4875
      End
      Begin VB.TextBox txtContact 
         Height          =   285
         Index           =   2
         Left            =   300
         TabIndex        =   13
         Top             =   3240
         Width           =   4875
      End
      Begin VB.TextBox txtContact 
         Height          =   285
         Index           =   1
         Left            =   300
         TabIndex        =   11
         Top             =   2460
         Width           =   4875
      End
      Begin VB.TextBox txtContact 
         Height          =   285
         Index           =   0
         Left            =   300
         TabIndex        =   9
         Top             =   1680
         Width           =   4875
      End
      Begin VB.Label lblContact 
         Alignment       =   1  'Right Justify
         Caption         =   "required"
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H80000011&
         Height          =   195
         Index           =   7
         Left            =   3720
         TabIndex        =   16
         Top             =   2220
         Width           =   1455
      End
      Begin VB.Label lblContact 
         Alignment       =   1  'Right Justify
         Caption         =   "required"
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H80000011&
         Height          =   195
         Index           =   6
         Left            =   3720
         TabIndex        =   17
         Top             =   1440
         Width           =   1455
      End
      Begin VB.Label lblContact 
         Caption         =   "Please enter the following contact information about the operator of this computer system."
         Height          =   495
         Index           =   1
         Left            =   0
         TabIndex        =   7
         Top             =   720
         Width           =   5595
      End
      Begin VB.Label lblContact 
         Caption         =   "Location (Site / Building / Office):"
         Height          =   255
         Index           =   5
         Left            =   0
         TabIndex        =   14
         Top             =   3780
         Width           =   5595
      End
      Begin VB.Line Lines 
         BorderColor     =   &H80000014&
         Index           =   5
         X1              =   0
         X2              =   5640
         Y1              =   495
         Y2              =   495
      End
      Begin VB.Line Lines 
         BorderColor     =   &H80000010&
         Index           =   4
         X1              =   0
         X2              =   5640
         Y1              =   480
         Y2              =   480
      End
      Begin VB.Label lblContact 
         Caption         =   "Phone Number or Extension:"
         Height          =   255
         Index           =   4
         Left            =   0
         TabIndex        =   12
         Top             =   3000
         Width           =   5595
      End
      Begin VB.Label lblContact 
         Caption         =   "E-Mail Address or Alias:"
         Height          =   255
         Index           =   3
         Left            =   0
         TabIndex        =   10
         Top             =   2220
         Width           =   5595
      End
      Begin VB.Label lblContact 
         Caption         =   "First and Last Name:"
         Height          =   255
         Index           =   2
         Left            =   0
         TabIndex        =   8
         Top             =   1440
         Width           =   5595
      End
      Begin VB.Label lblContact 
         Caption         =   "Contact Information"
         BeginProperty Font 
            Name            =   "Times New Roman"
            Size            =   20.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   -1  'True
            Strikethrough   =   0   'False
         EndProperty
         Height          =   555
         Index           =   0
         Left            =   0
         TabIndex        =   6
         Top             =   0
         Width           =   5595
      End
   End
   Begin VB.PictureBox picWizard 
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      Height          =   4335
      Left            =   180
      Picture         =   "frmWizard.frx":086C
      ScaleHeight     =   4335
      ScaleWidth      =   2115
      TabIndex        =   48
      TabStop         =   0   'False
      Top             =   180
      Width           =   2115
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Left            =   7020
      TabIndex        =   47
      Top             =   4920
      Width           =   1275
   End
   Begin VB.CommandButton cmdNext 
      Caption         =   "&Next >"
      Default         =   -1  'True
      Height          =   375
      Left            =   5460
      TabIndex        =   46
      Top             =   4920
      Width           =   1275
   End
   Begin VB.CommandButton cmdBack 
      Caption         =   "< &Back"
      Enabled         =   0   'False
      Height          =   375
      Left            =   4140
      TabIndex        =   45
      Top             =   4920
      Width           =   1275
   End
   Begin VB.Line Lines 
      BorderColor     =   &H80000014&
      Index           =   1
      X1              =   180
      X2              =   8280
      Y1              =   4755
      Y2              =   4755
   End
   Begin VB.Line Lines 
      BorderColor     =   &H80000010&
      Index           =   0
      X1              =   180
      X2              =   8280
      Y1              =   4740
      Y2              =   4740
   End
End
Attribute VB_Name = "frmWizard"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'**************************************************************
' Copyright (c)1999 Microsoft Corporation, All Rights Reserved
'
' Version 1.0
'**************************************************************

'frmWizard.frm (STARTUP FORM)

Private CurrentWizardPage As Integer
Private FormCaption As String


' **********************************************************
' ** FORM_LOAD *********************************************
' **********************************************************
Private Sub Form_Load()
    
    ' Store the form caption for later use
    FormCaption = Me.Caption
    
    ' Begin with the first wizard page
    CurrentWizardPage = 0
    
    ' Update the form
    UpdateCurrentWizardPage
    
    ' Declare some wbem objects
    Dim WbemLocator As Object
    Dim WbemServices As Object
    Dim WbemObject As Object
    
    ' Force form to display NOW
    Me.Show
    
    ' Go to hourglass cursor while we do some potentially slow dcom stuff
    Me.MousePointer = vbHourglass
    
    ' Enable error trapping
    On Error Resume Next
    
    ' Create a wbem locator
    Set WbemLocator = CreateObject("WbemScripting.SWbemLocator")
    
    If Err Then
    
        cmdNext.Enabled = False
        lblWelcome(3).Visible = False
        lblWelcome(2).Caption = "Click Cancel to quit."
        ErrMsgBox "This computer must be an SMS Client to run this application." & vbCrLf & "You will not be able to proceed."
        
    Else
    
        ' Connect to namespace root\cimv2
        Set WbemServices = WbemLocator.ConnectServer(, "root\cimv2")
        If Err Then
            cmdNext.Enabled = False
            lblWelcome(3).Visible = False
            lblWelcome(2).Caption = "Click Cancel to quit."
            ErrMsgBox "This computer must be an SMS Client to run this application." & vbCrLf & "You will not be able to proceed."
        End If
        
        Set WbemObject = WbemServices.Get("SMS_AssetWizard_1")
        
        ' If this call failed, we need to make the SMS_AssetWizard_1 class
        If Err Then
            
            ' Retrieve blank class
            Set WbemObject = WbemServices.Get
            
            ' Set class name
            WbemObject.Path_.Class = "SMS_AssetWizard_1"
            
            ' Add Properties (8 = CIM_STRING, 11 = CIM_BOOLEAN)
            WbemObject.Properties_.Add "Type", 19
            WbemObject.Properties_.Add "ContactFullName", 8
            WbemObject.Properties_.Add "ContactEmail", 8
            WbemObject.Properties_.Add "ContactPhone", 8
            WbemObject.Properties_.Add "ContactLocation", 8
            WbemObject.Properties_.Add "SysLocationSite", 8
            WbemObject.Properties_.Add "SysLocationBuilding", 8
            WbemObject.Properties_.Add "SysLocationRoom", 8
            WbemObject.Properties_.Add "SysUnitManufacturer", 8
            WbemObject.Properties_.Add "SysUnitModel", 8
            WbemObject.Properties_.Add "SysUnitAssetNumber", 8
            WbemObject.Properties_.Add "SysUnitIsLaptop", 11
            
            ' Add key qualifier to Type property
            WbemObject.Properties_("Type").Qualifiers_.Add "key", True
            
            ' Commit class definition
            WbemObject.Put_
            
            ' Attempt to open the root\cimv2\sms namespace
            Set WbemServices = WbemLocator.ConnectServer(, "root\cimv2\sms")
            
            ' If an error occurred, it probably doesn't exist... so make it
            If Err Then
                
                ' Spawn an instance of __Namespace
                Set WbemObject = WbemServices.Get("__NAMESPACE").SpawnInstance_
                
                'Set the name to SMS
                WbemObject.Name = "sms"
                
                'Commit
                WbemObject.Put_
                
                ' Connect again
                Set WbemServices = WbemLocator.ConnectServer(, "root\cimv2\sms")
                
                ' Make a SMS_Class_Template base class
                Set WbemObject = WbemServices.Get
                WbemObject.Path_.Class = "SMS_Class_Template"
                WbemObject.Put_
                
            End If
            
            ' Retrieve superclass
            Set WbemObject = WbemServices.Get("SMS_Class_Template").SpawnDerivedClass_
            
            ' Set class name and qualifier values
            WbemObject.Path_.Class = "SMS_AssetWizard_1"
            WbemObject.Qualifiers_.Add "SMS_Report", True
            WbemObject.Qualifiers_.Add "SMS_Group_Name", "Asset Wizard Results"
            WbemObject.Qualifiers_.Add "SMS_Group_Name", "Asset Wizard Results"
            WbemObject.Qualifiers_.Add "SMS_Class_ID", "MICROSOFT|ASSETWIZARD|1.0"
            
            ' Add Properties, set SMS_Report qualifiers to True
            WbemObject.Properties_.Add("Type", 19).Qualifiers_.Add "SMS_Report", True
            WbemObject.Properties_("Type").Qualifiers_.Add "key", True
            WbemObject.Properties_.Add("ContactFullName", 8).Qualifiers_.Add "SMS_Report", True
            WbemObject.Properties_.Add("ContactEmail", 8).Qualifiers_.Add "SMS_Report", True
            WbemObject.Properties_.Add("ContactPhone", 8).Qualifiers_.Add "SMS_Report", True
            WbemObject.Properties_.Add("ContactLocation", 8).Qualifiers_.Add "SMS_Report", True
            WbemObject.Properties_.Add("SysLocationSite", 8).Qualifiers_.Add "SMS_Report", True
            WbemObject.Properties_.Add("SysLocationBuilding", 8).Qualifiers_.Add "SMS_Report", True
            WbemObject.Properties_.Add("SysLocationRoom", 8).Qualifiers_.Add "SMS_Report", True
            WbemObject.Properties_.Add("SysUnitManufacturer", 8).Qualifiers_.Add "SMS_Report", True
            WbemObject.Properties_.Add("SysUnitModel", 8).Qualifiers_.Add "SMS_Report", True
            WbemObject.Properties_.Add("SysUnitAssetNumber", 8).Qualifiers_.Add "SMS_Report", True
            WbemObject.Properties_.Add("SysUnitIsLaptop", 11).Qualifiers_.Add "SMS_Report", True
            
            ' Commit class definition
            WbemObject.Put_
            
        Else
        
            'Read Existing values from object
            Set WbemObject = WbemServices.Get("SMS_AssetWizard_1.Type=0")
            txtContact(0).text = WbemObject.ContactFullName
            txtContact(1).text = WbemObject.ContactEmail
            txtContact(2).text = WbemObject.ContactPhone
            txtContact(3).text = WbemObject.ContactLocation
            txtSysLocation(0).text = WbemObject.SysLocationSite
            txtSysLocation(1).text = WbemObject.SysLocationBuilding
            txtSysLocation(2).text = WbemObject.SysLocationRoom
            txtSysUnit(0).text = WbemObject.SysUnitManufacturer
            txtSysUnit(1).text = WbemObject.SysUnitModel
            txtSysUnit(2).text = WbemObject.SysUnitAssetNumber
            chkSysUnit.Value = IIf(WbemObject.SysUnitIsLaptop, 1, 0)
            
        End If
    
    End If
    
    ' Restore mouse cursor
    Me.MousePointer = vbDefault
    
End Sub


' **********************************************************
' ** cmdBack_Click *****************************************
' **********************************************************
Private Sub cmdBack_Click()

    ' Move to the previous wizard page
    CurrentWizardPage = CurrentWizardPage - 1
    
    ' Update the form
    UpdateCurrentWizardPage

End Sub


' **********************************************************
' ** cmdNext_Click *****************************************
' **********************************************************
Private Sub cmdNext_Click()
    
    ' If we're not on the last page...
    If CurrentWizardPage < fraWizardPages.UBound Then
    
        ' Make sure values on this page are valid before
        ' moving on.
        If ValidatePage(CurrentWizardPage) = True Then
                
            ' Move to the next wizard page
            CurrentWizardPage = CurrentWizardPage + 1
            
            ' Update the form
            UpdateCurrentWizardPage
            
        End If
        
    Else
        
        'If we're on the last page, the Next button is the Finish button
        FinishProcedure
        
    End If

End Sub


' **********************************************************
' ** cmdCancel_Click ***************************************
' **********************************************************
Private Sub cmdCancel_Click()
    Unload Me
End Sub


' **********************************************************
' ** UpdateCurrentWizardPage *******************************
' **********************************************************
Private Sub UpdateCurrentWizardPage()

    Dim iWizardPage As Integer
    
    'Hide all but the current wizard page
    For iWizardPage = fraWizardPages.LBound To fraWizardPages.UBound
        If iWizardPage <> CurrentWizardPage Then
            fraWizardPages(iWizardPage).Visible = False
        Else
            fraWizardPages(iWizardPage).Visible = True
        End If
    Next iWizardPage
    
    ' Disable "< Back" if we're on the first page
    If CurrentWizardPage = fraWizardPages.LBound Then
        cmdBack.Enabled = False
    Else
        cmdBack.Enabled = True
    End If
    
    'If the last page is displayed...
    If CurrentWizardPage = fraWizardPages.UBound Then
        
        'Set "Next" button caption to "Finish"
        cmdNext.Caption = "&Finish"
        
        'Generate a text summary, place in textbox.
        txtFinishSummary.text = GenerateSummary
        
        'Scroll the textbox to the top.
        txtFinishSummary.SelStart = 0
        
    Else
        cmdNext.Caption = "&Next >"
    End If
    
    ' Update the form caption to reflect the current page number
    Me.Caption = FormCaption & " - Step " & CStr(CurrentWizardPage - fraWizardPages.LBound + 1) & " of " & CStr(fraWizardPages.UBound - fraWizardPages.LBound + 1)
    
End Sub


' **********************************************************
' ** ValidatePage ******************************************
' **********************************************************
' Validate values on the wizard page specified by PageIndex
' Return true to allow the user to move to the next page
' Return false to keep them on this page until they get it right
Private Function ValidatePage(PageIndex As Integer) As Boolean
    
    ' Default to True
    ValidatePage = True
    
    Select Case PageIndex
        
        ' Contact Information
        Case 1
            If Trim(txtContact(0).text) = "" Then
                ErrMsgBox "A value is required for ""First and Last Name"""
                ValidatePage = False
            ElseIf Trim(txtContact(1).text) = "" Then
                ErrMsgBox "A value is required for ""E-Mail Address or Alias"""
                ValidatePage = False
            End If
        
        ' Base Unit Details
        Case 3
            If Trim(txtSysUnit(0).text) = "" Then
                ErrMsgBox "A value is required for ""Base Unit Manufacturer"""
                ValidatePage = False
            ElseIf Trim(txtSysUnit(1).text) = "" Then
                ErrMsgBox "A value is required for ""Base Unit Model"""
                ValidatePage = False
            ElseIf Trim(txtSysUnit(2).text) = "" Then
                ErrMsgBox "A value is required for ""Base Unit Asset Number"""
                ValidatePage = False
            End If
    End Select
End Function


' **********************************************************
' ** GenerateSummary ***************************************
' **********************************************************
Private Function GenerateSummary() As String
    GenerateSummary = _
    "Contact Information" & vbCrLf & _
    "   First/Last Name: " & txtContact(0).text & vbCrLf & _
    "   E-Mail Address: " & txtContact(1).text & vbCrLf & _
    "   Phone Number: " & txtContact(2).text & vbCrLf & _
    "   Location: " & txtContact(3).text & vbCrLf & _
    vbCrLf & _
    "Computer System Location" & vbCrLf & _
    "   Site: " & txtSysLocation(0).text & vbCrLf & _
    "   Building: " & txtSysLocation(1).text & vbCrLf & _
    "   Room: " & txtSysLocation(2).text & vbCrLf & _
    vbCrLf & _
    "Computer System Base Unit" & vbCrLf & _
    "   Manufacturer: " & txtSysUnit(0).text & vbCrLf & _
    "   Model: " & txtSysUnit(1).text & vbCrLf & _
    "   Asset Number: " & txtSysUnit(2).text & vbCrLf & _
    "   Laptop: " & IIf(chkSysUnit.Value, "Yes", "No")
End Function


' **********************************************************
' ** FinishProcedure ***************************************
' **********************************************************
' FinishProcedure is called when the Finish button is pressed
Private Sub FinishProcedure()
    
    Dim WbemLocator As Object
    Dim WbemServices As Object
    Dim WbemObject As Object
    
    ' Connect to root\cimv2 namespace
    Set WbemLocator = CreateObject("WbemScripting.SWbemLocator")
    Set WbemServices = WbemLocator.ConnectServer(, "root\cimv2")
    
    ' Spawn an instance of SMS_AssetWizard_1
    Set WbemObject = WbemServices.Get("SMS_AssetWizard_1").SpawnInstance_
    
    ' Store property values
    WbemObject.Type = 0
    WbemObject.ContactFullName = txtContact(0).text
    WbemObject.ContactEmail = txtContact(1).text
    WbemObject.ContactPhone = txtContact(2).text
    WbemObject.ContactLocation = txtContact(3).text
    WbemObject.SysLocationSite = txtSysLocation(0).text
    WbemObject.SysLocationBuilding = txtSysLocation(1).text
    WbemObject.SysLocationRoom = txtSysLocation(2).text
    WbemObject.SysUnitManufacturer = txtSysUnit(0).text
    WbemObject.SysUnitModel = txtSysUnit(1).text
    WbemObject.SysUnitAssetNumber = txtSysUnit(2).text
    WbemObject.SysUnitIsLaptop = IIf(chkSysUnit.Value <> 0, True, False)
    
    'WMI will overwrite the existing instance
    WbemObject.Put_
    
    MsgBox "Your asset information has been successfully updated.", vbInformation, "Asset Information Wizard"
    
    Unload Me
    
End Sub


' **********************************************************
' ** ErrMsgBox *********************************************
' **********************************************************
Private Sub ErrMsgBox(text As String)
    MsgBox text, vbExclamation, "Asset Information Wizard"
End Sub
