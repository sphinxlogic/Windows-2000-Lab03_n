Attribute VB_Name = "Explorer"
Option Explicit


Private Sub Main()
Dim oExplorer As New fExplorer
    '
    ' Initialize
    '
    Initialize
    
    '
    ' Set the ADsPath:
    '
    If Command = "" Then
        oExplorer.SetADsPath "ADS://"
    Else
        oExplorer.SetADsPath Command
    End If
    
    '
    ' Show the explorer:
    '
    oExplorer.Show
End Sub

Sub StartInNewThread(ByVal lpVoid As Long)
    Dim oNewExplorer As fExplorer
    Dim sADsPath As String
    
    sADsPath = CStr(lpVoid)
    MsgBox sADsPath
    Exit Sub
    
    '
    ' Create a new explorer:
    '
    Set oNewExplorer = New fExplorer
    Load oNewExplorer
    
    '
    ' Inherit the toolbar settings in the new window:
    '
    'oNewExplorer.mnuViewToolbar.Checked = mnuViewToolbar.Checked
    'oNewExplorer.cbToolbar.Visible = mnuViewToolbar.Checked
    
    'If ((oNewExplorer.Width + Me.Left + 360) < Screen.Width) And _
    '   ((oNewExplorer.Height + Me.Top + 360) < Screen.Height) Then
    '    oNewExplorer.Top = Me.Top + 360
    '    oNewExplorer.Left = Me.Left + 360
    'End If
        
    '
    ' Point it to our child:
    '
    On Error Resume Next
    oNewExplorer.SetADsPath sADsPath
    If Err.Number <> 0 Then
        '
        ' Unload it:
        '
        Unload oNewExplorer
    Else
        '
        ' Display it:
        '
        oNewExplorer.Show
    End If
End Sub
