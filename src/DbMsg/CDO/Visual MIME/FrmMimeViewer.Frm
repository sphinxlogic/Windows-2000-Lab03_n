VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "TABCTL32.OCX"
Begin VB.Form frmMimeViewer 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Visual MIME"
   ClientHeight    =   6630
   ClientLeft      =   3075
   ClientTop       =   2550
   ClientWidth     =   9870
   Icon            =   "frmMimeViewer.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   6630
   ScaleWidth      =   9870
   Begin TabDlg.SSTab tabBP 
      Height          =   6495
      Left            =   4200
      TabIndex        =   1
      Top             =   120
      Width           =   5655
      _ExtentX        =   9975
      _ExtentY        =   11456
      _Version        =   393216
      Style           =   1
      TabHeight       =   520
      TabCaption(0)   =   "Fields"
      TabPicture(0)   =   "frmMimeViewer.frx":0E0A
      Tab(0).ControlEnabled=   -1  'True
      Tab(0).Control(0)=   "lstFields"
      Tab(0).Control(0).Enabled=   0   'False
      Tab(0).Control(1)=   "frmeFields"
      Tab(0).Control(1).Enabled=   0   'False
      Tab(0).ControlCount=   2
      TabCaption(1)   =   "Contents"
      TabPicture(1)   =   "frmMimeViewer.frx":0E26
      Tab(1).ControlEnabled=   0   'False
      Tab(1).Control(0)=   "pictBPContents"
      Tab(1).Control(1)=   "cmdBodyPartLoadFromFile"
      Tab(1).Control(2)=   "cmdContentsSaveToFile"
      Tab(1).Control(3)=   "cmdContentsSave"
      Tab(1).Control(4)=   "txtContents"
      Tab(1).Control(5)=   "lblCantShowContents"
      Tab(1).ControlCount=   6
      TabCaption(2)   =   "Full Stream"
      TabPicture(2)   =   "frmMimeViewer.frx":0E42
      Tab(2).ControlEnabled=   0   'False
      Tab(2).Control(0)=   "txtFullStream"
      Tab(2).Control(1)=   "cmdStreamSave"
      Tab(2).Control(2)=   "cmdStreamLoadFromFile"
      Tab(2).Control(3)=   "cmdStreamSaveToFile"
      Tab(2).ControlCount=   4
      Begin VB.PictureBox pictBPContents 
         BorderStyle     =   0  'None
         Height          =   5415
         Left            =   -74880
         ScaleHeight     =   5415
         ScaleWidth      =   5415
         TabIndex        =   20
         Top             =   480
         Visible         =   0   'False
         Width           =   5415
      End
      Begin VB.CommandButton cmdBodyPartLoadFromFile 
         Caption         =   "Load file into bodypart"
         Enabled         =   0   'False
         Height          =   375
         Left            =   -74760
         TabIndex        =   19
         Top             =   6000
         Width           =   1815
      End
      Begin VB.CommandButton cmdContentsSaveToFile 
         Caption         =   "Save Contents to File"
         Enabled         =   0   'False
         Height          =   375
         Left            =   -72720
         TabIndex        =   17
         Top             =   6000
         Width           =   1815
      End
      Begin VB.CommandButton cmdStreamSaveToFile 
         Caption         =   "Save Stream to File"
         Enabled         =   0   'False
         Height          =   375
         Left            =   -74520
         TabIndex        =   16
         Top             =   5880
         Width           =   1695
      End
      Begin VB.CommandButton cmdStreamLoadFromFile 
         Caption         =   "&Replace with text file"
         Enabled         =   0   'False
         Height          =   375
         Left            =   -72600
         TabIndex        =   15
         Top             =   5880
         Width           =   1695
      End
      Begin VB.CommandButton cmdContentsSave 
         Caption         =   "&Save Changes"
         Enabled         =   0   'False
         Height          =   375
         Left            =   -70680
         TabIndex        =   14
         Top             =   6000
         Width           =   1215
      End
      Begin VB.TextBox txtContents 
         Enabled         =   0   'False
         Height          =   5415
         Left            =   -74880
         MultiLine       =   -1  'True
         ScrollBars      =   3  'Both
         TabIndex        =   13
         Top             =   480
         Width           =   5415
      End
      Begin VB.CommandButton cmdStreamSave 
         Caption         =   "&Save Changes"
         Enabled         =   0   'False
         Height          =   375
         Left            =   -70680
         TabIndex        =   12
         Top             =   5880
         Width           =   1215
      End
      Begin VB.TextBox txtFullStream 
         Enabled         =   0   'False
         Height          =   5055
         Left            =   -74880
         MultiLine       =   -1  'True
         ScrollBars      =   3  'Both
         TabIndex        =   11
         Top             =   600
         Width           =   5415
      End
      Begin VB.Frame frmeFields 
         Caption         =   "Property Details"
         Height          =   3375
         Left            =   120
         TabIndex        =   3
         Top             =   2520
         Width           =   5415
         Begin VB.CommandButton cmdFieldsDelete 
            Caption         =   "&Delete"
            Enabled         =   0   'False
            Height          =   375
            Left            =   2640
            TabIndex        =   10
            Top             =   2880
            Width           =   1215
         End
         Begin VB.CommandButton cmdFieldsAdd 
            Caption         =   "&New"
            Enabled         =   0   'False
            Height          =   375
            Left            =   1320
            TabIndex        =   9
            Top             =   2880
            Width           =   1215
         End
         Begin VB.CommandButton cmdFieldsSave 
            Caption         =   "&Save Changes"
            Enabled         =   0   'False
            Height          =   375
            Left            =   3960
            TabIndex        =   8
            Top             =   2880
            Width           =   1335
         End
         Begin VB.TextBox txtFieldValue 
            Height          =   1095
            Left            =   120
            MultiLine       =   -1  'True
            TabIndex        =   7
            Top             =   1560
            Width           =   5175
         End
         Begin VB.TextBox txtFieldName 
            Height          =   285
            Left            =   120
            TabIndex        =   6
            Top             =   720
            Width           =   5175
         End
         Begin VB.Label lblFieldValue 
            Caption         =   "Value:"
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
            Left            =   120
            TabIndex        =   5
            Top             =   1200
            Width           =   1695
         End
         Begin VB.Label lblFieldName 
            Caption         =   "Name:"
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
            Left            =   120
            TabIndex        =   4
            Top             =   360
            Width           =   1695
         End
      End
      Begin VB.ListBox lstFields 
         Height          =   1620
         ItemData        =   "frmMimeViewer.frx":0E5E
         Left            =   120
         List            =   "frmMimeViewer.frx":0E60
         TabIndex        =   2
         Top             =   480
         Width           =   5415
      End
      Begin VB.Label lblCantShowContents 
         Height          =   975
         Left            =   -74880
         TabIndex        =   18
         Top             =   600
         Width           =   5295
      End
   End
   Begin MSComDlg.CommonDialog OpenBoxDlg 
      Left            =   9360
      Top             =   0
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      DefaultExt      =   "eml"
      DialogTitle     =   "Choose an email file to open"
      Filter          =   "Email Messages (*.eml)|*.eml|Text Files (*.txt)|*.txt|All Files (*.*)|*.*"
   End
   Begin MSComctlLib.TreeView treeMIME 
      Height          =   6375
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   3975
      _ExtentX        =   7011
      _ExtentY        =   11245
      _Version        =   393217
      HideSelection   =   0   'False
      LabelEdit       =   1
      LineStyle       =   1
      Style           =   6
      Appearance      =   1
   End
   Begin MSComDlg.CommonDialog StreamReplaceDialog 
      Left            =   8760
      Top             =   0
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      DialogTitle     =   "Choose a file to replace the stream of this bodypart"
      Filter          =   "Text Files (*.txt)|*.txt|Email Messages (*.eml)|*.eml|All Files (*.*)|*.*"
      Flags           =   1052676
   End
   Begin MSComDlg.CommonDialog StreamSaveDialog 
      Left            =   8160
      Top             =   0
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      DefaultExt      =   "txt"
      DialogTitle     =   "Choose where to save the stream of this bodypart"
      Filter          =   "Text Files (*.txt)|*.txt|Email Messages (*.eml)|*.eml|All Files (*.*)|*.*"
      Flags           =   1048580
   End
   Begin MSComDlg.CommonDialog ContentsSaveDialog 
      Left            =   7560
      Top             =   0
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      DefaultExt      =   "txt"
      DialogTitle     =   "Choose where to save the contents of this body part."
      Filter          =   "Text Files (*.txt)|*.txt|All Files (*.*)|*.*"
      Flags           =   104850
   End
   Begin MSComDlg.CommonDialog AddAttachmentDialog 
      Left            =   6960
      Top             =   0
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      CancelError     =   -1  'True
      DialogTitle     =   "Choose a file to add as an attachment"
      Filter          =   "All Files (*.*)|*.*"
      Flags           =   2
   End
   Begin MSComDlg.CommonDialog SaveAsDialog 
      Left            =   6360
      Top             =   0
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      DefaultExt      =   "eml"
      DialogTitle     =   "Where would you like to save this file?"
      Filter          =   "Email Messages (*.eml)|*.eml|Text Files (*.txt)|*.txt|All Files (*.*)|*.*"
      Flags           =   1048580
   End
   Begin MSComDlg.CommonDialog BodypartReplaceDialog 
      Left            =   5760
      Top             =   0
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      CancelError     =   -1  'True
      DialogTitle     =   "Choose a file to load into this MIME body part."
      Filter          =   "All Files (*.*)|*.*"
      Flags           =   1048580
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&File"
      Begin VB.Menu mnuNew 
         Caption         =   "&New"
      End
      Begin VB.Menu mnuOpen 
         Caption         =   "&Open"
         Shortcut        =   ^O
      End
      Begin VB.Menu mnuSeperator1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuSave 
         Caption         =   "&Save"
         Enabled         =   0   'False
         Shortcut        =   ^S
      End
      Begin VB.Menu mnuSaveAs 
         Caption         =   "Sa&ve As..."
      End
      Begin VB.Menu mnuSeperator2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuExit 
         Caption         =   "E&xit"
         Shortcut        =   ^Q
      End
   End
   Begin VB.Menu mnuMessage 
      Caption         =   "&Message"
      Begin VB.Menu mnuCreateMHTML 
         Caption         =   "&Create MTHML"
      End
      Begin VB.Menu mnuAddAttachment 
         Caption         =   "&Add Attachment..."
      End
      Begin VB.Menu mnuSeperator4 
         Caption         =   "-"
      End
      Begin VB.Menu mnuRefresh 
         Caption         =   "&Refresh"
         Shortcut        =   ^R
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "&Help"
      Begin VB.Menu mnuAbout 
         Caption         =   "A&bout"
      End
   End
   Begin VB.Menu mnuPopUp 
      Caption         =   "PopUp"
      Visible         =   0   'False
      Begin VB.Menu mnuDeleteBP 
         Caption         =   "Delete"
      End
      Begin VB.Menu mnuCreateChildBP 
         Caption         =   "Add child body part"
      End
      Begin VB.Menu mnuViewEmbeddedMessage 
         Caption         =   "View Embedded Message"
         Enabled         =   0   'False
      End
   End
End
Attribute VB_Name = "frmMimeViewer"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

' My global configuration
Dim Config As New Configuration

' This is a reference to the current message
' that is being viewed
Dim Msg As New Message

' This is a reference to the current bodypart
' that is being viewed
Dim BodyPart As IBodyPart

' This indicates the key of the node that is
' currently loaded (so I don't reload a bodypart
' on a click that is already loaded)
Dim LoadedKey As String

' This indicates if this form is currently showing an embedded message
Dim IsEmbedded As Boolean

' This indicates the filename that a message was loaded from
Dim LoadedFile As String

' This indicates the current field being displayed in the fields dialog
Dim FieldIndex As String

' This is set if the user right-clicks on controls with special
' right-click behavior
Dim RightClick As Boolean


'---------------------------------------------------
' Sub cmdContentsSave_Click
'
' Takes the changes the user has made in the text box
' with the contents of the body part and commits the changes
' back to the body part.
'
'---------------------------------------------------

Private Sub cmdContentsSave_Click()
    Dim Strm As Stream
    
    Set Strm = BodyPart.GetDecodedContentStream
    
    Strm.Position = 0
    
    If Len(txtContents.Text) > 0 Then
        Strm.WriteText txtContents.Text
    End If
    
    Strm.SetEOS
    Strm.Flush
    
    cmdContentsSave.Enabled = False
    LoadFullStreamTab
    LoadFieldsTab
    mnuSave.Enabled = True
End Sub

'---------------------------------------------------
' Sub cmdContentsSaveToFile_Click
'
' Saves the contents of the body part to a file using
' Bodypart.SaveToFile
'
' It also sets a default file extension based on the
' BodyPart.FileName property.  For GIF and JPEG files,
' it will also set the correct default file extension
'
'---------------------------------------------------
Private Sub cmdContentsSaveToFile_Click()
    On Error GoTo CantSave

    Dim oldCurDir As String
    Dim Strm As Stream
    Dim i As Integer
    Dim FileExt As String
    
    oldCurDir = CurDir
    
    ' If the bodypart has a filename associated with it then
    ' use that filename by default to save the body part
    If BodyPart.FileName <> "" Then
        
        ' Configure the save dialog box to have the filename (without extension)
        ' and add the extension to the drop down list in the save dialog box
        ContentsSaveDialog.FileName = BodyPart.FileName
        i = InStrRev(BodyPart.FileName, ".")
        If i > 0 Then
            FileExt = Right(BodyPart.FileName, Len(BodyPart.FileName) - i)
            ContentsSaveDialog.DefaultExt = FileExt
            ContentsSaveDialog.FileName = Left(BodyPart.FileName, i - 1)
            ContentsSaveDialog.Filter = UCase(FileExt) & " files (*." & FileExt & ")|*." & FileExt & "|" & ContentsSaveDialog.Filter
        Else
            ContentsSaveDialog.FileName = BodyPart.FileName
        End If
    Else
        If UCase(BodyPart.ContentMediaType) = "IMAGE/GIF" Then
            ContentsSaveDialog.FileName = "image"
            FileExt = "gif"
            ContentsSaveDialog.DefaultExt = FileExt
            ContentsSaveDialog.Filter = UCase(FileExt) & " files (*." & FileExt & ")|*." & FileExt & "|" & ContentsSaveDialog.Filter
        Else
            If UCase(BodyPart.ContentMediaType) = "IMAGE/JPEG" Then
                ContentsSaveDialog.FileName = "image"
                FileExt = "jpg"
                ContentsSaveDialog.DefaultExt = FileExt
                ContentsSaveDialog.Filter = UCase(FileExt) & " files (*." & FileExt & ")|*." & FileExt & "|" & ContentsSaveDialog.Filter
            Else
                ContentsSaveDialog.FileName = "bodypart contents"
            End If
        End If
    End If
    
    ContentsSaveDialog.CancelError = True
    ContentsSaveDialog.ShowSave
    
    If ContentsSaveDialog.FileName <> "" Then
        BodyPart.SaveToFile ContentsSaveDialog.FileName
    End If
           
    ChDir oldCurDir
    
    Exit Sub
    
CantSave:
    If Err.Number <> 32755 Then
        MsgBox "Error in saving the contents of the body part." & vbCrLf & Err.Description & " (" & Hex(Err.Number) & ")", vbCritical, "Error."
    Else
        ' The user cancelled the save dialog box
    End If
    
    Err.Clear
End Sub

'---------------------------------------------------
' Sub cmdFieldsAdd_Click
'
' This clears the boxes where fields are displayed
' so that a new one can be added by the user
'
'---------------------------------------------------
Private Sub cmdFieldsAdd_Click()
    txtFieldName.Text = ""
    txtFieldValue.Text = ""
    cmdFieldsSave.Enabled = False
    cmdFieldsDelete.Enabled = False
    FieldIndex = ""
    mnuSave.Enabled = True
End Sub

'---------------------------------------------------
' Sub cmdFieldsDelete_Click
'
' This deletes the current field from the body part's
' fields collection.
'
'---------------------------------------------------
Private Sub cmdFieldsDelete_Click()
     On Error GoTo CantDelete
     
     Dim Index As Integer
     
     
     If FieldIndex <> "" Then
        BodyPart.Fields.Delete (FieldIndex)
        BodyPart.Fields.Update
        Index = lstFields.ListIndex
        
        LoadFieldsTab
        LoadFullStreamTab
        LoadContentsTab
        
        If Index < lstFields.ListCount Then
            lstFields.Selected(Index) = True
        Else
            lstFields.Selected(lstFields.ListCount - 1) = True
        End If
        mnuSave.Enabled = True
     End If
     
     Exit Sub
     
CantDelete:
    MsgBox "Cannot delete this property because it is read-only or required.", vbCritical, "Error deleting property."
    Err.Clear
End Sub

'---------------------------------------------------
' Sub cmdFieldsSave_Click
'
' This saves any changes made to the fields in the
' field name/value text boxes or creates a new field
' if necessary
'
'---------------------------------------------------
Private Sub cmdFieldsSave_Click()
    On Error GoTo CannotSave
    
    Dim flds As Fields
    Dim i As Integer
    Dim FieldName As String
        
    Set flds = BodyPart.Fields
        
    FieldName = txtFieldName.Text
    
    If FieldIndex = txtFieldName.Text Then
        ' If the name has not changed, then just save the new value
        flds.Item(FieldIndex) = txtFieldValue.Text
    Else
        ' Delete the original field if
        ' this is a change to the name of an existing field
        '
        ' If we are adding a new field, do not do a delete
        If FieldIndex <> "" Then
            flds.Delete (FieldIndex)
        End If
        
        flds.Item(FieldName) = txtFieldValue.Text
        flds.Update
        LoadFieldsTab
        For i = 0 To lstFields.ListCount - 1
            lstFields.Selected(i) = (lstFields.List(i) = FieldName)
        Next
    End If
    
    If (FieldName = cdoContentMediaType) Or (FieldName = cdoContentType) Then
        treeMIME.SelectedItem.Text = flds(cdoContentMediaType)
    End If
    
    cmdFieldsSave.Enabled = False
    LoadFullStreamTab
    LoadContentsTab
    mnuSave.Enabled = True
    
    Exit Sub
CannotSave:
    MsgBox "Unable to save changes to that property because either the data type is incorrect or the property is read-only." & vbCrLf & "Error: " & Err.Description & vbCrLf & "Error #: 0x" & Hex(Err.Number), vbCritical, "Error!"
    Err.Clear
End Sub

'---------------------------------------------------
' Sub cmdStreamLoadFromFile_Click
'
' This loads a text file from disk and uses the contents
' of that file to replace the body part's entire stream
'
'---------------------------------------------------
Private Sub cmdStreamLoadFromFile_Click()
    Dim oldCurDir   As String
    Dim Strm As Stream
   
    oldCurDir = CurDir
    StreamReplaceDialog.ShowOpen
    If StreamReplaceDialog.FileName <> "" Then
        Set Strm = BodyPart.GetStream
        Strm.Position = 0
        Strm.Type = adTypeText
        Strm.LoadFromFile StreamReplaceDialog.FileName
        Strm.Flush
        LoadMessage Msg
        mnuSave.Enabled = True
    End If
        
    ChDir oldCurDir
End Sub

'---------------------------------------------------
' Sub cmdStreamSave_Click
'
' This takes the changes typed in by the user in the
' full stream text box and commits them to the body part
'
'---------------------------------------------------
Private Sub cmdStreamSave_Click()
    On Error GoTo CantSave
    Dim NodeKey As String
    
    Dim Strm As Stream
    
    Set Strm = BodyPart.GetStream
    Strm.Position = 0
    
    If Len(txtFullStream.Text) > 0 Then
        Strm.WriteText txtFullStream.Text, adWriteChar
    End If
    
    Strm.SetEOS
    Strm.Flush
    
    NodeKey = treeMIME.SelectedItem.Key
    
    LoadMessage Msg
    
    treeMIME.Nodes(NodeKey).Selected = True
    LoadBodypartInfo
    Exit Sub
    
CantSave:
    If Err.Number = 35601 Then
        ' The bodypart does not exist in the new message because
        ' the MIME structure has been reorganized
    Else
        MsgBox "Unable to save changes to the body part's stream.", vbCritical, "Error in saving changes."
    End If
    Err.Clear
End Sub

'---------------------------------------------------
' Sub cmdStreamSaveToFile_Click
'
' Allows the user to save the complete stream of the body
' part to a text file
'
'---------------------------------------------------
Private Sub cmdStreamSaveToFile_Click()
    On Error GoTo CantSave

    Dim oldCurDir   As String
    Dim Strm As Stream
   
    oldCurDir = CurDir
    StreamSaveDialog.ShowSave
    If StreamSaveDialog.FileName <> "" Then
        Set Strm = BodyPart.GetStream
        Strm.SaveToFile StreamSaveDialog.FileName, adSaveCreateOverWrite
    End If
           
    ChDir oldCurDir
    
    Exit Sub
CantSave:
    MsgBox "Error in saving the stream of the body part." & vbCrLf & Err.Description & " (" & Hex(Err.Number) & ")", vbCritical, "Error."
    Err.Clear
End Sub

'---------------------------------------------------
' Sub cmdBodyPartLoadFromFile_Click
'
' Allows the user to load a file into the contents
' of a body part (for example, for adding an attachment).
'
'---------------------------------------------------
Private Sub cmdBodyPartLoadFromFile_Click()
    On Error GoTo CantLoad
    
    Dim Strm As Stream

    BodypartReplaceDialog.ShowOpen
    
    If BodypartReplaceDialog.FileName <> "" Then
        Set Strm = BodyPart.GetDecodedContentStream
        Strm.Type = adTypeBinary
        Strm.LoadFromFile BodypartReplaceDialog.FileName
        Strm.Flush
        
        LoadBodypartInfo
        mnuSave.Enabled = True
    End If
    
    Exit Sub
CantLoad:
    
    Err.Clear
End Sub


Private Sub Form_Load()
    ActivateForm False, False
    Config.Fields(cdoAutoPromoteBodyParts) = False
    Config.Fields.Update
End Sub

'---------------------------------------------------
' Sub listFields_Click
'
' When a user clicks on a field name, it puts the
' field's name and value into the appropriate boxes
' and enableds/disables the corresponding buttons
'
'---------------------------------------------------
Private Sub lstFields_Click()
    On Error Resume Next
    
    Dim fld As Field
    Dim fldName As String
    
    
    If lstFields.ListIndex >= 0 Then
        fldName = lstFields.List(lstFields.ListIndex)
        txtFieldName.Text = fldName
        Set fld = BodyPart.Fields.Item(fldName)
        txtFieldValue.Text = fld.Value
        
        frmeFields.Enabled = True
        cmdFieldsSave.Enabled = False
        cmdFieldsDelete.Enabled = True
        cmdFieldsAdd.Enabled = True
        lblFieldName.Enabled = True
        lblFieldValue.Enabled = True
        FieldIndex = fldName
    End If
End Sub

'---------------------------------------------------
' Sub mnuAbout_Click
'
' Shows the "about" form
'
'---------------------------------------------------
Private Sub mnuAbout_Click()
    frmAbout.Show vbModal, Me
End Sub

'---------------------------------------------------
' Sub mnuAddAttachment_Click
'
' Brings up a box that allows the user to pick a file
' to add as an attachment to the message using
' Message.AddAttachment
'
'---------------------------------------------------
Private Sub mnuAddAttachment_Click()
    On Error GoTo FailedOpen

    AddAttachmentDialog.Flags = cdlOFNFileMustExist Or Mscomdlg.cdlOFNNoDereferenceLinks Or cdlOFNHideReadOnly
    AddAttachmentDialog.ShowOpen
    Msg.AddAttachment AddAttachmentDialog.FileName
    mnuSave.Enabled = True
    
    LoadMessage Msg
    Exit Sub

FailedOpen:
    If Err.Number = -2146644475 Then
        MsgBox "Error adding child body part.  When you add a body part after having deleted one previously, an error occurs.  This is a known issue in this release.", vbExclamation, "Error"
        Msg.Attachments.Delete Msg.Attachments.Count
        LoadMessage Msg
    Else
        If Err.Number <> 32755 Then
            MsgBox "Unable to add the attachment." & vbCrLf & "Error: " & Err.Description & vbCrLf & "Err #:" & Hex(Err.Number), vbInformation
        Else
        ' The user cancelled the open box
        End If
    End If
    
    Err.Clear
End Sub

'---------------------------------------------------
' Sub mnuCreateChildBP_Click
'
' Creates a new body part that is a child of the
' current one.
'
'---------------------------------------------------

Private Sub mnuCreateChildBP_Click()
On Error GoTo AddBPError

    Dim ParentBP As IBodyPart
    Dim Bp As IBodyPart
    Dim Strm As Stream
    
    Set ParentBP = BodyPart
    Set Bp = ParentBP.BodyParts.Add
    mnuSave.Enabled = True
    LoadMessage Msg
    
    Exit Sub
AddBPError:
    If Err.Number = -2146644475 Then
        MsgBox "Error adding child body part.  When you add a body part after having deleted one previously, an error occurs.  This is a known issue in this release.", vbExclamation, "Error"
        ParentBP.BodyParts.Delete ParentBP.BodyParts.Count
        LoadMessage Msg
        Err.Clear
    End If
End Sub

'--------------------------------------------------
' Sub mnuCreateMHTML_Click
'
' Opens an input box that takes in a URL.
' Calls CreateMHTMLBody on the current message
'
'--------------------------------------------------
Private Sub mnuCreateMHTML_Click()
    On Error Resume Next

    Dim URL As String

    
    URL = InputBox("Enter a URL to create from.", "URL")
    If Len(URL) > 0 Then
        Msg.CreateMHTMLBody URL
        
        ' Do some error handling on CreateMHTMLBody and reset the global
        ' message object
        If Err.Number <> 0 Then
            MsgBox "There was an error creating from that URL." & vbCrLf & vbCrLf & "  Err: 0x" & Hex(Err.Number) & vbCrLf & "  " & Err.Description, vbExclamation
            Err.Clear
        Else
        ' If it succeeded, load the global message object
            mnuSave.Enabled = True
            LoadMessage Msg
        End If
    End If
End Sub

'--------------------------------------------------
' Sub OpenFromFile
'
' Takes in the name of a directory and file and
'  opens a message object from that file.
' Then it loads the message into the MIME viewer
'
' Returns TRUE if a message file was successfully opened
'--------------------------------------------------
Public Function OpenFromFile(FileName As String) As Boolean
    On Error GoTo CantOpen
    
    Dim Strm As ADODB.Stream
    Dim objMsg As New Message
    Dim success As Boolean

    If FileName <> "" Then
        Set Strm = objMsg.GetStream
        Strm.LoadFromFile FileName
        Strm.Flush
        success = LoadMessage(objMsg)
        If success Then Me.Caption = "[" & FileName & "] - Visual MIME"
        LoadedFile = FileName
    Else
        success = False
    End If
    
    OpenFromFile = success
    
    Exit Function

CantOpen:
    MsgBox "Unable to open the file " & FileName & "." & vbCrLf & vbCrLf & "  Err: 0x" & Hex(Err.Number) & vbCrLf & "  " & Err.Description, vbCritical, "Error loading file."
    Err.Clear
    OpenFromFile = False
End Function

'---------------------------------------------------
' Sub mnuDeleteBP_Click
'
' Deletes the current body part
'
'---------------------------------------------------
Private Sub mnuDeleteBP_Click()
    Dim curNode As Node
    Dim result As VbMsgBoxResult
    Dim i As Integer
    Dim NodeFocusKey As String
    
    result = MsgBox("Are you sure you want to delete this body part?", vbYesNo)
    
    If result = vbYes Then
        Set curNode = treeMIME.SelectedItem
        mnuSave.Enabled = True
        If curNode.Key = "R" Then
            Set Msg = Nothing
            Set Msg = New Message
            LoadMessage Msg
        Else
           
            If Not (curNode.Previous Is Nothing) Then
                NodeFocusKey = curNode.Previous.Key
            Else
                NodeFocusKey = curNode.Parent.Key
            End If
            
            curNode.Parent.Tag.BodyParts.Delete curNode.Tag
            LoadMessage Msg
            
            treeMIME.Nodes(NodeFocusKey).Selected = True
            
            
        End If
    End If
    
End Sub

'--------------------------------------------------
' Sub mnuExit_Click
'
' Ends the program
'--------------------------------------------------
Private Sub mnuExit_Click()
    Unload Me
End Sub

'--------------------------------------------------
' Sub ActivateForm
'
' Enables/disables buttons & menu options
'--------------------------------------------------
Public Sub ActivateForm(Enabled As Boolean, Embedded As Boolean)
    IsEmbedded = Embedded

    mnuOpen.Enabled = Not Embedded
    mnuNew.Enabled = (Not Embedded) Or (Not Enabled)
    
    If Embedded Then
        mnuSave.Caption = "Save embedded message"
    Else
        mnuSave.Caption = "Save"
    End If
    mnuSaveAs.Enabled = Enabled
    frmeFields.Enabled = Enabled
    lblFieldName.Enabled = Enabled
    lblFieldValue.Enabled = Enabled
    cmdFieldsAdd.Enabled = Enabled
    cmdFieldsDelete.Enabled = Enabled
    mnuCreateMHTML.Enabled = Enabled
    mnuAddAttachment.Enabled = Enabled
    mnuRefresh.Enabled = Enabled
    
End Sub

'--------------------------------------------------
' Sub mnuNew_Click
'
' Creates a new message and loads it.
'--------------------------------------------------
Private Sub mnuNew_Click()
    Dim NewMsg As New Message
    
    ActivateForm True, False
    mnuSave.Enabled = False
    
    LoadMessage NewMsg
End Sub

'--------------------------------------------------
' Sub mnuOpen_Click
'
' Shows an open dialog box and opens from the selected
' file
'
'--------------------------------------------------
Private Sub mnuOpen_Click()
   Dim oldCurDir   As String
   Dim success As Boolean
    
    OpenBoxDlg.Flags = Mscomdlg.cdlOFNFileMustExist Or Mscomdlg.cdlOFNNoDereferenceLinks Or cdlOFNHideReadOnly
    oldCurDir = CurDir
    OpenBoxDlg.ShowOpen
    If OpenBoxDlg.FileName <> "" Then
        success = OpenFromFile(OpenBoxDlg.FileName)
        mnuSave.Enabled = False
    End If
    
    ChDir oldCurDir
End Sub


'--------------------------------------------------
' RecursiveTraversal Sub
'
' This recursively traverses the MIME structure of the
'   bodypart passed into it and adds the bodyparts into the
'   tree control based on the parentkey parameter
'--------------------------------------------------
Sub RecursiveTraversal(MimeTree As TreeView, BodyP As IBodyPart, ParentKey As String)
    On Error GoTo ErrorInTraversal

    Dim Bp As IBodyPart
    Dim NewNode As Node
    Dim i As Integer
    
    i = 1
    
    For Each Bp In BodyP.BodyParts
        Set NewNode = MimeTree.Nodes.Add(ParentKey, tvwChild, ParentKey & "." & LTrim(Str(i)), Bp.ContentMediaType)
        Set NewNode.Tag = Bp
        NewNode.Expanded = True
        RecursiveTraversal MimeTree, Bp, NewNode.Key
        i = i + 1
    Next
    
    Exit Sub
ErrorInTraversal:
    If Err.Number = -2146644475 Then
            Err.Raise -2146644475
    Else
        MsgBox "There was an error traversing the MIME hierarchy."
    End If
    Err.Clear
End Sub


'--------------------------------------------------
' LoadMessage public function
'
' This function loads a message from into the MIME viewer
'   from an existing message object.
'
' It returns the success value of the operation.
'--------------------------------------------------
Public Function LoadMessage(Msg2Load As Message) As Boolean
    On Error GoTo CantLoad

    Dim RootNode As Node
    Dim Bp As IBodyPart
    
    Set Msg = Msg2Load
    Set Msg.Configuration = Config
    
    Me.MousePointer = 11

    treeMIME.Nodes.Clear
    Set RootNode = treeMIME.Nodes.Add(, , "R", Msg2Load.BodyPart.ContentMediaType)
    Set RootNode.Tag = Msg2Load.BodyPart
    RootNode.Expanded = True
    
    RecursiveTraversal treeMIME, Msg2Load, RootNode.Key
        
    treeMIME.Nodes("R").Selected = True
    LoadBodypartInfo
    
    Me.MousePointer = 0
    
    
    ActivateForm True, IsEmbedded
    Msg.DataSource.IsDirty = False
    LoadMessage = True
    Exit Function
    
CantLoad:
    If Err.Number = -2146644475 Then
            Err.Raise -2146644475
    Else
        MsgBox "Unable to load that message.  This application can only load MIME messages." & vbCrLf & vbCrLf & "  Err: 0x" & Hex(Err.Number) & vbCrLf & "  " & Err.Description, vbCritical, "Error!"
        Err.Clear
        Me.MousePointer = 0
        LoadMessage = False
    End If
End Function

'--------------------------------------------------
' FindBodyPart function
'
' Takes in a key which is a reference to a node in
'   the treeMIME control and returns the bodypart
'   of the message that corresponds to that key
'
' Used to load information about a bodypart when
'   the user clicks on a node in the tree.
'--------------------------------------------------
Private Function FindBodyPart(ByVal Key As String, Root As IBodyPart) As IBodyPart
    Set FindBodyPart = treeMIME.Nodes(Key).Tag
End Function

'--------------------------------------------------
' Sub mnuRefresh_Click
'
' Re-loads the current message
'--------------------------------------------------
Private Sub mnuRefresh_Click()
    LoadMessage Msg
End Sub

'--------------------------------------------------
' Sub mnuSave_Click
'
' Saves the message either back to the stream or
' to its data source if it has been opened
' as an embedded message
'
'--------------------------------------------------
Private Sub mnuSave_Click()
    mnuSave.Enabled = False
    If mnuSave.Caption <> "Save" Then
        Msg.DataSource.Save
        LoadMessage Msg
    Else
        If LoadedFile <> "" Then
            Msg.GetStream.SaveToFile LoadedFile, adSaveCreateOverWrite
            
            LoadMessage Msg
        End If
    End If
End Sub


'--------------------------------------------------
' Sub LoadFieldsTab
'
' Traverses the fields collection of the body part
' and adds them to the list box in the fields tab
'
'--------------------------------------------------
Private Sub LoadFieldsTab()
    Dim fld As Field
    
    lstFields.Clear
    For Each fld In BodyPart.Fields
        lstFields.AddItem fld.Name
    Next
    lstFields.Selected(0) = True
    lstFields_Click
End Sub

'--------------------------------------------------
' Sub LoadFullStreamTab
'
' Gets the full stream of the body part (Bodypart.GetStream)
' and loads it into the text box on the "Full Stream" tab
'
'--------------------------------------------------
Private Sub LoadFullStreamTab()
    txtFullStream.Text = BodyPart.GetStream.ReadText
    cmdStreamSave.Enabled = False
    cmdStreamLoadFromFile.Enabled = True
    cmdStreamSaveToFile.Enabled = True
    txtFullStream.Enabled = True
End Sub

'--------------------------------------------------
' Sub LoadContentsTab
'
' Gets the contents (Bodypart.GetDecodedContentStream) of
' the body part and displays them if they are text or images.
'
' Else, the user is told the contents can't be displayed
'
' This also activates a button to enable saving of the
' contents.
'
'--------------------------------------------------
Private Sub LoadContentsTab()
    On Error GoTo nocontent
    
    Dim Strm As Stream
    Dim TempFileName As String
    Dim pictBP As IPictureDisp
    

    
    Set Strm = BodyPart.GetDecodedContentStream
    
    If UCase(BodyPart.ContentMediaType) = "IMAGE/GIF" Or _
        UCase(BodyPart.ContentMediaType) = "IMAGE/JPEG" Then
        
        
        ' Save the image to disk and use VB's
        ' LoadPicture to load it into a VB picture control
        TempFileName = "temp-image"
        If UCase(BodyPart.ContentMediaType) = "IMAGE/GIF" Then
            TempFileName = TempFileName & ".gif"
        Else
            TempFileName = TempFileName & ".jpg"
        End If
        Strm.SaveToFile TempFileName, adSaveCreateOverWrite
        
        Set pictBP = LoadPicture(TempFileName)
        Set pictBPContents.Picture = pictBP
        Kill TempFileName
        
        pictBPContents.Visible = True
        txtContents.Visible = False
    Else
        pictBPContents.Visible = False
        txtContents.Text = Strm.ReadText
        txtContents.Enabled = True
        txtContents.Visible = True
    End If
    
    cmdContentsSave.Enabled = False
    cmdContentsSaveToFile.Enabled = True
    cmdBodyPartLoadFromFile.Enabled = True
    
    Exit Sub
    
nocontent:
    txtContents.Visible = False
    txtContents.Enabled = False
    cmdContentsSave.Enabled = False
    pictBPContents.Visible = False
    If Left(UCase(BodyPart.ContentMediaType), 9) = "MULTIPART" Then
        cmdContentsSaveToFile.Enabled = False
        lblCantShowContents.Caption = "This body part has a content-type of " & BodyPart.ContentMediaType & ", and therefore has no content." & vbCrLf & vbCrLf & "Click on the Full Stream tab to view the entire bodypart, including headers."
        cmdBodyPartLoadFromFile.Enabled = False
    Else
        lblCantShowContents.Caption = "This body part contains binary data which cannot be displayed in a text box." & vbCrLf & vbCrLf & "Click on the Full Stream tab to view the entire bodypart, including headers."
        cmdBodyPartLoadFromFile.Enabled = True
    End If
End Sub


'--------------------------------------------------
' Sub LoadBodypartInfo
'
' When a node is clicked on in the tree control, this
' is called to find the corresponding bodypart
' and load the information about the body part
'
'--------------------------------------------------
Private Sub LoadBodypartInfo()
    Dim SelectedNode As Node
    Dim fld
    
    Me.MousePointer = 11
        
    If treeMIME.Nodes.Count > 0 Then
        Set SelectedNode = treeMIME.SelectedItem
        LoadedKey = SelectedNode.Key
        Set BodyPart = FindBodyPart(SelectedNode.Key, Msg)
        LoadFieldsTab
        LoadFullStreamTab
        LoadContentsTab
    End If
    
    Me.MousePointer = 0
    Exit Sub
End Sub


'--------------------------------------------------
' Sub mnuSaveAs_Click
'
' Save the current message out to a file
'
'--------------------------------------------------
Private Sub mnuSaveAs_Click()
    On Error GoTo CantSave
    
    SaveAsDialog.ShowSave
    If SaveAsDialog.FileName <> "" Then
        Msg.GetStream.SaveToFile SaveAsDialog.FileName, adSaveCreateOverWrite
        LoadMessage Msg
    End If
    Exit Sub
    
CantSave:
    MsgBox "There was an error saving the file." & vbCrLf & "Error: " & Err.Description & vbCrLf & "Err: " & Hex(Err.Number), vbExclamation
    Err.Clear
End Sub

'--------------------------------------------------
' Sub mnuViewEmbeddedMessage_Click
'
' Creates a new message and opens the embedded message
' using the IDataSource interface.  Then creates a new
' instance of the Visual MIME form and loads the embedded
' message into it.
'
'--------------------------------------------------
Private Sub mnuViewEmbeddedMessage_Click()
    On Error GoTo EmbeddedError

    Dim frm As New frmMimeViewer
    Dim EmbeddedMsg As New Message
    
    EmbeddedMsg.DataSource.OpenObject BodyPart, cdoIBodyPart
    
    frm.ActivateForm False, True
    frm.LoadMessage EmbeddedMsg
    frm.Caption = "[embedded message] " & Me.Caption
    frm.Left = Me.Left + Me.Width * 0.03
    frm.Top = Me.Top + Me.Height * 0.03
    frm.Show vbModal, Me

    
    Set frm = Nothing
    
    LoadBodypartInfo ' reload current bodypart info in case changes
                     ' were made to the embedded message
    Exit Sub

EmbeddedError:
    MsgBox "Unable to view the embedded message.  Perhaps it is not a valid RFC 822 message." & vbCrLf & "Error: " & Err.Description & vbCrLf & "Err #:" & Hex(Err.Number), vbExclamation
    Err.Clear
End Sub

'--------------------------------------------------
' Sub treeMIME_MouseDown
'
' Keeps track of whether or not the right-mouse button
' was used
'
'--------------------------------------------------
Private Sub treeMIME_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
    If Button = vbRightButton Then
        RightClick = True
    Else
        RightClick = False
    End If
End Sub

'--------------------------------------------------
' Sub treeMIME_NodeClick
'
' Loads the information about the selected body part
' If a right-click was used, the popup menu is shown.
'
'--------------------------------------------------
Private Sub treeMIME_NodeClick(ByVal Node As MSComctlLib.Node)
    
    LoadBodypartInfo
    
    If RightClick Then
        mnuViewEmbeddedMessage.Enabled = (UCase(BodyPart.ContentMediaType) = "MESSAGE/RFC822")
        PopupMenu mnuPopUp
    End If
    
End Sub

'--------------------------------------------------
' Sub txtContents_Change
'
' Enables the contents save button
'
'--------------------------------------------------
Private Sub txtContents_Change()
    cmdContentsSave.Enabled = True
End Sub

'--------------------------------------------------
' Sub txtFullStream_Change
'
' Enables the full stream save button
'
'--------------------------------------------------
Private Sub txtFullStream_Change()
    cmdStreamSave.Enabled = True
End Sub

'--------------------------------------------------
' Sub txtFieldName_Change
'
' Enables the field save button
'
'--------------------------------------------------
Private Sub txtFieldName_Change()
    cmdFieldsSave.Enabled = True
End Sub

'--------------------------------------------------
' Sub txtFieldValue_Change
'
' Enables the field save button
'
'--------------------------------------------------
Private Sub txtFieldValue_Change()
    cmdFieldsSave.Enabled = True
End Sub

