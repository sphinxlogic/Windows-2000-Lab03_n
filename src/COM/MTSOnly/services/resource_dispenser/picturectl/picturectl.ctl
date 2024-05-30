VERSION 5.00
Begin VB.UserControl PictureCtl 
   AutoRedraw      =   -1  'True
   BackColor       =   &H80000005&
   ClientHeight    =   3180
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   3375
   OLEDropMode     =   1  'Manual
   ScaleHeight     =   3180
   ScaleWidth      =   3375
End
Attribute VB_Name = "PictureCtl"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit
'Default Property Values:
Const m_def_PictureFileName = ""
'Property Variables:
Dim m_PictureFileName As String
'Event Declarations:
Event PictureChanged(PictureFileName As String)


Public Property Get PictureFileName() As String
Attribute PictureFileName.VB_Description = "FileName of bitmap to Display"
    PictureFileName = m_PictureFileName
End Property

Public Property Let PictureFileName(ByVal New_PictureFileName As String)
    m_PictureFileName = New_PictureFileName
On Error GoTo p_Err
    Picture = LoadPicture(New_PictureFileName)
    PropertyChanged "Picture"
    Exit Property
p_Err:
    MsgBox$ "Error Loading file: " & New_PictureFileName + Chr$(10) + Chr$(13) + Err.Description
    Picture = Nothing
    Me.Print New_PictureFileName & ":" & Chr$(10) + Chr$(13) & "Not an Image File"
End Property

'Initialize Properties for User Control
Private Sub UserControl_InitProperties()
    m_PictureFileName = m_def_PictureFileName
End Sub



'Load property values from storage
Private Sub UserControl_ReadProperties(PropBag As PropertyBag)
    m_PictureFileName = PropBag.ReadProperty("PictureFileName", m_def_PictureFileName)
End Sub

'Write property values to storage
Private Sub UserControl_WriteProperties(PropBag As PropertyBag)
    Call PropBag.WriteProperty("PictureFileName", m_PictureFileName, m_def_PictureFileName)
End Sub

Private Sub UserControl_OLEDragDrop(Data As DataObject, Effect As Long, Button As Integer, Shift As Integer, X As Single, Y As Single)
    
    If (Data.Files.Count > 0) Then
        PictureFileName = Data.Files.Item(1)
        RaiseEvent PictureChanged(Data.Files.Item(1))
    End If
    
End Sub
