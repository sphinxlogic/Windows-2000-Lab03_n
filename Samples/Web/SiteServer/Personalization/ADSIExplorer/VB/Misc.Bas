Attribute VB_Name = "Misc"
Private Declare Function SendMessageByNum Lib "user32" Alias "SendMessageA" (ByVal hWnd As Long, ByVal wMsg As Long, ByVal wParam As Long, ByVal lParam As Long) As Long

' List View constants
Public Const lvs_ExGridLines = &H1
Public Const lvs_ExSubItemImages = &H2
Public Const lvs_ExCheckBoxes = &H4
Public Const lvs_ExTrackSelect = &H8
Public Const lvs_ExHeaderDragDrop = &H10
Public Const Lvs_ExFullRowSelect = &H20
Public Const lvs_ExOneClickActivate = &H40
Public Const lvs_ExTwoClickActivate = &H80
    
Private Const LVM_FIRST = &H1000
Private Const LVM_SETEXTENDEDLISTVIEWSTYLE = (LVM_FIRST + 54)
Private Const LVM_GETEXTENDEDLISTVIEWSTYLE = (LVM_FIRST + 55)


Public Function regGetSetting(ByRef sSection As String, ByRef sKey As String, Optional ByVal sDefault As String) As String
    regGetSetting = GetSetting(App.Title, sSection, sKey, sDefault)
End Function

'===============================================================================
' lvSetExtendedStyle (List View To Extend, New Style)
'   Sets the style of the list view to match the style passed.
'===============================================================================
Sub lvSetExtendedStyle(ByRef lvListView As ListView, ByVal lStyle As Long)
    Call SendMessageByNum(lvListView.hWnd, _
                          LVM_SETEXTENDEDLISTVIEWSTYLE, _
                          ByVal 0&, _
                          ByVal lStyle)
End Sub


'===============================================================================
' lvGetExtendedStyle (List View To Extend, New Style)
'   Returns the style of the list view specified.
'===============================================================================
Function lvGetExtendedStyle(ByRef lvListView As ListView) As Long
    lvGetExtendedStyle = SendMessageByNum(lvListView.hWnd, _
                                          LVM_GETEXTENDEDLISTVIEWSTYLE, _
                                          ByVal 0&, _
                                          ByVal 0&)
End Function



Public Sub regSaveSetting(ByVal sSection As String, ByVal sKey As String, ByVal sValue As String)
    SaveSetting App.Title, sSection, sKey, sValue
End Sub

