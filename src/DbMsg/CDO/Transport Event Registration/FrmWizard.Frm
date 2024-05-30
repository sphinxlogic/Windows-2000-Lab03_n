VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "mscomctl.ocx"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "comdlg32.ocx"
Begin VB.Form frmWizard 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Transport Event Registration Wizard"
   ClientHeight    =   4155
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   7080
   Icon            =   "frmWizard.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4155
   ScaleWidth      =   7080
   StartUpPosition =   1  'CenterOwner
   Begin VB.PictureBox pictProgress 
      BackColor       =   &H00C0FFFF&
      BorderStyle     =   0  'None
      FillColor       =   &H80000008&
      Height          =   2775
      Index           =   18
      Left            =   0
      ScaleHeight     =   2775
      ScaleWidth      =   1815
      TabIndex        =   84
      TabStop         =   0   'False
      Top             =   780
      Width           =   1815
      Begin VB.Label lblSteps 
         BackColor       =   &H00C0FFFF&
         Caption         =   "Review && Finish"
         Height          =   255
         Index           =   8
         Left            =   10
         TabIndex        =   93
         Top             =   2160
         Width           =   1815
      End
      Begin VB.Label lblSteps 
         BackColor       =   &H00C0FFFF&
         Caption         =   "Set a priority"
         Height          =   255
         Index           =   7
         Left            =   10
         TabIndex        =   92
         Top             =   1920
         Width           =   1815
      End
      Begin VB.Label lblSteps 
         BackColor       =   &H00C0FFFF&
         Caption         =   "Create a rule"
         Height          =   255
         Index           =   6
         Left            =   10
         TabIndex        =   91
         Top             =   1680
         Width           =   1815
      End
      Begin VB.Label lblSteps 
         BackColor       =   &H00C0FFFF&
         Caption         =   "Select the class"
         Height          =   255
         Index           =   5
         Left            =   10
         TabIndex        =   90
         Top             =   1440
         Width           =   1815
      End
      Begin VB.Label lblSteps 
         BackColor       =   &H00C0FFFF&
         Caption         =   "Select the script"
         Height          =   255
         Index           =   4
         Left            =   10
         TabIndex        =   89
         Top             =   1200
         Width           =   1815
      End
      Begin VB.Label lblSteps 
         BackColor       =   &H00C0FFFF&
         Caption         =   "Set the sink type"
         Height          =   255
         Index           =   3
         Left            =   10
         TabIndex        =   88
         Top             =   960
         Width           =   1815
      End
      Begin VB.Label lblSteps 
         BackColor       =   &H00C0FFFF&
         Caption         =   "Pick the event"
         Height          =   255
         Index           =   2
         Left            =   10
         TabIndex        =   87
         Top             =   720
         Width           =   1815
      End
      Begin VB.Label lblSteps 
         BackColor       =   &H00C0FFFF&
         Caption         =   "Choose a name"
         Height          =   255
         Index           =   1
         Left            =   10
         TabIndex        =   86
         Top             =   480
         Width           =   1815
      End
      Begin VB.Label lblSteps 
         BackColor       =   &H00C0FFFF&
         Caption         =   "Introduction"
         Height          =   255
         Index           =   0
         Left            =   10
         TabIndex        =   85
         Top             =   240
         Width           =   1815
      End
   End
   Begin VB.PictureBox pict 
      BorderStyle     =   0  'None
      Height          =   2655
      Index           =   13
      Left            =   10000
      ScaleHeight     =   2655
      ScaleWidth      =   6135
      TabIndex        =   56
      TabStop         =   0   'False
      Top             =   840
      Width           =   6135
      Begin VB.TextBox txtRule 
         Height          =   285
         Left            =   1440
         TabIndex        =   61
         ToolTipText     =   "Put a rule in this box to indicate when your event sink is fired.  For example, ""Mail From=bob@samples.microsoft.com"""
         Top             =   960
         Width           =   4335
      End
      Begin VB.Label Label19 
         Caption         =   "Put your rule in the following box, or leave blank to not have any rule."
         Height          =   375
         Left            =   1440
         TabIndex        =   60
         Top             =   480
         Width           =   4455
      End
   End
   Begin VB.PictureBox pict 
      BorderStyle     =   0  'None
      Height          =   2655
      Index           =   11
      Left            =   10000
      ScaleHeight     =   2655
      ScaleWidth      =   6135
      TabIndex        =   45
      TabStop         =   0   'False
      Top             =   840
      Width           =   6135
      Begin VB.ComboBox cboProgIDs 
         Height          =   315
         ItemData        =   "frmWizard.frx":0442
         Left            =   3240
         List            =   "frmWizard.frx":0444
         TabIndex        =   70
         ToolTipText     =   "Put the name of the class to use here."
         Top             =   2040
         Width           =   2175
      End
      Begin VB.CommandButton cmdBrowse2 
         Caption         =   "B&rowse"
         Height          =   375
         Left            =   4200
         TabIndex        =   54
         Top             =   1080
         Width           =   1215
      End
      Begin VB.TextBox txtDLLLocation 
         Height          =   285
         Left            =   1320
         TabIndex        =   53
         Top             =   720
         Width           =   4095
      End
      Begin VB.Label Label18 
         Caption         =   "Choose from the drop down list the class that you wish to use as your event sink or type in a class name on your own."
         Height          =   495
         Left            =   1320
         TabIndex        =   55
         Top             =   1560
         Width           =   4575
      End
      Begin VB.Label Label17 
         Caption         =   $"frmWizard.frx":0446
         Height          =   615
         Left            =   1320
         TabIndex        =   52
         Top             =   0
         Width           =   4695
      End
   End
   Begin VB.PictureBox pict 
      BorderStyle     =   0  'None
      Height          =   2655
      Index           =   9
      Left            =   10000
      ScaleHeight     =   2655
      ScaleWidth      =   6135
      TabIndex        =   41
      TabStop         =   0   'False
      Top             =   840
      Width           =   6135
      Begin VB.CommandButton cmdBrowse 
         Caption         =   "B&rowse"
         Height          =   375
         Left            =   4440
         TabIndex        =   44
         Top             =   1440
         Width           =   1215
      End
      Begin VB.TextBox txtScriptPath 
         Height          =   285
         Left            =   1440
         TabIndex        =   43
         Top             =   1080
         Width           =   4215
      End
      Begin VB.Label Label9 
         Caption         =   "What is the path to the script to run?"
         Height          =   255
         Left            =   1440
         TabIndex        =   42
         Top             =   720
         Width           =   3735
      End
   End
   Begin VB.PictureBox pict 
      BorderStyle     =   0  'None
      Height          =   2655
      Index           =   7
      Left            =   10000
      ScaleHeight     =   2655
      ScaleWidth      =   6135
      TabIndex        =   33
      TabStop         =   0   'False
      Top             =   840
      Width           =   6135
      Begin VB.PictureBox Picture5 
         Appearance      =   0  'Flat
         BackColor       =   &H8000000A&
         BorderStyle     =   0  'None
         ForeColor       =   &H80000008&
         Height          =   375
         Left            =   2160
         ScaleHeight     =   375
         ScaleWidth      =   2895
         TabIndex        =   34
         TabStop         =   0   'False
         Top             =   1080
         Width           =   2895
         Begin VB.OptionButton optSinkType 
            Caption         =   "DLL"
            Height          =   255
            Index           =   1
            Left            =   1560
            TabIndex        =   36
            ToolTipText     =   "Choose this if your event handler is a compiled DLL."
            Top             =   120
            Width           =   1215
         End
         Begin VB.OptionButton optSinkType 
            Caption         =   "Script"
            Height          =   255
            Index           =   0
            Left            =   0
            TabIndex        =   35
            ToolTipText     =   "Click this if your event handler is written in a script file."
            Top             =   120
            Width           =   1215
         End
      End
      Begin VB.Label Label10 
         Caption         =   "Is your custom event handler in a script (VBScript or JScript), or is it in a compiled DLL?"
         Height          =   495
         Left            =   1800
         TabIndex        =   37
         Top             =   480
         Width           =   3735
      End
   End
   Begin VB.PictureBox pict 
      BorderStyle     =   0  'None
      Height          =   2655
      Index           =   5
      Left            =   10000
      ScaleHeight     =   2655
      ScaleWidth      =   6135
      TabIndex        =   20
      TabStop         =   0   'False
      Top             =   840
      Width           =   6135
      Begin VB.PictureBox Picture3 
         Appearance      =   0  'Flat
         BackColor       =   &H8000000A&
         BorderStyle     =   0  'None
         ForeColor       =   &H80000008&
         Height          =   375
         Left            =   1800
         ScaleHeight     =   375
         ScaleWidth      =   3015
         TabIndex        =   32
         TabStop         =   0   'False
         Top             =   480
         Width           =   3015
         Begin VB.OptionButton optEventType 
            Caption         =   "NNTP (News)"
            Height          =   255
            Index           =   1
            Left            =   1560
            TabIndex        =   25
            ToolTipText     =   "Click on this to register for an NNTP (News) event."
            Top             =   0
            Width           =   1695
         End
         Begin VB.OptionButton optEventType 
            Caption         =   "SMTP (Mail)"
            Height          =   255
            Index           =   0
            Left            =   0
            TabIndex        =   24
            ToolTipText     =   "Click on this to register for an SMTP (Mail) event."
            Top             =   0
            Width           =   1335
         End
      End
      Begin VB.PictureBox Picture2 
         Appearance      =   0  'Flat
         BackColor       =   &H8000000A&
         BorderStyle     =   0  'None
         ForeColor       =   &H80000008&
         Height          =   615
         Left            =   1800
         ScaleHeight     =   615
         ScaleWidth      =   2895
         TabIndex        =   31
         TabStop         =   0   'False
         Top             =   1320
         Width           =   2895
         Begin VB.OptionButton optEventNum 
            Caption         =   "OnArrival"
            Enabled         =   0   'False
            Height          =   255
            Index           =   0
            Left            =   0
            TabIndex        =   26
            ToolTipText     =   "The OnArrival event is fired when an SMTP server receives a message."
            Top             =   0
            Width           =   1215
         End
         Begin VB.OptionButton optEventNum 
            Caption         =   "OnPost"
            Enabled         =   0   'False
            Height          =   255
            Index           =   2
            Left            =   0
            TabIndex        =   28
            ToolTipText     =   "The OnPost event is fired after an NNTP server receives the entire NNTP posting."
            Top             =   360
            Width           =   1215
         End
         Begin VB.OptionButton optEventNum 
            Caption         =   "OnPostEarly"
            Enabled         =   0   'False
            Height          =   255
            Index           =   1
            Left            =   1560
            TabIndex        =   27
            ToolTipText     =   "The OnPostEarly event is fired when an NNTP server receives the headers of an NNTP posting."
            Top             =   0
            Width           =   1215
         End
         Begin VB.OptionButton optEventNum 
            Caption         =   "OnPostFinal"
            Enabled         =   0   'False
            Height          =   255
            Index           =   3
            Left            =   1560
            TabIndex        =   29
            ToolTipText     =   "The OnPostFinal event is fired when an NNTP server commits a posting to storage."
            Top             =   360
            Width           =   1215
         End
      End
      Begin VB.TextBox txtVirtualServerNum 
         Height          =   285
         Left            =   3360
         TabIndex        =   30
         Text            =   "1"
         ToolTipText     =   $"frmWizard.frx":0508
         Top             =   2280
         Width           =   615
      End
      Begin VB.Label lblQ3 
         Caption         =   "Which virtual server does this event apply to?"
         Height          =   255
         Left            =   1440
         TabIndex        =   23
         Top             =   2040
         Width           =   3495
      End
      Begin VB.Label lblQ2 
         Caption         =   "What is the transport event that will fire this event sink?"
         Height          =   255
         Left            =   1440
         TabIndex        =   22
         Top             =   960
         Width           =   4095
      End
      Begin VB.Label lblQ1 
         Caption         =   "Is this registration for an NNTP or SMTP event?"
         Height          =   255
         Left            =   1440
         TabIndex        =   21
         Top             =   120
         Width           =   3375
      End
   End
   Begin VB.PictureBox pict 
      BorderStyle     =   0  'None
      Height          =   2655
      Index           =   3
      Left            =   10000
      ScaleHeight     =   2655
      ScaleWidth      =   6135
      TabIndex        =   8
      TabStop         =   0   'False
      Top             =   840
      Width           =   6135
      Begin VB.TextBox txtName 
         Height          =   285
         Left            =   1920
         TabIndex        =   9
         Top             =   1080
         Width           =   2655
      End
      Begin VB.Label Label4 
         Caption         =   "Enter a name for this event sink registration."
         Height          =   255
         Left            =   1560
         TabIndex        =   10
         Top             =   720
         Width           =   3255
      End
   End
   Begin VB.PictureBox pict 
      BorderStyle     =   0  'None
      Height          =   2655
      Index           =   1
      Left            =   10000
      ScaleHeight     =   2655
      ScaleWidth      =   6135
      TabIndex        =   6
      TabStop         =   0   'False
      Top             =   840
      Width           =   6135
      Begin VB.Label Label3 
         Caption         =   "Transport Event Registration Wizard"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   24
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   1815
         Left            =   1920
         TabIndex        =   7
         Top             =   360
         Width           =   3975
      End
   End
   Begin VB.PictureBox Picture1 
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   0  'None
      Height          =   375
      Left            =   6480
      Picture         =   "frmWizard.frx":05A3
      ScaleHeight     =   375
      ScaleWidth      =   495
      TabIndex        =   5
      TabStop         =   0   'False
      Top             =   120
      Width           =   495
   End
   Begin VB.Frame Frame1 
      Caption         =   "Frame1"
      Height          =   855
      Left            =   -720
      TabIndex        =   4
      Top             =   3480
      Width           =   8055
      Begin VB.CommandButton cmdFinish 
         Caption         =   "&Finish"
         Enabled         =   0   'False
         Height          =   375
         Left            =   4200
         TabIndex        =   2
         ToolTipText     =   "Quit the wizard and save this event registration."
         Top             =   240
         Width           =   1095
      End
      Begin VB.CommandButton cmdCancel 
         Caption         =   "&Cancel"
         Height          =   375
         Left            =   5400
         TabIndex        =   3
         ToolTipText     =   "Exit the wizard without saving changes."
         Top             =   240
         Width           =   1095
      End
      Begin VB.CommandButton cmdNext 
         Caption         =   "&Next >"
         Default         =   -1  'True
         Height          =   375
         Left            =   3000
         TabIndex        =   1
         ToolTipText     =   "Move forward to the next page."
         Top             =   240
         Width           =   1095
      End
      Begin VB.CommandButton cmdBack 
         Caption         =   "< &Back"
         Enabled         =   0   'False
         Height          =   375
         Left            =   1800
         TabIndex        =   0
         ToolTipText     =   "Move back to the previous page."
         Top             =   240
         Width           =   1095
      End
   End
   Begin VB.PictureBox pict 
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   0  'None
      Height          =   795
      Index           =   0
      Left            =   10000
      ScaleHeight     =   795
      ScaleWidth      =   7080
      TabIndex        =   11
      TabStop         =   0   'False
      Top             =   0
      Width           =   7080
      Begin VB.Label Label1 
         BackColor       =   &H00FFFFFF&
         Caption         =   "Transport Event Registration Wizard"
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
         Left            =   0
         TabIndex        =   13
         Top             =   0
         Width           =   3135
      End
      Begin VB.Label Label2 
         BackColor       =   &H00FFFFFF&
         Caption         =   "Use this wizard to modify your event sink registration information."
         Height          =   255
         Left            =   600
         TabIndex        =   12
         Top             =   360
         Width           =   4695
      End
   End
   Begin VB.PictureBox pict 
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   0  'None
      Height          =   795
      Index           =   2
      Left            =   10000
      ScaleHeight     =   795
      ScaleWidth      =   7080
      TabIndex        =   14
      TabStop         =   0   'False
      Top             =   0
      Width           =   7080
      Begin VB.Label Label6 
         BackColor       =   &H00FFFFFF&
         Caption         =   "This name will help you to identify this registration later."
         Height          =   255
         Left            =   600
         TabIndex        =   16
         Top             =   360
         Width           =   4695
      End
      Begin VB.Label Label5 
         BackColor       =   &H00FFFFFF&
         Caption         =   "Give a name to this event sink registration"
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
         Left            =   0
         TabIndex        =   15
         Top             =   0
         Width           =   4095
      End
   End
   Begin VB.PictureBox pict 
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   0  'None
      Height          =   795
      Index           =   4
      Left            =   10000
      ScaleHeight     =   795
      ScaleWidth      =   7080
      TabIndex        =   17
      TabStop         =   0   'False
      Top             =   0
      Width           =   7080
      Begin VB.Label Label8 
         BackColor       =   &H00FFFFFF&
         Caption         =   "Service, event and virtual server information"
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
         Left            =   0
         TabIndex        =   19
         Top             =   0
         Width           =   4095
      End
      Begin VB.Label Label7 
         BackColor       =   &H00FFFFFF&
         Caption         =   "This will determine the event for this registration."
         Height          =   255
         Left            =   600
         TabIndex        =   18
         Top             =   360
         Width           =   4695
      End
   End
   Begin VB.PictureBox pict 
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   0  'None
      Height          =   795
      Index           =   6
      Left            =   10000
      ScaleHeight     =   795
      ScaleWidth      =   7080
      TabIndex        =   38
      TabStop         =   0   'False
      Top             =   0
      Width           =   7080
      Begin VB.Label Label13 
         BackColor       =   &H00FFFFFF&
         Caption         =   "You can register script-based or DLL-based event sinks."
         Height          =   255
         Left            =   600
         TabIndex        =   40
         Top             =   360
         Width           =   4695
      End
      Begin VB.Label Label12 
         BackColor       =   &H00FFFFFF&
         Caption         =   "Choose the type of event sink you are registering"
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
         Left            =   0
         TabIndex        =   39
         Top             =   0
         Width           =   4575
      End
   End
   Begin VB.PictureBox pict 
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   0  'None
      Height          =   795
      Index           =   8
      Left            =   10000
      ScaleHeight     =   795
      ScaleWidth      =   7080
      TabIndex        =   46
      TabStop         =   0   'False
      Top             =   0
      Width           =   7080
      Begin VB.Label Label11 
         BackColor       =   &H00FFFFFF&
         Caption         =   "Find your script-based event sink."
         Height          =   255
         Left            =   600
         TabIndex        =   48
         Top             =   360
         Width           =   4695
      End
      Begin VB.Label Label14 
         BackColor       =   &H00FFFFFF&
         Caption         =   "Select the script you want to register"
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
         Left            =   0
         TabIndex        =   47
         Top             =   0
         Width           =   4575
      End
   End
   Begin VB.PictureBox pict 
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   0  'None
      Height          =   795
      Index           =   10
      Left            =   10000
      ScaleHeight     =   795
      ScaleWidth      =   7080
      TabIndex        =   49
      TabStop         =   0   'False
      Top             =   0
      Width           =   7080
      Begin VB.Label Label16 
         BackColor       =   &H00FFFFFF&
         Caption         =   "Find the DLL you wish to register."
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
         Left            =   0
         TabIndex        =   51
         Top             =   0
         Width           =   4575
      End
      Begin VB.Label Label15 
         BackColor       =   &H00FFFFFF&
         Caption         =   "Find your DLL-based event sink."
         Height          =   255
         Left            =   600
         TabIndex        =   50
         Top             =   360
         Width           =   4695
      End
   End
   Begin VB.PictureBox pict 
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   0  'None
      Height          =   795
      Index           =   12
      Left            =   10000
      ScaleHeight     =   795
      ScaleWidth      =   7080
      TabIndex        =   57
      TabStop         =   0   'False
      Top             =   0
      Width           =   7080
      Begin VB.Label Label22 
         BackColor       =   &H00FFFFFF&
         Caption         =   "When the event you have registered for is fired you can configure a rule to indicate when your event sink is executed."
         Height          =   375
         Left            =   600
         TabIndex        =   59
         Top             =   360
         Width           =   4575
      End
      Begin VB.Label Label21 
         BackColor       =   &H00FFFFFF&
         Caption         =   "Set up a rule for executing your event sink."
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
         Left            =   0
         TabIndex        =   58
         Top             =   0
         Width           =   4575
      End
   End
   Begin VB.PictureBox pict 
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   0  'None
      Height          =   795
      Index           =   16
      Left            =   10000
      ScaleHeight     =   795
      ScaleWidth      =   7080
      TabIndex        =   63
      TabStop         =   0   'False
      Top             =   0
      Width           =   7080
      Begin VB.Label Label24 
         BackColor       =   &H00FFFFFF&
         Caption         =   "Review the registration information."
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
         Left            =   0
         TabIndex        =   65
         Top             =   0
         Width           =   4575
      End
      Begin VB.Label Label23 
         BackColor       =   &H00FFFFFF&
         Caption         =   "Click on Finish to accept these settings, or go back to make changes."
         Height          =   375
         Left            =   600
         TabIndex        =   64
         Top             =   360
         Width           =   5655
      End
   End
   Begin VB.PictureBox pict 
      BorderStyle     =   0  'None
      Height          =   2655
      Index           =   17
      Left            =   10000
      ScaleHeight     =   2655
      ScaleWidth      =   6135
      TabIndex        =   62
      TabStop         =   0   'False
      Top             =   840
      Width           =   6135
      Begin MSComctlLib.ProgressBar pbar1 
         Height          =   255
         Left            =   1320
         TabIndex        =   66
         Top             =   2160
         Width           =   4575
         _ExtentX        =   8070
         _ExtentY        =   450
         _Version        =   393216
         Appearance      =   1
      End
      Begin VB.Label lblProgress 
         Alignment       =   2  'Center
         Height          =   255
         Left            =   1800
         TabIndex        =   69
         Top             =   2400
         Width           =   3615
      End
      Begin VB.Label Label25 
         Caption         =   $"frmWizard.frx":09E5
         Height          =   735
         Left            =   1320
         TabIndex        =   68
         Top             =   600
         Width           =   4455
      End
      Begin VB.Label Label20 
         Caption         =   "Ready to finish?"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   1320
         TabIndex        =   67
         Top             =   120
         Width           =   2175
      End
   End
   Begin VB.PictureBox pict 
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   0  'None
      Height          =   795
      Index           =   14
      Left            =   10000
      ScaleHeight     =   795
      ScaleWidth      =   7080
      TabIndex        =   71
      TabStop         =   0   'False
      Top             =   0
      Width           =   7080
      Begin VB.Frame Frame2 
         Caption         =   "Frame2"
         Height          =   15
         Left            =   0
         TabIndex        =   83
         Top             =   840
         Width           =   855
      End
      Begin VB.Label Label27 
         BackColor       =   &H00FFFFFF&
         Caption         =   "The priority determines the execution order for event sinks registered for the same event."
         Height          =   375
         Left            =   600
         TabIndex        =   73
         Top             =   360
         Width           =   4575
      End
      Begin VB.Label Label26 
         BackColor       =   &H00FFFFFF&
         Caption         =   "Set a priority for this event sink."
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
         Left            =   0
         TabIndex        =   72
         Top             =   0
         Width           =   4575
      End
   End
   Begin VB.PictureBox pict 
      BorderStyle     =   0  'None
      Height          =   2655
      Index           =   15
      Left            =   960
      ScaleHeight     =   2655
      ScaleWidth      =   6135
      TabIndex        =   74
      TabStop         =   0   'False
      Top             =   840
      Width           =   6135
      Begin MSComDlg.CommonDialog dialogScripts 
         Left            =   5520
         Top             =   1680
         _ExtentX        =   847
         _ExtentY        =   847
         _Version        =   393216
         DialogTitle     =   "Choose your script-based event sink."
         Filter          =   "VB Script Files (*.vbs)|*.vbs|JScript Files (*.js)|*.js|All Files (*.*)|*.*"
      End
      Begin MSComDlg.CommonDialog dialogDLLs 
         Left            =   5520
         Top             =   2160
         _ExtentX        =   847
         _ExtentY        =   847
         _Version        =   393216
         DialogTitle     =   "Find your DLL-based event sink."
         Filter          =   "DLLs (*.dll)|*.dll|All Files (*.*) | *.*"
      End
      Begin VB.OptionButton optPriority 
         Caption         =   "Lowest"
         Height          =   195
         Index           =   4
         Left            =   3720
         TabIndex        =   82
         ToolTipText     =   "Give this registration the lowest priority."
         Top             =   1680
         Width           =   975
      End
      Begin VB.OptionButton optPriority 
         Caption         =   "Low"
         Height          =   195
         Index           =   3
         Left            =   3720
         TabIndex        =   81
         ToolTipText     =   "Give this registration a low priority."
         Top             =   1320
         Width           =   975
      End
      Begin VB.OptionButton optPriority 
         Caption         =   "Medium"
         Height          =   195
         Index           =   2
         Left            =   2520
         TabIndex        =   80
         ToolTipText     =   "Give this registration a medium priority."
         Top             =   2040
         Width           =   975
      End
      Begin VB.OptionButton optPriority 
         Caption         =   "High"
         Height          =   195
         Index           =   1
         Left            =   2520
         TabIndex        =   79
         ToolTipText     =   "Give this registration a high priority."
         Top             =   1680
         Width           =   975
      End
      Begin VB.OptionButton optPriority 
         Caption         =   "Highest"
         Height          =   195
         Index           =   0
         Left            =   2520
         TabIndex        =   78
         ToolTipText     =   "Give this registration the highest priority."
         Top             =   1320
         Width           =   975
      End
      Begin VB.TextBox txtPriority 
         BeginProperty DataFormat 
            Type            =   0
            Format          =   "0"
            HaveTrueFalseNull=   0
            FirstDayOfWeek  =   0
            FirstWeekOfYear =   0
            LCID            =   1033
            SubFormatType   =   0
         EndProperty
         Height          =   285
         Left            =   1440
         TabIndex        =   77
         ToolTipText     =   "The priority indicates the order in which event sinks are fired."
         Top             =   1320
         Width           =   855
      End
      Begin VB.Label Label30 
         Caption         =   "(0-32767)"
         Height          =   255
         Left            =   1560
         TabIndex        =   94
         Top             =   1680
         Width           =   735
      End
      Begin VB.Label Label29 
         Caption         =   $"frmWizard.frx":0A8F
         Height          =   615
         Left            =   1320
         TabIndex        =   76
         Top             =   360
         Width           =   4335
      End
      Begin VB.Label Label28 
         Alignment       =   2  'Center
         Height          =   255
         Left            =   1440
         TabIndex        =   75
         Top             =   2400
         Width           =   3615
      End
   End
End
Attribute VB_Name = "frmWizard"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim CurrentPage As Integer
Dim currentReg As EventRegistrationInfo

Const MaxPage = 8



' This is a list of the steps for the wizard
'
' 0         Intro Screen
' 1         Choose a name for the registration (txtName)
' 2         Choose a service, event and virtual server (optEventnum)
' 3         Choose script or DLL based sink (optSinkType) (Then jump to 4 or 5)
' 4         Find the path to the script to run
' 5         Enter the ProgID of the DLL to run
' 6         Select the rule to fire the event sink
' 7         Choose a priority for the event sink
' 8         Review & finish

' Indicates if the "Finish" button on the wizard should be enabled
Private Function ReadyToFinish() As Boolean
    Dim Ready As Boolean
    Dim I As Integer
    
    Ready = True
    For I = 0 To MaxPage - 1
        Ready = Ready And CanMoveNext(I)
    Next
      
    ReadyToFinish = Ready
End Function

' The main form calls this if it is using the wizard for
' modification purposes instead of to create a new binding
Public Sub ModifyReg(RegInfo As EventRegistrationInfo)
    On Error Resume Next
    
    txtName.Text = RegInfo.Binding.DisplayName
   
    Select Case RegInfo.EventNum
        Case 0: optEventType(0).Value = True
        Case 1: optEventType(1).Value = True
        Case 2: optEventType(1).Value = True
        Case 3: optEventType(1).Value = True
    End Select
    
    optEventNum(RegInfo.EventNum).Value = True
    optSinkType(RegInfo.SinkType).Value = True
    
    Select Case RegInfo.SinkType
        Case ScriptSink: txtScriptPath.Text = RegInfo.Binding.SinkProperties("ScriptName")
        Case DLLSink:
            cboProgIDs.AddItem RegInfo.Binding.SinkClass
            cboProgIDs.Text = RegInfo.Binding.SinkClass
    End Select
    
    txtRule.Text = RegInfo.Binding.SourceProperties("Rule")
    txtPriority.Text = RegInfo.Binding.SourceProperties("Priority")
    txtVirtualServerNum.Text = Trim(Str(RegInfo.VirtualServerNumber))
    Set currentReg = RegInfo
End Sub


Private Sub cboProgIDs_Change()
    cmdNext.Enabled = CanMoveNext(CurrentPage)
    cmdFinish.Enabled = ReadyToFinish()
End Sub


Private Sub cmdBrowse_Click()

    Dim oldCurDir   As String
    
    dialogScripts.Flags = Mscomdlg.cdlOFNFileMustExist Or Mscomdlg.cdlOFNNoDereferenceLinks Or cdlOFNHideReadOnly
    oldCurDir = CurDir
    dialogScripts.ShowOpen
    If dialogScripts.Filename <> "" Then
        txtScriptPath.Text = dialogScripts.Filename
       
    'else
        'user pressed cancel
    
    End If
    
    
    ChDir oldCurDir
 
End Sub

Private Sub cmdBrowse2_Click()
    Dim oldCurDir   As String
    
    dialogDLLs.Flags = Mscomdlg.cdlOFNFileMustExist Or Mscomdlg.cdlOFNNoDereferenceLinks Or cdlOFNHideReadOnly
    oldCurDir = CurDir
    dialogDLLs.ShowOpen
    If dialogDLLs.Filename <> "" Then
        txtDLLLocation.Text = dialogDLLs.Filename
       
    'else
        'user pressed cancel
    
    End If
    
    
    ChDir oldCurDir
End Sub

Private Sub cmdCancel_Click()
    Unload Me
End Sub

' This function indicates if the "next" button should be
' enabled in the wizard, depending on which page the user is on.
Private Function CanMoveNext(PageNo As Integer) As Boolean
    Dim temp As Boolean

    Select Case PageNo
        ' The intro screen.
        Case 0:     CanMoveNext = True
        
        ' The naming screen.  Can move next if there is a name here
        Case 1:     CanMoveNext = (Len(Trim(txtName.Text)) > 0)
                
        ' Can move next if they choose a service, virtual server and event here.
        Case 2:
                    temp = (optEventNum(OnArrival) Or optEventNum(OnPostEarly) Or optEventNum(OnPost) Or optEventNum(OnPostFinal))
                    temp = temp And (Len(Trim(txtVirtualServerNum.Text)) > 0)
                    CanMoveNext = temp
        
        ' Can move next if they choose DLL or script based sink
        Case 3:     CanMoveNext = optSinkType(ScriptSink).Value Or optSinkType(DLLSink).Value
        
        ' Can move next if there is a path to the script based sink
        Case 4:
                    If optSinkType(ScriptSink).Value Then
                        Dim fileobj As New FileSystemObject
                        CanMoveNext = fileobj.FileExists(Trim(txtScriptPath.Text))
                    Else
                        CanMoveNext = True
                    End If
                    
        ' Can move next if they set a Class if this is a DLL based sink
        Case 5:
                    If optSinkType(DLLSink).Value Then
                        CanMoveNext = (Len(cboProgIDs.Text) > 0)
                    Else
                        CanMoveNext = True
                    End If
                    
        ' A rule is not necessary, so they can always skip this screen
        Case 6:     CanMoveNext = True
        
        ' Setting the prio is not required, so they can always skip this screen
        Case 7:             CanMoveNext = True
        Case MaxPage:      CanMoveNext = False
    End Select
End Function

' The function to actually register the event after "Finish" is clicked
Private Function Register(ByVal Evt As EventTypes) As Boolean
    On Error Resume Next

    Dim EventManager As New CEventManager
    Dim SourceType As IEventSourceType
    Dim Source As IEventSource
    Dim srcDisplayName As String
    Dim Binding As IEventBinding
    Dim GUIDComCat As String
    Dim SSClass As String
    Dim tlb As New TLIApplication
    Dim tlbinfo As TypeLibInfo
    Dim SourceFound As Boolean
    Dim SourceSame As Boolean
    Dim I As Long
    
    ' Set up the information needed to create this event binding
    ' based on the event.
    GUIDComCat = GetEvtGUID(Evt)
    SSClass = GetEvtSSClass(Evt)
    srcDisplayName = GetEvtService(Evt) & " " & txtVirtualServerNum.Text
    Set SourceType = EventManager.SourceTypes(GetEvtSourceTypeGUID(Evt))
        
    ' Set the label that tells what is going on and the
    ' progress bar.
    ' The progress bar isn't necessarily real accurate, but registration happens
    ' so fast anyway, it seems okay...
    lblProgress.Caption = "Finding the source: " & srcDisplayName & "..."
    pbar1.Value = 10
    
    SourceFound = False
    For Each Source In SourceType.Sources
        If Source.DisplayName = srcDisplayName Then
            
            lblProgress.Caption = "Found the source: " & srcDisplayName & "..."
            pbar1.Value = 30
            
            SourceFound = True
            
            ' If this is a MODIFY operation (as opposed to creating a new registration)
            ' AND the source (event/service/server) has not changed, then
            ' mark SourceSame as true so we can do a true modification of the original
            ' binding instead of a copy+delete.
            SourceSame = False
            If Not (currentReg Is Nothing) Then
                If (currentReg.Service = GetEvtService(Evt)) And _
                    (currentReg.VirtualServerNumber = Val(txtVirtualServerNum.Text)) And _
                    (currentReg.EventNum = Evt) Then
                    SourceSame = True
                End If
            End If
            
            If Not SourceSame Then
                'now add a new binding with the right event GUID.
                ' by not specifying a GUID to the add method, SEO will create the new ID for this event.
                Set Binding = Source.GetBindingManager.Bindings(GUIDComCat).Add("")
            Else
                ' If the source is the same as before, then do not create a new binding.
                ' Instead, simply use the old one.
                Set Binding = currentReg.Binding
            End If
            
            
            ' Copy the properties of the old registration into this new one
            ' if we are doing a modify so we don't throw away other properties
            ' that we don't know about
            '
            ' We have to do this because a modify = copy + delete if
            ' the event source changes.
            If (Not (currentReg Is Nothing)) And (Not SourceSame) Then
                lblProgress.Caption = "Copying old source, binding and sink properties..."
                pbar1.Value = 40
                For I = 0 To currentReg.Binding.EventBindingProperties.Count
                    Binding.EventBindingProperties.Add currentReg.Binding.EventBindingProperties.Name(I), currentReg.Binding.EventBindingProperties.Item(I)
                Next
            End If
                        
            lblProgress.Caption = "Setting properties on the event binding ..."
            pbar1.Value = 50
            
            Binding.DisplayName = txtName.Text
            
            If Len(txtRule.Text) > 0 Then
                Binding.SourceProperties.Add "Rule", txtRule.Text
            Else
                Binding.SourceProperties.Remove "Rule"
            End If
            
            If Len(txtPriority.Text) > 0 Then
                Binding.SourceProperties.Add "Priority", Val(txtPriority.Text)
            Else
                Binding.SourceProperties.Remove "Priority"
            End If
            
            If optSinkType(ScriptSink).Value Then
                Binding.SinkClass = SSClass
                Binding.SinkProperties.Add "ScriptName", txtScriptPath.Text
            Else
                Binding.SinkProperties.Remove "ScriptName"
                
                Binding.SinkClass = cboProgIDs.Text
                
                If Len(txtDLLLocation.Text) > 0 Then
                    lblProgress.Caption = "Registering your DLL..."
                    pbar1.Value = 75
                    Set tlbinfo = tlb.TypeLibInfoFromFile(txtDLLLocation.Text)
                    tlbinfo.Register
                    If Err.Number <> 0 Then
                        MsgBox "Unable to register your COM DLL." & vbCrLf & "Error #:" & Hex(Err.Number) & vbCrLf & "Error: " & Err.Description, vbCritical, "Unexpected error"
                        Err.Clear
                    End If
                End If
            End If
            
            lblProgress.Caption = "Saving the binding..."
            pbar1.Value = 90
            Binding.Save
            If Err.Number = 0 Then
                lblProgress.Caption = "Event binding saved."
                pbar1.Value = 100
                Register = True
                If (Not (currentReg Is Nothing)) And (Not SourceSame) Then
                    RemoveRegistration currentReg
                    lblProgress.Caption = "Removing old registration information..."
                End If
            Else
                MsgBox "The registration failed." & vbCrLf & "Error #:" & Hex(Err.Number) & vbCrLf & "Error: " & Err.Description, vbCritical, "Unexpected error"
                pbar1.Value = 0
                lblProgress.Caption = ""
                Register = False
                Err.Clear
            End If
            Exit For
        End If
    Next
    
    If Not SourceFound Then
        MsgBox "Unable to find the event source you are trying to register for (" & srcDisplayName & ").  It is possible that this service is not installed, or the virtual server number you provided is not valid.", vbCritical, "Error"
        pbar1.Value = 0
        lblProgress.Caption = ""
        Register = False
    End If
End Function

Private Sub cmdFinish_Click()
    Dim I As Integer
    Dim p As PictureBox
    Dim success As Boolean
    
    CurrentPage = MaxPage
    
    SwitchPage
    
    ' Register the event binding
    pbar1.Value = 0
    lblProgress.Caption = "Starting the event registration process..."
    For I = 0 To 3
        If optEventNum(I) Then
            success = Register(I)
            Exit For
        End If
    Next
        
    If success Then
        Unload Me
    End If
End Sub

' Called to switch to the current page
Private Sub SwitchPage()
    Dim p As PictureBox
    Dim l As Label

    For Each p In pict
        p.Visible = False
    Next
    
    pict(CurrentPage * 2).Left = 0
    pict((CurrentPage * 2) + 1).Left = 960
    pict(CurrentPage * 2).Visible = True
    pict((CurrentPage * 2) + 1).Visible = True
    
    cmdBack.Enabled = (CurrentPage > 0)
    cmdNext.Enabled = (CurrentPage < MaxPage) And CanMoveNext(CurrentPage)
    cmdFinish.Enabled = ReadyToFinish()
    
    For Each l In lblSteps
        l.Font.Bold = False
    Next
    lblSteps(CurrentPage).Font.Bold = True
    
End Sub

Private Sub cmdBack_Click()
    Dim p As PictureBox
    
    Select Case CurrentPage
    Case 5: CurrentPage = 3
    Case 6:
            If optSinkType(ScriptSink).Value = True Then
                CurrentPage = 4
            Else
                CurrentPage = 5
            End If
    Case Else
            CurrentPage = CurrentPage - 1
    End Select
    
    SwitchPage
  
End Sub

Private Sub cmdNext_Click()
   
    Select Case CurrentPage
        Case 3:
            If optSinkType(ScriptSink).Value Then
                CurrentPage = CurrentPage + 1
            Else
                CurrentPage = CurrentPage + 2
            End If
        Case 4: CurrentPage = CurrentPage + 2
    
        Case Else
            CurrentPage = CurrentPage + 1
    End Select
    
    SwitchPage
End Sub

Private Sub Form_Load()
    CurrentPage = -1
    cmdNext_Click
End Sub


Private Sub cboProgIDs_Click()
    cmdNext.Enabled = CanMoveNext(CurrentPage)
    cmdFinish.Enabled = ReadyToFinish()
End Sub



Private Sub optEventNum_Click(Index As Integer)
    cmdNext.Enabled = CanMoveNext(CurrentPage)
    cmdFinish.Enabled = ReadyToFinish()
    FillProgIDList
End Sub

Private Sub optEventType_Click(Index As Integer)
    Select Case Index
        Case 0: optEventNum(OnArrival) = True
                optEventNum(OnArrival).Enabled = True
                optEventNum(OnPostEarly).Enabled = False
                optEventNum(OnPost).Enabled = False
                optEventNum(OnPostFinal).Enabled = False
                
        Case 1:
                optEventNum(OnArrival) = False
                optEventNum(OnArrival).Enabled = False
                optEventNum(OnPostEarly).Enabled = True
                optEventNum(OnPost).Enabled = True
                optEventNum(OnPostFinal).Enabled = True
                
    End Select
    
    cmdNext.Enabled = CanMoveNext(CurrentPage)
    cmdFinish.Enabled = ReadyToFinish
End Sub



Private Sub optPriority_Click(Index As Integer)
    Select Case Index
        Case 0: txtPriority.Text = 0
        Case 1: txtPriority.Text = 8191
        Case 2: txtPriority.Text = 16383
        Case 3: txtPriority.Text = 24575
        Case 4: txtPriority.Text = 32767
    End Select
    optPriority(Index).Value = True
End Sub

Private Sub optSinkType_Click(Index As Integer)
    cmdNext.Enabled = CanMoveNext(CurrentPage)
    cmdFinish.Enabled = ReadyToFinish()
End Sub


' After the user selects a DLL, the list of ProgIDs to choose from
' is populated by using Typelib information on the DLL to find classes
' that implement the interface for the event they are registering for
Private Sub FillProgIDList()
    On Error GoTo CancelThis

If Len(Trim(txtDLLLocation.Text)) > 0 Then
    Dim tlb As New TLIApplication
    Dim tlbinfo As TypeLibInfo
    Dim cclass As CoClassInfo
    Dim iface As InterfaceInfo
    Dim I As EventTypes
        
    cboProgIDs.Clear
    Set tlbinfo = tlb.TypeLibInfoFromFile(txtDLLLocation.Text)
    For Each cclass In tlbinfo.CoClasses
        For Each iface In cclass.Interfaces
            For I = OnArrival To OnPostFinal
                If optEventNum(I) Then
                    If iface.Guid = GetEvtInterfaceGUID(I) Then
                        cboProgIDs.AddItem tlbinfo.Name & "." & cclass.Name
                    End If
                End If
            Next
        Next
    Next
    
    If cboProgIDs.ListCount > 0 Then
        cboProgIDs.Text = cboProgIDs.List(0)
    End If
    
    cmdNext.Enabled = CanMoveNext(CurrentPage)
    cmdFinish.Enabled = ReadyToFinish()
    Exit Sub

CancelThis:
    cboProgIDs.Clear
    cmdNext.Enabled = CanMoveNext(CurrentPage)
    cmdFinish.Enabled = ReadyToFinish()

End If
End Sub
Private Sub txtDLLLocation_Change()
    txtDLLLocation.Text = LTrim(txtDLLLocation.Text)
    FillProgIDList
    cmdNext.Enabled = CanMoveNext(CurrentPage)
    cmdFinish.Enabled = ReadyToFinish()
End Sub

Private Sub txtName_Change()
    txtName.Text = LTrim(txtName.Text)
    cmdNext.Enabled = CanMoveNext(CurrentPage)
    cmdFinish.Enabled = ReadyToFinish()
End Sub


Private Sub txtPriority_Change()
    On Error Resume Next

    Dim Num As Long
    Dim optBtn As OptionButton
    
    
    Num = Val(txtPriority.Text)
  
    If Num < 0 Then
          ' This is the minimum alowed priority
          Num = 0
          txtPriority.Text = Str(Num)
          txtPriority.SelStart = Len(txtPriority.Text)
    End If
    If Num > 32767 Then
          ' This is the maximum allowed prio
          Num = 32767
          txtPriority.Text = Str(Num)
          txtPriority.SelStart = Len(txtPriority.Text)
    End If
    
    For Each optBtn In optPriority
        optBtn.Value = False
    Next

    cmdNext.Enabled = CanMoveNext(CurrentPage)
    cmdFinish.Enabled = ReadyToFinish()
End Sub

Private Sub txtPriority_KeyPress(KeyAscii As Integer)
    If (KeyAscii < Asc("0") Or KeyAscii > Asc("9")) And (KeyAscii <> 8) Then
        KeyAscii = 0
        Beep
    End If
End Sub

Private Sub txtScriptPath_Change()
    txtScriptPath.Text = LTrim(txtScriptPath.Text)
    cmdNext.Enabled = CanMoveNext(CurrentPage)
    cmdFinish.Enabled = ReadyToFinish()
End Sub

Private Sub txtVirtualServerNum_Change()
    txtVirtualServerNum.Text = Trim(txtVirtualServerNum.Text)
    cmdNext.Enabled = CanMoveNext(CurrentPage)
    cmdFinish.Enabled = ReadyToFinish()
End Sub

Private Sub txtVirtualServerNum_KeyPress(KeyAscii As Integer)
    If (KeyAscii < Asc("0") Or KeyAscii > Asc("9")) And (KeyAscii <> 8) Then
        KeyAscii = 0
        Beep
    End If
End Sub
